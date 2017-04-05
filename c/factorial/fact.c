#include "fact.h"


long double
odd_fact_log2(unsigned index) {
  static long double memo[MAX_FACT_INDEX+1] = { 0., 0. };
  if (index < 2) return 0;
  if (MAX_FACT_INDEX < index) {
    return INFINITY;
  }
  if (!memo[index]) {
    memo[index] = (index%2) ? odd_fact_log2(index-2)+log2(index) : odd_fact_log2(index-1);
  }
  return memo[index];
}


long double
odd_fact(unsigned index) {
  static long double memo[MAX_FACT_INDEX+1] = { 1., 1. };
  if (MAX_FACT_INDEX < index) {
    return INFINITY;
  }
  if (!memo[index]) {
    memo[index] = (index%2) ? odd_fact(index-2)*index : odd_fact(index-1);
  }
  return memo[index];
}


long double
fact_log2(unsigned index) {
  static long double memo[MAX_FACT_INDEX+1] = { 0., 0. };
  if (index < 2) return 0;
  if (MAX_FACT_INDEX < index) {
    return INFINITY;
  }
  if (!memo[index]) {
    memo[index] = odd_fact_log2(index)+fact_log2(index/2)+(index/2);
  }
  return memo[index];
}


long double
fact_over_2en(unsigned index) {
  if (index == 0) return 1.;
  if (index == 1) return 0.5;
  long double r = odd_fact(index)*fact_over_2en(index/2);
  return (index%2) ? r/2 : r;
}


long double
fact(unsigned index) {
  if (index < 2) return 1;
  return fact_over_2en(index)*powl(2., index);
}


long double
choose_log2(unsigned numerator, unsigned denominator) {
  if (denominator <= numerator) return
    fact_log2(numerator) - fact_log2(denominator) - fact_log2(numerator-denominator);
  return 0.;
}
