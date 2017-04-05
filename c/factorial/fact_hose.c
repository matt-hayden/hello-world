#include <stdio.h>
#include <stdlib.h>

#include "fact.h"

int
main(int argc, char **argv) {
  long double f;
  unsigned ubound = MAX_FACT_INDEX+2; // 16388 is a reasonable value
  if (argc == 2) {
    ubound = (unsigned) atol(argv[1]);
  }
  printf("%8s\t%12s\t%14s\n", "n", "log(n!)", "n!");
  for (unsigned x = 0; x < ubound; x++) {
    f = fact_log2(x);
    if (!isfinite(f)) exit(0);
    printf("%8u\t%12Lg\t%14Lg\n", x, f, exp_a_fact_log(f));
  }
}
