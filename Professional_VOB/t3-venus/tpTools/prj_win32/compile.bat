echo off
echo tpTools.exe build begin

if not exist "release" (
	mkdir release
)

rmdir /s/q "..\..\..\10-common\version\release\win32\tpTools"
if not exist "..\..\..\10-common\version\release\win32\tpTools" (
	mkdir "..\..\..\10-common\version\release\win32\tpTools"
)

if "%1" == "noclean" (
    echo build noclean release	

@msdev tpTools.dsp /MAKE "tpTools - Win32 Release" /REBUILD /NORECURSE /OUT ..\..\..\10-common\version\compileinfo\tpTools_r.txt
) else (

    echo build clean release

@msdev tpTools.dsp /MAKE "tpTools - Win32 Release" /REBUILD /NORECURSE /OUT ..\..\..\10-common\version\compileinfo\tpTools_r.txt

)



copy /Y release\tpTools.exe ..\..\..\10-common\version\release\win32\tpTools\tpTools.exe


copy /Y bin\umstooldll.dll ..\..\..\10-common\version\release\win32\tpTools\umstooldll.dll


copy /Y bin\cnsToolDll.dll ..\..\..\10-common\version\release\win32\tpTools\cnsToolDll.dll


copy /Y release\moonToolDll.dll ..\..\..\10-common\version\release\win32\tpTools\moonToolDll.dll


if not exist "..\..\..\10-common\version\release\win32\tpTools\rescnstool" (
	mkdir "..\..\..\10-common\version\release\win32\tpTools\rescnstool"
)
if not exist "..\..\..\10-common\version\release\win32\tpTools\resumstool" (
	mkdir "..\..\..\10-common\version\release\win32\tpTools\resumstool"
)
if not exist "..\..\..\10-common\version\release\win32\tpTools\resmoontool" (
	mkdir "..\..\..\10-common\version\release\win32\tpTools\resmoontool"
)
if not exist "..\..\..\10-common\version\release\win32\tpTools\res" (
	mkdir "..\..\..\10-common\version\release\win32\tpTools\res"
)
xcopy  rescnstool\*.* ..\..\..\10-common\version\release\win32\tpTools\rescnstool /s /y /h
xcopy  resumstool\*.* ..\..\..\10-common\version\release\win32\tpTools\resumstool /s /y /h  
xcopy  resmoontool\*.* ..\..\..\10-common\version\release\win32\tpTools\resmoontool /s /y /h
xcopy  res\*.* ..\..\..\10-common\version\release\win32\tpTools\res /s /y /h  


copy /Y release\tpTools.map ..\..\..\10-common\version\release\win32\tpTools\tpTools.map

echo build tpTools.exe over
echo on
