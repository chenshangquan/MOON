echo off
echo UsbVerify.lib build begin

if exist "./usbverify.dep" (
	del "./usbverify.dep"
)

if /I "%1" == "noclean" (
	echo build noclean debug
	nmake /NOLOGO /A /B /f UsbVerify.mak CFG="UsbVerify - Win32 Debug" /x nmakeError.log > ..\..\..\..\10-common\version\compileinfo\UsbVerify_D.txt

	echo build noclean release
	nmake /NOLOGO /B /f UsbVerify.mak CFG="UsbVerify - Win32 Release" /x nmakeError.log > ..\..\..\..\10-common\version\CompileInfo\UsbVerify_R.txt
) else (
	echo build clean debug
	nmake /NOLOGO /A /B /f UsbVerify.mak CLEAN ALL CFG="UsbVerify - Win32 Debug" /x nmakeError.log > ..\..\..\..\10-common\version\compileinfo\UsbVerify_D.txt

	echo build clean release
	nmake /NOLOGO /A /B /f UsbVerify.mak CLEAN ALL CFG="UsbVerify - Win32 Release" /x nmakeError.log > ..\..\..\..\10-common\version\compileinfo\UsbVerify_R.txt
)

echo UsbVerify.lib build over
echo on


