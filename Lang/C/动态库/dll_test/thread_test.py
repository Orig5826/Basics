
from ctypes import *
from time import sleep
import threading
import timeit

api = windll.LoadLibrary("./Debug/dll_test.dll")

api.num_set(1)
print(api.num_get())

api.num_set(2)
print(api.num_get())

num = api.g_num
print(type(num))
print(string_at(num,sizeof(num)))


def run_thread1(n):
    print("----- thread={} -----".format(n))
    for i in range(10):
        print(api.num_get())
       

def run_thread(n):
    print("----- thread={} -----".format(n))
    for i in range(10):
        api.num_set(i)

t1 = threading.Thread(target=run_thread, args=(5,))
t2 = threading.Thread(target=run_thread1, args=(8,))

t2.start()
t1.start()


t1.join()
t2.join()
