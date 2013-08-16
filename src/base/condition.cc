#include <base/condition.h>

#include <stdio.h>
#include <time.h>
#include <string.h>

using namespace scnet2;

void Condition::timedwait(int timewait) {
  struct timespec ts;
  int rc;
  char tmp[64];
  clock_gettime(CLOCK_REALTIME, &ts);
  ts.tv_sec += timewait;

  rc = pthread_cond_timedwait(&_cond, _lock.getRawLock(), &ts);
  if (rc != 0) {
    fprintf(stderr, "Phtread_wait_timewait return error:%s .%s:%d\n",
            strerror_r(rc, tmp, sizeof tmp), __FILE__,
            __LINE__);
  }
}
