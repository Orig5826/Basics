
# 注意小数精度问题
from decimal import Decimal
a = 0.1 + 0.2
if a != 0.3:
    print("a: {}".format(a))
else:
    print("a == 0.3")

# 格式化后的依然不行？
c = "%.1f" % a
if c != 0.3:
    print("c: {}".format(c))
else:
    print("c == 0.3")

# 导入decimal模块，用来对比小数
b = Decimal('0.1') + Decimal('0.2')
if b != 0.3:
    print("b: {}".format(b))
else:
    print("b == 0.3")
if b == Decimal('0.3'):
    print("b == Decimal('0.3')")
