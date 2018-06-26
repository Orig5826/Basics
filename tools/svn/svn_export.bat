@echo off
REM 用来下载git库中的某子文件夹内容的方法 -> svn export *.git/trunk/subdir
REM 注意添加trunk

set subdir=hid
set gitclone=https://github.com/Microsoft/Windows-driver-samples.git
svn export %gitclone%/trunk/%subdir%

set subdir=storage
set gitclone=https://github.com/Microsoft/Windows-driver-samples.git
svn export %gitclone%/trunk/%subdir%

set subdir=smartcrd
set gitclone=https://github.com/Microsoft/Windows-driver-samples.git
svn export %gitclone%/trunk/%subdir%
