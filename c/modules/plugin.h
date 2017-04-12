
#ifndef _PLUGIN_H_
#define _PLUGIN_H_

#define MAX_PLUGINS 255

typedef void* plugin_handle;

struct register_function_s {
  plugin_handle lib_handle;
  const char *name;
  const char *version;
  const char *declaration;
  double (*unsigned_to_double_function)(unsigned);
  void (*void_to_void_function)(void);
};


typedef int (*register_function_callback_t)(struct register_function_s);

#define REGISTER_FUNCTION(...) register_function((struct register_function_s) { __VA_ARGS__ })


struct plugin_loader_s {
  char *version;
  unsigned nfunctions;
  register_function_callback_t register_function;
  //register_plugin_callback_t register_plugin;
  struct register_function_s functions[MAX_PLUGINS];
};

typedef int (*register_plugin_callback_t)(struct plugin_loader_s *);

#endif
