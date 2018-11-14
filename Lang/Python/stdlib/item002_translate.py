
"""
# 有道官方实例，似乎是python2的
import random
import urllib
import md5
import httplib

# coding=utf8
appKey = '0b13f5d30d83bf9d'
secretKey = 'B5ztskhIh6vqPLW3mQSwxdv8U9kQYdsX'


httpClient = None
myurl = '/api'
q = 'good'
fromLang = 'EN'
toLang = 'zh-CHS'
salt = random.randint(1, 65536)

sign = appKey+q+str(salt)+secretKey
m1 = md5.new()
m1.update(sign)
sign = m1.hexdigest()
myurl = myurl+'?appKey='+appKey+'&q=' + \
    urllib.quote(q)+'&from='+fromLang+'&to='+toLang + \
    '&salt='+str(salt)+'&sign='+sign

try:
    httpClient = httplib.HTTPConnection('openapi.youdao.com')
    httpClient.request('GET', myurl)

    # response是HTTPResponse对象
    response = httpClient.getresponse()
    print response.read()
except Exception, e:
    print e
finally:
    if httpClient:
        httpClient.close()
"""

# 2018.11.13 by jianfeng
# 1. 直接修改为python3 示例(参考网上资料)
#   python2 -> python3
#   md5 -> hashlib.md5
#   httplib -> http.client
#   rllib.quote ->  urllib.parse.quote
# 
# 2. 利用python自带的2to3工具。
# 将2to3复制到需要转换的脚本目录下
# 使用命令 2to3 -w *.py
# 则会直接生成同名的python3脚本，py2被写入备份*.bak
# (当然了这个工具能够实现大部分转换，但偶尔也会出问题
# 那时候便需要手工调试了)
import random
import urllib
import hashlib
import http.client
import json


def translate(context):
    # 注意点
    # 1.编码都是utf8的
    # 2. appKey和secretKey都是从有道智云申请的你自己的
    # 有道智云https://ai.youdao.com/
    appKey = '0b13f5d30d83bf9d'
    secretKey = 'EUCRCf988ThQt8Fv2WaFv2W3wOaVTmj9'

    httpClient = None
    myurl = '/api'
    q = context
    fromLang = 'EN'
    toLang = 'zh-CHS'
    salt = random.randint(1, 65536)
    # 组织签名
    sign = appKey + q + str(salt) + secretKey
    # 计算md5
    sign = hashlib.md5(sign.encode()).hexdigest()

    myurl = myurl+'?appKey='+appKey+'&q=' + \
        urllib.parse.quote(q)+'&from='+fromLang+'&to='+toLang + \
        '&salt='+str(salt)+'&sign='+sign

    try:
        httpClient = http.client.HTTPConnection('openapi.youdao.com')
        httpClient.request('GET', myurl)

        # response是HTTPResponse对象
        response = httpClient.getresponse()
        jsonResponse = response.read().decode('utf-8')
        # print(jsonResponse)

        # 将json格式的结果转换字典结构
        js = json.loads(jsonResponse)
        # print(js)
        
        # 取得翻译后的文本结果
        result = '\n'.join(js['basic']["explains"])
        # print(dst)
        return result
        
    except Exception as e:
        print(e)
    finally:
        if httpClient:
            httpClient.close()


if __name__ == '__main__':
    while True:
        context = input('清输入英文单词(输入q退出):')
        # context = 'good'
        if context == 'q':
            break;
        ret = translate(context)
        print(ret)
    print('退出翻译')
