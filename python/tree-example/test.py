#!/usr/bin/env python3
import os, os.path
from pprint import pprint
import sys

from Tree import *

args = sys.argv[1:]

paths = sorted(line.rstrip() for line in (open(args[0]) if args else sys.stdin))

print(len(paths), "lines read:")

spaths = [ p.split(os.path.sep) for p in paths ]

# for extra credit, fatten up the example and notice how the storage size
# changes
#import itertools
#spaths = [ [c]+line for line in spaths for c in '0123456789ABCDEF' ]

print(spaths)
print()

tree = Tree()
[ add(tree, i) for i in spaths if any(i) ]

print(len(tree), "-branch tree created:")
pprint(tree)
print()

rows = list(flatten(tree))
print("Does the flattened tree match the input?:", set(rows) == set(paths))

print("Input with {} lines takes {} bytes".format(len(paths), sys.getsizeof(paths)) )
print("Example with {} leaves takes {} bytes".format(len(spaths), sys.getsizeof(spaths)) )
print("Tree takes {} bytes".format(sys.getsizeof(tree)) )
print("Flattened, it takes {} bytes".format(sys.getsizeof(rows)) )
