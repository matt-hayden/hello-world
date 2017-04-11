#include <assert.h>
#include <stdio.h>

void
narf(void) {
  printf("*** NARF ***\n");
}

#include "plugin.h"
int __init__(const loader_definition, plugin_definition);

const struct export_function_s __exports__[] = {
  { .name="__init__", .prototype="module_setup_function", .module_setup_function_handle=__init__ },
  { .name="narf",
    .description="I narf",
    .prototype="void_to_void_function",
    .void_to_void_handle=narf
  },
  { NULL }
};


int
__init__(const loader_definition loader, plugin_definition plugin) {
  assert (plugin->functions == NULL);
  assert (plugin->nfunctions == 0);
  plugin->name = "STUB";
  plugin->version = "1.0.1";
  plugin->functions = (export_function *) __exports__;
  for (unsigned i = 0; i < 255; i++) if (plugin->functions[i] == NULL) {
    plugin->nfunctions = i; break;
  }
  printf("Setup module STUB with %d functions\n", plugin->nfunctions);
  return 0;
}
