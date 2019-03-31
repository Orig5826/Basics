
from functools import reduce

def str_reverse():
    name = '我比较喜欢使用Visual Studio Code，微软还是很厉害的'
    # 逆序
    print(name[::-1])   # 1.0 字符串切片

    ll = list(name)
    ll.reverse()
    print(''.join(ll))  # 2.0 利用list进行逆序


    # 注意： py3中reduce已经不是全局函数了
    # 它被放置在functools中
    result = reduce(lambda x, y: y+x, name)  # 3.0 reduce方式
    print(result)

    """
    reduce 函数相关说明：
    用传给 reduce 中的函数 function（有两个参数）先对集合中的第 1、2 个元素进行操作，
    得到的结果再与第三个数据用 function 函数运算，最后得到一个结果。

    例如：
    # 简单的示例 1.0 
    def add(a, b):
        return a + b
    result = reduce(add, [1, 2, 3, 4, 5])
    print(result)

    # 需要思考的示例 2.0 
    result = reduce(lambda x, y: x - y, [1, 2, 3])
    print(result)
    # r1 = 1 - 2
    # r2 = r1 - 3

    result = reduce(lambda x, y: y - x, [1, 2, 3])
    print(result)
    # r1 = 2 - 1
    # r2 = 3 - r1

    # 至于利用reduce我觉得看完2.0示例之后应该就没有问题了
    """

    # 4.0 操作
    # 诸如循环，栈操作，递归等。这些操作和C语言类似，就不再一一列举


def list_str():
    ll = '1,2,3'.split(',')
    print(ll)
    ss = ','.join(['1', '2', '3'])
    print(ss)

