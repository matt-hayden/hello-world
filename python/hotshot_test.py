import hotshot, hotshot.stats

from local.units import byte_units

def runner(exp=2, max=1000000, method=1):
	assume_big = (method == 2)
	for x in xrange(0, max):
#		byte_units(x**exp, assume_big=assume_big)
		byte_units(x, assume_big=assume_big)

for method in [1,2]:
	prof = hotshot.Profile("byte_units.prof")
	prof.runcall(runner, **{'method':method})
	prof.close()
	stats = hotshot.stats.load("byte_units.prof")
	stats.strip_dirs()
	stats.sort_stats('time', 'calls')
	print
	print "Method", method
	stats.print_stats(20)
