
result = map(lambda x, y: x + y, range(10), range(10, 0, -1))
print(list(result))

result = filter(lambda x: abs(x) >= 2, [-5, -2, -1, 0, 1, 2, 5])
print(list(result))

# 哈哈，又找到一种方式，可以直接将列表中的每一个数字变为str
result = map(str, [1, 2, 3, 4, 5])
print(list(result))

result = map(int, '12345')
print(list(result))
