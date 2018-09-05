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


# ----------------------------------------------------------------
# 将list转换为hexstr
def py27_list2hexstr(ll):
    ss = str(bytearray(ll))
    return binascii.b2a_hex(ss)


if sys.version_info.major == 2:
    list2hexstr = py27_list2hexstr
elif sys.version_info.major == 3:
    pass
else:
    print("sys.version ? Error! ")


# ----------------------------------------------------------------


# 1.0 根据VID和PID查找指定设备
def usbdrv_find(VID=0x2309, PID=0x0606):
    print("查找USB设备:VID = 0x%04x,PID = 0x%04x" % (VID, PID))
    dev = usb.core.find(idVendor=VID, idProduct=PID)
    if dev == None:
        print("没有发现设备")
        return None
    print("已经发现设备")
    print(dev)
    return dev


# 2.0 返回指定设备的OUT端点和IN端点
# 备注：暂时实现为根据具体实现来手动修改
def usbdrv_get_point(dev):
    # 获取配置
    config = dev[0]
    # 获取接口
    interface = config[0, 0]
    # 获取输出端点和输入端点
    outpoint = interface[1]
    inpoint = interface[0]
    return (outpoint, inpoint)


# 3.0 将设备从内核驱动上进行卸载，并占用该接口
def usbdrv_start(dev):
    if True == dev.is_kernel_driver_active(0):
        dev.detach_kernel_driver(interface=0)
        usb.util.claim_interface(dev, interface=0)
    print("--- START --- ")


# 4.0 当自定义命令发送完成后，将设备重新挂载到系统驱动上
def usbdrv_end(dev):
    usb.util.release_interface(dev, 0)
    dev.attach_kernel_driver(0)
    print("--- END --- ")


# 5.0 发送数据(自定义命令0xFF)
def usbdrv_write(dev, data):
    outpoint, inpoint = usbdrv_get_point(dev)
    # 生成随机数Tag
    tag = []
    for i in range(0, 4):
        tag.append(random.randint(0, 256))
    cbw = [0x55, 0x53, 0x42, 0x43, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xff,
           0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00]
    # 配置长度
    length = len(data)
    cbw[8] = length & 0xff
    cbw[9] = (length >> 8) & 0xff
    cbw[10] = (length >> 16) & 0xff
    cbw[11] = (length >> 24) & 0xff
    # 配置Tag
    for i in range(0, 4):
        cbw[4 + i] = tag[i]

    # 1.0 写入cbw
    dev.write(outpoint, cbw)
    # 2.0 写入数据
    dev.write(outpoint, data)
    # hexstr显示
    print("[OUT]\t" + list2hexstr(data))
    # 3.0 读取csw
    res = dev.read(inpoint, 13)
    for i in range(0, 4):
        if res[4 + i] != tag[i]:
            print("响应Tag和命令Tag不一致")
            return False
    return True


# 6.0 接收数据(自定义命令0xFF)
def usbdrv_read(dev, length):
    outpoint, inpoint = usbdrv_get_point(dev)
    # 生成随机数Tag
    tag = []
    for i in range(0, 4):
        tag.append(random.randint(0, 256))
    data = []
    cbw = [0x55, 0x53, 0x42, 0x43, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x01, 0xff,
           0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00]
    # 配置长度
    cbw[8] = length & 0xff
    cbw[9] = (length >> 8) & 0xff
    cbw[10] = (length >> 16) & 0xff
    cbw[11] = (length >> 24) & 0xff
    # 配置Tag
    for i in range(0, 4):
        cbw[4 + i] = tag[i]

    # 1.0 写入cbw
    dev.write(outpoint, cbw)
    # 2.0 写入数据
    data = dev.read(inpoint, length)
    # hexstr显示
    print("[IN]\t" + list2hexstr(data))
    # 3.0 读取csw
    res = dev.read(inpoint, 13)
    for i in range(0, 4):
        if res[4 + i] != tag[i]:
            print("响应Tag和命令Tag不一致")
            return None
    return data


# -------------------------------------------------------------
#                   USB SCSI Test

dev = usbdrv_find()
if dev == None:
    sys.exit(-1)
usbdrv_start(dev)

# Write & Read
data = [0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88]
usbdrv_write(dev, data)
res = usbdrv_read(dev, 8)

usbdrv_end(dev)
