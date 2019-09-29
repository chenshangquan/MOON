# Microsoft Developer Studio Generated NMAKE File, Based on cms.dsp
!IF "$(CFG)" == ""
CFG=cms - Win32 Debug
!MESSAGE No configuration specified. Defaulting to cms - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "cms - Win32 Release" && "$(CFG)" != "cms - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
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
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "cms - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\cms.exe" "$(OUTDIR)\cms.bsc"

!ELSE 

ALL : "UIFactory - Win32 Release" "umclib - Win32 Release" "cncLib - Win32 Release" "$(OUTDIR)\cms.exe" "$(OUTDIR)\cms.bsc"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"cncLib - Win32 ReleaseCLEAN" "umclib - Win32 ReleaseCLEAN" "UIFactory - Win32 ReleaseCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\addrbooklogic.obj"
	-@erase "$(INTDIR)\addrbooklogic.sbr"
	-@erase "$(INTDIR)\addreditlogic.obj"
	-@erase "$(INTDIR)\addreditlogic.sbr"
	-@erase "$(INTDIR)\AddrList.obj"
	-@erase "$(INTDIR)\AddrList.sbr"
	-@erase "$(INTDIR)\audmixLogic.obj"
	-@erase "$(INTDIR)\audmixLogic.sbr"
	-@erase "$(INTDIR)\cms.obj"
	-@erase "$(INTDIR)\cms.pch"
	-@erase "$(INTDIR)\cms.res"
	-@erase "$(INTDIR)\cms.sbr"
	-@erase "$(INTDIR)\cmsDlg.obj"
	-@erase "$(INTDIR)\cmsDlg.sbr"
	-@erase "$(INTDIR)\cncaddrbook.obj"
	-@erase "$(INTDIR)\cncaddrbook.sbr"
	-@erase "$(INTDIR)\cncconfig.obj"
	-@erase "$(INTDIR)\cncconfig.sbr"
	-@erase "$(INTDIR)\commoninterface.obj"
	-@erase "$(INTDIR)\commoninterface.sbr"
	-@erase "$(INTDIR)\confCnsCtrlLogic.obj"
	-@erase "$(INTDIR)\confCnsCtrlLogic.sbr"
	-@erase "$(INTDIR)\confCnsLstLogic.obj"
	-@erase "$(INTDIR)\confCnsLstLogic.sbr"
	-@erase "$(INTDIR)\confCtrlLogic.obj"
	-@erase "$(INTDIR)\confCtrlLogic.sbr"
	-@erase "$(INTDIR)\confInfoLogic.obj"
	-@erase "$(INTDIR)\confInfoLogic.sbr"
	-@erase "$(INTDIR)\ConftempEdtLogic.obj"
	-@erase "$(INTDIR)\ConftempEdtLogic.sbr"
	-@erase "$(INTDIR)\ConftempEdtSubEvent.obj"
	-@erase "$(INTDIR)\ConftempEdtSubEvent.sbr"
	-@erase "$(INTDIR)\conftempLstLogic.obj"
	-@erase "$(INTDIR)\conftempLstLogic.sbr"
	-@erase "$(INTDIR)\ctrlFactory.obj"
	-@erase "$(INTDIR)\ctrlFactory.sbr"
	-@erase "$(INTDIR)\errCodeManage.obj"
	-@erase "$(INTDIR)\errCodeManage.sbr"
	-@erase "$(INTDIR)\handleErr.obj"
	-@erase "$(INTDIR)\handleErr.sbr"
	-@erase "$(INTDIR)\lockScreenLogic.obj"
	-@erase "$(INTDIR)\lockScreenLogic.sbr"
	-@erase "$(INTDIR)\logicManage.obj"
	-@erase "$(INTDIR)\logicManage.sbr"
	-@erase "$(INTDIR)\loginLogic.obj"
	-@erase "$(INTDIR)\loginLogic.sbr"
	-@erase "$(INTDIR)\mainFrameLogic.obj"
	-@erase "$(INTDIR)\mainFrameLogic.sbr"
	-@erase "$(INTDIR)\msgBoxLogic.obj"
	-@erase "$(INTDIR)\msgBoxLogic.sbr"
	-@erase "$(INTDIR)\msgdispatch.obj"
	-@erase "$(INTDIR)\msgdispatch.sbr"
	-@erase "$(INTDIR)\pollLstManage.obj"
	-@erase "$(INTDIR)\pollLstManage.sbr"
	-@erase "$(INTDIR)\popmsgdlg.obj"
	-@erase "$(INTDIR)\popmsgdlg.sbr"
	-@erase "$(INTDIR)\simulateCnsLogic.obj"
	-@erase "$(INTDIR)\simulateCnsLogic.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\sysTime.obj"
	-@erase "$(INTDIR)\sysTime.sbr"
	-@erase "$(INTDIR)\testcnsdlg.obj"
	-@erase "$(INTDIR)\testcnsdlg.sbr"
	-@erase "$(INTDIR)\testdlg.obj"
	-@erase "$(INTDIR)\testdlg.sbr"
	-@erase "$(INTDIR)\testumsdlg.obj"
	-@erase "$(INTDIR)\testumsdlg.sbr"
	-@erase "$(INTDIR)\toolMenuLogic.obj"
	-@erase "$(INTDIR)\toolMenuLogic.sbr"
	-@erase "$(INTDIR)\TouchListHelp.obj"
	-@erase "$(INTDIR)\TouchListHelp.sbr"
	-@erase "$(INTDIR)\TouchListProperty.obj"
	-@erase "$(INTDIR)\TouchListProperty.sbr"
	-@erase "$(INTDIR)\UiFactroyLog.obj"
	-@erase "$(INTDIR)\UiFactroyLog.sbr"
	-@erase "$(INTDIR)\uiManage.obj"
	-@erase "$(INTDIR)\uiManage.sbr"
	-@erase "$(INTDIR)\umcconf.obj"
	-@erase "$(INTDIR)\umcconf.sbr"
	-@erase "$(INTDIR)\umcconfig.obj"
	-@erase "$(INTDIR)\umcconfig.sbr"
	-@erase "$(INTDIR)\umcconftemplate.obj"
	-@erase "$(INTDIR)\umcconftemplate.sbr"
	-@erase "$(INTDIR)\umctvw.obj"
	-@erase "$(INTDIR)\umctvw.sbr"
	-@erase "$(INTDIR)\umcuser.obj"
	-@erase "$(INTDIR)\umcuser.sbr"
	-@erase "$(INTDIR)\valueSet.obj"
	-@erase "$(INTDIR)\valueSet.sbr"
	-@erase "$(INTDIR)\valueStorage.obj"
	-@erase "$(INTDIR)\valueStorage.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\wndLogicBase.obj"
	-@erase "$(INTDIR)\wndLogicBase.sbr"
	-@erase "$(OUTDIR)\cms.bsc"
	-@erase "$(OUTDIR)\cms.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GX /O2 /I ".\\" /I "..\include\\" /I "..\..\common\include" /I "..\..\..\10-common\include\nms1" /I "..\..\..\10-common\include\platform" /I "..\..\..\10-common\include\system1" /I "..\..\..\10-common\include\snmp" /I "..\..\..\10-common\include\protocol" /I "..\..\..\10-common\include\snmp\snmp_pp" /I "..\..\..\10-common\include\tp" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\cms.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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

MTL=midl.exe
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC=rc.exe
RSC_PROJ=/l 0x804 /fo"$(INTDIR)\cms.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\cms.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\addrbooklogic.sbr" \
	"$(INTDIR)\addreditlogic.sbr" \
	"$(INTDIR)\audmixLogic.sbr" \
	"$(INTDIR)\confCnsLstLogic.sbr" \
	"$(INTDIR)\confCtrlLogic.sbr" \
	"$(INTDIR)\confInfoLogic.sbr" \
	"$(INTDIR)\ConftempEdtLogic.sbr" \
	"$(INTDIR)\ConftempEdtSubEvent.sbr" \
	"$(INTDIR)\conftempLstLogic.sbr" \
	"$(INTDIR)\lockScreenLogic.sbr" \
	"$(INTDIR)\logicManage.sbr" \
	"$(INTDIR)\loginLogic.sbr" \
	"$(INTDIR)\mainFrameLogic.sbr" \
	"$(INTDIR)\msgBoxLogic.sbr" \
	"$(INTDIR)\simulateCnsLogic.sbr" \
	"$(INTDIR)\toolMenuLogic.sbr" \
	"$(INTDIR)\wndLogicBase.sbr" \
	"$(INTDIR)\cncaddrbook.sbr" \
	"$(INTDIR)\cncconfig.sbr" \
	"$(INTDIR)\commoninterface.sbr" \
	"$(INTDIR)\errCodeManage.sbr" \
	"$(INTDIR)\handleErr.sbr" \
	"$(INTDIR)\msgdispatch.sbr" \
	"$(INTDIR)\sysTime.sbr" \
	"$(INTDIR)\umcconf.sbr" \
	"$(INTDIR)\umcconfig.sbr" \
	"$(INTDIR)\umcconftemplate.sbr" \
	"$(INTDIR)\umctvw.sbr" \
	"$(INTDIR)\umcuser.sbr" \
	"$(INTDIR)\valueSet.sbr" \
	"$(INTDIR)\AddrList.sbr" \
	"$(INTDIR)\cms.sbr" \
	"$(INTDIR)\ctrlFactory.sbr" \
	"$(INTDIR)\popmsgdlg.sbr" \
	"$(INTDIR)\TouchListHelp.sbr" \
	"$(INTDIR)\TouchListProperty.sbr" \
	"$(INTDIR)\UiFactroyLog.sbr" \
	"$(INTDIR)\uiManage.sbr" \
	"$(INTDIR)\cmsDlg.sbr" \
	"$(INTDIR)\pollLstManage.sbr" \
	"$(INTDIR)\StdAfx.sbr" \
	"$(INTDIR)\testcnsdlg.sbr" \
	"$(INTDIR)\testdlg.sbr" \
	"$(INTDIR)\testumsdlg.sbr" \
	"$(INTDIR)\valueStorage.sbr" \
	"$(INTDIR)\confCnsCtrlLogic.sbr"

"$(OUTDIR)\cms.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\cms.pdb" /machine:I386 /out:"$(OUTDIR)\cms.exe" /libpath:"..\..\..\10-common\lib\release\win32" /libpath:"..\..\common\include\dxsdk\LIB" 
LINK32_OBJS= \
	"$(INTDIR)\addrbooklogic.obj" \
	"$(INTDIR)\addreditlogic.obj" \
	"$(INTDIR)\audmixLogic.obj" \
	"$(INTDIR)\confCnsLstLogic.obj" \
	"$(INTDIR)\confCtrlLogic.obj" \
	"$(INTDIR)\confInfoLogic.obj" \
	"$(INTDIR)\ConftempEdtLogic.obj" \
	"$(INTDIR)\ConftempEdtSubEvent.obj" \
	"$(INTDIR)\conftempLstLogic.obj" \
	"$(INTDIR)\lockScreenLogic.obj" \
	"$(INTDIR)\logicManage.obj" \
	"$(INTDIR)\loginLogic.obj" \
	"$(INTDIR)\mainFrameLogic.obj" \
	"$(INTDIR)\msgBoxLogic.obj" \
	"$(INTDIR)\simulateCnsLogic.obj" \
	"$(INTDIR)\toolMenuLogic.obj" \
	"$(INTDIR)\wndLogicBase.obj" \
	"$(INTDIR)\cncaddrbook.obj" \
	"$(INTDIR)\cncconfig.obj" \
	"$(INTDIR)\commoninterface.obj" \
	"$(INTDIR)\errCodeManage.obj" \
	"$(INTDIR)\handleErr.obj" \
	"$(INTDIR)\msgdispatch.obj" \
	"$(INTDIR)\sysTime.obj" \
	"$(INTDIR)\umcconf.obj" \
	"$(INTDIR)\umcconfig.obj" \
	"$(INTDIR)\umcconftemplate.obj" \
	"$(INTDIR)\umctvw.obj" \
	"$(INTDIR)\umcuser.obj" \
	"$(INTDIR)\valueSet.obj" \
	"$(INTDIR)\AddrList.obj" \
	"$(INTDIR)\cms.obj" \
	"$(INTDIR)\ctrlFactory.obj" \
	"$(INTDIR)\popmsgdlg.obj" \
	"$(INTDIR)\TouchListHelp.obj" \
	"$(INTDIR)\TouchListProperty.obj" \
	"$(INTDIR)\UiFactroyLog.obj" \
	"$(INTDIR)\uiManage.obj" \
	"$(INTDIR)\cmsDlg.obj" \
	"$(INTDIR)\pollLstManage.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\testcnsdlg.obj" \
	"$(INTDIR)\testdlg.obj" \
	"$(INTDIR)\testumsdlg.obj" \
	"$(INTDIR)\valueStorage.obj" \
	"$(INTDIR)\cms.res" \
	"$(INTDIR)\confCnsCtrlLogic.obj" \
	"..\..\..\10-common\lib\release\win32\cnclib.lib" \
	"..\..\cmslib\umclib\prj_win32\Release\umclib.lib" \
	"..\..\..\10-common\lib\release\win32\uifactory.lib"

"$(OUTDIR)\cms.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "cms - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\cms.exe" "$(OUTDIR)\cms.bsc"

!ELSE 

ALL : "UIFactory - Win32 Debug" "umclib - Win32 Debug" "cncLib - Win32 Debug" "$(OUTDIR)\cms.exe" "$(OUTDIR)\cms.bsc"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"cncLib - Win32 DebugCLEAN" "umclib - Win32 DebugCLEAN" "UIFactory - Win32 DebugCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\addrbooklogic.obj"
	-@erase "$(INTDIR)\addrbooklogic.sbr"
	-@erase "$(INTDIR)\addreditlogic.obj"
	-@erase "$(INTDIR)\addreditlogic.sbr"
	-@erase "$(INTDIR)\AddrList.obj"
	-@erase "$(INTDIR)\AddrList.sbr"
	-@erase "$(INTDIR)\audmixLogic.obj"
	-@erase "$(INTDIR)\audmixLogic.sbr"
	-@erase "$(INTDIR)\cms.obj"
	-@erase "$(INTDIR)\cms.pch"
	-@erase "$(INTDIR)\cms.res"
	-@erase "$(INTDIR)\cms.sbr"
	-@erase "$(INTDIR)\cmsDlg.obj"
	-@erase "$(INTDIR)\cmsDlg.sbr"
	-@erase "$(INTDIR)\cncaddrbook.obj"
	-@erase "$(INTDIR)\cncaddrbook.sbr"
	-@erase "$(INTDIR)\cncconfig.obj"
	-@erase "$(INTDIR)\cncconfig.sbr"
	-@erase "$(INTDIR)\commoninterface.obj"
	-@erase "$(INTDIR)\commoninterface.sbr"
	-@erase "$(INTDIR)\confCnsCtrlLogic.obj"
	-@erase "$(INTDIR)\confCnsCtrlLogic.sbr"
	-@erase "$(INTDIR)\confCnsLstLogic.obj"
	-@erase "$(INTDIR)\confCnsLstLogic.sbr"
	-@erase "$(INTDIR)\confCtrlLogic.obj"
	-@erase "$(INTDIR)\confCtrlLogic.sbr"
	-@erase "$(INTDIR)\confInfoLogic.obj"
	-@erase "$(INTDIR)\confInfoLogic.sbr"
	-@erase "$(INTDIR)\ConftempEdtLogic.obj"
	-@erase "$(INTDIR)\ConftempEdtLogic.sbr"
	-@erase "$(INTDIR)\ConftempEdtSubEvent.obj"
	-@erase "$(INTDIR)\ConftempEdtSubEvent.sbr"
	-@erase "$(INTDIR)\conftempLstLogic.obj"
	-@erase "$(INTDIR)\conftempLstLogic.sbr"
	-@erase "$(INTDIR)\ctrlFactory.obj"
	-@erase "$(INTDIR)\ctrlFactory.sbr"
	-@erase "$(INTDIR)\errCodeManage.obj"
	-@erase "$(INTDIR)\errCodeManage.sbr"
	-@erase "$(INTDIR)\handleErr.obj"
	-@erase "$(INTDIR)\handleErr.sbr"
	-@erase "$(INTDIR)\lockScreenLogic.obj"
	-@erase "$(INTDIR)\lockScreenLogic.sbr"
	-@erase "$(INTDIR)\logicManage.obj"
	-@erase "$(INTDIR)\logicManage.sbr"
	-@erase "$(INTDIR)\loginLogic.obj"
	-@erase "$(INTDIR)\loginLogic.sbr"
	-@erase "$(INTDIR)\mainFrameLogic.obj"
	-@erase "$(INTDIR)\mainFrameLogic.sbr"
	-@erase "$(INTDIR)\msgBoxLogic.obj"
	-@erase "$(INTDIR)\msgBoxLogic.sbr"
	-@erase "$(INTDIR)\msgdispatch.obj"
	-@erase "$(INTDIR)\msgdispatch.sbr"
	-@erase "$(INTDIR)\pollLstManage.obj"
	-@erase "$(INTDIR)\pollLstManage.sbr"
	-@erase "$(INTDIR)\popmsgdlg.obj"
	-@erase "$(INTDIR)\popmsgdlg.sbr"
	-@erase "$(INTDIR)\simulateCnsLogic.obj"
	-@erase "$(INTDIR)\simulateCnsLogic.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\sysTime.obj"
	-@erase "$(INTDIR)\sysTime.sbr"
	-@erase "$(INTDIR)\testcnsdlg.obj"
	-@erase "$(INTDIR)\testcnsdlg.sbr"
	-@erase "$(INTDIR)\testdlg.obj"
	-@erase "$(INTDIR)\testdlg.sbr"
	-@erase "$(INTDIR)\testumsdlg.obj"
	-@erase "$(INTDIR)\testumsdlg.sbr"
	-@erase "$(INTDIR)\toolMenuLogic.obj"
	-@erase "$(INTDIR)\toolMenuLogic.sbr"
	-@erase "$(INTDIR)\TouchListHelp.obj"
	-@erase "$(INTDIR)\TouchListHelp.sbr"
	-@erase "$(INTDIR)\TouchListProperty.obj"
	-@erase "$(INTDIR)\TouchListProperty.sbr"
	-@erase "$(INTDIR)\UiFactroyLog.obj"
	-@erase "$(INTDIR)\UiFactroyLog.sbr"
	-@erase "$(INTDIR)\uiManage.obj"
	-@erase "$(INTDIR)\uiManage.sbr"
	-@erase "$(INTDIR)\umcconf.obj"
	-@erase "$(INTDIR)\umcconf.sbr"
	-@erase "$(INTDIR)\umcconfig.obj"
	-@erase "$(INTDIR)\umcconfig.sbr"
	-@erase "$(INTDIR)\umcconftemplate.obj"
	-@erase "$(INTDIR)\umcconftemplate.sbr"
	-@erase "$(INTDIR)\umctvw.obj"
	-@erase "$(INTDIR)\umctvw.sbr"
	-@erase "$(INTDIR)\umcuser.obj"
	-@erase "$(INTDIR)\umcuser.sbr"
	-@erase "$(INTDIR)\valueSet.obj"
	-@erase "$(INTDIR)\valueSet.sbr"
	-@erase "$(INTDIR)\valueStorage.obj"
	-@erase "$(INTDIR)\valueStorage.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\wndLogicBase.obj"
	-@erase "$(INTDIR)\wndLogicBase.sbr"
	-@erase "$(OUTDIR)\cms.bsc"
	-@erase "$(OUTDIR)\cms.exe"
	-@erase "$(OUTDIR)\cms.ilk"
	-@erase "$(OUTDIR)\cms.map"
	-@erase "$(OUTDIR)\cms.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /GR /GX /ZI /Od /I ".\\" /I "..\include" /I "..\..\common\include" /I "..\..\..\10-common\include\nms1" /I "..\..\..\10-common\include\system1" /I "..\..\..\10-common\include\protocol" /I "..\..\..\10-common\include\platform" /I "..\..\common\include\platform sdk\include" /I "..\..\..\10-common\include\tp" /I "..\..\UIFactory\include" /I "..\..\uiexlib\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\cms.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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

MTL=midl.exe
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC=rc.exe
RSC_PROJ=/l 0x804 /fo"$(INTDIR)\cms.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\cms.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\addrbooklogic.sbr" \
	"$(INTDIR)\addreditlogic.sbr" \
	"$(INTDIR)\audmixLogic.sbr" \
	"$(INTDIR)\confCnsLstLogic.sbr" \
	"$(INTDIR)\confCtrlLogic.sbr" \
	"$(INTDIR)\confInfoLogic.sbr" \
	"$(INTDIR)\ConftempEdtLogic.sbr" \
	"$(INTDIR)\ConftempEdtSubEvent.sbr" \
	"$(INTDIR)\conftempLstLogic.sbr" \
	"$(INTDIR)\lockScreenLogic.sbr" \
	"$(INTDIR)\logicManage.sbr" \
	"$(INTDIR)\loginLogic.sbr" \
	"$(INTDIR)\mainFrameLogic.sbr" \
	"$(INTDIR)\msgBoxLogic.sbr" \
	"$(INTDIR)\simulateCnsLogic.sbr" \
	"$(INTDIR)\toolMenuLogic.sbr" \
	"$(INTDIR)\wndLogicBase.sbr" \
	"$(INTDIR)\cncaddrbook.sbr" \
	"$(INTDIR)\cncconfig.sbr" \
	"$(INTDIR)\commoninterface.sbr" \
	"$(INTDIR)\errCodeManage.sbr" \
	"$(INTDIR)\handleErr.sbr" \
	"$(INTDIR)\msgdispatch.sbr" \
	"$(INTDIR)\sysTime.sbr" \
	"$(INTDIR)\umcconf.sbr" \
	"$(INTDIR)\umcconfig.sbr" \
	"$(INTDIR)\umcconftemplate.sbr" \
	"$(INTDIR)\umctvw.sbr" \
	"$(INTDIR)\umcuser.sbr" \
	"$(INTDIR)\valueSet.sbr" \
	"$(INTDIR)\AddrList.sbr" \
	"$(INTDIR)\cms.sbr" \
	"$(INTDIR)\ctrlFactory.sbr" \
	"$(INTDIR)\popmsgdlg.sbr" \
	"$(INTDIR)\TouchListHelp.sbr" \
	"$(INTDIR)\TouchListProperty.sbr" \
	"$(INTDIR)\UiFactroyLog.sbr" \
	"$(INTDIR)\uiManage.sbr" \
	"$(INTDIR)\cmsDlg.sbr" \
	"$(INTDIR)\pollLstManage.sbr" \
	"$(INTDIR)\StdAfx.sbr" \
	"$(INTDIR)\testcnsdlg.sbr" \
	"$(INTDIR)\testdlg.sbr" \
	"$(INTDIR)\testumsdlg.sbr" \
	"$(INTDIR)\valueStorage.sbr" \
	"$(INTDIR)\confCnsCtrlLogic.sbr"

"$(OUTDIR)\cms.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\cms.pdb" /map:"$(INTDIR)\cms.map" /debug /machine:I386 /nodefaultlib:"nafxcwd.lib" /nodefaultlib:"libcd.lib" /nodefaultlib:"libc.lib" /nodefaultlib:"libcmt.lib" /nodefaultlib:"msvcrt.lib" /nodefaultlib:"Imm32.lib" /nodefaultlib:"libcmtd.lib" /out:"$(OUTDIR)\cms.exe" /pdbtype:sept /libpath:"..\..\..\10-common\lib\debug\win32" /libpath:"..\..\UIFactory\expat\lib\debug" /libpath:"..\..\common\include\platform sdk\lib" 
LINK32_OBJS= \
	"$(INTDIR)\addrbooklogic.obj" \
	"$(INTDIR)\addreditlogic.obj" \
	"$(INTDIR)\audmixLogic.obj" \
	"$(INTDIR)\confCnsLstLogic.obj" \
	"$(INTDIR)\confCtrlLogic.obj" \
	"$(INTDIR)\confInfoLogic.obj" \
	"$(INTDIR)\ConftempEdtLogic.obj" \
	"$(INTDIR)\ConftempEdtSubEvent.obj" \
	"$(INTDIR)\conftempLstLogic.obj" \
	"$(INTDIR)\lockScreenLogic.obj" \
	"$(INTDIR)\logicManage.obj" \
	"$(INTDIR)\loginLogic.obj" \
	"$(INTDIR)\mainFrameLogic.obj" \
	"$(INTDIR)\msgBoxLogic.obj" \
	"$(INTDIR)\simulateCnsLogic.obj" \
	"$(INTDIR)\toolMenuLogic.obj" \
	"$(INTDIR)\wndLogicBase.obj" \
	"$(INTDIR)\cncaddrbook.obj" \
	"$(INTDIR)\cncconfig.obj" \
	"$(INTDIR)\commoninterface.obj" \
	"$(INTDIR)\errCodeManage.obj" \
	"$(INTDIR)\handleErr.obj" \
	"$(INTDIR)\msgdispatch.obj" \
	"$(INTDIR)\sysTime.obj" \
	"$(INTDIR)\umcconf.obj" \
	"$(INTDIR)\umcconfig.obj" \
	"$(INTDIR)\umcconftemplate.obj" \
	"$(INTDIR)\umctvw.obj" \
	"$(INTDIR)\umcuser.obj" \
	"$(INTDIR)\valueSet.obj" \
	"$(INTDIR)\AddrList.obj" \
	"$(INTDIR)\cms.obj" \
	"$(INTDIR)\ctrlFactory.obj" \
	"$(INTDIR)\popmsgdlg.obj" \
	"$(INTDIR)\TouchListHelp.obj" \
	"$(INTDIR)\TouchListProperty.obj" \
	"$(INTDIR)\UiFactroyLog.obj" \
	"$(INTDIR)\uiManage.obj" \
	"$(INTDIR)\cmsDlg.obj" \
	"$(INTDIR)\pollLstManage.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\testcnsdlg.obj" \
	"$(INTDIR)\testdlg.obj" \
	"$(INTDIR)\testumsdlg.obj" \
	"$(INTDIR)\valueStorage.obj" \
	"$(INTDIR)\cms.res" \
	"$(INTDIR)\confCnsCtrlLogic.obj" \
	"..\..\..\10-common\lib\debug\win32\cnclib.lib" \
	"..\..\..\10-common\lib\debug\win32\umclib.lib" \
	"..\..\..\10-common\lib\debug\win32\uifactory.lib"

"$(OUTDIR)\cms.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("cms.dep")
!INCLUDE "cms.dep"
!ELSE 
!MESSAGE Warning: cannot find "cms.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "cms - Win32 Release" || "$(CFG)" == "cms - Win32 Debug"
SOURCE=..\source\addrbooklogic.cpp

"$(INTDIR)\addrbooklogic.obj"	"$(INTDIR)\addrbooklogic.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\cms.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\source\addreditlogic.cpp

"$(INTDIR)\addreditlogic.obj"	"$(INTDIR)\addreditlogic.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\cms.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\source\audmixLogic.cpp

"$(INTDIR)\audmixLogic.obj"	"$(INTDIR)\audmixLogic.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\cms.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\source\confCnsCtrlLogic.cpp

"$(INTDIR)\confCnsCtrlLogic.obj"	"$(INTDIR)\confCnsCtrlLogic.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\cms.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\source\confCnsLstLogic.cpp

"$(INTDIR)\confCnsLstLogic.obj"	"$(INTDIR)\confCnsLstLogic.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\cms.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\source\confCtrlLogic.cpp

"$(INTDIR)\confCtrlLogic.obj"	"$(INTDIR)\confCtrlLogic.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\cms.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\source\confInfoLogic.cpp

"$(INTDIR)\confInfoLogic.obj"	"$(INTDIR)\confInfoLogic.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\cms.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\source\ConftempEdtLogic.cpp

"$(INTDIR)\ConftempEdtLogic.obj"	"$(INTDIR)\ConftempEdtLogic.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\cms.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\source\ConftempEdtSubEvent.cpp

"$(INTDIR)\ConftempEdtSubEvent.obj"	"$(INTDIR)\ConftempEdtSubEvent.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\cms.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\source\conftempLstLogic.cpp

"$(INTDIR)\conftempLstLogic.obj"	"$(INTDIR)\conftempLstLogic.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\cms.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\source\lockScreenLogic.cpp

"$(INTDIR)\lockScreenLogic.obj"	"$(INTDIR)\lockScreenLogic.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\cms.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\source\logicManage.cpp

"$(INTDIR)\logicManage.obj"	"$(INTDIR)\logicManage.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\cms.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\source\loginLogic.cpp

"$(INTDIR)\loginLogic.obj"	"$(INTDIR)\loginLogic.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\cms.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\source\mainFrameLogic.cpp

"$(INTDIR)\mainFrameLogic.obj"	"$(INTDIR)\mainFrameLogic.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\cms.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\source\msgBoxLogic.cpp

"$(INTDIR)\msgBoxLogic.obj"	"$(INTDIR)\msgBoxLogic.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\cms.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\source\simulateCnsLogic.cpp

"$(INTDIR)\simulateCnsLogic.obj"	"$(INTDIR)\simulateCnsLogic.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\cms.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\source\toolMenuLogic.cpp

"$(INTDIR)\toolMenuLogic.obj"	"$(INTDIR)\toolMenuLogic.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\cms.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\source\wndLogicBase.cpp

"$(INTDIR)\wndLogicBase.obj"	"$(INTDIR)\wndLogicBase.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\cms.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\source\cncaddrbook.cpp

"$(INTDIR)\cncaddrbook.obj"	"$(INTDIR)\cncaddrbook.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\cms.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\source\cncconfig.cpp

"$(INTDIR)\cncconfig.obj"	"$(INTDIR)\cncconfig.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\cms.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\source\commoninterface.cpp

"$(INTDIR)\commoninterface.obj"	"$(INTDIR)\commoninterface.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\cms.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\source\errCodeManage.cpp

"$(INTDIR)\errCodeManage.obj"	"$(INTDIR)\errCodeManage.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\cms.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\source\handleErr.cpp

"$(INTDIR)\handleErr.obj"	"$(INTDIR)\handleErr.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\cms.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\source\msgdispatch.cpp

"$(INTDIR)\msgdispatch.obj"	"$(INTDIR)\msgdispatch.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\cms.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\source\sysTime.cpp

"$(INTDIR)\sysTime.obj"	"$(INTDIR)\sysTime.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\cms.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\source\umcconf.cpp

"$(INTDIR)\umcconf.obj"	"$(INTDIR)\umcconf.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\cms.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\source\umcconfig.cpp

"$(INTDIR)\umcconfig.obj"	"$(INTDIR)\umcconfig.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\cms.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\source\umcconftemplate.cpp

"$(INTDIR)\umcconftemplate.obj"	"$(INTDIR)\umcconftemplate.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\cms.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\source\umctvw.cpp

"$(INTDIR)\umctvw.obj"	"$(INTDIR)\umctvw.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\cms.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\source\umcuser.cpp

"$(INTDIR)\umcuser.obj"	"$(INTDIR)\umcuser.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\cms.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\source\valueSet.cpp

"$(INTDIR)\valueSet.obj"	"$(INTDIR)\valueSet.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\cms.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\source\AddrList.cpp

"$(INTDIR)\AddrList.obj"	"$(INTDIR)\AddrList.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\cms.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\source\cms.cpp

"$(INTDIR)\cms.obj"	"$(INTDIR)\cms.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\cms.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\source\ctrlFactory.cpp

"$(INTDIR)\ctrlFactory.obj"	"$(INTDIR)\ctrlFactory.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\cms.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\source\popmsgdlg.cpp

"$(INTDIR)\popmsgdlg.obj"	"$(INTDIR)\popmsgdlg.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\cms.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\source\TouchListHelp.cpp

"$(INTDIR)\TouchListHelp.obj"	"$(INTDIR)\TouchListHelp.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\cms.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\source\TouchListProperty.cpp

"$(INTDIR)\TouchListProperty.obj"	"$(INTDIR)\TouchListProperty.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\cms.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\source\UiFactroyLog.cpp

"$(INTDIR)\UiFactroyLog.obj"	"$(INTDIR)\UiFactroyLog.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\cms.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\source\uiManage.cpp

"$(INTDIR)\uiManage.obj"	"$(INTDIR)\uiManage.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\cms.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\cms.rc

"$(INTDIR)\cms.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=..\source\cmsDlg.cpp

"$(INTDIR)\cmsDlg.obj"	"$(INTDIR)\cmsDlg.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\cms.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\source\pollLstManage.cpp

"$(INTDIR)\pollLstManage.obj"	"$(INTDIR)\pollLstManage.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\cms.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "cms - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /I ".\\" /I "..\include\\" /I "..\..\common\include" /I "..\..\..\10-common\include\nms1" /I "..\..\..\10-common\include\platform" /I "..\..\..\10-common\include\system1" /I "..\..\..\10-common\include\snmp" /I "..\..\..\10-common\include\protocol" /I "..\..\..\10-common\include\snmp\snmp_pp" /I "..\..\..\10-common\include\tp" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\cms.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\cms.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "cms - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GR /GX /ZI /Od /I ".\\" /I "..\include" /I "..\..\common\include" /I "..\..\..\10-common\include\nms1" /I "..\..\..\10-common\include\system1" /I "..\..\..\10-common\include\protocol" /I "..\..\..\10-common\include\platform" /I "..\..\common\include\platform sdk\include" /I "..\..\..\10-common\include\tp" /I "..\..\UIFactory\include" /I "..\..\uiexlib\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\cms.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\cms.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\source\testcnsdlg.cpp

!IF  "$(CFG)" == "cms - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /I ".\\" /I "..\include\\" /I "..\..\common\include" /I "..\..\..\10-common\include\nms1" /I "..\..\..\10-common\include\platform" /I "..\..\..\10-common\include\system1" /I "..\..\..\10-common\include\snmp" /I "..\..\..\10-common\include\protocol" /I "..\..\..\10-common\include\snmp\snmp_pp" /I "..\..\..\10-common\include\tp" /I "..\prj_win32" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\cms.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\testcnsdlg.obj"	"$(INTDIR)\testcnsdlg.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\cms.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "cms - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GR /GX /ZI /Od /I ".\\" /I "..\include" /I "..\..\common\include" /I "..\..\..\10-common\include\nms1" /I "..\..\..\10-common\include\system1" /I "..\..\..\10-common\include\protocol" /I "..\..\..\10-common\include\platform" /I "..\..\common\include\platform sdk\include" /I "..\..\..\10-common\include\tp" /I "..\..\UIFactory\include" /I "..\..\uiexlib\include" /I "..\prj_win32" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\cms.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\testcnsdlg.obj"	"$(INTDIR)\testcnsdlg.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\cms.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\source\testdlg.cpp

!IF  "$(CFG)" == "cms - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /I ".\\" /I "..\include\\" /I "..\..\common\include" /I "..\..\..\10-common\include\nms1" /I "..\..\..\10-common\include\platform" /I "..\..\..\10-common\include\system1" /I "..\..\..\10-common\include\snmp" /I "..\..\..\10-common\include\protocol" /I "..\..\..\10-common\include\snmp\snmp_pp" /I "..\..\..\10-common\include\tp" /I "..\prj_win32" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\cms.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\testdlg.obj"	"$(INTDIR)\testdlg.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\cms.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "cms - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GR /GX /ZI /Od /I ".\\" /I "..\include" /I "..\..\common\include" /I "..\..\..\10-common\include\nms1" /I "..\..\..\10-common\include\system1" /I "..\..\..\10-common\include\protocol" /I "..\..\..\10-common\include\platform" /I "..\..\common\include\platform sdk\include" /I "..\..\..\10-common\include\tp" /I "..\..\UIFactory\include" /I "..\..\uiexlib\include" /I "..\prj_win32" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\cms.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\testdlg.obj"	"$(INTDIR)\testdlg.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\cms.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\source\testumsdlg.cpp

!IF  "$(CFG)" == "cms - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /I ".\\" /I "..\include\\" /I "..\..\common\include" /I "..\..\..\10-common\include\nms1" /I "..\..\..\10-common\include\platform" /I "..\..\..\10-common\include\system1" /I "..\..\..\10-common\include\snmp" /I "..\..\..\10-common\include\protocol" /I "..\..\..\10-common\include\snmp\snmp_pp" /I "..\..\..\10-common\include\tp" /I "..\prj_win32" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\cms.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\testumsdlg.obj"	"$(INTDIR)\testumsdlg.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\cms.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "cms - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GR /GX /ZI /Od /I ".\\" /I "..\include" /I "..\..\common\include" /I "..\..\..\10-common\include\nms1" /I "..\..\..\10-common\include\system1" /I "..\..\..\10-common\include\protocol" /I "..\..\..\10-common\include\platform" /I "..\..\common\include\platform sdk\include" /I "..\..\..\10-common\include\tp" /I "..\..\UIFactory\include" /I "..\..\uiexlib\include" /I "..\prj_win32" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\cms.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\testumsdlg.obj"	"$(INTDIR)\testumsdlg.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\cms.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\source\valueStorage.cpp

"$(INTDIR)\valueStorage.obj"	"$(INTDIR)\valueStorage.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\cms.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!IF  "$(CFG)" == "cms - Win32 Release"

"cncLib - Win32 Release" : 
   cd "\ccroot\20110212_HD2_V1R1_TP_2\Professional_VOB\70-neptune\cmslib\cnclib\prj_win32"
   $(MAKE) /$(MAKEFLAGS) /F ".\cncLib.mak" CFG="cncLib - Win32 Release" 
   cd "..\..\..\cms\prj_win32"

"cncLib - Win32 ReleaseCLEAN" : 
   cd "\ccroot\20110212_HD2_V1R1_TP_2\Professional_VOB\70-neptune\cmslib\cnclib\prj_win32"
   $(MAKE) /$(MAKEFLAGS) /F ".\cncLib.mak" CFG="cncLib - Win32 Release" RECURSE=1 CLEAN 
   cd "..\..\..\cms\prj_win32"

!ELSEIF  "$(CFG)" == "cms - Win32 Debug"

"cncLib - Win32 Debug" : 
   cd "\ccroot\20110212_HD2_V1R1_TP_2\Professional_VOB\70-neptune\cmslib\cnclib\prj_win32"
   $(MAKE) /$(MAKEFLAGS) /F ".\cncLib.mak" CFG="cncLib - Win32 Debug" 
   cd "..\..\..\cms\prj_win32"

"cncLib - Win32 DebugCLEAN" : 
   cd "\ccroot\20110212_HD2_V1R1_TP_2\Professional_VOB\70-neptune\cmslib\cnclib\prj_win32"
   $(MAKE) /$(MAKEFLAGS) /F ".\cncLib.mak" CFG="cncLib - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\..\..\cms\prj_win32"

!ENDIF 

!IF  "$(CFG)" == "cms - Win32 Release"

"umclib - Win32 Release" : 
   cd "\ccroot\20110212_HD2_V1R1_TP_2\Professional_VOB\70-neptune\cmslib\umclib\prj_win32"
   $(MAKE) /$(MAKEFLAGS) /F ".\umclib.mak" CFG="umclib - Win32 Release" 
   cd "..\..\..\cms\prj_win32"

"umclib - Win32 ReleaseCLEAN" : 
   cd "\ccroot\20110212_HD2_V1R1_TP_2\Professional_VOB\70-neptune\cmslib\umclib\prj_win32"
   $(MAKE) /$(MAKEFLAGS) /F ".\umclib.mak" CFG="umclib - Win32 Release" RECURSE=1 CLEAN 
   cd "..\..\..\cms\prj_win32"

!ELSEIF  "$(CFG)" == "cms - Win32 Debug"

"umclib - Win32 Debug" : 
   cd "\ccroot\20110212_HD2_V1R1_TP_2\Professional_VOB\70-neptune\cmslib\umclib\prj_win32"
   $(MAKE) /$(MAKEFLAGS) /F ".\umclib.mak" CFG="umclib - Win32 Debug" 
   cd "..\..\..\cms\prj_win32"

"umclib - Win32 DebugCLEAN" : 
   cd "\ccroot\20110212_HD2_V1R1_TP_2\Professional_VOB\70-neptune\cmslib\umclib\prj_win32"
   $(MAKE) /$(MAKEFLAGS) /F ".\umclib.mak" CFG="umclib - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\..\..\cms\prj_win32"

!ENDIF 

!IF  "$(CFG)" == "cms - Win32 Release"

"UIFactory - Win32 Release" : 
   cd "\ccroot\20110212_HD2_V1R1_TP_2\Professional_VOB\70-neptune\UIFactory\prj_win32"
   $(MAKE) /$(MAKEFLAGS) /F ".\UIFactory.mak" CFG="UIFactory - Win32 Release" 
   cd "..\..\cms\prj_win32"

"UIFactory - Win32 ReleaseCLEAN" : 
   cd "\ccroot\20110212_HD2_V1R1_TP_2\Professional_VOB\70-neptune\UIFactory\prj_win32"
   $(MAKE) /$(MAKEFLAGS) /F ".\UIFactory.mak" CFG="UIFactory - Win32 Release" RECURSE=1 CLEAN 
   cd "..\..\cms\prj_win32"

!ELSEIF  "$(CFG)" == "cms - Win32 Debug"

"UIFactory - Win32 Debug" : 
   cd "\ccroot\20110212_HD2_V1R1_TP_2\Professional_VOB\70-neptune\UIFactory\prj_win32"
   $(MAKE) /$(MAKEFLAGS) /F ".\UIFactory.mak" CFG="UIFactory - Win32 Debug" 
   cd "..\..\cms\prj_win32"

"UIFactory - Win32 DebugCLEAN" : 
   cd "\ccroot\20110212_HD2_V1R1_TP_2\Professional_VOB\70-neptune\UIFactory\prj_win32"
   $(MAKE) /$(MAKEFLAGS) /F ".\UIFactory.mak" CFG="UIFactory - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\..\cms\prj_win32"

!ENDIF 


!ENDIF 

