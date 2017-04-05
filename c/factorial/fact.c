#include "fact.h"


long double
odd_fact_log2(unsigned index) {
  static long double memo[MAX_FACT_INDEX+1] = { 0., 0. };
  if (index < 2) return 0.;
  if ((index < MAX_FACT_INDEX) && memo[index]) return memo[index];
  long double f = (index%2) ?
                    odd_fact_log2(index-2)+log2(index)
                    : odd_fact_log2(index-1);
  if (index < MAX_FACT_INDEX) memo[index] = f;
  return f;
}


long double
fact_log2(unsigned index) {
  static long double memo[MAX_FACT_INDEX+1] = { 0., 0. };
  if (index < 2) return 0;
  if ((index < MAX_FACT_INDEX) && memo[index]) return memo[index];
  long double f = odd_fact_log2(index)
                  + fact_log2(index/2)
                  + (index/2);
  if (index < MAX_FACT_INDEX) memo[index] = f;
  return f;
}


long double
choose_log2(unsigned numerator, unsigned denominator) {
  if (denominator <= numerator) return
    fact_log2(numerator) - fact_log2(denominator) - fact_log2(numerator-denominator);
  return 0.;
}
