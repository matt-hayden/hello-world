CC = gcc
CFLAGS = -Wall --std=gnu99 -fpic

all: libfact.so.1

fact_test.c: fact.c

libfact.a: fact.o
	ar rcs $@ $^

%.c: %.h

%.o: %.c
	$(CC) $(CFLAGS) -c $^ -o $@

libfact.so.1.0.1: fact.o
	$(CC) -shared -Wl,-soname,libfact.so.1 -o $@ $^ -lm

libfact.so.1: libfact.so.1.0.1
	[ -e $@ ] || ln -s $^ $@

fact_test.static: fact_test.c libfact.a
	$(CC) -o $@ -static $^ -L. -lfact -lm

fact_test.shared: fact_test.c libfact.so.1
	$(CC) -o $@ $^ -L. -lfact -lm
