@echo off
cd ..

set PathName="lua"
set Header="%PathName%.h"
set Dll="%PathName%54.dll"
set Lib="%PathName%54.lib"
set Demo="%PathName%_demo.exe"
set Exe="%PathName%.exe"

copy .\%PathName%\%Header%    .\0_backup\%Header%
copy .\Release\%Dll%          .\0_backup\%Dll%
copy .\Release\%Lib%          .\0_backup\%Lib%
copy .\Release\%Demo%         .\0_backup\%Demo%
copy .\Release\%Exe%         .\0_backup\%Exe%

pause