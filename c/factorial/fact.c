#include "fact.h"

fact_t
odd_fact(size_t index) {
  static fact_t memo[MAX_FACT_INDEX+1] = { 1., 1. };
  if (MAX_FACT_INDEX < index) {
    return INFINITY;
  }
  if (!memo[index]) {
    memo[index] = (index%2) ? odd_fact(index-2)*index : odd_fact(index-1);
  }
  return memo[index];
}

fact_t
fact(size_t index) {
  if (index < 2) return 1;
  return odd_fact(index)*fact(index/2)*POW(2, index/2);
}
