#!/bin/bash
: ${CC="gcc -std=gnu11"} ${CFLAGS="-g -Wall -include all.h"}
set -e

if ${CC} -xc -
then
	gdb ./a.out
fi
