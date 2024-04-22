
import socket
import sys

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# net_addr = ('127.0.0.1', 8080)
net_addr = ('192.168.30.131', 8080)

try:
	# 建立连接:
	s.connect(net_addr)
except:
	print('{}:{} Connect Failed!'.format(*net_addr))
	sys.exit(-1)

# 接收欢迎消息
res = s.recv(2048).decode('utf-8')
print(res.center(80))
print('-'*80)

print('Please Input the Command! ')
while True:
	cmd = input('>> ')
	if cmd == 'quit' or cmd == 'exit':
		s.send(b'exit')
		break
	if not cmd:
		continue
	
	s.send(cmd.encode('utf-8'))
	
	res = s.recv(2048).decode('utf-8')
	print(res)

s.close()
