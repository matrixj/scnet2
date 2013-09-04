#ifndef SRC_NET_SERVER_H_
#define SRC_NET_SERVER_H_

#include <net/listenner.h>
#include <base/typedef_callback.h>

#include <boost/noncopyable.hpp>
#include <map>

namespace scnet2 {

class BaseLoop;

namespace net {
class SockAddr;
class Server : boost::noncopyable {
 public:
  Server(BaseLoop& loop, SockAddr& sockaddr);
  ~Server() {}

  void start();
  void newConnCallback(int fd, SockAddr& peer);

  void setConnCallback(const ConnCallback& cb) {
    connCallback_ = cb;
  }
  void setCompleteReadCallback(const CompleteReadCallback& cb) {
    completeReadCallback_ = cb;
  }
  void setCompleteWrieCallback(const CompleteWriteCallback& cb) {
    completeWriteCallback_ = cb;
  }
  void connCloseCallback(const ConnectionPtr& cb);
 private:
  ConnCallback connCallback_;
  CompleteReadCallback completeReadCallback_;
  CompleteWriteCallback completeWriteCallback_;
  
  BaseLoop& loop_;
  SockAddr& sockaddr_;
  Listenner listenner_;
  std::map<std::string, ConnectionPtr> conns_;
  bool started_;
  long long int connId_;
};
} // namespace net
} // namespace scnet2
#endif // SRC_NET_SERVER_H_
