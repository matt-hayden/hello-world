from distutils.core import setup, Extension

module1 = Extension('keywdarg',
                    sources = ['Example-2.c'])

setup (name = 'ParrotPackage',
       version = '1.0',
       description = 'This is a demo package',
       ext_modules = [module1])
