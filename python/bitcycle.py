#! /usr/bin/env python3
from bitrev import *

class LimitExceeded(Exception):
	pass

def get_images(seed, images=None, limit=1E6):
	thisimage = [ x for x in seed ]
	assert thisimage
	images = images or []
	for r in range(int(limit)):
		if thisimage in images:
			return images
		else:
			images.append(thisimage)
			thisimage = [ thisimage[x] for x in thisimage ]
			if not thisimage:
				return images
	else:
		raise LimitExceeded("Stopped at {}".format(r))

print(219, 19323)
for lp in range(220,256):
	images = get_images(get_bit_reversal(lp))
	print(lp, len(images))
