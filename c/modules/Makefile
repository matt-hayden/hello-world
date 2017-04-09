CC ?= gcc
CFLAGS = -Wall -g

%.o: %.c
	$(CC) $(CFLAGS) -c $^ -o $@

%.so: %.c
	$(CC) $(CFLAGS) -fpic -shared -Wl,-soname,$@ -o $@ $^

manager_test: manager_test.o manager.o
	$(CC) $^ -o $@ -ldl
