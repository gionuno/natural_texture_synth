#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Mon Jul 15 15:03:22 2019

@author: gionuno
"""

from distutils.core import setup;
from distutils.extension import Extension;
from Cython.Build import cythonize;

e_modules = cythonize([Extension("libts",["libts.pyx"],extra_compile_args=['-std=c++14','-O3'],libraries=[],language="c++")]);
setup(name="libts",ext_modules = e_modules)