#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>

#include <obstack.h>
#define obstack_chunk_alloc xmalloc
#define obstack_chunk_free free



void
stack_alloc_failed (void) {
  fprintf(stderr, "virtual memory error");
  exit(10);
}

void *
xmalloc (size_t size)
{
  void *value = malloc (size);
  if (value == 0) stack_alloc_failed();
  return value;
}


main(int argc, char **argv) {
  struct obstack *stack = (struct obstack *) xmalloc (sizeof (struct obstack));
  #define myalloc(...) obstack_alloc(stack, __VA_ARGS__)
  obstack_alloc_failed_handler = &stack_alloc_failed;
  obstack_init (stack);
  /*
   * obstack_copy imitates this:
  char *i_am_a_string = (char *) myalloc(254+1);
  memcpy(i_am_a_string, "I am a string!", 254);
   */
  char *z = obstack_copy(stack, "I am a string!", 254);
  double *d = (double *) myalloc(sizeof(double));
  *d = 1234567890.1234567890;
  size_t *s = (size_t *) myalloc(sizeof(size_t));
  *s = 1234567890;
  int **a = (int **) myalloc(sizeof(int) * 1024);
  memset(a, 0, 1024);

  memcpy(z, "I am still a string!", 254);
  obstack_free(stack, a);
  //obstack_free(stack, NULL);
  #undef myalloc
  free(stack);
}
