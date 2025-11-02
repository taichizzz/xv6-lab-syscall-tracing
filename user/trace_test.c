#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[]) {
  if (argc < 2) { printf("Usage: trace_test pid\n"); exit(1); }
  int pid = atoi(argv[1]);
  int r = trace(pid);
  printf("trace(%d) -> %d\n", pid, r);
  exit(0);
}