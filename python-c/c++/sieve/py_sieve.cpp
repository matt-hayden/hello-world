/*
 Modified from Python documentation.
 Multiple argument type parsing
 */
#include <bitset>
#include <iostream>

#define _STR(arg) #arg
#define STR(arg) _STR(arg)

#include "Python.h"
#define PY_SSIZE_T_CLEAN
#define Py_LIMITED_API 0x03020000

#define raise(message) \
	do { PyErr_SetObject(PyExc_TypeError, PyUnicode_FromString(message)); return NULL; } while (0)
	

#define LIMIT 80000000ULL

typedef  unsigned long long int  sieve_size_t;


static
PyObject *
py_get_primes(PyObject * self, PyObject * args)
{
	std::bitset<LIMIT> * p_is_composite;
	PyObject * primes;

	Py_ssize_t nargs, a;
	sieve_size_t limit = (sieve_size_t) LIMIT;

	nargs = PyTuple_Size(args);
	if (nargs == 0) {
		// pass
	} else if (nargs == 1) {
		if (PyArg_ParseTuple(args, "n", &a)) { // n = Py_ssize_t
			if (1 < a) {
				limit = (sieve_size_t) a;
			} else { raise("Invalid limit"); }
		}
	} else { raise("Invalid limit"); }
	if (LIMIT < limit) { raise("limit larger than " STR(LIMIT) ", a baked-in maximum"); }

	p_is_composite = new std::bitset<LIMIT>;
	sieve_size_t i, j;
	for (i=2, j=0; i<limit; i++)
	{
		if (! (*p_is_composite)[i])
		{
			for (j=i; i*j<limit; j++)
				(*p_is_composite)[i*j]=1;
		}
	}
	primes = PyList_New(0);
	for (i=2, j=0; i<limit; i++)
	{
		if (! (*p_is_composite)[i]) {
			PyList_Append(primes, PyLong_FromUnsignedLongLong(i));
		}
	}
	delete p_is_composite;
	p_is_composite = NULL;
	return primes;
}

static
PyMethodDef sieve_methods[] = {
	{"get_primes", (PyCFunction) py_get_primes, METH_VARARGS, "Get a list of primes (up to " STR(LIMIT) ")."},
	{NULL, NULL, 0, NULL}   /* sentinel */
};

static struct
PyModuleDef sieve_module = {
	PyModuleDef_HEAD_INIT,
	"csieve",
	NULL,
	-1,
	sieve_methods
};

PyMODINIT_FUNC
PyInit_csieve(void)
{
	PyObject* m;
	m = PyModule_Create(&sieve_module);
	if (m == NULL)
		return NULL;
	PyModule_AddIntConstant(m, "INTEGER_SIZE_BYTES", sizeof(sieve_size_t));
	PyModule_AddIntConstant(m, "LIMIT", LIMIT);
	return m;
}
