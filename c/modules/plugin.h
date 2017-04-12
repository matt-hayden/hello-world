
#ifndef _PLUGIN_H_
#define _PLUGIN_H_

#define MAX_PLUGINS 255

#ifndef PLUGIN_PERROR
  #include <stdio.h>
  #include <stdlib.h>
  #define PLUGIN_PERROR(...) { fprintf(stderr, __VA_ARGS__); return(10); }
#endif

typedef void* plugin_handle;

typedef struct plugin_object_definition_s {
  plugin_handle lib_handle;
  const char *name;
  const char *filename;
  const char *version;
  const char *declaration;
  const char *built;
  void (*func_ptr)(void);
} *plugin_object;


typedef int (*register_for_plugin_callback_t)(struct plugin_object_definition_s);

typedef struct plugin_loader_s {
  const char *version;
  const char *built;
  unsigned nfunctions;
  register_for_plugin_callback_t register_for_plugin;
  struct plugin_object_definition_s functions[MAX_PLUGINS];
} *plugin_loader;

typedef int (*register_plugin_callback_t)(plugin_loader);


#ifdef __cplusplus
  #error "No C++ support"
#else
  /*
   * C only:
   */
  #define REGISTER_FUNCTION(...) register_for_plugin((struct plugin_object_definition_s) { \
    .filename=__FILE__, \
    .built=__DATE__ " " __TIME__, \
    .version="1.0.0", \
    __VA_ARGS__ })
#endif

#endif
