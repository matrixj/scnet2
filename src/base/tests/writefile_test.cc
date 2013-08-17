#include <base/logger.h>
#include <string>

using std::string;
using scnet2::Logger;


int main() {
  string filename = "filetowrite";
  Logger out(filename);

  for (int i = 0; i < 1000; ++i) {
    out.append("asdfsdfadfasdfasdf\n", sizeof "asdfsdfadfasdfasdf\n");
  }

  return 0;
}
