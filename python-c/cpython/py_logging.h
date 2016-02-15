/* py_logging
 * Provides DEBUG, INFO, WARNING, ERROR, CRITICAL in c
 * These shoot messages back to the Python logging module, with some
 * configuration allowed.
 */
#ifndef _PY_LOGGING_H_
#define _PY_LOGGING_H_

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

typedef struct LoggingFunctionHandleInterface {
	PyObject * debug,
			 * info,
			 * warning,
			 * error,
			 * critical;
} LoggingFunctionHandleInterface;

typedef struct LoggingLevelFunctionInterface {
	void (*debug)(PyObject * args);
	void (*info)(PyObject * args);
	void (*warning)(PyObject * args);
	void (*error)(PyObject * args);
	void (*critical)(PyObject * args);
} LoggingLevelFunctionInterface;

LoggingFunctionHandleInterface * get_standard_logging_handles(PyObject *);
/*
 * Get function pointers to Python functions
 */

LoggingLevelFunctionInterface * get_standard_logging(void);
/*
 * A struct of different c functions corresponding to debug ... critical
 */

int logging_set_logger(PyObject * logger);
/*
 * Manages global assignments from the above two functions
 */

int logging_config(const char * module_name,
				   const char * logger_name,
				   const char * child_name);
/*
 * Customize the underlying logging objects:
 *  module_name is usually "logging"
 *  logger_name is usually the name of your module, e.g. module.m_name
 *  child_name is usually "C"
 */

int logging_basicConfig(void);
/*
 * Simple wrapper of logging_config() without any tough decisions
 */

void exit_logging(void);
/*
 * This should be called above other AtExit calls:
 * Py_AtExit(exit_logging);
 */

/*
 * Globals for python logging
 */
PyObject * logging_logger;
LoggingFunctionHandleInterface * logging_function_handles;
LoggingLevelFunctionInterface * logging;

#endif
