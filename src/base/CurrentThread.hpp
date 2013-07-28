#ifndef _SCNET2_BASE_CURRENTTHREAD_H
#define _SCNET2_BASE_CURRENTTHREAD_H

namespace scnet2
{
namespace CurrentThread
{
    extern __thread int t_cachedTid;
    extern __thread char t_tidString[32];
    extern __thread const char* t_threadName;

    void cacheTid();

    inline int tid()
    {
        if (t_cachedTid == 0) 
            cacheTid();
        return t_cachedTid;
    }

    bool isMainThread();
}
}


#endif
