@echo off

echo "1.1 ����PEM����˽Կ�ļ�"
openssl genrsa -out rsa_pri_key.pem	1024

echo "1.2 ���ɵ�PEM�����ļ��Ѿ���������"
REM ��һ����Ҫ�ֶ����룬�ڶ�������ֱ��ָ��
REM openssl genrsa -des -out rsa_pri_key2.pem 1024
openssl genrsa -des -passout pass:12345678 -out rsa_pri_key2.pem 1024

echo "2.0 ��PEM����(base64)ת��ΪDER����(������)"
openssl enc -d -base64 -in rsa_pri_key.pem -out rsa_pri_key.der

echo "3.0 ��ȡ˽Կ���ݣ���ʾ��stdout��"
openssl rsa -in rsa_pri_key.pem

echo "3.1 �Դ��ı���ʽ���˽Կ���ݣ������ĸ���˽Կ��"
openssl rsa -in rsa_pri_key.pem -text -out rsa.pri -noout
REM -noout �������Կ����
REM �������������Ӹò���֮����pem��ʽ�����ݲ��ٴ�����������ʾһ������Ҫ����Կ����

echo "4.0 ��˽Կ����ȡ��Կ"
openssl rsa -in rsa_pri_key.pem -pubout -out rsa_pub_key.pem

echo "5.0 ��ȡ��Կ���ݣ���ʾ��stdout��"
openssl rsa -pubin -in rsa_pub_key.pem

echo "5.1 �Դ��ı���ʽ�����Կ����"
openssl rsa -pubin -in rsa_pub_key.pem -out rsa.pub -text -noout
