@echo off
REM enc ���ò���˵��
REM --------------------------------
REM 1. -e����(Ĭ��)  -d����
REM 2. �㷨��-aes-128-ecb
REM 3. -a/-base64 base64�ӽ���
REM 4. -in����  -out���
REM 5. -pass pase:***�û����������
   REM -pass file:***�û���Կ�����ļ�
REM 6. -S����(Ĭ��)  -nosalt�����Σ������飩
REM 7. -nopad����䷽ʽ����������ҪΪ�����㷨�����С��������
REM 8. -p��ӡ�ļ���ԿKey��IVֵ  -Pͬp��������ʾKey��iv�������������ļӽ��ܲ���
REM 9. -engineָ�������������豸��������Ӳ���豸
REM --------------------------------

echo "�û��������"
openssl enc -e -aes-128-ecb -in openssl_tools.md -out aes128_ecb.cipher -pass pass:12345678 -p
openssl enc -d -aes-128-ecb -in aes128_ecb.cipher -out aes128_ecb.plain -pass pass:12345678


echo "base64�ӽ���"
openssl enc -e -base64 -in openssl_tools.md -out base64.cipher
openssl enc -d -base64 -in base64.cipher -out base64.plain


echo "ָ��Key��Iv�ӽ���"
openssl enc -e -aes-128-cbc -in openssl_tools.md -out aes128_cbc.cipher -K 11223344 -iv 12345678 -nosalt -p
openssl enc -d -aes-128-cbc -in aes128_cbc.cipher -out aes128_cbc.plain -K 11223344 -iv 12345678 -nosalt
