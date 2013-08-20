#include <string>

#include <boost/bind.hpp>

#include <stdio.h>
#include <base/logbuffer.h>
#include <base/thread.h>
#include <base/Timestamp.h>

using  std::string;
using namespace scnet2;

LogBuffer *g_log = NULL;

void print() {
  const int kBatch = 2000;

  for (int t = 0; t < 30; ++t) {
    int i = 0;
    Timestamp begin = Timestamp::now();

    for (; i < kBatch; ++i) {
      g_log->appendToBuffer("abcdefghijklmnopqrstuvwxyz\n", 27);
    }

    Timestamp end = Timestamp::now();
    printf("%f\n", static_cast<double>(timestampDifference(end, begin)) / kBatch);
    struct timespec ts = { 0,  50 * 1000 *1000 };
    nanosleep(&ts, NULL);
  }
}

class TestLog {
 public:
  TestLog() : log_(string("tesglog")) {}
  ~TestLog() {}
 private:
  LogBuffer log_;
};

int main() {
  string basename = "testlog";
  LogBuffer logger(basename);

  g_log = &logger;
  logger.start();

  print();

}
