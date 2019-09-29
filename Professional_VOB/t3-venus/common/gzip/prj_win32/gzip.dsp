# Microsoft Developer Studio Project File - Name="gzip" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=gzip - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "gzip.mak".
!MESSAGE 
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

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName "gzip"
# PROP Scc_LocalPath "."
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "gzip - Win32 Release"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "./" /I "../include" /I "../../../../10-common/include/system1" /I "../../../../10-common/include/nms1" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /YX /FD /c
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"../../../../10-common/lib/release/win32/gzip.lib"

!ELSEIF  "$(CFG)" == "gzip - Win32 Debug"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "./" /I "../include" /I "../../../../10-common/include/system1" /I "../../../../10-common/include/nms1" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /YX /FD /GZ /c
# ADD BASE RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"../../../../10-common/lib/debug/win32/gzip.lib"

!ENDIF 

# Begin Target

# Name "gzip - Win32 Release"
# Name "gzip - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\source\bits.c
# End Source File
# Begin Source File

SOURCE=..\source\crypt.c
# End Source File
# Begin Source File

SOURCE=..\source\czip.cpp
# End Source File
# Begin Source File

SOURCE=..\source\deflate.c
# End Source File
# Begin Source File

SOURCE=..\source\getopt.c
# End Source File
# Begin Source File

SOURCE=..\source\gzip.c
# End Source File
# Begin Source File

SOURCE=..\source\inflate.c
# End Source File
# Begin Source File

SOURCE=..\source\lzw.c
# End Source File
# Begin Source File

SOURCE=..\source\tailor.c
# End Source File
# Begin Source File

SOURCE=..\source\trees.c
# End Source File
# Begin Source File

SOURCE=..\source\unlzh.c
# End Source File
# Begin Source File

SOURCE=..\source\unlzw.c
# End Source File
# Begin Source File

SOURCE=..\source\unpack.c
# End Source File
# Begin Source File

SOURCE=..\source\unzip.c
# End Source File
# Begin Source File

SOURCE=..\source\util.c
# End Source File
# Begin Source File

SOURCE=..\source\zip.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\include\crypt.h
# End Source File
# Begin Source File

SOURCE=..\include\getopt.h
# End Source File
# Begin Source File

SOURCE=..\include\gzip.h
# End Source File
# Begin Source File

SOURCE=..\include\lzw.h
# End Source File
# Begin Source File

SOURCE=..\include\revision.h
# End Source File
# Begin Source File

SOURCE=..\include\tailor.h
# End Source File
# End Group
# End Target
# End Project
