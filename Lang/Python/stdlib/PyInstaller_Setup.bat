@echo off
REM pyinstaller 命令行参数
REM -w 可以屏蔽掉，发布程序时带有的命令行调试窗口
REM -F 生成的程序打包为一个exe。否则带有诸多dll和依赖文件的文件夹
REM -p 后接搜索路径，不过site-package中默认就可以识别到。不用担心

if "%1" == "clean" (
    RD /Q /S    dist  build  __pycache__
    del 013_tkinter_2.spec
) else (
    python -m PyInstaller -w -F 013_tkinter_2.py -i ./res/apaki.ico
)