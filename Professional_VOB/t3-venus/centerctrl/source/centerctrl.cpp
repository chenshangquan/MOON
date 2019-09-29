// centerctrl.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "centerctrl.h"
#include "centerctrlDlg.h"
#include "LogicManage.h"

#include "exceptioncatch.h"

#define _NMS_COMMON_CPP_
#include "common.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


#define EXCEPTION_FILE_PATH _T("exception.log")

/////////////////////////////////////////////////////////////////////////////
// CCenterCtrlApp

BEGIN_MESSAGE_MAP(CCenterCtrlApp, CWinApp)
	//{{AFX_MSG_MAP(CCenterCtrlApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCenterCtrlApp construction

CCenterCtrlApp::CCenterCtrlApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CCenterCtrlApp object

CCenterCtrlApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CCenterCtrlApp initialization

BOOL CCenterCtrlApp::InitInstance()
{
    //ֻ����һ��
    if ( IsHasStart() )
    {   
        UINT uExitCode = 0;
        ExitProcess( uExitCode );
        return FALSE;
    }

	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

    //�쳣����
    CString strFullPath = GetModuleFullPath();
    strFullPath += EXCEPTION_FILE_PATH;
    CExceptionCatch::LogToFile( (LPSTR)(LPCSTR)strFullPath );
    CExceptionCatch::Start(); 

    //��ʼ��������Ϣ
    UIFACTORYMGR_PTR->InitUIFactory( "system.xml" );

    //��ʼ�����ڹ����߼���Ϣ
	LogicManagePtr->CreateLogic();

    //����cns session
	ComInterface->CreateSession();

    IWndTree* pTree = const_cast<IWndTree*>( UIFACTORYMGR_PTR->GetWindow( g_stcStrCenterCtrlDlg ) );
    if ( pTree == 0 )
    {
        return FALSE;
    }
    //UIFACTORYMGR_PTR->ShowWindow( g_stcStrCenterCtrlDlg );
    
    WndInfo* pInfo = pTree->GetItemData();
    m_pMainWnd = pInfo->pWnd;  
    m_pMainWnd->SendMessage( WM_REDRAW_UI ,0 ,0 ); 
      
    ::SetProp( m_pMainWnd->GetSafeHwnd(), AfxGetApp()->m_pszAppName, (HANDLE)1 );
    
    ::SetForegroundWindow( m_pMainWnd->GetSafeHwnd() );
    
    m_pMainWnd->RunModalLoop();
    
    return TRUE;

	CCenterCtrlDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}

int CCenterCtrlApp::ExitInstance() 
{
    // TODO: Add your specialized code here and/or call the base class
    CExceptionCatch::Free();
    
    ::RemoveProp( m_pMainWnd->GetSafeHwnd(), AfxGetApp()->m_pszAppName ); 
    
    return CWinApp::ExitInstance();
}

BOOL CCenterCtrlApp::PreTranslateMessage(MSG* pMsg) 
{ 	
    switch( pMsg->message )
    {
    case WM_KEYDOWN: //����ESC������ֹ�Ӵ�����ʧ 
        {  
            if ( pMsg->wParam == VK_ESCAPE )
            {
                return TRUE;
            }       
        }
        break;
    case WM_RBUTTONDOWN:  //�Ҽ���Ϣת��Ϊ�����Ϣ����ֹ������button�쳣
        pMsg->message = WM_LBUTTONDOWN;
        break;
    case WM_RBUTTONUP:
        pMsg->message = WM_LBUTTONUP;
        break;
    }

    MSG msgTemp;
    memcpy( &msgTemp, pMsg, sizeof(MSG));
    UIFACTORYMGR_PTR->HandleMsg( &msgTemp );
    
    return CWinApp::PreTranslateMessage(&msgTemp);
}


bool CCenterCtrlApp::IsHasStart()
{
    bool bHasStart = false;
    HWND hWnd =   GetWndByAppName( AfxGetApp()->m_pszAppName );
    
    if ( NULL != hWnd )
    {
        bHasStart = true;
        
        //   ����������С������ָ����С   
        if   (::IsIconic(hWnd)) 				
            ::ShowWindow(hWnd,SW_RESTORE);   
        
        HWND hdl = GetForegroundWindow();
        if (hWnd !=  hdl )
        {   					
            ::ShowWindow(hWnd,SW_RESTORE); 
            ::SetForegroundWindow(hWnd);
        }
    }
    
    return bHasStart;
}



////////////////////////////////////////////////////////////////////////////////
//��ӡ

API void help()
{
    PrtMsg( "\nprt: ��ӡ���м���Ϊ3���ϵ���Ϣ");
    PrtMsg( "\nstopprt: ֹͣ��ӡ������Ϣ");
}

API void prt()
{
    CPrintCtrl::GetPrintCtrl()->PrintAllMsg();
}


API void prtlevel( u8 byLevel )
{
    CPrintCtrl::GetPrintCtrl()->PrintMsgLevel( byLevel );
}

API void stopprt()
{
    CPrintCtrl::GetPrintCtrl()->StopPrint();
}

API void showver()
{   
    //��cncʹ����ͬ�汾��
    PrtMsg( "centerctrl version: %s  \n", GetCncBuildVersion() ); 
    PrtMsg( "compile time: %s %s", __DATE__, __TIME__ );
}