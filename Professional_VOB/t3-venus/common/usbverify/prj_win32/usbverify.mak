# Microsoft Developer Studio Generated NMAKE File, Based on usbverify.dsp
!IF "$(CFG)" == ""
CFG=UsbVerify - Win32 Debug
!MESSAGE No configuration specified. Defaulting to UsbVerify - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "UsbVerify - Win32 Release" && "$(CFG)" != "UsbVerify - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "usbverify.mak" CFG="UsbVerify - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "UsbVerify - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "UsbVerify - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "UsbVerify - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release

ALL : "..\..\..\..\10-common\lib\release\win32\usbverify.lib"


CLEAN :
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\UsbImportLicence.obj"
	-@erase "$(INTDIR)\UsbKey.obj"
	-@erase "$(INTDIR)\UsbVerify.obj"
	-@erase "$(INTDIR)\usbverify.pch"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "..\..\..\..\10-common\lib\release\win32\usbverify.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /ML /W3 /GX /O2 /I ".\\" /I "..\include" /I "..\..\..\..\10-common\include\system1" /I "..\..\..\..\10-common\include\nms1" /I "..\..\include" /I "..\..\..\..\b0-thirdparty\haikey\include" /I "..\..\..\..\10-common\include\protocol" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /Fp"$(INTDIR)\usbverify.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\usbverify.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
LIB32_FLAGS=/nologo /out:"..\..\..\..\10-common\lib\release\win32\usbverify.lib" 
LIB32_OBJS= \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\UsbImportLicence.obj" \
	"$(INTDIR)\UsbKey.obj" \
	"$(INTDIR)\UsbVerify.obj"

"..\..\..\..\10-common\lib\release\win32\usbverify.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ELSEIF  "$(CFG)" == "UsbVerify - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug

ALL : "..\..\..\..\10-common\lib\debug\win32\usbverify.lib"


CLEAN :
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\UsbImportLicence.obj"
	-@erase "$(INTDIR)\UsbKey.obj"
	-@erase "$(INTDIR)\UsbVerify.obj"
	-@erase "$(INTDIR)\usbverify.pch"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "..\..\..\..\10-common\lib\debug\win32\usbverify.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MLd /W3 /Gm /GX /ZI /Od /I ".\\" /I "..\include" /I "..\..\..\..\10-common\include\system1" /I "..\..\..\..\10-common\include\nms1" /I "..\..\include" /I "..\..\..\..\b0-thirdparty\haikey\include" /I "..\..\..\..\10-common\include\protocol" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /Fp"$(INTDIR)\usbverify.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\usbverify.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
LIB32_FLAGS=/nologo /out:"..\..\..\..\10-common\lib\debug\win32\usbverify.lib" 
LIB32_OBJS= \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\UsbImportLicence.obj" \
	"$(INTDIR)\UsbKey.obj" \
	"$(INTDIR)\UsbVerify.obj"

"..\..\..\..\10-common\lib\debug\win32\usbverify.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ENDIF 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("usbverify.dep")
!INCLUDE "usbverify.dep"
!ELSE 
!MESSAGE Warning: cannot find "usbverify.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "UsbVerify - Win32 Release" || "$(CFG)" == "UsbVerify - Win32 Debug"
SOURCE=..\source\StdAfx.cpp

!IF  "$(CFG)" == "UsbVerify - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /I ".\\" /I "..\include" /I "..\..\..\..\10-common\include\system1" /I "..\..\..\..\10-common\include\nms1" /I "..\..\include" /I "..\..\..\..\b0-thirdparty\haikey\include" /I "..\..\..\..\10-common\include\protocol" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /Fp"$(INTDIR)\usbverify.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\usbverify.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "UsbVerify - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /I ".\\" /I "..\include" /I "..\..\..\..\10-common\include\system1" /I "..\..\..\..\10-common\include\nms1" /I "..\..\include" /I "..\..\..\..\b0-thirdparty\haikey\include" /I "..\..\..\..\10-common\include\protocol" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /Fp"$(INTDIR)\usbverify.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\usbverify.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\source\UsbImportLicence.cpp

"$(INTDIR)\UsbImportLicence.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\usbverify.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\source\UsbKey.cpp

"$(INTDIR)\UsbKey.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\usbverify.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\source\UsbVerify.cpp

"$(INTDIR)\UsbVerify.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\usbverify.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)



!ENDIF 

