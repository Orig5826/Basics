# Built-in

### 基于python3.7
- abs(-0.1)
- all(iterable)
	> 若参数全部为真，则返回True
- any(iterable)
	> 若参数有一个为真，则返回True
- assic(object)
	> 返回assic表示
```
	>>> data = '\x35\x41bc好\u597d\x00'
	>>> ret = ascii(data)
	>>> print(ret)
	'5Abc\u597d\u597d\x00'
```
- bin(x)
	> 将整数x转化为以0b开头的二进制字符串
	- 若不需要0b，则可以采用以下两种方式之一
		1. print(format(data,'b'))
		2. print(f'{data:b}')
		> 若b前面添加#，则保留0b
- bool([x])
	> 返回True/False。x使用Truth Value Testing进行了转换
- breakpoint
	> ?
- bytearray
	> 内容可变
	- 若参数是字符串，则需要通过str.encode('utf-8')指定编码参数
	- 若是整数list，则范围为[0,256)
- bytes
	> 内容不可变
	- bytearray和bytes的区别，类似于list和tuple的区别
- callale(object)
	> ?
- chr(i)
	> The valid range for the argument is from 0 through 1,114,111 (0x10FFFF in base 16).
	- 和ord的作用的相反的
```
data = [48,0x41,0x597d]
for i in data:
    ret = chr(i)
    print(ret,end=' ')
```
- @classmethod
	> 将方法转换为类方法？
- compile
	> ?
- complex([real[,image]])
	> 复数
	- a = 3 + 4j
	- b = complex('3 + 4j')
	- c = complex(3, 4)
- delattr
	> delattr(x,'foo')相当于del x.foo
- dict
- dir
	> 若没有参数，则显示当前局部作用域的名称列表
	> dir(numpy)，显示
	
	
- round
	> 四舍五入
	- round(20.15,1) 结果为 20.1 ?可以查看py文档详细了解原因
	- round(121.15,-1) 结果为 120.0
- set
- setattr
- slice
	> 切片
```
# s = slice(10)
# s = slice(10,20)
s = slice(0,30,5)
data = range(30)
r = data[s]
print(tuple(r))
```
- sorted
- @staticmethod
	> ?
- str
- sum
- super
	> ?
- tuple
- type
- vars
	> 返回带有__dict__属性的模块、类、实例或任何其他对象的__dict__属性。
- zip
	> ?
