#ifndef SRC_NET_CONNECTION_H_
#define SRC_NET_CONNECTION_H_

#include <net/sockaddr.h>

#include <boost/scoped_ptr.hpp>
#include <boost/function.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/noncopyable.hpp>

namespace scnet2 {
class BaseLoop;
class Buffer;
namespace net {

class Connection : boost::noncopyable,
                   public boost::enable_shared_from_this<Connection> {
 public:
  typedef boost::function<void(const boost::shared_ptr<Connection>)> ConnCallback;
  typedef boost::function<void(const boost::shared_ptr<Connection>, 
                               Buffer*)> CompleteReadCallback; 
  typedef boost::function<void(const boost::shared_ptr<Connection>)> CompleteWriteCallback;
  typedef boost::function<void(const boost::shared_ptr<Connection>)> CloseCallback;

  Connection(BaseLoop *loop, std::string& name, int fd, SockAddr& peer);
  ~Connection();
  
  void setcompleteWriteCallback(const CompleteWriteCallback& cb) {
    completeWriteCallback_ = cb;
  }
  void setCompleteReadCallback(const CompleteReadCallback& cb) {
    completeReadCallback_ = cb;
  }

  void setConnCallback(const ConnCallback& cb) {
    connCallback_ = cb;
  }
  void setCloseCallback(const CloseCallback& cb) {
    closeCallback_ = cb;
  }
  bool isConnected() {
    return state_ == kConnected;
  }

  void readCallback();
  void writeCallback();
  void closeCallback();
  void shutDown();
  void send(const void *data, size_t len);
  void send(Buffer *buf);

  void established();
       
 private:
  void sendInLoop(const std::string msg); 
  void shutDownInLoop();

  enum State { kConecting, kConnected, kDisconnected, kDisconnecting};
  void setState(State s) {
    state_ = s;
  }
 private:
  BaseLoop *loop_;
  State state_;
  std::string name_;
  boost::scoped_ptr<struct socket_addr> addr_;
  int fd_;

  ConnCallback connCallback_;
  CompleteReadCallback completeReadCallback_;
  CompleteWriteCallback completeWriteCallback_;
  CloseCallback closeCallback_;
};
}  // End of namespace net
}  // End of namespace scnet2
#endif  // SRC_NET_CONNECTION_H_
