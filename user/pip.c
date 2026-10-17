#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(void) {
  int p[2];
  pipe(p);                          // p[0] read end, p[1] write end
  if(fork() == 0){
    close(p[1]);                    // child only reads
    char buf[32];
    int n = read(p[0], buf, sizeof(buf) - 1);
    buf[n] = 0;
    printf("child got: %s\n", buf);
    close(p[0]);
    exit(0);
  }
  close(p[0]);                      // parent only writes
  write(p[1], "hello", 5);
  close(p[1]);
  wait(0);
  exit(0);
}