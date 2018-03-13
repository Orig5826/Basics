# -*- coding: utf_8 -*-

import urllib.request
import re


def getHtml(url, code="utf8"):
    page = urllib.request.urlopen(url)
    html = page.read()
    html = html.decode(code)
    return html


url = "http://www.baidu.com/"
# url = "http://www.juzimi.com/"
html = getHtml(url)
# print(html)

print('----------------------------')
reg = r'<title>(.*)</title>' 
# reg = r'<div class="hebaddpost"><a href="/ju/[0-9]*" title="查看句子" class="hblinksen">(.?+)</a>'
imgre = re.compile(reg)
imList = re.findall(reg, html)
print(imList)
