import collections
import sqlite3


class SqliteSerializable:
	def __conform__(self, protocol):
		if protocol is sqlite3.PrepareProtocol:
			return ';'.join(str(i) for i in self)
class Point(collections.namedtuple('Point', 'x y'), SqliteSerializable):
	pass

con = sqlite3.connect(":memory:")
cur = con.cursor()

p = Point(1/11., 1/10.)
cur.execute("select ?", (p,))
print(cur.fetchone()[0])
