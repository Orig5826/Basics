# data = [1,2,3,4,5,6,7]
data = [2,1,4,6,7,5,3,9,10,8]
print(data)

def heap_min(data):
	length = len(data)
	for i in range(length-1,-1, -1):
		if data[i] < data[i//2]:
			data[i],data[i//2] = data[i//2],data[i]
	return data

def sort(data):
	ll = []
	length = len(data)
	for i in range(0,length):
		data = heap_min(data[:])
		ll.append(data[0])
		del data[0]
		print(data)
	return ll

data = sort(data)
print(data)
