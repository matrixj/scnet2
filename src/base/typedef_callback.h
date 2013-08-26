#ifndef SCNET_BASE_TYPEDEFCALLBACK_H
#define SCNET_BASE_TYPEDEFCALLBACK_H
#include <boost/function.hpp>
namespace scnet2 {
namespace net{
class SockAddr;
}
typedef boost::function<void()> Timercb;
typedef boost::function<void()> Queuecb;
typedef boost::function<void(int fd, net::SockAddr& sockaddr)> ConnCallback;
}

#endif
