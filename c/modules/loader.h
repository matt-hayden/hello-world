#ifndef _LOADER_H
#define _LOADER_H

#include "plugin.h"

int setup_loader(char **filenames);
int register_function(struct plugin_object_definition_s);
int load_plugin(const char *);

struct get_plugin_function_s {
  int status;
  plugin_object obj;
};
struct get_plugin_function_s get_plugin_function(const char*);

#endif
