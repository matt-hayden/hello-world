/*
 Modified from Python documentation.
 Multiple argument type parsing
 */

#include <stdio.h>

#include "Python.h"
#define PY_SSIZE_T_CLEAN
#define Py_LIMITED_API 0x03020000

int
print_iterable(PyObject* iterable)
{
	PyObject *iterator;
	PyObject *error;
	if (PyIter_Check(iterable)) {
		iterator = iterable;
	} else {
		iterator = PyObject_GetIter(iterable);
	}
	/*
	error = PyErr_Occurred();
	if (error != NULL) {
		printf("print_iterable failed\n");
		return 0;
	}
	Py_DECREF(error);
	*/
	
	if (iterator != NULL) {
		PyObject *item;
		printf("Iterable:\n");
		while (item = PyIter_Next(iterator)) {
			printf("\t");
			PyObject_Print(item, stdout, 0);
			printf("\n");
			/* release reference when done */
			Py_DECREF(item);
		}
		Py_DECREF(iterator);
		printf("\n");
		return 1;
	}
	return 0;
}

static PyObject *
argtest(PyObject *self, PyObject *args)
{
	int arg_parsed = 0;
	const char * argstring;
	PyObject * argobject; /* needs reference counting */

	if (PyArg_ParseTuple(args, "s", &argstring)) {
		printf("String: %s\n", argstring);
		arg_parsed = 1; // TRUE;
	} else if (PyErr_ExceptionMatches(PyExc_TypeError)) {
		PyErr_Clear();
	}
	if (!arg_parsed && PyArg_ParseTuple(args, "O", &argobject)) {
		if (argobject == Py_None) {
			printf("Argument is 'None'\n");
			arg_parsed = 1;
		} else if (print_iterable(argobject)) {
			arg_parsed = 1;
		} else {
			printf("argument not understood\n");
		}
		Py_DECREF(argobject);
	}
	//Py_RETURN_NONE;
	return arg_parsed ? Py_True : Py_False;
}

static PyMethodDef args_methods[] = {
	/* The cast of the function is necessary since PyCFunction values
	 * only take two PyObject* parameters, and argtest() takes
	 * three.
	 */
	{"argtest", (PyCFunction)argtest, METH_VARARGS,
	 "Show C args in Python."},
	{NULL, NULL, 0, NULL}   /* sentinel */
};

static struct PyModuleDef argsmodule = {
	PyModuleDef_HEAD_INIT,
	"args",
	NULL,
	-1,
	args_methods
};

PyMODINIT_FUNC
PyInit_args(void)
{
	PyObject* m;
	m = PyModule_Create(&argsmodule);
	if (m == NULL)
		return NULL;
	return m;
}
