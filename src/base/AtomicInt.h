#ifndef SCNET2_BASE_ATOMICTYPE_H
#define SCNET2_BASE_ATOMICTYPE_H

#include <boost/noncopyable.hpp>
#include <stdint.h>

namespace scnet2 {
class AtomicInt : boost::noncopyable {
 public:
  AtomicInt()
      : _value(0)
        { }
  int64_t get() {
    return __sync_val_compare_and_swap(&_value, 0, 0);
  }
  int64_t  getAndIncrement(int64_t x) {
    return __sync_fetch_and_add(&_value, x);
  }

  int64_t add(int64_t x) {
    return __sync_add_and_fetch(&_value, x);
  }

  int64_t incrementAndGet() {
    return add(1);
  }
  int64_t decrementAndGet() {
    return add(-1);
  }

  int64_t getAndSet(int64_t x) {
    return __sync_lock_test_and_set(&_value, x);
  }

 private:
  volatile int64_t _value;
};
}

#endif
