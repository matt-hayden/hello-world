#include "fact.h"


fact_t
fact(size_t index) {
  static fact_t memo[MAX_FACT_INDEX+1] = { 1., 1. };
  if (MAX_FACT_INDEX < index) {
    return INFINITY;
  }
  if (!memo[index]) {
    memo[index] = fact(index-1)*index;
  }
  return memo[index];
}
