#!/usr/bin/env python3
from contextlib import contextmanager, suppress

from curses import *

"""
This is a very small modification of wrapper that uses with-context.

Original comment:
Wrapper for the entire based application.  Runs a function which should be the rest of your based application.  If the application raises an exception, wrapper() will restore the terminal to a sane state so you can read the resulting traceback.
"""

@contextmanager
def curses_window():
	"""Original comment:
	Wrapper function that initializes and calls another function, restoring normal keyboard/screen behavior on error.  The callable object 'func' is then passed the main window 'stdscr' as its first argument, followed by any other arguments passed to wrapper().
	"""

	# Initialize curses
	stdscr = initscr()

	# Turn off echoing of keys, and enter cbreak mode, where no buffering is performed on keyboard input
	noecho()
	cbreak()

	# In keypad mode, escape sequences for special keys (like the cursor keys) will be interpreted and a special value like KEY_LEFT will be returned
	stdscr.keypad(1)

	 # Start color, too.  Harmless if the terminal doesn't have  color; user can test with has_color() later on.  The try/catch  works around a minor bit of over-conscientiousness in the  module -- the error return from C start_color() is ignorable.
	with suppress(Exception):
		start_color()

	try:
		yield stdscr # pivotal point in the context manager
	except Exception as e:
		raiseme = e
	finally:
		# Set everything back to normal
		if 'stdscr' in locals():
			stdscr.keypad(0)
			echo()
			nocbreak()
			endwin()
	if 'raiseme' in locals():
		raise raiseme
#

if __name__ == '__main__':
	with curses_window() as stdscr:
		lines, cols = stdscr.getmaxyx()
		init_pair(1,	COLOR_WHITE,	COLOR_RED)
		init_pair(2,	COLOR_GREEN,	COLOR_BLACK)
		init_pair(7,	COLOR_WHITE,	COLOR_BLUE)
		stdscr.border(*(color_pair(7),)*8)
		stdscr.addstr(lines//2, 1, "This window is {}x{}".format(lines, cols).center(cols-2), color_pair(1))
		stdscr.addstr(lines-1, 1, "Press the any key to exit".center(cols-2), color_pair(7))
		stdscr.getkey()
