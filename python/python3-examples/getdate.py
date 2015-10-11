#! /usr/bin/env python3
"""
Demonstration of parsedatetime.
"""
import parsedatetime
import time

cal = parsedatetime.Calendar()

import sys

full_arg = " ".join(sys.argv[1:])
timestamp, return_type = cal.parse(full_arg)
### return_type is an annoying code:
# 0 = not parsed at all
# 1 = parsed as a C{date}
# 2 = parsed as a C{time}
# 3 = parsed as a C{datetime}
assert return_type

print("{} is {}".format(full_arg, time.strftime('%Y-%m-%d %H:%M', timestamp)))