@echo off
REM 1.0 获取当前工程所在的目录的名称
for %%i in ("%cd%") do set name=%%~ni
echo %name%

REM 删除Project下的某些文件
cd .\Project

del /Q /S .\Objects\*
del /Q /S .\Listings\*
del /Q /S .\DebugConfig\*

del /Q /S *.uvguix.*
del /Q /S *.uvoptx
del /Q /S *.scvd

cd ..


REM pause