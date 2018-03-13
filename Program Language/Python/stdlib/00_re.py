# -*- coding: utf_8 -*-
import re
import urllib.request


def getHtml(url, code="utf8"):
    page = urllib.request.urlopen(url)
    html = page.read()
    html = html.decode(code)
    return html


url = "http://www.baidu.com/"
# html = getHtml(url)
# print(html)

# test RE
reg = re.search(r'www\..*\.com', url)
print(reg.group(0))

reg = re.compile('www\..*\.com')
print(reg)
ret = re.findall(reg, url)
print(ret)
