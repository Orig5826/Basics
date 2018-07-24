# -*- coding: utf_8 -*-

# -------------------------------------------------
#                   抓取句子
# -------------------------------------------------
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

def find_maxlen_instr(ss):
    ll = ss.split("\n")
    length = 0
    # 寻找最长行长度
    for d in range(0,len(ll)):
        length = len(ll[0])
        if length < len(ll[d]):
            length = len(ll[d])
    # 返回长度最长行的内容
    for d in range(0,len(ll)):
        if length == len(ll[d]):
            return ll[d]

# info = getInfo()  # 获取带发送的内容
# ret = find_maxlen_instr(info)
# print(ret)
# -------------------------------------------------
#                   发邮件模块
# -------------------------------------------------
import smtplib
from email.mime.text import MIMEText
from email.header import Header

# 不知道为什么QQ，用什么服务授权码
sender = '********@qq.com'  # 发件人邮箱账号
my_pass = 'zawopmsvbbppbbdj'  	# 发件人邮箱授权码
receiver0 = "********@139.com"  # 接收人邮箱

def mail(content,receiver = receiver0):
    ret = True
    try:
        # content = """<p>邮件发送</p><p><a href="http://www.baidu.com">百度</a></p><br>邮件能发送成功吗?</br>"""  # 邮件内容
        msg = MIMEText(content, 'html', 'utf-8')
        msg['From'] = sender  # Header("名字", 'utf-8')  # 发件人邮箱账号
        msg['To'] = receiver  # Header("名字", 'utf-8')
        msg['Subject'] = "感悟人生"  # 邮件的主题
# 创建连接对象并连接到服务器
        server = smtplib.SMTP("smtp.qq.com")  # 发件人邮箱中的SMTP服务器，端口是25
        server.login(sender, my_pass)  # 发件人邮箱账号、授权码
        server.sendmail(sender, receiver, msg.as_string())
        server.quit()  # 关闭连接
    except Exception as e:
        ret = False
        print(e)
    return ret


# -------------------------------------------------
#                   发邮件开始
# -------------------------------------------------
info = getInfo()  # 获取带发送的内容
content = find_maxlen_instr(info)
print(content)

maddr = ['***@qq.com','***@139.com']
for i in range(0,len(maddr)):
    ret = mail(content,maddr[i])
    if ret:
        print("... 成功邮件发送至" + maddr[i])
    else:
        print("!!! 邮件发送失败 to " + maddr[i])
