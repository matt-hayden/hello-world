#include <stdio.h>
#include <stdlib.h>

#include "plugin.h"

double
addone(unsigned arg) {
  return (double) arg+1;
}

void
iquit() {
  printf("Leaving " __FILE__ "\n");
}

int
register_plugin(plugin_loader loader) {
  loader->REGISTER_FUNCTION(.name="addone", .declaration="double addone(unsigned)", .func_ptr=addone);
  atexit(iquit);
  return 0;
}
