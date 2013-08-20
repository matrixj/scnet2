#include <base/baseloop.h>

#include <vector>
#include <string> //for LogBuffer constructor

#include <boost/bind.hpp>

#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <sys/eventfd.h>

#include <base/Timer.h>
#include <base/Time.h>
#include <base/Timestamp.h>
#include <base/Channel.h>
#include <base/CurrentThread.h>
#include <base/thread.h>
#include <net/poller.h>

#ifdef DEBUG
#include <base/logbuffer.h>
#endif


using namespace scnet2;
using namespace scnet2::base;
using namespace scnet2::net;

namespace{
const int kPollWaitTime = 10000;
__thread BaseLoop *g_loopInThread = 0;
#pragma GCC diagnostic error "-Wold-style-cast"""
}

BaseLoop::BaseLoop()
    : threadId_(CurrentThread::tid()),
      looping_(false),
      quit_(false),
      poll_(Poller::getEpoll(this)),
      timer_(new Timer(this)),
      wakeupfd_(createFd()),
      wakeupChannel_(new Channel(this, wakeupfd_)),
      log_("debug"){
  if (g_loopInThread) {
      perror("Another Loop run in this thread");
  } else {
      g_loopInThread = this;
  }

  wakeupChannel_->setReadCb(boost::bind(&BaseLoop::readWakeupfd, this));
  wakeupChannel_->enableRead();
  
  log_.start();
}

BaseLoop::~BaseLoop() {
  printf("BaseLoop destructs\n");
  g_loopInThread = NULL;
}

BaseLoop* BaseLoop::getLoopInThreadNum() {
  return g_loopInThread;
}

// Start looping  the base event loop
void BaseLoop::loop() {
  assert(!looping_);
  looping_ = true;
  quit_ = false;
  printf("Loop start looping\n");
  Channel *tmp;

  char msg[64];

  while (!quit_) {
    activeChannels_.clear();
    poll_->wait(kPollWaitTime, &activeChannels_);
    callingPollCbs_ = true;
    sprintf(msg, "Poller wait return %d activeChannels\n",
             static_cast<int>(activeChannels_.size()));
    log_.appendToBuffer(msg, static_cast<int>(strlen(msg)));
    
    printf("%s", msg);
    std::vector<Channel*>::iterator i = activeChannels_.begin();
    // Calling active Channels. The _activeChannels was copy from poller, no
    // need to be locked by mutexlock
    for (; i != activeChannels_.end(); i++) {
      tmp = *i;
      tmp->handleEvent();
    }
    callingQueueCbs_ = false;
    // Calling callback in the queue(Push main loop thread)
    printf("start to call handleQueueCb\n");
    handleQueueCb();
  }

  printf("Loop quit \n");
  looping_ = false;
}

void BaseLoop::handleQueueCb() {
  std::vector<Queuecb> tmp;
  callingQueueCbs_ = true;
  {
    MutexLockGuard lock(lock_);
    tmp.swap(queueCbs_);
  }
  for (size_t i = 0; i < tmp.size(); i++) {
    tmp[i]();
  }
  callingQueueCbs_ = false;
}

void BaseLoop::quit() {
  quit_ = true;
}

TimerId BaseLoop::runAt(const Timercb& cb, Timestamp ts) {
  return timer_->addTimer(cb, ts, 0.0);
}

void BaseLoop::updateChannel(Channel *c) {
  poll_->updateChannel(c);
}
void BaseLoop::runInLoop(const boost::function<void ()>& cb) {
  if (isInLoopThread()) {
    cb();
  } else {
    pushQueueInLoop(cb);
  }
}
bool BaseLoop::isInLoopThread() {
  return threadId_ == CurrentThread::tid();
}

void BaseLoop::pushQueueInLoop(const boost::function<void ()>& cb) {
  {
    MutexLockGuard lock(lock_);
    queueCbs_.push_back(cb);
  }

  if (!isInLoopThread() || callingQueueCbs_) {
    wakeupLoopThread();
  }
}



void BaseLoop::wakeupLoopThread() {
  uint64_t u;
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
  handleQueueCb();
}

int BaseLoop::createFd() {
  int fd = eventfd(0, EFD_CLOEXEC | EFD_NONBLOCK);
  if (fd == -1) {
    perror("eventfd");
  }
  return fd;
}
