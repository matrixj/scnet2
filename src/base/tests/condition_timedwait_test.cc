#include <base/condition.h>
#include <base/mutexlock.h>
#include <base/thread.h>
#include <base/countdown_latch.h>

#include <stdio.h>

using namespace scnet2;

MutexLock lock;
Condition cond(lock);
int n;
CountDownLatch latch(1);

void func() {
  int rc ;
  MutexLockGuard lock_(lock);
  latch.countDown(); 
  if (n == 0) {
    rc = cond.timedwait(3);
  }
  if (rc)
    printf("timeout error\n");
  printf("time up\n");
}

int main() {
  Thread thread(func);
  thread.start();

  latch.wait();
  sleep(4);
  thread.join();
}
