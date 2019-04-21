# -*- coding: utf-8 -*-
"""
Created on Sat Apr 20 19:31:43 2019

@author: kevin
"""
import numpy as np
from matplotlib import pyplot as plt

def ajuste_lineal(x,y):
    N=len(x)    
    Delta=N*sum(x**2)-sum(x)**2
    #b=(sum(x**2)*sum(y)-sum(x)*sum(x*y))/Delta
    a=(N*sum(x*y)-sum(x)*sum(y))/Delta
    return a


datos=np.loadtxt('ejercicio_6.txt')

p_c=0.5925


#plt.xlim(right=0.02)

plt.plot(datos[:,0],datos[:,1],'.')
#plt.plot(p_c*np.array([1,1]),np.array([0,10**7]),'-')
#plt.yscale('log')
plt.grid()
plt.savefig('Gamma_matching_1.pdf')
plt.show()

#plt.plot(abs(datos[:,0]-p_c),np.log(datos[:,1]),'.')
#plt.grid()
#plt.show()
k=30

gamma_mas=np.zeros(k)
gamma_menos=np.zeros(k)
for i in range(k):
    gamma_mas[i]=abs(ajuste_lineal(datos[43+i:48+i,0],datos[43+i:48+i,1]))
    gamma_menos[i]=abs(ajuste_lineal(datos[38-i:43-i,0],datos[38-i:43-i,1]))

j=np.argmin(abs(gamma_mas-gamma_menos))
print(gamma_mas[j])

plt.plot(datos[45:45+k,0]-p_c,gamma_mas,'.')
plt.plot(datos[45:45+k,0]-p_c,gamma_menos,'.')
plt.grid()
plt.xlabel('$p-p_c$')
plt.title('$\gamma$=%f' %gamma_mas[j])
plt.savefig('Gamma_matching_no_log.pdf')
plt.show()


gamma_mas_log=np.zeros(k)
gamma_menos_log=np.zeros(k)
for i in range(k):
    gamma_mas_log[i]=abs(ajuste_lineal(datos[43+i:48+i,0],np.log(datos[43+i:48+i,1])))
    gamma_menos_log[i]=abs(ajuste_lineal(datos[38-i:43-i,0],np.log(datos[38-i:43-i,1])))

l=np.argmin(abs(gamma_mas_log-gamma_menos_log))
print(gamma_mas_log[l])

plt.plot(datos[45:45+k,0]-p_c,gamma_mas_log,'.')
plt.plot(datos[45:45+k,0]-p_c,gamma_menos_log,'.')
plt.grid()
plt.xlabel('$p-p_c$')
plt.title('$\gamma$=%f' %gamma_mas_log[l])
plt.savefig('Gamma_matching_log.pdf')
plt.show()
