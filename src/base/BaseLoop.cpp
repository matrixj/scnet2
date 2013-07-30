#include <base/BaseLoop.h>
#include <base/Timer.h>
#include <base/Time.h>
#include <base/Timestamp.h>
#include <base/Channel.h>
#include <base/CurrentThread.h>
#include <base/Thread.h>

#include <boost/bind.hpp>

#include <assert.h>
#include <stdio.h>

using namespace scnet2;
using namespace scnet2::base;

namespace{
__thread BaseLoop *g_loopInThread = 0;
#pragma GCC diagnostic error "-Wold-style-cast"""
}

BaseLoop::BaseLoop()
    : _threadId(CurrentThread::tid()),
      _looping(false),
      _quit(false),
      _timer(new Timer(this))
{
        if (g_loopInThread) {
            perror("Another Loop run in this thread");
        } else {
            g_loopInThread = this;
        }
}

BaseLoop::~BaseLoop()
{
        printf("Loop destructs in thread \n");
        g_loopInThread = NULL;
}

BaseLoop* BaseLoop::getLoopInThreadNum()
{
        return g_loopInThread;
}

void BaseLoop::loop()
{
        assert(!_looping);
        _looping = true;
        printf("Loop start looping\n");

        while (!_quit) {
            //do somethings...

        }
        printf("Loop quit \n");
        _looping = false;
}

void BaseLoop::quit()
{
        _quit = true;
}

TimerId BaseLoop::runAt(const Timercb& cb, Timestamp ts)
{
    return _timer->addTimer(cb, ts, 0.0);
}

void BaseLoop::updateChannel(Channel *c) {

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
  
}
