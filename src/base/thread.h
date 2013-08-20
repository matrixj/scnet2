#ifndef SCNET2_BASE_THREAD_H
#define SCNET2_BASE_THREAD_H

#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/function.hpp>

#include <string>

#include <pthread.h>

namespace scnet2
{
using std::string;
class Thread : boost::noncopyable
{
    public:
     typedef boost::function<void ()> ThreadFunction;
     explicit Thread(const ThreadFunction&, const string& name = string());
     ~Thread();

     void start();
     int join();

     bool started() const { return started_; }
     pid_t tid() const { return *tid_; }
     const string& name() const { return name_; }

    private:
     bool started_;
     bool joined_;
     boost::shared_ptr<pid_t> tid_;
     pthread_t pid_;
     ThreadFunction func_;
     string name_;
};
}
#endif
