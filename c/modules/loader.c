
#include <assert.h>
#include <dlfcn.h>
#include <malloc.h>
#include <string.h>

#include "loader.h"


plugin_loader loader;

static
plugin_handle latest_handle;

int
register_for_plugin(struct plugin_object_definition_s f) {
  if (MAX_PLUGINS <= loader->nfunctions) return 1;
  f.lib_handle = latest_handle;
  loader->functions[loader->nfunctions++] = f;
  return 0;
}

int
load_plugin(const char *filename) {
  assert (loader != NULL);
  latest_handle = dlopen(filename, RTLD_LAZY);
  if (latest_handle == NULL) PLUGIN_PERROR("%s failed to load: %s\n", filename, dlerror());
  register_plugin_callback_t reg = dlsym(latest_handle, "register_plugin");
  if (reg == NULL) PLUGIN_PERROR("%s failed to load: %s\n", "register_plugin", dlerror());
  return reg(loader);
}

int
_setup_loader(char const **filenames) {
  #ifndef PLUGIN_PATH
    #define PLUGIN_PATH "./"
  #endif
  if (loader == NULL) {
    loader = malloc(sizeof(struct plugin_loader_s));
    *loader = (struct plugin_loader_s) {
      .version = "1.0.1",
      .built = __DATE__ " " __TIME__,
      .register_for_plugin = register_for_plugin
    };
  }
  if (filenames != NULL) {
    char* filename = malloc(10*1024);
    for (unsigned i = 0; filenames[i] != NULL; i++) {
      sprintf(filename, PLUGIN_PATH "/%s", filenames[i]);
      load_plugin(filename);
    }
    free(filename);
  }
}

struct get_plugin_function_s
get_plugin_function(const char* name) {
  for (int i = loader->nfunctions-1; 0 <= i; i--) {
    plugin_object obj = &loader->functions[i];
    if (obj == NULL) continue;
    if (!strcmp(obj->name, name)) {
      return (struct get_plugin_function_s) { .obj = obj };
    }
  }
  return (struct get_plugin_function_s) { .status=1 };
}

