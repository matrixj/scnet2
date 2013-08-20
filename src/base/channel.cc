#include <base/baseloop.h>
#include <base/channel.h>

#include <assert.h>
#include <poll.h>

using namespace scnet2;
//using namespace scnet2::base;

const int Channel::RDEVT = POLLIN | POLLPRI;
const int Channel::WRTEVT = POLLOUT;

Channel::Channel(BaseLoop *loop, int filedes)
  : _loop(loop),
    _fd(filedes),
    _events(0),
    _revents(0),
    _eventHandling(false),
    _tied(false),
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
   _readCb();
 }
 if (_revents & WRTEVT) {
   assert(_writeCb);
   _writeCb();
 }
 //TODO::more events handler
}
