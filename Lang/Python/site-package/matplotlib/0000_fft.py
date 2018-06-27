import numpy as np
import matplotlib.pyplot as plt
# -------------------------
# 采样频率
Fs = 50
N = 1024
# -------------------------
# 数据--->采集的用来计算频率的数据
# Note:此处对N/Fs做一下解释：
# 一共采样了N个点，每个点的时间为1/Fs
# 因此此处采用N*1/Fs的方式
t = np.linspace(0, N/Fs, N)
# 直流
A0 = 5
# 波形1
A1 = 4
f1 = 1  # 1Hz
# 波形2
A2 = 2
f2 = 3  # 3Hz
# x = A1*np.sin(2*np.pi*f1*t) 		#用标准sin测试一下
# x = A0 + A1*np.sin(2*np.pi*f1*t) + A2*np.sin(2*np.pi*f2*t)
x = A0 + A1*np.sin(2*np.pi*f1*t) + A2*np.sin(2*np.pi *
                                             f2*t) + (-5)*np.random.random(N)

# --------------------------
# 进行fft变换
y = np.fft.fft(x)
freq = np.fft.fftfreq(N, d=(t[0]-t[1]))

# -----------------------------------
# 能不能将高频率的波形滤掉
# 直接删除可好？----这个...太简洁了吧？
# ------------------------------------
# 定义一个滤波函数


def filter(freq, ft, flag=0, threshold=5):
    for i in range(N):
        if flag == 1:
            # 滤掉直流
            if np.abs(freq[i]) == 0:
                ft[i] = 0
        elif flag == 2:
            # 滤掉低频部分
            if np.abs(freq[i]) < threshold and np.abs(freq[i]) != 0:
                ft[i] = 0
        elif flag == 3:
            # 滤掉高频部分
            if np.abs(freq[i]) > threshold:
                ft[i] = 0
        elif flag == 4:
            # 尝试滤掉低振幅的杂波
            # 效果不是很好？是不是方法太low？
            if np.abs(ft[i])/N < 0.2:
                ft[i] = 0
        elif flag == 5:
            # 若已经知道当前最大频率
            # 则再高的频率直接滤掉
            # 相对于方法4而言，效果要好一些
            if np.abs(freq[i]) > 3.5:
                ft[i] = 0
        else:
            print("no filter")


# --------------------------
# 1.0 显示原始图形
plt.subplot(411)
plt.axis([0, 10, -10, 10])
plt.plot(t, x, 'b')


# 1.1 频谱
plt.subplot(412)
y1 = np.abs(y)/N  # 显示绝对值
plt.plot(freq, y1, 'r')

# --------------------------
# 滤波
filter(freq, y, 5, threshold=2)
# 进行ifft反变换
x2 = np.fft.ifft(y)

# 1.1 频谱
plt.subplot(413)
y1 = np.abs(y)/N  # 显示绝对值
plt.plot(freq, y1, 'r')

# 2.1fft逆变换之后
plt.subplot(414)
plt.axis([0, 10, -10, 10])
plt.plot(t, x2.real, 'b')  # 直接x2这里有warning，是不是应该x2.real
# 因为x2为Complex

plt.show()
