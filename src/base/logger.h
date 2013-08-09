#ifndef SCNET2_BASE_LOGGER_H
#define SCNET2_BASE_LOGGER_H

#include <boost/noncopyable.hpp>
#include <boost/scoped_ptr.hpp>
#include <string>

#include <stdio.h>

namespace scnet2 {

class Logger : boost::noncopyable {
 private:
  class FilePtrHolder {
   private:
    FILE *_file;
    std::string _filename;
    void openFile();
    std::string getFileName(const std::string& basename);
    char _buffer[64 * 1024];

   public:
    FilePtrHolder(const std::string& basename) 
      : _filename(getFileName(basename)) { openFile();}

    ~FilePtrHolder() {
      ::fclose(_file);
    }
    size_t write(const char *str, size_t len);
    FILE *getFilePtr() {
      return _file;
    }
    void flush();
  };//end of FilePtrHolder class

  size_t write(const char *str, size_t len);

  const std::string _basename;
  boost::scoped_ptr<FilePtrHolder> _file;

 public:
  explicit Logger(const std::string& basename);
  ~Logger();
  size_t append(const char *logline, size_t len);
  void flush();
};
}
#endif
