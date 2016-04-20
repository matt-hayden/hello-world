#ifndef __str_h__
#define __str_h__

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <glib.h>

#include "dbg.h"

#define APPEND(write_to, ...) {			\
	char * scratch = write_to;		\
	asprintf(&(write_to), __VA_ARGS__);	\
	free(scratch);				\
}

#define FOREACH(iterator, ...) \
	for (char **iterator = (char * []) {__VA_ARGS__, NULL}; *iterator; iterator++)

typedef struct _s {
	char * contents;
	GError *error;
} file_and_error ;

file_and_error *
string_from_file(char const *filename) {
file_and_error * r;

	r = malloc(sizeof(file_and_error));
	r->error = NULL;
	GIOChannel *f;
	check( (f = g_io_channel_new_file(filename, "r", &(r->error)) ), "g_io_channel_new_file(%s)", filename);
	check( (g_io_channel_read_to_end(f, &(r->contents), NULL, &(r->error)) == G_IO_STATUS_NORMAL), "g_io_channel_read_to_end");
	return r;
error:
	return r;
}
#endif
