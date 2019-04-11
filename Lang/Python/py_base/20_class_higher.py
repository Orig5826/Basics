import time

"""
# 这种方式是初学类常用的方式
class Student(object):
	def score(self):
		return self._score

	def set_score(self,value):
		if not isinstance(value, int):
			raise ValueError('score must be an integer!')
		if value < 0 or value > 100:
			raise ValueError('score must between 0 ~ 100!')
		self._score = value
		
s = Student()

s.set_score(100)
print(s.score())

s.set_score(200)
print(s.score())
"""


# 但是以上的类定义方式，再调用的时候
# 通过方法复制，毕竟要写很多的代码
# 不如直接操作变量and复制来的更加便捷 （优势1）
# 并且以下的方式，还保留着对于输入参数的判定 （优势2）
class Student(object):
	
	@property
	def score(self):
		return self._score
	
	@score.setter
	def score(self,value):
		if not isinstance(value, int):
			raise ValueError('score must be an integer!')
		if value < 0 or value > 100:
			raise ValueError('score must between 0 ~ 100!')
		self._score = value
		
s = Student()
# print(dir(s))

s.score = 100
print(s.score)

s.score = 200
print(s.score)
