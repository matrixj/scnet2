#ifndef SCNET2_BASE_CONDITION_H
#define SCNET2_BASE_CONDITION_H

#include <pthread.h>
#include <stdint.h>

#include <base/mutexlock.h>
namespace scnet2 {

class Condition : boost::noncopyable {
 private:
  pthread_cond_t _cond;
  MutexLock& _lock;
 public:
  explicit Condition(MutexLock& lock) : _lock(lock) {
        ::pthread_cond_init(&_cond, NULL);
      }
  ~Condition() {
    ::pthread_cond_destroy(&_cond);
  }
  void wait() {
    ::pthread_cond_wait(&_cond, _lock.getRawLock());
  }
  void signal() {
    pthread_cond_signal(&_cond);
  }
  void broadcast() {
    pthread_cond_broadcast(&_cond);
  }

  //use seconds
  bool timedwait(int  waittime);
};
}
#endif
