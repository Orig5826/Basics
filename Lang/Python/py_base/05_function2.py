
"""
	python 是顺序执行的
	若遇到函数，则将函数添加到属性中，暂不调用。
	等到实际执行的时候，才会寻找函数来调用。
	其中，dir()函数的作用是：返回当前范围内的变量、方法和定义的类型列表
	举例如下
"""
def test():
	print('222')
	fun()
	
print(dir())	
# test()	# 若在此处调用，则会在打印完222之后报错

def fun():
	print('111')

print(dir())
test()
