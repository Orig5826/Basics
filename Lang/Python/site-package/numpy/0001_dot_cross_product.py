
from scipy.spatial.distance import pdist
import numpy as np


def get_module(x):
    """
        x为需要求长度的向量
        欧拉距离/欧式距离(Euclidean Distance)
    """
    return np.sqrt(np.sum(np.square(x)))


def get_angle(x, y):
    """
        一维数据，dot点乘，对数学而言即为求取其数量积
    """
    return np.arccos(np.dot(x, y)/(get_module(x)*get_module(y)))


def get_mudule_len_by_dot():
    print('----- 通过数量积求模长 ----- ')
    # --------------------------------
    # 纯numpy(数学)方式
    OA = np.array([3, 0])
    OB = np.array([0, 4])
    AB = OB - OA  # 指向被减数
    # 长度
    d = get_module(AB)
    print('mlen = ', d)

    # -------------------------------
    # numpy + scipy方式
    xy = np.vstack([OA, OB])
    print(xy)
    dist = pdist(xy)
    print('mlen = ', dist[0])


def get_angle_by_cross():
    """
        已知M(1,1,1),A(2,2,1),B(2,1,2)
        求角度AMB
    """
    print('----- 通过向量积求角度 ----- ')
    M = np.array([1, 1, 1])
    A = np.array([2, 2, 1])
    B = np.array([2, 1, 2])
    MA = A - M
    MB = B - M
    angle = get_angle(MA, MB)
    print(angle)
    if angle - np.pi/3 < 0.0001:
        print('数量积结果正确')


def get_triangle_area_by_cross():
    """
        已知三角形三点坐标，A，B，C坐标点。
        求三角形面积
    """
    print('----- 通过向量积求三角形面积 ----- ')
    A = np.array([1, 2, 3])
    B = np.array([3, 4, 5])
    C = np.array([2, 4, 7])
    AB = B - A
    AC = C - A
    # 面积
    AB_AC = 1/2 * np.cross(AB, AC)
    S = get_module(AB_AC)
    print(S)
    if S - np.sqrt(14) < 0.0001:
        print('向量积结果正确')


if __name__ == "__main__":
    get_mudule_len_by_dot()
    get_angle_by_cross()
    get_triangle_area_by_cross()
