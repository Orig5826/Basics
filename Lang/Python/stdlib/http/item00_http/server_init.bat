@echo off
python -m http.server 8000
REM python -m http.server 192.160.1.104 8000
REM win10下测试，本地访问没有问题。但是通过局域网下的手机访问总是失败
REM 后来通过关闭公用网络防火墙，测试通过(但是禁用防火墙毕竟不安全)
REM 在防火墙高级设置中，配置进站规则，将python软件，本地8000端口放开即可。
