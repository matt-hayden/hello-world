CC = gcc
CFLAGS = -Wall --std=gnu99 -fpic -g

all: fact_hose take

libfact.a: fact.o
	ar rcs $@ $^

%.c: %.h

%.o: %.c
	$(CC) $(CFLAGS) -c $^ -o $@

libfact.so.1.0.1: fact.o
	$(CC) -shared -Wl,-soname,libfact.so.1 -o $@ $^ -lm

libfact.so.1: libfact.so.1.0.1
	[ -e $@ ] || ln -s $^ $@

fact_hose: fact_test.o libfact.a
	$(CC) -o $@ -static $^ -L. -lfact -lm
# shared:
#	$(CC) -o $@ $^ -L. -lfact -lm

take: take.o libfact.a
	$(CC) -o $@ -static $^ -L. -lfact -lm
