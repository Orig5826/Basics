import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

figure = plt.figure()
# axes = Axes3D(figure)

R = 10
t = np.linspace(-np.pi, np.pi, 100)
X = R * np.cos(t)
Y = R * np.sin(t)
# X, Y = np.meshgrid(X, Y)
# Z = R**2 - X**2 - Y**2
X = R * np.outer(np.cos(t), np.sin(t))
Y = R * np.outer(np.sin(t), np.sin(t))
Z = R * np.outer(np.ones(np.size(t)), np.cos(t))
"""
    不明白为什么这样绘制出来的是球形
"""
axes = figure.add_subplot(121, projection='3d')
axes.plot_surface(X, Y, Z, rstride=4, cstride=4, color='b')
axes = figure.add_subplot(122, projection='3d')
axes.plot_wireframe(X, Y, Z)
plt.show()
