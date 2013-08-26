#include <net/sockaddr.h>

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <string.h>

#include <boost/static_assert.hpp>
#include <string>

#pragma GCC diagnostic ignored "-Wold-style-cast"
const static in_addr_t kINADDR_ANY = INADDR_ANY;
#pragma GCC diagnostic error "-Wold-style-cast"

using scnet2::net::SockAddr;

BOOST_STATIC_ASSERT(sizeof(struct sockaddr_in) == sizeof(SockAddr));
// For bind(2)
SockAddr::SockAddr() {
  sockaddr_in_.sin_family = AF_INET;
  sockaddr_in_.sin_addr.s_addr = htobe32(kINADDR_ANY);
  sockaddr_in_.sin_port = htons(0);
}
// For server to listen(2)
SockAddr::SockAddr(const uint16_t port) {
  sockaddr_in_.sin_family = AF_INET;
  sockaddr_in_.sin_addr.s_addr = htobe32(kINADDR_ANY);
  sockaddr_in_.sin_port = htons(port);
}
// For client to connect(2)
SockAddr::SockAddr(const std::string& ip, const uint16_t port) {
  sockaddr_in_.sin_family = AF_INET;
  sockaddr_in_.sin_port = htons(port);
  sockaddr_in_.sin_addr.s_addr = inet_addr(ip.c_str());
  bzero(sockaddr_in_.sin_zero, 8);
}
/*
SockAddr::SockAddr(const std::string& ipAndPort) {
  sockaddr_in_.sin_family = AF_INET;
  int pos = static_cast<int>(ipAndPort.find(':', 0));
  sockaddr_in_.sin_addr.s_addr = inet_addr(ipAndPort.substr(pos).c_str());
  sockaddr_in_.sin_port = htons(ipAndPort.substr(pos, ipAndPort.length() - pos).c_str());
  bzero(sockaddr_in_.sin_zero, 8);
}
*/
