#include <net/epoller.h>

#include <stdio.h>
#include <poll.h>
#include <sys/epoll.h>

#include <vector>

#include <base/channel.h>
#include <base/types.h>

using scnet2::Channel;
using scnet2::Timestamp;
using scnet2::net::Epoller;

namespace {
const int NEW = -1;
const int DELED = 1;
const int ADDED = 2;

}

Epoller::Epoller(BaseLoop *loop)
  : Poller(loop),
    _loop(loop),
    _epollfd(::epoll_create1(EPOLL_CLOEXEC)),
    _events(64) {
  if (_epollfd < 0) {
    perror("epoll_create");
  }
}
Epoller::~Epoller() { ::close(_epollfd); }

Timestamp Epoller::wait(int timeout, std::vector<Channel*> *channels) {
  int n = ::epoll_wait(_epollfd, &(*_events.begin()),
            static_cast<int>(_events.size()), timeout);
  if (n > 0) {
    padChannels(n, channels);
    if (implicit_cast<size_t>(n) == _events.size()) {
      _events.resize(n * 2);
    }
  } else if (n < 0) {
    perror("epoll_wait");
  }
  return Timestamp::now();
}

void Epoller::padChannels(int number, std::vector<Channel*> *channels) {
  int i = 0;
  for (; i < number; ++i) {
    assert(_events[i].data.ptr != NULL);
    Channel *c = static_cast<Channel*>(_events[i].data.ptr);
    int fd = c->fd();
    assert(_channels.find(fd) != _channels.end());
    assert(_channels[fd] == c);
    c->set_revents(_events[i].events);
    channels->push_back(c);
  }
}

void Epoller::updateChannel(Channel *c) {
  int idx = c->index();
  int fd = c->fd();
  if (idx == NEW || idx == DELED) {
    if (idx == NEW) {
      _channels[fd] = c;
    } else {
      assert(_channels.find(fd) != _channels.end());
      assert(_channels[fd] == c);
    }
    c->set_index(ADDED);
    update(EPOLL_CTL_ADD, c);
  } else {
    // Modified exist fd
    if (c->isNonCb()) {
      update(EPOLL_CTL_DEL, c);
    } else {
      update(EPOLL_CTL_MOD, c);
    }
  }
}

void Epoller::update(int operation, Channel *c) {
  struct epoll_event event;
  bzero(&event, sizeof event);
  event.events = c->events();
  event.data.ptr = c;
  if (::epoll_ctl(_epollfd, operation, c->fd(), &event) != 0) {
    perror("epoll_ctl");
  }
}
