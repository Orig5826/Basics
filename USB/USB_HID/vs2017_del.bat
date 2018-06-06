@echo off
REM 1.0 获取当前工程所在的目录的名称
for %%i in ("%cd%") do set name=%%~ni
echo %name%

REM vs2017 *.db等文件均放在.vs目录下，上传不用保留
RD /Q /S .\.vs

REM x64 相关文件删除
RD /Q /S .\x64
cd  .\%name%
RD /Q /S  .\x64
	cd ..

REM 删除Debug目录下的所有文件S，但保留文件夹Debug
cd .\Debug
	del /Q /S *
	cd ..

REM 删除工程下的Debug及其目录下的编译产生的所有文件
cd  .\%name%
	RD /Q /S  .\Debug
	del /Q /S *.user
	cd ..

REM 如果有必要，将工程路径下的dll复制到Debug中一份，方便直接调用
REM copy .\%name%\*.dll  .\Debug
	
REM 删除完毕
REM pause
