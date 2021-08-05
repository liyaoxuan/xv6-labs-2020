#include <kernel/types.h>
#include <user/user.h>


int pipeline(int data[], int num);

int main(int argc, char* argv[])
{
    int numbers[35], count;
    for (count = 0; count < 34; ++count)
        numbers[count] = count + 2;
    pipeline(numbers, count);
    exit(0);
}


int pipeline (int data[], int num)
{
    int p[2];
    pipe(p);
    if (fork() == 0) { // child process
        //first read from parent
        close(p[1]);
        int data_new[35], count = 0;
        while (read(p[0], &data_new[count], sizeof(int)) != 0) count += 1;
        close(p[0]);

        if (count == 0) {
            fprintf(0, "child process %d exit!\n", getpid());
            exit(0);
        }
        // send to right neighbour
        pipeline(data_new, count);
    } else {
        close(p[0]);
        fprintf(0, "prime %d\n", data[0]);
        //fprintf(0, "parent process %d begin to send\n", getpid());
        for (int i = 1; i < num; ++i) {
            if (data[i] % data[0] == 0)
                continue;
            //fprintf(0, "parent process %d send %d\n", getpid(), data[i]);
            write(p[1], &data[i], sizeof(int));
        }
        close(p[1]);
        wait(0);
    }
    return 0;
}

