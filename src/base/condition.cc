#include <base/condition.h>

#include <stdio.h>
#include <time.h>

using namespace scnet2;

void Condition::timedwait(int timewait) {
  struct timespec ts;
  int rc;
  clock_gettime(CLOCK_REALTIME, &ts);
  ts.tv_sec += static_cast<time_t>(10);

  rc = pthread_cond_timedwait(&_cond, _lock.getRawLock(), &ts);
  if (rc != 0) {
    fprintf(stderr, "Phtread_wait_timewait return error .%s:%d", __FILE__,
            __LINE__);
  }
}
