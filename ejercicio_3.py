# -*- coding: utf-8 -*-
"""
Created on Sat Apr 13 17:58:58 2019

@author: kevin
"""
import numpy  as np
from matplotlib import pyplot as plt

p=np.arange(0.5907,0.5947,0.001)

def ajuste_lineal(x,y):
    N=len(x)    
    Delta=N*sum(x**2)-sum(x)**2
    b=(sum(x**2)*sum(y)-sum(x)*sum(x*y))/Delta
    a=(N*sum(x*y)-sum(x)*sum(y))/Delta
    return a,b

D=91/48

f=open("Dimension_fractal.txt","w")
f.write('D(inf)=\t%f\n' %D)

for i in p:
   # print(i)
    datos=np.loadtxt('ej_3_p_%.6f.txt' % i)
    plt.plot(np.log(datos[:,0]),np.log(datos[:,1]),'.',label='p=%.4f' % i)    
    a,b=ajuste_lineal(np.log(datos[:,0]),np.log(datos[:,1]))
    print('D=',2+a)    
    plt.show()
#plt.plot([0,1],[0.5,0.5],'--')
#plt.legend(loc= 'upper right')
    f.write('p=%f\tD=%f\n' %(i,2+a))
f.close()



#plt.xlabel('Log(ro)')
#plt.ylabel('Log(L)')
#plt.grid()
#plt.savefig('fafafa.pdf')
#plto.show()
