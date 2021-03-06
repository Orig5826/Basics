# -*- coding: utf_8 -*-
"""
	urllib.request
"""
import urllib.request
import re


def getHtml(url, code="utf8"):

    response = urllib.request.urlopen(url)
    html = response.read().decode("utf8")
    return html

def getInfo():
    url = "http://www.juzimi.com/"
    html = getHtml(url)
    # print(html)
    reg = r'<a href="/ju/[0-9]*" title="查看句子" class="hblinksen">(.*?)</a>'
    rex = re.compile(reg)
    txt = re.findall(rex, html)

    ss = "\r\n".join(txt)
    r = re.sub("[A-Za-z0-9\[\`\~\!\@\#\$\^\&\*\(\)\=\|\{\}\'\:\;\'\,\[\]\.\<\>\/\?\~\@\#\\\&\*\%]", "", ss)
    return r

print(getInfo())