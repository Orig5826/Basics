from ctypes import *
from time import sleep

# --------------------------------------------
# ctypes array
# --------------------------------------------
def c_u8(n)  : return (c_uint8 * n)()
def c_u16(n) : return (c_uint16 * n)()
def c_u32(n) : return (c_uint32 * n)()

# --------------------------------------------
# º”‘ÿdllø‚
# Load dll
# __stdcall
api = windll.LoadLibrary("usbdisk.dll")
# __cdecl
# api = cdll.LoadLibrary("usbdisk.dll")

def usb_open():
	api.usb_open()

def usb_close():
	api.usb_close()
	
def usb_display(data):
	Length = len(data)
	__data = c_u8(Length)
	for i in range(Length):
		__data[i] = data[i]
	api.usb_display(__data,Length)

def usb_set_debug_level(level):
	api.usb_set_debug_level(level)
