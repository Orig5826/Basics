import numpy as np

'''
	py卷积计算
'''
a = np.array([1,2])
b = np.array([3,4])
print(a)
print(b)
ret = np.convolve(a,b)
print(ret)

'''
	系数向量内积
'''
c = np.array([[2,1,0,],[0,2,1],[0,0,2]])
d = np.array([0,3,4])
print(c)
print(d)
ret = c.dot(d)
# print(ret)


def lsl(lst,k,cnt):
	temp = np.concatenate((lst[-k:],lst[:-k]),axis=0)
	z = np.zeros(cnt)
	z[k:] = temp[k:]
	return z

def conv(a,b):
	'''
		将卷积转换为矩阵运算
	'''
	l_a = len(a)
	l_b = len(b)
	item_cnt = len(a) + len(b) - 1
	data = np.zeros((item_cnt,item_cnt))
	data2 = np.zeros(item_cnt)
	data2[-l_b:] = b[-l_b:]
	a = a[::-1]
	for i in range(item_cnt):
		data[i][:l_a] = a
		data[i][:] = lsl(data[i],i,item_cnt)
	return np.dot(data,data2.transpose())


ret = conv(a,b)
print(ret)
