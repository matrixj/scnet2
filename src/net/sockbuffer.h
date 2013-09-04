#ifndef SCNET2_NET_SOCKBUFFER_H_
#define SCNET2_NET_SOCKBUFFER_H_

#include <vector>

#include <assert.h>
#include <stdio.h>

namespace scnet2 {
namespace net {

class SockBuffer {
 public:
  SockBuffer();
  ~SockBuffer() {}
  ssize_t readSockFd(int fd, int *error);
  void reset() {
    //buf_.clear();
    len_ = end_ = begin_ = 0;
  }
  size_t len() {
    assert(len_ == static_cast<size_t>(end_ - begin_));
    return len_;
  }
  
  size_t end() const {
    return end_;
  }
  /*
  string toString() {
    string str(buf_.begin(), buf_.length());
    return str;
  }
  */
  // After write(2) write data in buf_ to OS socket buffer, begin_ have to add len
  void retrieve(size_t l) {
    assert (l <= buf_.size() - end_);
    begin_ += l;
    if (begin_ == end_) {
      reset();
    } else {
      len_ -= l;
    }
  }

  void append(const char *str, size_t l) {
    testAvaliableLenAndAlloc(l);
    assert(buf_.size() - end_ >= l);

    std::copy(str, str + l, writablePtr());
    end_ += l;
    len_ += l;
  }
  size_t begin() const {
    return begin_;
  }
  char *beginPtr() {
    return &*buf_.begin();
  }

 private:
  void testAvaliableLenAndAlloc(size_t l) {
    if (l <= buf_.size() - end_) {
      return; 
    } else {
      buf_.resize(end_ + l);
    }
  }
  const char *beginPtr() const {
    return &*buf_.begin();
  }

  char *writablePtr() {
    return beginPtr() + end_;
  }
  
  const char *writablePtr() const {
    return beginPtr() + end_;
  }
 private:
  std::vector<char> buf_;
  size_t len_;
  size_t begin_, end_;

};
} // namespace net
} // namespace scnet2
#endif // SCNET2_NET_SOCKBUFFER_H_
