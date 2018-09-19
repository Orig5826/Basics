# Openssl 
`2018.9.19 by jianfeng`

## 安装平台 Ubuntu 14.0 32bit 
	> OpenSSL 1.1.1  11 Sep 2018
- ./config shared
	> 安装的默认路径是？
- make
- make test
- make install

- ln -s /usr/local/ssl/include/openssl /usr/include/openssl
- ln -s /usr/local/ssl/bin/openssl /usr/bin/openssl
	> 这个似乎有问题，找不到ssl/bin，我使用whereis openssl查找之后，发现再bin下有openssl，因此修改为如下
	- ln -s /usr/local/bin/openssl /usr/bin/openssl
- echo "/usr/local/ssl/lib" >> /etc/ld.so.conf
- ldconfig -v

## 安装完毕测试一下
### 问题
- 执行openssl version 报错
	- openssl: error while loading shared libraries: libssl.so.1.1: cannot open shared object file: No such file or directory
		> 解决方法如下
		- ln -s /usr/local/lib/libssl.so.1.1 /usr/lib/libssl.so.1.1
		- ln -s /usr/local/lib/libcrypto.so.1.1 /usr/lib/libcrypto.so.1.1
