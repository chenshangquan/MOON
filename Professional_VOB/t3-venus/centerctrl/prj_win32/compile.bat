echo off
echo centerctrl.exe build begin


if not exist "..\..\..\10-common\version\release\win32\centerctrl" (
	mkdir "..\..\..\10-common\version\release\win32\centerctrl"
)

if /I "%1" == "noclean" (
	echo build noclean debug
	@msdev centerctrl.dsp /MAKE "centerctrl - Win32 Debug" /REBUILD /NORECURSE /OUT ..\..\..\10-common\version\compileinfo\centerctrl_d.txt

	echo build noclean release
	@msdev centerctrl.dsp /MAKE "centerctrl - Win32 Release" /REBUILD /NORECURSE /OUT ..\..\..\10-common\version\compileinfo\centerctrl_r.txt
) else (
	echo build clean debug
	@msdev centerctrl.dsp /MAKE "centerctrl - Win32 Debug" /REBUILD /NORECURSE /OUT ..\..\..\10-common\version\compileinfo\centerctrl_d.txt

	echo build clean release
	@msdev centerctrl.dsp /MAKE "centerctrl - Win32 Release" /REBUILD /NORECURSE /OUT ..\..\..\10-common\version\compileinfo\centerctrl_r.txt
)

copy /Y release\centerctrl.exe ..\..\..\10-common\version\release\win32\centerctrl\centerctrl.exe
copy /Y system.xml ..\..\..\10-common\version\release\win32\centerctrl\system.xml
copy /Y ..\..\windowsexsdk\lib\release\windowsexsdk.dll  ..\..\..\10-common\version\release\win32\centerctrl\windowsexsdk.dll

if not exist "..\..\..\10-common\version\release\win32\centerctrl\layout" (
	mkdir "..\..\..\10-common\version\release\win32\centerctrl\layout"
)
if not exist "..\..\..\10-common\version\release\win32\centerctrl\src" (
	mkdir "..\..\..\10-common\version\release\win32\centerctrl\src"
)
xcopy  layout\*.* ..\..\..\10-common\version\release\win32\centerctrl\layout /y /k
xcopy  src\*.* ..\..\..\10-common\version\release\win32\centerctrl\src /s /y /h  

copy /Y release\centerctrl.map ..\..\..\10-common\version\release\win32\centerctrl\centerctrl.map

echo centerctrl.exe build over
echo on