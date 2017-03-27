
#undef NAME_CODE_MESSAGE
#define NAME_CODE_MESSAGE( _name, _code, _message ) _name = _code,
typedef enum {
  #include "error_def.h"
  ERROR_MAX
} error_code;
#undef NAME_CODE_MESSAGE

#undef NAME_CODE_MESSAGE
#define NAME_CODE_MESSAGE( _name, _code, _message ) [_code] = #_name,
const char* lookup_error(const error_code k) {
  const static
  char* table[] = {
    #include "error_def.h"
  };
  return (k < ERROR_MAX) ? table[k] : NULL;
}
#undef NAME_CODE_MESSAGE
