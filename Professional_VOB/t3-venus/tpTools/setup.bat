
if not exist "setup files" (
    mkdir "setup files"
)

rem 拷贝相应文件
if not exist "setup files\res" (
    mkdir "setup files\res"
)

if not exist "setup files\rescnstool" (
    mkdir "setup files\rescnstool"
)

if not exist "setup files\resumstool" (
    mkdir "setup files\resumstool"
)

if not exist "setup files\resmoontool" (
    mkdir "setup files\resmoontool"
)

if not exist "..\..\10-common\version\release\win32\tpTools\tpTools.exe" (
    goto end
)

if not exist "..\..\t3-venus\tpTools\prj_win32\bin\cnsToolDll.dll" (
    goto end
)

if not exist "..\..\t3-venus\tpTools\prj_win32\bin\umstooldll.dll" (
    goto end
)

if not exist "..\..\10-common\version\release\win32\tpTools\moontooldll.dll" (
    goto end
)

copy /Y ..\..\10-common\version\release\win32\tpTools\tpTools.exe "setup files\tpTools.exe"

copy /Y ..\..\t3-venus\tpTools\prj_win32\bin\cnsToolDll.dll "setup files\cnsToolDll.dll"

copy /Y ..\..\10-common\version\release\win32\tpTools\tpTools.map "setup files\tpTools.map"

copy /Y ..\..\t3-venus\tpTools\prj_win32\bin\umstooldll.dll "setup files\umstooldll.dll"

copy /Y ..\..\10-common\version\release\win32\tpTools\moontooldll.dll "setup files\moontooldll.dll"

xcopy "..\..\t3-venus\tpTools\prj_win32\rescnstool\*.*" "setup files\rescnstool\" /s /y /h
xcopy "..\..\t3-venus\tpTools\prj_win32\resumstool\*.*" "setup files\resumstool\" /s /y /h  
xcopy "..\..\10-common\version\release\win32\tpTools\resmoontool\*.*" "setup files\resmoontool\" /s /y /h  
xcopy "..\..\10-common\version\release\win32\tpTools\res\*.*" "setup files\res\" /s /y /h

cd setup
call compile.bat %1
rem call compile_desk.bat %1
cd..

del /S /Q "setup files\*.*"
rmdir /s /q "setup files"

:end

