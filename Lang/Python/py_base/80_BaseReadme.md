# 相关知识点说明
`2019.03.31 by jianfeng`

### py2和py3的区别
1. print用法不同
2. py3中字符串可以通过str完成unicode和非unicode转换，不用像py2中使用全局函数unicode强制转换
3. py3中没有long的概念
4. py2中range和xrange，py3中的range
5. py3中没有xreadlines文件操作方式 -> 修改为for line in lines: ... 操作方式

### is 和 == 的区别
- == 用于对比两个变量中的值是否相等
- is 用于对比两个变量是否为同一个对象
```
a = b = [1, 2, 3]
c = [1, 2, 3]
d = a.copy()
print(a is b)   # True
print(a is c)   # False
print(a is d)   # False

print(a == b)   # True
print(a == c)   # True
print(a == d)   # True
```

