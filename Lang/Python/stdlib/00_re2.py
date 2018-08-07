
import re
subject = '002d010070f1341217a1c6beae9779538cab5edbd8876539ab50aa2d67a2867328c605755a02a73860403aabe35cabf20a88a87e81beaab190836fd4572722a027b8ad3962508f41c9be3589e9e48ceba913845bb497b4157992c74f67be02a8db62ac7855e552b8d6efc1c3d7157ef1dfc0797bae70'
# 每2个字符，添加一个空格
ret = re.sub(r"(?<=\w)(?=(?:\w\w)+$)", " ", subject)
print(ret)

'''
``` 简单的使用此处不再列举，此处主要针对**分组语法**进行说明 ```
### 捕获
- (exp)
	> 匹配exp，并捕获文本到自动命名的组里
- (?<name>exp) 或者 (?'name'exp)
	> 匹配exp，并捕获文本到名称为name的组里
- (?:exp)
	> 匹配exp，不捕获匹配的文本
### 位置指定
- (?=exp)
	> 匹配exp前面的位置
- (?<=exp)
	> 匹配exp后面的位置
- (?!exp)
	> 匹配exp后面跟的不是exp的位置
- (?<!exp)
	> 匹配前面不是exp的位置
- (?#comment)
	> 这个类型不对正则表达式产生影响，就是个注释
'''

### ------ 举例子说明 ------
subject = '''
def SendData(data):
def GetData(data):
def SendString():
def GetString():
def SendHex():
def GetHex():
'''
# print(subject)
# 显示Send
ret = re.findall(r".*(Send).*",subject)
print(ret)
# 为什么也显示Send？不是说不捕获吗？
# 是不是我理解错这个“捕获”的含义了?
ret = re.findall(r".*(?:Send).*",subject)
print(ret)
# 仅仅捕获了SendData的Send
ret = re.findall(r".*Send(?=Data).*",subject)
print(ret)
# 仅仅捕获了SendHex中的Hex
ret = re.findall(r".*(?<=Send)Hex.*",subject)
print(ret)
# 仅仅捕获了非SendData的Send*
ret = re.findall(r".*Send(?!Data).*",subject)
print(ret)
# 仅仅捕获非SendHex的*Hex
ret = re.findall(r".*(?<!Send)Hex.*",subject)
print(ret)
# 正则表达式中的注释
ret = re.findall(r".*(?#Send)Hex.*",subject)
print(ret)
