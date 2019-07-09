@echo off
echo 1.0 ׼��CA�����ļ�ca.conf
echo 1.1 ����CA��Կca.key
openssl genrsa -out ca.key 2048
echo 1.2 ����CA֤��ǩ������ca.csr
openssl req -new -sha256 -key ca.key -config ca.conf -out ca.csr 
echo 1.3 ����CA��֤��ca.crt
openssl x509 -req -days 3650 -in ca.csr -signkey ca.key -out ca.crt


echo 2.0 ׼�������ļ�server.conf
echo 2.1 ������Կserver.key
openssl genrsa -out server.key 2048
echo 2.2 ����֤��ǩ������server.csr
openssl req -new -sha256 -key server.key -config server.conf -out server.csr 
echo 2.3 ��CA֤�������ն��û�֤��
openssl x509 -req -days 365 -CA ca.crt -CAkey ca.key -CAcreateserial -in server.csr -extensions req_ext -extfile server.conf -out server.crt

pause
