# -*- coding: utf-8 -*-
"""
Created on Fri Apr 12 01:12:28 2019

@author: kevin
"""
import numpy as np
from matplotlib import pyplot as plt

p=np.array([4,16,32,64])

for i in p:
    datos=np.loadtxt('distribucion_de_probabilidad_dim_%i.txt' % i)
    plt.plot(datos[:,0],datos[:,1],'.',label='Dimension %i' % i)
plt.plot([0,1],[0.5,0.5],'--')
plt.legend(loc= 'upper left')
plt.grid()
plt.savefig('primera_imagen.pdf')
plt.show()