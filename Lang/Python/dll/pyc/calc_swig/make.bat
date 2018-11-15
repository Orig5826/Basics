
@echo off
if "%1"=="clean" (
    echo "0. ɾ�����ɵ��ļ�"
    del /Q /S calc_module.*
    del /Q /S calc_wrap.*
    del /Q /S *.obj

    RD /Q /S build
    RD /Q /S __pycache__
    del calc_module.pyd
    del *.dll
 ) else (

echo "1. swig ���������ʹ��"
swig -python -py3 calc.i

if "%1"=="setup" (

REM setup�ķ�ʽ����ͨ����������Ϊ��֮ǰ��װpython��ʱ��û�а�װ��صĵ��Կ�ɣ�
echo "2. setup Python->distutils�����ʹ��"
setup.py build
REM ���ɵ��ļ���build��Ŀ¼�£��Լ���һ��
) else (


REM ���ַ�ʽ���ǲ��У������Ҷ���cl������˽ⲻ����
echo "2. VS cl�������"
echo cl�������ʹ��VS�ṩ��ר�������й���

set src=calc_wrap.c
set des=calc_module.pyd
set PyInc=D:\\Lang\\Python\\Python37\\include
set PyLib=D:\\Lang\\Python\\Python37\\libs\\python37.lib

cl /LD calc.c %src% /o %des% -I%PyInc% %PyLib% 

)
)