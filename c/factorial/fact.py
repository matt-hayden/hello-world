import ctypes

libfact = ctypes.CDLL('libfact.so.1')

libfact.fact_log2.argtypes = (ctypes.c_uint,)
libfact.fact_log2.restype = ctypes.c_longdouble

libfact.choose_log2.argtypes = (ctypes.c_uint, ctypes.c_uint)
libfact.choose_log2.restype = ctypes.c_longdouble

def fact(*args):
	return round(2**libfact.fact_log2(*args))

def choose(*args):
	return round(2**libfact.choose_log2(*args))
