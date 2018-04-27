@echo off
REM 1.0 获取当前工程所在的目录的名称
for %%i in ("%cd%") do set name=%%~ni
echo %name%


REM 2.0 删除sdf文件
del *.sdf

REM 2.1 删除Debug目录下的所有文件S，但保留文件夹Debug
cd .\Debug
	del /Q /S *.ilk *.pdb *.exe
	cd ..
REM 删除ipch及其目录下的所有文件
RD /Q /S .\ipch

REM 删除工程下的Debug及其目录下的编译产生的所有文件
cd  .\%name%
	RD /Q /S  .\Debug
	del /Q /S *.user
	cd ..

REM 删除完毕
REM pause
