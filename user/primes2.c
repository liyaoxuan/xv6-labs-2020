#include <kernel/types.h>
#include <user/user.h>


#define R 0
#define W 1
int pipeline(int data[], int num);

int main(int argc, char* argv[])
{
    int numbers[35], count = 0;
    for (int i = 2; i <= 35; ++i)
        numbers[count++] = i;
    while (count > 0) {
        int p[2];
        pipe(p);
        if (fork() == 0) {
            close(p[W]);
            count = 0;
            while (read(p[R], &numbers[count], sizeof(int)) != 0) {
                count += 1;
            }
            close(p[R]);
            if (count == 0)
                exit(0);
        } else {
            close(p[R]);
            fprintf(0, "prime %d\n", numbers[0]);
            for (int i = 1; i < count; ++i) {
                if (numbers[i] % numbers[0] == 0)
                    continue;
                write(p[W], &numbers[i], sizeof(int));
            }
            close(p[W]);
            wait(0);
            break;
        }
    }
    exit(0);
}

