
# 1.0 打印 9*9 乘法表
for i in range(1, 10):
    for j in range(1, 10):
        if i >= j:
            print('{}*{}={}'.format(j, i, j*i), end=' ')
        if i == j:
            print('')


# 2.0 打印 9*9 乘法表
for i in range(1, 10):
    for j in range(1, i+2):
        if i >= j:
            print('{}*{}={}'.format(j, i, j*i), end=' ')
        else:
            print('')

# 3.0 一行代码打印 9*9 乘法表
[[print('{}*{}={}'.format(i, j, i*j), end=' ') if i >= j else print('')
  for j in range(1, i+2)] for i in range(1, 10)]
