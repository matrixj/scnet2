#include <net/sockbuffer.h>
#include <sys/uio.h>
#include <errno.h>

using scnet2::net::SockBuffer;

SockBuffer::SockBuffer()
  : len_(0),
    begin_(0),
    end_(0) {}

ssize_t SockBuffer::readSockFd(int fd, int *error) {
  char buf[65535];
  struct iovec vec[2];
  size_t avalibleLen = buf_.size() - end_;

  vec[0].iov_base = writablePtr();
  vec[0].iov_len = avalibleLen;
  vec[1].iov_base = buf;
  vec[1].iov_len = 65535;

  ssize_t l = ::readv(fd, vec, 2);
  if (l < 0) 
    *error = errno;
  if (static_cast<size_t>(l) <= avalibleLen) {
    end_ += l;
    len_ += l;
  } else {
    //end_ += l;
    append(buf, l - avalibleLen);
  }

  return l;
}
