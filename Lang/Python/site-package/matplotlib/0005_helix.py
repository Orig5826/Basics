import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

# 解决中文乱码问题，方便显示
plt.rcParams['font.sans-serif'] = ['Fangsong']
# 解决保存图像是负号'-'显示为方块的问题,或者转换负号为字符串
plt.rcParams['axes.unicode_minus'] = False

R = 10
b = 1
theta = np.arange(0, 4 * np.pi, 0.01)

X = R * np.cos(theta)
Y = R * np.sin(theta)
Z = b * theta


def plane_view():
    # 主要是为了查看一下
    # 三视图
    plt.axis('equal')
    plt.plot(X, Y, 'r', label='俯视图')
    plt.plot(X, Z, 'g', label='正视图')
    plt.plot(Y, Z, 'b', label='侧视图')
    plt.legend()    # 显示图例
    # plt.show()


def view_3d():
    # 显示实际的三维曲线
    fig = plt.figure()
    ax = fig.gca(projection='3d')
    # 用取样点(x,y,z)去构建曲面
    ax.plot(X, Y, Z, c='r', label='螺旋线')

    # 给三个坐标轴注明
    ax.set_xlabel('x label', color='r')
    ax.set_ylabel('y label', color='g')
    ax.set_zlabel('z label', color='b')
    plt.legend()    # 显示图例
    # plt.show()


if __name__ == '__main__':
    plane_view()
    view_3d()
    plt.show()
