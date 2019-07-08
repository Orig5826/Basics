# openssl 用法详解
`2019.04.13 by jiafeng`

### Openssl 组成
1. openssl 多用途命令行工具
2. libctypro 加密算法库
3. libssl 加密模块应用库，实现ssl和tls


### 多用途命令行工具
- 对称加密 enc
	- 1. -e加密(默认)  -d解密
	- 2. -aes-128-ecb 指定算法
	- 3. -a/-base64 base64加解密
	- 4. -in输入  -out输出
	- 5. -pass pase:1234用户密码输入的  -pass file:keyfile用户密钥所在文件
	- 6. -S加盐(默认)  -nosalt不加盐（不建议）
	- 7. -nopad非填充方式，则明文需要为加密算法分组大小的整数倍
	- 8. -p打印文件密钥Key和IV值  -P同p，但仅显示Key和iv，不进行真正的加解密操作
	- 9. -engine指定第三方加密设备，可能是硬件设备