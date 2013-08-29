#include <net/connection.h>

#include <string>
using namespace scnet2;
using namespace scnet2::net;

Connction::Connection(BaseLoop *loop, std::string& name, int fd, SockAddr& peer)
  : loop_(loop),
    name_(name),
    addr_(peer),
    fd_(fd),
    socket_(fd_),
    channel_(new Channel(loop, fd)) {
  channel_.setReadCb(boost::bind(&Connection::readCallback, this));
  channel_.setWriteCb(boost::bind(&Connection::writeCallback, this));
  channel_.setErrorCb(boost::bind(&Connection::errorCallback, this));
  channel_.setCloseCb(boost::bind(&Connection::closeCallback, this));
  socket_.setKeepalive();
}

void Connection::send(const void *data, size_t len) {
  if (state_ == kConnected) {
    if (loop->isInLoopThread()) {
      sendInLoopThread(static_cast<char*>(data), len);
    } else {
      string msg(static_cast<char*>data, len);

      // FIXME :Have to copy the whole msg 
      // Is nice to use std::forward if possible
      loop_->runInLoopThread(boost::bind(&Connection::sendInLoopThread, this,
                                         msg));           }
  }
}
void Connection::send(Buffer *buf) {
  if (state_ == kConnected) {
    if (loop->isInLoopThread()) {
      runInLoopThread(buf->begin(), buf->len());
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
      loop_->runInLoopThread(boost::bind(&Connection::sendInLoopThread, this,
                                         buf.toString()));
    }
  }
}

// It is call in io thread, no need to make it thread safe
void Connection::sendInLoopThread(std::string msg) {
  if (state_ != kDisconnected) {
    return;
  }
  ssize_t n = 0;
  size_t remainSize = msg.size();
  bool error = false; 
  
  // To send data directory
  if (!channel_.isWritting() && buffToSend_.dataLen() == 0) {
   n = detail::send(fd_, msg.data(), msg.size());
    if (n > 0) {
      remainSize -= n;
      if (remainSize == 0 && completeWriteCallback) {
        loop_->pushQueueInLoop(boost::bind(&Connection::completeWriteCallback,
                                           shared_from_this()));
      }
    } else {
      if (errno != EWOULDBLOCK) {
        // TODO(matrixj) : Do something to handle error
        error = ture
      }
    }
  }
  if(!error && remainSize > 0) {
    size_t size = buffToSend_.dataLen();
    buffToSend_.append(msg.data() + n, remainSize);
    if (!channel_.isWritting()) {
      channel_.enableWrite();
    }
  }
}

void Connection::established() {
  assert(loop->isInLoopThread());
  setState(kConnectted);
  channel_.enableRead();
  
  establishedCallback(shared_from_this());
}
// Read data from system socket buffer to build-in buffer 
// When socket is able to read
void Connection::readCallback() {
  if (state_ != kConnected) {
    return;
  }
  int error;
  ssize_t len = buffToSend_.readSockFd(*error);
  if (len > 0) {
    userReadCallback_(shared_from_this(), &buffToSend_);
  } else if (n == 0) {
    closeCallback();
  } else {
    // Do something to handle error
  }
}

void Connection::writeCallback() {
  ssize_t len = 0;
  bool error = false;

  if (channel_->isWritting() && buffToSend_.dataLen() > 0) {
    len = detail::write(fd_, buffToSend_.data(), buffToSend_.dataLen());
    if (len > 0) {
      buffToSend_.moveBegin(len);
      if (buffToSend_.dataLen() == 0) {
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
    // TODO(matrixj): To Log message here
  }
}

void Connction::closeCallback() {
  channel_.setNoneCb();
  setState(kDisconnected);

  userCloseCallback_(shared_from_this());
}
// Not thread safe
void Connction::shutDown() {
  if (state_ == kConnected) {
    setState(kDisconnected);
    loop_->pushQueueInLoop(boost::bind(&Connction::shutDownInLoop,
                                       shared_from_this()));
  }
}

void Connction::shutDownInLoop() {
  if (!channel_.isWritting()) {
    socket_.shutDownWrite();
  }
}
