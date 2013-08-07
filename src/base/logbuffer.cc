#include <base/logbuffer.h>



using namespace scnet2;

LogBuffer:LogBuffer()
  : _current(new BufferType),
    _next(new BufferType),
    _thread(new Thread(boost::bind(&LogBuffer::ThradFunc, this))) {
      _thread.start();
          }
void LogBuffer:appendToBuffer(const char *str, int len) {
  //TODO:Add mutex lock here;
  //MutextLock guard(_lock);
  if (len < _current->avaliable()) {
    _current->append(str, len)
  } else {
    _bufferVector.push_back(_current.release());
    if (_next) {
      _current = boost::ptr_container::move(_next);
    } else {
      _current.reset(new BufferType);
    }

    _current->append(str, len);
    _cond.notify();
  }
}

void LogBuffer::threadFunc() {
  //_bufferVector::iterator it = _bufferVector.begin();
   VecTypePtr buffer1(new BufferType);
   VecTypePtr buffer2(new BufferType);

   buffer1->bzero();
   buffer2->bzero();
   BufferVector buffersToWriteToFile;
   buffersToWriteToFile.reserve(16);

   while(_logging) {
     {
     //TODO:Add mutex lock here;
       //MutextLock guard(_lock);
     if (_bufferVector.empty()) {
       _cond.waitForTime(kCondWaitInterval);
     }
     _bufferVector.push_back(_current.release());
     _bufferVector.clear();
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
