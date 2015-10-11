from datetime import timedelta
import ephem

t=ephem.localtime # time formatter

home = ephem.Observer()
home.lat, home.lon = '40', '-104.5'	# +N, +E
home.elevation = 1700	# meters

observ=home

sun = ephem.Sun()
sun.compute(observ)

def timedelta_from_ephem(days):
	return timedelta(days=days)

daily_diff = observ.next_rising(sun) - observ.previous_rising(sun) - 1
daily_diff = timedelta_from_ephem(observ.next_rising(sun) - observ.previous_rising(sun) - 1)
print t(observ.next_rising(sun))
print t(observ.previous_rising(sun))
print daily_diff
