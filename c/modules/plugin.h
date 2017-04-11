
#ifndef _PLUGIN_H_
#define _PLUGIN_H_

#define MAX_NPLUGINS 16

#include <dlfcn.h>

typedef struct loader_definition_s *loader_definition;
typedef struct plugin_definition_s *plugin_definition;
typedef struct export_function_s *export_function;

typedef int (*module_setup_function_handle_t)(const loader_definition, plugin_definition);
typedef int (*delete_module_function_handle_t)(plugin_definition);

struct loader_definition_s {
  const char *name;
  const char *version;
  int argc;
  char **argv;
  unsigned nplugins;
  plugin_definition plugins[MAX_NPLUGINS];
};

struct plugin_definition_s {
  unsigned order;
  void *handle;
  int disabled;
  char *filename;
  char *name;
  char *description;
  char *version;
  unsigned nfunctions;
  export_function *functions;
};

struct export_function_s {
  const char *name;
  const char *description;
  const char *prototype;
  module_setup_function_handle_t module_setup_function_handle;
  delete_module_function_handle_t delete_module_function_handle;
  double (*unsigned_to_double_handle)(unsigned);
  void (*void_to_void_handle)(void);
};

#endif
