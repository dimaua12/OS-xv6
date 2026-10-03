 #include "kernel/types.h"
 #include "user/user.h"

  int
  main(int argc, char *argv[])
  {
    if (argc != 2) {
      fprintf(2, "usage: square number\n");
      exit(1);
    }

    printf("%d\n", square(atoi(argv[1])));
    exit(0);
  }
