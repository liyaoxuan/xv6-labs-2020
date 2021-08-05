#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/fs.h"
#include "kernel/fcntl.h"
#include "user/user.h"


void
find(char* dir, char* name)
{
    int fd;
    struct dirent de;
    struct stat st;
    char buf[512], *p;
    if ((fd = open(dir, 0)) < 0) {
       fprintf(2, "find: cannot open %s\n", dir);
       return;
    }

    if (strlen(dir) + 1 + DIRSIZ + 1 > sizeof(buf)) {
        fprintf(2, "find: path too long\n");
        close(fd);
        return;
    }
    strcpy(buf, dir);
    p = buf + strlen(buf);
    *p++ = '/';
    while (read(fd, &de, sizeof(de)) == sizeof(de)) {
        if (de.inum == 0)
            continue;
        memmove(p, de.name, DIRSIZ);
        p[DIRSIZ] = 0;
        if (stat(buf, &st) < 0) {
            printf("find: cannot stat %s\n", buf);
            continue;
        }
        switch (st.type) {
        case T_FILE:
            if (strcmp(de.name, name) == 0){
                printf("%s\n", buf+2); //skip "./"
            }
            break;
        case T_DIR:
            if (strcmp(de.name, ".") == 0 || strcmp(de.name, "..") == 0)
                continue;
            find(buf, name);
            break;
        }
    }
    close(fd);
}


int
main(int argc, char* argv[])
{
    if (argc <= 2) {
        fprintf(2, "usage: find path file\n");
        exit(1);
    }

    char* path = argv[1];
    char* filename = argv[2];
    find(path, filename);
    exit(0);
}

