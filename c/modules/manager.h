#ifndef _MANAGER_H_
#define _MANAGER_H_

#include "plugin.h"

static
struct loader_definition_s loader = { .name="Manager", .version="1.0.1" };

int close_plugins(void);
int load_plugin(const char*);
void plugin_info(const plugin_definition);
#endif
