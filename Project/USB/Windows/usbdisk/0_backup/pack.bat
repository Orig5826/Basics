@echo off
REM -----------------------------------
REM pyinstall (ͨ��pip install pyinstall��װ)
REM		-> Ĭ�ϴ���ɴ��д���DLL���ļ���
REM ˵����(���ɵ��ļ�/��)
REM 	build ��ʱ�ļ�
REM		dist ��Ŀ¼�´�����յĳ����ļ�/��
REM 	*.spec 
REM ����˵����
REM 	-F �����һ��exe��������dll��
REM		-i/--icon *.ico/*.exe ָ���������ʹ�õ�ICON�ļ�
REM		-w ���Ϊû��CMD��exe
REM -----------------------------------
pyinstaller --icon ./apaki.ico -F usbdisk_apdu.py
