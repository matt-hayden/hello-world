
#ifndef _PLUGIN_H_
#define _PLUGIN_H_
#include <malloc.h>

typedef struct plugin_definition_s {
  const char *filename;
  const char *name;
  const char *version;
  unsigned nfunctions;
  char **functions;
  void *handle;
} *plugin_definition;

typedef struct loader_definition_s {
  const char *name;
  const char *version;
  int argc;
  char **argv;
  unsigned nplugins;
  plugin_definition *plugins;
} *loader_definition;

typedef int (*definition_function)(const loader_definition, plugin_definition);
#endif
