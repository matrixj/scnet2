#ifndef SCNET2_BASE_BUFFER_H
#define SCNET2_BASE_BUFFER_H

#include <stdlib.h>

namespace scnet2 {

namespace detail {

template<int SIZE>
class Buffer : boost::noncopyable {
 public:
  Buffer()
      :_start(_data),
       _begin(_start),
       _end(_data + SIZE) { }

  ~Buffer() { }

  void append(const char *str, int length) {
    memcpy(_begin, str, length);
    _begin += length;
  }

  void bzero() {
    memset(_data, 0, SIZE);
  }

  void reset() {
    _begin= _data;
  }

  size_t avaliable() {
    return _end - _begin;
  }

  char *data() const {
    return _start;
  }
  size_t len() {
     return _begin - _start;
  }

 private:
  char *_start;//start of buffer;
  char *_begin;//pointer to buffer avaliable;
  char *_end;
  char _data[SIZE];
};
}
}

#endif
