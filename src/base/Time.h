#ifndef _SCNET2_BASE_TIME_H_
#define _SCNET2_BASE_TIME_H_

namespace scnet2
{
namespace base
{
class Time : boost::noncopyable
{
    Timer(const TimerCb& cb, Timestamp ts, double interval)
        : _callback(cb),
          _expiration(ts),
          _interval(interval),
          _repeat(interval > 0.0)
          _sequence(_s_numCreated.incrementAndGet())
    {

    }

    void run() const
    {
        _callback();
    }

    Timestamp expiration() const
    {
        return _expiration;
    }

    int64_t sequence() const 
    {
        return _sequence;
    }

    bool repeat() const
    {
        return _repeat;
    }

    void restart(Timestamp ts);
    static int64_t numCreated() 
    {
        return _s_numCreated.get();
    }

    private:
    const TimerCb _callback;
    Timestamp _expiration;
    const double _interval;
    const bool  _repeat;
    const int64_t _sequence;
    
    static AtomicInt64 _s_numCreated;

};
}
}

#endif
