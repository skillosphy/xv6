#include "kernel/types.h"
#include "kernel/sysinfo.h"
#include "user/user.h"

int main(void) {
  struct sysinfo si;
  if(sysinfo(&si) < 0){ fprintf(2, "sysinfo failed\n"); exit(1); }
  printf("free memory: %ld bytes, procs: %ld\n", si.freemem, si.nproc);
  exit(0);
}