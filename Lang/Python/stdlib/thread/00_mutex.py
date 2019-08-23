

import threading
import timeit


"""
# 简单测试了下：
# 100万次执行基本都会出现意外的结果
"""
execution_times = 1000000

# 全局的变量（线程共享）
balance = 0

# 添加线程锁
lock = threading.Lock()

def change_it(n):
    global balance
    balance += n
    balance -= n

"""
# 此处添加一个注释

try{
    //可能抛出异常
}catch(Exception e){
    //捕获异常
}finally{
    //不管有无异常都执行
}
"""

def run_thread(n):
    # for i in range(execution_times):
    #     change_it(n)

    for i in range(execution_times):
        # 当前线程获取锁，则其他线程需要等待
        lock.acquire()
        try:
            change_it(n)
        finally:
            # 释放当前线程锁，以保证不会出现死锁
            lock.release()


# ---------------------------------------------------------
timer_start = timeit.default_timer()

t1 = threading.Thread(target=run_thread, args=(5,))
t2 = threading.Thread(target=run_thread, args=(8,))

t1.start()
t2.start()
t1.join()
t2.join()

print("thread_end: balance=", balance)
timer_end = timeit.default_timer()
print("run timer={}s".format(timer_end - timer_start))


# ---------------------------------------------------------
timer_start = timeit.default_timer()
for i in range(execution_times * 2):
    change_it(111)
print("single: balance=", balance)
timer_end = timeit.default_timer()
print("run timer={}s".format(timer_end - timer_start))

"""
    做个记录：
    为什么多线程的方式还没有单线程的方式运行效率高？
    是因为线程锁的原因吗？
    还是因为我的测试方式有问题
"""
