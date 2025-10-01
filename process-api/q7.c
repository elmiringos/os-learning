#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>

int main() {
  int rc = fork();

  if (rc < 0) {
    printf("Error to call fork");
    exit(1);
  } else if (rc == 0) {
    close(STDOUT_FILENO);
    printf("Try to write to stdout form child");
  } else {
    int rc_wait = wait(NULL);
    printf("Try to write to stdout from parent");
  }
}
