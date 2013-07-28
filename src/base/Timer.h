#ifndef SCNET2_BASE_TIMER_H_
#define SCNET2_BASE_TIMER_H_

#include <base/timer.h>

#include <boost/noncopyable.hpp>

namespace scnet2
{
namespace base
{
    class Timer : boost::noncopyable
    {
        public:
            Timer(BaseLoop* loop);
            ~Timer();

            TimerId addTimer(const Timercb& cb,
                            Timerstamp time,
                            double interval);

            void cancle(TimerId timerId);

        private:
            typedef std::pair<Timerstamp, Timer*> TimerMap;
            typedef std::set<TimerMap> timerList;
            typedef std::pair<Timer*, int64_t>  endTimer;
            typedef std::set<endTimer> endTimerList;  

            void reset(const std::vector<TimerMap>& exp, Timestamp ts);
            bool insert(Time* time);
            BaseLoop *_loop;
            const int _timerfd;
            Channel _channel;
            timerList _timerList;
            endTimerList _endTimerList;
            bool _callingExpiredTimers;

            endTimerList _cancelingTimers;


    };
}
}


#endif
