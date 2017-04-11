
#include <assert.h>
#include <dlfcn.h>
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>

#include "plugin.h"

#define FATAL(...) { fprintf(stderr, __VA_ARGS__); exit(10); }

struct plugin_loader_s *loader;

int
register_function(struct register_function_s f) {
  if (255 <= loader->nfunctions) return 1;
  loader->functions[loader->nfunctions++] = f;
  return 0;
}

int
load_plugin(const char *filename) {
  assert (loader != NULL);
  if (loader == NULL) {
    loader = malloc(sizeof(struct plugin_loader_s));
    *loader = (struct plugin_loader_s) {
      .version = "1.0.1"
    };
  }
  void *lib_handle = dlopen(filename, RTLD_LAZY);
  if (lib_handle == NULL) FATAL("%s failed to load: %s\n", filename, dlerror());
  register_plugin_callback_t reg = dlsym(lib_handle, "register_plugin");
  if (reg == NULL) FATAL("%s failed to load: %s\n", "register_plugin", dlerror());
  return reg(lib_handle, register_function, loader);
}

int
main(int argc, char **argv) {
  if (loader == NULL) {
    loader = malloc(sizeof(struct plugin_loader_s));
    *loader = (struct plugin_loader_s) {
      .version = "1.0.1"
    };
  }
  printf("%d plugins\n", loader->nfunctions);
  load_plugin("./stub.so");
  double (*f)(unsigned) = loader->functions[0].unsigned_to_double_function;
  printf("addone(1) = %f\n", f(1));
  printf("%d plugins\n", loader->nfunctions);
}
