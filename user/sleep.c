#include <kernel/types.h>
#include <kernel/stat.h>
#include <user/user.h>


int
main(int argc, char* argv[])
{
    if(argc != 2) {
        fprintf(2, "usage: sleep <time>(in seconds)\n");
        exit(-1);
    }

    int time = atoi(argv[1]);
    if (time < 0) {
        fprintf(2, "error: time should be non-negative\n");
        exit(-1);
    }

    sleep(time);
    exit(0);
}
