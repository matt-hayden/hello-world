#ifndef _PY_LOGGING_C_
#define _PY_LOGGING_C_
#include "py_logging.h"

#include <assert.h>


static PyObject * logging_logger;
static LoggingFunctionHandleInterface * logging_function_handles;
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


LoggingFunctionHandleInterface *
get_standard_logging_handles(PyObject * arg)
{
	LoggingFunctionHandleInterface * handles;
	handles = malloc(sizeof(LoggingFunctionHandleInterface));
	assert(handles != NULL && "memory error");
	assert(PyObject_HasAttrString(arg, "debug") && "debug() invalid");
	handles->debug = PyObject_GetAttrString(arg, "debug");
	assert(PyObject_HasAttrString(arg, "info") && "info() invalid");
	handles->info = PyObject_GetAttrString(arg, "info");
	assert(PyObject_HasAttrString(arg, "warning") && "warning() invalid");
	handles->warning = PyObject_GetAttrString(arg, "warning");
	assert(PyObject_HasAttrString(arg, "error") && "error() invalid");
	handles->error = PyObject_GetAttrString(arg, "error");
	assert(PyObject_HasAttrString(arg, "critical") && "critical() invalid");
	handles->critical = PyObject_GetAttrString(arg, "critical");
	return handles;
}


LoggingLevelFunctionInterface *
get_standard_logging(void)
{
	LoggingLevelFunctionInterface * lo;
	lo = malloc(sizeof(LoggingLevelFunctionInterface));
	assert(lo != NULL && "memory error");
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
		logging_module = PyImport_ImportModule(module_name);
	else
		logging_module = PyImport_ImportModule("logging");

	assert(logging_module != NULL && "module import error");
	assert(PyObject_HasAttrString(logging_module, "getLogger") && "logger.getLogger() invalid");

	if (logger_name != NULL && logger_name[0] != '\0')
		logger = PyObject_CallMethod(logging_module, "getLogger", "(z)", logger_name);
	else
		logger = PyObject_CallMethod(logging_module, "getLogger", NULL);

	assert(logger != NULL && "method error");

	if (child_name != NULL || child_name[0] != '\0')
	{
		assert(PyObject_HasAttrString(logger, "getChild") && "logger.getChild() invalid");
		Py_DECREF(logger); // replaced by...
		logger = PyObject_CallMethod(logger, "getChild", "(z)", child_name);
	}
	Py_XDECREF(logging_module);
	return logging_set_logger(logger);
}

int inline
logging_basicConfig(void)
{
	return logging_config("logging", NULL, "C");
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
