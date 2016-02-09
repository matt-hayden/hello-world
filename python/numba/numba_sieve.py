#! /usr/bin/env python3
import numpy as np
import numba

@numba.jit
def make_sieve(maxsize=1E7):
	prime_lookup = np.ones(int(maxsize), dtype=np.dtype('uint8'))
	for i in range(2, maxsize):
		if prime_lookup[i]:
			prime_lookup[i<<1::i] = 0
	#return [ i for i, b in enumerate(prime_lookup) if b ] # numba fails
	#del prime_lookup[0] # numba fails 
	return prime_lookup

PRIMES = [ i for i, b in enumerate(make_sieve()) if b ]
PRIMES.pop(0) # remove 0
print(len(PRIMES), "primes between", PRIMES[:5], "and", PRIMES[-3:])

# vim: tabstop=4 shiftwidth=4 softtabstop=4 number :
