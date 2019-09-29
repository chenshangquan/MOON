rem echo off
if not exist "..\..\10-common\version\release\win32\cms" (
    mkdir "..\..\10-common\version\release\win32\cms"
)


if exist "..\..\10-common\version\compileinfo\cms_setup.txt" (
    del ..\..\10-common\version\compileinfo\cms_setup.txt
)


if not exist "setup files" (
    mkdir "setup files"
)


rem 拷贝相应文件
if not exist "setup files\layout" (
    mkdir "setup files\layout"
)

if not exist "setup files\src" (
    mkdir "setup files\src"
)

if not exist "setup files\handInputTablet" (
    mkdir "setup files\handInputTablet"
)

if not exist "setup files\handInputTablet\src" (
    mkdir "setup files\handInputTablet\src"
)


copy /Y ..\..\10-common\version\release\win32\cms\cmc.exe "setup files\cmc.exe"
copy /Y ..\..\10-common\version\release\win32\cms\system.xml "setup files\system.xml"
copy /Y ..\..\10-common\version\release\win32\cms\loadcmc.exe "setup files\loadcmc.exe"

copy /Y "..\..\10-common\version\release\win32\cms\layout\*.*" "setup files\layout\"
xcopy "..\..\10-common\version\release\win32\cms\src\*.*" "setup files\src\" /s /y /h

copy /Y ..\..\10-common\version\release\win32\cms\cmc.map "setup files\cmc.map"

copy /Y ..\..\10-common\version\release\win32\handInputTablet\handInputTablet.exe "setup files\handInputTablet\handInputTablet.exe"
copy /Y ..\..\10-common\version\release\win32\handInputTablet\WINPY.TXT "setup files\handInputTablet\WINPY.TXT"
xcopy "..\..\10-common\version\release\win32\handInputTablet\src\*.*" "setup files\handInputTablet\src\" /s /y /h

cd setup
call compile.bat %1
rem call compile_desk.bat %1
cd..

del /S /Q "setup files\*.*"

:end
