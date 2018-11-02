
# -------------------------------------------
# 			II. 循环遍历dt
d = {"name1": "Juli", "name5": "Baker", "name3": "Bryce", "name4": "Loski"}
print(type(d))

# 方法1：dict[key]
for key in d:
    print("{}:{}".format(key, d[key]))
print('------------')

# 方法2:解包
for key, value in d.items():
    print("{}:{}".format(key, value))
print('------------')

# 直接显示Key和Value
print(d.keys())
print(d.values())

# 按照key排序
ret = sorted(d.items())  # sorted默认给dict排序是按照key排序的
ret = sorted(d.items(), key=lambda d: d[0])
print(ret)
# 按照value排序
ret = sorted(d.items(), key=lambda d: d[1])
print(ret)
print(type(ret))    # sourted返回的是list

dd2 = dict(ret)
print(dd2)    # dict转换一下即可
