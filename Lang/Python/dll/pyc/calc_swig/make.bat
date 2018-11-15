
@echo off
if "%1"=="clean" (
    echo "0. 删除生成的文件"
    del /Q /S calc_module.*
    del /Q /S calc_wrap.*
    del /Q /S *.obj

    RD /Q /S build
    RD /Q /S __pycache__
    del calc_module.pyd
    del *.dll
 ) else (

echo "1. swig 工具命令的使用"
swig -python -py3 calc.i

if "%1"=="setup" (

REM setup的方式测试通过，可能因为我之前安装python的时候，没有安装相关的调试库吧？
echo "2. setup Python->distutils命令的使用"
setup.py build
REM 生成的文件在build子目录下，自己找一下
) else (


REM 这种方式还是不行，可能我对于cl命令的了解不够吧
echo "2. VS cl命令编译"
echo cl命令必须使用VS提供的专用命令行工具

set src=calc_wrap.c
set des=calc_module.pyd
set PyInc=D:\\Lang\\Python\\Python37\\include
set PyLib=D:\\Lang\\Python\\Python37\\libs\\python37.lib

cl /LD calc.c %src% /o %des% -I%PyInc% %PyLib% 

)
)