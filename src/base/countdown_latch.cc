#include <base/countdown_latch.h>

#include <base/mutexlock.h>
#include <base/condition.h>

#include <stdio.h>
#include <string.h>

using namespace scnet2;

CountDownLatch::CountDownLatch(int count) 
  : lock_(),
    cond_(lock_),
    count_(count) { }

void CountDownLatch::countDown() {
  MutexLockGuard lock(lock_);
  --count_;
  if (count_ == 0) {
    //TODO:Change to "signalAll"
    cond_.signal();
  }
}

void CountDownLatch::wait() {
  MutexLockGuard lock(lock_);
  while (count_ > 0) {
    cond_.wait();
  }
}
