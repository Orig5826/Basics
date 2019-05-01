# linux下源码安装常见问题
`2019.05.01 by jianfeng`

### 常见报错信息(Ubuntu18)
- ZipImportError: can’t decompress data; zlib not available
    > make前安装zlib即可。(zlib-1.2.11)

- ModuleNotFoundError: No module named ‘_ctypes’
    > 先执行如下命令，随后再重新编译安装即可
```
sudo apt-get update
sudo apt-get upgrade
sudo apt-get dist-upgrade
sudo apt-get install build-essential python-dev python-setuptools python-pip python-smbus
sudo apt-get install build-essential libncursesw5-dev libgdbm-dev libc6-dev
sudo apt-get install zlib1g-dev libsqlite3-dev tk-dev
sudo apt-get install libssl-dev openssl
sudo apt-get install libffi-dev
```