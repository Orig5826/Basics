@echo off

REM 1.0 ��ȡ��ǰ�������ڵ�Ŀ¼������
for %%i in ("%cd%") do set name=%%~ni
echo %name%

REM ɾ�����������Ŀ¼��ĳЩ�ļ�/��
REM vs2017 *.db���ļ�������.vsĿ¼
RD /Q /S  .\.vs
RD /Q /S  .\Debug  .\Release  .\x64  .\x86  .\ARM
REM ɾ����Ӧ�����µ�Debug����Ŀ¼�µı�������������ļ�
cd  .\%name%
	RD /Q /S  .\Debug  .\Release  .\x64  .\x86  .\ARM
	del /Q /S *.user
	cd ..

REM ��������Ŀ¼Ҳ��Ҫɾ��
set name="usb_drive"
cd  .\%name%
	RD /Q /S  .\Debug  .\Release  .\x64  .\x86  .\ARM
	del /Q /S *.user
	cd ..

REM ɾ�����
REM pause
