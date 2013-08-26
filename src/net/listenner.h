#ifndef SCNET2_NET_LISTENER_H
#define SCNET2_NET_LISTENER_H

#include <net/sockaddr.h>
#include <net/socket.h>
#include <base/channel.h>

#include <boost/noncopyable.hpp>
namespace scnet2 {

class BaseLoop;

namespace net {

class Listenner : boost::noncopyable {
 public:
  typedef boost::function<void (int fd, SockAddr& peer)> ConnCallback;
  Listenner(BaseLoop& loop, const SockAddr& sockaddr);
  ~Listenner();
  void listen();
  void acceptCallback();
  void setConnCallback(const ConnCallback& cb);
 private:
  void addToNewConnCallback(int fd);

  BaseLoop& loop_;
  SockAddr sockaddr_;
  int fd_;
  Socket socket_;
  //int ops_;
  Channel channel_;
  bool listenning_;
  ConnCallback  connCallback_;
  bool hasNewConnCallback_;
};
}
}
#endif
