#ifndef SRC_NET_CONNECTION_H_
#define SRC_NET_CONNECTION_H_

#include <net/sockaddr.h>
#include <base/event.h>
#include <net/sockbuffer.h>
#include <net/socket.h>

#include <boost/scoped_ptr.hpp>
#include <boost/function.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/noncopyable.hpp>
#include <boost/any.hpp>

namespace scnet2 {
class BaseLoop;
class Buffer;
namespace net {

class Connection : boost::noncopyable,
                   public boost::enable_shared_from_this<Connection> {
 public:
  typedef boost::function<void(const boost::shared_ptr<Connection>)> ConnCallback;
  typedef boost::function<void(const boost::shared_ptr<Connection>, 
                               SockBuffer*)> CompleteReadCallback; 
  typedef boost::function<void(const boost::shared_ptr<Connection>)> CompleteWriteCallback;
  typedef boost::function<void(const boost::shared_ptr<Connection>)> CloseCallback;

  Connection(BaseLoop *loop, std::string& name, int fd, SockAddr& peer);
  ~Connection() {}
  
  void setCompleteWriteCallback(const CompleteWriteCallback& cb) {
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
  std::string name() const {
    return name_;
  }

  // Local funtions 
  void readCallback();
  void writeCallback();
  void closeCallback();
  void shutDown();
  void send(const void *data, size_t len);
  void send(SockBuffer *buf);

  void established();
  void setctx(boost::any& ctx) {
    any_ = ctx;
  }
  boost::any *getctx() {
    return &any_;
  }
  SockBuffer& getReadBuffer() {
    return buffToRead_;
  }
       
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
  SockAddr addr_;
  int fd_;
  Socket socket_;
  Event event_;
  SockBuffer buffToSend_;
  SockBuffer buffToRead_;
  boost::any any_;

  ConnCallback connCallback_;
  CompleteReadCallback completeReadCallback_;
  CompleteWriteCallback completeWriteCallback_;
  CloseCallback closeCallback_;

  // If the connection is not depand on any other connection;
  bool single_connection_;
  bool timeout_;
  bool error_;
  // If the tcp socket of this connection is destroy
  bool destroyed_;
  bool idle_;
  std::vector<Connection *> reuseConnQueue_;
  bool reusable_;
  bool close_;
};
}  // End of namespace net
}  // End of namespace scnet2
#endif  // SRC_NET_CONNECTION_H_
