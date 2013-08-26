#ifndef SRC_NET_SOCKADDR_H_
#define SRC_NET_SOCKADDR_H_

#include <netinet/in.h>
#include <stdint.h>

#include <base/copyable.h>

#include <boost/noncopyable.hpp>
#include <string>

namespace scnet2 {
namespace net {
class SockAddr : scnet2::copyable {
 public:
  SockAddr();
  explicit SockAddr(const uint16_t port);
  SockAddr(const std::string& ip, const uint16_t port);

  struct sockaddr_in& sockaddr_in() {
    return sockaddr_in_;
  }

  struct sockaddr* getSockaddr() {
    return reinterpret_cast<struct sockaddr*>(&sockaddr_in_);
  }

 private:
  struct sockaddr_in sockaddr_in_;
};

}  // namespace net
}  // namespace scnet2
#endif  // SRC_NET_SOCKADDR_H_
