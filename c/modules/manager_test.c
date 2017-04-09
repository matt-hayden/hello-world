#include "manager.h"

extern
struct loader_definition_s loader;

int
main(int argc, char **argv) {
  loader.argc = argc;
  loader.argv = argv;
  for (unsigned i = 1; i < argc; i++) {
    load_plugin(argv[i]);
  }
  plugin_info(NULL);
  close_plugins();
}
