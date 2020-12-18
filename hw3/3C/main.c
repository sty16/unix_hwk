#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <ctype.h>
#include <iostream>
using namespace std;

int main() {
    int f[2];
    pipe(f);
    for (int i = 0; i < 2; ++i) {
        pid_t pid = fork();
        if (pid == 0) {
            if (i == 1) {
                close(f[1]);
                dup2(f[0], 0);
                char *name = "/usr/bin/wc";
                char **argv = new char*[1];
                argv[0] = "/usr/bin/wc";
                int exet_st = execv(name, argv);
                close(f[0]);
                _exit(EXIT_SUCCESS);
            } else {
                close(f[0]);
                char buff[] = "adfasdfasdfasdfasdfasdfasdfads";
                write(f[1], buff, strlen(buff));
                close(f[1]);
                _exit(EXIT_SUCCESS);
            }
        }
    }
    close(f[0]);
    close(f[1]);
    for (int i = 0; i < 2; ++i) {
        wait(NULL);
    }
    return 0;
}