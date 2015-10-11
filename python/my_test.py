import curses
from curses.textpad import *
from curses_context import curses_wrapper

with curses_wrapper() as stdscr:
	lines, cols = stdscr.getmaxyx()
	curses.init_pair(1, curses.COLOR_RED, curses.COLOR_WHITE)
	curses.init_pair(2, curses.COLOR_WHITE, curses.COLOR_BLACK)
	stdscr.border(curses.color_pair(1))
	stdscr.addstr(1, 1, "{}x{}".format(*stdscr.getmaxyx())

