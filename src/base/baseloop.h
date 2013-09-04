#ifndef SCNET2_BASE_BASELOOP_H_
#define SCNET2_BASE_BASELOOP_H_

#include <boost/noncopyable.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/function.hpp>

#include <base/timer.h>
#include <base/timestamp.h>
#include <base/typedef_callback.h>
#include <base/thread.h>
#include <base/mutexlock.h>
#include <base/logbuffer.h>

#define LOG_DEBUG(str) { \
  char fmt[64]; \
    int n = sprintf(fmt, "%s %s:%d %d\n", str, __FILE__, __LINE__, CurrentThread::tid()); \
    log_.appendToBuffer((fmt), n); \
}
#define LOG_ERROR(str) LOG_DEBUG(str) \
    abord();

namespace scnet2 {

namespace net {
class Poller;
}

//namespace base {

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

  TimerId addTimer(const Timercb& cb, const Timestamp& ts);
  void delegate(const boost::function<void ()>&);
  void updateChannel(Channel *c);
  bool isInLoopThread();
  void pushQueueInLoop(const boost::function<void ()>);

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

//}
}// End of scnet2 namespace
#endif
