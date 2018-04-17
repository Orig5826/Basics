# -*- code=utf_8 -*-
import PyPDF2 as pdf

inputfile = r".\i2c.pdf"
outputfile = r".\i2c_out.pdf"
reader = pdf.PdfFileReader(inputfile)
getpages = list()

PageIndexMax = reader.getNumPages()
print("pages = %d" % PageIndexMax)


# 目标：将文档中的首页去除
for i in range(1, PageIndexMax):
    page = reader.getPage(i)
    getpages.append(page)

writer = pdf.PdfFileWriter()
i = 0
str = ['第一页', '', '', '第3页', '', '', '起始和停止条件', '']
for page in getpages:
    writer.addPage(page)
    # 此处是在第8页添加了一个书签
    # str可以写成字符串数字，用于对应相应的页数
    # i是pagenum
    if i < 8 and str[i].strip():
        writer.addBookmark(str[i], i)
    i += 1


with open(outputfile, 'ab+') as fh:
    writer.write(fh)
