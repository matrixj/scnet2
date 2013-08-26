#ifndef SRC_NET_SERVER_H_
#define SRC_NET_SERVER_H_

#include <net/listenner.h>
#include <boost/noncopyable.hpp>

namespace scnet2 {

class BaseLoop;

namespace net {
class SockAddr;
class Server : boost::noncopyable {
 public:
  Server(BaseLoop& loop, SockAddr& sockaddr);
  void start();
  void newConnCallback(int fd, SockAddr& peer);
 private:
  BaseLoop& loop_;
  SockAddr& sockaddr_;
  Listenner listenner_;
  bool started_;
};
} // namespace net
} // namespace scnet2
#endif // SRC_NET_SERVER_H_
