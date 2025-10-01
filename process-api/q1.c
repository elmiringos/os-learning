#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char** argv) {
  printf("Hello world (pid:%d) \n", (int) getpid());
  int a = 100;

  printf("Initial value for a = %d", a);

  int rc = fork();

  if (rc < 0) {
    fprintf(stderr, "fork failed\n");
    exit(1);
  } else if (rc == 0) {
    a = 200;
    printf("hello, i am child (pid:%d) a = %d \n", (int) getpid(), a);
  } else {
    int rc_wait = wait(NULL);
    printf("hello, I am parent of %d (rc_wait:%d) (pid:%d) a = %d \n", rc, rc_wait, (int) getpid(), a);
  }

  return 0;
}
