#ifndef SCNET2_BASE_POLLER_H
#define SCNET2_BASE_POLLER_H

#include <vector>

#include <boost/noncopyable.hpp>

#include <net/poller.h>
#include <base/Timestamp.h>

namespace scnet2 {

namespace base {
class BaseLoop;
class Channel;
}

namespace net {

class Poller : boost::noncopyable {
 public:
  Poller(base::BaseLoop *loop);
  ~Poller();

  static Poller* getEpoll(base::BaseLoop* loop);

  virtual Timestamp wait(const int timeout, std::vector<base::Channel*> *chanels) = 0;
  virtual void updateChannel(base::Channel *channel) = 0;
 private:
  base::BaseLoop *_loop;
};

} //end of scnet namespace
} //end of net namespace


#endif
