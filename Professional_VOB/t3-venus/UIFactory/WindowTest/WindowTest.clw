; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CWindowTestDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "WindowTest.h"

ClassCount=4
Class1=CWindowTestApp
Class2=CWindowTestDlg
Class3=CAboutDlg

ResourceCount=5
Resource1=IDD_DIALOG1
Resource2=IDR_MAINFRAME
Resource3=IDD_WINDOWTEST_DIALOG
Class4=CTestWnd
Resource4=IDD_DIALOG2
Resource5=IDD_ABOUTBOX

[CLS:CWindowTestApp]
Type=0
HeaderFile=WindowTest.h
ImplementationFile=WindowTest.cpp
Filter=N
BaseClass=CWinApp
VirtualFilter=AC
LastObject=CWindowTestApp

[CLS:CWindowTestDlg]
Type=0
HeaderFile=WindowTestDlg.h
ImplementationFile=WindowTestDlg.cpp
Filter=D
LastObject=CWindowTestDlg
BaseClass=CDialog
VirtualFilter=dWC

[CLS:CAboutDlg]
Type=0
HeaderFile=WindowTestDlg.h
ImplementationFile=WindowTestDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_WINDOWTEST_DIALOG]
Type=1
Class=CWindowTestDlg
ControlCount=3
Control1=IDC_EDIT1,edit,1350631552
Control2=IDC_BUTTON1,button,1342242816
Control3=IDC_LIST1,listbox,1352728835

[DLG:IDD_DIALOG1]
Type=1
Class=CTestWnd
ControlCount=0

[CLS:CTestWnd]
Type=0
HeaderFile=TestWnd.h
ImplementationFile=TestWnd.cpp
BaseClass=CDialog
Filter=D
LastObject=CTestWnd
VirtualFilter=dWC

[DLG:IDD_DIALOG2]
Type=1
Class=?
ControlCount=2
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816

