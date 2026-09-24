#include "kernel/types.h"
#include "user/user.h"

void sleep(int n){
	pause(n);
}

int
main(int argc, char *argv[])
{
  if (argc != 2) {
    fprintf(2, "usage: sleep ticks\n");
    exit(1);
  }

  sleep(atoi(argv[1]));
  exit(0);
}
