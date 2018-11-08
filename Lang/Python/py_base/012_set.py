
# 这种表达的方式不是set，而使dict
# r0 = {}


# -----------------------------------------
r0 = set()
print("-> 空集", r0)

r1 = {1, 2, 3, 4}
r2 = {2, 3, 5, 6}
print("-> 集合r1 ", r1)
print("-> 集合r2 ", r2)

r = r1 & r2
print("交集 ", r)
r = r1 | r2
print("并集 ", r)
r = r1 - r2
print("相对补集/差集r1-r2 ", r)
r = r2 - r1
print("相对补集/差集r2-r1 ", r)

r3 = {1, 2}
print("-> 集合r3 ", r3)
print("r3是r1的子集？", r3.issubset(r1))
print("r3是r2的子集？", r3.issubset(r2))

r = r1 ^ r2
print("对称差集/差分 ", r)
r = (r1 | r2) - (r1 & r2)
print(r)

# ------------------------------------------
fr1 = frozenset({1, 2, 3, 4, 5})
# fr1.add(6) 失败
# frozenset得到的集合，不可修改
