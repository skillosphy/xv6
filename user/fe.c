#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"


int main(void) {
  if(fork() == 0){
    char *args[] = {"echo", "hi", "there", 0};
    exec("echo", args);

    // if exec fails this will not print
    
    fprintf(2, "exec failed\n");   
    exit(1);
  }
  wait(0);
  printf("parent done\n");
  exit(0);
}