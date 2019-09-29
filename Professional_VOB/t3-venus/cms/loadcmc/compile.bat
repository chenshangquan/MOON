@echo off
echo loadcmc.exe build begin


if not exist "debug" (
	mkdir debug
)
if not exist "release" (
	mkdir release
)


if "%1" == "noclean" (
    echo build noclean debug
@msdev loadcmc.dsp /MAKE "loadcmc - Win32 Debug" /REBUILD /NORECURSE /OUT ..\..\..\10-common\version\compileinfo\loadcmc_d.txt

    echo build noclean release	
@msdev loadcmc.dsp /MAKE "loadcmc - Win32 Release" /REBUILD /NORECURSE /OUT ..\..\..\10-common\version\compileinfo\loadcmc_r.txt
) else (
    echo build clean debug
@msdev loadcmc.dsp /MAKE "loadcmc - Win32 Debug" /REBUILD /NORECURSE /OUT ..\..\..\10-common\version\compileinfo\loadcmc_d.txt

    echo build clean release
@msdev loadcmc.dsp /MAKE "loadcmc - Win32 Release" /REBUILD /NORECURSE /OUT ..\..\..\10-common\version\compileinfo\loadcmc_r.txt

)

copy /Y debug\loadcmc.exe ..\..\..\10-common\version\debug\win32\cms\loadcmc.exe
copy /Y release\loadcmc.exe ..\..\..\10-common\version\release\win32\cms\loadcmc.exe

echo build loadcmc.exe over
echo on
