
#include "fact.h"


long double
odd_fact_log2(unsigned index) {
  if (index < 2) return 0.L; // This function is recursive
#ifdef ALLOW_MEMO_ON_STACK
  static
  long double memo[MAX_FACT_INDEX+1] = { 0.L, 0.L };
#else
  static
  long double *memo = NULL;
  if (memo == NULL) {
    memo = malloc((MAX_FACT_INDEX+1)*sizeof(memo));
    if (memo == NULL) {
      fprintf(stderr, "Out of memory\n");
      exit(10);
    }
    memo[0] = memo[1] = 0.L;
  }
#endif
  if ((index < MAX_FACT_INDEX) && (memo[index] != 0.L)) return memo[index];
  long double f = (index%2) ?
                    odd_fact_log2(index-2)+log2l(index)
                    : odd_fact_log2(index-1);
  if (index < MAX_FACT_INDEX) memo[index] = f;
  return f;
}


long double
fact_log2(unsigned index) {
  if (index < 2) return 0.L; // This function is recursive
  return odd_fact_log2(index)
         + fact_log2(index/2)
         + (index/2);
}


long double
choose_log2(unsigned numerator, unsigned denominator) {
  if (numerator == 0 || denominator == 0)
    return 0.L; // This function is recursive, and log-output
  if (denominator <= numerator) return
    odd_fact_log2(numerator)
    - odd_fact_log2(numerator-denominator)
    - odd_fact_log2(denominator)
    + choose_log2(numerator/2, denominator/2);
  return 0.L;
}
