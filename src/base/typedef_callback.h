#ifndef SCNET_BASE_TYPEDEFCALLBACK_H
#define SCNET_BASE_TYPEDEFCALLBACK_H
#include <net/connection.h>

#include <boost/function.hpp>
namespace scnet2 {
class SockBuffer;
namespace net{
class SockAddr;
class Connection;

typedef boost::shared_ptr<Connection> ConnectionPtr;
typedef boost::function<void(const boost::shared_ptr<Connection>)> ConnCallback;                        
typedef boost::function<void(const boost::shared_ptr<Connection>,                                       
    SockBuffer*)> CompleteReadCallback;                                        
typedef boost::function<void(const boost::shared_ptr<Connection>)> CompleteWriteCallback;               
typedef boost::function<void(const boost::shared_ptr<Connection>)> CloseCallback;
}

typedef boost::function<void()> Timercb;
typedef boost::function<void()> Queuecb;
typedef boost::function<void(int fd, net::SockAddr& sockaddr)> ConnCallback;
}

#endif
