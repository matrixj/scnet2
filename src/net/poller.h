#ifndef SCNET2_BASE_POLLER_H
#define SCNET2_BASE_POLLER_H

#include <vector>

#include <boost/noncopyable.hpp>

#include <net/poller.h>
#include <base/timestamp.h>

namespace scnet2 {

//namespace base {
class BaseLoop;
class Channel;
//}

namespace net {

class Poller : boost::noncopyable {
 public:
  Poller(BaseLoop *loop);
  ~Poller();

  static Poller* getEpoll(BaseLoop* loop);

  virtual Timestamp wait(const int timeout, std::vector<Channel*> *chanels) = 0;
  virtual void updateChannel(Channel *channel) = 0;
 private:
  BaseLoop *_loop;
};

} //end of scnet namespace
} //end of net namespace


#endif
