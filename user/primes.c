#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

static void sieve(int in);
static void (*next_sieve)(int);

static void sieve(int in) {
  int prime, n, p[2];
  if (read(in, &prime, sizeof(prime)) != sizeof(prime)) { close(in); exit(0); }
  printf("prime %d\n", prime);
  pipe(p);
  if (fork() == 0) { close(p[1]); close(in); next_sieve(p[0]); }
  close(p[0]);
  while (read(in, &n, sizeof(n)) == sizeof(n)) if (n % prime) write(p[1], &n, sizeof(n));
  close(in); close(p[1]); wait(0); exit(0);
}
int main(void) {
  next_sieve = sieve;
  int p[2]; pipe(p);
  if (fork() == 0) { close(p[1]); sieve(p[0]); }
  close(p[0]); for (int i = 2; i <= 35; i++) write(p[1], &i, sizeof(i));
  close(p[1]); wait(0); exit(0);
}
