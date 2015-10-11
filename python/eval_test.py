#!env python
import ast

def python_statement(text, lambda_args='_'):
	"""
	NOT SAFE
	Given a (probably user-specified string) return the python code. Several
	attempts are made to turn strings into executable statements.
	
	>>> python_statement('1+1')
	2
	
	>>> python_statement('import os')
	'import os'
	
	Yikes:
	>>> python_statement("__import__('os').system('echo calc.exe')")
	0
	"""
	try:
		lresult = ast.literal_eval(text)
		if not isinstance(lresult, basestring): return lresult
	except: lresult = text
	# Try to limit some craziness:
	env = {}
	env['locals'] =  env['globals'] = env['__name__'] = env['__file__'] = None
#	env['__builtins__'] = None
	#
	try:
		result = eval(lresult, env)
		if not isinstance(result, basestring): return result
	except: result=lresult
	try:
		return eval('lambda '+lambda_args+':'+result)
	except: return result
#
if __name__=='__main__':
	import sys
	args = sys.argv[1:]
	if args:
		for arg in args:
			result = python_statement(arg)
			print arg, '->', type(result), result
	else:
		import doctest
		print 'Running unit test:'
		doctest.testmod()