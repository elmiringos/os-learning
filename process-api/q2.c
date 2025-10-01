#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>

int main() {
    printf("Hello world (pid:%d)\n", (int) getpid());

    int fd = open("./q2.txt", O_CREAT | O_RDWR | O_TRUNC, S_IRWXU);
    if (fd < 0) {
        perror("open");
        exit(1);
    }

    int rc = fork();

    if (rc < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        // child
        printf("hello, i am child (pid:%d)\n", (int) getpid());
        char msg[] = "child wrote 101\n";
        write(fd, msg, strlen(msg));
    } else {
        // parent
        printf("hello, i am parent (pid:%d)\n", (int) getpid());
        char msg[] = "parent wrote 22\n";
        write(fd, msg, strlen(msg));

        wait(NULL); // wait for child to finish
    }

    close(fd);
    return 0;
}
