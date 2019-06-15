
import numpy as np

"""
    备注：本示例中所有的matrix都使用的是array来体现
    实际上python中存在专门的matrix

    # 主要注意matrix和array的区别
    # matrix 使用更加接近matlab的使用方式
    简单示例如下：
    B = np.matrix('1,2;3,4')
    print(B*B)
    # 注意：若使用matrix，则*直接表示矩阵乘法
    # 而元素对应乘积则使用 multiply() 函数
"""


def vector_dot():
    a = np.array([1, 3, 5, 7, 9])
    b = np.array([1, 2, 3, 4, 5])
    # 对应元素相乘
    print(a * b)
    # 对应元素2次幂
    print(a ** 2)
    # dot product
    print(a.dot(b))
    print(type(a))
    print(a.dtype)
    print(a.shape)


def array_matrix_sum():
    d = np.arange(10)
    # 求和：针对数组
    print(d.sum())
    # 求最值
    print(np.min(d))    # 两种方式结果一致
    print(d.max())
    # 累加
    print(d.cumsum())

    x = np.array([[1, 2, 3], [4, 5, 6], [7, 8, 9]])
    # 求和：针对矩阵
    print(x.sum())
    print(np.sum(x, axis=0))  # 列sum
    print(x.sum(axis=1))  # 行sum


def array_matrix_slice():
    # start,stop,num
    d = np.linspace(0, 90, 10)
    print(d)
    # start,stop,num,endpoint=False
    d = np.linspace(0, 100, 10, endpoint=False)
    print(d)
    # 切片
    indices = [1, 3, -1]
    print(d[indices])
    print(d[[1, 3, -1]])  # 外[]表示d的下标，内[]表示下标列表
    print(d[:5])
    # 按照条件 切片
    print(d[d >= 50])
    # 按照条件 查找元素下标
    index = np.where(d >= 50)
    print(index[0])
    print(d[index[0]])

    e = np.array([[1, 2, 3, 4], [5, 6, 7, 8], [9, 10, 11, 12],
                  [13, 14, 15, 16]])
    print(e)
    # 矩阵切片方式
    print(e[1:3, 1:3])
    # 选取矩阵中某点
    print(e[3, 2])
    print(e[(3, 2)])
    # 花式索引 --- array[[x],[y]]
    # 坐标对应(1,1),(1,2),(2,1),(2,2)
    # 最终将回去的所有点排成一个一维数组
    print(e[[1, 1, 2, 2], [1, 2, 1, 2]])
    #
    print(e[np.arange(1, 3), 1:3])
    # 返回布尔值，（针对对应元素）
    # 该布尔值也可以用于索引切片
    print(e % 2 == 0)
    print(e[e % 2 == 0])


def array_stack():
    a = np.array([[1, 2, 3, 4], [5, 6, 7, 8]])
    b = np.array([0, 1, 0, -1])
    c = np.array([0, 1, 0, -1]).reshape(2, 2)
    print('-------------堆叠--------------')
    # 垂直堆叠
    r = np.vstack([a, b])
    print(r)
    # 水平堆叠
    r2 = np.hstack([a, c])
    print(r2)

    print('---------堆叠（方式2）----------')
    # 方式2（以垂直为例）
    b = np.array([[0, 1, 0, -1]])  # concatenate要求dimension一致
    r3 = np.concatenate((a, b), axis=0)
    # r3 = np.concatenate((a, c), axis=1)
    print(r3)

    print('---------堆叠（方式3）----------')
    # 方式3（以水平为例）
    # r4 = np.r_[a, b]  # 垂直堆叠
    r4 = np.c_[a, c]
    print(r4)

    print('-------------扩展--------------')
    x = np.array([1, 2, 3])
    # repeat以元素为单位扩展
    ret = np.repeat(x, 3)
    print(ret)
    # repeat以数组为单位扩展
    ret2 = np.tile(x, 3)
    print(ret2)
    ret3 = np.r_[np.repeat(x, 3), np.tile(x, 3)]
    print(ret3)


def create_matrix():
    a = np.zeros((3, 3))
    print(a)
    b = np.ones((3, 2))
    print(b)
    # 用9填充3*3的矩阵
    c = np.full((3, 3), 9)
    print(c)
    # 用6填充类似b的矩阵
    d = np.full_like(b, 6)
    print(d)
    e = np.eye(3)
    print(e)
    r = np.random.random((2, 2))
    print(r)


def dot_product():
    # 针对 1 dimension
    # 此时dot作用类似于inner(内积)
    # 作用式：两向量数量积
    v = np.array([9, 10])
    w = np.array([11, 12])
    print(v.dot(w))         # Two different ways to express
    print(np.dot(v, w))     # ret = 219

    # 针对 2 dimension
    # 作用是：矩阵乘法
    x = np.array([[1, 2], [3, 4]])
    y = np.array([[5, 6], [7, 8]])
    print(np.dot(x, y))  # dot for 2d -> Matrix / vector product
    # ret = [[19,22],[43,50]]

    # 针对 矩阵
    # 作用是：矩阵乘法
    x = np.array([[1, 2, 3], [4, 5, 6], [7, 8, 9]])
    print(x)
    y = np.eye(3)
    y[(1, 0)] = 2   # 用矩阵描述 矩阵消元法（高斯消元法）
    print(y)
    print(np.dot(y, x))


def matrix_transpose():
    x = np.array([[1, 2, 3], [4, 5, 6], [7, 8, 9]])
    print(x.T)
    # @attention 1d   .T无效
    y = np.array([1, 2, 3])
    print(y.T)

    # 翻转行&列的方式
    print(x[::-1])          # 翻转行
    print(x[:, ::-1])       # 翻转列


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

    """
        广播应用2
    """
    a = np.array([1, 2, 3])
    b = np.array([4, 5])
    c = a.reshape((3, 1))
    print(c)
    print(c * b)


def linalg_demo():
    # 资料链接
    # https://www.numpy.org.cn/article/basics/numpy_matrices_vectors.html

    print('----- 解线性方程组 -----')
    A = np.array([[2, 1, -2], [3, 0, 1], [1, 1, -1]])
    b = np.transpose(np.array([[-3, 5, -2]]))
    x = np.linalg.solve(A, b)
    print(x)
    # 查看一些结果，看是否正确
    print(A.dot(x))

    print('----- 求矩阵的逆 -----')
    C = np.linalg.inv(A)
    # 使用round的目的是，让特别小的数，例如1.11e-16显示为0
    print(C)
    print(np.round(C, 6))
    ret = C.dot(A)
    print(np.round(ret, 6))

    print('----- 计算行列式 -----')
    # 方式1
    # D = np.array([[3, 4], [5, 6]])
    # E = np.asmatrix(D)
    # 方式2
    E = np.mat('3,4; 5,6')
    print(E)
    ret = np.linalg.det(E)
    print(np.round(ret, 6))


def float_random_demo():
    a = np.random.random((10, 10))
    np.set_printoptions(precision=3)  # 显示精度3位小数
    np.set_printoptions(threshold=3)  # 最多显示6项，其他项使用省略号
    # np.set_printoptions(threshold=np.nan)   # 显示所有项目
    print(a)


def uniformization():
    value = np.random.randint(5, 10, size=16).reshape(4, 4)
    print(value)
    v_max, v_min = value.max(), value.min()
    # 归一化处理
    uniform_value = (value - v_min) / (v_max - v_min)
    print(uniform_value)


if __name__ == "__main__":
    # vector_dot()
    # array_matrix_sum()
    # array_matrix_slice()
    # array_stack()
    # create_matrix()
    # dot_product()
    # matrix_transpose()
    # broadcasting(0)
    # linalg_demo()
    # float_random_demo()
    uniformization()
