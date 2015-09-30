#!/usr/bin/env python3
from collections  import defaultdict

#
def Tree(): return defaultdict(Tree)
#
def add(tree, path, leaf_value=None):
	fn = path.pop(-1)
	for node in path:
		tree = tree[node]
	if fn:
		tree[fn] = leaf_value
#
def flatten(tree, joiner='{}/{}'.format):
	for k, v in tree.items():
		if v and isinstance(v, dict):
			if joiner:
				for sv in flatten(v):
					yield joiner(k, sv)
			else:
				yield from flatten(v, joiner=joiner)
		else:
			yield k
#
