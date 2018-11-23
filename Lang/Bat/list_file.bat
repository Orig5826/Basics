@echo off

dir /B /S /ON ( .s *.c *.lib ) > file.txt

REM 然后再使用支持re的编辑器，诸如notepad++，vscode等
REM 替换:    .+\\(.+)$    替换为    \1    \(.text\)
REM 本示例主要是针对CodeWarrior编译器link文件内容的便捷操作
