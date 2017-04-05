//#include <malloc.h>
#include <stdio.h>

#include "fact.h"

int
main(int argc, char **argv) {
  long double f;
  for (unsigned x = 0; x < 25; x++) {
    f = fact_over_2en(x);
    //printf("\t%12u\t%12Lg\t%12Lg\t%12Lg\n", x, odd_fact(x), f, fact(f));
    printf("\t%12u\t%12Lg\t%12Lg\t%12Lg\n", x, odd_fact(x), f, f*powl(2., x));
  }
}
