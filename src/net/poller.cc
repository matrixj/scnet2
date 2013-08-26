#include <net/poller.h>

#include <net/epoller.h>
#include <base/baseloop.h>

using scnet2::BaseLoop;
using scnet2::net::Poller;

Poller::Poller(BaseLoop *loop)
  : _loop(loop) { }

Poller::~Poller() { }

Poller* Poller::getEpoll(BaseLoop* loop) {
  return new Epoller(loop);
}


