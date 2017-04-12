CC ?= gcc
CFLAGS ?= -Wall -g
LDFLAGS ?= -ldl

all: example_plugin.so plugin_info.so loader_test
	cp example_plugin.so example_plugin2.so

clean:
	-rm -f a.out *.o *.so loader_test

%.o: %.c
	$(CC) $(CFLAGS) -fpic -c $^ -o $@

%.so: %.o
	$(CC) $(CFLAGS) -shared -Wl,-soname,$@ -o $@ $^

loader_test: loader_test.o loader.o
	$(CC) $^ -o $@ $(LDFLAGS)
