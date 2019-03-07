
import re
import sys

def file_hex2bin(infile,outfile):
	with open(infile,'r') as fsrc:
		data = fsrc.read()
	bdata = bytes.fromhex(data)
	# print(bdata)
	with open(outfile,'wb') as fout:
		fout.write(bdata)
	
def file_bin2hex(infile,outfile):
	with open(infile,'rb') as fsrc:
		data = fsrc.read()
	hdata = data.hex()
	# 每两个字符添加一个空格操作
	result = re.sub(r"(?<=\w)(?=(?:\w\w)+$)", " ", hdata);
	# print(result)
	
	with open(outfile,'w') as fout:
		fout.write(result)

def file_cmd_help():
	print('''参数说明：
1. bin2hex infile [-hex] outfile  # 将bin文件转为assic显示的hex内容
2. bin2hex infile -bin  outfile   # 将assic显示的hex内容转换为bin文件
	''')
		
if __name__ == '__main__':
	argv_len = len(sys.argv)	
	if argv_len == 3:
		infile = sys.argv[1]
		outfile = sys.argv[2]
		file_bin2hex(infile,outfile)
		print('file_bin2hex转化完成')
	elif argv_len == 4:
		infile = sys.argv[1]
		mode = sys.argv[2]
		outfile = sys.argv[3]
		if mode == '-hex':
			file_bin2hex(infile,outfile)
		elif mode == '-bin':
			file_hex2bin(infile,outfile)
		else:
			file_cmd_help()
			sys.exit(-1)
		print('file_bin2hex转化完成')
	else:
		file_cmd_help()
