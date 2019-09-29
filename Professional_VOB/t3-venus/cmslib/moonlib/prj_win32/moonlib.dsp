# Microsoft Developer Studio Project File - Name="moonlib" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=moonlib - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "moonlib.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "moonlib.mak" CFG="moonlib - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "moonlib - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "moonlib - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "moonlib - Win32 Release"

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
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GR /GX /O2 /I "..\include" /I "..\source" /I "..\..\common\include" /I "..\..\common\source" /I "..\..\..\..\10-common\include\um" /I "..\..\..\..\10-common\include\radstack" /I "..\..\..\..\10-common\include\platform" /I "..\..\..\..\10-common\include\mt" /I "..\..\..\..\10-common\include\system1" /I "..\..\..\..\10-common\include\nms1" /I "..\..\..\..\10-common\include\snmp" /I "..\..\..\..\10-common\include\protocol" /I "..\..\..\..\10-common\include\tp" /I "..\..\..\common\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\..\..\..\10-common\lib\Release\win32\moonlib.lib"

!ELSEIF  "$(CFG)" == "moonlib - Win32 Debug"

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
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GR /GX /ZI /Od /I "..\include" /I "..\source" /I "..\..\common\include" /I "..\..\common\source" /I "..\..\..\..\10-common\include\um" /I "..\..\..\..\10-common\include\radstack" /I "..\..\..\..\10-common\include\platform" /I "..\..\..\..\10-common\include\mt" /I "..\..\..\..\10-common\include\system1" /I "..\..\..\..\10-common\include\nms1" /I "..\..\..\..\10-common\include\snmp" /I "..\..\..\..\10-common\include\protocol" /I "..\..\..\..\10-common\include\tp" /I "..\..\..\common\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "SOFT_CODEC" /Yu"stdafx.h" /FD /GZ /c
# SUBTRACT CPP /X
# ADD BASE RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\..\..\..\10-common\lib\debug\win32\moonlib.lib"

!ENDIF 

# Begin Target

# Name "moonlib - Win32 Release"
# Name "moonlib - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "common No. 1"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\common\source\commandqueue.cpp
# End Source File
# Begin Source File

SOURCE=..\..\common\source\kdvdispevent.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=..\source\camconfig.cpp
# End Source File
# Begin Source File

SOURCE=..\source\moonlib.cpp
# End Source File
# Begin Source File

SOURCE=..\source\moonmsgdriver.cpp
# End Source File
# Begin Source File

SOURCE=..\source\moonmsgrecver.cpp
# End Source File
# Begin Source File

SOURCE=..\source\moonSession.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=..\source\sysconfig.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Group "common"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\common\include\commandqueue.h
# End Source File
# End Group
# Begin Source File

SOURCE=..\include\camconfig.h
# End Source File
# Begin Source File

SOURCE=..\..\..\common\include\moonlib.h
# End Source File
# Begin Source File

SOURCE=..\include\moonmsgdriver.h
# End Source File
# Begin Source File

SOURCE=..\include\moonmsgrecver.h
# End Source File
# Begin Source File

SOURCE=..\include\moonSession.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=..\include\sysconfig.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\Readme.txt
# End Source File
# End Target
# End Project
