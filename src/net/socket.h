#ifndef SCNET2_NET_SOCKET_H
#define SCNET2_NET_SOCKET_H

#include <boost/noncopyable.hpp>

namespace scnet2 {
namespace net {
class SockAddr;
class Socket : boost::noncopyable {
 public:
  // All of this function don't need to deal with error
  // it will abort inside the call of @detail if there is any unexpected result
  explicit Socket(int fd) : fd_(fd) {}
  ~Socket();
  void close(int fd);
  void bind(SockAddr& host);
  void listen();
  int accept(SockAddr& peer);
  void setNoDelay();
  void setNoPush();
  void setReuseAddr();
  void setReusePort();
  void setKeepalive();
  void shutDownWrite();
 private:
  const int fd_;
};
}// End of namespace net
}// End of namespace scnet2
#endif
