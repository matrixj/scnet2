#include <base/current_thread.h>

//#include <pthread.h>
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/syscall.h>

//using namespace scnet2::base;

int main() {
  printf("%d\n", static_cast<int>(syscall(SYS_gettid)));
}
