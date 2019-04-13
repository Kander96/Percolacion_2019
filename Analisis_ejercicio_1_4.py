# -*- coding: utf-8 -*-
"""
Created on Mon Apr  8 18:59:42 2019

@author: kevin
"""
import numpy as np
from matplotlib import pyplot as plt



def ajuste_lineal(x,y):
    N=len(x)    
    Delta=N*sum(x**2)-sum(x)**2
    b=(sum(x**2)*sum(y)-sum(x)*sum(x*y))/Delta
    a=(N*sum(x*y)-sum(x)*sum(y))/Delta
    return a,b

def testear_ajuste(dim,p):
    
    t=np.zeros(len(p))
    for i in range(len(p)):
        datos=np.loadtxt("ej_1_4_p_%.5f_dim_%i.txt" % (p[i],dim))
        x=np.log(datos[:16,0])
        y=np.log(datos[:16,1]/len(x))
        a,b=ajuste_lineal(x,y)
        t[i]=sum((y-(a*x+b))**2) 
    """
        plt.plot(x,y,'.r')
        plt.plot(x,a*x+b,'-g')
        plt.title("p=%.4f" % p[i])
        plt.ylabel('Log($n_s(p)$)')
        plt.xlabel('Log(s)')
        plt.grid()
        plt.show()
    """    
    return t
p=np.linspace(0.59190,0.59200,51)    
t=testear_ajuste(32,p)
k=p[np.argmin(t)]
print('$p_{crtitico}=$',k)
plt.plot(p,t,'.')
plt.plot(k,t[np.argmin(t)],'*r')
plt.grid()