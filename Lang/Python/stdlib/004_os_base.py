
import sys
import os


# 注意下这两个的区别
print(os.name)
print(sys.platform)

# print(os.uname())	# invalid in Windows Platform

# 环境变量
# print(os.environ)

"""
		系统目录
"""
print(os.path.abspath('.'))
# 在某目录下创建一个新目录,windows下没有反应？
# ret = os.path.join('.', 'py_dir_test')
# print(ret)

path = 'py测试目录'
if not os.path.exists(path):
	os.mkdir(path)
	print(path + '创建成功')
	os.system('pause')
	
if os.path.exists(path):
	os.rmdir(path)
	print(path + '删除成功')

path = r'E:\code\CodeBase\Lang\py_test\022_doctest.py'
# 一般用于分割目录和文件
ret = os.path.split(path)
print(ret)
# pathname,filename = os.path.split(path)
# print(pathname,filename)

# 用于直接获取文件后缀
ret = os.path.splitext(path)
print(ret)

os.mk('a.txt')
os.rename('a,txt','b.txt')
os.remove('a.txt')

# 文件过滤 -> 列出当前目录下所有目录
# [x for x in os.listdir('.') if os.path.isdir(x)]

# 文件过滤 -> 列出当前目录下所有python文件
# [x for x in os.listdir('.') if os.path.isfile(x) and os.path.splitext(x)[1]=='.py']

