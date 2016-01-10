#! /usr/bin/env python3
import numpy as np

big_permutations = { 'bit-reversal': np.array([0, 1], dtype=np.uint) }

def get_bit_reversal(mylen, lookup=big_permutations):
	cur = lookup['bit-reversal']
	while len(cur) < mylen:
		dlen = 2*len(cur)
		n = (cur<<1)
		s = (n+1)
		cur = np.hstack((n, s)) % dlen
	lookup['bit-reversal'] = cur
	return np.extract( (cur<mylen), cur)
#
