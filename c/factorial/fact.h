#ifndef _FACT_H_
#define _FACT_H_
#include <math.h>
#include <stddef.h> // for size_t

//#define MAX_FACT_INDEX 1755
#define MAX_FACT_INDEX 200

#if (170 <= MAX_FACT_INDEX)
  typedef long double fact_t;
  #define FACT_PRINTF_FORMAT "L"
#elif (34 <= MAX_FACT_INDEX)
  typedef double fact_t;
  #define FACT_PRINTF_FORMAT "l"
#else
  typedef float fact_t;
  #define FACT_PRINTF_FORMAT ""
#endif

fact_t fact(size_t);
#endif
