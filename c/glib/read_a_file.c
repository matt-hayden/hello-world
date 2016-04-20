
#include "str.h"

int
main(int argc, char * argv[])
{
	for (int i = 1; i < argc; i++) {
		printf("\n");
		file_and_error * f_e;
		f_e = string_from_file(argv[i]);
		if (f_e->error) printf("GError: %p\n", f_e->error);
		printf("contents: %s\n", f_e->contents);
		g_free(f_e->contents);
		free(f_e);
	}
}
