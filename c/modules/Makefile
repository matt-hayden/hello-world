CC ?= gcc
CFLAGS ?= -Wall -g
LDFLAGS ?= -ldl

%.o: %.c
	$(CC) $(CFLAGS) -fpic -c $^ -o $@

%.so: %.o
	$(CC) $(CFLAGS) -shared -Wl,-soname,$@ -o $@ $^

loader_test: loader_test.o loader.o
	$(CC) $^ -o $@ $(LDFLAGS)

