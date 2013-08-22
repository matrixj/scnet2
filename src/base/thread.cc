#include <base/thread.h>

#include <boost/static_assert.hpp>
#include <boost/weak_ptr.hpp>

#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <linux/unistd.h>

#include <base/current_thread.h>

namespace scnet2 {
namespace CurrentThread {
    __thread int t_cachedTid = 0;
    __thread char t_tidString[32];
    __thread const char* t_threadName = "unknown";
    const bool sameType = boost::is_same<int, pid_t>::value;
    BOOST_STATIC_ASSERT(sameType);
}
namespace detail {
pid_t gettid() {
    return static_cast<pid_t>(::syscall(SYS_gettid));
}

struct ThreadData {
  typedef scnet2::Thread::ThreadFunction Func;
  Func func_;
  const string& name_;
  boost::weak_ptr<pid_t> wptrPid_;

  ThreadData(const Func& func,
             const string& name,
             const boost::shared_ptr<pid_t>& tid)
    : func_(func),
      name_(name),
      wptrPid_(tid) {}

  void run() {
    pid_t tid = scnet2::CurrentThread::tid();
    boost::shared_ptr<pid_t> ptid = wptrPid_.lock();
    if (ptid) {
      *ptid = tid;
      ptid.reset();
    }
    scnet2::CurrentThread::t_threadName = name_.c_str();
    try {
      func_();
      scnet2::CurrentThread::t_threadName = "finished";
    }
    /*
    catch (const Exception& ex)
    {
        scnet2::CurrentThread::t_threadName = "dump";
        fprintf(stderr, "exception caught in Thread %s\n", _name.c_str());
        fprintf(stderr, "reason: %s\n", ex.what());
        abort();
    }
    */
    catch (const std::exception& ex) {
      scnet2::CurrentThread::t_threadName = "dump";
      fprintf(stderr, "exception caught in Thread %s\n", name_.c_str());
      fprintf(stderr, "reason: %s\n", ex.what());
      abort();
    }
    catch (...) {
      scnet2::CurrentThread::t_threadName = "dump";
      fprintf(stderr, "exception caught in Thread %s\n", name_.c_str());
      fprintf(stderr, "reason: %s\n", "unknown");
      throw;
    }
  }
};

void* startThread(void* obj) {
  ThreadData *data = static_cast<ThreadData*>(obj);
  data->run();
  delete data;
  return NULL;
}

}
}

using namespace scnet2;

void CurrentThread::cacheTid() {
    if (t_cachedTid == 0) {
        t_cachedTid = detail::gettid();
        int n = snprintf(t_tidString, sizeof t_tidString, "%5d", t_cachedTid);
        (void) n;
    }
}

bool CurrentThread::isMainThread() {
    return tid() == ::getpid();
}

Thread::Thread(const ThreadFunction& func, const string& threadName)
: started_(false),
  joined_(false),
  tid_(new pid_t(0)),
  func_(func),
  name_(threadName) { }

Thread::~Thread() {
    if (started_ && !joined_) {
        pthread_detach(pid_);
    }
}

void Thread::start() {
    assert(!started_);
    started_ = true;
    detail::ThreadData *data = new detail::ThreadData(func_, name_, tid_);
    if (int rc = pthread_create(&pid_, NULL, &detail::startThread, data)) { 
      started_ = false; 
      char buf[64];
      fprintf(stderr, "pthrad_create error:%s", strerror_r(rc, buf, sizeof
                                                           buf));
    }
}

int Thread::join() {
    assert(started_);
    assert(!joined_);
    joined_ = true;
    return pthread_join(pid_, NULL);
}
