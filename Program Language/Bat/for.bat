@echo off
@echo for
REM 变量设置的等号中间不能有空格
set times=10
echo %times%
for /l %%i in (1,1,%times%) do (
	echo %%i%
)
pause