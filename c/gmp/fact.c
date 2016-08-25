#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_SEQ 1756

typedef long double real;

real fact_seq[MAX_SEQ] = { 1 };

int
populate_fact() {
	int i;
	real s = fact_seq[0];
	for (i = 1; i < MAX_SEQ; i++) {
		s *= i;
		if isinf(s) break;
		fact_seq[i] = s;
	}
	return i;
}

real
fact(int x) {
	if (x < 0)
		return NAN;
	if (MAX_SEQ-1 < x)
		return INFINITY;
	return fact_seq[x];
}

real
choose(int n, int k) {
	if (n <= 0)
		return 1;
	if (k <= 0)
		return 1;
	if (n < k)
		return n;
	// Recurse if n is too high
	if ( (fact(n) == 0.) || isinf(fact(n)) )
		return choose(n-1, k-1)+choose(n-1, k);
	return fact(n)/(fact(k)*fact(n-k));
}

int
main()
{
	int n = populate_fact();
	printf("%d factorials generated\n", n);
	for (int i = 0; i <= n; i++)
		printf("%4d: %24Le\n",
			i, fact(i));
	return EXIT_SUCCESS;
}
