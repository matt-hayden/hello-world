#ifndef _FACT_H_
#define _FACT_H_
#include <math.h>
#include <stddef.h> // for size_t

#define MAX_FACT_INDEX 1755
typedef long double fact_t;
#define FACT_PRINTF_FORMAT "L"
/*
#define MAX_FACT_INDEX 170
typedef double fact_t;
#define FACT_PRINTF_FORMAT "l"

#define MAX_FACT_INDEX 34
typedef float fact_t;
#define FACT_PRINTF_FORMAT ""
*/

fact_t fact(size_t);
#endif
