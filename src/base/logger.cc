#include <base/logger.h>
#include <base/current_thread.h>

#include <string>

#include <assert.h>
#include <string.h>
#include <sys/time.h>

using namespace scnet2;
using std::string;

Logger::Logger(const string& basename) 
  : _basename(basename),
    _file(new FilePtrHolder(basename)) {
 //   assert(basename.fine("/") == string::npos);
}

Logger::~Logger() {  }

void Logger::FilePtrHolder::openFile() {
  //const string filename = getFileName(_basename);
  _file = ::fopen(_filename.data(), "ae");
  assert(_file);
  ::setbuffer(_file, _buffer, sizeof _buffer);
}

size_t Logger::FilePtrHolder::write(const char *str, size_t len) {
  return ::fwrite_unlocked(str, 1, len, _file);
  
}

size_t Logger::write(const char *str, size_t len) {
  return _file->write(str, len);
}

size_t Logger::append(const char *str, size_t len) {
  size_t n = write(str, len);
  while (n < len) {
    size_t m = write(str + n, len - n);
    if (m == 0) {
      int err = ferror(_file->getFilePtr());
      fprintf(stderr, "write logfile error in Logger::append %s \n",
              strerror(err));
      break;
    }
    n += m;
  }
  return n;
}

void Logger::FilePtrHolder::flush() {
  ::fflush(_file);
}

void Logger::flush() {
  _file->flush();
}

string Logger::FilePtrHolder::getFileName(const string& basename) {
  string name;
  name.reserve(basename.size() + 64);
  name = basename;

  char subfix[64];
  struct timeval now;
  gettimeofday(&now, NULL);
  time_t tt = now.tv_sec;
  struct tm t;
  localtime_r(&tt, &t);
  /*
  sprintf(subfix, 
          ".lib.%02d-%02d-%llx.log.%04d%02d%02d",
          t.tm_hour,
          t.tm_min,
          static_cast<long long unsigned int>(::getpid()),
           t.tm_year + 1990,
          t.tm_mon + 1, 
          t.tm_mday
          );
  */
#ifndef DEBUG
  sprintf(subfix, 
          ".lib.%02d-%02d.log.%d.%04d%02d%02d",
          t.tm_hour,
          t.tm_min,
          CurrentThread::tid(),
          t.tm_year + 1990,
          t.tm_mon + 1, 
          t.tm_mday
          );
#else
  sprintf(subfix,
          "debug.lib.log.%04d%02d%02d",
          t.tm_year + 1990,
          t.tm_mon + 1,
          t.tm_mday
          );
#endif
  name += subfix;
  fflush(stdout);
  return name;
}

