from distutils.core import setup, Extension

module1 = Extension('csieve',
                    sources = ['py_sieve.cpp'])

setup (name = 'csieve',
       version = '0.0',
       description = 'Example of sieve of Eratosthanes, in C++, for Python',
       ext_modules = [module1])
