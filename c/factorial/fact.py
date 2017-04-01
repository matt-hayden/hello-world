import ctypes

libfact = ctypes.CDLL('libfact.so.1')
libfact.fact.argtypes = (ctypes.c_size_t,)
libfact.fact.restype = ctypes.c_longdouble

fact = libfact.fact
