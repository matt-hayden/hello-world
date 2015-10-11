import curses
from curses.textpad import Textbox, rectangle

def main(stdscr): # stdscr is a Window
	curses.init_pair(1, curses.COLOR_RED, curses.COLOR_WHITE)
	curses.init_pair(2, curses.COLOR_WHITE, curses.COLOR_BLACK)
	
	lines, cols = curses.LINES, curses.COLS
	# Clear screen
	stdscr.clear()

	stdscr.addstr("{}x{}\n".format(cols, lines), curses.color_pair(1))
	stdscr.refresh()
	#pad = curses.newpad(100, 100)
	stdscr.addstr("Hit any key to exit", curses.color_pair(2))
	stdscr.getkey()
def main(stdscr):
	lines, cols = curses.getmaxyx()
	stdscr.addstr(1, 1, "Enter IM message: (hit Ctrl-G to send)")
	stdscr.border()

	editwin = curses.newwin(5,30, 3,2)
	rectangle(stdscr, 2,1, 1+5+1, 1+30+1)
	stdscr.refresh()

	box = Textbox(editwin)

	# Let the user edit until Ctrl-G is struck.
	box.edit()

	# Get resulting contents
	message = box.gather()
curses.wrapper(main)
