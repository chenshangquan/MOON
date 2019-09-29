# Microsoft Developer Studio Project File - Name="centerctrl" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=centerctrl - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "centerctrl.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "centerctrl.mak" CFG="centerctrl - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "centerctrl - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "centerctrl - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName "centerctrl"
# PROP Scc_LocalPath ".."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "centerctrl - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GR /GX /O2 /I ".\\" /I "..\include" /I "..\..\common\include" /I "..\..\..\10-common\include\nms1" /I "..\..\..\10-common\include\system1" /I "..\..\..\10-common\include\protocol" /I "..\..\..\10-common\include\platform" /I "..\..\common\include\platform sdk\include" /I "..\..\..\10-common\include\tp" /I "..\..\UIFactory\include" /I "..\..\uiexlib\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386 /nodefaultlib:"nafxcw" /nodefaultlib:"nafxcwd" /nodefaultlib:"libcd" /nodefaultlib:"libc" /nodefaultlib:"libcmt" /nodefaultlib:"msvcrtd" /nodefaultlib:"Imm32.lib" /nodefaultlib:"libcmtd.lib" /nodefaultlib:"strmiids.lib" /libpath:"..\..\..\10-common\lib\release\win32" /libpath:"..\..\common\include\platform sdk\lib"

!ELSEIF  "$(CFG)" == "centerctrl - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GR /GX /ZI /Od /I ".\\" /I "..\include" /I "..\..\common\include" /I "..\..\..\10-common\include\nms1" /I "..\..\..\10-common\include\system1" /I "..\..\..\10-common\include\protocol" /I "..\..\..\10-common\include\platform" /I "..\..\common\include\platform sdk\include" /I "..\..\..\10-common\include\tp" /I "..\..\UIFactory\include" /I "..\..\uiexlib\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /nodefaultlib:"nafxcwd.lib" /nodefaultlib:"libcd.lib" /nodefaultlib:"libc.lib" /nodefaultlib:"libcmt.lib" /nodefaultlib:"msvcrt.lib" /nodefaultlib:"Imm32.lib" /nodefaultlib:"libcmtd.lib" /pdbtype:sept /libpath:"..\..\..\10-common\lib\debug\win32" /libpath:"..\..\common\include\platform sdk\lib"

!ENDIF 

# Begin Target

# Name "centerctrl - Win32 Release"
# Name "centerctrl - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "logic_cpp"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\source\airconditionlogic.cpp
# End Source File
# Begin Source File

SOURCE=..\source\CameraLogic.cpp
# End Source File
# Begin Source File

SOURCE=..\source\centerctrllogic.cpp
# End Source File
# Begin Source File

SOURCE=..\source\CurtainCfgLogic.cpp
# End Source File
# Begin Source File

SOURCE=..\source\mainmenulogic.cpp
# End Source File
# Begin Source File

SOURCE=..\source\monitorlogic.cpp
# End Source File
# Begin Source File

SOURCE=..\source\touchpadlogic.cpp
# End Source File
# Begin Source File

SOURCE=..\source\WndLogicBase.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=..\source\centerctrl.cpp
# End Source File
# Begin Source File

SOURCE=.\centerctrl.rc
# End Source File
# Begin Source File

SOURCE=..\source\centerctrlDlg.cpp
# End Source File
# Begin Source File

SOURCE=..\source\commoninterface.cpp
# End Source File
# Begin Source File

SOURCE=..\source\LogicManage.cpp
# End Source File
# Begin Source File

SOURCE=..\source\msgdispatch.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Group "logic_h"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\include\airconditionlogic.h
# End Source File
# Begin Source File

SOURCE=..\include\CameraLogic.h
# End Source File
# Begin Source File

SOURCE=..\include\centerctrllogic.h
# End Source File
# Begin Source File

SOURCE=..\include\CurtainCfgLogic.h
# End Source File
# Begin Source File

SOURCE=..\include\mainmenulogic.h
# End Source File
# Begin Source File

SOURCE=..\include\monitorlogic.h
# End Source File
# Begin Source File

SOURCE=..\include\touchpadlogic.h
# End Source File
# Begin Source File

SOURCE=..\include\WndLogicBase.h
# End Source File
# End Group
# Begin Source File

SOURCE=..\include\centerctrl.h
# End Source File
# Begin Source File

SOURCE=..\include\centerctrlDlg.h
# End Source File
# Begin Source File

SOURCE=..\include\commoninterface.h
# End Source File
# Begin Source File

SOURCE=..\include\HeaderCtrl.h
# End Source File
# Begin Source File

SOURCE=..\include\LogicManage.h
# End Source File
# Begin Source File

SOURCE=..\include\msgdispatch.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\centerctrl.ico
# End Source File
# Begin Source File

SOURCE=.\res\centerctrl.rc2
# End Source File
# End Group
# Begin Source File

SOURCE=.\centerctrl.exe.manifest
# End Source File
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
