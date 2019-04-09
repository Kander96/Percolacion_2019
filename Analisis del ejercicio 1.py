# -*- coding: utf-8 -*-
"""
Created on Sat Apr  6 17:19:57 2019

@author: kevin
"""
import numpy as np
from matplotlib import pyplot as plt

p=np.loadtxt("p.txt")
plt.hist(p,30)

p_c=np.mean(p)
sigma=np.sqrt(np.var(p))
gu=35

f=open("sigmaVsPc.txt","a")
f.write("%f\t" % sigma)
f.write("%f\n" % p_c)
f.close()