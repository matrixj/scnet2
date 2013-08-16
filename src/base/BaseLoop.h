#ifndef SCNET2_BASE_BASELOOP_H_
#define SCNET2_BASE_BASELOOP_H_

#include <boost/noncopyable.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/function.hpp>

#include <base/Timer.h>
#include <base/Timestamp.h>
#include <base/TypedefCallback.h>
#include <base/thread.h>

namespace scnet2
{
namespace net {
class Poller;
}
namespace base 
{

//class Timer;
class TimerId;
class Channel;

class BaseLoop : boost::noncopyable
{
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

     const pid_t _threadId;
     bool _looping;
     bool _quit;
     boost::scoped_ptr<net::Poller> _poll;
     boost::scoped_ptr<Timer> _timer;
     int _wakeupfd;
     std::vector<Queuecb> _queueCbs;
     bool _callingQueueCbs;
     boost::scoped_ptr<Channel> _wakeupChannel;
     std::vector<Channel*> _activeChannels;
     bool _callingPollCbs;
};

}
}
#endif
