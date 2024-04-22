
import socket
import sys
import random
import time

def time_items():
    print("|  time(s)  |    KB   |   KB/s   |   MB/s   |   Mbps   |")

def time_calc(time_diff, datalen):
    print("{:10.6f}".format(time_diff),end="")
    if time_diff >= 0.000001:
        print("{:10.2f}".format(datalen/1024),end="")
        print("{:10.2f}".format(datalen/1024/time_diff),end="")
        print("{:10.2f}".format(datalen/1024/1024/time_diff),end="")
        print("{:10.2f}".format(8*datalen/1024/1024/time_diff),end="")
    print("")

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

net_addr = ('192.168.10.135', 8080)
# net_addr = ('192.168.30.131', 8080)

try:
    # 建立连接:
    s.connect(net_addr)
except:
    print('{}:{} Connect Failed!'.format(*net_addr))
    sys.exit(-1)


print('echo test by 1024 bytes!')
time_items()


# --------------------------------
# 测试包长
package_size = 2048

# 测试轮次
count = 1000


# 生成随机数
cmd = bytearray(package_size)
for i in range(package_size):
    cmd[i] = random.randint(0,255)

# 开始计时
start_time = time.time()
for i in range(count):
    s.send(cmd)
    res = s.recv(package_size)

end_time = time.time()

# 计算代码执行的时间
time_diff = end_time - start_time
time_calc(time_diff, package_size*count)

# print(res.hex(' '))

s.close()
print('----- Disconnect -----')
