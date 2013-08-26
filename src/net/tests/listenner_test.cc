#include <base/baseloop.h>
#include <net/listenner.h>
#include <net/sockaddr.h>

#include <string>
#include <iostream>

using namespace std;
using namespace scnet2;
using namespace scnet2::net;

int main() {
  BaseLoop loop;
  SockAddr sockaddr(8080);
  Listenner listenner(loop, sockaddr);

//  listenner.listen();

  loop.loop();
}
