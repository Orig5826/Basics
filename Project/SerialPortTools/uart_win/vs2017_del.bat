@echo off

REM ɾ�����������Ŀ¼��ĳЩ�ļ�/��
REM vs2017 *.db���ļ�������.vsĿ¼
RD /Q /S  .\.vs
RD /Q /S  .\Debug  .\Release .\x64  .\x86  .\ARM

REM ��ʽ1 ��ȡ��ǰ�������ڵ�Ŀ¼������
REM for %%i in ("%cd%") do set name=%%~ni
REM echo %name%

REM ��ʽ2 ֱ���ҳ������ļ����µ��м��ļ�
REM ���ɾ��
for /f %%i in ('dir /B /ON /AD') do (
echo %%i

cd  .\%%i
	RD /Q /S  .\Debug .\Release .\x64  .\x86  .\ARM
	del /Q /S *.user
	cd ..
)
