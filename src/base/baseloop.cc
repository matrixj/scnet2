#include <base/baseloop.h>

#include <vector>

#include <boost/bind.hpp>

#include <assert.h>
#include <stdio.h>
#include <sys/eventfd.h>

#include <base/Timer.h>
#include <base/Time.h>
#include <base/Timestamp.h>
#include <base/Channel.h>
#include <base/CurrentThread.h>
#include <base/thread.h>
#include <net/poller.h>


using namespace scnet2;
using namespace scnet2::base;
using namespace scnet2::net;

namespace{
const int kPollWaitTime = 10000;
__thread BaseLoop *g_loopInThread = 0;
#pragma GCC diagnostic error "-Wold-style-cast"""
}

BaseLoop::BaseLoop()
    : _threadId(CurrentThread::tid()),
      _looping(false),
      _quit(false),
      _poll(Poller::getEpoll(this)),
      _timer(new Timer(this)),
      _wakeupfd(createFd()),
      _wakeupChannel(new Channel(this, _wakeupfd)) {
        if (g_loopInThread) {
            perror("Another Loop run in this thread");
        } else {
            g_loopInThread = this;
        }

        _wakeupChannel->setReadCb(boost::bind(&BaseLoop::readWakeupfd, this));
        _wakeupChannel->enableRead();
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
  assert(!_looping);
  _looping = true;
  _quit = false;
  printf("Loop start looping\n");
  Channel *tmp;

  while (!_quit) {
    _activeChannels.clear();
    _poll->wait(kPollWaitTime, &_activeChannels);
    _callingPollCbs = true;
    std::vector<Channel*>::iterator i = _activeChannels.begin();
    // Calling active Channels. The _activeChannels was copy from poller, no
    // need to be locked by mutexlock
    for (; i != _activeChannels.end(); i++) {
      tmp = *i;
      tmp->handleEvent();
    }
    _callingQueueCbs = false;
    // Calling callback in the queue(Push main loop thread)
    printf("start to call handleQueueCb\n");
    handleQueueCb();
  }

  printf("Loop quit \n");
  _looping = false;
}

void BaseLoop::handleQueueCb() {
  std::vector<Queuecb> tmp;
  _callingQueueCbs = true;
  {
    MutexLockGuard lock(lock_);
    tmp.swap(_queueCbs);
  }
  for (size_t i = 0; i < tmp.size(); i++) {
    tmp[i]();
  }
  _callingQueueCbs = false;
}

void BaseLoop::quit() {
  _quit = true;
}

TimerId BaseLoop::runAt(const Timercb& cb, Timestamp ts) {
  return _timer->addTimer(cb, ts, 0.0);
}

void BaseLoop::updateChannel(Channel *c) {
  _poll->updateChannel(c);
}
void BaseLoop::runInLoop(const boost::function<void ()>& cb) {
  if (isInLoopThread()) {
    cb();
  } else {
    pushQueueInLoop(cb);
  }
}
bool BaseLoop::isInLoopThread() {
  return _threadId == CurrentThread::tid();
}

void BaseLoop::pushQueueInLoop(const boost::function<void ()>& cb) {
  {
    MutexLockGuard lock(lock_);
    _queueCbs.push_back(cb);
  }

  if (!isInLoopThread() || _callingQueueCbs) {
    wakeupLoopThread();
  }
}



void BaseLoop::wakeupLoopThread() {
  uint64_t u;
  if (::write(_wakeupfd, &u, sizeof u) != sizeof u) {
    perror("write to wakeupfd");
  }
} 

void BaseLoop::readWakeupfd() {
  uint64_t u;
  ssize_t n = ::read(_wakeupfd, &u, sizeof u);
  if (n != sizeof n) {
    perror("read wakefd");
  }
  handleQueueCb();

}

int BaseLoop::createFd() {
  int fd = eventfd(0, EFD_CLOEXEC | EFD_NONBLOCK);
  if (_wakeupfd == -1) {
    perror("eventfd");
  }
  return fd;
}
