
@echo off
if "%1"=="clean" (
    echo "0. 删除生成的文件"
    del /Q /S calc_module.*
    del /Q /S calc_wrap.*
    del /Q /S *.obj

    RD /Q /S build
    RD /Q /S __pycache__
	REM vs2017
	del *.exp *.lib
    del *.dll *.pyd
 ) else (

echo "1. swig 工具命令的使用"
swig -python -py3 calc.i


REM 之前失败，可能因为我安装python的时候，没有安装相关的调试库吧？
REM 1.0 distutils通过setup方式调试成功
REM 2.0 直接调用VS2017命令行工具，CL命令调试成功

if "%1"=="setup" (

echo "2. setup Python->distutils命令的使用"
setup.py build
REM 生成的文件在build子目录下，自己找一下
) else (

echo "2. VS cl命令编译"
echo cl命令必须使用VS提供的专用命令行工具

set src="calc_wrap.c"
REM 之所以名称使用_(下划线)，是为了和swig生成的calc_module.py配合使用
set des="_calc_module.pyd"
set PyInc="D:\\Lang\\Python\\Python38\\include"
set PyLib="D:\\Lang\\Python\\Python38\\libs\\python38.lib"

REM vs2017
cl /LD calc.c %src% /Fe%des% /I %PyInc% %PyLib% 

)
)