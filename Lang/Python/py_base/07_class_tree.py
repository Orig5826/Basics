
class tree():
	def __init__(self,value=None):
		self.value = value
		self.parent = None
		self.left = None
		self.right = None
	
	def __str__(self):
		"""
			>> a = tree([1,2,3])
			>> print(a)
			[1,2,3]
		"""
		return str(self.value)
	def __repr__(self):
		"""
			# 结合__str__使用，主要用于命令行下直接输入变量，
			# 显示__str__下的内容，否则显示为地址
			>> from test import tree
			>> a = tree([1,2,3])
			>> a
			[1,2,3]
		"""
		return str(self)
