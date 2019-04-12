

def abs(n):
	'''
	若注释中的交互示例错误，则可以通过doctest模块检测出来
	>>> abs(1)
	1
	>>> abs(-1)
	1
	>>> abs(0)
	0
	'''
	return n if n >= 0 else (-n)
	
	
if __name__ == '__main__':
	import doctest
	doctest.testmod()
