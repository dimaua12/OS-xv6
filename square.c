#include "kernel/types.h"
#include "kernel/fcntl.h"
#include "user/user.h"

int i;

void
square(int n)
{printf("\n%d", n**2;}

int
main(int argc, char *argv[])
{
  int i;

  if (argc <= 1) {
    cat(0);
    exit(0);
  }
  if (argc == 2){
	  square(atoi(argv[1]));
	  exit(0);
	}else{
		fprintf(2,"ERR");
		exit(-1);
	}
  exit(0);
}
