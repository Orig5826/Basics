
"""
# 有道官方实例，似乎是python2的
import random
import urllib
import md5
import httplib

# coding=utf8
appKey = '0b13f5d30d83bf9d'
secretKey = 'B5ztskhIh6vqPLW3mQSwxdv8U9kQYdsX


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
# 修改未python3 示例
# python2 -> python3
# md5 -> hashlib.md5
# httplib -> http.client
#  rllib.quote ->  urllib.parse.quote
import random
import urllib
import hashlib
import http.client
import json

# 注意点
# 1.编码都是utf8的
# 2. appKey和secretKey都是从有道智云申请的你自己的
# 有道智云https://ai.youdao.com/
appKey = '*b13f5d30d83bf9d'
secretKey = 'EUCRCf988ThQt8Fv2WaFv2W3wOaVTmj*'


httpClient = None
myurl = '/api'
q = 'good'
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
    print(jsonResponse)

    js = json.loads(jsonResponse)  # 将json格式的结果转换字典结构
    dst = str(js["explain"])  # 取得翻译后的文本结果
    print(dst)

except Exception as e:
    print(e)
finally:
    if httpClient:
        httpClient.close()

"""
这个json报文的解析还有问题，先学习一下报文解析之后，再开始操作吧
{"tSpeakUrl":"http://openapi.youdao.com/ttsapi?q=%E5%A5%BD&langType=zh-CHS&sign=9DEB8FE960F816763F977691C429078B&salt=1542121873261&voice=4&format=mp3&appKey=0b13f5d30d83bf9d","web":[{"value":["好的","善","良好","商品"],"key":"good"},{"value":["耶稣受难节","耶稣受难日","受难节","受难日"],"key":"Good Friday"},{"value":["吉芬商品","吉芬物品","吉芬品","季芬财"],"key":"Giffen Good"}],"query":"good","translation":["好"],"errorCode":"0","dict":{"url":"yddict://m.youdao.com/dict?le=eng&q=good"},"webdict":{"url":"http://m.youdao.com/dict?le=eng&q=good"},"basic":{"us-phonetic":"ɡʊd","phonetic":"gʊd","uk-phonetic":"gʊd","wfs":[{"wf":{"name":"比较级","value":"better"}},{"wf":{"name":"最高级","value":"best"}}],"uk-speech":"http://openapi.youdao.com/ttsapi?q=good&langType=en&sign=06AC4C6ACF1C7E672CB5038DD1C6E0F6&salt=1542121873261&voice=5&format=mp3&appKey=0b13f5d30d83bf9d","explains":["adj. 好的；优良的；愉快的；虔诚的","n. 好处；善行；慷慨的行为","adv. 好","n. (Good)人名；(英)古德；(瑞典)戈德"],"us-speech":"http://openapi.youdao.com/ttsapi?q=good&langType=en&sign=9828888B8EF683D1DF7BFA83AF07340A&salt=1542121873262&voice=6&format=mp3&appKey=0b13f5d30d83bf9d"},"l":"EN2zh-CHS","speakUrl":"http://openapi.youdao.com/ttsapi?q=good&langType=en&sign=06AC4C6ACF1C7E672CB5038DD1C6E0F6&salt=1542121873261&voice=4&format=mp3&appKey=0b13f5d30d83bf9d"}
"""
