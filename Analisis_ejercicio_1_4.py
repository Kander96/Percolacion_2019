# -*- coding: utf-8 -*-
"""
Created on Mon Apr  8 18:59:42 2019

@author: kevin
"""
import numpy as np
from matplotlib import pyplot as plt

#%matplotlib qt

def ajuste_lineal(x,y):
    N=len(x)    
    Delta=N*sum(x**2)-sum(x)**2
    b=(sum(x**2)*sum(y)-sum(x)*sum(x*y))/Delta
    a=(N*sum(x*y)-sum(x)*sum(y))/Delta
    return a,b

def testear_ajuste(dim,p):
    
    t=np.zeros(len(p))
    a=np.zeros(len(p))
    for i in range(len(p)):
        datos=np.loadtxt("ej_1_d_p_%.4f_dim_%i_2.txt" % (p[i],dim))
        x=np.log(datos[int(dim**2*0.01):int((dim**2)*0.06),0])
        y=np.log(datos[int(dim**2*0.01):int((dim**2)*0.06),1]/len(x))
        a[i],b=ajuste_lineal(x,y)
        t[i]=sum((y-(a[i]*x+b))**2) 
        """
        plt.plot(x,y,'.r')
        plt.plot(x,a[i]*x+b,'-g')
        plt.title("p=%.4f" % p[i])
        plt.ylabel('Log($n_s(p)$)')
        plt.xlabel('Log(s)')
        plt.grid()
        plt.pause(0.01)
        plt.clf()
        """
    return t,a
 
     

def funcion(i):    
    p=np.linspace(r[i,1],r[i,2],r[i,3])    
    t,a=testear_ajuste(r[i,0],p)
    k=p[np.argmin(t)]
    tau=a[np.argmin(t)]
    plt.title('p=%.3f   tau=%.3f' %(k,tau))
    plt.plot(p-r[i,1],t,'.')
    plt.plot(k-r[i,1],t[np.argmin(t)],'*r')
    plt.xlabel('p-%.3f' %r[i,1])
    plt.grid()
    plt.savefig('ejercicio_1_4_%i.pdf' %int(r[i,0]))
    plt.show()
    
#r=np.array([[16,0.5882,0.5892,101],[32,0.5917,0.5921,41],[64,0.5922,0.5926,41],[128,0.5924,0.5928,41]])
r=np.array([[16,0.4,0.75,36],[32,0.35,0.75,9],[64,0.5,0.65,16],[128,0.535,0.62,18]])

for i in range(len(r)):
    funcion(i)

funcion(0)