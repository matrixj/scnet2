#include <base/Timer.h>
#include <base/BaseLoop.h>

#include <boost/bind.hpp>

#include <sys/timerfd.h>

namespace scnet2
{
namespace base
{
namespace more
{
int createTimerfd()
{
    int fd = ::timerfd_create(CLOCK_MONOTONIC, TFD_NONBLOCK | TFD_CLOEXEC);

    if (fd < 0) {
        perror("tiemrfd_create");
        exit(0);
    }
    return fd;
}

struct timerspec howMuchTimerFromNow(Timerstamp t)
{
    int64_t ms = t.microSecondsSinceEpoch()
                    - Timerstamp::now().microSecondsSinceEpoch();
    if (ms < 100) {
        ms = 100;
    }
    struct timespec ts;
    ts.tv_sec = static_cast<time_t>(ms / Timerstamp::kMicroSecondsPerSecond);
    ts.tv_nsec = static_cast<long>(ms % Timerstamp::kMicroSecondsPerSecond)
    return ts;
}

void readTimerfd(int fd, Timerstamp t)
{
    uint64_t rdbuf;
    ssize_t n = ::read(fd, &rdbuf, sizeof rdbuf);
    if (n != sizeof rdbuf) {
        perror("readTimerfd");
    }
}

void resetTimerfd(int fd, Timerstamp expiration)
{
    struct itimerspec newTimerspec;
    struct itimerspec oldTimerspec;
    bzero(&newTimerspec, sizeof newTimerspec);
    bzero(&oldTimerspec, sizeof oldTimerspec);
    newTimerspec.it_value = howMuchTimerFromNow(expiration);

    int ret = ::timerfd_settime(fd, 0, &newTimerspec, &oldTimerspec);
    if (ret) {
        perror("timerfd_settime");
    }
}

}

}
}

using namespace scnet2;
using namespace scnet2::base;
using namespace sncet2::base:detail

Timer::Timer(BaseLoop *loop)
    :_loop(loop)
     _timerfd(createTimerfd()),
     _timers(),
     _callingExpiredTimers(false)
{
    _channel.setReadCb(
        boost::bind(&Timer::readCb, this));
    _channel.enableRead();

}

Timer::~Timer()
{
    ::close(_timerfd);
    for (timerList::iterator i = _timerList.begin();
        i != _timerList.end(); i++) {
            delete i->second;
        }
}

TimerId Timer::addTimer(const TimerCb& cb,
                       Timestamp ts,
                       double interval)
{
    Time *t = new Time(cb, ts, interval);
    _loop->runInLoop(
        boost::bind(&Timer::addTimerLoop, this, t));
    return TimerId(timer, timer->sequence());
}

void Timer::addTimerLoop(Time *t)
{
    bool firstChaneged = insert(t);

    if (firstChaneged) {
        resetTimerfd(_timerfd, t->expiration());
    }
}


void Timer::handleRead()
{
    Timestamp ts(Timestamp::now());
    readTimerfd(_timerfd, ts);

    std::vector<TimerMap> expired = getExpired(ts);
    _callingExpiredTimers = ture;
    
    for (std::vector<TimerMap>::iterator i = expired.begin();
        i != expired.end(); ++i) {
            i->second->run();
        }
    _callingExpiredTimers = false;
    reset(expired, ts);
}

void Timer::reset(const std::vector<TimerMap>& expired, Timestamp ts)
{
    Timestamp nextExpire;
    for (std::vector<TimerMap>::const_iterator i = expired.begin();
        i != expired.end(); ++i) {
            endTimer timer(i->second, i->second->sequence());
            //if the timer was setted to repeat and not be canceled
            if (i->second->repeat()
               && _cancelingTimers.find(timer) == _cancelingTimers.end()) {
                   i->second->restart(ts);
                   insert(i->second);
               }

        }

}

//TODO:Add cancle timer

//If the the time is early then the first time in _timerlist,then must reset the timerfd by timerfd_settime immediately
bool Timer::insert(Time* t)
{
    bool firstChaneged = false;
    Timestamp ts = t->expiration();
    timerList::iterator i = _timerList.begin();
    if (i == _timerList.end() || ts < i->first) {
        firstChaneged = true;
    }
    {
        std::pair<timerList::iterator, bool> ret
        = _timerList.insert(TimerMap(ts, t));
        assert(ret.second); (void)ret;
    }
    {
        std::pair<endTimerList::iterator, bool> ret
        =_endTimerList.insert(endTimer(t, t->sequence()));
        assert(ret.second); (void)ret;
    }

    return firstChaneged;
}
