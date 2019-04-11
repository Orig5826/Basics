import time

# -------------------------------------
def calc_sum(*args):
	ax = 0
	for n in args:
		ax = ax + n
	return ax
	
# ret = calc_sum(1,2,3,4,5)
a = (1,2,3,4,5)
ret = calc_sum(*a)	# 和上面的传参方式本质上是一样的
print(ret)

# -------------------------------------
"""
	“闭包（Closure）”的程序结构
注意：
返回函数不要引用任何循环变量，或者后续会发生变化的变量。
-> 该问题后续可以再研究
"""
def calc2_sum(*args):
	def sum():
		ax = 0
		for n in args:
			ax = ax + n
		return ax
	return sum	#返回求和函数
	
ret = calc2_sum(*a)
print(ret)
print(ret())
print('')

# -------------------------------------
"""
	装饰器
函数调用前后添加内容，但又不希望修改原函数的定义，这种在代码运行期间动态增加功能的方式，称之为“装饰器”（Decorator）
"""

def log(func):
	def wrapper(*args, **kw):
		print('[ start time ] ' + time.strftime("%Y-%m-%d %H:%M:%S", time.localtime()))
		
		# return func(*args, **kw)
		func(*args, **kw)
		
		print('[  end  time ] ' + time.strftime("%Y-%m-%d %H:%M:%S", time.localtime()))
		
	return wrapper

# 装饰器
@log
def test_fun():
	print('test_fun ok!')


test_fun()
print('当前函数名称：' + test_fun.__name__)
print('')


# -------------------------------------
"""
	偏函数
"""
import functools
def int2(x,base=2):
	return int(x,base)
print(int2('10010'))

# 偏函数的用法，不用再重新定义一个函数
# 直接采用这种方式将原函数的某些参数固定
# 方便后续调用
int2 = functools.partial(int,base=2)
print(int2('10010'))
