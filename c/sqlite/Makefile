
CC = gcc
CFLAGS ?= $(shell pkg-config --cflags sqlite3) -O0 -g
LDLIBS ?= $(shell pkg-config --libs sqlite3)

%: %.c
	#gcc -o $@ -Wall $^ -ldl -lpthread -lsqlite3
	$(CC) $(CFLAGS) -o $@ -Wall $^ $(LDLIBS)
