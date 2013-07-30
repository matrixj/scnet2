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

  private:
   const int RDEVT;
   const int WRTEVT;

   void updatePoller();

   Callback _readCb;
   Callback _writeCb;
   Callback _errorCb;

   BaseLoop *_loop;
   boost::weak_ptr<void> _tie;
   int _fd;
   int _events;
   int _revents;
   bool _eventHandling;
   bool _tied;
};

}
}
#endif
