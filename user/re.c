#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fcntl.h"

int main(void) {
  if(fork() == 0){
    close(1);
    open("out.txt", O_CREATE | O_WRONLY);   // gets fd 1
    char *args[] = {"echo", "redirected", 0};
    exec("echo", args);
    exit(1);
  }
  wait(0);
  exit(0);
}