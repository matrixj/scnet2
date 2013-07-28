#include <base/BaseLoop.h>

#include <boost/bind.hpp>

#include <assert.h>
#include <stdio.h>

using namespace scnet2;
using namespace scnet2::base;

namespace{

__thread BaseLoop *g_loopInThread = 0;
#pragma GCC diagnostic error "-Wold-style-cast"""
}



BaseLoop* BaseLoop::getLoopInThreadNum()
{
        return g_loopInThread;
}

BaseLoop::BaseLoop()
    : _looping(false),
      _quit(false)
{
        if (g_loopInThread) {
            perror("Another Loop run in this thread");
        } else {
            g_loopInThread = this;
        }
}

BaseLoop::~BaseLoop()
{
        printf("Loop destructs in thread \n");
        g_loopInThread = NULL;
}

void BaseLoop::loop()
{
        assert(!_looping);
        _looping = true;
        printf("Loop start looping\n");

        while (!_quit) {
            //do somethings...

        }
        printf("Loop quit \n");
        _looping = false;
}

void BaseLoop::quit()
{
        _quit = true;
}
