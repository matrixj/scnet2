#ifndef SCNET2_BASE_LOGBUFFER_H
#define SCNET2_BASE_LOGBUFFER_H

class Logbuffer : boost::noncopyable {
 public:
  Logbuffer();
  ~Logbuffer();
  void appendTobuffer();
  void writeToFile();


 private:
  Logbuffer(const Logbuffer&);
  void operator=(const Logbuffer&);

  typedef scnet2::detail::Buffer<64 * 1024> BufferType;
  typedef boost::ptr_vector<BufferType> BufferVector;
  typedef BufferVector::auto_type VecTypePtr;
  void threadFunc();

  VecTypePtr _current;
  VecTypePtr _next;
  BufferVector _bufferVector;
  scnet2::Thread _thread;
  bool _logging;
}

#endif
