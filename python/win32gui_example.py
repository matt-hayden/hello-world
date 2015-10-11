import win32con, win32gui

def WindowsByClass(ignored_titles=['Default IME'],
				   ignored_classes=['ComboLBox', 'GRAPHBALLOON','MSCTFIME UI', 'tooltips_class32']):
	toplist = []
	winlist = []
	def enum_callback(hwnd, results):
		title = win32gui.GetWindowText(hwnd)
		wclass = win32gui.GetClassName(hwnd)
		if title not in ignored_titles and wclass not in ignored_classes:
			winlist.append((hwnd, title, wclass))
	#
	win32gui.EnumWindows(enum_callback, toplist)
	return winlist
#
if __name__=='__main__':
	#for handle, title, wclass in WindowsByClass():
	#	print handle, '\t', title, '\t', wclass
	itunesHandles = [ handle for handle, title, wclass in WindowsByClass() if wclass == 'iTunesApp' ]
	if itunesHandles:
		win32gui.SetForegroundWindow(itunesHandles[0])
		#win32gui.ShowWindow(itunesHandles[0], win32con.SW_MAXIMIZE)
		#print itunesHandles