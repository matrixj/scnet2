#include <base/baseloop.h>
#include <base/channel.h>

#include <assert.h>
#include <poll.h>

using scnet2::BaseLoop;
using scnet2::Channel;

const int Channel::RDEVT = POLLIN | POLLPRI;
const int Channel::WRTEVT = POLLOUT;

Channel::Channel(BaseLoop *loop, int filedes)
  : _loop(loop),
    _fd(filedes),
    _events(0),
    _revents(0),
    _eventHandling(false),
    _tied(false),
    writing_(false),
    reading_(false),
    index_(-1) { }
    
Channel::~Channel() {
  assert(!_eventHandling);
}
void Channel::updatePoller() {
  _loop->updateChannel(this);
}
void Channel::tie(boost::weak_ptr<void>& obj) {
  _tie = obj;
  _tied = true;
}
void Channel::handleEvent() {
 if ( _revents & RDEVT) {
   assert(_readCb);
   reading_ = true;
   _readCb();
   readding_ = false;
 }
 if (_revents & WRTEVT) {
   assert(_writeCb);
   writing_ = true;
   _writeCb();
   wirtting_ = false;
 }
 //TODO::more events handler
}
