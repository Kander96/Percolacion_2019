# -*- coding: utf-8 -*-
"""
Created on Sat Apr 20 15:57:45 2019

@author: kevin
"""
import numpy as np
from matplotlib import pyplot as plt

#Según el ejercicio 1.a la probabilidad crítica para una red de L=64 es 0.5925

datos=np.loadtxt('ejercicio_5.txt')

p_c=0.5925
sigma_inf=(3*48)/(4*91)
s=np.arange(1,16,1)

def ajuste_lineal(x,y):
    N=len(x)    
    Delta=N*sum(x**2)-sum(x)**2
    b=(sum(x**2)*sum(y)-sum(x)*sum(x*y))/Delta
    a=(N*sum(x*y)-sum(x)*sum(y))/Delta
    return a,b

def funcion(j):
    z=[]
    f_z=[]
    for i in range(101):
        z=np.append(z,(s**sigma)*(datos[i,0]-datos[j,0]))
        f_z=np.append(f_z,datos[i,1:]/datos[j,1:])
    
    plt.plot(z,f_z,'.')
    plt.title('p=%.4f' % datos[j,0])
    plt.yscale('log')
    plt.grid(True,'minor')
    plt.show()

p_max=np.zeros(len(datos[0,:])-1)
for i in range(len(datos[0,:])-1):
    p_max[i]=max(datos[:,i+1])

x=np.log(s)
y=np.log(p_max-p_c)

a,b=ajuste_lineal(x[:8],y[:8])
sigma=-a

plt.plot(x,y,'.')
plt.plot(x,a*x+b,'-')

print(sigma)
    
for j in range(101):
    funcion(j)
