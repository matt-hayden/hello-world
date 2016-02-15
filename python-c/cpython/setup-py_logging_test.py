from distutils.core import setup, Extension

module1 = Extension('logging_test',
                    sources = ['py_logging_test.c', 'py_logging.c'])

setup (name = 'logging_test',
       version = '0.0',
       description = 'This is a demo package',
       ext_modules = [module1])
