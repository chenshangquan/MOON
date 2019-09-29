# Microsoft Developer Studio Project File - Name="cms" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=cms - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "cms.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "cms.mak" CFG="cms - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "cms - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "cms - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName "cms"
# PROP Scc_LocalPath "..\.."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "cms - Win32 Release"

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
# ADD CPP /nologo /MD /W3 /GR /GX /Zd /O2 /I ".\\" /I "..\include" /I "..\..\common\include" /I "..\..\..\10-common\include\nms1" /I "..\..\..\10-common\include\system1" /I "..\..\..\10-common\include\protocol" /I "..\..\..\10-common\include\platform" /I "..\..\common\include\platform sdk\include" /I "..\..\..\10-common\include\tp" /I "..\..\UIFactory\include" /I "..\..\uiexlib\include" /I "..\..\luaplus" /I "..\..\windowsexsdk\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /map /machine:I386 /nodefaultlib:"nafxcw" /nodefaultlib:"nafxcwd" /nodefaultlib:"libcd" /nodefaultlib:"libc" /nodefaultlib:"libcmt" /nodefaultlib:"msvcrtd" /nodefaultlib:"Imm32.lib" /nodefaultlib:"libcmtd.lib" /nodefaultlib:"strmiids.lib" /out:"Release/cnc.exe" /libpath:"..\..\..\10-common\lib\release\win32" /libpath:"..\..\UIFactory\expat\lib\release" /libpath:"..\..\common\include\platform sdk\lib" /libpath:"..\..\windowsexsdk\lib\release" /mapinfo:lines
# SUBTRACT LINK32 /pdb:none /debug

!ELSEIF  "$(CFG)" == "cms - Win32 Debug"

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
# ADD CPP /nologo /MDd /W3 /Gm /Gi /GR /GX /ZI /Od /I ".\\" /I "..\include" /I "..\..\common\include" /I "..\..\..\10-common\include\nms1" /I "..\..\..\10-common\include\system1" /I "..\..\..\10-common\include\protocol" /I "..\..\..\10-common\include\platform" /I "..\..\common\include\platform sdk\include" /I "..\..\..\10-common\include\tp" /I "..\..\UIFactory\include" /I "..\..\uiexlib\include" /I "..\..\luaplus" /I "..\..\windowsexsdk\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /map /debug /machine:I386 /nodefaultlib:"nafxcwd.lib" /nodefaultlib:"libcd.lib" /nodefaultlib:"libc.lib" /nodefaultlib:"libcmt.lib" /nodefaultlib:"msvcrt.lib" /nodefaultlib:"Imm32.lib" /nodefaultlib:"libcmtd.lib" /out:"Debug/cnc.exe" /pdbtype:sept /libpath:"..\..\..\10-common\lib\debug\win32" /libpath:"..\..\UIFactory\expat\lib\debug" /libpath:"..\..\common\include\platform sdk\lib" /libpath:"..\..\windowsexsdk\lib\debug" /mapinfo:lines
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "cms - Win32 Release"
# Name "cms - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "logic_cpp"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\source\addrbooklogic.cpp
# End Source File
# Begin Source File

SOURCE=..\source\addreditlogic.cpp
# End Source File
# Begin Source File

SOURCE=..\source\alarminfologic.cpp
# End Source File
# Begin Source File

SOURCE=..\source\audmixLogic.cpp
# End Source File
# Begin Source File

SOURCE=..\source\callingLogic.cpp
# End Source File
# Begin Source File

SOURCE=..\source\callSerCfgAudioModeLogic.cpp
# End Source File
# Begin Source File

SOURCE=..\source\callservercfglogic.cpp
# End Source File
# Begin Source File

SOURCE=..\source\callservercfgmodechooselogic.cpp
# End Source File
# Begin Source File

SOURCE=..\source\callservercfgshowmodechooselogic.cpp
# End Source File
# Begin Source File

SOURCE=..\source\cnscfglogic.cpp
# End Source File
# Begin Source File

SOURCE=..\source\confCnsCtrlLogic.cpp
# End Source File
# Begin Source File

SOURCE=..\source\confCnsLstLogic.cpp
# End Source File
# Begin Source File

SOURCE=..\source\confCnsShowCtrlLogic.cpp
# End Source File
# Begin Source File

SOURCE=..\source\confCtrlLogic.cpp
# End Source File
# Begin Source File

SOURCE=..\source\conftempLstLogic.cpp
# End Source File
# Begin Source File

SOURCE=..\source\connectcnslogic.cpp
# End Source File
# Begin Source File

SOURCE=..\source\dualSrcLogic.cpp
# End Source File
# Begin Source File

SOURCE=..\source\dualSrcManageLogic.cpp
# End Source File
# Begin Source File

SOURCE=..\source\ethnetcfglogic.cpp
# End Source File
# Begin Source File

SOURCE=..\source\lockScreenLogic.cpp
# End Source File
# Begin Source File

SOURCE=..\source\logicManage.cpp
# End Source File
# Begin Source File

SOURCE=..\source\loginLogic.cpp
# End Source File
# Begin Source File

SOURCE=..\source\mainFrameLogic.cpp
# End Source File
# Begin Source File

SOURCE=..\source\mainmenulogic.cpp
# End Source File
# Begin Source File

SOURCE=..\source\msgBoxLogic.cpp
# End Source File
# Begin Source File

SOURCE=..\source\NetManageCfgLogic.cpp
# End Source File
# Begin Source File

SOURCE=..\source\regGklogic.cpp
# End Source File
# Begin Source File

SOURCE=..\source\regservicelogic.cpp
# End Source File
# Begin Source File

SOURCE=..\source\SaveLogLogic.cpp
# End Source File
# Begin Source File

SOURCE=..\source\scrnDisplayMenuLogic.cpp
# End Source File
# Begin Source File

SOURCE=..\source\simulateCnsLogic.cpp
# End Source File
# Begin Source File

SOURCE=..\source\syscfglogic.cpp
# End Source File
# Begin Source File

SOURCE=..\source\SysStandByLogic.cpp
# End Source File
# Begin Source File

SOURCE=..\source\timeSetLogic.cpp
# End Source File
# Begin Source File

SOURCE=..\source\titleBarLogic.cpp
# End Source File
# Begin Source File

SOURCE=..\source\toolMenuLogic.cpp
# End Source File
# Begin Source File

SOURCE=..\source\updservicelogic.cpp
# End Source File
# Begin Source File

SOURCE=..\source\userDefinedLogic.cpp
# End Source File
# Begin Source File

SOURCE=..\source\userManageLogic.cpp
# End Source File
# Begin Source File

SOURCE=..\source\VideoLogic.cpp
# End Source File
# Begin Source File

SOURCE=..\source\volumCtrlLogic.cpp
# End Source File
# Begin Source File

SOURCE=..\source\WaitingRefreshLogic.cpp
# End Source File
# Begin Source File

SOURCE=..\source\wndLogicBase.cpp
# End Source File
# End Group
# Begin Group "business_cpp"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\source\cncaddrbook.cpp
# End Source File
# Begin Source File

SOURCE=..\source\cncconf.cpp
# End Source File
# Begin Source File

SOURCE=..\source\cncconfig.cpp
# End Source File
# Begin Source File

SOURCE=..\source\commoninterface.cpp
# End Source File
# Begin Source File

SOURCE=..\source\errCodeManage.cpp
# End Source File
# Begin Source File

SOURCE=..\source\handleErr.cpp
# End Source File
# Begin Source File

SOURCE=..\source\msgdispatch.cpp
# End Source File
# Begin Source File

SOURCE=..\source\sysTime.cpp
# End Source File
# Begin Source File

SOURCE=..\source\uiconfig.cpp
# End Source File
# Begin Source File

SOURCE=..\source\umcconf.cpp
# End Source File
# Begin Source File

SOURCE=..\source\umcconftemplate.cpp
# End Source File
# Begin Source File

SOURCE=..\source\umctvw.cpp
# End Source File
# Begin Source File

SOURCE=..\source\umcuser.cpp
# End Source File
# End Group
# Begin Group "UI_cpp"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\source\AddrList.cpp
# End Source File
# Begin Source File

SOURCE=..\source\ctrlFactory.cpp
# End Source File
# Begin Source File

SOURCE=..\source\dlgchild.cpp
# ADD CPP /I "..\prj_win32"
# End Source File
# Begin Source File

SOURCE=..\source\dlgModal.cpp
# End Source File
# Begin Source File

SOURCE=..\source\dlgoverlapped.cpp
# ADD CPP /I "..\prj_win32"
# End Source File
# Begin Source File

SOURCE=..\source\dlgpopup.cpp
# End Source File
# Begin Source File

SOURCE=..\source\horilist.cpp
# End Source File
# Begin Source File

SOURCE=..\source\popupdlg.cpp
# ADD CPP /I "..\prj_win32"
# End Source File
# Begin Source File

SOURCE=..\source\TouchListHelp.cpp
# End Source File
# Begin Source File

SOURCE=..\source\TouchListProperty.cpp
# End Source File
# Begin Source File

SOURCE=..\source\transparentbasedlg.cpp
# End Source File
# Begin Source File

SOURCE=..\source\transparentbaselist.cpp
# End Source File
# Begin Source File

SOURCE=..\source\UiFactroyLog.cpp
# End Source File
# Begin Source File

SOURCE=..\source\uiManage.cpp
# End Source File
# Begin Source File

SOURCE=..\source\valueSet.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=..\source\cms.cpp
# End Source File
# Begin Source File

SOURCE=.\cms.rc
# End Source File
# Begin Source File

SOURCE=..\source\cmsDlg.cpp
# End Source File
# Begin Source File

SOURCE=..\source\confSign.cpp
# End Source File
# Begin Source File

SOURCE=..\source\Decoder.cpp
# End Source File
# Begin Source File

SOURCE=..\source\funcLstMenu.cpp
# End Source File
# Begin Source File

SOURCE=..\source\hzpysearch.cpp
# End Source File
# Begin Source File

SOURCE=..\source\ipinfomanager.cpp
# End Source File
# Begin Source File

SOURCE=..\source\netadapter.cpp
# End Source File
# Begin Source File

SOURCE=..\source\outPrint.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=..\source\UIDataMgr.cpp
# End Source File
# Begin Source File

SOURCE=..\source\valueStorage.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Group "UIFactoryLib"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\UIFactory\include\EventManage.h
# End Source File
# Begin Source File

SOURCE=..\..\UIFactory\include\MfcDefaultWndPropertySet.h
# End Source File
# Begin Source File

SOURCE=..\..\UIFactory\include\PropertyHelp.h
# End Source File
# Begin Source File

SOURCE=..\..\UIFactory\include\PropertySet.h
# End Source File
# Begin Source File

SOURCE=..\..\UIFactory\include\RegDefaultData.h
# End Source File
# Begin Source File

SOURCE=..\..\UIFactory\include\System.h
# End Source File
# Begin Source File

SOURCE=..\..\UIFactory\include\uifactorydef.h
# End Source File
# Begin Source File

SOURCE=..\..\UIFactory\include\UifactoryHeader.h
# End Source File
# End Group
# Begin Group "logic_h"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\include\addrbooklogic.h
# End Source File
# Begin Source File

SOURCE=..\include\addreditlogic.h
# End Source File
# Begin Source File

SOURCE=..\include\alarminfologic.h
# End Source File
# Begin Source File

SOURCE=..\include\audmixLogic.h
# End Source File
# Begin Source File

SOURCE=..\include\callingLogic.h
# End Source File
# Begin Source File

SOURCE=..\include\callSerCfgAudioModeLogic.h
# End Source File
# Begin Source File

SOURCE=..\include\callservercfglogic.h
# End Source File
# Begin Source File

SOURCE=..\include\callservercfgmodechooselogic.h
# End Source File
# Begin Source File

SOURCE=..\include\callservercfgshowmodechooselogic.h
# End Source File
# Begin Source File

SOURCE=..\include\cnscfglogic.h
# End Source File
# Begin Source File

SOURCE=..\include\confCnsLstLogic.h
# End Source File
# Begin Source File

SOURCE=..\include\confCtrlLogic.h
# End Source File
# Begin Source File

SOURCE=..\include\conftempLstLogic.h
# End Source File
# Begin Source File

SOURCE=..\include\connectcnslogic.h
# End Source File
# Begin Source File

SOURCE=..\include\dualSrcLogic.h
# End Source File
# Begin Source File

SOURCE=..\include\dualSrcManageLogic.h
# End Source File
# Begin Source File

SOURCE=..\include\ethnetcfglogic.h
# End Source File
# Begin Source File

SOURCE=..\include\lockScreenLogic.h
# End Source File
# Begin Source File

SOURCE=..\include\logicManage.h
# End Source File
# Begin Source File

SOURCE=..\include\loginLogic.h
# End Source File
# Begin Source File

SOURCE=..\include\mainFrameLogic.h
# End Source File
# Begin Source File

SOURCE=..\include\mainmenulogic.h
# End Source File
# Begin Source File

SOURCE=..\include\msgBoxLogic.h
# End Source File
# Begin Source File

SOURCE=..\include\NetManageCfgLogic.h
# End Source File
# Begin Source File

SOURCE=..\include\processMsgBase.h
# End Source File
# Begin Source File

SOURCE=..\include\regGklogic.h
# End Source File
# Begin Source File

SOURCE=..\include\regservicelogic.h
# End Source File
# Begin Source File

SOURCE=..\include\SaveLogLogic.h
# End Source File
# Begin Source File

SOURCE=..\include\scrnDisplayMenuLogic.h
# End Source File
# Begin Source File

SOURCE=..\include\simulateCnsLogic.h
# End Source File
# Begin Source File

SOURCE=..\include\syscfglogic.h
# End Source File
# Begin Source File

SOURCE=..\include\SysStandByLogic.h
# End Source File
# Begin Source File

SOURCE=..\include\timeSetLogic.h
# End Source File
# Begin Source File

SOURCE=..\include\titleBarLogic.h
# End Source File
# Begin Source File

SOURCE=..\include\toolMenuLogic.h
# End Source File
# Begin Source File

SOURCE=..\include\updservicelogic.h
# End Source File
# Begin Source File

SOURCE=..\include\userDefinedLogic.h
# End Source File
# Begin Source File

SOURCE=..\include\userManageLogic.h
# End Source File
# Begin Source File

SOURCE=..\include\VideoLogic.h
# End Source File
# Begin Source File

SOURCE=..\include\volumCtrlLogic.h
# End Source File
# Begin Source File

SOURCE=..\include\WaitingRefreshLogic.h
# End Source File
# Begin Source File

SOURCE=..\include\wndLogicBase.h
# End Source File
# End Group
# Begin Group "business_h"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\include\commoninterface.h
# End Source File
# Begin Source File

SOURCE=..\include\errCodeManage.h
# End Source File
# Begin Source File

SOURCE=..\include\handleErr.h
# End Source File
# Begin Source File

SOURCE=..\include\msgdispatch.h
# End Source File
# Begin Source File

SOURCE=..\include\sysTime.h
# End Source File
# End Group
# Begin Group "UI_h"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\include\AddrList.h
# End Source File
# Begin Source File

SOURCE=..\include\ctrlFactory.h
# End Source File
# Begin Source File

SOURCE=..\include\dlgchild.h
# End Source File
# Begin Source File

SOURCE=..\include\dlgModal.h
# End Source File
# Begin Source File

SOURCE=..\include\dlgoverlapped.h
# End Source File
# Begin Source File

SOURCE=..\include\dlgpopup.h
# End Source File
# Begin Source File

SOURCE=..\include\horilist.h
# End Source File
# Begin Source File

SOURCE=..\include\popupdlg.h
# End Source File
# Begin Source File

SOURCE=..\include\TouchListHelp.h
# End Source File
# Begin Source File

SOURCE=..\include\TouchListProperty.h
# End Source File
# Begin Source File

SOURCE=..\include\transparentbasedlg.h
# End Source File
# Begin Source File

SOURCE=..\include\UiFactroyLog.h
# End Source File
# Begin Source File

SOURCE=..\include\uiManage.h
# End Source File
# Begin Source File

SOURCE=..\include\valueSet.h
# End Source File
# Begin Source File

SOURCE=..\include\valueStorage.h
# End Source File
# End Group
# Begin Source File

SOURCE=..\include\cms.h
# End Source File
# Begin Source File

SOURCE=..\include\cmsDlg.h
# End Source File
# Begin Source File

SOURCE=..\include\confSign.h
# End Source File
# Begin Source File

SOURCE=..\include\Decoder.h
# End Source File
# Begin Source File

SOURCE=..\include\funcLstMenu.h
# End Source File
# Begin Source File

SOURCE=..\include\HeaderCtrl.h
# End Source File
# Begin Source File

SOURCE=..\include\hzpysearch.h
# End Source File
# Begin Source File

SOURCE=..\include\ipinfomanager.h
# End Source File
# Begin Source File

SOURCE=..\..\common\include\msgIdDispatch.h
# End Source File
# Begin Source File

SOURCE=..\include\netadapter.h
# End Source File
# Begin Source File

SOURCE=..\include\outPrint.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=..\include\UIDataMgr.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\32.ico
# End Source File
# Begin Source File

SOURCE=.\res\cms.ico
# End Source File
# Begin Source File

SOURCE=.\res\cms.rc2
# End Source File
# Begin Source File

SOURCE=.\res\cnc16.ico
# End Source File
# Begin Source File

SOURCE=.\res\cnc32.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon1.ico
# End Source File
# Begin Source File

SOURCE=.\res\msgtipalert.ico
# End Source File
# Begin Source File

SOURCE=.\res\popmsg_close_normal.ico
# End Source File
# Begin Source File

SOURCE=.\res\popmsg_close_press.ico
# End Source File
# End Group
# Begin Source File

SOURCE=.\cnc.exe.manifest
# End Source File
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
