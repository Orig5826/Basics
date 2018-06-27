#
# 本脚本不用于执行，进作为学习备份
# --------------------------------
# range
range(5) => 0,1,2,3,4
range(5,9) => 5,6,7,8
range(10,50,20) => 10,30
#-------------
# 常用于数组中
a = ['Mary', 'had', 'a', 'little', 'lamb']
for i in range(len(a)):
    print(i, a[i])
#-------------
# 查看range中的数据
list(range(10,-2,-3))

# -----------------------------------------------
# learn the keyworks
# *arguments存放所有未命名的函数(本质是tuple)
# **keywords 存放所有带有关键字的参数(本质是dict)
# 若以上两个同时存在，则带有关键字的参数必须在没有关键字的参数之后
# 例如：
# fun_test("Hello","world",name="orig",age='25',"hha")            #error
# fun_test(hah="Hehe","Hello","world",name="orig",age='25')     #error

# -*- coding: gb18030 -*-
def fun_test(*arguments,**keywords):
    """
    函数的注释，可以通过调用
    "函数名.__doc__"来进行查看
    例如，脚本中
    print(fun_test.__doc__)
    """
    for arg in arguments:
        print(arg,end=' ')
    print('\n--------------------')
    for kw in keywords:
        print(kw,':',keywords[kw])
    print(list(keywords[kw]))

fun_test("Hello","world",name="orig",age='25')
print(fun_test.__doc__)


# -----------------------------------------------
# join方法的使用
pt = '.'
addr = ("255","255","255","0")
ret = pt.join(addr)
print(ret)

# -----------------------------------------------
# 匿名函数的用法
sum = lambda x,y: x+y
print(sum(1,5))

# 
# 命令行下,1.和2.是有区别的，你能猜出来结果吗
pairs = [(2,"aa"),(1,"cc"),(5,"bb")]
# 1.
pairs.sort(key=lambda pair:pair[0])
# 2.
pairs.sort(key=lambda pair:pair[1])


# ------------------------------------------------
# map的使用 map(函数，参数n..)
# [E]命令行下
map(lambda x:x*x , range(10))
list(_)