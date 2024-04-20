
import socket
import sys
import random
import time


def time_calc(time_diff, datalen):
    print("{:%0.2d}s".format(time_diff),end="")
    if time_diff != 0:
        print("{:%0.2f}B/s".format(datalen/time_diff),end="")
        print("{:%0.2f}KB/s".format(datalen/1024/time_diff),end="")
        print("{:%0.2f}MB/s".format(datalen/1024/1024/time_diff),end="")
        print("{:%0.2f}Mb/s".format(8*datalen/1024/1024/time_diff),end="")
    print("")

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

net_addr = ('192.168.10.135', 8080)

try:
    # 建立连接:
    s.connect(net_addr)
except:
    print('{}:{} Connect Failed!'.format(*net_addr))
    sys.exit(-1)


print('echo test by 1024 bytes!')
print("")
#while True:
for i in range(10):
    cmd = bytearray(1024)
    for i in range(1024):
        cmd[i] = random.randint(0,255)
        
    start_time = time.time()
    s.send(cmd)
    res = s.recv(1024)
    end_time = time.time()
    
    # 计算代码执行的时间
    time_diff = end_time - start_time
    time_calc(time_diff, 1024)
    
    # print(res.hex(' '))

s.close()
print('----- Disconnect -----')
