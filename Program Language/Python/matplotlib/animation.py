# -*- coding: utf_8 -*-
# 注意，使用utf-8的文件，添加中文。必须包含上述
# 文件编码类型声明
import numpy as np;
import matplotlib.pyplot as plt;
from matplotlib import animation

#animation
fig = plt.figure()
ax = plt.axes(xlim=(0, 2), ylim=(-2, 2))
# create simply plot an empty line
# 注意加逗号的作用，表示其为tuple的对象
line, = ax.plot([],[],lw=2)
line2, = ax.plot([],[],lw=2)

def init():
	line.set_data([],[])
	line2.set_data([],[])
	return line,line2,

def animate(i):
	x = np.linspace(0,2,1000);
	y = np.sin(2 * np.pi * (x-0.01*i))
	y2 = np.cos(2 * np.pi * (x-0.01*i))
	line.set_data(x,y)
	line2.set_data(x,y2)
	return line,line2,
	
anim = animation.FuncAnimation(fig,animate,init_func=init,
								frames=200,interval=20,blit=True)

# 若是生成im.mp4似乎需要ffmpeg支持。
# 此处就先保存为*.htm/*.html看下效果
anim.save('im.htm', metadata={'artist':'Guido'})							
plt.show()