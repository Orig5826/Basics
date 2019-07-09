# openssl 用法详解
`2019.04.13 by jiafeng`

### Openssl 组成
1. openssl 多用途命令行工具
2. libctypro 加密算法库
3. libssl 加密模块应用库，实现ssl和tls


### 多用途命令行工具
- 对称加密 enc
	1. -e加密(默认)  -d解密
	2. -aes-128-ecb 指定算法
	3. -a/-base64 base64加解密
	4. -in输入  -out输出
	5. -pass pase:1234用户密码输入的  -pass file:keyfile用户密钥所在文件
	6. -S加盐(默认)  -nosalt不加盐（不建议）
	7. -nopad非填充方式，则明文需要为加密算法分组大小的整数倍
	8. -p打印文件密钥Key和IV值  -P同p，但仅显示Key和iv，不进行真正的加解密操作
	9. -engine指定第三方加密设备，可能是硬件设备
	
- 摘要算法 dgst
	1. -c用分割冒号输出摘要(-hex时)  -r以coreutils格式输出摘要？
	2. -hex,-binary
	3. -hamc 12345678
	4. -md5/-sha1/-sha256/-sha384/-sha512...
	5. -sign file/-verify file使用file中的私钥签名/公钥验签
	6. -prverify file使用file密钥文件验签
	7. -out filename输出到文件而不是标准输出
	
- 生成rsa密钥指令 genrsa
	> 此处详细指令，不再解释。可以参考genrsa.bat
	- PEM文件格式相关说明
		- ----BEGIN RSA PRIVATE KEY----- and -----END RSA PRIVATEKEY-----
			> RSA私钥
		- ----BEGIN PUBLIC KEY----- and -----END PUBLIC KEY-----
			> 公钥
		- -----BEGIN CERTIFICATE REQUEST----- and -----END CERTIFICATEREQUEST-----
			> CSR(证书签名请求)
		- -----BEGIN CERTIFICATE----- and -----END CERTIFICATE-----
			> 证书文件
	
	- 将PEM输出 带有-text的时候，相当于把密钥以带有冒号分割的16进制数据显示出来。
		- Modulus
			> N 合数模
		- publicExponent
			> E 公开幂
		- privateExponent
			> D(ND模式的私钥) 私有幂
		- prime1(不含首字节00)
			> P(CRT模式) N的素数因子
		- prime2(不含首字节00)
			> Q(CRT模式) N的素数因子
		- exponent1(不含首字节00)
			> DP(CRT模式) = (D % (P − 1))
		- exponent2(不含首字节00)
			> DQ(CRT模式) = (D % (Q − 1))
		- coefficient
			> InverseQ(CRT模式) = ((Q - 1) % P)
	