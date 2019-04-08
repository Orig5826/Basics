
import copy

"""
	1. = 相当于引用，地址数据始终保持一致（即一个变化，另一个也变化）
	2. deepcopy 这个也好理解，就是完全的复制。数据地址完全不一样
		>> 注意一点：若被复制的数据为不可变数据，则数据地址不变
	3. copy 浅拷贝，这个需要重点理解下，它仅仅复制当前层，对于它的子集是不做复制的。
		也即子集若是可变的的，那么即便浅拷贝完毕。那么子集内容也会随之变化。
		
	# 个人认为重点理解，python中内存的分配方式，
"""

def copy_test_01():
	a = (1,2,3)
	b = a
	c = copy.copy(a)
	d = copy.deepcopy(a)

	print(a is b)
	print(a is c)
	print(a is d)

	print(a == b)
	print(a == c)
	print(a == d)
	
	print(a)
	print(b)
	print(c)
	print(d)
	
	print(id(a))
	print(id(b))
	print(id(c))
	print(id(d))
	print('-----------01------------')

def copy_test_02():
	a = [1,2,3]
	b = a
	c = copy.copy(a)
	d = copy.deepcopy(a)

	a[0] = 0
	
	print(a is b)
	print(a is c)
	print(a is d)

	print(a == b)
	print(a == c)
	print(a == d)
	
	print(a)
	print(b)
	print(c)
	print(d)
	
	print(id(a))
	print(id(b))
	print(id(c))
	print(id(d))
	print('-----------02------------')
	

def copy_test_03():
	a = [1,2,(3,4,5)]
	b = a
	c = copy.copy(a)
	d = copy.deepcopy(a)

	a[0] = 0
	a[2] = [6,7,8]
	
	print(a is b)
	print(a is c)
	print(a is d)

	print(a == b)
	print(a == c)
	print(a == d)
	
	print(a[2] is b[2])
	print(a[2] is c[2])
	print(a[2] is d[2])
	
	print(a)
	print(b)
	print(c)
	print(d)
	
	print(id(a))
	print(id(b))
	print(id(c))
	print(id(d))
	print('------------03-----------')	

def copy_test_04():

	a = (1,2,[3,4,5])
	c = copy.copy(a)
	d = copy.deepcopy(a)
	print(a)
	a[2][0] = 0
	print(a)
	print(a[2] is c[2])
	print(a[2] is d[2])
	print(a[2][0] is c[2][0])
	print(a[2][0] is d[2][0])
	print(c)
	print(d)
	print('------------04-----------')	

copy_test_01()
copy_test_02()
copy_test_03()
copy_test_04()
