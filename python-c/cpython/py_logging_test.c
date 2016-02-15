#include "Python.h"
#include "py_logging.c"

static PyMethodDef logging_test_methods[] = {
	{NULL, NULL, 0, NULL}   /* sentinel */
};

/*
 * PyModuleDef has:
 * m_base		PyModuleDef_HEAD_INIT
 * m_name
 * m_doc
 * m_size		-1
 * m_methods	PyMethodDef (above)
 * m_slots
 */
static struct
PyModuleDef module = {
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

void
example(void)
{
	// begin of trivial examples:
	DEBUG("debug from c");
	INFO("info from c");
	WARNING("warning from c");
	logging.warning(Py_BuildValue("(zii)", "The best number is %d, way better than %d", 42, 0));
	ERROR("error from c");
	CRITICAL("critical from c");
}

PyMODINIT_FUNC
PyInit_logging_test(void)
{
	// stock...
	PyObject * m;
	m = PyModule_Create(&module);
	if (m == NULL)
		return NULL;
	// ... end of stock
	setup_logging(NULL, module.m_name, "C");
	Py_AtExit(exit_logging); // Can call multiple times, exit_logging should be called first
	example();
	return m;
}
