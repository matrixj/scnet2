#include <base/condition.h>
#include <base/thread.h>
#include <base/mutexlock.h>

#include <stdio.h>
using namespace scnet2;

MutexLock lock;
Condition cond(lock);
int n;

void func() {
  sleep(2);
  MutexLockGuard lock_(lock);
  while (n == 0) {
    cond.wait();
  }
  printf("func received signal\n");
}

int main()  {
  Thread thread(func, "condtion test");

  thread.start();
  printf("main thread signal now\n");

  n = 1;
  cond.signal();
  thread.join();
}
