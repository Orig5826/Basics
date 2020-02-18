import string

content = "Today is the first day of my life, I wake as a child to see the world again. On monarch wings and birthday wonderings, want to put on faces, walk in the wet and cold. And look forward to my growing old, to grow is to change, to change is to be new, to be new is to be young again, I barely remember when."

# 通过空格分割，变成list
word = content.split(' ')

# 去除标点符号
for i in range(len(word)):
	# 去除标点
	word[i] = word[i].rstrip(string.punctuation)
	
# 单词统计
dd = dict()
for w in word:
	if w in dd:
		dd[w] += 1
	else:
		dd[w] = 1
		
# 打印统计结果
print("-----------------------------")
for key in dd:
	print(key,end='')
	print(" : ",end='')
	print(dd[key])
print("-----------------------------")
