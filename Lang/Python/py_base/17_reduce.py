
from functools import reduce

"""
	1.0 reduce 在str逆序上的应用，参考文件14_str2.py
"""

"""
#	2.0 
# 另一个经典应用
# 实现[1,2,3,4] ->  (int)1234
"""
def fn(x, y):
	return x*10 + y
	
ret = reduce(fn,[1,2,3,4])
print(type(ret))
print(ret)

"""
#	2.1
# 结合map再进一步应用应用
# 实现'1234' -> (int)1234
"""
def str2int(s):
	# def fn(x, y):
	# 	return x*10 + y
	def char2num(s):
		return {'0': 0, '1': 1, '2': 2, '3': 3, '4': 4, '5': 5, '6': 6, '7': 7, '8': 8, '9': 9}[s]
	# return reduce(fn,map(char2num,s))
	return reduce(lambda x,y: x*10+y,map(char2num,s))
	
ret = str2int('1234')
print(type(ret))
print(ret)
