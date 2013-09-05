#include <net/socket.h>
#include <net/socket_helpers.h>

#include <stdio.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netinet/tcp.h>

using namespace scnet2;
using namespace scnet2::net;
using namespace scnet2::net::detail;

Socket::~Socket() {
  detail::close(fd_);
}

void Socket::close(int fd) {
  detail::close(fd);
}

void Socket::bind(SockAddr& host) {
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
  detail::socketCall("setNoDelay", setsockopt(fd_, IPPROTO_TCP, TCP_NODELAY,
                 &on, static_cast<socklen_t>(sizeof on)));
}

void Socket::setNoPush() {
  int on = 1;
  detail::socketCall("setNoPush", setsockopt(fd_, SOL_SOCKET, TCP_CORK,
                 &on, static_cast<socklen_t>(sizeof on)));
}

void Socket::setReuseAddr() {
  int on = 1;
  detail::socketCall("setReuseAddr", setsockopt(fd_, SOL_SOCKET, SO_REUSEADDR, &on,
                                              static_cast<socklen_t>(sizeof on)));
}

void Socket::setReusePort() {
  #ifdef SO_REUSEPORT
  int on = 1;
  detail::socketCall("setReusePort", setsockopt(fd_, SOL_SOCKET, SO_REUSEPORT, &on,
                                              static_cast<socklen_t>(sizeof on)));
  #else
//  fprintf(stderr, "No SO_REUSEPORT support\n");
  #endif
}

void Socket::setKeepalive() {
  int on = 1;
  detail::socketCall("setKeepalive", setsockopt(fd_, SOL_SOCKET, SO_KEEPALIVE, &on,
                                              static_cast<socklen_t>(sizeof on)));
}

void Socket::shutDownWrite() {
  socketCall("shutDownWrite", ::shutdown(fd_, SHUT_RD));
}
