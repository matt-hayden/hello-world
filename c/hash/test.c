#define _GNU_SOURCE

#include <ctype.h>
#include <malloc.h>
#include <stdio.h>
#include <string.h>

#include "djb2_hash.c"


void
hash_lines(FILE *fp) {
  static size_t len = 0;
  ssize_t nbytes;
  static char *buffer = NULL;
  while ( (nbytes = getline(&buffer, &len, fp)) ) {
    if (nbytes == -1) break;
    char *line = buffer;
    if (0 < nbytes) {
      while (isspace(line[nbytes-1])) nbytes--;
      line[nbytes] = '\0';
      while (isspace(line[0])) line++;
    }
    printf("%16lx\t=%s=\n", djbh_text_hash(line), line);
  }
  if (buffer != NULL) free(buffer);
}   


int
main(int argc, char **argv) {
  if (argc == 1)
    hash_lines(stdin);
  else {
    for (unsigned i = 1; i < argc; i++) {
      FILE *fn = fopen(argv[i], "r");
      hash_lines(fn);
    }
  }
}

