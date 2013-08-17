#include <base/condition.h>

#include <stdio.h>
#include <time.h>
#include <errno.h>

using namespace scnet2;

bool Condition::timedwait(int timewait) {
  struct timespec ts;
  clock_gettime(CLOCK_REALTIME, &ts);
  ts.tv_sec += timewait;

  return ETIMEDOUT == pthread_cond_timedwait(&_cond, _lock.getRawLock(), &ts);
}
