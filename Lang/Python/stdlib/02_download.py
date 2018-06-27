# -*- coding: utf_8 -*-
import urllib.request
import re
import os


def getHtml(url, code="utf8"):
    response = urllib.request.urlopen(url)
    html = response.read().decode(code)
    return html


def getImg(reg, html):
    imgre = re.compile(reg)
    imglist = re.findall(imgre, html)
    x = 0
    for imgurl in imglist:
        imgurl = "http:" + imgurl
        urllib.request.urlretrieve(imgurl, './resource/%s.png' % x)
        x += 1


def savTxt(txt, file):
    fd = open(file, mode='w')
    for str in txt:
        fd.write(str)
    fd.close()


url = "http://www.baidu.com/"
html = getHtml(url)
# print(html)

# 若目录不存在则创建
path = "./resource/"
if not os.path.exists(path):
	os.mkdir(path)

reg = r'<title>(.*?)</title>'
regx = re.compile(reg)
txt = re.findall(regx, html)
savTxt(txt, "./resource/a.txt")
print(txt)

reg = r'src="(.+?\.png)"'
getImg(reg, html)
reg = r'src="(.+?\.gif)"'
getImg(reg, html)
