# -*- coding: utf-8 -*-
"""
Created on Sat Apr  6 17:19:57 2019

@author: kevin
"""
import numpy as np
from matplotlib import pyplot as plt
#from Analisis_ejercicio_1_4 import ajuste_lineal

def ajuste_lineal(x,y):
    N=len(x)    
    Delta=N*sum(x**2)-sum(x)**2
    b=(sum(x**2)*sum(y)-sum(x)*sum(x*y))/Delta
    a=(N*sum(x*y)-sum(x)*sum(y))/Delta
    return a,b

dim=np.array([4,16,32,64,128])
f=open("sigmaVsPc.txt","w")
sigma=np.zeros(len(dim))
p_c=np.zeros(len(dim))

for i in range(len(dim)):
    p=np.loadtxt("probabilidad_critica_dim_%i.txt" % dim[i])
    #plt.hist(p,30)
    #plt.show()
    
    p_c[i]=np.mean(p)
    sigma[i]=np.sqrt(np.var(p))
    
    f.write("%i\t" % dim[i])
    f.write("%f\t" % sigma[i])
    f.write("%f\n" % p_c[i])
f.close()

a,b=ajuste_lineal(sigma,p_c)
print(b)

plt.plot(sigma,p_c,'.')
plt.plot(sigma,a*sigma+b,'-')
plt.show()

