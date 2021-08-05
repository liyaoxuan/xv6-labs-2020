#include "kernel/types.h"
#include "user/user.h"


int main(int argc, char* argv[]) {
    int i = 0;
    while (i++ < 10) {
        switch (i) {
        case 1:
            printf("1\n");
            break;
        case 2:
            printf("2\n");
            break;
        default:
            printf("default\n");
        }
    }
    exit(0);
}
