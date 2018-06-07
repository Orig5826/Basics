@echo off
REM 实现递归的删除.svn目录
REM ！递归的根目录是指当前的目录！

REM echo的目的是为了让你看清楚自己删除的是谁
REM 若确认没有问题，将echo去掉，便是实际操作了
for /R %%i in (.svn) do (
	echo RD /S /Q %%i%
	RD /S /Q %%i%
)
REM 若没有提示，则表示删除成功
REM 若提示"系统找不到指定文件"，说明文件不存在已经被删除了

REM pause