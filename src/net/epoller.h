#ifndef SCNET2_NET_EPOLLER_H
#define SCNET2_NET_EPOLLER_H

#include <vector>
#include <map>

#include <poll.h>
#include <sys/epoll.h>

#include <net/poller.h>
#include <base/Timestamp.h>

namespace scnet2 {

namespace base{
class BaseLoop;
class Channel;
}

namespace net {

class Epoller : public Poller {
 public:
  Epoller(base::BaseLoop *loop);
  virtual ~Epoller();

  virtual Timestamp wait(int timeout, std::vector<base::Channel*> *channels);
  virtual void updateChannel(base::Channel *c);

 private:
  //size is ignored nowaday in epoll_create(1)
  const static int SIZE = 11;
  base::BaseLoop *_loop;
  int _epollfd;
  //int _timeout;

  std::vector<struct epoll_event> _events;
  typedef std::map<int, base::Channel*> ChannelMap;

  ChannelMap _channels;

  void padChannels(int number, std::vector<base::Channel*> *channel);
  void update(int operation, base::Channel *c);

};


}
}

#endif
