#ifndef SRC_NET_EPOLLER_H_
#define SRC_NET_EPOLLER_H_

#include <poll.h>
#include <sys/epoll.h>

#include <vector>
#include <map>

#include <net/poller.h>
#include <base/timestamp.h>

namespace scnet2 {

class BaseLoop;
class Channel;

namespace net {

class Epoller : public Poller {
 public:
  explicit Epoller(BaseLoop *loop);
  virtual ~Epoller();

  virtual Timestamp wait(int timeout, std::vector<Channel*> *channels);
  virtual void updateChannel(Channel *c);

 private:
  // Size is ignored nowaday in epoll_create(1)
  const static int SIZE = 11;
  BaseLoop *_loop;
  int _epollfd;
  // int _timeout;

  std::vector<struct epoll_event> _events;
  typedef std::map<int, Channel*> ChannelMap;

  ChannelMap _channels;

  void padChannels(int number, std::vector<Channel*> *channel);
  void update(int operation, Channel *c);
};

}  // namespace net
}  // namespace scnet2

#endif  // SRC_NET_EPOLLER_H_
