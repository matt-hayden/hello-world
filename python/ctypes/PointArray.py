from ctypes import CDLL, c_int, Structure


class Point(Structure):
	_fields_ = [("x", c_int), 
				("y", c_int)]
	def __lt__(self, other):
		assert isinstance(other, Point)
		#return (self.x, self.y) < (other.x, other.y)
		return self.L2() < other.L2()
	def __repr__(self):
		return "(%d, %d)" % (self.x, self.y)
	def L2(self):
		return self.x**2 + self.y**2
	
class PointArray:
	mlen = 10
	inner_type = Point
	initializer = inner_type * mlen # Struct concatenation
	def __length_hint__(self):
		return self.mlen
	def __len__(self):
		return len(self.ctype)
	def __init__(self, init=[], **kwargs):
		if hasattr(init, '__call__'):
			#self.from_iterable( map(init, range(self.mlen)) )
			self.from_iterable( init(i, **kwargs) for i in range(self.mlen) )
		else:
			self.from_iterable(init)
	def __iter__(self):
		return iter(self.ctype)
	def __repr__(self):
		return "<%r %s>" % (self.__class__, list(self))
	def from_iterable(self, iterable):
		self.ctype = self.initializer(*iterable)
	def __getitem__(self, key):
		return self.ctype[key]
	def __setitem__(self, key, value):
		self.ctype[key] = value
