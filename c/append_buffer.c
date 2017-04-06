
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

#include "macro_tricks.h"

struct abuf_s {
  int len;
  char *b;
  void (*append)(struct abuf_s*, const char*, unsigned);
  void (*free)(struct abuf_s*);
};


void abAppend(struct abuf_s *ab, const char *s, unsigned len) {
  char *new = realloc(ab->b, ab->len + len);

  if (new == NULL) {
    perror("Out of memory at " __FILE__ ":" S__LINE__);
    //ab->free(ab);
    exit(10);
  }
  memcpy(&new[ab->len], s, len);
  ab->b = new;
  ab->len += len;
}

char*
abTrim(struct abuf_s *ab) {
  char *new = realloc(ab->b, ab->len+1);
  if (new == NULL) {
    perror("Out of memory");
    //ab->free(ab);
    exit(10);
  }
  new[ab->len+1] = '\0';
  return (ab->b = new);
}

void abFree(struct abuf_s *ab) {
  free(ab->b);
}

struct abuf_s*
abNew(void) {
  struct abuf_s *ab = malloc(sizeof(struct abuf_s));
  *ab = (struct abuf_s) { .free=abFree, .append=abAppend };
  return ab;
}

