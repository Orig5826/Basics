# -*- coding: utf_8 -*-
import re
import urllib.request
'''
    因本文件内容，有一些是后添加的。
    若存在有不理解的代码语句，有可能需要参考
    00.re2.py文件中涉及到的技巧。
    亦或者直接参考python原文档
'''

def getHtml(url, code="utf8"):
    page = urllib.request.urlopen(url)
    html = page.read()
    html = html.decode(code)
    return html

def default_demo():
    url = "http://www.baidu.com/"
    # html = getHtml(url)
    # print(html)

    # search 在字符串开始处查找第一个匹配项
    reg = re.search(r'www\..*\.com', url)
    print(reg.group(0))

    # findall 在整个字符串中查找所有匹配项
    reg = re.compile('www\..*\.com')    #根据指定的正则表达式创建模式对象
    print(reg)
    ret = re.findall(reg, url)
    print(ret)

'''
    # 2018.11.09
    贪婪匹配问题
    1. 诸如'.','*','?' 都是贪婪匹配，而'.?','*?','??'是非贪婪匹配，或者说是最小匹配
    2. {m,n} 和 {m,n}? 的区别和以上说明类似
'''
ss = 'abcFFFFaadcP'
ret = re.findall(r'a(.*)c',ss)
print(ret)
ret = re.findall(r'a(.*?)c',ss)
print(ret)

ret = re.findall(r'F{2,4}',ss)
print(ret)
ret = re.findall(r'F{2,4}?',ss)
print(ret)

'''
    1. A|B 匹配A或者B
'''
ss = 'abcFFFFaadcP'
ret = re.findall(r'a(?:d|b)c',ss)
print(ret)
