#include <base/Time.h>
#include <base/Timestamp.h>
#include <base/Timer.h>
#include <base/AtomicInt.h>

using namespace scnet2;
using namespace scnet2::base;

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
