#include <base/thread.h>

#include <boost/static_assert.hpp>
#include <boost/weak_ptr.hpp>

#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <linux/unistd.h>

#include <base/CurrentThread.h>

namespace scnet2
{
namespace CurrentThread
{
    __thread int t_cachedTid = 0;
    __thread char t_tidString[32];
    __thread const char* t_threadName = "unknown";
    const bool sameType = boost::is_same<int, pid_t>::value;
    BOOST_STATIC_ASSERT(sameType);
}
namespace detail
{
pid_t gettid()
{
    return static_cast<pid_t>(::syscall(SYS_gettid));
}

struct ThreadData
{
    typedef scnet2::Thread::ThreadFunction Func;
    Func _func;
    string _name;
    boost::weak_ptr<pid_t> _wptrPid;

    ThreadData(const Func& func,
              const string& name,
               const boost::shared_ptr<pid_t>& tid)
    : _func(func),
      _name(name),
      _wptrPid(tid)
    { }
    void run()
    {
        pid_t tid = scnet2::CurrentThread::tid();
        boost::shared_ptr<pid_t> ptid = _wptrPid.lock();
        if (ptid) {
            *ptid = tid;
            ptid.reset();
        }

        scnet2::CurrentThread::t_threadName = _name.c_str();
        try
        {
            _func();
            scnet2::CurrentThread::t_threadName = "finished";
        }
       /* catch (const Exception& ex)
        {
            scnet2::CurrentThread::t_threadName = "dump";
            fprintf(stderr, "exception caught in Thread %s\n", _name.c_str());
            fprintf(stderr, "reason: %s\n", ex.what());
            abort();
        }
        */
        catch (const std::exception& ex)
        {
            scnet2::CurrentThread::t_threadName = "dump";
            fprintf(stderr, "exception caught in Thread %s\n", _name.c_str());
            fprintf(stderr, "reason: %s\n", ex.what());
            abort();
        }
        catch (...)
        {
            scnet2::CurrentThread::t_threadName = "dump";
            fprintf(stderr, "exception caught in Thread %s\n", _name.c_str());
            fprintf(stderr, "reason: %s\n", "unknown");
            throw;
        }
    }
};

void* startThread(void* obj)
{
    ThreadData* data = static_cast<ThreadData*>(obj);
    data->run();
    delete data;
    return NULL;
}

}
}

using namespace scnet2;

void CurrentThread::cacheTid()
{
    if (t_cachedTid == 0) {
        t_cachedTid = detail::gettid();
        int n = snprintf(t_tidString, sizeof t_tidString, "%5d", t_cachedTid);
        (void) n;
    }
}

bool CurrentThread::isMainThread()
{
    return tid() == ::getpid();
}

Thread::Thread(const ThreadFunction& func, const string& name)
: _started(false),
  _joined(false),
  _tid(new pid_t(0)),
  _func(func),
  _name(name) { }

Thread::~Thread() {
    if (_started && !_joined) {
        pthread_detach(_pid);
    }
}

void Thread::start()
{
    assert(!_started);
    _started = true;
    detail::ThreadData *data = new detail::ThreadData(_func, _name, _tid);
    if (pthread_create(&_pid, NULL, &detail::startThread, data)) { 
      _started = false; 
      perror("pthread_create");
    }

}

int Thread::join()
{
    assert(_started);
    assert(!_joined);
    _joined = true;
    return pthread_join(_pid, NULL);
}
