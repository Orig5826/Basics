
# 从本质上而言，turple内容不可变，在定义的时候便已经确定下来了
a = (1)
print(a)	#1. 此处的括号就仅仅是括号
a = (1,)
print(a)	#2. 此处添加了逗号，则表示turple
a = 1,
print(a)	#3. 同2

# a[0] = 5  #4. turple内容不可变

b = (1,[2,3])
print(b)
b[1][0] = 4
b[1][1] = 5
print(b)	#5. 这里修改的不是trple内容，而是他的元素list的内容
print(len(b))
			#6. 同样，凡是涉及到修改内容的方法都不支持
			#	比如list支持的append等
			
