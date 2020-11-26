@echo off
REM -----------------------------------
REM pyinstall (通过pip install pyinstall安装)
REM		-> 默认打包成带有大量DLL的文件夹
REM 说明：(生成的文件/夹)
REM 	build 临时文件
REM		dist 该目录下存放最终的程序文件/夹
REM 	*.spec 
REM 参数说明：
REM 	-F 打包成一个exe，不带有dll的
REM		-i/--icon *.ico/*.exe 指定打包程序使用的ICON文件
REM		-w 打包为没有CMD的exe
REM -----------------------------------
pyinstaller --icon ./apaki.ico -F usbdisk_apdu.py
