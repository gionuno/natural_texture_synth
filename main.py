#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Sun Jul 14 22:28:41 2019

@author: gionuno
"""

import matplotlib.pyplot as plt;
import matplotlib.image  as img;
import numpy        as np;
import numpy.random as rd;
import scipy.signal as sig;
from libts import tex_synth;

texture = img.imread("flowers.jpeg")/255.0;
mask    = img.imread("mask.jpeg")/255.0;

S = 1;
K = 7;
result = tex_synth(texture,mask,S,K);

synth = result[:,:,:3];
coord = np.zeros(mask.shape);
coord[:,:,0:2] = result[:,:,3:5];

f,ax = plt.subplots(2,2);
ax[0,0].imshow(texture);
ax[0,0].set_axis_off();
ax[0,1].imshow(mask);
ax[0,1].set_axis_off();
ax[1,0].imshow(synth);
ax[1,0].set_axis_off();
ax[1,1].imshow(coord);
ax[1,1].set_axis_off();
plt.show(); 

img.imsave("result.jpeg",synth);
