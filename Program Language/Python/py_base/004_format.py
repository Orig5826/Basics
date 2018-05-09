#! python

# # 测试print函数，类似C的方式输出，字符串和数据
# str = 'Aston'
# cipher = 27149
# print("%s's number is %d" % (str,cipher))

# # 测试file相关操作
# fname = input("Please input the file name: ")
# fHandle = open(fname,'r')
# for line in fHandle:
	# print(line,end='')
# fHandle.close()

# -----------------------------------
# 此处b?.py 表示该脚本名称
# 测试命令行 python b?.py 10
# 其实际上相当于执行了fib(10)
# 主要是理解其传参的方式

# def fib(n):
	# a,b = 0,1
	# result = []
	# while b < n:
		# a,b = b,a+b
		# result.append(b)
	# return result

# if __name__ == "__main__":
	# import sys
	# ret = fib(int(sys.argv[1]))
	# print(ret)

	
# -----------------------------------
#			sys
# sys.ps1 存储的是">>>" 即命令输入提示
# sys.ps2 存储的是"..." 即连续输入提示
# -----------------------------------
# import sys
# print(sys.ps1)
# print(sys.ps2)
# 此处不知道为什么不能在脚本里面运行，但是在python
# 解释器中可以执行?



# -----------------------------------
# for x in range(1,11):
	# print(repr(x).rjust(4),repr(x**2).rjust(4),repr(x**3).rjust(4),end=' ')	#一行
	# print("")	#回车

#format的使用
# for x in range(1,11):
	# print("{0:2d} {1:3d} {2:4d}".format(x,x**2,x**3))		#format用法1
# print("the {} of {} is over!".format("test2","format2"))		#format用法2
# print("the {1} of {0} is over!".format("test3","format3"))		#format用法3，【相对】
# print("the {T} of {F} is over!".format(T = "Test4",F = "Format4"))		#format用法4，【绝对】
# 
# ...format 还有很多用法，暂不一一列举，等用到的时候再查看。




# .zfill的使用
# a = "1.2".zfill(5)		#zero fill 用0填充够5个字节
# print(a)

input("请按任意键退出... \n")