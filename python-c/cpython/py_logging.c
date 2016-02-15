#include <assert.h>

#define FALSE 0
#define TRUE !FALSE
#define _STR(arg) #arg
#define STR(arg) _STR(arg)

#include "Python.h"

// Arguments are tuples:
	#define DEBUG(arg) \
		logging.debug(Py_BuildValue("(z)", arg));
	#define INFO(arg) \
		logging.info(Py_BuildValue("(z)", arg));
	#define WARNING(arg) \
		logging.warning(Py_BuildValue("(z)", arg));
	#define ERROR(arg) \
		logging.error(Py_BuildValue("(z)", arg));
	#define CRITICAL(arg) \
		logging.critical(Py_BuildValue("(z)", arg));

// globals for python logging
PyObject * logging_module,
		 * logging_logger;

struct LoggingFunctionHandleInterface {
	PyObject * debug,
		 * info,
		 * warning,
		 * error,
		 * critical;
} logging_function_handles;

struct LoggingFunctionHandleInterface
get_standard_logging_handles(PyObject * arg)
{
	const struct LoggingFunctionHandleInterface handles =
		{ PyObject_GetAttrString(arg, "debug"),
		  PyObject_GetAttrString(arg, "info"),
		  PyObject_GetAttrString(arg, "warning"),
		  PyObject_GetAttrString(arg, "error"),
		  PyObject_GetAttrString(arg, "critical") };
	return handles;
}


struct LoggingLevelFunctionInterface {
	void (*debug)(PyObject * args);
	void (*info)(PyObject * args);
	void (*warning)(PyObject * args);
	void (*error)(PyObject * args);
	void (*critical)(PyObject * args);
} logging;

// These can't be inlines
	void
	_debug(PyObject * args)
	{ PyObject_CallObject(logging_function_handles.debug, args); }

	void
	_info(PyObject * args)
	{ PyObject_CallObject(logging_function_handles.info, args); }

	void
	_warning(PyObject * args)
	{ PyObject_CallObject(logging_function_handles.warning, args); }

	void
	_error(PyObject * args)
	{ PyObject_CallObject(logging_function_handles.error, args); }

	void
	_critical(PyObject * args)
	{ PyObject_CallObject(logging_function_handles.critical, args); }

struct LoggingLevelFunctionInterface
get_standard_logging_functions(struct LoggingFunctionHandleInterface handles)
{
	const struct LoggingLevelFunctionInterface logging = {
		_debug,
		_info,
		_warning,
		_error,
		_critical };
	return logging;
}

int
setup_logging(const char * module_name,
			  const char * logger_name, 
			  const char * child_name)
{
	if (module_name != NULL)
		logging_module = PyImport_ImportModule(module_name); // global
	else
		logging_module = PyImport_ImportModule("logging"); // global
	assert(PyObject_HasAttrString(logging_module, "getLogger"));
	if (logger_name != NULL)
		logging_logger = PyObject_CallMethod(logging_module, "getLogger", "(z)", logger_name);
	else
		logging_logger = PyObject_CallMethod(logging_module, "getLogger", NULL);
	if (child_name != NULL) {
		assert(PyObject_HasAttrString(logging_logger, "getChild"));
		Py_DECREF(logging_logger);
		logging_logger = PyObject_CallMethod(logging_logger, "getChild", "(z)", child_name);
	}
	logging_function_handles = get_standard_logging_handles(logging_logger);
	assert( PyCallable_Check(logging_function_handles.debug) &&
			PyCallable_Check(logging_function_handles.info) &&
			PyCallable_Check(logging_function_handles.warning) &&
			PyCallable_Check(logging_function_handles.error) &&
			PyCallable_Check(logging_function_handles.critical) );
	logging = get_standard_logging_functions(logging_function_handles);
	return TRUE;
}


void
exit_logging(void)
{
	Py_DECREF(logging_function_handles.debug);
	Py_DECREF(logging_function_handles.info);
	Py_DECREF(logging_function_handles.warning);
	Py_DECREF(logging_function_handles.error);
	Py_DECREF(logging_function_handles.critical);
	Py_DECREF(logging_logger);
	Py_XDECREF(logging_module);
}


