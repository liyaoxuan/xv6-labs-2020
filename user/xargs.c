#include "kernel/types.h"
#include "kernel/param.h"
#include "user/user.h"


#define XARGS_BUF_SIZE 128


int main(int argc, char* argv[])
{
  char *argv_new[MAXARG];
  static char buf[MAXARG][XARGS_BUF_SIZE];
  int argc_new = 0;
    if (argc <= 1) {
        fprintf(2, "usage: xargs command\n");
        exit(-1);
    }

    for (int i = 1; i < argc; ++i) {
        argv_new[argc_new++] = argv[i];
    }

    int cnt = 0, idx = 0;
    int last_is_space = 0;
    char tmp;
    while (read(0, &tmp, 1) != 0) {
        if (tmp == '\n' || tmp == '\0' || cnt >= MAXARG-argc_new) {
            buf[cnt][idx] = '\0';
            if (idx != 0 && cnt < MAXARG-argc_new) {
                argv_new[cnt+argc_new] = buf[cnt];
                cnt += 1;
            }
            if (fork() == 0) {
                int ret = exec(argv_new[0], argv_new);
                exit(ret);
            } else {
                cnt = 0;
                idx = 0;
                wait(0);
            }
            continue;
        }
        if (tmp == ' ') {
            if (!last_is_space) {
                buf[cnt][idx++] = '\0';
                last_is_space = 1;
            }
            continue;
        }
        if (last_is_space) {
            argv_new[argc_new+cnt] = buf[cnt];
            cnt += 1;
            idx = 0;
        }
        buf[cnt][idx++] = tmp;
        last_is_space = 0;
    }
    exit(0);
}
