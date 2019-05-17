
g0 = {	'A': ['B', 'C', 'F'],
		'B': ['C', 'D'],
		'C': ['D'],
		'D': ['C'],
		#'E': ['F', 'D'],
		'E': ['D', 'F'],
		'F': ['C']
		}

def dict2list(dd):
	ll = []
	keys = dd.keys()
	for key0 in keys:
		ll_temp = []
		for key1 in keys:
			if key1 in dd[key0]:
				ll_temp.append(1)
			else:
				ll_temp.append(0)
		ll.append(ll_temp)
	# print(ll)
	return ll


tag = ['A','B','C','D','E','F']
g = [	[0,1,1,0,0,1],
		[0,0,1,1,0,0],
		[0,0,0,1,0,0],
		[0,0,1,0,0,0],
		[0,0,0,1,0,1],
		[0,0,1,0,0,0],
]

def list2dict(ll):
	dd = {}
	for i in range(len(ll)):
		ll_temp = []
		for j in range(len(ll[0])):
			if ll[i][j] == 1:
				ll_temp.append(tag[j])
		dd[tag[i]] = ll_temp
	return dd


if __name__ == '__main__':
	result = dict2list(g0)
	if result == g:
		print('正确')
	else:
		print('错误')
	
	result = list2dict(g)
	if result == g0:
		print('正确')
	else:
		print('错误')
