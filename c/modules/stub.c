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
register_plugin(struct plugin_loader_s *loader) {
  loader->REGISTER_FUNCTION(.name="addone", .declaration="double addone(unsigned)", .unsigned_to_double_function=addone);
  atexit(iquit);
  return 0;
}
