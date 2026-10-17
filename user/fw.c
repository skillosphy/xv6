// always include kernel types kernel stat and user user

#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(void)
{
    int pid= fork();
    if (pid < 0)
    {
        fprintf(2, "fork failed\n");
        exit(69);

    }
    if (pid == 0)
    {
        printf("child %d\n", getpid());
        exit(67);
    }

    int status;
    wait(&status);
    printf("parent: child %d exited with %d\n", pid, status);
    exit(68);
}
