#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fcntl.h"

void dup2_xv6(int oldfd, int newfd) {
  if (oldfd == newfd) return;
  close(newfd);
  while (dup(oldfd) != newfd) {
  }
}

int
main(int argc, char *argv[])
{
  if (argc < 2) {
    fprintf(2, "Usage: strace command [args...]\n");
    exit(1);
  }

  int pid = fork();
  if (pid < 0) {
    fprintf(2, "strace: fork failed\n");
    exit(1);
  }

  if (pid == 0) {
    int fd = open("user_output.txt", O_CREATE | O_WRONLY);
    if (fd >= 0) {
      dup2_xv6(fd, 1);
      close(fd);
    }

    int curr_pid = getpid();
    trace(curr_pid);
    exec(argv[1], argv + 1);
    fprintf(2, "strace: exec %s failed\n", argv[1]);
    exit(1);
  } else {
    wait(0);
  }

  exit(0);
}