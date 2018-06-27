import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

# 假设圆锥底面积的半径为R
R = 10
theta = np.arange(0, 2 * np.pi, 0.01)

X = R * np.cos(theta)
Y = R * np.sin(theta)
X, Y = np.meshgrid(X, Y)
Z = np.sqrt(X**2 + Y**2)

fig = plt.figure()
ax = Axes3D(fig)
# 用取样点(x,y,z)去构建曲面
ax.plot_surface(X, Y, Z, rstride=1, cstride=1, cmap=plt.cm.coolwarm)

# 给三个坐标轴注明
ax.set_xlabel('x label', color='r')
ax.set_ylabel('y label', color='g')
ax.set_zlabel('z label', color='b')

plt.show()
