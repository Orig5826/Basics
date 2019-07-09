@echo off

echo "1.1 生成PEM编码私钥文件"
openssl genrsa -out rsa_pri_key.pem	1024

echo "1.2 生成的PEM编码文件已经被加密了"
REM 第一个需要手动输入，第二个则是直接指定
REM openssl genrsa -des -out rsa_pri_key2.pem 1024
openssl genrsa -des -passout pass:12345678 -out rsa_pri_key2.pem 1024

echo "2.0 将PEM编码(base64)转换为DER编码(二进制)"
openssl enc -d -base64 -in rsa_pri_key.pem -out rsa_pri_key.der

echo "3.0 读取私钥内容，显示到stdout上"
openssl rsa -in rsa_pri_key.pem

echo "3.1 以纯文本格式输出私钥内容？具体哪个是私钥？"
openssl rsa -in rsa_pri_key.pem -text -out rsa.pri -noout
REM -noout 不输出密钥内容
REM 例如以上命令，添加该参数之后，则pem格式的数据不再带出来。仅显示一种你需要的密钥数据

echo "4.0 从私钥中提取公钥"
openssl rsa -in rsa_pri_key.pem -pubout -out rsa_pub_key.pem

echo "5.0 读取公钥内容，显示到stdout上"
openssl rsa -pubin -in rsa_pub_key.pem

echo "5.1 以纯文本格式输出公钥内容"
openssl rsa -pubin -in rsa_pub_key.pem -out rsa.pub -text -noout
