#include <stdio.h>
#include <stdlib.h>

#include <assert.h>

#define LIMIT 100000000LL

typedef
unsigned long long  sieve_size_t;

typedef
struct prime_array_struct
{
	size_t		len;
	int		member_size;
	sieve_size_t	* primes;
}
prime_array;

#define INIT_PRIME_ARRAY() \
{ .len=0, .member_size=sizeof(sieve_size_t) }

prime_array
get_primes(sieve_size_t limit)
{
	prime_array pa = INIT_PRIME_ARRAY();

	int * is_composite;
	is_composite = calloc(limit, sizeof(int));

	sieve_size_t i, j;
	for (i=2; i<limit; i++)
	{
		if (!is_composite[i])
		{
			for (j=i; i*j<limit; j++)
				is_composite[i*j]=1;
			pa.len++;
		}
	}
	pa.primes = calloc(pa.len, pa.member_size);
	
	j = 0;
	for (i=2; i<limit; i++)
	{
		if (!is_composite[i]) pa.primes[j++] = i;
	}
	assert(j == pa.len);
#ifdef pause
	printf("Hit enter to free %lld bytes\n", limit);
	char nada[2];
	fgets(nada, 2, stdin);
#endif
	free(is_composite);
	return pa;
}


int main(void)
{
#ifdef pause
	printf("Hit enter to sieve up to %lld\n", LIMIT);
	char nada[2];
	fgets(nada, 2, stdin);
#endif
	prime_array pa = get_primes(LIMIT);
	printf("%ld primes exist up to %lld\n", pa.len, LIMIT);
#ifdef pause
	printf("Hit enter to quit\n");
	fgets(nada, 2, stdin);
#endif
	return 0;
}
