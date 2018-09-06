#!/usr/bin/python
# -*- coding: utf-8 -*-
#
# 本pyusb使用例程主要是针对linux上连接的SCSI设备
# 来实现的wirte和read接口
#
import sys
import usb
import binascii
import random

global usbdrv_debug_level
usbdrv_debug_level = 1

# ----------------------------------------------------------------
# @fun 将list转换为hexstr
# 根据py版本，来决定list2hexstr实际调用的是哪个版本的函数
def __py27_list2hexstr(ll):
    ss = str(bytearray(ll))
    return binascii.b2a_hex(ss)

if sys.version_info.major == 2:
    list2hexstr = __py27_list2hexstr
elif sys.version_info.major == 3:
    pass
else:
    print("sys.version ? Error! ")

# ----------------------------------------------------------------
def __usbdrv_find(VID=0x2309, PID=0x0606):
    '''
        1.0 根据VID和PID查找指定设备
    '''
    print("查找USB设备:VID = 0x%04x,PID = 0x%04x" % (VID, PID))
    dev = usb.core.find(idVendor=VID, idProduct=PID)
    if dev == None:
        print("没有发现设备")
        return None
    return dev


def __usbdrv_get_point(dev):
    '''
        2.0 返回指定设备的OUT端点和IN端点
        # 备注：暂时实现为根据具体实现来手动修改
    '''
    # 获取配置
    config = dev[0]
    # 获取接口
    interface = config[0, 0]
    # 获取输出端点和输入端点
    # 常见的情况就是2个端点，IN和OUT，暂定为如此
    for i in range(0,2):
        if 0x80 == interface[i].bEndpointAddress & 0x80:
            inpoint = interface[i]
        else:
            outpoint = interface[i]
    # 注意返回的turple必须保证
    # 这样后续的接口就不用修改了
    # 0.out 1.in
    return (outpoint, inpoint)


def __usbdrv_start(dev):
    '''
        3.0 将设备从内核驱动上进行卸载，并占用该接口
    '''
    if True == dev.is_kernel_driver_active(0):
        dev.detach_kernel_driver(interface=0)
        usb.util.claim_interface(dev, interface=0)

def __usbdrv_end(dev):
    '''
        4.0 当自定义命令发送完成后，将设备重新挂载到系统驱动上
    '''
    usb.util.release_interface(dev, 0)
    dev.attach_kernel_driver(0)


def __usbdrv_send_cbw(dev,Length,Direction,CBLength=0x01,CB=[0xff]):
    '''
        5.0 CBW的发送 和 CSW的接收
        @ param
            Length      OUT发送/IN接收的数据长度
            Dircetion   0x80接收，0x00发送
            CBLength    范围区间(0,16]，默认为1
            CB          CB数据列表，默认为[0xff]
    '''
    outpoint = __usbdrv_get_point(dev)[0]
    tag = []
    for i in range(0, 4):
        tag.append(random.randint(0, 256))

    if Direction != 0x80 and Direction != 0x00:
        return False
    if CBLength <= 0 or CBLength > 16:
        return False
    if CBLength != len(CB):
        return False
    cbw = [ 0x55, 0x53, 0x42, 0x43, tag[0], tag[1], tag[2], tag[3],\
            Length & 0xff, (Length >> 8) & 0xff,(Length >> 16) & 0xff,(Length >> 24) & 0xff,\
            Direction, 0x00, CBLength,0x00,0x00, 0x00, 0x00, 0x00,\
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00]
    cbw[15:(15 + CBLength)] = CB[0:CBLength]
    if usbdrv_debug_level >= 2:
        print("len = %d,cbw = %s" % (len(cbw),list2hexstr(cbw)))
    dev.write(outpoint, cbw)
    return tag


def __usbdrv_recv_csw(dev,tag):
    '''
        5.1 CSW的接收
        @ param
            tag USB scsi协议中的参数
    '''
    inpoint = __usbdrv_get_point(dev)[1]
    csw = list(dev.read(inpoint, 13))
    if usbdrv_debug_level >= 2:
        print("len = %d,csw = %s" % (len(csw),list2hexstr(csw)))
    if csw[4:8] != tag:
        return False
    if csw[0:4] != [0x55,0x53,0x42,0x53]:
        return False
    if csw[-1] != 0x00:
        return False
    return True


# 6.0 数据的发送和接收
def __usbdrv_send_data(dev,data):
    '''
        6.0 数据的发送
    '''
    outpoint = __usbdrv_get_point(dev)[0]
    dev.write(outpoint, data)
    if usbdrv_debug_level >= 1:
        print("-> " + list2hexstr(data))


def __usbdrv_recv_data(dev,length):
    '''
        6.1 数据的接收
    '''
    inpoint = __usbdrv_get_point(dev)[1]
    data = list(dev.read(inpoint, length))
    if usbdrv_debug_level >= 1:
        print("<- " + list2hexstr(data))
    return data

# -------------------------------------------------------------
#                   USB SCSI API
# global g_Dev
__g_Dev = None
def usbdrv_open(vid=0x2309,pid=0x0606):
    '''
        打开UBS设备
    '''
    global __g_Dev
    __g_Dev = __usbdrv_find()
    if __g_Dev == None:
        return False
    __usbdrv_start(__g_Dev)
    print("---------------- START ----------------")
    return True
def usbdrv_show():
    '''
        显示UBS设备信息
    '''
    print(__g_Dev)

def usbdrv_close():
    '''
        关闭UBS设备
    '''
    __usbdrv_end(__g_Dev)
    print("---------------- END ----------------")

def usbdrv_write(data):
    '''
        写数据
        > 针对SCSI设备做的封装函数
    '''
    tag = __usbdrv_send_cbw(__g_Dev,len(data),0x00)
    if False == tag:
        return False
    __usbdrv_send_data(__g_Dev,data)
    return __usbdrv_recv_csw(__g_Dev,tag)

def usbdrv_read(length):
    '''
        读数据
        > 针对SCSI设备做的封装函数
    '''
    tag = __usbdrv_send_cbw(__g_Dev,length,0x80)
    if False == tag:
        return False
    data = __usbdrv_recv_data(__g_Dev,length)
    return __usbdrv_recv_csw(__g_Dev,tag)

def usbdrv_write_hs(apdu,data):
    '''
        写数据_hs
        > 针对SCSI设备做的封装函数
    '''
    if len(apdu) > 15:
        return False
    cb = [0xfd]
    cb.extend(apdu)
    tag = __usbdrv_send_cbw(__g_Dev,len(data),0x00,len(cb),cb)
    if False == tag:
        return False
    __usbdrv_send_data(__g_Dev,data)
    return __usbdrv_recv_csw(__g_Dev,tag)

def usbdrv_read_hs(apdu,length):
    '''
        读数据_hs
        > 针对SCSI设备做的封装函数
    '''
    if len(apdu) > 15:
        return False
    cb = [0xfe]
    cb.extend(apdu)
    tag = __usbdrv_send_cbw(__g_Dev,length,0x80,len(cb),cb)
    if False == tag:
        return False
    data = __usbdrv_recv_data(__g_Dev,length)
    return __usbdrv_recv_csw(__g_Dev,tag)

# ---------------- USBDRV TEST ----------------
def usbdrv_test():
    if False == usbdrv_open():
        sys.exit(-1)
    # usb_show()

    data = [0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88]
    usbdrv_write(data)
    usbdrv_read(8)

    usbdrv_close()
