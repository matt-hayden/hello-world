#include <fcntl.h>
#include <stdio.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <unistd.h>

#include "dbg.h"

int
mmap_copy(int input_fd, int output_fd, size_t limit)
{
	debug("Using fd %d", input_fd);
	void *imf;
	check((imf = mmap(NULL, limit, PROT_READ, MAP_SHARED, input_fd, 0)) != (caddr_t) -1, "mmap failed");

	debug("Using fd %d", output_fd);
	ftruncate(output_fd, limit);
	void *omf;
	check((omf = mmap(NULL, limit, PROT_WRITE, MAP_SHARED, output_fd, 0)) != (caddr_t) -1, "mmap failed");

	void *dest;
	dest = memcpy(omf, imf, limit);
	debug("memcpy: %p -> %p -> %p", imf, omf, dest);
cleanup:
	munmap(imf, limit);
	munmap(omf, limit);
	return 0;
error:
	munmap(imf, limit);
	munmap(omf, limit);
	return -1;
}

int
main(int argc, char *argv[])
{
	FILE *input, *output;
	check((input = fopen(argv[1], "rb")), "Failed to open %s", argv[1]);
	check((output = fopen(argv[2], "w+b")), "Failed to open %s", argv[2]);
	mmap_copy(fileno(input), fileno(output), 16);
cleanup:
	fclose(input);
	fclose(output);
	return 0;
error:
	fclose(input);
	fclose(output);
	return -1;
}
