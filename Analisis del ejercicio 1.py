# -*- coding: utf-8 -*-
"""
Created on Sat Apr  6 17:19:57 2019

@author: kevin
"""
import numpy as np
from matplotlib import pyplot as plt

dim=np.array([4,16,32,64,128])
f=open("sigmaVsPc.txt","w")

for i in dim:
    p=np.loadtxt("probabilidad_critica_dim_%i.txt" % i)
    plt.hist(p,30)
    plt.show()
    
    p_c=np.mean(p)
    sigma=np.sqrt(np.var(p))
    
    f.write("%i\t" % i)
    f.write("%f\t" % sigma)
    f.write("%f\n" % p_c)
f.close()

datos=np.loadtxt("sigmaVsPc.txt")
plt.plot(datos[1:,1],datos[1:,2],'.')

datos[-2,1]