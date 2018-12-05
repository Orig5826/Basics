
"""
# 
import urllib
import http.client
# 
import urllib.request
import json

def get_json_response():
	# 方式1
	# url = '/crc/c?data=11+22+33+44+55+66+77+88&width=16&poly=1021&init=FFFF&xor=FFFF&refin=true&refout=true'
	# httpClient = http.client.HTTPConnection('api.ip33.com')
	# httpClient.request('GET',url)
	# response = httpClient.getresponse()
	
	# 方式2
	url = 'http://api.ip33.com/crc/c?data=11+22+33+44+55+66+77+88&width=16&poly=1021&init=FFFF&xor=FFFF&refin=true&refout=true'
	response = urllib.request.urlopen(url)
	
	# 返回响应
	json_response = response.read().decode('utf-8')
	return json_response

def get_crc_result(json_response):
	js = json.loads(json_response)
	print(js)
	return js['hex']

response = get_json_response()
crc_result = get_crc_result(response)
print(crc_result)
"""


import urllib.request
import json
import re

"""
	感谢ip33.com网站
"""

CRC_CUSTOM = -1
# poly=1021
CRC_CCIT_KERMIT = 0
CRC_CCIT_XMODEM = 1
CRC_CCIT_FALSE = 2
CRC_CCIT_GENIBUS = 3
CRC_CCIT_X_25 = 4
CRC_CCIT_MCRF4XX = 5
CRC_CCIT_AUG_CCIT = 6
CRC_CCIT_TMS37157 = 7
CRC_CCIT_RIELLO = 8
CRC_CCIT_CRC_A = 9
# poly=8005
CRC_16_BUYPASS = 10
CRC_16_ARC = 11
CRC_16_MODBUS = 12
CRC_16_MAXIM = 13
CRC_16_USB = 14
CRC_16_DDS_110 = 15

class CRC():
	def __init__(self):
		# swap_flag for 32i1
		self.swap_flag = (0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x01, 0x01, 0x01, 0x00, 0x01, 0x01, 0x01, 0x01, 0x00)
		self.data = ''
		self.set_mode()
	def set_mode(self,mode = CRC_CCIT_XMODEM):
		# CRC_CCIT_XMODEM
		self.width = '16'
		self.poly = '1021'
		self.init = '0000'
		self.xor = '0000'
		self.refin = 'false'
		self.refout = 'false'
		self.mode = mode
		
		# ------------------------------------
		# poly=1021
		if mode == CRC_CCIT_KERMIT:
			self.refin = 'true'
			self.refout = 'true'
		elif mode == CRC_CCIT_XMODEM:
			pass
		elif mode == CRC_CCIT_FALSE:
			self.init = 'FFFF'
		elif mode == CRC_CCIT_FALSE:
			self.init = 'FFFF'
		elif mode == CRC_CCIT_GENIBUS:
			self.init = 'FFFF'
			self.xor = 'FFFF'
		elif mode == CRC_CCIT_X_25:
			self.init = 'FFFF'
			self.xor = 'FFFF'
			self.refin = 'true'
			self.refout = 'true'
		elif mode == CRC_CCIT_MCRF4XX:
			self.init = 'FFFF'
		elif mode == CRC_CCIT_AUG_CCIT:
			self.init = '1D0F'
		elif mode == CRC_CCIT_TMS37157:
			self.init = '89EC'
			self.refin = 'true'
			self.refout = 'true'
		elif mode == CRC_CCIT_RIELLO:
			self.init = 'B2AA'
			self.refin = 'true'
			self.refout = 'true'
		elif mode == CRC_CCIT_CRC_A:
			self.init = 'C6C6'
			self.refin = 'true'
			self.refout = 'true'
		# ------------------------------------
		# poly=8005
		elif mode == CRC_16_BUYPASS:
			self.poly = '8005'
		elif mode == CRC_16_ARC:
			self.poly = '8005'
			self.refin = 'true'
			self.refout = 'true'
		elif mode == CRC_16_MODBUS:
			self.poly = '8005'
			self.init = 'FFFF'
			self.refin = 'true'
			self.refout = 'true'
		elif mode == CRC_16_MAXIM:
			self.poly = '8005'
			self.xor = 'FFFF'
			self.refin = 'true'
			self.refout = 'true'
		elif mode == CRC_16_USB:
			self.poly = '8005'
			self.init = 'FFFF'
			self.xor = 'FFFF'
			self.refin = 'true'
			self.refout = 'true'
		elif mode == CRC_16_DDS_110:
			self.poly = '8005'
			self.init = '800D'
		else:
			print('自定义')
			pass
	def set_data(self,dd,dd_type='hex'):
		if isinstance(dd,list):
			data = bytes(dd).hex()
		elif isinstance(dd,str) and dd_type == 'str':
			data = ''.join([hex(ord(c)).replace('0x','') for c in dd])
		elif isinstance(dd,str) and dd_type == 'hex':
			data = dd
		else:
			data = ''
			print('数据类型错误01')
		# 先按照list处理
		"""
		for i in range(len(data)):
			if i != 0:
				self.data += '+'
			self.data += format(data[i],'x')
		"""
		print('数据(hexstr) = {}'.format(data))
		self.data = re.sub(r'(?<=\w)(?=(?:\w\w)+$)', '+', data)
		# print(self.data)
	def set_width(self,width):
		self.width = width
	def set_poly(self,poly):
		self.poly = poly
	def set_init(self,init):
		self.init = init
	def set_result_xor(self,result_xor):
		self.xor = result_xor
	def reverse_in(self,refin):
		if refin == True:
			self.refin = 'true'
		else:
			self.refin = 'false'
	def reverse_out(self,refout):
		if refout == True:
			self.refout = 'true'
		else:
			self.refout = 'false'
	def __swap(self,hexstr):
		if self.mode != CRC_CUSTOM:
			if self.swap_flag[self.mode] == 1:
				return hexstr[-2:] + hexstr[0:2]
		return hexstr
	def get_mode(self):
		mode_dict = dict(CRC_CCIT_KERMIT=0,
		CRC_CCIT_XMODEM = 1,
		CRC_CCIT_FALSE = 2,
		CRC_CCIT_GENIBUS = 3,
		CRC_CCIT_X_25 = 4,
		CRC_CCIT_MCRF4XX = 5,
		CRC_CCIT_AUG_CCIT = 6,
		CRC_CCIT_TMS37157 = 7,
		CRC_CCIT_RIELLO = 8,
		CRC_CCIT_CRC_A = 9,
		CRC_16_BUYPASS = 10,
		CRC_16_ARC = 11,
		CRC_16_MODBUS = 12,
		CRC_16_MAXIM = 13,
		CRC_16_USB = 14,
		CRC_16_DDS_110 = 15)
		
		return list(mode_dict.keys())[list(mode_dict.values()).index(self.mode)]

	def get_crc_result(self):
		# url = 'http://api.ip33.com/crc/c?data=11+22+33+44+55+66+77+88&width=16&poly=1021&init=FFFF&xor=FFFF&refin=true&refout=true'
		url = 'http://api.ip33.com/crc/c?'
		url += 'data=' + self.data + '&'
		url += 'width=' + self.width + '&'
		url += 'poly=' + self.poly + '&'
		url += 'init=' + self.init + '&'
		url += 'xor=' + self.xor + '&'
		url += 'refin=' + self.refin + '&'
		url += 'refout=' + self.refout
		# print(url)
		response = urllib.request.urlopen(url)
		# 返回响应
		json_response = response.read().decode('utf-8')
		js = json.loads(json_response)
		# print(js)
		crc = self.__swap(js['hex'])
		
		return crc


if __name__ == '__main__':
	print(' ----- CRC 计算 ----- ')
	# data = [0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38]
	# data = '131D1122334455667788'
	data = '12345678'
	crc = CRC()
	crc.set_data(data,'str')
	for i in range(16):
		crc.set_mode(i)
		crc_result = crc.get_crc_result()
		mode = crc.get_mode()
		print('{0:20s} = {1}'.format(mode,crc_result))
	print(' ----- END ----- ')
