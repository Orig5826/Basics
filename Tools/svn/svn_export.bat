@echo off
REM ��������git���е�ĳ���ļ������ݵķ��� -> svn export *.git/trunk/subdir
REM ע�����trunk

set subdir=hid
set gitclone=https://github.com/Microsoft/Windows-driver-samples.git
svn export %gitclone%/trunk/%subdir%

set subdir=storage
set gitclone=https://github.com/Microsoft/Windows-driver-samples.git
svn export %gitclone%/trunk/%subdir%

set subdir=smartcrd
set gitclone=https://github.com/Microsoft/Windows-driver-samples.git
svn export %gitclone%/trunk/%subdir%
