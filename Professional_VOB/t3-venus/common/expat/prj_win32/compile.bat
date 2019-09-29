echo off
echo expat.lib build begin

if /I "%1" == "noclean" (
	echo build noclean debug
	@msdev expat.dsp /MAKE "mcslib - Win32 Debug" /REBUILD /NORECURSE /OUT ..\..\..\..\10-common\version\CompileInfo\expat_d.txt

	echo build noclean release
	@msdev expat.dsp /MAKE "mcslib - Win32 Release" /REBUILD /NORECURSE /OUT ..\..\..\..\10-common\version\CompileInfo\expat_r.txt
) else (
	echo build clean debug
	@msdev expat.dsp /MAKE "mcslib - Win32 Debug" /REBUILD /NORECURSE /OUT ..\..\..\..\10-common\version\CompileInfo\expat_d.txt

	echo build clean release
	@msdev expat.dsp /MAKE "mcslib - Win32 Release" /REBUILD /NORECURSE /OUT ..\..\..\..\10-common\version\CompileInfo\expat_r.txt
)

echo expat.lib build over
echo on