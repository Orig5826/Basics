from ctypes import *
from time import sleep


BUFFER_SIZE_MAX = 0x400 + 0x40 + 8
# --------------------------------------------
# ctypes array
# --------------------------------------------
def c_u8(n)	 : return (c_uint8 * n)()
def c_u16(n) : return (c_uint16 * n)()
def c_u32(n) : return (c_uint32 * n)()

def list2str(ll):
    '''
        [0x31,0x32,0x33,0x41,0x42,0x43] -> str("123ABC")
    '''
    return ''.join([chr(i) for i in ll])

def list2hex(ll):
    '''
        [0x31,0x32,0x33] -> str("313233")
    '''
    return bytes(ll).hex()


# 定义C结构，用于传递参数
class HID_Config(Structure):
	_fields_ = [('PID', c_ushort),('VID', c_ushort)]
# GetString参数
GET_MANUFACTURE	=	1	#厂商信息
GET_PRODUCT		=	2	#产品信息
GET_SERIALNUM	=	3	#序列号


class usbhid():
	def __init__(self,pid=None,vid=None):
		# Load dll
		self.api = windll.LoadLibrary("usb_drive.dll")
		self.level = 0
		if pid != None and vid != None:
			self.open(pid,vid)
	def __del__(self):
		self.close()
	
	def set_debug_level(self,level):
		self.level = level
	def open(self,pid,vid):
		'''
			打开USB设备
		'''
		hid_cfg = HID_Config()
		hid_cfg.PID = pid
		hid_cfg.VID = vid
		
		print("----- 打开设备 -----")
		return self.api.USB_HID_Connect(byref(hid_cfg))
	
	def close(self):
		self.api.USB_HID_Close()
		print("----- 关闭设备 -----")
	
	def disp_info(self):
		info = self.get_manufacture()
		print('【厂商信息】 ' + info)
		info = self.get_product()
		print('【产品信息】 ' + info)
		info = self.get_serialnum()
		print('【 序列号 】 ' + info)
		print()
	
	def get_manufacture(self):
		data = []
		__data = c_u8(BUFFER_SIZE_MAX)
		Length = 32
		self.api.USB_HID_GetString(byref(__data),Length,GET_MANUFACTURE)
		for i in range(0,Length,2):
			data.append(__data[i] | (__data[i + 1] << 8) )
		return list2str(data)
	def get_product(self):
		data = []
		__data = c_u8(BUFFER_SIZE_MAX)
		Length = 32
		self.api.USB_HID_GetString(byref(__data),Length,GET_PRODUCT)
		for i in range(0,Length,2):
			data.append(__data[i] | (__data[i + 1] << 8) )
		return list2str(data)
	def get_serialnum(self):
		data = []
		__data = c_u8(BUFFER_SIZE_MAX)
		Length = 32
		self.api.USB_HID_GetString(byref(__data),Length,GET_SERIALNUM)
		for i in range(0,Length,2):
			data.append(__data[i] | (__data[i + 1] << 8) )
		return list2str(data)
		
	def write(self,data):
		'''
			写入数据
		'''
		Length = len(data)
		if Length > 64:
			return False
		__data = c_u8(Length)
		for i in range(Length):
			__data[i] = data[i]
		if self.level > 0:
			print('-> ' + list2hex(__data))
		self.api.USB_HID_Write(0,__data,Length)
		return True
	def read(self,rLen):
		'''
			读取数据
		'''
		if rLen > 64:
			return False
		data = []
		__data = c_u8(BUFFER_SIZE_MAX)
		Length = c_uint32(rLen)
		self.api.USB_HID_Read(0, byref(__data),byref(Length))
		for i in range(Length.value):
			data.append(__data[i])
		if self.level > 0:
			print('<- ' + list2hex(data))
		return data
	def setfeature(self,data):
		'''
			21 09 00 03 00 00 40 00 
		'''
		# print('   [SetFeature]')
		Length = len(data)
		if Length > 64:
			return False
		__data = c_u8(Length)
		for i in range(Length):
			__data[i] = data[i]
		if self.level > 0:
			print('-> ' + list2hex(__data))
		self.api.USB_HID_SetFeature(0,__data,Length)
		return True
	def getfeature(self,rLen):
		'''
			A1 01 00 03 00 00 40 00 
		'''
		# print('   [GetFeature]')
		if rLen > 64:
			return False
		data = []
		__data = c_u8(BUFFER_SIZE_MAX)
		Length = c_uint32(rLen)
		self.api.USB_HID_GetFeature(0, byref(__data),byref(Length))
		# print(Length.value) #长度有误，请查看dll
		for i in range(Length.value):
			data.append(__data[i])
		if self.level > 0:
			print('<- ' + list2hex(data))
		return data


def usbhid_test():
	hid = usbhid()
	hid.open(0x084B,0x4853)
	hid.disp_info()
	hid.set_debug_level(1)

	data = []
	for i in range(64):
		data.append(i)
	hid.write(data)
	hid.read(64)

	hid.setfeature(data)
	hid.getfeature(64)

	
# usbhid_test()
