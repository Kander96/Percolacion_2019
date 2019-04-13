# -*- coding: utf-8 -*-
"""
Created on Fri Apr 12 01:12:28 2019

@author: kevin
"""
import numpy as np
from matplotlib import pyplot as plt

L=[4,16,32,64,128]
f=open("p_critica_1_2.txt","w")

for i in L:
    datos=np.loadtxt('distribucion_de_probabilidad_dim_%i.txt' % i)
    plt.plot(datos[:,0],datos[:,1],'-',label='L=%i' % i)
    j=np.argmin(abs(datos[:,1]-0.5))
    f.write('L:%i\t' % i)
    f.write('p=%f\n' % datos[j,0])    
f.close()
plt.plot([0,1],[0.5,0.5],'--')
plt.legend(loc= 'upper left')
plt.xlim(right=1)
plt.grid()
plt.savefig('primera_imagen.pdf')
plt.show()