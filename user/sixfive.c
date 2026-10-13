#include "kernel/types.h"
#include "user/user.h"
#include "kernel/fcntl.h"

#define MAX_BUF_SIZE 40

static void
process_file(int fd)
{
    char c;
    char buf[MAX_BUF_SIZE];
    int n, buf_len = 0, start_valid = 1;

    while ((n = read(fd, &c, 1)) > 0) {
        char *is_valid = strchr(" -\r\t\n./,", c);
        if (is_valid) {
            if (buf_len > 0) {
                buf[buf_len] = '\0';
                int num = atoi(buf);
                if (num % 5 == 0 || num % 6 == 0)
                    fprintf(1, "%d\n", num);
            }
            buf_len = 0;
            start_valid = 1;
        } else if (c >= '0' && c <= '9' && start_valid) {
            if (buf_len < MAX_BUF_SIZE - 1)
                buf[buf_len++] = c;
        } else {
            buf_len = 0;
            start_valid = 0;
        }
    }

    if (buf_len > 0) {
        buf[buf_len] = '\0';
        int num = atoi(buf);
        if (num % 5 == 0 || num % 6 == 0)
            fprintf(1, "%d\n", num);
    }
}

int main(int argc, char *argv[])
{
    if (argc == 1) {
        process_file(0);
    }
    for (int i = 1; i < argc; i++) {
        int fd = open(argv[i], O_RDONLY);
        if (fd < 0) {
            fprintf(2, "cannot open file %s\n", argv[i]);
            continue;
        }
        process_file(fd);
        close(fd);
    }

    exit(0);
}