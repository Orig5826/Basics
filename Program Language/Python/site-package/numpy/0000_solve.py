# ----------------------------
# 1.0 学习一下numpy怎么使用
# ----------------------------

item = int(input("请输入项目编号："))

# if item == 1:
	# import numpy as np
	# # 求解一元高次函数
	# print("求解x^2+2x+1=-1")
	# a = [1,2,2]
	# b = np.roots(a)
	# print(b)
	

# ----------------------------
# 2.0 学习一下，两种import的方式的区别
# ----------------------------
from numpy import *
if item == 1:
	ret = roots([1,2,1])
	print(ret)
	
elif item == 2:
	a = [[1,2],[2,-1]]
	print(a)
	b = [4,3]
	print(b)
	print("\n求解多元一次方程组")
	print("x+2y=4")
	print("2x-y=3")
	print("结果为:")
	result = linalg.solve(a,b)
	print(result)
elif item == 3:
	x = arange(6)
	print(x)
	x = x.reshape((2,3))
	print(x)
elif item == 4:
	x = zeros(9)
	y = ones((2,6))
	print(x)
	print(y)
elif item==5:
	x = linspace(0,pi,10)
	print(x)
elif item==6:
	import math
	x = random.rand(2,3)
	print(x)
	y = (x * 10)%6 + 1
	print(y)
	y = floor(y)
	print(y)
else:
	print("the number is error!")