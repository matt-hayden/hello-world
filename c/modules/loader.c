
#include <assert.h>
#include <dlfcn.h>
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>

#include "plugin.h"

#define FATAL(...) { fprintf(stderr, __VA_ARGS__); exit(10); }

struct plugin_loader_s *loader;
plugin_handle latest_handle;

int
register_function(struct register_function_s f) {
  if (MAX_PLUGINS <= loader->nfunctions) return 1;
  f.lib_handle = latest_handle;
  loader->functions[loader->nfunctions++] = f;
  return 0;
}

int
load_plugin(const char *filename) {
  assert (loader != NULL);
  latest_handle = dlopen(filename, RTLD_LAZY);
  if (latest_handle == NULL) FATAL("%s failed to load: %s\n", filename, dlerror());
  register_plugin_callback_t reg = dlsym(latest_handle, "register_plugin");
  if (reg == NULL) FATAL("%s failed to load: %s\n", "register_plugin", dlerror());
  return reg(loader);
}

int
setup_loader() {
  if (loader == NULL) {
    loader = malloc(sizeof(struct plugin_loader_s));
    *loader = (struct plugin_loader_s) {
      .version = "1.0.1",
      .register_function = register_function
    };
  }
}
