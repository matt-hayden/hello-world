#include <stdint.h>

static
unsigned djbh_text_hash(char const *str) {
  register unsigned hash = 5381L;
  char c;
  while ((c = *str++)) hash += (hash<<5) + c;
  return hash;
}

static
unsigned djbh_list_hash(void const **in) {
  register unsigned hash = 5381L;
  void *c;
  while ((c = *in++)) hash += (hash<<5) + (uintptr_t)c;
  return hash;
}
