
#include <gsl/gsl_blas.h>

gsl_matrix*
fib_m1(void) {
  gsl_matrix *m = gsl_matrix_alloc(2, 2);
  assert (m != NULL);
  gsl_matrix_set(m, 0, 0, 1.);
  gsl_matrix_set(m, 0, 1, 1.);
  gsl_matrix_set(m, 1, 0, 1.);
  gsl_matrix_set(m, 1, 1, 0.);
  return m;
}

gsl_matrix*
fib_m(const unsigned n) {
  static
  gsl_matrix *memo = NULL;
  if (memo == NULL) {
    memo = malloc(6*sizeof(gsl_matrix));
    memo[1] = fib_m1();
  }
  gsl_matrix *result = gsl_matrix_malloc(2, 2);
}
