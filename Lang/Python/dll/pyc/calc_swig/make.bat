
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

REM ???
REM 各种测试，总是提示找不到PyInit_*接口... 不知道什么原因

if "%1"=="setup" (
echo "2. setup Python->distutils命令的使用"
setup.py build
move .\\build\\lib.win-amd64-3.7\\_calc_module.cp37-win_amd64.pyd  .\\calc_module.pyd
) else (

echo "2. VS cl命令编译"
echo cl命令必须使用VS提供的专用命令行工具

set src=calc_wrap.c
set des=calc_module.pyd
set PyInc=D:\\Lang\\Python\\Python37\\include
set PyLib=D:\\Lang\\Python\\Python37\\libs\\python37.lib

cl /LD calc.c %src% /o %des% -I%PyInc% %PyLib% 

)
)