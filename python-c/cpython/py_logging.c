/* py_logging.c
 * Provides DEBUG, INFO, WARNING, ERROR, CRITICAL in c
 * These shoot messages back to the Python logging module, configured by:
setup_logging(const char * module_name,		// Usually NULL for "logging"
			  const char * logger_name, 	// Usually the module name
			  const char * child_name)		// Could be "C", or NULL
 */
#ifndef _PY_LOGGING_C_
#define _PY_LOGGING_C_
#include <assert.h>

#define FALSE 0
#define TRUE !FALSE

#include "Python.h"

// Arguments are tuples:
	#define DEBUG(arg) \
		assert(logging->debug != NULL); \
		logging->debug(Py_BuildValue("(z)", arg));
	#define INFO(arg) \
		logging->info(Py_BuildValue("(z)", arg));
	#define WARNING(arg) \
		logging->warning(Py_BuildValue("(z)", arg));
	#define ERROR(arg) \
		logging->error(Py_BuildValue("(z)", arg));
	#define CRITICAL(arg) \
		logging->critical(Py_BuildValue("(z)", arg));

// globals for python logging
PyObject * logging_logger;

typedef struct LoggingFunctionHandleInterface {
	PyObject * debug,
			 * info,
			 * warning,
			 * error,
			 * critical;
} LoggingFunctionHandleInterface;
LoggingFunctionHandleInterface * logging_function_handles;

LoggingFunctionHandleInterface *
get_standard_logging_handles(PyObject * arg)
{
	assert( PyObject_HasAttrString(arg, "debug") &&
			PyObject_HasAttrString(arg, "info") &&
			PyObject_HasAttrString(arg, "warning") &&
			PyObject_HasAttrString(arg, "error") &&
			PyObject_HasAttrString(arg, "critical") );
	LoggingFunctionHandleInterface * handles;
	handles = malloc(sizeof(LoggingFunctionHandleInterface));
	handles->debug = PyObject_GetAttrString(arg, "debug");
	handles->info = PyObject_GetAttrString(arg, "info");
	handles->warning = PyObject_GetAttrString(arg, "warning");
	handles->error = PyObject_GetAttrString(arg, "error");
	handles->critical = PyObject_GetAttrString(arg, "critical");
	return handles;
}


typedef struct LoggingLevelFunctionInterface {
	void (*debug)(PyObject * args);
	void (*info)(PyObject * args);
	void (*warning)(PyObject * args);
	void (*error)(PyObject * args);
	void (*critical)(PyObject * args);
} LoggingLevelFunctionInterface;
LoggingLevelFunctionInterface * logging;

// These can't be inlines
	void
	_debug(PyObject * args)
	{ PyObject_CallObject(logging_function_handles->debug, args); }

	void
	_info(PyObject * args)
	{ PyObject_CallObject(logging_function_handles->info, args); }

	void
	_warning(PyObject * args)
	{ PyObject_CallObject(logging_function_handles->warning, args); }

	void
	_error(PyObject * args)
	{ PyObject_CallObject(logging_function_handles->error, args); }

	void
	_critical(PyObject * args)
	{ PyObject_CallObject(logging_function_handles->critical, args); }

LoggingLevelFunctionInterface *
get_standard_logging(void)
{
	LoggingLevelFunctionInterface * lo;
	lo = malloc(sizeof(LoggingLevelFunctionInterface));
	lo->debug = _debug;
	lo->info = _info;
	lo->warning = _warning;
	lo->error = _error;
	lo->critical = _critical;
	return lo;
}


int
logging_set_logger(PyObject * logger)
{
	if (logger == NULL)
		return FALSE;
	logging_logger = logger;
	logging_function_handles = get_standard_logging_handles(logging_logger);
	assert( PyCallable_Check(logging_function_handles->debug) &&
			PyCallable_Check(logging_function_handles->info) &&
			PyCallable_Check(logging_function_handles->warning) &&
			PyCallable_Check(logging_function_handles->error) &&
			PyCallable_Check(logging_function_handles->critical) );
	logging = get_standard_logging();
	return TRUE;
}

int
logging_config(const char * module_name,
			   const char * logger_name,
			   const char * child_name)
{
	PyObject * logger, * logging_module;
	if (module_name != NULL && module_name[0] != '\0')
		logging_module = PyImport_ImportModule(module_name); // global
	else
		logging_module = PyImport_ImportModule("logging"); // global
	assert(PyObject_HasAttrString(logging_module, "getLogger"));
	if (logger_name != NULL && logger_name[0] != '\0')
		logger = PyObject_CallMethod(logging_module, "getLogger", "(z)", logger_name);
	else
		logger = PyObject_CallMethod(logging_module, "getLogger", NULL);
	if (child_name != NULL || child_name[0] != '\0')
	{
		assert(PyObject_HasAttrString(logger, "getChild"));
		Py_DECREF(logger); // replaced by...
		logger = PyObject_CallMethod(logger, "getChild", "(z)", child_name);
	}
	Py_XDECREF(logging_module);
	return logging_set_logger(logger);
}

int inline
logging_basicConfig(void)
{
	return logging_config(NULL, NULL, NULL);
}

void
exit_logging(void)
{
	Py_DECREF(logging_function_handles->debug);
	Py_DECREF(logging_function_handles->info);
	Py_DECREF(logging_function_handles->warning);
	Py_DECREF(logging_function_handles->error);
	Py_DECREF(logging_function_handles->critical);
	free(logging);
	free(logging_function_handles);
	Py_DECREF(logging_logger);
}

#endif
