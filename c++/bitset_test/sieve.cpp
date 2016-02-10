#include <bitset>
#include <vector>

#include <iostream>

#define LIMIT 10000000LL

typedef
unsigned long long  sieve_size_t;

std::vector<unsigned long long>
get_primes(sieve_size_t limit)
{
	std::bitset<LIMIT> is_composite;
	std::vector<unsigned long long> pa;

	sieve_size_t i, j;

	for (i=2; i<limit; i++)
	{
		if (!is_composite[i])
		{
			for (j=i; i*j<limit; j++)
				is_composite[i*j]=1;
		}
	}
	
	j = 0;
	for (i=2; i<limit; i++)
	{
		if (!is_composite[i]) pa.push_back(i);
	}
	return pa;
}


int main(void)
{
	std::vector<unsigned long long> pa = get_primes(LIMIT);
	std::cout << pa.size() << " primes exist up to " << LIMIT << std::endl;
	return 0;
}
