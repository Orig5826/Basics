import serial
import signal


ser = serial.Serial("COM3", 115200, timeout=0.5)

# 主要是暂时不知道这两个参数都是用来做什么的
# 哈哈哈，先定义为what??好了
# 以后理解了之后再进行修改


def signal_int(what01, what02):
    print("退出2")
    exit(0)


signal.signal(signal.SIGINT, signal_int)

print(ser.name)
print(ser.port)
while True:
    string = ser.readline()
    print(string)

ser.close()
