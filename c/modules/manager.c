#include <assert.h>
#include <dlfcn.h>
#include <malloc.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "plugin.h"

void
plugin_info(plugin_definition plugin) {
  if (plugin == NULL) printf("  (null)\n");
  unsigned w = 2;
  unsigned sw;
  if (w < (sw = strlen(plugin->name)) ) w = sw;
  if (w < (sw = strlen(plugin->version)) ) w = sw;
  printf("  %d)\n", plugin->order);
  printf("  Name:     \t%*s\n", w, plugin->name);
  printf("  Version:  \t%*s\n", w, plugin->version);
  printf("  Functions:\t%*d\n", w, plugin->nfunctions);
}

void
loader_info(loader_definition loader) {
  unsigned w = 2;
  unsigned sw;
  if (w < (sw = strlen(loader->name)) ) w = sw;
  if (w < (sw = strlen(loader->version)) ) w = sw;
  printf("Name:   \t%*s\n", w, loader->name);
  printf("Version:\t%*s\n", w, loader->version);
  printf("Plugins:\t%*d\n", w, loader->nplugins);
  for (unsigned i = 0; i < loader->nplugins; i++) {
    plugin_info(loader->plugins[i]);
    printf("\n");
  }
}

int
call_plugin_setup(loader_definition loader, plugin_definition plugin) {
  module_setup_function_handle_t setup = NULL;
  assert (1 < plugin->nfunctions);
  for (unsigned i = 0; i < plugin->nfunctions; i++) {
    export_function f = plugin->functions[i];
    if (!strcmp(f->name, "__init__")) {
      setup = f->module_setup_function_handle; break;
    }
  }
  if (setup == NULL) {
    fprintf(stderr, "%s plugin has no initialization function\n", plugin->name);
    return 1;
  }
  int status;
  if ( (status = setup(loader, plugin)) ) {
    fprintf(stderr, "%s plugin __init__(...) failed (%d)", plugin->name, status);
  }
  return status;
}

int
initialize_plugin(loader_definition loader, plugin_definition plugin) {
  if (plugin == NULL) {
    fprintf(stderr, "Invalid plugin\n");
    return 1;
  }
  if (plugin->functions == NULL) {
    fprintf(stderr, "Failed to load %s plugin\n", plugin->name);
    return 1;
  }
  return call_plugin_setup(loader, plugin);
}


int
close_plugin(plugin_definition plugin, unsigned flags) {
  plugin->disabled = 1;
  dlclose(plugin->handle);
  plugin = NULL;
  return 0;
}

int
close_plugins(loader_definition loader) {
  for (unsigned i = 0; i < loader->nplugins; i++) {
    close_plugin(loader->plugins[i], 0x0);
  }
}


int
load_plugin(loader_definition loader, const char* filename) {
  if (MAX_NPLUGINS <= loader->nplugins) {
    fprintf(stderr, "Max (%d) plugins already loaded\n", MAX_NPLUGINS);
    return 1;
  }
  assert (loader->plugins[loader->nplugins] == NULL);
  void *lib_handle = dlopen(filename, RTLD_LAZY);
  if (lib_handle == NULL) {
    fprintf(stderr, "Failed to load %s: %s\n", filename, dlerror());
    return 1;
  }
  export_function functions = dlsym(lib_handle, "__exports__");
  if (functions == NULL) {
    fprintf(stderr, "Failed to load functions from %s: %s\n", filename, dlerror());
    return 1;
  }

  module_setup_function_handle_t setup = NULL;
  for (unsigned i = 0; i < 255; i++) {
    char *name = functions[i].name;
    if (name == NULL) break;
    if (!strcmp(name, "__init__") || !strcmp(name, "__INIT__")) {
      setup = functions[i].module_setup_function_handle;
      break;
    }
  }

  plugin_definition plugin = (plugin_definition) malloc(sizeof(struct plugin_definition_s));
  *plugin = (struct plugin_definition_s) {
    .filename=filename,
    .order=loader->nplugins,
    .handle=lib_handle
  };
  if (setup == NULL) {
    fprintf(stderr, "No initialization for plugin %s\n", filename);
  } else if (setup(loader, plugin)) {
    fprintf(stderr, "Failed to initialize plugin %s\n", filename);
    return 2;
  }

  loader->plugins[loader->nplugins++] = plugin;
  return 0;
}



int
main(int argc, char **argv) {
  loader_definition loader = malloc(sizeof(struct loader_definition_s));
  *loader = (struct loader_definition_s) {
    .name="Loader",
    .version="1.0.1",
    .argc=argc,
    .argv=argv
  };
  loader_info(loader);
  load_plugin(loader, "./stub.so");
  loader_info(loader);
  close_plugins(loader);
}
