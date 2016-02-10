#include <bitset>
#include <vector>

#include <iostream>

#define LIMIT 100000000ULL

typedef
unsigned long long  sieve_size_t;

std::vector<unsigned long long> *
get_primes(sieve_size_t limit)
{
	std::bitset<LIMIT>		*	p_is_composite;
	std::vector<unsigned long long>	*	p_pa;
	p_is_composite			=	new std::bitset<LIMIT>; // avoid the heap
	p_pa				=	new std::vector<unsigned long long>;

	sieve_size_t i, j;
	for (i=2; i<limit; i++)
	{
		if (! (*p_is_composite)[i])
		{
			for (j=i; i*j<limit; j++)
				(*p_is_composite)[i*j]=1;
		}
	}
	
	for (i=2; i<limit; i++)
	{
		if (! (*p_is_composite)[i]) (*p_pa).push_back(i);
	}
#ifdef pause
	std::cout << "Hit enter to delete p_is_composite" << std::endl;
	std::cin.ignore();
#endif
	//delete[] p_is_composite; // segfaults
	delete p_is_composite;
	p_is_composite = NULL;
	return p_pa;
}


int main(void)
{
#ifdef pause
	std::cout << "Hit enter to generate " << LIMIT << " primes" << std::endl;
	std::cin.ignore();
#endif
	std::vector<unsigned long long> * p_pa = get_primes(LIMIT);
	std::cout << (*p_pa).size() << " primes exist up to " << LIMIT << std::endl;
#ifdef pause
	std::cout << "Hit enter to quit" << std::endl;
	std::cin.ignore();
#endif
	return 0;
}
