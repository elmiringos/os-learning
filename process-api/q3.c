#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>


int main() {
  int rc = fork();

  int fd[2];

  pipe(fd);

  if (rc < 0) {
    fprintf(stderr, "fork failed\n");
    exit(1);
  } else if (rc == 0) {
    close(fd[0]);
    printf("hello \n");
    write(fd[1], "x", 1);
    close(fd[1]);
  } else {
    close(fd[1]);
    char buf;
    read(fd[0], &buf, 1);
    printf("goodbye \n");
    close(fd[0]);
  }
}
