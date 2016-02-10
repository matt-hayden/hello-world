#! /usr/bin/env python3
"""Comparison of methods for a simplified prime sieve

The vanilla method builts a ndarray of primes less than maxsize

The numba-accelerated methos builds the same, 
"""
import numpy as np
import numba

from timeme import timeme

maxsize = int(1E7)

def make_sieve(maxsize):
	maxsize = int(maxsize)
	prime_lookup = [1]*(maxsize)
	for i in range(2, (maxsize+1)>>1):
		if prime_lookup[i]:
			prime_lookup[i<<1::i] = [False]*((maxsize-1)//i - 1)
	for n, p in enumerate(prime_lookup):
		if p:
			yield n

with timeme() as t:
	s0 = list(make_sieve(maxsize))
	t0 = t.stop()
print(t0, "in Python")
print(len(s0), "primes between", s0[:5], "and", s0[-3:])

def make_sieve_numpy(maxsize):
	maxsize = int(maxsize)
	prime_lookup = np.ones(maxsize, dtype=np.dtype('uint8'))
	for i in range(2, (maxsize+1)>>1):
		if prime_lookup[i]:
			prime_lookup[i<<1::i] = 0
	return np.nonzero(prime_lookup)[0]

with timeme() as t:
	s1 = make_sieve_numpy(maxsize)
	t1 = t.stop()
print(t1, "with numba but not numba")
print(len(s1), "primes between", s1[:5], "and", s1[-3:])

@numba.jit
def make_sieve_numba(maxsize):
	"""Same as make_sieve_numpy
	"""
	maxsize = int(maxsize)
	prime_lookup = np.ones(maxsize, dtype=np.dtype('uint8'))
	for i in range(2, (maxsize+1)>>1):
		if prime_lookup[i]:
			prime_lookup[i<<1::i] = 0
	#return [ i for i, b in enumerate(prime_lookup) if b ] # numba fails
	#del prime_lookup[0] # numba fails 
	return np.nonzero(prime_lookup)[0]

with timeme() as t:
	s2 = make_sieve_numba(maxsize)
	t2 = t.stop()
print(t2, "with numba")
print(len(s2), "primes between", s2[:5], "and", s2[-3:])

assert (s1 == s2).all()

print()
print("Difference:")
print((t2-t1).total_seconds(), "seconds")
print("{:.0%}".format( (t2-t1)/t1 ))


# vim: tabstop=4 shiftwidth=4 softtabstop=4 number :
