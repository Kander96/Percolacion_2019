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

def testear_ajuste(dim):
    p=np.linspace(0.55,0.64,10)
    for i in p:
        datos=np.loadtxt("ej_1_4_p_%.4f_dim_%i.txt" % (i,dim))
        x=np.log(datos[:20,0])
        y=np.log(datos[:20,1]/len(x))
        a,b=ajuste_lineal(x,y)
        
        plt.plot(x,y,'.r')
        plt.plot(x,a*x+b,'-g')
        plt.title("p=%.4f" % i)
        plt.ylabel('Log($n_s(p)$)')
        plt.xlabel('s')
        plt.grid()
        plt.show()

testear_ajuste(16)