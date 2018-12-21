import collections

class node():
	def __init__(self,value=None):
		self.value = value
		# self.parent = None
		self.left = None
		self.right = None
	
	def __str__(self):
		return str(self.value)
	def __repr__(self):
		return str(self)

	def __lt__(self,other):
		return list(self.value.values()) < list(other.value.values())

	def __add__(self,other):
		value1 = list(self.value.values())[0]
		value2 = list(other.value.values())[0]
		temp = node({None:value1+value2})
		return temp
		
def huff(node_list):
	while 1 != len(node_list):
		# print(node_list)
		
		cur_node = min(node_list)
		index = node_list.index(cur_node)
		node_list.pop(index)
		
		cur_node2 = min(node_list)
		index = node_list.index(cur_node2)
		node_list.pop(index)
		
		temp = node((cur_node + cur_node2).value)
		temp.left = cur_node
		temp.right = cur_node2
		node_list.insert(0,temp)

	# 返回root
	return temp
	
def node_disp(t=node()):
	if t == None:
		return
	print(t)
	node_disp(t.left)
	node_disp(t.right)
	# print(t)

def get_weight(t=node(),level=0):
	if t == None:
		return
	if not hasattr(get_weight,'total'):
		"""
			通过这种方式实现，静态变量
		"""
		get_weight.total = 0
	level += 1
	get_weight(t.left,level)
	get_weight(t.right,level)
	level -= 1
	if t.left == None and t.right == None:
		for key,value in t.value.items():
			weight = level * value
			print('the weight of \'{0}\' = {1:d}'.format(key,weight))
			get_weight.total += weight
	return get_weight.total
	
	
# 脚本入口
if __name__ == '__main__':
	dicts = collections.Counter('abcdeabceacecec')
	print(dicts)
	print('----------------')

	node_list = []
	for dic in dicts.items():
		temp = node({dic[0]:dic[1]})
		node_list.append(temp)

	root = huff(node_list)
	node_disp(root)
	print('----------------')
	total_weight = get_weight(root)
	print('----------------')
	print('total_weight = ',total_weight)
