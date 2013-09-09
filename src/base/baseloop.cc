#include <base/baseloop.h>

#include <vector>
#include <string> //for LogBuffer constructor

#include <boost/bind.hpp>

#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <sys/eventfd.h>

#include <base/timer.h>
#include <base/time.h>
#include <base/timestamp.h>
#include <base/event.h>
#include <base/current_thread.h>
#include <base/thread.h>
#include <net/poller.h>

#ifdef DEBUG
#include <base/logbuffer.h>
#endif


using namespace scnet2;
using namespace scnet2::net;

namespace{
const int kPollWaitTime = 5000;
__thread BaseLoop *g_loopInThread = 0;
}

BaseLoop::BaseLoop()
    : threadId_(CurrentThread::tid()),
      looping_(false),
      quit_(false),
      poll_(Poller::getEpoll(this)),
      timer_(new Timer(this)),
      wakeupfd_(createFd()),
      wakeupEvent_(new Event(this, wakeupfd_)),
      log_("debug"){
  if (g_loopInThread) {
      perror("Another Loop run in this thread");
  } else {
      g_loopInThread = this;
  }

  wakeupEvent_->setReadCb(boost::bind(&BaseLoop::readWakeupfd, this));
  wakeupEvent_->enableRead();
  
  log_.start();
}

BaseLoop::~BaseLoop() {
  LOG_DEBUG("BaseLoop destroctor");
  g_loopInThread = NULL;
}


// Start looping  the base event loop
void BaseLoop::start() {
  LOG_DEBUG("bseLoop::loop start to loop");

  assert(!looping_);
  looping_ = true;
  quit_ = false;
  uint32_t flags;
  char msg[64];

  while (!quit_) {
    callingPollCbs_ = true;
    poll_->processEvent(kPollWaitTime, &flags);

    handleQueueCb();
  }
  LOG_DEBUG("BaseLoop::loop is going to stop");
  looping_ = false;
}

void BaseLoop::handleQueueCb() {
  std::vector<Queuecb> tmp;
  callingQueueCbs_ = true;
  {
    MutexLockGuard lock(lock_);
    tmp.swap(queueCbs_);
  }

  LOG_DEBUG("handleQueueCb call");
  for (size_t i = 0; i < tmp.size(); i++) {
    tmp[i]();
  }
  callingQueueCbs_ = false;
}

void BaseLoop::quit() {
  quit_ = true;
}

TimerId BaseLoop::addTimer(const Timercb& cb, const Timestamp& ts) {
  return timer_->addTimer(cb, ts, 0.0);
}

void BaseLoop::updateEvent(Event *c) {
  poll_->updateEvent(c);
}

void BaseLoop::delegate(const boost::function<void ()>& cb) {
  LOG_DEBUG("Add callback to queuq in loop");
  if (isInLoopThread()) {
    cb();
  } else {
    LOG_DEBUG("Another thread add callback to loop thread");
    pushQueueInLoop(cb);
  }
}

bool BaseLoop::isInLoopThread() {
  return threadId_ == CurrentThread::tid();
}

void BaseLoop::pushQueueInLoop(const boost::function<void ()> cb) {
  {
    MutexLockGuard lock(lock_);
    queueCbs_.push_back(cb);
  }

  if (!isInLoopThread() || callingQueueCbs_) {
    // QueueCbs use COW, so if callback in queue call @pushQueueInLoop we must 
    // wakeup when callingPollCbs_ is ture so that the event loop can process
    // it as soon as posiable
    wakeupLoopThread();
  }
}

void BaseLoop::wakeupLoopThread() {
  uint64_t u;
  LOG_DEBUG("To wakeupLoopThread");
  if (::write(wakeupfd_, &u, sizeof u) != sizeof u) {
    perror("write to wakeupfd");
  }
} 

void BaseLoop::readWakeupfd() {
  uint64_t u;
  ssize_t n = ::read(wakeupfd_, &u, sizeof u);
  if (n != sizeof n) {
    perror("read wakefd");
  }
  // Don't call handleQueueCb here, because it will clear the queueCbs which
  // will call later by other Event
  //handleQueueCb();
}

int BaseLoop::createFd() {
  int fd = eventfd(0, EFD_CLOEXEC | EFD_NONBLOCK);
  if (fd == -1) {
    perror("eventfd");
  }
  return fd;
}
