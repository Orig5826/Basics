
import html

'''
    HTML转义字符
'''
r = html.escape('<123>(&.&)')
print(r)

r = html.unescape('&quot;I am Bruce&quot;128&#165;')
print(r)
