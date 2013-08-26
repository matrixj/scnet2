#include <base/baseloop.h>
#include <base/channel.h>
#include <net/listenner.h>
#include <net/socket_helpers.h>
#include <net/socket.h>

#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>

using scnet2::BaseLoop;
using scnet2::net::SockAddr;
using scnet2::net::Listenner;

Listenner::Listenner(BaseLoop& loop, const SockAddr& sockaddr)
  : loop_(loop),
    sockaddr_(sockaddr),
    fd_(detail::createSocketAndSetNonblock()),
    socket_(fd_),
    channel_(&loop_, fd_),
    listenning_(false),
    hasNewConnCallback_(false) {
  socket_.setReuseAddr();
  socket_.setReusePort();
  socket_.bind(sockaddr_);
  channel_.setReadCb(boost::bind(&Listenner::acceptCallback, this));
}

Listenner::~Listenner() {
  ::close(fd_);
}

void Listenner::listen() {
  assert(!listenning_);
  listenning_ = true;
  socket_.listen();
  channel_.enableRead();
}

void Listenner::acceptCallback() {
  assert(loop_.isInLoopThread());
  SockAddr peer;
  int acceptFd = socket_.accept(peer);
  if (acceptFd > 0) {
    if (hasNewConnCallback_)
    connCallback_(acceptFd, peer);
  } else {
    detail::close(acceptFd);
  }
}

//  void Listenner::addToNewConnCallback(int fd) {
//  TODO(matrixj): Add function
//   boost::shared_ptr<Channel> c=new Channel(loop_, fd);
//  c->setReadCb(connCallback_);
//  c->enableRead();
//  }

void Listenner::setConnCallback(const ConnCallback& cb) {
  hasNewConnCallback_ = true;
  connCallback_ = cb;
}
