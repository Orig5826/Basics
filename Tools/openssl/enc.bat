@echo off
REM enc 常用参数说明
REM --------------------------------
REM 1. -e加密(默认)  -d解密
REM 2. 算法：-aes-128-ecb
REM 3. -a/-base64 base64加解密
REM 4. -in输入  -out输出
REM 5. -pass pase:***用户密码输入的
   REM -pass file:***用户密钥所在文件
REM 6. -S加盐(默认)  -nosalt不加盐（不建议）
REM 7. -nopad非填充方式，则明文需要为加密算法分组大小的整数倍
REM 8. -p打印文件密钥Key和IV值  -P同p，但仅显示Key和iv，不进行真正的加解密操作
REM 9. -engine指定第三方加密设备，可能是硬件设备
REM --------------------------------

echo "用户密码加密"
openssl enc -e -aes-128-ecb -in openssl_tools.md -out aes128_ecb.cipher -pass pass:12345678 -p
openssl enc -d -aes-128-ecb -in aes128_ecb.cipher -out aes128_ecb.plain -pass pass:12345678


echo "base64加解密"
openssl enc -e -base64 -in openssl_tools.md -out base64.cipher
openssl enc -d -base64 -in base64.cipher -out base64.plain


echo "指定Key和Iv加解密"
openssl enc -e -aes-128-cbc -in openssl_tools.md -out aes128_cbc.cipher -K 11223344 -iv 12345678 -nosalt -p
openssl enc -d -aes-128-cbc -in aes128_cbc.cipher -out aes128_cbc.plain -K 11223344 -iv 12345678 -nosalt
