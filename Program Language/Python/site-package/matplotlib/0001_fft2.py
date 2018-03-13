# 安装：pip3.6 install opencv-pytho
import cv2
import numpy as np;
import matplotlib.pyplot as plt;

# ------------------------------
# 1.0读入图片
plt.figure('a beautiful girl')
beauty = cv2.imread('beauty.jpg',0)
plt.subplot(221)
plt.imshow(beauty,'gray')

# ------------------------------
# 1.1 fft2变换
y = np.fft.fft2(beauty)
y = np.fft.fftshift(y)
y1 = np.log(np.abs(y))
plt.subplot(222)
plt.imshow(y1,'gray')

# -------------------------------
# 2.0 插入滤波器
# 边上是1，是高通
# 中心是1，是低通
row,col = beauty.shape
mask = np.zeros(beauty.shape,np.uint8)
radius = 20
# 这里使用//是因为整数除法，若直接/是小数除法
mask[row//2-radius:row//2+radius,col//2-radius:col//2+radius] = 1
y2 = y*mask
y2 = np.fft.ifftshift(y2)	#...?

# -------------------------------
# 2.1 ifft2逆变换
x1 = np.fft.ifft2(y2)
plt.subplot(223)
x1 = np.abs(x1)
plt.imshow(x1,'gray')

# 2.2 mask图像
plt.subplot(224)
mask2 = np.abs(mask)
plt.imshow(mask2,'gray')

plt.show()


