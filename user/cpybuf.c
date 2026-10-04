#include "kernel/types.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  if (argc != 2) {
    fprintf(2, "usage: cpybuf file\n");
    exit(1);
  }

  if (cpybuf(argv[1]) < 0) {
    fprintf(2, "cpybuf: cannot copy %s\n", argv[1]);
    exit(1);
  }

  exit(0);
}
