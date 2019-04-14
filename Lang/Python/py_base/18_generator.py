
"""
# 列表生成式，直径生成会直接占用大量空间(若数据较大的话)
a = [x*x for x in range(5)]
# 而此时，生成器的优势便体现出来了
                1.0 生成器

留个问题：
send和next的区别
"""


def disp(a):
    print(a)
    for i in a:
        print(i, end=' ')
    print('\n')

# 创建generator方式二
# 针对相对复杂一些的逻辑，将函数返回直接作为生成器


def fib(max):
    n, a, b = 0, 0, 1
    while n < max:
        # print(b,end=' ')
        # 执行过程中，遇到yield就中断。直到next之后才继续执行
        yield b
        a, b = b, a + b
        n = n + 1


# 创建generator方式一
a = (x*x for x in range(5))
# print(next(a))
disp(a)


a = fib(6)
# print(next(a))
disp(a)


"""
                2.0 迭代器
注意：list，str等可迭代，但其本质不是迭代器。
但可以通过iter转换。

Iterator对象表示的是一个数据流
"""

a = fib(6)

# 以下代码和disp中的某些代码
# 在本质上是同一种行为
while True:
    try:
        print(next(a), end=' ')
    except StopIteration:
        # 遇到StopIteration就退出循环
        print('\n')
        break

print(type(a))
b = [1, 2, 3, 4, 5]
print(type(b))
c = iter(b)
print(type(c))
