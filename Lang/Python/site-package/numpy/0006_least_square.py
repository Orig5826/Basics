# -*- coding: utf-8 -*-
"""
Created on Sun Nov 17 14:12:55 2019

@author: Administrator
"""

import matplotlib.pyplot as plt
import numpy as np
x = np.array([25,27,31,33,35])
y = np.array([110,115,155,160,180])
# result = (7.2,-73)
X = np.mat([[25,1],[27,1],[31,1],[33,1],[35,1]])
Y = np.mat(y).T
"""
    最小二乘法的矩阵形式
"""
X_T = X.transpose()
A = np.dot(np.dot(np.linalg.inv(np.dot(X_T,X)),X_T),Y)

a = A[0,0]
b = A[1,0]
y2 = a*x + b
plt.plot(x,y2)
plt.scatter(x,y)
plt.show()
