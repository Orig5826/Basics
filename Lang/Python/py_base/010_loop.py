
# -------------------------------------------
# 			I. 布尔
# and,or,not,

# -------------------------------------------
# 			II. 循环技巧
c = dict(sape=4139, guido=4127, jack=4098)
for key, value in c.items():
    print(key, value)

# 循环遍历序列时，可以使用枚举函数，在同一个时间检索位置和相应value
for i, v in enumerate([11, 22, 33, 44, 55]):
    print(i, v)

# 若同时循环两个或者超过两个
questions = ['name', 'quest', 'favorite color']
answers = ['lancelot', 'the holy grail', 'blue']
for q, a in zip(questions, answers):
    print('What is your {0}?  It is {1}.'.format(q, a))

# 倒序，可以使用 reversed()
for i in reversed(range(1,10,2)):
    print(i)

# 排序算法sort()
