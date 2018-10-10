
from usbdisk import *
import os
import sys
import time

class Apdu:
	'''
		py3
	'''
	def __init__(self):
		# 打开设备
		if True != usb_open():
			sys.exit(-1)
		# 配置调试信息等级
		usb_set_debug_level(0)
	def __del__(self):
		# 关闭设备
		usb_close()
	
	def __str2list(self,ss):
		return list(bytes.fromhex(ss))
	def __list2str(self,ll):
		return str(bytes(ll))
	
	def SendAPDU(self,apdu,data = None,Le = 0):
		'''
			该函数的参数
			apdu (list/str) APDU指令
			data (list/str) CASE3/CASE4下的数据
			Le   (int)      
			@note isinstance 和 type的应用
		'''
		# 判断apdu和Le的合法性
		if isinstance(apdu,list) and isinstance(Le,int):
			pass
		elif (type(apdu) is str) and (type(Le) == int):
			if len(apdu)%2!=0:
				print("apdu指令少了一个字符")
				os.system("pause")
			apdu = self.__str2list(apdu)
		else:
			print("apdu/Le指令类型出错")
		
		# 判断data的合法性
		if data != None:
			if type(data) is str:
				if data != None and len(data)%2!=0:
					print("data数据少了一个字符")
					os.system("pause")
				data = self.__str2list(data)
		
		# 命令处理
		cmd = apdu.copy()
		if data == None:
			# case2
			if Le != 0:
				if Le < 256:
					cmd.append(Le)
				else:
					cmd.append(0x00)
					cmd.append((Le >> 8) & 0xff)
					cmd.append(Le & 0xff)
		else:
			# case3
			Lc = len(data)
			if Lc < 256:
				cmd.append(Lc)
			else:
				cmd.append(0x00)
				cmd.append((Lc >> 8) & 0xff)
				cmd.append(Lc & 0xff)
	
			cmd.extend(data)
			
			# case4
			if Le != 0:
				if Le < 256:
					cmd.append(Le)
				else:
					cmd.append(0x00)
					cmd.append((Le >> 8) & 0xff)
					cmd.append(Le & 0xff)
		usb_write(cmd)
		return usb_read(Le + 2)

	def Initinal(self):
		''' 生成SM2密钥对 '''
		self.SendAPDU("00200000")
		''' 生成SM4 加解密密钥 '''
		self.SendAPDU("00200001")
	def GetChallenge(self,len = 0x08):
		''' 获取随机数 '''
		apdu = [0x00,0x84,0x00,0x00]
		self.SendAPDU(apdu,Le=len)
	def GetPubKey(self):
		''' 获取公钥 '''
		return self.SendAPDU("00210000",Le=0x40)
	def Hash_SM3(self,data):
		''' SM3 Hash计算 '''
		# sm3 hash start
		self.SendAPDU("00300000")
		data_len = len(data)
		Hash = []
		for i in range(0,data_len,1024):
			if data_len - i > 1024:
				self.SendAPDU("00300001",data[i:i+1024])
			else:
				ret = self.SendAPDU("003000ff",data[i:],Le=32)
				Hash.extend(ret[:-2])
		return Hash

	def Sign_SM2(self,data):
		''' SM2 签名 '''
		self.Hash_SM3(data)
		# sm2 sign
		sign = self.SendAPDU("00310000",Le=0x40)
		return sign[:-2]
		
	def Verify_SM2(self,data,sign):
		''' SM2 验签 '''
		self.Hash_SM3(data)
		# sm2 sign
		self.SendAPDU("00320000",sign)
	def Encrypt_SM4(self,plain):
		data_len = len(plain)
		cipher = []
		for i in range(0,data_len,1024):
			if data_len - i > 1024:
				res = self.SendAPDU("00410000",plain[i:i+1024],Le=1024)
				cipher.extend(res[:-2])
			else:
				res = self.SendAPDU("004100ff",plain[i:],Le=len(plain[i:])+16)
				cipher.extend(res[:-2])
		return cipher
	def Decrypt_SM4(self,cipher):
		data_len = len(cipher)
		plain = []
		for i in range(0,data_len,1024):
			if data_len - i > 1024:
				res = self.SendAPDU("00420000",cipher[i:i+1024],Le=1024)
				plain.extend(res[:-2])
			else:
				res = self.SendAPDU("004200ff",cipher[i:],Le=len(cipher[i:])+16)
				plain.extend(res[:-2])
		return plain

tm = time.clock()
# ---------- START ----------
apdu = Apdu()
apdu.Initinal()
apdu.GetPubKey()


apdu.GetChallenge()
print("Time = {}s".format(time.clock() - tm))
apdu.GetChallenge(256)

data = [0x61,0x62,0x63]
for i in range(1021):
	data.append(i)
sign = apdu.Sign_SM2(data)
apdu.Verify_SM2(data,sign)

res = apdu.Encrypt_SM4(data)
apdu.Decrypt_SM4(res)

# 等待按键退出...
# os.system("pause")
# ---------- END ----------
print("Time = {}s".format(time.clock() - tm))
