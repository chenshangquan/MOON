echo off
echo cnc.exe build begin

rem copy /Y ..\..\..\10-Common\version\release\win32\incversion\IncVersion.exe
rem IncVersion.exe

if not exist "debug" (
	mkdir debug
)
if not exist "release" (
	mkdir release
)

if exist "..\..\..\10-common\version\debug\win32\cnc" (
rmdir /s/q "..\..\..\10-common\version\debug\win32\cnc"
)
if not exist "..\..\..\10-common\version\debug\win32\cnc" (
	mkdir "..\..\..\10-common\version\debug\win32\cnc"
)

if exist "..\..\..\10-common\version\release\win32\cnc" (
rmdir /s/q "..\..\..\10-common\version\release\win32\cnc"
)
if not exist "..\..\..\10-common\version\release\win32\cnc" (
	mkdir "..\..\..\10-common\version\release\win32\cnc"
)

if "%1" == "noclean" (
    echo build noclean debug
@msdev cms.dsp /MAKE "cms - Win32 Debug" /REBUILD /NORECURSE /OUT ..\..\..\10-common\version\compileinfo\cnc_d.txt

    echo build noclean release	

@msdev cms.dsp /MAKE "cms - Win32 Release" /REBUILD /NORECURSE /OUT ..\..\..\10-common\version\compileinfo\cnc_r.txt
) else (

    echo build clean debug
@msdev cms.dsp /MAKE "cms - Win32 Debug" /REBUILD /NORECURSE /OUT ..\..\..\10-common\version\compileinfo\cnc_d.txt

    echo build clean release

@msdev cms.dsp /MAKE "cms - Win32 Release" /REBUILD /NORECURSE /OUT ..\..\..\10-common\version\compileinfo\cnc_r.txt

)

copy /Y debug\cnc.exe ..\..\..\10-common\version\debug\win32\cnc\cnc.exe


copy /Y release\cnc.exe ..\..\..\10-common\version\release\win32\cnc\cnc.exe
copy /Y system.xml ..\..\..\10-common\version\release\win32\cnc\system.xml
copy /Y system_pad.xml ..\..\..\10-common\version\release\win32\cnc\system_pad.xml
copy /Y ..\..\windowsexsdk\lib\release\windowsexsdk.dll  ..\..\..\10-common\version\release\win32\cnc\windowsexsdk.dll

if not exist "..\..\..\10-common\version\release\win32\cnc\layout" (
	mkdir "..\..\..\10-common\version\release\win32\cnc\layout"
)
if not exist "..\..\..\10-common\version\release\win32\cnc\src" (
	mkdir "..\..\..\10-common\version\release\win32\cnc\src"
)
xcopy  layout\*.* ..\..\..\10-common\version\release\win32\cnc\layout /y /k
xcopy  src\*.* ..\..\..\10-common\version\release\win32\cnc\src /s /y /h  

copy /Y release\cnc.map ..\..\..\10-common\version\release\win32\cnc\cnc.map

echo build cnc.exe over
echo on
