#include <stdint.h>

typedef unsigned long long hash_value;


static
hash_value djbh_text_hash(char const *str) {
  register hash_value hash = 5381LL;
  char c;
  while ((c = *str++)) hash += (hash<<5) + c;
  return hash;
}

static
hash_value djbh_list_hash(void const **in) {
  register hash_value hash = 5381LL;
  void *c;
  while ((c = *in++)) hash += (hash<<5) + (uintptr_t)c;
  return hash;
}
