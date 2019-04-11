
"""
	自定义的类表现的和list，dict等没有什么区别，
	主要是因为动态语言的"鸭子类型"
	不需要强制继承某个接口
"""

class Fib(object):
	def __init__(self,max):
		self.a = 0
		self.b = 1
		self.max = max
	
	# 结合next实现可迭代对象
	def __iter__(self):
		return self
		
	def __next__(self):
		self.a, self.b = self.b, self.a + self.b
		
		if self.b > self.max:
			raise StopIteration()
		else:
			return self.a
		
	# 类的下标访问 & 切片等操作的实现
	def __getitem__(self, n):
		
		# 下标访问实现
		if isinstance(n, int):
			a, b = 0, 1
			# 考虑到下标从0开始，且为了和iter结果保持一致
			# 因此采用n+1的方式
			for x in range(n+1):
				a, b = b, a + b
			return a
		
		# 切片实现
		if isinstance(n, slice):
			start = n.start
			stop = n.stop
			if start is None:
				start = 0
			a, b = 0, 1
			ll = []
			for x in range(stop):
				a, b = b, a + b
				if x >= start:
					ll.append(a)
			return ll
			
def disp(a):
	print(a)
	for i in a:
		print(i,end=' ')
	print('\n')
	

a = Fib(10000)
disp(a)

print(a[5])
print(a[5:8])
