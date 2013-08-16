#ifndef SCNET2_BASE_LOGBUFFER_H
#define SCNET2_BASE_LOGBUFFER_H

#include <boost/noncopyable.hpp>
#include <boost/ptr_container/ptr_vector.hpp>

#include <base/mutexlock.h>
#include <base/condition.h>
#include <base/buffer.h>
#include <base/thread.h>
#include <base/countdown_latch.h>

namespace scnet2 {
//namespace base {

class LogBuffer : boost::noncopyable {
 private:
  LogBuffer(const LogBuffer&);
  void operator=(const LogBuffer&);

  void stop() {
    _logging = false;
    _cond.signal();
    _thread.join();
  }

  //TODO:change buffer size to satisfied  the CPU cache line;
  typedef detail::Buffer<64 * 1024> BufferType;
  typedef boost::ptr_vector<BufferType> BufferVector;
  typedef BufferVector::auto_type VecTypePtr;
  void threadFunc();

  const int kCondWaitInterval;
  VecTypePtr _current;
  VecTypePtr _next;
  BufferVector _bufferVector;
  Thread _thread;
  string& _basename;
  bool _logging;

  MutexLock _lock;
  Condition _cond;
  CountDownLatch latch_;

 public:
  LogBuffer(std::string& basename);
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

//}
};
}
#endif
