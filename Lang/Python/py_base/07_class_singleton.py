
class singleton(object):
	"""
		单例模式
	"""
	instance = None
	def __new__(cls, *args, **kargs):
		if not singleton.instance:
			singleton.instance = object.__new__(cls)
		return singleton.instance
		
a = singleton()
b = singleton()
print(a)
print(b)
