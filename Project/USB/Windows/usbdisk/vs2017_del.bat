@echo off

REM 删除解决方案主目录下某些文件/夹
REM vs2017 *.db等文件均放在.vs目录
RD /Q /S  .\.vs
RD /Q /S  .\Debug  .\Release .\x64  .\x86  .\ARM

REM 方式1 获取当前工程所在的目录的名称
REM for %%i in ("%cd%") do set name=%%~ni
REM echo %name%

REM 方式2 直接找出所有文件夹下的中间文件
REM 随后删除
for /f %%i in ('dir /B /ON /AD') do (
echo %%i

cd  .\%%i
	RD /Q /S  .\Debug .\Release .\x64  .\x86  .\ARM
	del /Q /S *.user
	cd ..
)
