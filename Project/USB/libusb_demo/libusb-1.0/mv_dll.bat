@echo off
cd ..
REM 到工程主目录
set usb_dll=".\libusb-1.0\libusb-1.0.dll"

set des="Debug"
if exist %des% (
copy    %usb_dll%       %des%
) else (
	echo %des% is not exist
)

set des="Release"
if exist %des% (
copy    %usb_dll%       %des%
) else (
	echo %des% is not exist
)
