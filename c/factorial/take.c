//#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>

#include "fact.h"

int
main(int argc, char **argv) {
  if (argc != 2+1) {
    printf("Check usage\n");
    exit(1);
  }
  unsigned num = (unsigned) atoi(argv[1]);
  unsigned denom = (unsigned) atoi(argv[2]);
  printf("(%u %u) = ", num, denom);
  printf("%Lg\n", choose(num, denom));
}
