# -*- code=utf_8 -*-
import PyPDF2 as pdf
import sys
import os

def pdf_del_first_page(inputfile):
	print(os.path.splitext(inputfile))
	outputfile = os.path.splitext(inputfile)[0] + '_out' + os.path.splitext(inputfile)[1]
	reader = pdf.PdfFileReader(inputfile)
	getpages = list()

	PageIndexMax = reader.getNumPages()
	print("pages = %d" % PageIndexMax)


	pageLabels = {}
	# 目标：将文档中的首页去除
	for i in range(0, PageIndexMax):
		page = reader.getPage(i)
		getpages.append(page)
		pageLabels[page.indirectRef.idnum] = i - 1
	
	outlines= reader.getOutlines()
	# print(outlines)
	BookMark = []
	for outline in outlines:
		# print(outline)
		if type(outline) == pdf.generic.Destination:
			title = outline[r'/Title']
			page = pageLabels[outline.page.idnum]
			connect = (title,page)
			BookMark.append(connect)
	print(BookMark)

	writer = pdf.PdfFileWriter()
	bm_index = 0
	page_num = 0
	for page in getpages[1:]:
		writer.addPage(page)
		while bm_index < len(BookMark) and BookMark[bm_index][1] == page_num:
			writer.addBookmark(BookMark[bm_index][0], BookMark[bm_index][1])
			bm_index += 1
		page_num += 1

	with open(outputfile, 'wb+') as fh:
		writer.write(fh)

if __name__ == '__main__':
	if len(sys.argv) != 2:
		print('参数不对')
		os.exit(-1)
	pdf_del_first_page(sys.argv[1])
	print('删除pdf第一页成功')
	