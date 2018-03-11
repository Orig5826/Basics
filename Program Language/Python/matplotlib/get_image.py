# -*- coding: utf_8 -*-
"""
	从贴吧，爬几个简单的图，还存在一些问题
	似乎需要先在当前目录下创建image文件夹
"""
import urllib
import urllib.request
import re


def getHtml(url, code="utf8"):

    response = urllib.request.urlopen(url)
    html = response.read().decode("utf8")
    return html


def getImg(html):
    reg = r'src="(.+?\.jpg)"'  # 正则表达式，得到图片地址
    imgre = re.compile(reg)
    imglist = re.findall(imgre, html)
    print(imglist)
    # 核心是urllib.urlretrieve()方法,直接将远程数据下载到本地，图片通过x依次递增命名
    x = 0
    for imgurl in imglist:
        urllib.request.urlretrieve(imgurl, '.\image\%s.jpg' % x)
        x += 1

# 应该是该网页上直接有原图的话，可以直接下载，否则需要跳转
# 我猜测。
# 要不然我怎么down不下来百度图片呢？
url = "https://tieba.baidu.com/p/5547163950"
html = getHtml(url)
# print(html)
getImg(html)
print('download ok!')
