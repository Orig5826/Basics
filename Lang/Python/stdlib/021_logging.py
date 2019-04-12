
import logging
# logging.basicConfig(level=logging.INFO)
# logging.basicConfig(filename='a.txt',level=logging.DEBUG)

logging.basicConfig(
	# 日志级别
	level = logging.INFO,
	# 日志格式
	# 时间、代码所在文件名、代码行号、日志级别名字、日志信息
	format = '%(asctime)s  %(filename)s  line:%(lineno)d  (%(levelname)s)  "%(message)s"   ',
	# 打印日志的时间格式
	datefmt = '[%Y-%m-%d %H:%M:%S]',
	# 日志文件存放的目录（目录必须存在）及日志文件名
	filename = './report.log',
	# 打开日志文件的方式
	filemode = 'w'
)


def div(a,b):
	return a/b
	
logging.debug('1.0 div 0 err!')
logging.info('2.0 div 0 err!')
logging.warning('3.0 div 0 err!')

print(div(10,0))
