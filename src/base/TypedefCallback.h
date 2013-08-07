#ifndef SCNET_BASE_TYPEDEFCALLBACK_H
#define SCNET_BASE_TYPEDEFCALLBACK_H
#include <boost/function.hpp>
namespace scnet2 {
typedef boost::function<void()> Timercb;
typedef boost::function<void()> Queuecb;
}

#endif
