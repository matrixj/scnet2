#include <base/Thread.h>
#include <base/BaseLoop.h>

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
    Thread thread(func);
    thread.start();

    loop.loop();
}
