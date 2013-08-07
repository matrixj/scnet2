#ifndef SCNET2_BASE_TIMER_H_
#define SCNET2_BASE_TIMER_H_

#include <set>
#include <vector>

#include <base/Time.h>
#include <base/Timestamp.h>
#include <base/TypedefCallback.h>
#include <base/Channel.h>

#include <boost/noncopyable.hpp>

namespace scnet2
{
namespace base
{
    class BaseLoop;
    //class TimerId;
    class Time;
    //class Channel;

    class Timer : boost::noncopyable
    {
        public:
            Timer(BaseLoop* loop);
            ~Timer();

            TimerId addTimer(const Timercb& cb,
                            Timestamp time,
                            double interval);

            void addTimerLoop(Time *t);

            void cancle(TimerId timerId);

            void readcb();

        private:
            typedef std::pair<Timestamp, Time*> TimerMap;
            typedef std::set<TimerMap> timerList;
            typedef std::pair<Time*, int64_t>  endTimer;
            typedef std::set<endTimer> endTimerList;  

            std::vector<TimerMap> getExpired(const Timestamp);
            void reset(const std::vector<TimerMap>& exp, Timestamp ts);
            bool insert(Time* time);
            BaseLoop *_loop;
            const int _timerfd;
            Channel _channel;
            timerList _timerList;
            endTimerList _endTimerList;
            bool _callingExpiredTimers;

            //timerList _timers;

            endTimerList _cancelingTimers;


    };
}
}


#endif
