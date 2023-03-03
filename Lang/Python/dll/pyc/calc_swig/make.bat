
@echo off
if "%1"=="clean" (
    echo "0. ɾ�����ɵ��ļ�"
    del /Q /S calc_module.*
    del /Q /S calc_wrap.*
    del /Q /S *.obj

    RD /Q /S build
    RD /Q /S __pycache__
	REM vs2017
	del *.exp *.lib
    del *.dll *.pyd
 ) else (

echo "1. swig ���������ʹ��"
swig -python -py3 calc.i


REM ֮ǰʧ�ܣ�������Ϊ�Ұ�װpython��ʱ��û�а�װ��صĵ��Կ�ɣ�
REM 1.0 distutilsͨ��setup��ʽ���Գɹ�
REM 2.0 ֱ�ӵ���VS2017�����й��ߣ�CL������Գɹ�

if "%1"=="setup" (

echo "2. setup Python->distutils�����ʹ��"
setup.py build
REM ���ɵ��ļ���build��Ŀ¼�£��Լ���һ��
) else (

echo "2. VS cl�������"
echo cl�������ʹ��VS�ṩ��ר�������й���

set src="calc_wrap.c"
REM ֮��������ʹ��_(�»���)����Ϊ�˺�swig���ɵ�calc_module.py���ʹ��
set des="_calc_module.pyd"
set PyInc="D:\\Lang\\Python\\Python38\\include"
set PyLib="D:\\Lang\\Python\\Python38\\libs\\python38.lib"

REM vs2017
cl /LD calc.c %src% /Fe%des% /I %PyInc% %PyLib% 

)
)