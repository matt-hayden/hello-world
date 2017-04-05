#ifndef _FACT_H_
#define _FACT_H_

#include <math.h> // for pow, powl, and powf

#define MAX_FACT_INDEX 65535


long double odd_fact_log2(unsigned);
long double fact_log2(unsigned);
long double choose_log2(unsigned, unsigned);

static inline
long double
exp_a_fact_log(long double f) {
  return powl(2., f);
}

static inline
long double
fact(unsigned index) {
  return exp_a_fact_log(fact_log2(index));
}

static inline
long double
odd_fact(unsigned index) {
  return exp_a_fact_log(odd_fact_log2(index));
}

static inline
long double
choose(unsigned numerator, unsigned denominator) {
  return exp_a_fact_log(choose_log2(numerator, denominator));
}
#endif
