import statistics as stats
a = []
for i in range(11):
    a.append(i)
print(a)

# 均值
ret = stats.mean(a)
print('the average/mean value is {:0.2f}'.format(ret))
# 中位数
ret = stats.median(a)
print('the meidan value is {:0.2f}'.format(ret))
# 方差
ret = stats.variance(a)
print('the variance is {:0.2f}'.format(ret))
## ---------------------------------------------------
# 若需要更多的数值运算，手动添加scipy工具包
