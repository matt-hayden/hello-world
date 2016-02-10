#! /usr/bin/env python3
from datetime import timedelta
import time

class timeme:
	def __init__(self, arg=None):
		self.start(arg)
		self.ends = None
	def __enter__(self):
		return self
	def __exit__(self, exc_type, exc_value, traceback):
		self.stop()
		return # return True suppresses exceptions
	def start(self, arg=None):
		self.begins = arg or time.time()
	def stop(self, arg=None):
		self.ends = arg or time.time()
		return self.get_timedelta()
	def get_timedelta(self):
		stop = self.ends or time.time()
		return timedelta(seconds=stop-self.begins)

# vim: tabstop=4 shiftwidth=4 softtabstop=4 number :
