#include <errno.h>

#include <net/connection.h>
#include <base/baseloop.h>
#include <net/sockbuffer.h>

#include <boost/bind.hpp>
#include <string>
using namespace scnet2;
using namespace scnet2::net;

Connection::Connection(BaseLoop *loop, std::string& namestr, int fd, SockAddr& peer)
  : loop_(loop),
    state_(kDisconnected),
    name_(namestr),
    addr_(peer),
    fd_(fd),
    socket_(fd_),
    channel_(loop, fd) {
  channel_.setReadCb(boost::bind(&Connection::readCallback, this));
  channel_.setWriteCb(boost::bind(&Connection::writeCallback, this));
//  channel_.setErrorCb(boost::bind(&Connection::errorCallback, this));
  // CloseCb in channel is no working now
  channel_.setCloseCb(boost::bind(&Connection::closeCallback, this));
  socket_.setKeepalive();
}

void Connection::send(const void *data, size_t len) {
  if (state_ == kConnected) {
    if (loop_->isInLoopThread()) {
      string msg(static_cast<const char*>(data), len);
      sendInLoop(msg);
    } else {
      string msg(static_cast<const char*>(data), len);

      // FIXME :Have to copy the whole msg 
      // Is nice to use std::forward if possible
      loop_->delegate(boost::bind(&Connection::sendInLoop, this,
                                         msg));           }
  }
}
void Connection::send(SockBuffer *buf) {
  if (state_ == kConnected) {
    if (loop_->isInLoopThread()) {
      string msg(buf->beginPtr(), buf->len());
      sendInLoop(msg);
      buf->reset();

      /*
      while(buf->dataLen() > 0) {
        size_t n = sendInLoopThread(buf);
        buf->addBegin(n);
        if (n < buf->dataLen()) {
          buf->dataLen -= n;
          assert(buf->dataLen() >= 0);
        }
      }
      */
    } else {
      string msg(buf->beginPtr(), buf->len());
      loop_->delegate(boost::bind(&Connection::sendInLoop, this,
                                         msg));
    }
  }
}

// It is call in io thread, no need to make it thread safe
void Connection::sendInLoop(const std::string msg) {
  if (state_ != kDisconnected) {
    return;
  }
  ssize_t n = 0;
  size_t remainSize = msg.size();
  bool error = false; 
  
  // To send data directory
  if (!channel_.isWritting() && buffToSend_.len() == 0) {
    n = ::write(fd_, msg.data(), msg.size());
    if (n > 0) {
      remainSize -= n;
      if (remainSize == 0 && completeWriteCallback_) {
        loop_->pushQueueInLoop(boost::bind(&Connection::completeWriteCallback_,
                                           shared_from_this()));
      }
    } else {
      if (errno != EWOULDBLOCK) {
        // TODO(matrixj) : Do something to handle error
        error = true;
      }
    }
  }
  if(!error && remainSize > 0) {
   // size_t size = buffToSend_.len();
    buffToSend_.append(msg.data() + n, remainSize);
    if (!channel_.isWritting()) {
      channel_.enableWrite();
    }
  }
}

void Connection::established() {
  assert(loop_->isInLoopThread());
  setState(kConnected);
  channel_.enableRead();
  
  if (connCallback_)
    connCallback_(shared_from_this());
}
// Read data from system socket buffer to build-in buffer 
// When socket is able to read
void Connection::readCallback() {
  if (state_ != kConnected) {
    return;
  }
  int error;
  ssize_t len = buffToSend_.readSockFd(fd_, &error);
  if (len > 0 && completeReadCallback_) {
    completeReadCallback_(shared_from_this(), &buffToSend_);
  } else if (len == 0) {
    closeCallback();
  } else {
    // Do something to handle error
  }
}

void Connection::writeCallback() {
  ssize_t len = 0;
  bool error = false;

  if (channel_.isWritting() && buffToSend_.len() > 0) {
    len = ::write(fd_, buffToSend_.beginPtr(), buffToSend_.len());
    if (len > 0) {
      buffToSend_.retrieve(len);
      if (buffToSend_.len() == 0) {
        channel_.disableWrite();
        if (completeWriteCallback_) {
          loop_->pushQueueInLoop(boost::bind(completeWriteCallback_,
                                            shared_from_this()));
        }
        // This state setted in @shutDownInLoop
        if (state_ == kDisconnecting) {
          shutDownInLoop();
        }
      }
    }

  } else {
    (void) error;
    // TODO(matrixj): To Log message here
  }
}

void Connection::closeCallback() {
  channel_.setNoneCb();
  setState(kDisconnected);

  if (connCallback_)
    connCallback_(shared_from_this());
}
// Not thread safe
void Connection::shutDown() {
  if (state_ == kConnected) {
    setState(kDisconnected);
    loop_->pushQueueInLoop(boost::bind(&Connection::shutDownInLoop,
                                       shared_from_this()));
  }
}

void Connection::shutDownInLoop() {
  if (!channel_.isWritting()) {
    socket_.shutDownWrite();
  }
}
