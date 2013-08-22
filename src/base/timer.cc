#include <base/timer.h>
#include <boost/bind.hpp>

#include <stdio.h>
#include <sys/timerfd.h>
#include <sys/time.h>

#include <base/time.h>
#include <base/baseloop.h>
#include <base/timestamp.h>
#include <base/channel.h>
#include <base/timestamp.h>


namespace scnet2 {

namespace detail {

int createTimerfd() {
    int fd = ::timerfd_create(CLOCK_MONOTONIC, TFD_NONBLOCK | TFD_CLOEXEC);

    if (fd < 0) {
        perror("tiemrfd_create");
        exit(0);
    }
    return fd;
}

struct timespec howMuchTimerFromNow(Timestamp t) {
    int64_t ms = t.microSecondsSinceEpoch()
                    - Timestamp::now().microSecondsSinceEpoch();
    if (ms < 100) {
        ms = 100;
    }
    struct timespec ts;
    ts.tv_sec = static_cast<time_t>(ms / 1000000);
    ts.tv_nsec = static_cast<long>((ms % 1000000) *
                                   1000 );
    return ts;
}

void readTimerfd(int fd, Timestamp t) {
    uint64_t rdbuf;
    ssize_t n = ::read(fd, &rdbuf, sizeof rdbuf);
    if (n != sizeof rdbuf) {
        perror("readTimerfd");
    }
}

void resetTimerfd(int fd, Timestamp expiration) {
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

}// End of namespace detail
}// End of namespace scnet2


using namespace scnet2;
using namespace scnet2::detail;

Timer::Timer(BaseLoop *loop)
    : _loop(loop),
      _timerfd(createTimerfd()),
      _channel(loop, _timerfd),
      _timerPairSet(),
      _callingExpiredTimers(false) {
    _channel.setReadCb(
        boost::bind(&Timer::readcb, this));
    _channel.enableRead();
}

Timer::~Timer() {
    ::close(_timerfd);
    for (TimerPairSet::iterator i = _timerPairSet.begin();
        i != _timerPairSet.end(); i++) {
            delete i->second;
        }
}

TimerId Timer::addTimer(const Timercb& cb,
                       Timestamp ts,
                       double interval) {
  // Time del in the close of Timer
  Time *t = new Time(cb, ts, interval);
  _loop->runInLoop(boost::bind(&Timer::addTimerLoop, this, t));

  return TimerId(t, t->sequence());
}

void Timer::addTimerLoop(Time *t) {
  bool firstChaneged = insert(t);
  if (firstChaneged) {
    resetTimerfd(_timerfd, t->expiration());
  }
}

void Timer::readcb() {
    Timestamp ts(Timestamp::now());
    readTimerfd(_timerfd, ts);

    std::vector<TimerPair> expired = getExpired(ts);
    _callingExpiredTimers = true;
    
    for (std::vector<TimerPair>::iterator i = expired.begin();
        i != expired.end(); ++i) {
            i->second->run();
        }
    _callingExpiredTimers = false;
    reset(expired, ts);
}

std::vector<Timer::TimerPair> Timer::getExpired(const Timestamp ts) {
  std::vector<TimerPair> expired;
  TimerPair tp = std::make_pair(ts, reinterpret_cast<Time*>(UINT_MAX));
  TimerPairSet::iterator i = _timerPairSet.lower_bound(tp);
  std::copy(_timerPairSet.begin(), i, back_inserter(expired));
  _timerPairSet.erase(_timerPairSet.begin(), i);
  return expired;
}

void Timer::reset(const std::vector<TimerPair>& expired, Timestamp ts) {
  Timestamp nextExpire;
  for (std::vector<TimerPair>::const_iterator i = expired.begin();
    i != expired.end(); ++i) {
      OverdueTimer timer(i->second, i->second->sequence());
      //if the timer was setted to repeat and not be canceled
      if (i->second->repeat()
         && _cancelingTimers.find(timer) == _cancelingTimers.end()) {
             i->second->restart(ts);
             insert(i->second);
         }

    }
}

//TODO:Add cancle timer

// If the time is early then the first timer in _timerPairSet,
// then must reset the timerfd by timerfd_settime immediately
bool Timer::insert(Time* t) {
  bool firstChaneged = false;
  Timestamp ts = t->expiration();
  TimerPairSet::iterator i = _timerPairSet.begin();
  if (i == _timerPairSet.end() || ts < i->first) {
      firstChaneged = true;
  }
  {
      std::pair<TimerPairSet::iterator, bool> ret
          = _timerPairSet.insert(TimerPair(ts, t));
      assert(ret.second); (void)ret;
  }
  {
      std::pair<OverdueTimerSet::iterator, bool> ret
          =_overdueTimerList.insert(OverdueTimer(t, t->sequence()));
      assert(ret.second); (void)ret;
  }

  return firstChaneged;
}
