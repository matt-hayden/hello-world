
#include <string.h>

#include "str.h"

int
main(int argc, char * argv[])
{
	size_t place, counter;
	char * line, * scratch = NULL;
	for (int file_no = 1; file_no < argc; file_no++) {
		counter = 0;
		place = 0;
		printf("\n");
		file_and_error * f_e;
		f_e = string_from_file(argv[file_no]);
		printf("%s:\n", argv[file_no]);

		if (f_e->error) {
			printf("GError: %p\n", f_e->error);
			continue;
		}

		place = f_e->len;
		//line = strtok_s(f_e->contents, &place, "\n", &scratch);
		line = strtok_r(f_e->contents, "\n", &scratch);
		//printf("%lu: %s\n", counter++, line);
		while(line) {
			printf("%lu: %s\n", counter++, line);
			line = strtok_r(NULL, "\n", &scratch);
			//line = strtok_s(NULL, &place, "\n", &scratch);
		}
		g_free(f_e->contents);
		g_free(f_e->error);
		free(f_e);
	}
}
