import serial
import signal
import time
import sys

class Uart():
    def __init__(self, num):
        self.uart_status = 0
        com = "COM{}".format(num)
        """
        self.ser = serial.Serial()
        self.ser.com = com
        self.ser.boud = 115200
        self.ser.timerout = 0.5
        """
        try:
            self.ser = serial.Serial(com, 115200, timeout=0.5)
            print("----- 串口{}打开 -----".format(self.ser.name))
            self.uart_status = 1
        except:
            print("----- 串口{}打开失败 -----".format(com))
            sys.exit(-1)
    def __del__(self):
        if self.uart_status == 1:
            self.ser.close()
            print("----- 串口{}关闭 -----".format(self.ser.name))
    def __write(self, b_data):
        print("-> ",b_data.hex())
        try:
            self.ser.write(b_data)
            return True
        except:
            print('发送数据时通讯错误')
            return False
    def __read(self):
        res = bytearray()
        while True:
            try:
                bb = self.ser.read()
                if bb == b'':
                    break
                res.extend(bb)
            except:
                print('发送数据时通讯错误')
                break
        print("<- ",res.hex())
        return res

    def send(self, cmd):
        """
            @param bytes/hexstr
            @return bytes
        """
        if not isinstance(cmd, bytes) and not isinstance(cmd,bytearray):
            return False
        self.__write(cmd)
        res = self.__read()
        return res


# example

"""
com = Uart(1)
cmd = bytes.fromhex("00244110002040BB12DD6A8273867F3529D354B4A026FFEEDDCCBBAA99887766554433221100")
res = com.send(cmd)
# print(res)
"""