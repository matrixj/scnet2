#ifndef SCNET2_BASE_BASELOOP_H_
#define SCNET2_BASE_BASELOOP_H_

#include <base/Timer.h>
#include <base/Timestamp.h>
#include <base/TypedefCallback.h>

#include <boost/noncopyable.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/function.hpp>

#include <base/Thread.h>

namespace scnet2
{
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
     void abortNotLoopThread();
     const pid_t _threadId;
     bool _looping;
     bool _quit;
     boost::scoped_ptr<Timer> _timer;
};

}
}
#endif
