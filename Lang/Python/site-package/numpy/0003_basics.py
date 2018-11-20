
import numpy as np


def basics_00():
    a = np.array([1, 3, 5, 7, 9])
    b = np.array([1, 2, 3, 4, 5])
    print(a * b)
    print(a ** 2)
    # dot product
    print(a.dot(b))
    print(type(a))
    print(a.dtype)
    print(a.shape)


def basics_01():
    d = np.arange(10)
    print(d.sum())
    print(np.min(d))    # 两种方式结果一致
    print(d.max())
    print(d.cumsum())

    x = np.array([[1, 2, 3], [4, 5, 6], [7, 8, 9]])
    print(x.sum())
    print(np.sum(x, axis=0))  # 列sum
    print(x.sum(axis=1))  # 行sum


def basics_02():
    d = np.linspace(0, 100, 11)
    #
    indices = [1, 3, -1]
    print(d[indices])
    print(d[[1, 3, -1]])  # 外[]表示d的下标，内[]表示下标列表
    #
    print(d[:5])
    print(d[d >= 50])
    #
    index = np.where(d >= 50)
    print(index[0])
    print(d[index[0]])

    e = np.array([[1, 2, 3, 4], [5, 6, 7, 8], [9, 10, 11, 12],
                  [13, 14, 15, 16]])
    print(e)
    print(e[1:3, 1:3])
    print(e[3, 2])
    print(e[(3, 2)])
    print(e[[1, 1, 2, 2], [1, 2, 1, 2]])  # 坐标对应(1,1),(1,2),(2,1),(2,2)
    print(e[np.arange(1, 3), 1:3])
    print(e % 2 == 0)


def basics_03():
    a = np.array([[1, 2, 3, 4], [5, 6, 7, 8]])
    b = np.array([0, 1, 0, -1])
    c = np.array([0, 1, 0, -1]).reshape(2, 2)
    # 垂直堆叠
    r = np.vstack([a, b])
    print(r)
    # 水平堆叠
    r2 = np.hstack([a, c])
    print(r2)

    # 方式2（以垂直为例）
    b = np.array([[0, 1, 0, -1]])  # concatenate要求dimension一致
    r3 = np.concatenate((a, b), axis=0)
    print(r3)

    # 方式3（以水平为例）
    r4 = np.r_[a, b]
    print(r4)

    print('-------------应用示例--------------')
    x = np.array([1, 2, 3])
    # repeat以元素为单位扩展
    ret = np.repeat(x, 3)
    print(ret)
    # repeat以数组为单位扩展
    ret2 = np.tile(x, 3)
    print(ret2)
    ret3 = np.r_[np.repeat(x, 3), np.tile(x, 3)]
    print(ret3)


def create_array_function():
    a = np.zeros((3, 3))
    print(a)
    b = np.ones((3, 2))
    print(b)
    c = np.full((3, 3), 9)
    print(c)
    d = np.full_like(b, 6)
    print(d)
    e = np.eye(3)
    print(e)
    r = np.random.random((2, 2))
    print(r)


def dot_cross_product():
    # 1 dimension
    v = np.array([9, 10])
    w = np.array([11, 12])
    print(v.dot(w))     # Two different ways to express
    print(np.dot(v, w))  # ret = 219
    # 2 dimension
    x = np.array([[1, 2], [3, 4]])
    y = np.array([[5, 6], [7, 8]])
    print(np.dot(x, y))  # dot for 2d -> Matrix / vector product
    # ret = [[19,22],[43,50]]


def transpose():
    x = np.array([[1, 2, 3], [4, 5, 6], [7, 8, 9]])
    print(x.T)
    # @attention 1d   .T无效
    y = np.array([1, 2, 3])
    print(y.T)
    # 翻转行&列的方式
    print(x[::-1])      # 翻转行
    print(x[:, ::-1])    # 翻转列


def broadcasting(mode=2):
    """
        默认表示经典用法。其他表示常规用法
    """
    x = np.array([[1, 2, 3], [4, 5, 6], [7, 8, 9], [10, 11, 12]])
    v = np.array([1, 0, -1])
    if mode == 0:
        """
            当数据大时，效率低下
        """
        y = np.empty_like(x)
        for i in range(4):
            y[i, :] = x[i, :] + v
    elif mode == 1:
        vv = np.tile(v, (4, 1))
        y = x + vv
    elif mode == 2:
        """
            广播
        """
        y = x + v
    else:
        y = None
    print(y)


def broadcasting_02(mode=2):
    a = np.array([1, 2, 3])
    b = np.array([4, 5])
    print(a.reshape((3, 1)) * b)


def linalg_demo():
    A = np.array([[2, 1, -2], [3, 0, 1], [1, 1, -1]])
    b = np.transpose(np.array([[-3, 5, -2]]))
    x = np.linalg.solve(A, b)
    print(x)
    # 资料链接
    # https://www.numpy.org.cn/article/basics/numpy_matrices_vectors.html


def float_random_demo():
    a = np.random.random((5, 5))
    np.set_printoptions(precision=3)  # 显示精度3位小数
    np.set_printoptions(threshold=3)  # 最多显示6项，其他项使用省略号
    # np.set_printoptions(threshold=np.nan) # 显示所有项目
    print(a)


def uniformization():
    value = np.random.randint(5, 10, size=16).reshape(4, 4)
    print(value)
    v_max, v_min = value.max(), value.min()
    # 归一化处理
    uniform_value = (value - v_min) / (v_max - v_min)
    print(uniform_value)


if __name__ == "__main__":
    uniformization()
