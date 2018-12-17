# -*- code=utf_8 -*-
import PyPDF2 as pdf
import os

inputfile = r".\安全模块设计文档20180612_1536_V1.0.pdf"
outputpath = ".\\split\\"

reader = pdf.PdfFileReader(inputfile)
PageIndexMax = reader.getNumPages()
print("pages = %d" % PageIndexMax)

if not os.path.exists(outputpath):
    os.mkdir(outputpath)

# 每5页分割为一个单独的pdf文件

for i in range(0, PageIndexMax):
    # 写入分割后的文件
    if i % 5 == 0:
        writer = pdf.PdfFileWriter()
        split_pdf = outputpath + 'split_' + '{0:02d}'.format(i//5) + '.pdf'
    page = reader.getPage(i)
    writer.addPage(page)
    if (i + 1) % 5 == 0:
        with open(split_pdf, 'wb+') as fh:
            writer.write(fh)
