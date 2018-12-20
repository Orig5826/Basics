import os
import docx
# 合并后的文档路径
foutname = 'merge.docx'

# 获取分离的文档
index = 0x00
fname = 'split_' + '{0:02x}'.format(0) + '.docx'
new_word = docx.Document()

while os.path.exists(fname):
	print(fname)
	file = docx.Document(fname)
	# 虽然可以保留部分格式，但和原始文档还有有一些差异的。
	# 包括分页位置、表格宽度等
	for element in file.element.body:
		new_word.element.body.append(element)
	index += 1
	fname = 'split_' + '{0:02x}'.format(index) + '.docx'
print('word merge finished!')
new_word.save(foutname)
