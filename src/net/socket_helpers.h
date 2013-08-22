#ifndef SCNET2_NET_HELPERS_H
#define SCNET2_NET_HELPERS_H

#include <sys/types.h>
#include <sys/socket.h>

namespace scnet2 {
namespace net {
namespace detail {

void socketCall(const char* callName, int result) {
  if (result != 0) {
    perror(callName);
    abord();
  }
}

void close() {
  socketCall("close", ::close());
}

void bind(const SockAddr& host, int fd) {
  socketCall("bind", ::bind(fd, host.sockaddr(), host.len()));
}

void listen(int fd) {
  socketCall("listen", ::listen(fd, SOMAXCONN));
}

int accept(int fd, const SockAddr& peer) {
  int err = -1;
  struct sockaddr_in *peerAddr = peer.sockaddr_in();
  socketlen_t len = static_cast<socketlen_t>(sizeof peerAddr);

  int acceptFd = ::accept4(fd, toSockaddr(peerAddr), &len, SOCK_NONBLOCK | SOCK_CLOEXEC);

  if (fd < 0) {
    err = errno;
    //TODO:Log the reason of fail
  }
  return acceptFd;
}

}// End of namespace detial
}// End of namespace net
}// End of namespace scnet2
#endif
