@echo off
echo gzip.lib build begin

if exist "gzip.dep" (
	del sucui.dep
)

if not exist "debug" (
	mkdir debug
)
if not exist "release" (
	mkdir release
)


if /i "%1" == "noclean" (
	echo build noclean debug
	nmake /NOLOGO /B /f gzip.mak CFG="gzip - Win32 Debug" /x nmakeError_D.log > ..\..\..\..\10-common\version\compileinfo\gzip_D.txt

	echo build noclean release
	nmake /NOLOGO /B /f gzip.mak CFG="gzip - Win32 Release" /x nmakeError_R.log > ..\..\..\..\10-common\version\compileinfo\gzip_R.txt
) else (
	echo build noclean debug
	nmake /NOLOGO /A /B /f gzip.mak CLEAN ALL CFG="gzip - Win32 Debug" /x nmakeError_D.log > ..\..\..\..\10-common\version\compileinfo\gzip_D.txt

	echo build noclean release
	nmake /NOLOGO /A /B /f gzip.mak CLEAN ALL CFG="gzip - Win32 Release" /x nmakeError_R.log > ..\..\..\..\10-common\version\compileinfo\gzip_R.txt
)


echo build gzip.lib over

