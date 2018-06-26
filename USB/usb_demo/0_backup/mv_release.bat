@echo off
cd ..
copy .\usb_drive\usb_drive.h  .\0_backup\usb_drive.h
copy .\Release\usb_drive.dll  .\0_backup\usb_drive.dll
copy .\Release\usb_drive.lib  .\0_backup\usb_drive.lib
copy .\Release\usb_demo.exe  .\0_backup\usb_demo.exe 
pause