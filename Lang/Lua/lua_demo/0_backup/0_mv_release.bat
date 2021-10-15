@echo off
cd ..

copy .\src\lua.h        .\0_backup\lua.h
copy .\src\lauxlib.h    .\0_backup\lauxlib.h
copy .\src\lualib.h     .\0_backup\lualib.h

set PathName="lua"
set Dll="%PathName%54.dll"
set Lib="%PathName%54.lib"
set Demo="%PathName%_demo.exe"
copy .\%PathName%_demo\test.lua    .\0_backup\test.lua

set Exe="%PathName%.exe"

copy .\Release\%Dll%          .\0_backup\%Dll%
copy .\Release\%Lib%          .\0_backup\%Lib%
copy .\Release\%Demo%         .\0_backup\%Demo%
copy .\Release\%Exe%         .\0_backup\%Exe%

set lusbdisk="lusbdisk.dll"
copy .\Release\%lusbdisk%         .\0_backup\%lusbdisk%

pause
