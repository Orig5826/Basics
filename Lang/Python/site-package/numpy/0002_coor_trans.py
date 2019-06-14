
import numpy as np


def coor_trans(point, theta):
    """
        theta方向：以顺时针旋转为正
    """
    if len(point) != 2:
        return False
    point = np.transpose(point)
    k = np.array([[np.cos(theta), np.sin(theta)],
                  [-np.sin(theta), np.cos(theta)]])
    return np.dot(k,point)


if __name__ == "__main__":
    point = np.array([1, 2])
    print(point)
    point_trans = coor_trans(point, np.pi / 2)
    print(point_trans)
