#include <base/BaseLoop.h>
#include <basy/typedefCallbac.h>

void timercb() {
  printf("Time up\n\n");
}

int main() {
  BaseLoop loop;
  loop.runAt(boost::bind(timercb))
}
