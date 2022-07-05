"""
    2022-07-05 by jianfeng
"""
import urllib.request
import json
import re

# -------------------------------
# 模式选择
# -------------------------------
CRC_CUSTOM = -1
# poly=1021
CRC_CCIT_KERMIT = 0
CRC_CCIT_XMODEM = 1
CRC_CCIT_FALSE = 2
CRC_CCIT_GENIBUS = 3
CRC_CCIT_X_25 = 4
CRC_CCIT_MCRF4XX = 5
CRC_CCIT_AUG_CCIT = 6
CRC_CCIT_TMS37157 = 7
CRC_CCIT_RIELLO = 8
CRC_CCIT_CRC_A = 9
# poly=8005
CRC_16_BUYPASS = 10
CRC_16_ARC = 11
CRC_16_MODBUS = 12
CRC_16_MAXIM = 13
CRC_16_USB = 14
CRC_16_DDS_110 = 15


class CRC():
    def __init__(self):
        self.set_mode()
        self.__crcInit()

    def set_mode(self, mode=CRC_CCIT_XMODEM):
        # CRC_CCIT_XMODEM
        self.width = 16
        self.poly = 0x1021
        self.init = 0x0000
        self.final = 0x0000
        self.refin = False
        self.refout = False
        self.mode = mode
        self.endian = True

        # ------------------------------------
        # poly=1021
        if mode == CRC_CCIT_KERMIT:
            self.refin = True
            self.refout = True
        elif mode == CRC_CCIT_XMODEM:
            pass
        elif mode == CRC_CCIT_FALSE:
            self.init = 0xFFFF
        elif mode == CRC_CCIT_FALSE:
            self.init = 0xFFFF
        elif mode == CRC_CCIT_GENIBUS:
            self.init = 0xFFFF
            self.final = 0xFFFF
        elif mode == CRC_CCIT_X_25:
            self.init = 0xFFFF
            self.final = 0xFFFF
            self.refin = True
            self.refout = True
        elif mode == CRC_CCIT_MCRF4XX:
            self.init = 0xFFFF
        elif mode == CRC_CCIT_AUG_CCIT:
            self.init = 0x1D0F
        elif mode == CRC_CCIT_TMS37157:
            self.init = 0x89EC
            self.refin = True
            self.refout = True
        elif mode == CRC_CCIT_RIELLO:
            self.init = 0xB2AA
            self.refin = True
            self.refout = True
        elif mode == CRC_CCIT_CRC_A:
            self.init = 0xC6C6
            self.refin = True
            self.refout = True
        # ------------------------------------
        # poly=8005
        elif mode == CRC_16_BUYPASS:
            self.poly = 0x8005
        elif mode == CRC_16_ARC:
            self.poly = 0x8005
            self.refin = True
            self.refout = True
        elif mode == CRC_16_MODBUS:
            self.poly = 0x8005
            self.init = 0xFFFF
            self.refin = True
            self.refout = True
        elif mode == CRC_16_MAXIM:
            self.poly = 0x8005
            self.final = 0xFFFF
            self.refin = True
            self.refout = True
        elif mode == CRC_16_USB:
            self.poly = 0x8005
            self.init = 0xFFFF
            self.final = 0xFFFF
            self.refin = True
            self.refout = True
        elif mode == CRC_16_DDS_110:
            self.poly = 0x8005
            self.init = 0x800D
        else:
            print('自定义')
            pass

    def set_width(self, width=16):
        self.width = width

    def set_poly(self, poly=0x1021):
        self.poly = poly

    def set_init(self, init=0x0000):
        self.init = init

    def set_final(self, final=0x000):
        self.final = final

    def reverse_in(self, refin=False):
        self.refin == refin

    def reverse_out(self, refout=False):
        self.refout == refout

    def set_endian(self, endian=False):
        self.endian = endian

    def __swap(self, hexstr):
        if self.mode != CRC_CUSTOM:
            if self.swap_flag[self.mode] == 1:
                return hexstr[-2:] + hexstr[0:2]
        return hexstr

    def get_mode(self):
        mode_dict = dict(CRC_CCIT_KERMIT=0,
                         CRC_CCIT_XMODEM=1,
                         CRC_CCIT_FALSE=2,
                         CRC_CCIT_GENIBUS=3,
                         CRC_CCIT_X_25=4,
                         CRC_CCIT_MCRF4XX=5,
                         CRC_CCIT_AUG_CCIT=6,
                         CRC_CCIT_TMS37157=7,
                         CRC_CCIT_RIELLO=8,
                         CRC_CCIT_CRC_A=9,
                         CRC_16_BUYPASS=10,
                         CRC_16_ARC=11,
                         CRC_16_MODBUS=12,
                         CRC_16_MAXIM=13,
                         CRC_16_USB=14,
                         CRC_16_DDS_110=15)

        return list(mode_dict.keys())[list(mode_dict.values()).index(self.mode)]

    def __crcInit(self):
        self.crcTable = {}

        SHIFT = self.width - 8
        topbit = 1 << (self.width - 1)
        for step in range(0, 256):
            remainder = step << SHIFT
            for bit in range(8, 0, -1):
                if remainder & topbit:
                    remainder = ((remainder << 1) & 0xFFFF) ^ self.poly
                else:
                    remainder = remainder << 1
            self.crcTable[step] = remainder

    def __crcReverse(self, data, bitcnt):
        if bitcnt == 8:
            data = (data & 0xF0) >> 4 | (data & 0x0F) << 4
            data = (data & 0xCC) >> 2 | (data & 0x33) << 2
            data = (data & 0xAA) >> 1 | (data & 0x55) << 1
        elif bitcnt == 16:
            data = (data & 0xFF00) >> 8 | (data & 0x00FF) << 8
            data = (data & 0xF0F0) >> 4 | (data & 0x0F0F) << 4
            data = (data & 0xCCCC) >> 2 | (data & 0x3333) << 2
            data = (data & 0xAAAA) >> 1 | (data & 0x5555) << 1
        else:
            return False
        return data

    def __crcFast(self, data):
        """
            查表法实现
        """
        # for i in range(len(crcTable)):
        #	print('{0:04x}\t'.format(crcTable[i]),end='')
        length = len(data)
        crc_value = self.init
        for i in range(length):
            """
                refin 输入bit逆序
            """
            temp = crc_value >> 0x08
            if self.refin == True:
                temp ^= self.__crcReverse(data[i], 8)
            else:
                temp ^= data[i]
            crc_value = (self.crcTable[temp & 0xFF] ^ (
                (crc_value << 8) & 0xFFFF)) & 0xFFFF
        """
            refout 输出bit逆序
        """
        if self.refout == True:
            # print('crc_value = ',hex(crc_value))
            crc_value = self.__crcReverse(crc_value, 16)

        """
            异或
        """
        crc_value ^= self.final

        res_str = '{0:04x}'.format(crc_value)
        return bytes.fromhex(res_str)

    def crc_calc(self, data):
        if not isinstance(data, list):
            return False
        bb = self.__crcFast(data)
        return list(bb)

    def crc_mode_test(self, data):
        print("----- 原始数据 ----- ")
        print(bytes(data).hex())
        print("----- CRC 计算 ----- ")
        for i in range(16):
            crc.set_mode(i)
            crc_result = crc.crc_calc(data)
            mode = crc.get_mode()
            print('{0:20s} = {1}'.format(mode, bytes(crc_result).hex()))
        print(' ----- END ----- ')

if __name__ == '__main__':
    data = [0x33,0x32,0x43,0x31,0x56,0x36,0x2E,0x30,0x90,0x00]
    print(bytes(data).hex())
    crc = CRC()
    crc.crc_mode_test(data)
