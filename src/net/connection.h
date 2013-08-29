#ifndef SRC_NET_CONNECTION_H_
#define SRC_NET_CONNECTION_H_

#include <net/sockaddr.h>

#include <boost/scoped_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>

namespace scnet2 {
class BaseLoop;
namespace net {

class Connection : boost::noncopyable,
                   public boost::enable_shared_from_this<Connection> {
 public:
  Connection(BaseLoop *loop, std::string& name, int fd, SockAddr& peer);
  ~Connection();

  ;oid setConnCallback(const ConnCallback& cb) {
    connCallback_ = cb;
  }
  void setcompleteCallback(const CompleteCallback& cb) {
    completeCallback_ = cb;
  }
  void setCloseCallback(const CloseCallback& cb) {
    closeCallback_ = cb;
  }
  void established();
  bool isConnected() {
    return state_ == kConnected;
  }
       
 private:
  void setState(state s) {
    state_ = s;
  }
 
  enum State { kConecting, kConnected, };
  State state_;

  BaseLoop *loop_;
  std::string name_;
  boost::scoped_ptr<struct socket_addr> addr_;
  int fd_;

  ConnCallback connCallback_;
  CompleteCallback completeCallback_;
  CloseCallback closeCallback_;
};
}  // End of namespace net
}  // End of namespace scnet2
#endif  // SRC_NET_CONNECTION_H_
