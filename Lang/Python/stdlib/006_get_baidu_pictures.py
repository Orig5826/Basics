# -*- coding: utf_8 -*-
"""
    最初的时候，百度图片一直下载失败。
    后来仔细分析了网页源码，理解并明白从何处下载
    从而实现该脚本。（原理都相似，实现略有区别而已）
"""
import urllib
import urllib.request
import re
import os
import sys

def getHtml(url, code="utf8"):

    response = urllib.request.urlopen(url)
    html = response.read().decode("utf8")
    return html


def getImg(html):
    reg = r'"objURL":"(.+?\.jpg)",'
    imgre = re.compile(reg)
    imglist = re.findall(imgre, html)
    # print(imglist)

    if not os.path.exists(r'.\image'):
        os.mkdir(r'.\image')

    x = 0
    for imgurl in imglist:
        try:
            print('%s.jpg'%x,end='')
            urllib.request.urlretrieve(imgurl, r'.\image\%s.jpg' % x)
            print(' -> download finished!')
            x += 1
        except:
            print('-> [%d] url错误，跳过。重新下载下一个' % x)
            pass
    if os.path.exists(r'.\image\0.jpg'):
        os.remove(r'.\image\0.jpg')


if __name__ == '__main__':
    # url = "http://image.baidu.com/search/index?tn=baiduimage&ct=201326592&lm=-1&cl=2&ie=gb18030&word=%B0%D9%B6%C8%B1%DA%D6%BD&fr=ala&ala=1&pos=0&alatpl=wallpaper&oriquery=%E7%99%BE%E5%BA%A6%E5%A3%81%E7%BA%B8"
    
    if len(sys.argv) != 2:
        print('Please add the download address!')
        sys.exit(-1)
    url = sys.argv[1]
    html = getHtml(url)
    # print(html)
    getImg(html)
    print('download ok!')
