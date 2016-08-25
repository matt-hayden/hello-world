#include <gmp.h>

#include <stdio.h>
#include <stdlib.h>

#define MAX_SEQ 1756

typedef mpz_t counting;

counting fib_seq[MAX_SEQ] = {};

int
populate_fib() {
	mpz_init_set_si(fib_seq[0], 0);
	mpz_init_set_si(fib_seq[1], 1);
	int i;
	for (i = 2; i < MAX_SEQ; i++) {
		mpz_init_set_si(fib_seq[i], 0);
		mpz_add(fib_seq[i], fib_seq[i-2], fib_seq[i-1]);
	}
	return i;
}

void
free_internal(counting arr[]) {
	for (int i = 0; i < MAX_SEQ; i++) {
		if (arr[i]) mpz_clear(arr[i]);
		else break;
	}
}


int
main()
{
	int n = populate_fib();
	printf("%d Fibonacci numbers generated\n", n);
	for (int i = 0; i <= n; i++) {
		printf("%8d:\t", i);
		mpz_out_str(stdout, 10, fib_seq[i]);
		printf("\t");
		mpz_out_str(stdout, 16, fib_seq[i]);
		printf("\n");
	}
	free_internal(fib_seq);
	return EXIT_SUCCESS;
}
