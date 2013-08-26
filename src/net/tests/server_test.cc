#include <net/sockaddr.h>
#include <net/server.h>
#include <base/baseloop.h>

using namespace scnet2;
using namespace scnet2::net;
int main() {
  BaseLoop loop;
  SockAddr sockaddr(8080);
  Server server(loop, sockaddr);
  server.start();
  loop.loop();
}
