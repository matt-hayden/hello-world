from ctypes import CDLL, CFUNCTYPE, sizeof, POINTER, c_int

import PointArray
#
class MyPointArray(PointArray.PointArray):
	mlen = 5
	inner_type = PointArray.PointArray.inner_type
	initializer = inner_type * mlen # Struct concatenation
#
import random
def my_rand(*args):
	return random.randint(0, 100), random.randint(0, 100)
parr = MyPointArray(my_rand)


libc = CDLL(None)
qsort = libc.qsort
qsort.resttype = None


def cmp_fn(pa, pb):
	a = pa[0] # must unbox
	b = pb[0] # must unbox
	return a < b


print(parr)
qsort(parr.ctype, len(parr), sizeof(parr.inner_type), CFUNCTYPE(c_int, POINTER(parr.inner_type), POINTER(parr.inner_type))(cmp_fn))
print(parr)
