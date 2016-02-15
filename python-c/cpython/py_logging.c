/*
Access the Python logging facility from within C. debug(), info(), warning(), error(), critical() are simple functions for dropping
strings to Python.

// Don't forget to initialize and finalize in this way:

PyMODINIT_FUNC
PyInit_logging_test(void)
{
	// stock...
	PyObject * m;
	m = PyModule_Create(&logging_test_module);
	if (m == NULL)
		return NULL;
	// ... end of stock
	setup_logging("logging");
	Py_AtExit(exit_logging); // Can call multiple times, exit_logging should be called first
	DEBUG("debug from c");
	INFO("info from c");
	WARNING("warning from c");
	// arguments must be explicitly specified:
	logging.warning(Py_BuildValue("(zii)", "The best number is %d, way better than %d", 42, 0));
	ERROR("error from c");
	CRITICAL("critical from c");
	return m;
}
*/

#include <assert.h>

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
PyObject * pLoggingModule;
struct LoggingFunctionHandleInterface {
	PyObject * debug,
		 * info,
		 * warning,
		 * error,
		 * critical;
} py_logging_handles;

struct LoggingFunctionHandleInterface
get_standard_logging_handles(PyObject * pModule)
{
	PyObject * pModuleContents;
	pModuleContents = PyModule_GetDict(pModule);
	const struct LoggingFunctionHandleInterface handles =
		{ PyDict_GetItemString(pModuleContents, "debug"),
		  PyDict_GetItemString(pModuleContents, "info"),
		  PyDict_GetItemString(pModuleContents, "warning"),
		  PyDict_GetItemString(pModuleContents, "error"),
		  PyDict_GetItemString(pModuleContents, "critical") };
	Py_DECREF(pModuleContents);
	pModuleContents = NULL;
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
	{ PyObject_CallObject(py_logging_handles.debug, args); }

	void
	_info(PyObject * args)
	{ PyObject_CallObject(py_logging_handles.info, args); }

	void
	_warning(PyObject * args)
	{ PyObject_CallObject(py_logging_handles.warning, args); }

	void
	_error(PyObject * args)
	{ PyObject_CallObject(py_logging_handles.error, args); }

	void
	_critical(PyObject * args)
	{ PyObject_CallObject(py_logging_handles.critical, args); }

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
	

PyObject *
setup_logging(const char * module_name)
{
	pLoggingModule = PyImport_Import(PyUnicode_FromString(module_name));

	py_logging_handles = get_standard_logging_handles(pLoggingModule);
	assert( PyCallable_Check(py_logging_handles.debug) &&
		PyCallable_Check(py_logging_handles.info) &&
		PyCallable_Check(py_logging_handles.warning) &&
		PyCallable_Check(py_logging_handles.error) &&
		PyCallable_Check(py_logging_handles.critical) );
	logging = get_standard_logging_functions(py_logging_handles);
	return pLoggingModule;
}


void
exit_logging(void)
{
	Py_DECREF(py_logging_handles.debug);
	Py_DECREF(py_logging_handles.info);
	Py_DECREF(py_logging_handles.warning);
	Py_DECREF(py_logging_handles.error);
	Py_DECREF(py_logging_handles.critical);
	Py_DECREF(pLoggingModule);
}


