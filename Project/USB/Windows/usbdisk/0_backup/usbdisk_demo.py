
from usbdisk import *
import os
import sys

# 打开设备
if True != usb_open():
	sys.exit(-1)
# 配置调试信息等级
usb_set_debug_level(2)

# 显示数据
data = []
for i in range(32):
	data.append(i % 8)

# 写入数据
usb_write(data)
# 读取数据
ret = usb_read(32)
# usb_display(ret)
# print("")

# 写入hs数据
apdu = [0x00,0x80,0x00,0x00,0x08]
usb_write_hs(apdu,data)
# 读取hs数据
ret = usb_read_hs(apdu,32)
# usb_display(ret)
# print("")

# 关闭设备
usb_close()

# 等待按键退出...
os.system("pause")
