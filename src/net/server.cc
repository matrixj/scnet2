#include <base/baseloop.h>
#include <net/sockaddr.h>
#include <net/server.h>
#include <net/connection.h>

#include <boost/bind.hpp>
#include <iostream>

using namespace scnet2;
using namespace scnet2::net;

Server::Server(BaseLoop& loop, SockAddr& sockaddr) 
  : loop_(loop),
    sockaddr_(sockaddr),
    listenner_(loop_, sockaddr_),
    started_(false),
    connId_(0) {

  listenner_.setConnCallback(boost::bind(&Server::newConnCallback, this, _1, _2));
}

void Server::start() {
  assert(!started_);
  started_ = true;
  loop_.delegate(boost::bind(&Listenner::listen, &listenner_));
}

void Server::newConnCallback(int fd, SockAddr& peer) {
  char tmp[16];
  sprintf(tmp, "conn-%lld", connId_); 
  std::string name(tmp);
  boost::shared_ptr<Connection> conn(new Connection(&loop_, name, fd, peer));
  conns_[name] = conn;
  conn->setCloseCallback(boost::bind(&Server::connCloseCallback, this, _1));

  conn->setConnCallback(connCallback_);
  conn->setCompleteReadCallback(completeReadCallback_);
  conn->setCompleteWriteCallback(completeWriteCallback_);

  ++connId_;
  conn->established();
}

void Server::connCloseCallback(const ConnectionPtr& conn) {
  conns_.erase(conn->name());
}

