#include <stdio.h>
#include <stdlib.h>

#include <assert.h>

#define LIMIT 10000000LL

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

	int *lookup; /* an array of 0 for non-prime and 1 for prime */
	lookup = malloc(sizeof(int)*limit);

	sieve_size_t i, j;
	// clear
	for (i=2; i<limit; i++)
		lookup[i]=1;

	for (i=2; i<limit; i++)
	{
		if (lookup[i])
		{
			for (j=i; i*j<limit; j++)
				lookup[i*j]=0;
			pa.len++;
		}
	}
	pa.primes = malloc(pa.len*pa.member_size);
	
	j = 0;
	for (i=2; i<limit; i++)
	{
		if (lookup[i]) pa.primes[j++] = i;
	}
	assert(j == pa.len);
	free(lookup);
	return pa;
}


int main(void)
{
	prime_array pa = get_primes(LIMIT);
	printf("%ld primes exist up to %lld\n", pa.len, LIMIT);
	return 0;
}
