#include <net/socket.h>
#include <net/socket_helpers.h>

using namespace scnet2;
using namespace scnet2::net;

Socket::~Socket() {
  detail::close(fd);
}

void Socket::bind(const SockAddr& host) {
  detail::bind(host, fd_);
}

void Socket::listen() {
  detail::listen(fd_);
}
int Socket::accept(SockAddr& peer) {
  return detail::accept(fd_, peer);
}

void Socket::setNoDelay() {
  int on = 1;
  detail::sockCall("setNoDelay", setsockopt(fd_, IPPROTO_TCP, TCP_NODELAY,
                 &on, static_cast<socklen_t>(sizeof on)));
}

void Socket::setNoPush() {
  int on = 1;
  detail::sockCall("setNoPush", setsockopt(fd_, SOL_SOCKET, TCP_CORK,
                 &on, static_cast<socklen_t>(sizeof on)));
}

void Socket::setReuseAddr() {
  int on = 1;
  detail::sockCall("setReuseAddr", setsockopt(fd_, SOL_SOCKET, SO_REUSEADDR, &on,
                                              static_cast<socklen_t>(sizeof on)));
}

void Socket::setReusePort() {
  #ifdef SO_REUSEPORT
  int on = 1;
  detail::sockCall("setReusePort", setsockopt(fd_, SOL_SOCKET, SO_REUSEPORT, &on,
                                              static_cast<socklen_t>(sizeof on)));
  #else
  fprintf(stderr, "No SO_REUSEPORT support\n");
  #endif
}

void Socket::setKeepalive() {
  int on = 1;
  detail::sockCall("setKeepalive", setsockopt(fd_, SOL_SOCKET, SO_KEEPALIVE, &on,
                                              static_cast<socklen_t>(sizeof on)));
}
