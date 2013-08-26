#ifndef SRC_NET_SOCKET_HELPERS_H_
#define SRC_NET_SOCKET_HELPERS_H_

#include <string>

namespace scnet2 {
namespace net {
class SockAddr;
namespace detail {

void socketCall(const char* callName, int result);
int createSocketAndSetNonblock();
void close(int fd);
void bind(SockAddr& host, int fd);
void listen(int fd);
int accept(int fd, SockAddr& peer);

}  // namespace detail
}  // namespace net
}  // namespace　scnet2

#endif  // SRC_NET_SOCKET_HELPERS_H_
