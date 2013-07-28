#include <base/Time.h>

using namespace scnet2;
using namespace scnet2::base;

AtomicInt64 Time::_s_numCreated;

void Time::restart(Timestamp ts)
{
    if (_repeat)
    {
        _expiration = addTime(ts, _interval)
    } else {
        _expiration = Timestamp::invalid();
    }
}
