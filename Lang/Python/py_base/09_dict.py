
# -------------------------------------------
# 			I. 创建dict
a = {}			# 创建空dict
print(a)
a.setdefault('name', 'cat')
print(a)

# 1.0 利用{}来构建字典
b = {'name': 'ball', 'radius': 0.05, 'color': 'white'}
print(b)
print(b.keys())		# 返回所有关键字列表
print(b.values())  # 返回所有Value列表

print('color' in b)
del b['color']		# 删除key='color'的项
print(b)
print('color' in b)

print(list(b))		# 列出所有key

# 2.0 利用key-value对，来构建dict
c = dict([('sape', 4139), ('guido', 4127), ('jack', 4098)])
print(c)
# 当key仅为简单的字符串时，也可以使用如下方式创建
c = dict(sape=4139, guido=4127, jack=4098)
print(c)

# 3.0 利用表达式等方式创建
d = {x: x**2 for x in range(1, 5)}
print(d)
