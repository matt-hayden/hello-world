#include <Python.h>

#include "PythonLogging.cpp"

PythonLogging * logging;

void inline
DEBUG(const std::string & message)
{ logging->debug(Py_BuildValue("(z)", message.c_str() )); }

void inline
INFO(const std::string & message)
{ logging->info(Py_BuildValue("(z)", message.c_str() )); }

void inline
WARNING(const std::string & message)
{ logging->warning(Py_BuildValue("(z)", message.c_str() )); }

void inline
ERROR(const std::string & message)
{ logging->error(Py_BuildValue("(z)", message.c_str() )); }

void inline
CRITICAL(const std::string & message)
{ logging->critical(Py_BuildValue("(z)", message.c_str() )); }


/* Needs:
 *	Py_AtExit(kill_PythonLogging);
 */
void
kill_PythonLogging(void)
{
	delete logging;
}
