
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
        print(i, end=' ')
    print('\n')


def multi(x):
    return x * x


a = [1, 2, 3, 4, 5]
# ret = multi(a)
ret = map(multi, a)
disp(ret)


"""
    filter 函数较好理解，就不再单独列文件了
    除非遇到经典用法
"""
result = filter(lambda x: abs(x) >= 2, [-5, -2, -1, 0, 1, 2, 5])
print(list(result))


"""
    map 我不能理解的地方，似乎map调用add的时候必须在list之后？

    不同操作观察现象：
    1. 若print(result)， 则add函数中的print不会显示？
        # >> 1，2，3，4，5 (我以为)
        <map object at 0x00000246C5F69A20> （实际上）
    2. 若调用print(list(result))，则显示
        >> 1 2 3 4 5 [1, 2, 3, 4, 5]
"""


def add(x):
    print(x + 1, end=' ')
    return x + 1

print('--------------- 1.0 --------------------')
result = map(add, [0, 1, 2, 3, 4])
print('--------------- 2.0 --------------------')
result.next
# print(result)
# print(list(result))
print('--------------- 3.0 -------------------')
