#include <stdlib.h>

#include "plugin.h"

double
addone(unsigned arg) {
  return (double) arg+1;
}

void
iquit() {
}

int
register_plugin(void *lib_handle,
                const register_function_callback_t register_function,
                struct plugin_loader_s *loader) {
  register_function((struct register_function_s) {
    .lib_handle=lib_handle,
    .name="addone",
    .declaration="double addone(unsigned arg)",
    .unsigned_to_double_function=addone
  });
  atexit(iquit);
  return 0;
}
