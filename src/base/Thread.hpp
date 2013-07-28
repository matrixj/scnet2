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

        bool started() const { return _started; }
        pid_t tid() const { return *_tid; }
        const string& getName() const { return _name; }

        private:
         bool _started;
         bool _joined;
         boost::shared_ptr<pid_t> _tid;
         pthread_t _pid;
         ThreadFunction _func;
         string _name;
    };
}
#endif
