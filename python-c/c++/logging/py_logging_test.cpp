#include <Python.h>

#include "py_logging.cpp"

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


void
example(void)
{
	// begin of trivial examples:
	DEBUG("debug from c");
	INFO("info from c");
	WARNING("warning from c");
	// Note that % notation is passed to Python, which is different than printf
	logging->warning(Py_BuildValue("(zif)", "The best number is %d, way better than %.5f", 42, 3.14159));
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
	//logging = logging_config("logging", module.m_name, "C");
	logging = logging_basicConfig();
	Py_AtExit(kill_PythonLogging); // Can call multiple times, exit_logging should be called first
	example();
	return m;
}
