# -*- coding: utf-8 -*-
"""
Created on Sat Apr 13 17:58:58 2019

@author: kevin
"""
import numpy  as np
from matplotlib import pyplot as plt

#p=np.linspace(0.585,0.602,18)
p=[0.585,0.593,0.602]

def ajuste_lineal(x,y):
    N=len(x)    
    Delta=N*sum(x**2)-sum(x)**2
    b=(sum(x**2)*sum(y)-sum(x)*sum(x*y))/Delta
    a=(N*sum(x*y)-sum(x)*sum(y))/Delta
    return a,b

D=91/48

j=[18,10,5]

f=open("Dimension_fractal_3.txt","w")
f.write('D(inf)=\t%f\n' %D)

for i in range(len(p)):
   # print(i)
    #plt.clf()    
    datos=np.loadtxt('ej_3_p_%.6f_2.txt' % p[i])
    plt.plot(np.log(datos[:,0]),np.log(datos[:,1]),'.',label='p=%.4f' % p[i])    
    a,b=ajuste_lineal(np.log(datos[:j[i],0]),np.log(datos[:j[i],1]))
    plt.plot(np.log(datos[:,0]),a*np.log(datos[:,0])+b,'-k')
    print('D=',2+a) 
    plt.legend()    
    plt.grid()
    plt.xlabel('Log(L)')
    plt.ylabel(r'Log($\rho$)')
    plt.pause(0.01)
    #plt.show()
#plt.plot([0,1],[0.5,0.5],'--')
#plt.legend(loc= 'upper right')
    f.write('p=%f\tD=%f\n' %(i,2+a))
f.close()
plt.savefig('densidad_de_masa.pdf')


#plt.xlabel('Log(ro)')
#plt.ylabel('Log(L)')
#plt.grid()
#plt.savefig('fafafa.pdf')
#plto.show()
