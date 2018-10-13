
import os
import calc_module as calc

print("乘方计算：")
for i in range(100):
    ret = calc.py_get_squre(i)
    print("{0:4d}={1:4.0f}  ".format(i, ret), end='')
    if (i+1) % 10 == 0:
        print()

os.system("pause")
