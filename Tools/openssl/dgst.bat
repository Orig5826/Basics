@echo off

REM dgst 常用参数说明
REM --------------------------------
REM 1. -c用分割冒号输出摘要(-hex时)  -r以coreutils格式输出摘要？
REM 2. -hex,-binary
REM 3. -hamc 12345678
REM 4. -md5/-sha1/-sha256/-sha384/-sha512...
REM 5. -sign file/-verify file使用file中的私钥签名/公钥验签
REM 6. -prverify file使用file密钥文件验签
REM 7. -out filename输出到文件而不是标准输出
REM --------------------------------


openssl dgst -sha256 -hex openssl_tools.md
openssl dgst -sha256 -binary openssl_tools.md > dgst.bin
openssl dgst -sha256 -binary -out dgst2.bin openssl_tools.md

REM -------------------------------------------------------------
REM MAC消息认证码，构造方法可以基于hash，也可以基于对称加密算法。
REM HMAC是基于hash的消息认证码。
REM 数据和密钥作为输入，摘要信息作为输出，常用于认证

REM 命令中的密钥12345678是个字符串
openssl dgst -sha256 -hex -hmac 12345678 openssl_tools.md
openssl dgst -sha256 -r -hex -hmac 12345678 dgst.bin
pause
