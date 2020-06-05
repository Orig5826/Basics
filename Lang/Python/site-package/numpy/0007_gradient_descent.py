# -*- coding: utf-8 -*-
"""
Created on Mon Nov 18 20:46:20 2019

@author: Administrator
"""

import matplotlib.pyplot as plt
import numpy as np

def cost_function(X,y,theta):
    m = len(y)
    y_mat = y.reshape(m,1)
    J = 1/(2*m) * np.sum(np.power((X@theta - y_mat),2))
    return J

def gradient_descent(X,y,theta,alpha,num_iters):
    J_history = np.zeros((num_iters,1))
    m = len(y)
    y_mat = y.reshape(m,1)
    for n_iter in range(num_iters):
        theta = theta - alpha * 1 / m * X.T @ (X @ theta - y_mat)
        J_history[n_iter, 0] = cost_function(X,y,theta)
    return J_history, theta

"""
the result of least square = 
[[  7.20930233]
 [-73.72093023]]
"""
x = np.array([25,27,31,33,35])
y = np.array([110, 115, 155, 160, 180])
m = len(x)
X = np.hstack((x.reshape(m, 1), np.ones((m, 1))))

# initial value = (0,0)
theta = np.array([0, 0]).reshape(2, 1)
# if alpha >= 0.0022 ---> overflow (@.@)
alpha = 0.0021

J,theta = gradient_descent(X,y,theta,alpha,400000)
print(theta)
