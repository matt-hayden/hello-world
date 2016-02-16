from distutils.core import setup, Extension

module1 = Extension('args',
                    sources = ['Example-3.c'])

setup (name = 'Cargs',
       version = '1.0',
       description = 'This is a demo package',
       ext_modules = [module1])
