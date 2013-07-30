#include <base/Channel.h>

#include <assert.h>

using namespace scnet2;
using namespace scnet2::base;

const int Channel::RDEVT = POLLIN | POLLPRI;
const int Channel::WRTEVT = POLLOUT;

Channel::Channel(BaseLoop *loop, int fd)
  : _loop(loop),
    _fd(fd),
    _tied(false),
    _events(0),
    _revents(0),
    _eventHandling(false) {
    }
Channel::~Channel() {
  assert(!_eventHandling);
}
void Channel::updatePoller() {
  _loop.updateChannel(this);
}
void tie(boost::weak_ptr<void>& obj) {
  _tie = obj;
  _tied = true;
}
