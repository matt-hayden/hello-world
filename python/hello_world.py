#!/usr/bin/env python3

import ctypes

libc = ctypes.CDLL(None)
NULL = None

def hello_world(message="Hello World"):
	assert 0 < libc.puts(message.encode('UTF-8'))
hello_world()
