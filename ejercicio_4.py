# -*- coding: utf-8 -*-
"""
Created on Fri Apr 19 21:00:41 2019

@author: kevin
"""
import numpy as np
from matplotlib import pyplot as plt

#% matplotlib qt
#Según el ejercicio 1.a la probabilidad crítica para una red de L=64 es 0.5925

p_c=0.5925
sigma=(3*48)/(4*91)
s=np.arange(40,500,1)

def funcion(j):
    z=[]
    f_z=[]
    for i in range(len(datos)):
        z=np.append(z,(s**sigma)*(datos[i,0]-datos[j,0]))
        f_z=np.append(f_z,datos[i,1:]/datos[j,1:])
    
    plt.clf()
    plt.plot(z,f_z,'.')
    plt.title('p=%.4f' % datos[j,0])
    plt.yscale('log')
    plt.grid(True,'minor')
    plt.pause(0.1)
    
def funcion_2(j):
    for i in range(len(datos)):
        z=[]
        f_z=[]
        z=np.append(z,(s**sigma)*(datos[i,0]-datos[j,0]))
        f_z=np.append(f_z,datos[i,1:]/datos[j,1:])
    
        #plt.clf()        
        plt.plot(z,f_z,'.r')
        plt.title('p=%.4f' % datos[i,0])
        #plt.xlim(-1.3,1.1)
        #plt.ylim(0,5.5)
        plt.yscale('log')
        plt.grid(True,'minor')
        plt.pause(0.1)
        
def takeFirst(elem):
    return elem[0]

datos=np.loadtxt('ejercicio_4.txt')
h=list(datos)
h.sort(key=takeFirst)
datos=np.array(h)

for j in np.linspace(28,78,51):
    funcion(j)

funcion_2(51)