import random
import copy

''
# 1.0 python中三元表达方式
# a = 1 > 3 ? '我的' ： '你的'  # C语言示例，在python中不适用
num = -1
a = '正数' if num > 0 else '负数'  # python中类似的替代方式
print(a)

# 2.0 range和xrange
# b = xrange(1, 10, 2)    #python3没有该函数，python3中的range即为该作用
# python2中range返回的是list，直接分配空间，性能相对较低
# python2中xrange返回的是一个迭代器
# python3取消了原range的用法。py3中的range相当于py2中的xrange -> 返回一个类型为<class 'range'>的对象。
a = range(1, 10, 2)
print(a)
print(type(a))


# 3.0 copy模块下的copy和deepcopy的区别
a = [1, 2, [3, 4]]
b = a                   # 引用
c = copy.copy(a)        # 若a存在子对象，则无法完全复制子对象内容
d = copy.deepcopy(a)    # 符合我们的直面理解，复制就是全部的独立
a[2][0] = 'a'
a[0] = 'b'
print(b)
print(c)
print(d)


# 4.0 将顺序列表打乱顺序
alist = list(range(10))
print(alist)
random.shuffle(alist)   # 打乱顺序
print(alist)
