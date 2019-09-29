echo off
echo tpadlib.lib build begin

if /I "%1" == "noclean" (
	echo build noclean debug
	@msdev tpadlib.dsp /MAKE "tpadlib - Win32 Debug" /REBUILD /NORECURSE /OUT ..\..\..\10-common\version\compileinfo\tpadlib_d.txt

	echo build noclean release
	@msdev tpadlib.dsp /MAKE "tpadlib - Win32 Release" /REBUILD /NORECURSE /OUT ..\..\..\10-common\version\compileinfo\tpadlib_r.txt
) else (
	echo build clean debug
	@msdev tpadlib.dsp /MAKE "tpadlib - Win32 Debug" /REBUILD /NORECURSE /OUT ..\..\..\10-common\version\compileinfo\tpadlib_d.txt

	echo build clean release
	@msdev tpadlib.dsp /MAKE "tpadlib - Win32 Release" /REBUILD /NORECURSE /OUT ..\..\..\10-common\version\compileinfo\tpadlib_r.txt
)

echo tpadlib.lib build over
echo on