#ifndef SCNET2_BASE_CHANNEL_H
#define SCNET2_BASE_CHANNEL_H

#include <boost/noncopyable.hpp>
#include <boost/function.hpp>
#include <boost/weak_ptr.hpp>

namespace scnet2 {
//namespace base {

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

  void set_fd(int tmp_fd) {
    _fd = tmp_fd;
  }

  int fd() {
    return _fd;
  }

  void enableWrite() {
    _events |= WRTEVT;
    updatePoller();
  }
  void disableWrite() {
    _events &= ~WRTEVT;
    updatePoller();
  }
  void enableRead() {
    _events |= RDEVT;
    updatePoller();
  }
  void disableRead() {
    _events &= ~RDEVT;
    updatePoller();
  }

  int events() {
    return _events;
  }

  void set_revents(int revents) {
    _revents = revents;
  }

  void set_index(int idx) {
    index_ = idx;
  }

  int index() {
    return index_;
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

   int index_;
   bool _noneCb;
};

//}
}// End of namepace scnet2
#endif
