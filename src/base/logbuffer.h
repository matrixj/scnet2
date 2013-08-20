#ifndef SCNET2_BASE_LOGBUFFER_H
#define SCNET2_BASE_LOGBUFFER_H

#include <boost/noncopyable.hpp>
#include <boost/ptr_container/ptr_vector.hpp>

#include <stdio.h>

#include <base/mutexlock.h>
#include <base/condition.h>
#include <base/buffer.h>
#include <base/thread.h>
#include <base/countdown_latch.h>

namespace scnet2 {
//namespace base {

class LogBuffer : boost::noncopyable {
 public:
  LogBuffer(const std::string& basename);
  ~LogBuffer() {
    if (_logging) {
      stop();
    }
  }
  void appendToBuffer(const char *str, int len);

  void start() {
    _logging = true;
    _thread.start();
    latch_.wait();
  }

 private:
  LogBuffer(const LogBuffer&);
  void operator=(const LogBuffer&);

  void stop() {
    _logging = false;
    _cond.signal();
    printf("going to stop main thread\n");
    _thread.join();
  }

  //TODO:change buffer size to satisfied  the CPU cache line;
  typedef detail::Buffer<64 * 1024> BufferType;
  typedef boost::ptr_vector<BufferType> BufferVector;
  typedef BufferVector::auto_type VecTypePtr;
  void threadFunc();

  const int kCondWaitTime;
  VecTypePtr _current;
  VecTypePtr _next;
  BufferVector _bufferVector;
  Thread _thread;
  const string _basename;
  bool _logging;

  MutexLock _lock;
  Condition _cond;
  CountDownLatch latch_;

//}
};
}
#endif
