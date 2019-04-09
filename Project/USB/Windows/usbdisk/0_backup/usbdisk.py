from ctypes import *
from time import sleep

#Symbolic_link = 'HSEC    USBCOS'
Symbolic_link = 'HSEC    UCOS'

BUFFER_SIZE_MAX = 0x400 + 0x40 + 8
# --------------------------------------------
# ctypes array
# --------------------------------------------
def c_u8(n)  : return (c_uint8 * n)()
def c_u16(n) : return (c_uint16 * n)()
def c_u32(n) : return (c_uint32 * n)()


'''
	加载dll库
__stdcall
	api = windll.LoadLibrary("usbdisk.dll")
__cdecl
	api = cdll.LoadLibrary("usbdisk.dll")
'''
api = windll.LoadLibrary("usbdisk.dll")

def usb_open():
	'''
		打开USB设备
	'''
	return api.usb_open(Symbolic_link)

def usb_close():
	'''
		关闭USB设备
	'''
	return api.usb_close()
	
def usb_display(data):
	'''
		显示USB设备信息
	'''
	Length = len(data)
	__data = c_u8(Length)
	for i in range(Length):
		__data[i] = data[i]
	api.usb_display(__data,Length)

def usb_set_debug_level(level):
	'''
		配置USB调试信息等级
	'''
	api.usb_set_debug_level(level)

def usb_write(data):
	'''
		写入数据，CMD=0xFF
	'''
	Length = len(data)
	__data = c_u8(Length)
	for i in range(Length):
		__data[i] = data[i]
	api.usb_write(__data,Length)	

def usb_read(rLen):
	'''
		读取数据，CMD=0xFF
	'''
	data = []
	__data = c_u8(BUFFER_SIZE_MAX)
	Length = c_uint32(rLen)
	api.usb_read(byref(__data),byref(Length))
	for i in range(Length.value):
		data.append(__data[i])
	return data
	

def usb_write_hs(apdu,data):
	'''
		写入数据，CMD=0xFD
	'''
	# 组织数据
	Length = len(data)
	__data = c_u8(Length)
	for i in range(Length):
		__data[i] = data[i]
	# 组织APDU	
	Apdu_Len = len(apdu)
	__apdu = c_u8(Apdu_Len)
	for i in range(Apdu_Len):
		__apdu[i] = apdu[i]
	
	api.usb_write_hs(__apdu,Apdu_Len,__data,Length)	

def usb_read_hs(apdu,rLen):
	'''
		读取数据，CMD=0xFE
	'''
	# 组织数据
	data = []
	__data = c_u8(BUFFER_SIZE_MAX)
	Length = c_uint32(rLen)
	
	# 组织APDU
	Apdu_Len = len(apdu)
	__apdu = c_u8(Apdu_Len)
	for i in range(Apdu_Len):
		__apdu[i] = apdu[i]
	
	api.usb_read_hs(__apdu,Apdu_Len,byref(__data),byref(Length))
	for i in range(Length.value):
		data.append(__data[i])
	return data
