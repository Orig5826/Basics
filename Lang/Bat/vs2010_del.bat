@echo off
REM 1.0 ��ȡ��ǰ�������ڵ�Ŀ¼������
for %%i in ("%cd%") do set name=%%~ni
echo %name%


REM 2.0 ɾ��sdf�ļ�
del *.sdf

REM 2.1 ɾ��DebugĿ¼�µ������ļ�S���������ļ���Debug
cd .\Debug
	del /Q /S *.ilk *.pdb *.exe
	cd ..
REM ɾ��ipch����Ŀ¼�µ������ļ�
RD /Q /S .\ipch

REM ɾ�������µ�Debug����Ŀ¼�µı�������������ļ�
cd  .\%name%
	RD /Q /S  .\Debug
	del /Q /S *.user
	cd ..

REM ɾ�����
REM pause
