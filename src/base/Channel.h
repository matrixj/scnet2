#ifndef SCNET2_BASE_CHANNEL_H
#define SCNET2_BASE_CHANNEL_H

#include <boost/noncopyable.hpp>
#include <boost/function.hpp>
#include <boost/weak_ptr.hpp>

namespace scnet2 {
namespace base {

class BaseLoop;

class Channel : boost::noncopyable {
 public:
  typedef boost::function<void ()> Callback;
  Channel(BaseLoop *loop, int fd);
  ~Channel();

  void tie(boost::weak_ptr<void>&);

  void setReadCb(const Callback& cb) {
    _readCb = cb;
  }
  void setWriteCb(const Callback& cb) {
    _writeCb = cb;
  }
  void setErrorCb(const Callback& cb) {
    _errorCb = cb;
  }

  void setNoneCb() {
    _noneCb = true;
    updatePoller();
  }

  bool isNonCb() {
    return _noneCb;
  }

  void setFd(int tmp_fd) {
    _fd = tmp_fd;
  }

  int fd() {
    return _fd;
  }

  void enableWrite() {
    _events |= RDEVT;
    updatePoller();
  }
  void disableWrite() {
    _events &= ~WRTEVT;
    updatePoller();
  }
  void enableRead() {
    _events |= WRTEVT;
    updatePoller();
  }
  void disableRead() {
    _events &= ~RDEVT;
    updatePoller();
  }

  int events() {
    return _events;
  }

  void setRevents(int revents) {
    _revents = revents;
  }

  void setIndex(int idx) {
    _idx = idx;
  }

  int index() {
    return _idx;
  }

  
  void handleEvent();

  private:
   static const int RDEVT;
   static const int WRTEVT;

   void updatePoller();

   Callback _readCb;
   Callback _writeCb;
   Callback _errorCb;

   BaseLoop *_loop;
   boost::weak_ptr<void> _tie;
   int _fd;
   int  _events;
   int _revents;
   bool _eventHandling;
   bool _tied;

   int _idx;
   bool _noneCb;
};

}
}
#endif
