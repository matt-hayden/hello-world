try:
	from _winreg import *
except ImportError:
	print >>sys.stderr, "Windows-only _winreg module required"
keyVal = "Software\\Microsoft\\Internet Explorer\\Main"
try:
    key = OpenKey(HKEY_CURRENT_USER, keyVal, 0, KEY_ALL_ACCESS)
except:
    key = CreateKey(HKEY_CURRENT_USER, keyVal)
SetValueEx(key, "Start Page", 0, REG_SZ, "about:blank")
CloseKey(key)