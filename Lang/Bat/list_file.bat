@echo off

dir /B /S /ON ( .s *.c *.lib ) > file.txt

REM Ȼ����ʹ��֧��re�ı༭��������notepad++��vscode��
REM �滻:    .+\\(.+)$    �滻Ϊ    \1    \(.text\)
REM ��ʾ����Ҫ�����CodeWarrior������link�ļ����ݵı�ݲ���
