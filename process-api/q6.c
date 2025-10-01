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
  } else {
    int status;
    pid_t child_pid = rc;
    int rc_wait = waitpid(rc, &status, 0);
    printf("parent pid:%d, rc_wait=%d \n", (int) getpid(), rc_wait);
    printf("child status = %d", status);
  }
}
