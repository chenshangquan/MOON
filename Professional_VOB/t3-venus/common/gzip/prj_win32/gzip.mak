# Microsoft Developer Studio Generated NMAKE File, Based on gzip.dsp
!IF "$(CFG)" == ""
CFG=gzip - Win32 Debug
!MESSAGE No configuration specified. Defaulting to gzip - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "gzip - Win32 Release" && "$(CFG)" != "gzip - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "gzip.mak" CFG="gzip - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "gzip - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "gzip - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "gzip - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release

ALL : "..\..\..\..\10-common\lib\release\win32\gzip.lib"


CLEAN :
	-@erase "$(INTDIR)\bits.obj"
	-@erase "$(INTDIR)\crypt.obj"
	-@erase "$(INTDIR)\czip.obj"
	-@erase "$(INTDIR)\deflate.obj"
	-@erase "$(INTDIR)\getopt.obj"
	-@erase "$(INTDIR)\gzip.obj"
	-@erase "$(INTDIR)\inflate.obj"
	-@erase "$(INTDIR)\lzw.obj"
	-@erase "$(INTDIR)\tailor.obj"
	-@erase "$(INTDIR)\trees.obj"
	-@erase "$(INTDIR)\unlzh.obj"
	-@erase "$(INTDIR)\unlzw.obj"
	-@erase "$(INTDIR)\unpack.obj"
	-@erase "$(INTDIR)\unzip.obj"
	-@erase "$(INTDIR)\util.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\zip.obj"
	-@erase "..\..\..\..\10-common\lib\release\win32\gzip.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GX /O2 /I "./" /I "../include" /I "../../../../10-common/include/system1" /I "../../../../10-common/include/nms1" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /Fp"$(INTDIR)\gzip.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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

RSC=rc.exe
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\gzip.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
LIB32_FLAGS=/nologo /out:"../../../../10-common/lib/release/win32/gzip.lib" 
LIB32_OBJS= \
	"$(INTDIR)\bits.obj" \
	"$(INTDIR)\crypt.obj" \
	"$(INTDIR)\czip.obj" \
	"$(INTDIR)\deflate.obj" \
	"$(INTDIR)\getopt.obj" \
	"$(INTDIR)\gzip.obj" \
	"$(INTDIR)\inflate.obj" \
	"$(INTDIR)\lzw.obj" \
	"$(INTDIR)\tailor.obj" \
	"$(INTDIR)\trees.obj" \
	"$(INTDIR)\unlzh.obj" \
	"$(INTDIR)\unlzw.obj" \
	"$(INTDIR)\unpack.obj" \
	"$(INTDIR)\unzip.obj" \
	"$(INTDIR)\util.obj" \
	"$(INTDIR)\zip.obj"

"..\..\..\..\10-common\lib\release\win32\gzip.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ELSEIF  "$(CFG)" == "gzip - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug

ALL : "..\..\..\..\10-common\lib\debug\win32\gzip.lib"


CLEAN :
	-@erase "$(INTDIR)\bits.obj"
	-@erase "$(INTDIR)\crypt.obj"
	-@erase "$(INTDIR)\czip.obj"
	-@erase "$(INTDIR)\deflate.obj"
	-@erase "$(INTDIR)\getopt.obj"
	-@erase "$(INTDIR)\gzip.obj"
	-@erase "$(INTDIR)\inflate.obj"
	-@erase "$(INTDIR)\lzw.obj"
	-@erase "$(INTDIR)\tailor.obj"
	-@erase "$(INTDIR)\trees.obj"
	-@erase "$(INTDIR)\unlzh.obj"
	-@erase "$(INTDIR)\unlzw.obj"
	-@erase "$(INTDIR)\unpack.obj"
	-@erase "$(INTDIR)\unzip.obj"
	-@erase "$(INTDIR)\util.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\zip.obj"
	-@erase "..\..\..\..\10-common\lib\debug\win32\gzip.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /ZI /Od /I "./" /I "../include" /I "../../../../10-common/include/system1" /I "../../../../10-common/include/nms1" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /Fp"$(INTDIR)\gzip.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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

RSC=rc.exe
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\gzip.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
LIB32_FLAGS=/nologo /out:"../../../../10-common/lib/debug/win32/gzip.lib" 
LIB32_OBJS= \
	"$(INTDIR)\bits.obj" \
	"$(INTDIR)\crypt.obj" \
	"$(INTDIR)\czip.obj" \
	"$(INTDIR)\deflate.obj" \
	"$(INTDIR)\getopt.obj" \
	"$(INTDIR)\gzip.obj" \
	"$(INTDIR)\inflate.obj" \
	"$(INTDIR)\lzw.obj" \
	"$(INTDIR)\tailor.obj" \
	"$(INTDIR)\trees.obj" \
	"$(INTDIR)\unlzh.obj" \
	"$(INTDIR)\unlzw.obj" \
	"$(INTDIR)\unpack.obj" \
	"$(INTDIR)\unzip.obj" \
	"$(INTDIR)\util.obj" \
	"$(INTDIR)\zip.obj"

"..\..\..\..\10-common\lib\debug\win32\gzip.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("gzip.dep")
!INCLUDE "gzip.dep"
!ELSE 
!MESSAGE Warning: cannot find "gzip.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "gzip - Win32 Release" || "$(CFG)" == "gzip - Win32 Debug"
SOURCE=..\source\bits.c

"$(INTDIR)\bits.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\source\crypt.c

"$(INTDIR)\crypt.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\source\czip.cpp

"$(INTDIR)\czip.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\source\deflate.c

"$(INTDIR)\deflate.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\source\getopt.c

"$(INTDIR)\getopt.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\source\gzip.c

"$(INTDIR)\gzip.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\source\inflate.c

"$(INTDIR)\inflate.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\source\lzw.c

"$(INTDIR)\lzw.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\source\tailor.c

"$(INTDIR)\tailor.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\source\trees.c

"$(INTDIR)\trees.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\source\unlzh.c

"$(INTDIR)\unlzh.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\source\unlzw.c

"$(INTDIR)\unlzw.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\source\unpack.c

"$(INTDIR)\unpack.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\source\unzip.c

"$(INTDIR)\unzip.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\source\util.c

"$(INTDIR)\util.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\source\zip.c

"$(INTDIR)\zip.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)



!ENDIF 

