@echo off

REM dgst ���ò���˵��
REM --------------------------------
REM 1. -c�÷ָ�ð�����ժҪ(-hexʱ)  -r��coreutils��ʽ���ժҪ��
REM 2. -hex,-binary
REM 3. -hamc 12345678
REM 4. -md5/-sha1/-sha256/-sha384/-sha512...
REM 5. -sign file/-verify fileʹ��file�е�˽Կǩ��/��Կ��ǩ
REM 6. -prverify fileʹ��file��Կ�ļ���ǩ
REM 7. -out filename������ļ������Ǳ�׼���
REM --------------------------------


openssl dgst -sha256 -hex openssl_tools.md
openssl dgst -sha256 -binary openssl_tools.md > dgst.bin
openssl dgst -sha256 -binary -out dgst2.bin openssl_tools.md

REM -------------------------------------------------------------
REM MAC��Ϣ��֤�룬���췽�����Ի���hash��Ҳ���Ի��ڶԳƼ����㷨��
REM HMAC�ǻ���hash����Ϣ��֤�롣
REM ���ݺ���Կ��Ϊ���룬ժҪ��Ϣ��Ϊ�������������֤

REM �����е���Կ12345678�Ǹ��ַ���
openssl dgst -sha256 -hex -hmac 12345678 openssl_tools.md
openssl dgst -sha256 -r -hex -hmac 12345678 dgst.bin
pause
