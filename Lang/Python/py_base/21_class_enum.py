
from enum import Enum, EnumMeta, unique


def disp(data):
    if isinstance(data, EnumMeta):
        for name, member in data.__members__.items():
            print(name + ' => ', member, ',', member.value)
        print('--------------------------------')
    else:
        print(type(data))


# 获得Month的枚举类
Month = Enum('Month', ('Jan', 'Feb', 'Mar', 'Apr', 'May',
                       'Jun', 'Jul', 'Aug', 'Sep', 'Oct', 'Nov', 'Dec'))

# value 是从1开始的
disp(Month)

"""
    可以派生出自定义类，见下
"""

@unique
class Weekday(Enum):
    Sun = 0     # Sun的value被设定为0
    Mon = 1
    Tue = 2
    Wed = 3
    Thu = 4
    Fri = 5
    Sat = 6

disp(Weekday)

# 其他操作 or 调用方式
print(Weekday.Sun.value)
day = Weekday.Mon
print(day)
day = Weekday['Tue']
print(day)
day = Weekday(3)
print(day)

# day = Weekday.Sun
if day == Weekday.Sat or day == Weekday.Sun:
    print('Yes，放假了')
else:
    print('工作中...')
