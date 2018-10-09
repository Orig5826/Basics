@echo off

REM 1.0 获取当前工程所在的目录的名称
for %%i in ("%cd%") do set name=%%~ni
echo %name%

REM 删除解决方案主目录下某些文件/夹
REM vs2017 *.db等文件均放在.vs目录
RD /Q /S  .\.vs
RD /Q /S  .\Debug  .\x64  .\x86  .\ARM
REM 删除相应工程下的Debug及其目录下的编译产生的所有文件
cd  .\%name%
	RD /Q /S  .\Debug  .\x64  .\x86  .\ARM
	del /Q /S *.user
	cd ..

REM 其他工程目录也需要删除
set name=%name%"_demo"
cd  .\%name%
	RD /Q /S  .\Debug  .\x64  .\x86  .\ARM
	del /Q /S *.user
	cd ..

REM 删除完毕
REM pause
