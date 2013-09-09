#include <net/epoller.h>

#include <stdio.h>
#include <poll.h>
#include <sys/epoll.h>

#include <vector>

#include <base/channel.h>
#include <base/types.h>

using scnet2::Event;
using scnet2::Timestamp;
using scnet2::net::Epoller;

namespace {
const int NEW = -1;
const int DELED = 1;
const int ADDED = 2;

}

Epoller::Epoller(BaseLoop *loop)
  : Poller(loop),
    loop_(loop),
    epollfd_(::epoll_create1(EPOLL_CLOEXEC)),
    events_(64) {
  if (epollfd_ < 0) {
    perror("epoll_create");
  }
}
Epoller::~Epoller() { ::close(epollfd_); }

Timestamp Epoller::porcessEvent(int timeout, std::vector<Event*> *events, uint32_t flags) {
  int events;
  int err;
  int i, instance;
  std::vecotr<Event *> postedAcceptQueue, postedQueue, *eventQueue;
  events = ::epoll_wait(epollfd_, &(*events_.begin()),
            static_cast<int>(events_.size()), timeout);
  err = (events == -1) ? errno : 0;
  if (events == 0) {
    // TODO:(matrixj) epoll_wait return 0 event without timeout
  }

  // FIXME: process err
  if (events > 0) {
    for (i = 0; i < events; i++) {
      e = events_[i].data.ptr;
      instance = (uintptr_t) e & 1;
      e = static_cast<Event *>((uintptr_t) c & (uintptr_t) ~1);
    }

    if (e->fd() == -1 || e->rdevent->instance != instance) {
      continue;
    }
    revents = events_[i].events;
    // We want to read or write to event whatever error happened
    if ((revents & (EPOLLERR|EPOLLHUP)) && 
        (revents & (EPOLLIN|EPOLLOUT)) == 0) {
      revents |= EPOLLIN|EPOLLOUT;
    }
    e->set_revents(revents);
    if ((revents & EPOLLIN) && e->rdevent->active()) {
      if (flags && SCNET2_POSTEVENTS) {
        eventQueue = (e->isAcceptEvent() || e->isTimer()) ? &postedAcceptQueue : &postedQueue;
        eventQueue->push_back(e);
      } else {
        e->rdevent->handleEvent();
      }
    }
    if (e->fd() = -1 || e->wrevent->instance() != instance) {
      continue;
    } 
    if ((revents && EPOLLOUT) && e->wrevent->active()) {
      if (flags && SCNET2_POSTEVENTS) {
        postedQueue.push_back(e);
      } else {
        e->wrevent->handleEvent();
      }
  } 
  
  if (implicit_cast<size_t>(events) == events_.size())
      events_.resize(events * 2);

  processEventsAndTimer(postedAcceptQueue, postedQueue);
  return Timestamp::now();
}

void Epoller::processEventsAndTimer(std::vecotr<Event *>& postedAcceptQueue,
                                    std::vector<Event *>& postedQueue) { 
  std::vector<Event *>::iterator it;
  Evnet *tmp;
  for (it = postedAcceptQueue.begin(); it != postedAcceptQueue.end(); ++it) {
    tmp = &(*it);
    tmp->handler();
  }
  for (it = postedQueue.begin(); it != postedQueue.end(); ++it) {
    tmp = &(*it);
    tmp->handler();
    postedQueue.pop_back();
  }
}
void Epoller::updateEvent(Event *e) {
  struct epoll_event ee;
  int op;
  if (e->active()) {
    op = EPOLL_CTL_ADD;
  } else {
    op = EPOLL_CTL_MOD;
  }

  ee.events = e->events();
  ee.data.ptr = (void *)((uintptr_t) e | ev->instance);
  if (::epoll_ctl(epollfd_, op, e->fd(), &ee) == -1) {
    perror("epoll_ctl");
  }
  e->set_active();
  return ;
}

