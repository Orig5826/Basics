@echo off
cd ..

set PathName="usbdisk"
set Header="%PathName%.h"
set Dll="%PathName%.dll"
set Lib="%PathName%.lib"
set Demo="%PathName%_demo.exe"

copy .\%PathName%\%Header%    .\0_backup\%Header%
copy .\Release\%Dll%          .\0_backup\%Dll%
copy .\Release\%Lib%          .\0_backup\%Lib%
copy .\Release\%Demo%         .\0_backup\%Demo%

pause