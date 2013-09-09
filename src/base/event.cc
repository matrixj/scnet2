#include <base/baseloop.h>
#include <base/channel.h>

#include <assert.h>
#include <poll.h>

using scnet2::BaseLoop;
using scnet2::Event;

const int Event::RDEVT = POLLIN | POLLPRI;
const int Event::WRTEVT = POLLOUT;

Event::Event(BaseLoop *loop, int filedes)
  : _loop(loop),
    _fd(filedes),
    _events(0),
    _revents(0),
    _eventHandling(false),
    _tied(false),
    index_(-1) { }
    
Event::~Event() {
  assert(!_eventHandling);
}
void Event::updatePoller() {
  _loop->updateEvent(this);
}
void Event::tie(boost::weak_ptr<void>& obj) {
  _tie = obj;
  _tied = true;
}
void Event::handleEvent() {
  if (active_ == false) {
    return ;
  }
 if ( _revents & RDEVT) {
   assert(_readCb);
   _readCb();
 }
 if (_revents & WRTEVT) {
   assert(_writeCb);
   _writeCb();
 }
 //TODO::more events handler
}
