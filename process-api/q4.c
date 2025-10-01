#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>


int main() {
  int rc = fork();

  if (rc < 0) {
    printf("error in invoking fork");
    exit(1);
  } else if (rc == 0) {
    execlp("ls", "ls", (char *)0);
  } else {
    wait(NULL);
  }

  return 0;
}
