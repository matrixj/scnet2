#include <base/baseloop.h>
#include <net/sockaddr.h>
#include <net/server.h>

#include <boost/bind.hpp>
#include <iostream>

using namespace scnet2;
using namespace scnet2::net;

Server::Server(BaseLoop& loop, SockAddr& sockaddr) 
  : loop_(loop),
    sockaddr_(sockaddr),
    listenner_(loop_, sockaddr_),
    started_(false) {

  listenner_.setConnCallback(boost::bind(&Server::newConnCallback, this, _1, _2));
}

void Server::start() {
  assert(!started_);
  started_ = true;
  loop_.runInLoop(boost::bind(&Listenner::listen, &listenner_));
}

void Server::newConnCallback(int fd, SockAddr& peer) {

}

