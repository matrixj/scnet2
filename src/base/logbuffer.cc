#include <base/logbuffer.h>

#include <boost/bind.hpp>
#include <string>

#include <base/mutexlock.h>
#include <base/condition.h>
#include <base/buffer.h>
#include <base/logger.h>
#include <base/countdown_latch.h>

#ifdef DEBUG
#include <iostream>
#endif

using namespace scnet2;

LogBuffer::LogBuffer(const std::string& basename)
  : kCondWaitTime(3),
    _current(new BufferType),
    _next(new BufferType),
    _thread(boost::bind(&LogBuffer::threadFunc, this), "BGLogThread"),
    _basename(basename),
    _lock(),
    _cond(_lock),
    latch_(1) {
  _current->bzero();
  _next->bzero();
  _bufferVector.reserve(16);
}
void LogBuffer::appendToBuffer(const char *str, int len) {
  {
    MutexLockGuard lock(_lock);
    if (len < static_cast<int>(_current->avaliable())) {
      _current->append(str, len);
    } else {
      _bufferVector.push_back(_current.release());
      if (_next) {
        _current = boost::ptr_container::move(_next);
      } else {
        _current.reset(new BufferType);
      }

      _current->append(str, len);
    }
  }
  _cond.signal();
}

void LogBuffer::threadFunc() {
  assert(_logging);

  bool rc;
  (void) rc;
  latch_.countDown();
  Logger out(_basename);
  VecTypePtr buffer1(new BufferType);
  VecTypePtr buffer2(new BufferType);

  buffer1->bzero();
  buffer2->bzero();
  BufferVector buffersToWriteToFile;
  buffersToWriteToFile.reserve(16);

  while(_logging) {
    {
      assert(buffer1 && buffer1->len() == 0);
      assert(buffer2 && buffer2->len() == 0);

      MutexLockGuard lock(_lock);
      if (_bufferVector.empty()) {
        rc = _cond.timedwait(kCondWaitTime);
      }

      _bufferVector.clear();
      _bufferVector.push_back(_current.release());
      _current = boost::ptr_container::move(buffer1);
      buffersToWriteToFile.swap(_bufferVector);

      if (!_next) {
        _next = boost::ptr_container::move(buffer2);
      }
    }

    for (size_t i = 0; i < buffersToWriteToFile.size(); i++) {
      out.append(buffersToWriteToFile[i].data(), buffersToWriteToFile[i].len());
    }

   // if(!buffer1) {
    assert(!buffer1);
    buffer1 = buffersToWriteToFile.pop_back();
    buffer1->reset();
    //}
    if(!buffer2) {
      buffer2 = buffersToWriteToFile.pop_back();
      buffer2->reset();
    }
    buffersToWriteToFile.clear();
    out.flush();
 }
 out.flush();
}
