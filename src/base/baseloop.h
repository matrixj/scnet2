#ifndef SCNET2_BASE_BASELOOP_H_
#define SCNET2_BASE_BASELOOP_H_

#include <boost/noncopyable.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/function.hpp>

#include <base/Timer.h>
#include <base/Timestamp.h>
#include <base/TypedefCallback.h>
#include <base/thread.h>
#include <base/mutexlock.h>
#include <base/logbuffer.h>

namespace scnet2 {

namespace net {
class Poller;
}

namespace base {

//class Timer;
class TimerId;
class Channel;

class BaseLoop : boost::noncopyable {
  public:
   BaseLoop();
   ~BaseLoop();

   void loop();
   void quit();

  static BaseLoop* getLoopInThreadNum();

  TimerId runAt(const Timercb& cb, Timestamp ts);
  void runInLoop(const boost::function<void ()>&);
  void updateChannel(Channel *c);
  bool isInLoopThread();
  void pushQueueInLoop(const boost::function<void ()>&);

  private:
   int createFd();
   void abortNotLoopThread();
   void wakeupLoopThread();
   void handleQueueCb();
   void readWakeupfd();

   const pid_t threadId_;
   bool looping_;
   bool quit_;
   boost::scoped_ptr<net::Poller> poll_;
   boost::scoped_ptr<Timer> timer_;
   int wakeupfd_;
   std::vector<Queuecb> queueCbs_;
   bool callingQueueCbs_;
   boost::scoped_ptr<Channel> wakeupChannel_;
   std::vector<Channel*> activeChannels_;
   bool callingPollCbs_;
   MutexLock lock_;

   LogBuffer log_;
};

}
}
#endif
