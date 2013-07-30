#ifndef _SCNET2_BASE_TIME_H_
#define _SCNET2_BASE_TIME_H_

#include <base/TypedefCallback.h>
#include <base/AtomicInt.h>
#include <base/Timestamp.h>

#include <boost/noncopyable.hpp>

namespace scnet2 {
namespace base {

class Time;
class TimerId : scnet2::copyable {
    public:
        TimerId(Time *timer, int64_t id);
        ~TimerId();
        friend class Timer;
    private:
        Time *_timer;
        int64_t _id;

};
    
class Time : boost::noncopyable {
 public:
    Time(const Timercb& cb, Timestamp ts, double interval)
        : _callback(cb),
          _expiration(ts),
          _interval(interval),
          _repeat(interval > 0.0),
          _sequence(_s_numCreated.incrementAndGet()) { }

    void run() const {
        _callback();
    }

    Timestamp expiration() const {
        return _expiration;
    }

    int64_t sequence() const {
        return _sequence;
    }

    bool toRepeat() const {
        return _repeat;
    }

    void restart(Timestamp ts);
    static int64_t numCreated() {
        return _s_numCreated.get();
    }

    
 private:
  const Timercb _callback;
  Timestamp _expiration;
  const double _interval;
  const bool  _repeat;
  const int64_t _sequence;
    
  static AtomicInt _s_numCreated;

};
}
}

#endif
