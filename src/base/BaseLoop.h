#ifndef SCNET2_BASE_BASELOOP_H_
#define SCNET2_BASE_BASELOOP_H_

#include <boost/noncopyable.hpp>

//#include <base/Thread.hpp>

namespace scnet2
{
namespace base 
{

class BaseLoop : boost::noncopyable
{
    public:
     BaseLoop();
     ~BaseLoop();

     void loop();
     void quit();

    static BaseLoop* getLoopInThreadNum();

    private:
     void abortNotLoopThread();
     //const pid_t _threadId;
     bool _looping;
     bool _quit;
};

}
}
#endif
