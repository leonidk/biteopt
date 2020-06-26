#!/usr/bin/env python
import os
import sys
from distutils.core import setup, Extension

# https://github.com/pypa/packaging-problems/issues/84
# no sensible way to include header files by default
headers = ['biteopt.h','biternd.h']
def get_c_sources(files, include_headers=False):
    return files + (headers if include_headers else [])

module1 = Extension('biteopt_ext',
                  sources=get_c_sources(['biteopt_py_ext.cpp'], include_headers=(sys.argv[1] == "sdist")),
                  language="c++",
                  extra_compile_args=['-std=c++11'] if os.name != 'nt' else [])

setup(name='biteopt',
      version='0.1',
      description="Python Wrapper for Aleksey Vaneev's BiteOpt",
      author='leonidk',
      author_email='lkeselman@gmail.com',
      url = 'https://github.com/leonidk/biteopt',
      py_modules=[],
      ext_modules = [module1]
     )
