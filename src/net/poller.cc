#include <net/poller.h>

#include <net/epoller.h>
#include <base/baseloop.h>

using namespace scnet2;
using namespace scnet2::net;
using namespace scnet2::base;

Poller::Poller(BaseLoop *loop) 
  : _loop(loop) { }

Poller::~Poller() { }

Poller* Poller::getEpoll(BaseLoop* loop) {
  return new Epoller(loop);
}


