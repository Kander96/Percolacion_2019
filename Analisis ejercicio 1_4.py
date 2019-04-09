# -*- coding: utf-8 -*-
"""
Created on Mon Apr  8 18:59:42 2019

@author: kevin
"""
import numpy as np

p=np.linspace(0.55,0.65,11)

def ajuste_lineal(x,y):
    N=len(x)    
    Delta=N*sum(x**2)-sum(x)**2
    b=(sum(x**2)*sum(y)-sum(x)*sum(x*y))/Delta
    a=(N*sum(x*y)-sum(x)*sum(y))/Delta
    return a,b

for i in p:
    datos=np.loadtxt("%.4f.txt" % i)
    x=datos[:20,0]
    y=np.log(datos[:20,1]/len(x))
    a,b=ajuste_lineal(x,y)