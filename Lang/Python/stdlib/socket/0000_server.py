
import threading
import socket
import time
import datetime

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

net_addr = ('127.0.0.1', 8080)

s.bind(net_addr)
s.listen(5)
print('[Server] Waiting Client Connection ...'.center(80))
print('-'*80)

def tcplink(sock, addr):
	print('-> Accept New Connection From {}:{}'.format(*addr))
	
	# 发送欢迎消息
	sock.send(b'Welcome to League of Legends!')
	
	while True:
		try:
			data = sock.recv(1024*1024)
		except:
			print('Client Cause Accidental Withdrawal')
			break
		if not data:
			break
		
		cmd = data.decode('utf-8').lower()
		# print(data)
		if cmd == 'now':
			res = time.strftime('%Y-%m-%d %H:%M:%S')
		elif cmd == '?' or cmd == 'help':
			res = '''------------------------
? -> 获取帮助
help -> 获取帮助
now -> 获取当前时间
exit -> 退出
quit -> 退出
------------------------'''
		elif cmd == 'exit' or cmd == 'quit':
			break
		else:
			res = 'ERROR: command [{}] is invalid'.format(data.decode('utf-8'))
		
		sock.send(res.encode('utf-8'))
		
	sock.close()
	print('<- Connection From {}:{} Closed.'.format(*addr))

while True:
	sock, addr = s.accept()
	t = threading.Thread(target=tcplink, args=(sock, addr))
	t.start()
