@echo off

echo "1. 对openssl_tools.md文件中的内容做签名，Hash算法选择sha256"
openssl dgst -sign rsa_pri_key.pem -sha256 -out sha256_rsa_sign.bin openssl_tools.md

echo "2. verify验签"
openssl dgst -verify rsa_pub_key.pem -sha256 -signature sha256_rsa_sign.bin openssl_tools.md

echo "3. prverify验签"
openssl dgst -prverify rsa_pri_key.pem -sha256 -signature sha256_rsa_sign.bin openssl_tools.md

pause
