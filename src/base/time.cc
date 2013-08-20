#include <base/time.h>
#include <base/timestamp.h>
#include <base/timer.h>
#include <base/atomic_int.h>

using namespace scnet2;

AtomicInt Time::_s_numCreated;

void Time::restart(Timestamp ts)
{
    if (_repeat)
    {
        _expiration = addTime(ts, _interval);
    } else {
        _expiration = Timestamp::invalid();
    }
}

TimerId::TimerId(Time *timer, const int64_t id)
    :_timer(timer),
     _id(id) { }

TimerId::TimerId()
  : _timer(NULL),
    _id(0) { }

TimerId::~TimerId()
{ }
