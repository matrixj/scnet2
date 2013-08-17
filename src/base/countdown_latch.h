#ifndef SCNET2_BASE_COUNTDOWN_LATCH_H
#define SCNET2_BASE_COUNTDOWN_LATCH_H

#include <base/mutexlock.h>
#include <base/condition.h>

namespace scnet2 {

class CountDownLatch {
 private:
  MutexLock lock_;
  Condition cond_;
  int count_;

 public:
  CountDownLatch(int count);
  ~CountDownLatch() { }
  void countDown(); 
  void wait();
};
}

#endif
