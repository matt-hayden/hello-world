#! /usr/bin/env python3

import logging

from logging import debug, info, warning, error, critical

def main(*args):
	logging.basicConfig(filename='log',level=logging.DEBUG if __debug__ else logging.WARNING)
	debug('This message should go to the log file')
	info('So should this')
	warning('And this, too')
if __name__ == '__main__':
	import sys
	main(sys.argv[1:])