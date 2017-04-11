
#ifndef _PLUGIN_H_
#define _PLUGIN_H_


struct register_function_s {
  void *lib_handle;
  const char *name;
  const char *version;
  const char *declaration;
  double (*unsigned_to_double_function)(unsigned);
  void (*void_to_void_function)(void);
};

struct plugin_loader_s {
  char *version;
  unsigned nfunctions;
  struct register_function_s functions[255];
};

typedef int (*register_function_callback_t)(struct register_function_s);
typedef int (*register_plugin_callback_t)(void*,
          register_function_callback_t,
          struct plugin_loader_s *);


#endif
