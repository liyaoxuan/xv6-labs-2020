#include <kernel/types.h>
#include <user/user.h>


int
main(int argc, char* argv[])
{
    int p[2][2];
    pipe(p[0]);
    pipe(p[1]);
    if (fork() == 0) {
        char v;
        read(p[0][0], &v, 1);
        fprintf(0, "%d: received ping\n", getpid());
        write(p[1][1], &v, 1);
        exit(0);
    } else {
        char v = 'x';
        write(p[0][1], &v, 1);
        read(p[1][0], &v, 1);
        fprintf(0, "%d: received pong\n", getpid());
        exit(0);
    }
}
