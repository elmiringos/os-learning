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
    printf("child pid:%d \n", (int) getpid());
    int rc_wait = wait(NULL);
    printf("using wait in child process rc_wait=%d", rc_wait);
  } else {
    int rc_wait = wait(NULL);
    printf("parent pid:%d, rc_wait=%d \n", (int) getpid(), rc_wait);
  }
}
