@echo off
echo 1.0 准备CA配置文件ca.conf
echo 1.1 生成CA密钥ca.key
openssl genrsa -out ca.key 2048
echo 1.2 生成CA证书签发请求ca.csr
openssl req -new -sha256 -key ca.key -config ca.conf -out ca.csr 
echo 1.3 生成CA根证书ca.crt
openssl x509 -req -days 3650 -in ca.csr -signkey ca.key -out ca.crt


echo 2.0 准备配置文件server.conf
echo 2.1 生成密钥server.key
openssl genrsa -out server.key 2048
echo 2.2 生成证书签发请求server.csr
openssl req -new -sha256 -key server.key -config server.conf -out server.csr 
echo 2.3 用CA证书生成终端用户证书
openssl x509 -req -days 365 -CA ca.crt -CAkey ca.key -CAcreateserial -in server.csr -extensions req_ext -extfile server.conf -out server.crt

pause
