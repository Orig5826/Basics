from tree import Node

n1 = Node(1)
print(n1)

n2 = Node(2)
print(n2)


n1, n2 = n2, n1
print('n1 = ',n1)
print('n2 = ',n2)

print(n1 < n2)
print(n2 > n1)
print(n2 != n1)
