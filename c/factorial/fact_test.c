#include <stdio.h>

#include "fact.h"

int
main(int argc, char **argv) {
  printf("Computing...\n");
  fact(MAX_FACT_INDEX+1);
  int i;
  for (i = 0; i < 24; i++) {
    printf("%02d %25.0" FACT_PRINTF_FORMAT "f\n", i, fact(i));
  }
  for (i = MAX_FACT_INDEX-24; i <= MAX_FACT_INDEX; i++) {
    printf("%02d %.2" FACT_PRINTF_FORMAT "e\n", i, fact(i));
  }
}
