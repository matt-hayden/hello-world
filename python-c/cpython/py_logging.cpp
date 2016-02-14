/*

Access the Python logging facility from within C. debug(), info(), warning(), error(), critical() are simple functions for dropping
strings to Python. debugO allows explicit args like so:
	debug0(Py_BuildValue("(zi)", PyUnicode_FromString(message), PyInt_FromLong(1234)) ) 

// Don't forget to initialize and finalize in this way:

PyMODINIT_FUNC
PyInit_clogging(void)
{
	// stock...
	PyObject * m;
	m = PyModule_Create(&your_logging_module);
	if (m == NULL)
		return NULL;
	// ... end of stock
	setup_logging();
	Py_AtExit(exit_logging); // Can call multiple times, exit_logging should be called first
	debug("clogging module imported");
	return m;
}
*/

#include <assert.h>

#define _STR(arg) #arg
#define STR(arg) _STR(arg)

#include "Python.h"

#define debug(arg) \
	debugO(Py_BuildValue("(z)", arg));
#define info(arg) \
	infoO(Py_BuildValue("(z)", arg));
#define warning(arg) \
	warningO(Py_BuildValue("(z)", arg));
#define error(arg) \
	errorO(Py_BuildValue("(z)", arg));
#define critical(arg) \
	criticalO(Py_BuildValue("(z)", arg));

// globals for python logging
PyObject * pLoggingModule,
	* pLoggingDebugHandle,
	* pLoggingInfoHandle,
	* pLoggingWarningHandle,
	* pLoggingErrorHandle,
	* pLoggingCriticalHandle;

int
setup_logging(void)
{
	int rv = 0;
	PyObject * pLoggingModuleContents;
	pLoggingModule		=	PyImport_Import(PyUnicode_FromString("logging"));
	pLoggingModuleContents	=	PyModule_GetDict(pLoggingModule);

	pLoggingDebugHandle	=	PyDict_GetItemString(pLoggingModuleContents, "debug");
	assert(PyCallable_Check(pLoggingDebugHandle));
	pLoggingInfoHandle	=	PyDict_GetItemString(pLoggingModuleContents, "info");
	assert(PyCallable_Check(pLoggingInfoHandle));
	pLoggingWarningHandle	=	PyDict_GetItemString(pLoggingModuleContents, "warning");
	assert(PyCallable_Check(pLoggingWarningHandle));
	pLoggingErrorHandle	=	PyDict_GetItemString(pLoggingModuleContents, "error");
	assert(PyCallable_Check(pLoggingErrorHandle));
	pLoggingCriticalHandle	=	PyDict_GetItemString(pLoggingModuleContents, "critical");
	assert(PyCallable_Check(pLoggingCriticalHandle));

	rv = 1;
	Py_DECREF(pLoggingModuleContents);
	pLoggingModuleContents = NULL;
	return rv;
}

void
debugO(PyObject * args)
{ PyObject_CallObject(pLoggingDebugHandle, args); }

void
infoO(PyObject * args)
{ PyObject_CallObject(pLoggingInfoHandle, args); }

void
warningO(PyObject * args)
{ PyObject_CallObject(pLoggingWarningHandle, args); }

void
errorO(PyObject * args)
{ PyObject_CallObject(pLoggingErrorHandle, args); }

void
criticalO(PyObject * args)
{ PyObject_CallObject(pLoggingCriticalHandle, args); }

void
exit_logging(void)
{
	Py_DECREF(pLoggingModule);
	pLoggingModule = NULL;
	Py_DECREF(pLoggingDebugHandle);
	pLoggingDebugHandle = NULL;
	Py_DECREF(pLoggingInfoHandle);
	pLoggingInfoHandle = NULL;
	Py_DECREF(pLoggingWarningHandle);
	pLoggingWarningHandle = NULL;
	Py_DECREF(pLoggingErrorHandle);
	pLoggingErrorHandle = NULL;
	Py_DECREF(pLoggingCriticalHandle);
	pLoggingCriticalHandle = NULL;
}

