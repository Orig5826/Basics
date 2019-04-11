
result = map(lambda x, y: x + y, range(10), range(10, 0, -1))
print(list(result))

# 哈哈，又找到一种方式，可以直接将列表中的每一个数字变为str
result = map(str, [1, 2, 3, 4, 5])
print(list(result))

result = map(int, '12345')
print(list(result))


"""
应用
对指定序列做映射
# py2返回的是list
# py3返回的是iter
"""
def disp(a):
	print(a)
	for i in a:
		print(i,end=' ')
	print('\n')

def multi(x):
	return x * x
	
a = [1,2,3,4,5]
# ret = multi(a)
ret = map(multi,a)
disp(ret)



"""
	filter 函数较好理解，就不再单独列文件了
	除非遇到经典用法
"""
result = filter(lambda x: abs(x) >= 2, [-5, -2, -1, 0, 1, 2, 5])
print(list(result))

