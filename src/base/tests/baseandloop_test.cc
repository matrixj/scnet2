#include <base/thread.h>
#include <base/baseloop.h>

using namespace scnet2;
using namespace scnet2::base;

void func()
{
    BaseLoop loop;
    loop.loop();
}

int main()
{
    BaseLoop loop;
 //   Thread thread(func, "Another_thread");
//    thread.start();

    loop.loop();
}
