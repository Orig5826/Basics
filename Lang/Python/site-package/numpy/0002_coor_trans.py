
import numpy as np


def coor_trans(point, theta):
	"""
		coordinate transformation (坐标转换)

		theta方向：以顺时针旋转为正
	"""
	point = np.transpose(point)
	k = np.array([[np.cos(theta), np.sin(theta)],
				  [-np.sin(theta), np.cos(theta)]])
	print(point)
	# return np.dot(k, point)
	return np.round(np.dot(k, point),6)


if __name__ == "__main__":
	point = np.array([[1,0],[1,2],[2,0],[1,0]])
	print(point)
	point_trans = coor_trans(point, np.pi / 2)
	print(point_trans)
