#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/param.h"
#include "user/user.h"
int main(int argc, char **argv) {
  if (argc < 2) { fprintf(2, "usage: xargs command [args...]\n"); exit(1); }
  char line[512], *args[MAXARG]; int n = argc - 1, len = 0, k;
  for (int i = 1; i < argc; i++) args[i - 1] = argv[i];
  while ((k = read(0, line + len, sizeof(line) - len - 1)) > 0) {
    len += k; line[len] = 0; char *start = line;
    for (int i = 0; i <= len; i++) if (line[i] == '\n' || line[i] == 0) {
      line[i] = 0; if (*start) { args[n] = start; args[n + 1] = 0;
        if (fork() == 0) { exec(args[0], args); exit(1); } wait(0); }
      start = line + i + 1;
    }
    len = 0;
  }
  exit(0);
}
