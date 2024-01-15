from usbhid import usbhid
import sys
import threading
import time
import random

hid = usbhid()
ret = hid.open(0x084B,0x4853)
if ret != True:
	sys.exit(-1)
# hid.disp_info()
# hid.set_debug_level(1)


# hid.
def hid_write(data):
	block_size = 64

	total_length = len(data)
	offset = 0
	length = total_length
	
	__data = [0] * 64
	while length > block_size:
		__data[0:block_size] = data[offset:offset + block_size]
		hid.setfeature(__data)
		length -= block_size
		offset += block_size
	
	__data = [0] * 64
	if length != 0:
		__data[0:0+length] = data[offset:offset + length]
		hid.setfeature(__data)

def hid_read():
	data = []
	for i in range(5):
		__data = hid.getfeature(64)
		data.extend(__data)
	return data

	
# -------------------------------------------
def disp_hid_info():
	print("thread %s is start" % threading.current_thread().name)
	while True:
		print('')
		hid.disp_info()
		
		delay_ms = random.uniform(0,5.0)
		print('延时{0:0.2f}s再插入下一条命令'.format(delay_ms))
		time.sleep(delay_ms)
		# break
	print("thread %s is end" % threading.current_thread().name)

# --------------
def feature_test():
	print("thread %s is start" % threading.current_thread().name)
	data = []
	for i in range(292):
		data.append(i)

	while True:
		print('.',end='',flush=True)
		hid_write(data)
		hid_read()
		# break
	print("thread %s is end" % threading.current_thread().name)

# -------------------------------------------
print("thread %s is start" % threading.current_thread().name)

t1 = threading.Thread(target=disp_hid_info, name='disp_hid_info')
t2 = threading.Thread(target=feature_test, name='feature_test')

t1.start()
t2.start()

t1.join()
t2.join()

print("thread %s is end" % threading.current_thread().name)
