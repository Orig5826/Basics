
import html

'''
    HTML转义字符和普通字符串 相互切换
'''
r = html.escape('<123>(&.&)')
print(r)

r = html.unescape('&quot;I am Bruce&quot;128&#165;')
print(r)
