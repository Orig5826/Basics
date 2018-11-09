import smtplib
from email.mime.text import MIMEText
from email.header import Header

# 不知道为什么QQ，用什么服务授权码
sender = '########@##.com'  # 发件人邮箱账号
my_pass = '**************'  	# 发件人邮箱授权码
receiver = "#########@###.com"  # 接收人邮箱

def mail():
    ret = True
    try:
        content = """<p>邮件发送</p><p><a href="http://www.baidu.com">百度</a></p><br>邮件能发送成功吗?</br>"""  # 邮件内容
        msg = MIMEText(content, 'html', 'utf-8')
        msg['From'] = sender  # Header("名字", 'utf-8')  # 发件人邮箱账号
        msg['To'] = receiver  # Header("名字", 'utf-8')
        msg['Subject'] = "收发邮件测试"  # 邮件的主题
# 创建连接对象并连接到服务器
        server = smtplib.SMTP("smtp.qq.com")  # 发件人邮箱中的SMTP服务器，端口是25
        server.login(sender, my_pass)  # 发件人邮箱账号、授权码
        server.sendmail(sender, receiver, msg.as_string())
        server.quit()  # 关闭连接
    except Exception as e:
        ret = False
        print(e)
    return ret


ret = mail()
if ret:
    print("邮件发送成功")
else:
    print("邮件发送失败")
