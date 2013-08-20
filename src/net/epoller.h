#ifndef SCNET2_NET_EPOLLER_H
#define SCNET2_NET_EPOLLER_H

#include <vector>
#include <map>

#include <poll.h>
#include <sys/epoll.h>

#include <net/poller.h>
#include <base/timestamp.h>

namespace scnet2 {

//namespace base{
//class BaseLoop;
//class Channel;
//}
class BaseLoop;
class Channel;

namespace net {

class Epoller : public Poller {
 public:
  Epoller(BaseLoop *loop);
  virtual ~Epoller();

  virtual Timestamp wait(int timeout, std::vector<Channel*> *channels);
  virtual void updateChannel(Channel *c);

 private:
  //size is ignored nowaday in epoll_create(1)
  const static int SIZE = 11;
  BaseLoop *_loop;
  int _epollfd;
  //int _timeout;

  std::vector<struct epoll_event> _events;
  typedef std::map<int, Channel*> ChannelMap;

  ChannelMap _channels;

  void padChannels(int number, std::vector<Channel*> *channel);
  void update(int operation, Channel *c);

};


}
}

#endif
