#include "plugin.h"


int
register_plugin(plugin_loader loader) {
  printf("%8s\t%20s\n", "version", "built");
  printf("%8s\t%20s\n", loader->version, loader->built);
  printf("   %2d functions%s\n", loader->nfunctions, (0 < loader->nfunctions)? ":" : "");
  for (unsigned i = 0; i < loader->nfunctions; i++) {
    struct plugin_object_definition_s obj = loader->functions[i];
    printf("%2d %p\t%30s\t%12s\t%8s\t%20s\n", i, obj.lib_handle, obj.declaration, obj.filename, obj.version, obj.built);
  }
  return 0;
}
