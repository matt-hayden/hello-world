CC ?= gcc
CFLAGS = -Wall -g

%.o: %.c
	$(CC) $(CFLAGS) -fpic -c $^ -o $@

%.so: %.o
	$(CC) $(CFLAGS) -shared -Wl,-soname,$@ -o $@ $^

loader: loader.o
	$(CC) $(CFLAGS) $^ -o $@ -ldl
