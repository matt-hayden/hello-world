#include <malloc.h>
#include <stdio.h>

#include "loader.h"
#include "example_plugin.h"

extern struct plugin_loader_s *loader;

int
main(int argc, char **argv) {
  if (loader != NULL) printf("%d functions\n", loader->nfunctions);
  setup_loader();
  for (unsigned a = 1; a < argc; a++) load_plugin(argv[a]);
  printf("%d functions\n", loader->nfunctions);

  printf("Searching for function 'addone'... ");
  struct get_plugin_function_s g = get_plugin_function("addone");
  if (!g.status) {
    plugin_object obj = g.obj;
    printf("found in %p: %s\n", obj->lib_handle, obj->declaration);
    addone_prototype f = (addone_prototype) obj->func_ptr;
    printf("addone(1) = %f\n", f(1));
  } else {
    printf("not found\n");
  }
}


