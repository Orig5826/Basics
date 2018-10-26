@echo off
REM 1.0 获取当前工程所在的目录的名称
for %%i in ("%cd%") do set name=%%~ni
echo %name%

REM 删除Project下的某些文件
cd .\Project

for /R %%i in (Demo_Example Custom_HID Virtual_COM_Port Custom_CCID) do (
	echo cd %%i%
	cd %%i%
	
	RD /S /Q .\Objects
	RD /S /Q .\Listings
	RD /S /Q .\DebugConfig
	del /S /Q *.uvguix.*
	del /S /Q *.uvoptx
	del /S /Q *.scvd
	
	del /S /Q JLink*
)
cd ..

REM pause