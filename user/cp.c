#include "kernel/types.h"
#include "kernel/fcntl.h"
#include "user/user.h"

char buf[512];

void
cp(int in, int out)
{
  int n;
  while ((n = read(in, buf, sizeof(buf))) > 0) {
    if (write(out,buf,n) != n) {
      fprintf(2, "cat: write error\n");
      close(in);
      close(out);
      exit(1);
    }
  }
  if (n < 0) {
    fprintf(2, "read error\n");
    close(in);
    close(out);
    exit(1);
  }
  close(in);
  close(out);
}

int
main(int argc, char *argv[])
{
  int in,out;

  if (argc != 3) {
    fprintf(2,"err");
    exit(1);
  }
  if((in = open(argv[1], O_RDONLY)) < 0){
  	fprintf(2,"err");
	close(in);
	exit(1);
  }
    out = open(argv[2], O_CREATE | O_WRONLY | O_TRUNC);
    if (out < 0) {
      fprintf(2, "cannot create %s\n", argv[2]);
      close(in);
      exit(1);
    }
  cp(in,out);
  exit(0);
}
