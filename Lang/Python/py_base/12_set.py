
# 这种表达的方式不是set，而使dict
# r0 = {}


# -----------------------------------------
def base():
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


def base2():
    r1 = {1, 2, 3, 4}
    r2 = {2, 3}
    r3 = {4, 5, 6}
    print('4 in r1? ', 4 in r1)
    print('5 not in r1? ', 5 in r2)
    # isdisjoint没有交集返回True
    print(r3.isdisjoint(r2))
    print(r3.isdisjoint(r1))

    # 判断子集 & 真子集 issubset
    print('r2是r1的子集么？ ', r2.issubset(r1))
    print(r2 <= r1)
    print(r2 < r1)
    print('r2是r1的子集么？ ', r1.issuperset(r2))
    print(r1 >= r2)
    print(r1 > r2)

    # 交集，并集，差集...的其他表示方式
    # 下面的方式仅仅作为计算，而不改变r1的值
    r = r1.union(r2, r3)
    print('r1,r2,r3的并集', r)
    r = r1.intersection(r2, r3)
    print('r1,r2,r3的交集', r)
    r = r1.difference(r3)
    print('r1 - r3差集', r)
    r = r1.symmetric_difference(r3)
    print('对称差分', r)

    # 使用update的，会同步更新r1的值
    r = r1.copy()
    r.update(r2, r3)
    print('r1,r2,r3的并集', r)
    r = r1.copy()
    r.intersection_update(r2, r3)
    print('r1,r2,r3的交集', r)
    r = r1.copy()
    r.difference_update(r3)
    print('r1 - r3差集', r)
    r = r1.copy()
    r.symmetric_difference_update(r3)
    print('对称差分', r)

if __name__ == "__main__":
    # base()
    base2()
