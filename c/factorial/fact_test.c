#include <stdio.h>
#include <stdlib.h>

#include "fact.h"

int
main(int argc, char **argv) {
  long double f;
  for (unsigned x = 0; x < (unsigned) atol(argv[1]); x++) {
    f = fact_log2(x);
    printf("%12u\t%12Lg\t%12Lg\n", x, f, (f < 16388.) ? exp_a_fact_log(f) : INFINITY);
  }
}
