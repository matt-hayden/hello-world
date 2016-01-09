from distutils.core import setup, Extension

module1 = Extension('spam',
                    sources = ['Example-1.c'])

setup (name = 'SpamPackage',
       version = '1.0',
       description = 'This is a demo package',
       ext_modules = [module1])
