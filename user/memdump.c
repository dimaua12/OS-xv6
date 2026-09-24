#include "kernel/types.h"
#include "user/user.h"
#include "kernel/fcntl.h"

void memdump(char *fmt, char *data, int len);

int
main(int argc, char *argv[])
{
  if (argc == 1) {
    printf("Example 1:\n");
    int a[2] = {61810, 2026};
    memdump("ii", (char *)a, sizeof(a));

    printf("Example 2:\n");
    memdump("S", "a string", sizeof("a string"));

    printf("Example 3:\n");
    char *s = "another";
    memdump("s", (char *)&s, sizeof(s));

    struct sss {
      char *ptr;
      int num1;
      short num2;
      char byte;
      char bytes[8];
    } example;

    example.ptr = "hello";
    example.num1 = 1819438967;
    example.num2 = 100;
    example.byte = 'z';
    strcpy(example.bytes, "xyzzy");

    printf("Example 4:\n");
    memdump("pihcS", (char *)&example, sizeof(example));

    printf("Example 5:\n");
    memdump("sccccc", (char *)&example, sizeof(example));
  } else if (argc == 2) {
    // format in argv[1], up to 512 bytes of data from standard input.
    char data[512];
    int n = 0;
    memset(data, '\0', sizeof(data));
    while (n < sizeof(data)) {
      int nn = read(0, data + n, sizeof(data) - n);
      if (nn <= 0)
        break;
      n += nn;
    }
    memdump(argv[1], data, n);
  } else {
    printf("Usage: memdump [format]\n");
    exit(1);
  }
  exit(0);
}


void
memdump(char *fmt, char *data, int len)
{
  // Your code here.  `data` holds `len` valid bytes.
  int remaining = len;

  while (*fmt != '\0') {
    switch (*fmt) {
    case 'c':
      if (remaining < sizeof(char)) {
        fprintf(2, "memdump: not enough data for 'c'\n");
        return;
      }
      printf("%c\n", *data);
      data += sizeof(char);
      remaining -= sizeof(char);
      break;

    case 'h':
      if (remaining < sizeof(short)) {
        fprintf(2, "memdump: not enough data for 'h'\n");
        return;
      }
      printf("%d\n", *((short *)data));
      data += sizeof(short);
      remaining -= sizeof(short);
      break;

    case 'i':
      if (remaining < sizeof(int)) {
        fprintf(2, "memdump: not enough data for 'i'\n");
        return;
      }
      printf("%d\n", *((int *)data));
      data += sizeof(int);
      remaining -= sizeof(int);
      break;

    case 'p':
      if (remaining < sizeof(uint64)) {
        fprintf(2, "memdump: not enough data for 'p'\n");
        return;
      }
      printf("%lx\n", *((uint64 *)data));
      data += sizeof(uint64);
      remaining -= sizeof(uint64);
      break;

    case 's':
      if (remaining < sizeof(char *)) {
        fprintf(2, "memdump: not enough data for 's'\n");
        return;
      }
      printf("%s\n", *((char **)data));
      data += sizeof(char *);
      remaining -= sizeof(char *);
      break;

    case 'S':
      while (remaining > 0 && *data != '\0') {
        printf("%c", *data);
        data++;
        remaining--;
      }
      printf("\n");
      if (remaining > 0) {
        data++;
        remaining--;
      }
      break;
    }

    fmt++;
  }
}
