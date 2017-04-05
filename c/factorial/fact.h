#ifndef _FACT_H_
#define _FACT_H_

#include <math.h> // for pow, powl, and powf
//#include <stddef.h> // for size_t

#define MAX_FACT_INDEX 1755

long double odd_fact(unsigned);

long double fact_over_2en(unsigned);

long double fact(unsigned);

long double choose(unsigned, unsigned);

#endif
