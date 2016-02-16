#include <string>
#include <Python.h>

class PythonLogging
{
public:
	PythonLogging(PyObject * logger);
	~PythonLogging();
	void inline debug(PyObject * args);
	void inline info(PyObject * args);
	void inline warning(PyObject * args);
	void inline error(PyObject * args);
	void inline critical(PyObject * args);
protected:
	PyObject * _debug,
			 * _info,
			 * _warning,
			 * _error,
			 * _critical,
			 * _logger;	
};

PythonLogging::PythonLogging(PyObject * logger)
{
	_logger = logger;
	_debug = PyObject_GetAttrString(logger, "debug");
	assert(PyCallable_Check(_debug) && "logger.debug() invalid");
	_info = PyObject_GetAttrString(logger, "info");
	assert(PyCallable_Check(_info) && "logger.info() invalid");
	_warning = PyObject_GetAttrString(logger, "warning");
	assert(PyCallable_Check(_warning) && "logger.warning() invalid");
	_error = PyObject_GetAttrString(logger, "error");
	assert(PyCallable_Check(_error) && "logger.error() invalid");
	_critical = PyObject_GetAttrString(logger, "critical");
	assert(PyCallable_Check(_critical) && "logger.critical() invalid");
}

PythonLogging::~PythonLogging()
{
	Py_DECREF(_debug);
	Py_DECREF(_info);
	Py_DECREF(_warning);
	Py_DECREF(_error);
	Py_DECREF(_critical);
	Py_XDECREF(_logger);
}

void
inline
PythonLogging::debug(PyObject * args)
{ PyObject_CallObject(_debug, args); }

void
inline
PythonLogging::info(PyObject * args)
{ PyObject_CallObject(_info, args); }

void
inline
PythonLogging::warning(PyObject * args)
{ PyObject_CallObject(_warning, args); }

void
inline
PythonLogging::error(PyObject * args)
{ PyObject_CallObject(_error, args); }

void
inline
PythonLogging::critical(PyObject * args)
{ PyObject_CallObject(_critical, args); }

static
PythonLogging *
logging_config(const std::string & module_name,
			   const std::string & logger_name,
			   const std::string & child_name)
{
	PyObject * logger, * logging_module;
	if (!module_name.empty())
		logging_module = PyImport_ImportModule(module_name.c_str());
	else
		logging_module = PyImport_ImportModule("logging");
	assert(PyObject_HasAttrString(logging_module, "getLogger") && "logger.getLogger() not found");
	if (!logger_name.empty())
		logger = PyObject_CallMethod(logging_module, "getLogger", "(z)", logger_name.c_str());
	else
		logger = PyObject_CallMethod(logging_module, "getLogger", NULL);
	if (!child_name.empty())
	{
		assert(PyObject_HasAttrString(logger, "getChild") && "logger.getChild() not found");
		Py_DECREF(logger); // replaced by...
		logger = PyObject_CallMethod(logger, "getChild", "(z)", child_name.c_str());
	}
	Py_XDECREF(logging_module);
	return new PythonLogging(logger);
}

static
PythonLogging *
logging_basicConfig(void)
{
	return logging_config("logging", "", "C++");
}
