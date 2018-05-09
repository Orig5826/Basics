# **************************************************
# 未进行详细理解的部分：
#
# * 和 ** 的应用场合
# Lambda Forms
# Documentation Strings
# **************************************************
# 基础语法学习
item = int(input("please input item_index: "))

# ----------------------------------		
# 		1.0 修改为函数
# ----------------------------------
def fib(n):
	print("#1.0 测试：斐波那契数列")
	a,b = 0,1
	while b < n:
		print(b,end='  ')
		# 先用C的思路实现了一下
		# t = a
		# a = b
		# b = t+b
		a,b = b,a+b		#a,b=b,a 相当于a和b交换数据
# ----------------------------------		
# 		2.0 带有返回值的函数
# ----------------------------------
def fib2(n):
	"""
		测试：斐波那契数列
	"""
	# print("#1.0 测试：斐波那契数列")
	a,b = 0,1
	result = []
	while b < n:
		result.append(b)
		a,b = b,a+b		#a,b=b,a 相当于a和b交换数据
	return result
# ----------------------------------		
# 		3.0 带有默认参数的函数
# ----------------------------------	
def ask_ok(prompt,retries,complaint = "Are you OK? (yes or no)"):
	while True:
		print(complaint)
		
		ok = input(prompt)
		if ok in ('y','yes'):
			return True
		if ok in ('n','no'):
			return False
		retries = retries - 1
		if retries < 0:
			raise IOError("'refusenik user'")
# ----------------------------------		
# 		5.0 带有默认参数的函数
# ----------------------------------	
def num_append(a,L = []):
	L.append(a)
	return L
def num_append2(a,L = None):
	#
	# 若没有L这个参数时，则L不添加数据
	if L is None:
		L = []
	else:
		L.append(a)
	return L			
# ----------------------------------		
# 		6.0 关键字传参
# 还有一些，复杂一点的应用，但是没看
# 若后续遇到，再来看。
# ----------------------------------				
def adjust(voltage,type="music",state='on'):
	print(type,"音量：",voltage,"开启？",state)

# ----------------------------------		
# 		7.0 参数可变
# ----------------------------------	
def concat(*arg,sep='/'):
	return sep.join(arg)
	
	
# ===========================================================================
# ----------------------------------		
# 				执行...
# ----------------------------------
if item == 1:
	n = int(input("please input 'n' = : "))
	# fib(n)
	print(fib2(n))
	# print(fib2.__doc__)		#仅仅用于显示Documentation
elif item == 2:
	str = ['hello','world','Haha']
	# for x in str:
		# print(x,len(x))
	# 用一下item=3时的range
	# for i in range(3):
		# print(i,str[i])
	
	# * 的使用
	a = [0,3]
	for i in range(*a):
		print(i,str[i])
	
elif item == 3:
	for x in range(1,10):
		for y in range(1,10):
			if x >= y:
				print(x,'*',y,'=',x*y,end='  ')
		print("")

elif item == 4:
	a = ""
	# 默认参数
	ask_ok(a,2,)
	
	str = "like it or not?(y/n)"
	# 默认参数可以被覆盖
	# ask_ok(a,2,str)
	
elif item == 5:
	# 带有L参数的，自己测试一下就可以，和想的一样。
	#
	# 若没有传递L，则L数据本身不会被修改
	L = []
	print(num_append(1))
	print(num_append(2))
	print(num_append(3))
	#
	print("L = ",end='')
	print(L)
	print("---------------")
	
	# 该实现，主要看num_append2
	# 若没有L这个参数，则返回值也不添加a
	L = []
	print(num_append2(1))
	print(num_append2(2))
	print(num_append2(3))
	#
	print("把L打印一下")
	print(L)
	
elif item==6:
	# 利用关键字传参数
	adjust(voltage = 70)
	adjust(voltage = 0,state="off")
	adjust(voltage = 100,type="video")
	#但Voltage这个参数是每次必须传递的
	adjust(0,type="video",state='off')
	adjust(20,state="on")
	
		
	#参数也可以这样修改
	# d = {"voltage":200,"type":"Phone","state":"off"}
	d = {"voltage":200,"type":"Phone"}
	# ** 的用法
	adjust(**d)
elif item==7:
	Data = concat("2017","09","11")
	print(Data,end=' ')
	
	Data = concat("16","29","00",sep=':')
	print(Data,end='   ')
	
	Data = concat("1",sep=' ')
	print("星期",Data)
else:
	print("Hello world!")
