
import matplotlib.pyplot as plt
import numpy as np

plt.rcParams['font.sans-serif'] = ['SimHei']  # 步骤一（替换sans-serif字体）
plt.rcParams['axes.unicode_minus'] = False   # 步骤二（解决坐标轴负数的负号显示问题）


if __name__ == "__main__":
    number = 20
    x = np.arange(1, number)
    y1 = 1/3 * x**3 - 1/3
    y2 = np.cumsum(x**2)
    Delta_y = y2 - y1

    epsilon_1 = Delta_y / y1
    epsilon_2 = Delta_y / y2

    plt.subplot(2, 2, 1)
    plt.plot(x, y1, 'b-',  label='对x^2积分')
    plt.plot(x, y2, 'r.', label='平方累加和')
    plt.legend()
    plt.title('原始数据')

    plt.subplot(2, 2, 2)
    plt.plot(x, Delta_y)
    plt.title('数据误差')

    plt.subplot(2, 2, 3)
    plt.plot(x, epsilon_1)
    plt.title('误差相对积分值的大小')

    plt.subplot(2, 2, 4)
    plt.plot(x, epsilon_2)
    plt.title('误差相对累加和的大小')

    plt.show()
