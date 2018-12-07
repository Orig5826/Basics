# -*- coding: utf_8 -*-
"""
    最初的时候，百度图片一直下载失败。
    后来仔细分析了网页源码，理解并明白从何处下载
    从而实现该脚本。（原理都相似，实现略有区别而已）
"""
import urllib
import urllib.request
import json
import re
import os
import sys


def get_keyword(url):
    reg = re.compile(r'word=(.*)$')
    key_word = re.findall(reg, url)[0]
    print(key_word)

    # 显示关键字
    hexstr = key_word.replace('%', '')
    word = bytes.fromhex(hexstr)
    word_disp = word.decode('utf-8')
    print(word_disp)
    # 返回为 HTML转义后的
    return key_word


def get_html(url, code="utf8"):

    response = urllib.request.urlopen(url)
    html = response.read().decode(code)
    return html


def get_image(html, path='./', index=0):
    reg = r'"objURL":"(.+?\.jpg)",'
    imgre = re.compile(reg)
    imglist = re.findall(imgre, html)
    # print(imglist)

    x = index
    for imgurl in imglist:
        print(imgurl)
        try:
            fname = path + '{0}.jpg'.format(x)
            print(fname, end='')
            urllib.request.urlretrieve(imgurl, fname)
            print(' -> download finished!')
            x += 1
        except:
            print('-> [%d] url错误，跳过。重新下载下一个' % x)
            pass
    return x


def image_download(url, index=0, page=1):
    path = './image/'
    if not os.path.exists(path):
        os.mkdir(path)
    # 获取关键字
    key_word = get_keyword(url)

    x = index
    for i in range(page):
        url_next = 'https://image.baidu.com/search/acjson?tn=resultjson_com&ipn=rj\
                    &ct=201326592&is=&fp=result\&queryWord={0}&cl=2&lm=-1&ie=utf-8\
                    &oe=utf-8&adpicid=&st=-1&z=&ic=0&hd=&latest=&copyright=&word={0}\
                    &s=&se=&tab=&width=&height=&face=0&istype=2&qc=&nc=1&fr=&expermode=\
                    &selected_tags=&pn={1}&rn=30&gsm={2}&1544193388557=\
                    '.format(key_word, i*30, hex(i*30).replace('0x', ''))
        if i == 0:
            html = get_html(url)
        else:
            html = get_html(url_next)

        # print(html)
        x = get_image(html, path, x)


if __name__ == '__main__':
    index = 0
    if len(sys.argv) == 1:
        url = 'https://image.baidu.com/search/index?tn=baiduimage&ipn=r&ct=201326592&cl=2&lm=-1&st=-1&sf=1&fmq=&pv=&ic=0&nc=1&z=&se=1&showtab=0&fb=0&width=&height=&face=0&istype=2&ie=utf-8&fm=index&pos=history&word=%E6%98%9F%E7%90%83%E5%A3%81%E7%BA%B8'
    elif len(sys.argv) == 2:
        url = sys.argv[1]
    elif len(sys.argv) == 3:
        url = sys.argv[1]
        index = int(sys.argv[2], 10)
    else:
        print('Please add the download address!')
        sys.exit(-1)

    image_download(url, index=0, page=2)
