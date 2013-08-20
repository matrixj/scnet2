#include <base/timestamp.h>

#include <sys/time.h>

using namespace scnet2;

Timestamp::Timestamp(int64_t m)
    :_microSecondsSinceEpoch(m) { }

Timestamp::Timestamp() 
  :_microSecondsSinceEpoch(0) { }
Timestamp Timestamp::now()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    int64_t s = tv.tv_sec;
    return Timestamp(s * microSecondsPersecond + tv.tv_usec);
}

Timestamp Timestamp::invalid()
{
    return Timestamp(0);
}


