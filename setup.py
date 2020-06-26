#!/usr/bin/env python

from distutils.core import setup, Extension

module1 = Extension('biteopt',
                    sources = ['biteopt.cpp'])

setup(name='BiteOpt',
      version='0.1',
      description="Python Wrapper for Aleksey Vaneev's BiteOpt",
      author='leonidk',
      author_email='lkeselman@gmail.com',
      url = 'https://github.com/leonidk/biteopt',
      py_modules=['biteopt'],
      ext_modules = [module1]
     )