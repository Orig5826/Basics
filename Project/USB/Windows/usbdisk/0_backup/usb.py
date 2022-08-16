# -*- coding: utf-8 -*-
from ctypes import *
from time import sleep
import os

# usbdisk.dll -> maxsize=4096
BUFFER_SIZE_MAX = 0x1000
# --------------------------------------------
# ctypes array
# --------------------------------------------
def c_u8(n): return (c_uint8 * n)()
def c_u16(n): return (c_uint16 * n)()
def c_u32(n): return (c_uint32 * n)()


def dbg(prompt="\n", dat=None):
    if dat != None:
        print(prompt+'{}'.format(bytes(dat).hex(' ')))
    else:
        print(prompt)


class usbdisk():
    def __init__(self, dllpath=None):
        '''
            加载dll库
            __stdcall
            api = windll.LoadLibrary("usbdisk.dll")
            __cdecl
            api = cdll.LoadLibrary("usbdisk.dll")
        '''
        try:
            if dllpath == None:
                fpath = os.path.realpath(__file__)
                fpath = os.path.split(fpath)[0]
                dllpath = fpath + '\\' + 'usbdisk.dll'
                
            # print(dllpath)
            self.api = windll.LoadLibrary(dllpath)
        except FileNotFoundError:
            raise FileNotFoundError('Load [{}] failed! '.format(dllpath))

    def __del__(self):
        self.close()

    def open(self, symbolic, translog=True):
        '''
            打开USB设备
        '''
        symbolic_link = bytes(symbolic, encoding='utf-8')
        symbolic_link = c_char_p(symbolic_link)
        
        # 是否显示传输日志
        self.translog = translog
        # 打开设备，并获取句柄
        self.handle = self.api.usb_open(symbolic_link)
        # print(self.handle)
        if(self.handle == 0):
            # raise Exception('Open dev "{}" failed! '.format(symbolic_link))
            return False
        return True

    def close(self):
        '''
            关闭USB设备
        '''
        self.api.usb_close(self.handle)

    def write(self, data):
        '''
            通用写接口，CMD=0xFF
        '''
        # 组织数据
        data_len = len(data)
        __data = c_u8(data_len)
        for i in range(data_len):
            __data[i] = data[i]

        # 组织命令
        __cmd = c_u8(1)
        __cmd[0] = 0xFF

        self.api.usb_write(self.handle, __cmd, 1, __data, data_len)

    def read(self, rlen=BUFFER_SIZE_MAX):
        '''
            通用读接口，CMD=0xFF
        '''
        # 组织数据
        data = []
        __data = c_u8(BUFFER_SIZE_MAX)
        data_len = c_uint32(rlen)

        # 组织命令
        __cmd = c_u8(1)
        __cmd[0] = 0xFF

        self.api.usb_read(self.handle, __cmd, 1, byref(__data), byref(data_len))
        for i in range(data_len.value):
            data.append(__data[i])
        return data

    def write_hs(self, apdu, data):
        '''
                写入数据，CMD=0xFD
        '''
        # 组织数据
        data_len = len(data)
        __data = c_u8(data_len)
        for i in range(data_len):
            __data[i] = data[i]

        # 组织命令
        cmd_len = len(apdu)
        if(cmd_len > 15):
            raise Exception('cmd_len cannot exceed 15! ')
        __cmd = c_u8(cmd_len + 1)
        __cmd[0] = 0xFD
        for i in range(cmd_len):
            __cmd[i + 1] = apdu[i]

        self.api.usb_write(self.handle, __cmd, cmd_len, __data, data_len)

    def read_hs(self, cmd, rlen):
        '''
                读取数据，CMD=0xFE
        '''
        # 组织数据
        data = []
        __data = c_u8(BUFFER_SIZE_MAX)
        data_len = c_uint32(rlen)

        # 组织命令
        cmd_len = len(apdu)
        if(cmd_len > 15):
            raise Exception('cmd_len cannot exceed 15! ')
        __cmd = c_u8(cmd_len + 1)
        __cmd[0] = 0xFE
        for i in range(cmd_len):
            __cmd[i + 1] = cmd[i]

        self.api.usb_read(self.handle, __cmd, cmd_len + 1, byref(__data), byref(data_len))
        for i in range(data_len.value):
            data.append(__data[i])
        return data

    def trans(self, data):
        '''
            data 必须为list或者hex，其他不支持
        '''
        if isinstance(data, list):
            _data = data.copy()
        elif (type(data) is str):
            try:
                _data = hex2list(data)
            except:
                raise Exception("trans函数hex数据非法")
        else:
            raise Exception("trans函数data参数只能是list或者hex")

        if self.translog == True:
            dbg("-> ", _data)
        self.write(_data)
        _res = self.read()
        if self.translog == True:
            dbg("<- ", _res)
            # dbg("")
        return _res


if __name__ == "__main__":
    usb = usbdisk()
    if False != usb.open("HSEC    hsc32k1_usb2sti 1.00"):
        for i in range(10):
            apdu = [0x00, 0x84, 0x00, 0x00, 0x10]
            usb.trans(apdu)
