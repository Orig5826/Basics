import datetime
import win32api # need pywin32

def set_system_time(year, month, day, hour, minute, second):
    # 创建一个新的日期和时间对象
    new_time = datetime.datetime(year, month, day, hour, minute, second)
    
    # 计算从 1601-01-01 到新时间的总秒数，乘以 10000000 转换为 100 纳秒数
    win_time = (new_time - datetime.datetime(1601, 1, 1)).total_seconds() * 10000000
    
    # 使用 win32api.SetSystemTime 函数设置系统时间
    win32api.SetSystemTime(new_time.year, new_time.month, new_time.weekday(), new_time.day, new_time.hour - 8, new_time.minute, new_time.second, int(win_time % 10000000))


if __name__ == "__main__":
    # 调用函数设置系统时间，例如设置为 2025 年 1 月 13 日 15 点 30 分 0 秒
    set_system_time(2025, 1, 13, 12, 0, 0)
