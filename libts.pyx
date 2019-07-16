#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Mon Jul 15 15:03:22 2019

@author: gionuno
"""

import cython;
from libcpp.vector cimport vector;
import numpy as np;

cdef extern from "libts.hpp":
    cdef vector[vector[vector[double]]] tex_synth_cpp(vector[vector[vector[double]]] &,vector[vector[vector[double]]] &,int,int);

def tex_synth(T,I,S,K):
    return np.array(tex_synth_cpp(T,I,S,K));

