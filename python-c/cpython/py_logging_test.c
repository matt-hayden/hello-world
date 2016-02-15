#include "Python.h"
#include "py_logging.c"

static PyMethodDef logging_test_methods[] = {
	//{"argtest", (PyCFunction)argtest, METH_VARARGS, "Show C logging_test in Python."},
	{NULL, NULL, 0, NULL}   /* sentinel */
};

static struct
PyModuleDef logging_test_module = {
	PyModuleDef_HEAD_INIT,
	"logging_test",
	NULL,
	-1,
	logging_test_methods
};

/*

Access the Python logging facility from within C. debug(), info(), warning(), error(), critical() are simple functions for dropping
strings to Python.
	logging.debug(Py_BuildValue("(zi)", PyUnicode_FromString(message), PyInt_FromLong(1234)) ) 
*/

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
	ERROR("error from c");
	CRITICAL("critical from c");
	return m;
}
