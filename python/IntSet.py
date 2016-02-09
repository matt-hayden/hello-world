#! /usr/bin/env python3
from array import array

class IntSet:
	def __init__(self, size, initial=None):
		self.initial = ((1<<64)-1) if initial else 0
		self.size = None
		if size:
			self.resize(int(size))
	def resize(self, new_size):
		size = self.size or 0
		if size == 0:
			self.parts = array('L', [self.initial]*(new_size>>6))
			self.size = new_size
		elif size < new_size:
			tail = array('L', [self.initial]*((new_size-size)>>6))
			self.parts += tail
			self.size = new_size
		elif new_size < size:
			self.parts = self.parts[:(new_size>>6)]
			self.size = new_size
	def __getitem__(self, index):
		assert index < self.size
		a = (index & 63)
		b = index >> 6
		return self.parts[b] & (1<<a)
	def __contains__(self, index):
		return (0 < self[index])
	def __setitem__(self, index, value):
		assert index < self.size
		a = (index & 63)
		b = index >> 6
		if value:
			self.parts[b] |= (1<<a)
		else:
			self.parts[b] &= ~(1<<a)
	def __invert__(self):
		x = 0
		for q in self.parts:
			nq = ~q
			for i in range(64):
				if nq & (1<<i):
					yield x+i
			x += 64
	def __iter__(self):
		x = 0
		for q in self.parts:
			for i in range(64):
				if q & (1<<i):
					yield x+i
			x += 64
	@property
	def maxsize(self):
		return len(self.parts)*63
###
if __name__ == '__main__':
	lookup = IntSet(1E6, 0)
# vim: tabstop=4 shiftwidth=4 softtabstop=4 number :
