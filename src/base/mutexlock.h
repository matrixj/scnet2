#ifndef SCNET2_BASE_MUTEXLOCK_H
#define SCNET2_BASE_MUTEXLOCK_H

#include <boost/scoped_ptr.hpp>
#include <boost/noncopyable.hpp>

#include <pthread.h>

#include <base/CurrentThread.h>
namespace scnet2 {

class Holder : boost::noncopyable{
 private:
  pthread_mutex_t _lock;
  pid_t _locker;
 public:
  Holder() {
    ::pthread_mutex_init(&_lock, NULL);
  }
  void unlock() {
    ::pthread_mutex_unlock(&_lock);
    _locker = 0;
  }
  ~Holder() {
    assert(_locker == 0);
    ::pthread_mutex_destroy(&_lock);
  }
  void lock() {
    assert(_locker != CurrentThread::tid());
    ::pthread_mutex_lock(&_lock);
    _locker = CurrentThread::tid();
  }
  pthread_mutex_t *getLock() {
    return &_lock;
  }
};


class MutexLock : boost::noncopyable {
 private:
  boost::scoped_ptr<Holder> _lock;
 public:
  MutexLock() : _lock(new Holder) { }
  ~MutexLock() {
    _lock->unlock();
  }
  void unlock() {
    _lock->unlock();
  }
  void lock() {
    _lock->lock();
  }
  pthread_mutex_t *getRawLock() {
    return _lock->getLock();
  }
};

class MutexLockGuard : boost::noncopyable {
 private:
  friend class Condition;
  MutexLock& _lock;
 public:
  MutexLockGuard(MutexLock& lock) : _lock(lock) {
    _lock.lock();
  }
  ~MutexLockGuard() { _lock.unlock(); }
};

}
#endif
