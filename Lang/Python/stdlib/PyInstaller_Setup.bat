@echo off
REM pyinstaller �����в���
REM -w �������ε�����������ʱ���е������е��Դ���
REM -F ���ɵĳ�����Ϊһ��exe������������dll�������ļ����ļ���
REM -p �������·��������site-package��Ĭ�ϾͿ���ʶ�𵽡����õ���

if "%1" == "clean" (
    RD /Q /S    dist  build  __pycache__
    del 013_tkinter_2.spec
) else (
    python -m PyInstaller -w -F 013_tkinter_2.py -i ./res/apaki.ico
)