#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int fd[2];

    if (pipe(fd) == -1) {
        perror("pipe failed");
        exit(1);
    }

    pid_t rc1 = fork();
    if (rc1 < 0) {
        perror("fork failed");
        exit(1);
    } else if (rc1 == 0) {
        close(fd[0]);
        dup2(fd[1], STDOUT_FILENO);
        close(fd[1]);

        printf("Hello from child 1\n");
        fflush(stdout);
        _exit(0);
    }

    pid_t rc2 = fork();
    if (rc2 < 0) {
        perror("fork failed");
        exit(1);
    } else if (rc2 == 0) {
        close(fd[1]);
        dup2(fd[0], STDIN_FILENO);
        close(fd[0]);

        char buf[100];
        scanf("%99[^\n]", buf);
        printf("Child 2 got: %s\n", buf);
        fflush(stdout);
        _exit(0);
    }

    // Родительский процесс
    close(fd[0]);
    close(fd[1]);
    wait(NULL);
    wait(NULL);

    printf("Parent finished\n");
    return 0;
}
