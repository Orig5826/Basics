@echo off
REM 1.0 ��ȡ��ǰ�������ڵ�Ŀ¼������
for %%i in ("%cd%") do set name=%%~ni
echo %name%

REM vs2017 *.db���ļ�������.vsĿ¼�£��ϴ����ñ���
RD /Q /S .\.vs

REM x64 ����ļ�ɾ��
RD /Q /S .\x64
cd  .\%name%
RD /Q /S  .\x64
	cd ..

REM ɾ��DebugĿ¼�µ������ļ�S���������ļ���Debug
cd .\Debug
	del /Q /S *
	cd ..

REM ɾ�������µ�Debug����Ŀ¼�µı�������������ļ�
cd  .\%name%
	RD /Q /S  .\Debug
	del /Q /S *.user
	cd ..

REM ����б�Ҫ��������·���µ�dll���Ƶ�Debug��һ�ݣ�����ֱ�ӵ���
REM copy .\%name%\*.dll  .\Debug
	
REM ɾ�����
REM pause
