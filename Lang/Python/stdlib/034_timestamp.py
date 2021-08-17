
import datetime
import time

tm = time.time()
tm_i = int(tm)
print(tm)
print(f'{tm_i:0x}')

ltm = time.localtime(tm_i)
ts = time.strftime("%Y-%m-%d %H:%M:%S", ltm)
print(ts)

now = datetime.datetime.now()
dt = now.strftime('%Y-%m-%d %H:%M:%S')
print(dt)
