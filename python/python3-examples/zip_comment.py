#! /usr/bin/env python3
"""
Demonstration of Python 3 byte and string representations, as well as ZipFile and datetime.

This script adds a line to the often-ignored comments section of a zip file. Note that .DOCX and .ODT formats are valid zip files, even though the comments section may not persist between resaves.

unzip -z prints the comment
"""
from datetime import datetime
from zipfile import ZipFile

ENCODING = 'UTF-8'
MAX_LEN = (1<<16) - 1 # 65535

import sys
args = sys.argv[1:]

now = datetime.now()
for arg in args:
	with ZipFile(arg, 'a') as zfi:
		orig_comment = zfi.comment
		if MAX_LEN:
			assert len(orig_comment) <= MAX_LEN
		lines = orig_comment.decode(ENCODING).splitlines()
		print("Original comment: ({} lines)".format(len(lines)))
		for line in lines:
			print(line)
		zfi.comment += '\n\n{}: {} modified'.format(now, arg).encode(ENCODING)
		print()
		print("New comment:")
		print(zfi.comment.decode(ENCODING))