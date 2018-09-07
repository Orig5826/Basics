#!/usr/bin/python
# -*- coding: utf-8 -*-

import sys
import usbdrv

def default_demo():
	if False ==  usbdrv.usbdrv_open():
		sys.exit(-1)
	# usbdrv.usbdrv_show()

	data = [ 0x00,0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x00,0x11,0x22,0x33,0x44,0x55,0x66,0x77,\
			0x00,0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x00,0x11,0x22,0x33,0x44,0x55,0x66,0x77]
	for i in range(0,3):
		usbdrv.usbdrv_write(data)
		usbdrv.usbdrv_read(32)
		print("")

	usbdrv.usbdrv_close()

def default_demo_hs():
	if False ==  usbdrv.usbdrv_open():
		sys.exit(-1)
	# usbdrv.usbdrv_show()
	# usbdrv.usbdrv_debug_level = 2

	apdu = [0x00,0x84,0x00,0x00,0x08]
	usbdrv.usbdrv_read_hs(apdu,0x0a)

	usbdrv.usbdrv_close()

def default_sm4_hs():
	if False ==  usbdrv.usbdrv_open():
		sys.exit(-1)
	# usbdrv.usbdrv_show()
	usbdrv.usbdrv_debug_level = 0

	# 创建一个新文件吧
	file_plain = "plain.bin"
	plain = [0x01,0x23,0x45,0x67,0x89,0xab,0xcd,0xef,\
			0xfe,0xdc,0xba,0x98,0x76,0x54,0x32,0x10]
	with open(file_plain,'wb') as f:
		for i in range(0,(0xC000 * 4),16):
			file = f.write(bytearray(plain))
	f.close()

	# 打开明文文件
	file_plain = "plain.bin"
	with open(file_plain,'rb') as f:
		file = f.read()
	f.close()

	if len(file)%0xC000 != 0:
		print("the length of '%s' is error!" % file_plain)
		sys.exit(-1)

	# 加密文件
	file_crypt_ecb = "crypt_ecb.bin"
	fout = open(file_crypt_ecb,'wb')
	# ECB加密
	for i in range(0,len(file),0xC000):
		apdu = [0x80,0xC2,0x00,0x00,0x00]
		data = file[i:i+0xC000]
		usbdrv.usbdrv_write_hs(apdu,data)
		res = usbdrv.usbdrv_read_hs(apdu,0xC000)
		if False != res:
			crypt = bytearray(res)
			fout.write(crypt)
	# 关闭密文文件
	fout.close()



	# 打开密文文件
	with open(file_crypt_ecb,'rb') as f:
		file = f.read()
	f.close()
	if len(file)%0xC000 != 0:
		print("the length of '%s' is error!" % file_crypt_ecb)
		sys.exit(-1)
	# 解密文件
	file_result = "result.bin"
	fout = open(file_result,'wb')
	# ECB加密
	for i in range(0,len(file),0xC000):
		apdu = [0x80,0xC4,0x00,0x00,0x00]
		data = file[i:i+0xC000]
		usbdrv.usbdrv_write_hs(apdu,data)
		res = usbdrv.usbdrv_read_hs(apdu,0xC000)
		if False != res:
			crypt = bytearray(res)
			fout.write(crypt)
	# 关闭密文文件
	fout.close()


	usbdrv.usbdrv_close()




default_sm4_hs()
