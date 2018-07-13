from ctypes import *
from time import sleep


# 定义C结构，用于传递参数
class HID_Config(Structure):
    _fields_ = [('PID', c_ushort),('VID', c_ushort)]
# GetString参数
GET_MANUFACTURE	=	1	#厂商信息
GET_PRODUCT		=	2	#产品信息
GET_SERIALNUM	=	3	#序列号

# --------------------------------------
# 声明数组类型
STR = c_ubyte * 64
# 自定义显示函数
def disp(STR,hex = 0):
    # 问：如何按照Unicode来显示
    str = ""
    for i in STR:
        if hex == 0:
            if i != 0x00:
                str = str + '%c'%i
        else:
            str = str + "%02x "%i
    print("%s" % str.encode())
def cmp(buf1 = c_ubyte(64),buf2 = c_ubyte(64),len = 64):
    for i in range(len):
        if buf1[i] != buf2[i]:
            return 1
    return 0

# Load dll
api = windll.LoadLibrary("usb_drive.dll")

# usb_hid_test
api.usb_hid_test()

# Structure
hid_cfg=HID_Config()
hid_cfg.PID = 0x5750
hid_cfg.VID = 0x0483

# C API
ret = api.USB_HID_Connect(byref(hid_cfg))
if ret == True:
    str = STR()
    api.USB_HID_GetString(byref(str),len(str),GET_MANUFACTURE)
    disp(str)
    api.USB_HID_GetString(byref(str),len(str),GET_PRODUCT)
    disp(str)
    api.USB_HID_GetString(byref(str),len(str),GET_SERIALNUM)
    disp(str)

    BUFFER = c_ubyte * 65
    sBuf = BUFFER()
    rBuf = BUFFER()
    sLen = 64
    rLen = c_uint(0)
    num = 0
    while(1):
        for i in range(64):
            sBuf[i] = 0xff & (num + i)
        api.USB_HID_Write(0, sBuf, sLen)
        rLen.value = len(rBuf)
        api.USB_HID_Read(0, rBuf, byref(rLen))
        print("[Read]")
        disp(rBuf,1)

        if 0 != cmp(rBuf,sBuf,64):
            print("[Write]")
            disp(sBuf,1)
            print("[ERROR] --- 读写不一致 ---")
            break

        sleep(1)
        num += 1
        print("------------------------")
        
api.USB_HID_Close()
