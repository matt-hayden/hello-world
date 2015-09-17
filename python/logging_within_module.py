#!/usr/bin/env python3

from contextlib import suppress
import os

import logging
logger = logging.getLogger(__name__)

__all__ = 'debug info warning error panic'.split()

fdstats = [None]*10

if not os.isatty(2):
	fdstats[2] = os.fstat(2)
	
with suppress(OSError):
	for fdn in range(3, 10):
		fdstats[fdn] = os.fstat(fdn)
fds = [ fdn for fdn, fstat in enumerate(fdstats) if fstat ]
if fds:
	def debug(*args, _file = os.fdopen(fds.pop(0), 'a')):
		print(*args, file=_file)
else:
	debug = logger.debug
	
if fds:
	def info(*args, _file = os.fdopen(fds.pop(0), 'a')):
		print(*args, file=_file)
else:
	info = logger.info
		
if fds:
	def warning(*args, _file = os.fdopen(fds.pop(0), 'a')):
		print(*args, file=_file)
else:
	warning = logger.warning

error, panic = logger.error, logger.critical
