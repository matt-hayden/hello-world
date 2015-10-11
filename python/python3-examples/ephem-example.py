#! /usr/bin/env python3
"""Example of program with many options using docopt.

Usage:
  options_example.py [-hvqrf NAME] [--exclude=PATTERNS]
                     [--select=ERRORS | --ignore=ERRORS] [--show-source]
                     [--statistics] [--count] [--benchmark] PATH...
  options_example.py (--doctest | --testsuite=DIR)
  options_example.py --version

Arguments:
  PATH  destination path

Options:
  -h --help            show this help message and exit
  --version            show version and exit
  -v --verbose         print status messages
  -q --quiet           report only file names
  -r --repeat          show all occurrences of the same error
  --exclude=PATTERNS   exclude files or directories which match these comma
                       separated patterns [default: .svn,CVS,.bzr,.hg,.git]
  -f NAME --file=NAME  when parsing directories, only check filenames matching
                       these comma separated patterns [default: *.py]
  --select=ERRORS      select errors and warnings (e.g. E,W6)
  --ignore=ERRORS      skip errors and warnings (e.g. E4,W)
  --show-source        show source code for each error
  --statistics         count errors and warnings
  --count              print total number of errors and warnings to standard
                       error and set exit code to 1 if total is not null
  --benchmark          measure processing speed
  --testsuite=DIR      run regression tests from dir
  --doctest            run doctest on myself

"""

import logging

from logging import debug, info, warning, error, critical

import ephem
import pytz

utcnow = pytz.UTC.localize(datetime.utcnow())
 
degrees_per_radian = 180.0 / math.pi

home = ephem.Observer()
home.lat, home.lon = '40', '-104.5'	# +N, +E
home.elevation = 1700	# meters

def main(args):
	logging.basicConfig(filename='log',level=logging.DEBUG if __debug__ else logging.WARNING)
	for i, (arg, value) in enumerate(args.items()):
		debug("Arg {}: {} = {}".format(i, arg, value))

if __name__ == '__main__':
	from sys import argv, exit, stdin, stdout, stderr
	
	#from docopt import docopt
	
	args = {} # docopt(__doc__, version='Naval Fate 2.0')
	main(args)