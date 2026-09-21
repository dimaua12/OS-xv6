#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fcntl.h"


char c;
char *rozdiel = " -\r\t\n./,";

int delim(char c){
  return strchr(rozdiel, c) != 0;
}
void sixfive(int fd){
  int n;
  int number = 0;
  int isNumber = 1;
  int inNumber = 0;
  while((n = read(fd,&c,1))>0){
    if(c >= '0' && c <= '9'){
      if(!inNumber){
        number = 0;
        inNumber = 1;
      }
      number = number * 10 + (c- '0');
  }else if(delim(c)){
        if(inNumber){
          if(isNumber && (number % 5 == 0 || number % 6 == 0)){
              printf("\n%d",number);
          }
              number = 0;
              inNumber = 0;
              isNumber = 1;
          }
  }else{
  if(inNumber ){
    isNumber = 0;
    }
  }
}
  if(inNumber && isNumber){
    if(number % 5 ==0 || number % 6 == 0){
      printf("\n%d",number);
    }
  }

  if(n<0){
    fprintf(2,"sixfive: read error\n");
    exit(1);
  }

}

int main(int argc, char *argv[]){
  if(argc < 2){
    fprintf(2, "CHYBA PRETOZE < 2");
    exit(1);
  }
  for(int i = 1; i < argc; i++){
    int fd = open(argv[i],O_RDONLY);
    if(fd<0){
      fprintf(2,"NEPODARILO SA OTVORIT` %s",argv[i]);
          exit(1);
  }
  sixfive(fd);
  close(fd);
  exit(0);
  }
}
