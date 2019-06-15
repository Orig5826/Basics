import numpy as np
import scipy.linalg


def matrix_transform():
    """
        目的是通过矩阵乘法实现变换 ------ 旋转，翻转
        **直接**进行切片操作的此处就不介绍了
    """
    # A = np.array([[1, 2, 3], [4, 5, 6], [7, 8, 9]])
    A = np.arange(1, 10).reshape(3, 3)
    print('----- 原始矩阵 -----\n', A)

    B = np.eye(3)[[2, 1, 0]]
    # C = np.transpose(A)
    C = A.T

    print('----- 上下翻转 ----')
    A1 = B.dot(A)       # 左乘
    print(A1)
    print('----- 左右翻转 ----')
    A2 = A.dot(B)       # 右乘
    print(A2)

    print('----- 旋转180° ----')
    print(np.dot(A1, B))    # rotate180 = filpud + filplr
    print(np.dot(B, A2))    # rotate180 = filplr + filpud

    print('----- 旋转90°(以顺时针为正) ----')
    print(np.dot(C, B))     # rotate90 = transpose + filpud
    print('----- 旋转-90°(以顺时针为正) ----')
    print(np.dot(B, C))     # rotate-90 = transpose + filplr


def matrix_decomposition_lu():
    """
        https://baike.baidu.com/item/lu%E5%88%86%E8%A7%A3/764245?fr=aladdin
        scipy采用'列主元三角分解': A=PLU
        手动计算(高斯消元法): A=LU
    """
    A = np.matrix('2,3; 5,4')
    b = np.matrix('4,3').T

    print('----- LU分解 (返PLU参数)-----')
    p, l, u = scipy.linalg.lu(A)
    print(p)
    print(l)
    print(u)

    print('----- Ax=b (A=PLU) 求解x -----')
    y = np.linalg.solve(np.dot(p, l), b)
    x = np.linalg.solve(u, y)
    print(x)

    print('----- 直接解方程 -----')
    x = np.linalg.solve(A, b)
    print(x)

    """
    # 这个L相当于是上述的PL，形式很怪，此处不采用
    print('----- LU分解 (返LU参数)-----')
    l, u = scipy.linalg.lu(A, permute_l=True)
    print(l)
    print(u)
    """


if __name__ == "__main__":
    # matrix_transform()
    matrix_decomposition_lu()
