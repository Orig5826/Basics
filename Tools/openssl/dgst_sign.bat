@echo off

echo "1. ��openssl_tools.md�ļ��е�������ǩ����Hash�㷨ѡ��sha256"
openssl dgst -sign rsa_pri_key.pem -sha256 -out sha256_rsa_sign.bin openssl_tools.md

echo "2. verify��ǩ"
openssl dgst -verify rsa_pub_key.pem -sha256 -signature sha256_rsa_sign.bin openssl_tools.md

echo "3. prverify��ǩ"
openssl dgst -prverify rsa_pri_key.pem -sha256 -signature sha256_rsa_sign.bin openssl_tools.md

pause
