# -*- coding: utf-8 -*-
"""
Created on Sat Apr 20 15:57:45 2019

@author: kevin
"""
import numpy as np
from matplotlib import pyplot as plt

#% matplotlib qt
#Según el ejercicio 1.a la probabilidad crítica para una red de L=64 es 0.5925

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
    #j=41
    z=[]
    f_z=[]
    for i in range(len(datos)):
        z=np.append(z,(s**sigma_inf)*(datos[i,0]-datos[j,0]))
        f_z=np.append(f_z,datos[i,1:]/datos[j,1:])
    
    plt.clf()    
    plt.plot(z,f_z,'.')
    #plt.title('sigma=%.4f' % sigma)
    plt.title('p=%f' %datos[j,0])
    plt.yscale('log')
    plt.grid(True)
    plt.pause(0.001)
    #plt.show()

def funcion_sigma(sigma):
    j=120
    z=[]
    f_z=[]
    for i in range(len(datos)):
        z=np.append(z,(s**sigma)*(datos[i,0]-datos[j,0]))
        f_z=np.append(f_z,datos[i,1:]/datos[j,1:])
    
    plt.clf()    
    plt.plot(z,f_z,'.')
    #plt.title('sigma=%.4f' % sigma)
    plt.title('$\sigma$=%f' %sigma)
    plt.yscale('log')
    plt.xlim([-1.4,0.7])
    plt.grid(True)
    plt.pause(0.1)

def takeFirst(elem):
    return elem[0]

datos=np.loadtxt('ejercicio_5.txt')
h=list(datos)
h.sort(key=takeFirst)
datos=np.array(h)

p_max=np.zeros(len(datos[0,:])-1)
for i in range(len(datos[0,:])-1):
    p_max[i]=datos[np.argmax(datos[:,i+1]),0]

x=np.log(s)
y=np.log(abs(p_max-p_c))

a,b=ajuste_lineal(x,y)
a_1,b_1=np.polyfit(x[:8],y[:8],1)
sigma=-a

plt.plot(x,y,'.')
plt.plot(x,a*x+b,'-')
plt.xlabel('Log(s)')
plt.ylabel('Log($p_{max}-p_c$)')
plt.grid()
plt.xlim(left=-0.1)
plt.title(r'$\sigma=$%.4f' %sigma)
plt.savefig('sigma.pdf')
plt.show()

print('sigma=',sigma)
    
#for j in range(len(datos)):
#    funcion(j)

sig=np.linspace(0.3,0.4,30)  
for j in sig:
    funcion_sigma(j)