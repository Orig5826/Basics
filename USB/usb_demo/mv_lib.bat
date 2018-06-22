@echo off

set des=".\usb_demo"
set usb_lib=".\Debug\usb_drive.lib"
set usb_header=".\usb_drive\usb_drive.h"

REM 编译会用
copy    %usb_lib%       %des%
copy    %usb_header%    %des%
