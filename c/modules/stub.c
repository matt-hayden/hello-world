#include "plugin.h"

const char __name__[] = "STUB";

const char __definition_function__[] = "stub_plugin_get_definition";

int
stub_plugin_get_definition(const loader_definition loader, plugin_definition pd) {
  pd->name = __name__;
  pd->version="1.0.1";
}
