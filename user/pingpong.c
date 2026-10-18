#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
int main(void) {
  int p[2], q[2]; char c = 'x';
  pipe(p); pipe(q);
  if (fork() == 0) { close(p[1]); close(q[0]); read(p[0], &c, 1); printf("%d: received ping\n", getpid()); write(q[1], &c, 1); close(p[0]); close(q[1]); exit(0); }
  close(p[0]); close(q[1]); write(p[1], &c, 1); read(q[0], &c, 1); printf("%d: received pong\n", getpid()); close(p[1]); close(q[0]); wait(0); exit(0);
}
