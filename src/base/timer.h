#ifndef SCNET2_BASE_TIMER_H_
#define SCNET2_BASE_TIMER_H_

#include <set>
#include <vector>

#include <base/time.h>
#include <base/timestamp.h>
#include <base/typedef_callback.h>
#include <base/channel.h>

#include <boost/noncopyable.hpp>

namespace scnet2 {
class BaseLoop;
//class TimerId;
class Time;
//class Channel;

class Timer : boost::noncopyable {
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
    typedef std::pair<Timestamp, Time*> TimerPair;
    typedef std::set<TimerPair> TimerPairSet;
    typedef std::pair<Time*, int64_t>  OverdueTimer;
    typedef std::set<OverdueTimer> OverdueTimerSet;

    std::vector<TimerPair> getExpired(const Timestamp);
    void reset(const std::vector<TimerPair>& exp, Timestamp ts);
    bool insert(Time* time);
    BaseLoop *_loop;
    const int _timerfd;
    Channel _channel;
    TimerPairSet _timerPairSet;
    OverdueTimerSet _overdueTimerList;
    bool _callingExpiredTimers;

    //timerList _timers;

    OverdueTimerSet _cancelingTimers;
};
}// End of namespace scnet2


#endif
