#ifndef _LOADER_H
#define _LOADER_H

#include "plugin.h"

int register_function(struct plugin_object_definition_s);
int load_plugin(const char *);

#define GET_MACRO1(_0, _1, NAME, ...) NAME
#define setup_loader(...) GET_MACRO1(_0, ##__VA_ARGS__, setup_loader1, setup_loader0)(__VA_ARGS__)
#define setup_loader0()		_setup_loader(NULL);
#define setup_loader1(a)	_setup_loader(a);
int _setup_loader(char const **);

struct get_plugin_function_s {
  int status;
  plugin_object obj;
};
struct get_plugin_function_s get_plugin_function(const char*);

#endif
