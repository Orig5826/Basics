
"""
	--- CRC 计算python代码实现 ---
	@来源 https://blog.csdn.net/heathy__/article/details/53007037
	@注释 在CSDN用户__BOOM__原创代码的基础之上做的修改
	
	@目标：修改为 CRC_CCIT_X_25 (poly=1021,width=16,init=0xffff,xor=0xffff,refin,refout)
"""
WIDTH = 16
POLYNOMIAL = 0x1021
INITIAL_REMAINDER = 0xFFFF
FINAL_XOR_VALUE = 0xFFFF
REFIN_FLAG = True
REFOUT_FLAG = True

TOPBIT = (1 << (WIDTH - 1))
crcTable = {}

def __crcReverse(data,bitcnt):
	"""
		--- bit倒序---
		@来源 https://blog.csdn.net/jakee304/article/details/2152655?utm_source=blogxgwz7
		@注释 基于C代码实现高效bit逆序
	"""
	if bitcnt == 8:
		data = (data & 0xF0) >> 4 | (data & 0x0F) << 4
		data = (data & 0xCC) >> 2 | (data & 0x33) << 2
		data = (data & 0xAA) >> 1 | (data & 0x55) << 1
	elif bitcnt == 16:
		data = (data & 0xFF00) >> 8 | (data & 0x00FF) << 8
		data = (data & 0xF0F0) >> 4 | (data & 0x0F0F) << 4
		data = (data & 0xCCCC) >> 2 | (data & 0x3333) << 2
		data = (data & 0xAAAA) >> 1 | (data & 0x5555) << 1
	else:
		return False
	return data
	
def __crcInit():
	"""
		生成CRC表，方便快速计算
	"""
	SHIFT = WIDTH - 8
	for step in range(0, 256):
		remainder = step << SHIFT
		for bit in range(8, 0, -1):
			if remainder & TOPBIT:
				remainder = ((remainder << 1) & 0xFFFF) ^ 0x1021
			else:
				remainder = remainder << 1
		crcTable[step] = remainder

def __crcFast(data):
	__crcInit()
	"""
		查表法实现
	"""
	#for i in range(len(crcTable)):
	#	print('{0:04x}\t'.format(crcTable[i]),end='')
	length = len(data)
	crc_value = INITIAL_REMAINDER
	for i in range(length):
		"""
			refin 输入bit逆序
		"""
		temp = crc_value >> 0x08
		if REFIN_FLAG == True:
			temp ^= __crcReverse(data[i],8)
		else:
			temp ^= data[i]
		crc_value = (crcTable[temp & 0xFF] ^ ((crc_value << 8) & 0xFFFF)) & 0xFFFF
	"""
		refout 输出bit逆序
	"""
	if REFOUT_FLAG == True:
		# print('crc_value = ',hex(crc_value))
		crc_value = __crcReverse(crc_value,16)
	
	"""
		异或
	"""
	crc_value ^= FINAL_XOR_VALUE

	res_str = '{0:04x}'.format(crc_value)
	return bytes.fromhex(res_str)
	

def crc_calc(data):
	if not isinstance(data,list):
		return False
	bb = __crcFast(data)
	return list(bb)


if __name__ == '__main__':
	message = [0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38]
	res = crc_calc(message)
	# print(res)
	print(bytes(res).hex())