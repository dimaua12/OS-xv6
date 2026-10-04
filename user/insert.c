#include "kernel/types.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  if (argc != 2) {
    fprintf(2, "usage: insert file\n");
    exit(1);
  }

  if (insert(argv[1]) < 0) {
    fprintf(2, "insert: cannot write %s\n", argv[1]);
    exit(1);
  }

  exit(0);
}
