#include <net/socket_helpers.h>

#include <string>

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include <net/sockaddr.h>

using namespace scnet2;
using namespace scnet2::net;
//using namespace scnet2::net::detail;

namespace {

struct sockaddr* toSockaddr(struct sockaddr_in *sock) {
  return reinterpret_cast<sockaddr*>(sock);
}

}

void detail::socketCall(const char* callName, int result) {
  if (result != 0) {
    perror(callName);
    abort();
  }
}

int detail::createSocketAndSetNonblock() {
  int fd = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK | SOCK_CLOEXEC, IPPROTO_TCP);
  if (fd < 0) {
    perror("socket");
    abort();
  }
  return fd;
}

void detail::close(int fd) {
  close(fd);
}

void detail::bind(SockAddr&  host, int fd) {
  socketCall("bind", ::bind(fd, host.getSockaddr(),
                            static_cast<socklen_t>(sizeof host)));
}

void detail::listen(int fd) {
  socketCall("listen", ::listen(fd, SOMAXCONN));
}

int detail::accept(int fd, SockAddr& peer) {
  int err = -1;
  //struct sockaddr_in *peerAddr = peer.sockaddr_in();
  socklen_t len = static_cast<socklen_t>(sizeof peer);

  int acceptFd = ::accept4(fd, peer.getSockaddr(), &len, SOCK_NONBLOCK | SOCK_CLOEXEC);

  if (fd < 0) {
    err = errno;
    (void) err;
    //TODO:Log the reason of fail
  }
  return acceptFd;
}
