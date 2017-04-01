CC = gcc
CFLAGS = -Wall --std=gnu99 -fpic

libfact.a: fact.o
	ar rcs $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $^ -o $@

libfact.so.1.0.1: fact.o
	$(CC) -shared -Wl,-soname,libfact.so.1 -o $@ $^
	[ -e libfact.so.1 ] || ln -s libfact.so.1.0.1 libfact.so.1

fact_test.static: fact_test.c libfact.a
	$(CC) -o $@ -static $^ -L. -lfact

fact_test.shared: fact_test.c libfact.so.1.0.1
	$(CC) -o $@ $^ -L. -lfact
