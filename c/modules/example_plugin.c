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

#define GET_MACRO4(_0, _1, _2, _3, NAME, ...) NAME
#define EXPORT(...) GET_MACRO4(_0, ##__VA_ARGS__, EXPORT3, EXPORT2, EXPORT1, EXPORT0)(__VA_ARGS__)
#define EXPORT1(f)       EXPORT2("(no declaration)", f)
#define EXPORT2(d, f)    EXPORT3(#f, d, f)
#define EXPORT3(n, d, f) loader->REGISTER_FUNCTION(.name=n, .declaration=d, .func_ptr=(function_handle) f)
int
register_plugin(plugin_loader loader) {
  //EXPORT(addone); // Does not provide a useful .declaration
  EXPORT("double addone(unsigned)", addone);
  //EXPORT("addone", "double addone(unsigned)", addone); // allows you to rename functions
  atexit(iquit);
  return 0;
}
