// cms.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "cms.h"
#include "cmsDlg.h" 
#include "MsgDispatch.h"
#include "uiManage.h"
#include "logicManage.h"

#include "outPrint.h"

#include "nmscommon.h" 

#include "exceptioncatch.h"

#define _NMS_COMMON_CPP_
#include "common.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCmsApp

BEGIN_MESSAGE_MAP(CCmsApp, CWinApp)
	//{{AFX_MSG_MAP(CCmsApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCmsApp construction

CCmsApp::CCmsApp():m_hk(0)
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CCmsApp object

CCmsApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CCmsApp initialization

// 
// 
//  //д�쳣
// #define EXCEPTION_FILE_PATH _T("exception.log")
// void WriteLog( struct _EXCEPTION_POINTERS* lpExceptionInfo )
// {
//     CString strFullPath = GetModuleFullPath();
//     strFullPath += EXCEPTION_FILE_PATH;
//     
//     LONG lResult = lpExceptionInfo -> ExceptionRecord ->ExceptionCode;
//     CString strErr;
//     
//     SYSTEMTIME sysTime;
//     GetLocalTime(&sysTime);
//     CString strTime = "";
//     
//     strTime.Format("\n%d/%d/%d %d:%d:%d ", 
//         sysTime.wYear, sysTime.wMonth, sysTime.wDay, 
//         sysTime.wHour, sysTime.wMinute, sysTime.wSecond );
//     
//     strErr.Format( "Unknown WIN32 exception:%d at address 0x%.8x \n",
//         lpExceptionInfo->ExceptionRecord->ExceptionCode,
//         lpExceptionInfo->ExceptionRecord->ExceptionAddress ); 
//     
//     strTime += strErr;
// 
//     CFile file;
//     if ( file.Open( strFullPath, CFile::modeCreate|CFile::modeWrite  ,NULL) )
//     {  
// 
//         file.SeekToEnd();  
//         file.Write( strTime, strTime.GetLength() );
//         file.Close();
//         
//     }
//     
// }
// 
//  
// //��    ��: �쳣���� 
// LPTOP_LEVEL_EXCEPTION_FILTER g_ExceptionFilter = NULL;
// LONG WINAPI MyExceptionFilter (struct _EXCEPTION_POINTERS* lpExceptionInfo)
// {
//     WriteLog( lpExceptionInfo );
//     if(g_ExceptionFilter)
//         return g_ExceptionFilter(lpExceptionInfo); 
//     return EXCEPTION_CONTINUE_SEARCH;
// }
// 

#define WH_KEYBOARD_LL		13
#define LLKHF_ALTDOWN       0x00000020

typedef struct tagKBDLLHOOKSTRUCT {
    DWORD   vkCode;
    DWORD   scanCode;
    DWORD   flags;
    DWORD   time;
    DWORD   dwExtraInfo;
} KBDLLHOOKSTRUCT, FAR *LPKBDLLHOOKSTRUCT, *PKBDLLHOOKSTRUCT;


LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    if (nCode == HC_ACTION)
    {
        PKBDLLHOOKSTRUCT p;// 
        
        switch (wParam) 
        {
        case WM_KEYDOWN:  
        case WM_SYSKEYDOWN:
        case WM_KEYUP:    
        case WM_SYSKEYUP: 
            p = (PKBDLLHOOKSTRUCT)lParam;			
            if( //(p->vkCode==VK_TAB) ||
                (p->vkCode == VK_ESCAPE) ||
                (p->vkCode == VK_LWIN) ||
                (p->vkCode == VK_RWIN) ||
                /*(p->vkCode == VK_CONTROL) ||*/
                (p->vkCode == VK_SHIFT) ||
                (p->vkCode == VK_F1) ||
                //(p->vkCode == 0x6E) ||
                //(p->vkCode == 0x2E) ||
                ( (p->vkCode == VK_F4) && ((p->flags & LLKHF_ALTDOWN)!=0) ) ||    //ALT+F4
                ( (p->vkCode == VK_TAB) && ((p->flags & LLKHF_ALTDOWN)!=0) ) ||    //ALT+TAB
                ( (p->vkCode == VK_ESCAPE) && ((p->flags & LLKHF_ALTDOWN)!=0) ) ||   //ALT+ESC
                ( (p->vkCode == VK_ESCAPE) && ((GetKeyState(VK_CONTROL) & 0x8000)!=0) ) || //CTRL+ESC
                ( (p->vkCode == VK_DELETE) && ((p->flags & LLKHF_ALTDOWN)!=0) && ((GetKeyState(VK_CONTROL) & 0x8000)!=0)  ) //CTRL+ALT + DEL  
                
                )
            {
                return TRUE;
            }
            
            break;
        }
        
    }
    
    return ::CallNextHookEx( NULL, nCode, wParam, lParam );	
}



#define EXCEPTION_FILE_PATH _T("exception.log")
BOOL CCmsApp::InitInstance()
{ 
    // �쳣����
    // g_ExceptionFilter = SetUnhandledExceptionFilter( MyExceptionFilter);
   
    // AutoRun( TRUE );

	//ֻ����һ������ʵ��
    if ( !OnlyStartOne() )
	{
        TerminateProcess(GetCurrentProcess(), 0);
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
//cnc ������pc�汾��ȥ�����ӣ����ⲿ����ӵ�tpad��   2013.1.7 yjj 
//     //���ò�����ϼ��͹��ܼ�
//    #ifndef _DEBUG    
// //    // ���ڽ������������  2012.8.16 by yjj  ��ϵͳ����ʱ����
// //     BusinessManagePtr->DisableTaskMgr( /*TRUE*/FALSE );
//       m_hk = ::SetWindowsHookEx(WH_KEYBOARD_LL,LowLevelKeyboardProc, AfxGetApp()->m_hInstance, 0);  
//    #endif

    //---��ʼ��-----------begin---    
	//��ʼ��������Ϣ
	UIManagePtr->GetUiManagePtr();
   
	//��ʼ�����ڹ����߼���Ϣ
	CLogicManage::GetLogicManagePtr()->CreateLogic();

    //����usm ��cns session
	BusinessManagePtr->CreateSession();	

    //---��ʼ��-----------end---
  
    IWndTree* pTree = const_cast<IWndTree*>( UIManagePtr->GetWindow( g_stcStrMainFrameDlg )); 
	if ( pTree == 0 )
	{
		return FALSE;
	}
	WndInfo* pInfo = pTree->GetItemData();
	

 	m_pMainWnd = pInfo->pWnd ;  
	m_pMainWnd->SendMessage( WM_REDRAW_UI ,0 ,0 ); 

	::SetProp( m_pMainWnd->GetSafeHwnd(), AfxGetApp()->m_pszAppName, (HANDLE)1 );

    m_pMainWnd->RunModalLoop();
	
    return TRUE;
 	 
 
	CCmsDlg dlg;
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

BOOL CCmsApp::PreTranslateMessage(MSG* pMsg) 
{ 
    switch( pMsg->message )
    {
    case WM_KEYDOWN: //�����س�����ESC������ֹ�Ӵ�����ʧ 
    {  
        //2013.1.7 yjj
		if ( pMsg->wParam == VK_ESCAPE )
		{
			return TRUE;
		}

        if ( pMsg->wParam == VK_RETURN && pMsg->hwnd  )
        {    
            HWND defIDHwnd = GetDefIDWndHandle( pMsg->hwnd );
            if ( defIDHwnd > 0 )
            {
                pMsg->hwnd  = defIDHwnd;
                pMsg->message = WM_BUTTON_CLICK/*WM_LBUTTONUP*/;
                break;
            }  
            else
            {
               return TRUE;
            }
            
        }
		else if ( pMsg->wParam == VK_LWIN || pMsg->wParam == VK_RWIN)
		{
			//����˫������ 2013.2.1 yjj
			CMsgDispatch::SendMessage( WM_CMS_HIDE_VEDIO ,0 , 0 );
		} 

    }
    break;
    case WM_RBUTTONDOWN:  //�����Bug00079096 ���������㿪CMCһ���ؼ��������Ҽ�������һ���ؼ���ͬ���ؼ��ϵ������ԭ���汻�رն��¿ؼ�������ʾ�Ҳ�����Ӧ����
        pMsg->message = WM_LBUTTONDOWN;
        break;
    case WM_RBUTTONUP:
        pMsg->message = WM_LBUTTONUP;
        break;
//     case WM_TOUCH_BUTTONDOWN:
//         pMsg->message = WM_LBUTTONDOWN;
        break;
	case WM_COMMAND:
		if ( pMsg->wParam == WM_DESTROY )		//�������Ҽ�����رճ���  2013��11��8�� JYY
		{
			BusinessManagePtr->ShutDownCmc();
		}
		break;


//     case WM_KEYUP:
//     {   
//         //�������л���Сдʱ�������Ҳͬ���л�    
//         if (  pMsg->wParam == VK_CAPITAL  )
//         {  
//             CSoftKeyboardDlg::GetSingleTon()->RedrawUI(); 
//         }
// 
//         break;
//     }
//     case WM_LBUTTONDOWN:
//     {
//        //�жϵ�ǰhwnd�Ƿ��ǿɱ༭�ģ�����ǣ��򵯳�����̣�������ǣ������������
//         s8 pName[256]={0};
//         GetClassName(  pMsg->hwnd,pName,sizeof(pName) ); 
//         if ( strcmp(pName,"Edit") == 0  )
//         {   
//             WINDOWINFO pwi; 
//             if ( GetWindowInfo( pMsg->hwnd,&pwi ) )
//             { 
//                 if ( pwi.dwStyle & ES_READONLY || !::IsWindowVisible( pMsg->hwnd ) )  //ֻ�����Եı༭�򲻵�������
//                 {
//                      SetSoftKBDlgHide( );
//                      break;
//                 }
//             }
// 
//             SetSoftKBDlgShow( pMsg->hwnd );
//         
//         }
//         else if( pMsg->hwnd != CInputMgr::GetSingleTon()->GetCurHwnd() )
//         {  
//             if (  ::GetParent( pMsg->hwnd ) != CInputMgr::GetSingleTon()->GetCurHwnd() )
//             {
//                  SetSoftKBDlgHide( );
//             }  
//         }
//       
//        
//     }
//      
//     break;

  
    }
	
    UIManagePtr->HandleMsg( pMsg );
    
    return CWinApp::PreTranslateMessage(pMsg);
}



int CCmsApp::ExitInstance() 
{
    // TODO: Add your specialized code here and/or call the base class
    CExceptionCatch::Free();
	if ( m_hk )
    {
		::UnhookWindowsHookEx( m_hk );
    }
   // BusinessManagePtr->DisableTaskMgr( FALSE );
    if ( m_pMainWnd != NULL &&  m_pMainWnd->GetSafeHwnd() != NULL )
    {
        m_pMainWnd->DestroyWindow();
        delete m_pMainWnd;  
        m_pMainWnd = 0;
    } 
    
    ::RemoveProp( m_pMainWnd->GetSafeHwnd(), AfxGetApp()->m_pszAppName );
    

    return CWinApp::ExitInstance();
}




//��ĳ���������Ƿ��� Ĭ�ϰ�ť
HWND CCmsApp::GetDefIDWndHandle( HWND hwnd )
{
    s8 pName[256]={0};
    GetClassName(  hwnd,pName,sizeof(pName) );
    HWND hParent = hwnd;
    if ( strcmp(pName,"CDialog") != 0 )
    {   
        hParent = GetParent( hwnd );  
    } 
    
    if ( hParent  && CWnd::FromHandle( hParent ) )
    {  
        try
        {    
            CDialog *pParent = NULL;
            if ( pParent = dynamic_cast<CDialog * >( CWnd::FromHandle( hParent )) )
            {
                DWORD id = pParent->GetDefID();
                id = LOWORD(id);
                HWND hBtn = GetDlgItem(hParent, id );
                if ( hBtn )
                { 
                    return hBtn;
                } 
                
            }
        }
        catch ( ... )
        {
            
        } 
        
    }
    
    return 0;
    
}


/*
void DisableTaskMgr( BOOL bDisable )
{ 
    CString KEY_DisableTaskMgr = "Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System";
    CString VAL_DisableTaskMgr = "DisableTaskMgr";

    HKEY hk;
    BOOL32 bEnableTaskMgr = FALSE;
    if (  RegOpenKey(HKEY_CURRENT_USER, KEY_DisableTaskMgr, &hk)!=ERROR_SUCCESS )
    {
       //  û�д˼���δ����
        bEnableTaskMgr = FALSE;
    }
    else
    {   
        DWORD val=0;
        DWORD len=4;
        bEnableTaskMgr =  ( RegQueryValueEx(hk, VAL_DisableTaskMgr, NULL, NULL, (BYTE*)&val, &len)==ERROR_SUCCESS && val==1 );

    }  

    if ( bEnableTaskMgr  !=   bDisable )
    {
        if ( bDisable )
        {
            // ���ڽ���������������Ե�ע����ֵ�� 
            if (RegOpenKey(HKEY_CURRENT_USER, KEY_DisableTaskMgr,&hk)!=ERROR_SUCCESS)
            {
                RegCreateKey(HKEY_CURRENT_USER, KEY_DisableTaskMgr, &hk);
            }
            
            // ���������������disable TM���� set policy = 1
            DWORD val=1;
            RegSetValueEx(hk, VAL_DisableTaskMgr, NULL, REG_DWORD, (BYTE*)&val, sizeof(val));
        }
        else
        {
            // ���������������enable TM��
            RegDeleteValue(hk,VAL_DisableTaskMgr);
        }
    } 

}
*/

BOOL OnlyStartOne()
{  
	HANDLE  hSem  =  CreateSemaphore(NULL,  1,  1, AfxGetApp()->m_pszAppName);   
	 
	//   �ź������ڣ����������һ��ʵ������   
	if (GetLastError()   ==   ERROR_ALREADY_EXISTS)   
	{  		
		//   �ر��ź������   
		CloseHandle(hSem);   
		//   Ѱ����ǰʵ����������   
		HWND   hWndPrevious = ::GetWindow(::GetDesktopWindow(),GW_CHILD);   
		while   (::IsWindow(hWndPrevious))   
		{   
			//   ��鴰���Ƿ���Ԥ��ı��?   
			//   �У���������Ѱ�ҵ�����   
			if   (::GetProp(hWndPrevious, AfxGetApp()->m_pszAppName))   
			{    		 
				//BOOL re = ((CIPSetterDlg)(CWnd::FromHandle(hWndPrevious))).setDestroyFlagEx(FALSE);
				//(CWnd::FromHandle(hWndPrevious))->SendMessage(WM_DESTROY_FLAG,FALSE,TRUE); 
				
				//   ����������С������ָ����С   
				if   (::IsIconic(hWndPrevious)) 				
					::ShowWindow(hWndPrevious,SW_RESTORE);   
				
				HWND hdl = GetForegroundWindow();
				if (hWndPrevious !=  hdl )
				{   					
					::ShowWindow(hWndPrevious,SW_RESTORE); 
					::SetForegroundWindow(hWndPrevious);
				}
				
				return   FALSE;   
			}   
			//   ����Ѱ����һ������   
			hWndPrevious   =   ::GetWindow(hWndPrevious,GW_HWNDNEXT); 
		}   
		//   ǰһʵ���Ѵ��ڣ����Ҳ���������   
		//   �˳���ʵ��   
		return   FALSE;   
	} 
	return TRUE;
}

 

//ʵ�ֿ���������
BOOL  AutoRun( bool bAutoRun )
{

     BOOL bRe = TRUE; 
//#ifndef _DEBUG  
   
    char CurrentPath [sizeof(WCHAR)*100] = {0}; //����ǰ·��
    
    HKEY   hRegKey;   //ע��key
    BOOL   bResult;   //��ע�����ֵ
    CString str;
    str= "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Winlogon" ;//ע���   
   
    if ( bAutoRun )
    {
        GetModuleFileName(NULL,CurrentPath,MAX_PATH); //������ó���·��
      
    }
    else
    {
        sprintf ( CurrentPath, "explorer.exe");
    }
    
    
    if(bResult=RegOpenKey(HKEY_LOCAL_MACHINE,   str,   &hRegKey)   !=   ERROR_SUCCESS)//��ע���     
    {   	 
        bRe = FALSE;
        return bRe;   
    }  
    
    if(bResult=::RegSetValueEx(hRegKey,_T("Shell"),0,REG_SZ,(const unsigned char *)CurrentPath, MAX_PATH) != ERROR_SUCCESS)   //�򿪳ɹ�д��Ϣ��ע���
    {   //д��ʧ��
        RegCloseKey(hRegKey);   //�ر�ע���key 
        bRe = FALSE;
        return bRe;
    }   
    //�ɹ���ִ���ͷ��ڴ�
    RegCloseKey(hRegKey);   

//#endif   
    return bRe;

}


API void help()
{
    PrtMsg( "\nshowver: ��ʾ�汾�ͱ���ʱ��");
    PrtMsg( "\ntask 1/0: �Ƿ����������������1������ ��0������");
    PrtMsg( "\nprt: ��ӡ���м���Ϊ3���ϵ���Ϣ");
    PrtMsg( "\nprtlevel nLevel: ��ӡ����ΪnLevel����Ϣ����Ϣ���� 1-3��\n \
    1Ϊ������ߵ���Ϣ���ü������Ϣ��ϵͳ���ܲ�������Ӱ��\n \
    2Ϊһ�㼶�����Ϣ\n \
    3Ϊ��ͼ�����Ϣ " );
    PrtMsg( "\nprtid msgID: ��ӡ��Ϣ����msgID����Ϣ");
    PrtMsg( "\nprtrange beginID endID: ��ӡ��Ϣ�ŷ�Χ�� beginID �� endID ֮�����Ϣ");
    PrtMsg( "\nstopprt: ֹͣ��ӡ������Ϣ");
    PrtMsg( "\nprtrecive 0 / 1: ��ӡ���н��ܵ�����Ϣ, 0:����ӡ��1:��ӡ");
    PrtMsg( "\nprtsend 0 / 1: ��ӡ���з��ͳ�ȥ����Ϣ, 0:����ӡ��1:��ӡ"); 
    PrtMsg( "\nshowallconf: ��ʾ���л�����Ϣ");
    PrtMsg( "\nshowcns: ��ʾ���ػ᳡��Ϣ");
    PrtMsg( "\nshowconf wConfID: ��ʾIDΪwConfID�Ļ�����Ϣ");
    PrtMsg( "\nhangupep wConfID epID: �Ҷϻ����еĻ᳡��wConfID������ID��epID��������cns��ID"); 
    PrtMsg( "\nhangupconf wConfID: �Ҷϻ��飬wConfID������ID");  
    PrtMsg( "\nshowconfcns wConfID wCnsID: ��ʾ�����л᳡��Ϣ��wConfID������ID��wCnsID��������cns��ID");
    PrtMsg( "\nshowcnsstate: cns����״̬");
    //PrtMsg( "\nshowalltemp: ��ʾ��Ӧ��ģ����Ϣ��������ʾ����ģ����Ϣ" );
    //PrtMsg( "\nshowtemp ID: ����ʾ��Ӧ��ģ����Ϣ " );
    PrtMsg( "\nshowscrninfo: ��ʾ����Ϣ ");
    PrtMsg( "\nshowallcns: ��ʾ���ӵ����л᳡" );
    PrtMsg( "\nshowalluser: ��ʾ�����û���Ϣ" );
    PrtMsg( "\nshowlocalip: ��ʾ����PC��IP" );
    PrtMsg( "\nsetdecvol 0-255: ���ý�������������Χ 0-255" );
    PrtMsg( "\nshowdecvol :��ʾ��ǰ��������������Χ 0-255" );
    PrtMsg( "\nshowalarm: ��ʾ��ǰ���и澯��Ϣ" );
    PrtMsg( "\nshowaddrbook: ��ʾ��ǰ��ַ����Ϣ" );
    PrtMsg( "\nshowonlineaddr: ��ʾȫ�ֵ�ַ����Ϣ" );
    PrtMsg( "\nshowaddrentry dwEntryIndex: ��ʾ��ַ���᳡��Ϣ, dwEntryIndex:�᳡����" );
}

API void task( BOOL bEnable/* = TRUE */)
{
    BusinessManagePtr->DisableTaskMgr( !bEnable );
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


API void prtid( u32 msgID )
{
   CPrintCtrl::GetPrintCtrl()->SetPrintMsgID( msgID );
}

API void prtrange( u32 beginID, u32 endID )
{ 
    CPrintCtrl::GetPrintCtrl()->SetPrintMsgRange( beginID, endID ); 
}


API void prtrecive( BOOL bPrint /*= TRUE */ )
{
    CPrintCtrl::GetPrintCtrl()->PrintEnterMsg( bPrint ); 
}

API void prtsend( BOOL bPrint/* = TRUE */)
{
   CPrintCtrl::GetPrintCtrl()->PrintOutMsg( bPrint );
}


API void showver()
{   
    PrtMsg( "Cnc  version: %s  \n", GetCncBuildVersion() ); 
    PrtMsg( "compile time: %s %s", __DATE__, __TIME__ );
}

// ��ʾ���л���
API void showallconf()
{
    COutPrint::GetAllConfInfo();
}

//��ʾĳID�Ļ�����Ϣ
API void showconf( u16 wConfID )
{
    COutPrint::GetConfInfo( wConfID );
    COutPrint::GetConfCnsInfo( wConfID );
}



//��ʾ������cns����Ϣ
API void showconfcns( u16 wConfID , u16 wCnsID )
{
    COutPrint::GetConfCnsInfo( wConfID , wCnsID);
}

//��ʾ �᳡��Ϣ
API void showcns()
{
    COutPrint::GetLocalCnsInfo();
}

//��ʾCNS�����л᳡
API void showallcns()
{
	COutPrint::ShowCnsList();
}

//��ʾ����cns״̬
API void showcnsstate()
{
    COutPrint::IsLocalCnsInConf();
}

/*
API void showtemp( u16 tempID )   //��ʾ����ģ��
{
    COutPrint::ShowConfTemp( tempID );
}

API void showalltemp( )  //��ʾ����ģ��
{
     COutPrint::ShowConfTemp( -1 );
}
*/

//��ʾ����Ϣ
API void showscrninfo()
{
    COutPrint::ShowScrnInfo();
}

//��ʾ�����û���Ϣ
API void showalluser()
{
     COutPrint::ShowAllUseInfo();
}

API void  showlocalip()
{
    COutPrint::ShowLocalIP();
}

//���ý���������
API void  setdecvol( u8 abyVol )
{
    COutPrint::SetDecVol( abyVol );
}

//��ʾ��ǰ����������
API void  showdecvol()
{
    COutPrint::ShowDecVol();
}


//�Ҷ�ĳ�����е�ĳ���᳡
API void hangupep( u16 wConfID, u16 epID )
{
    TConfEpID ep;
    ep.m_wConfID = wConfID;
    ep.m_wEpID = epID;
    u16 re = BusinessManagePtr->HangupCNS( ep );
    if ( re != NO_ERROR )
    {
        PrtMsg("\n[API void hangupep]re = %d \n", re );
    }
}

//��������
API void hangupconf( u16 wConfID )
{   
    u16 re = BusinessManagePtr->HangupConf(   );
    if ( re != NO_ERROR )
    {
        PrtMsg("\n[API void hangupconf]re = %d \n", re );
    }
    
}

//��ʾ�澯��Ϣ
API void showalarm()
{
    COutPrint::ShowAlarmInfoLst();
}

//��ʾ��ַ����Ϣ
API void showaddrbook()
{
    COutPrint::ShowAddrbook();
}

//��ʾȫ�ֵ�ַ����Ϣ
API void showonlineaddr()
{
    COutPrint::ShowOnlineAddr();
}

API void showaddrentry( u32 dwEntryIndex )
{
    COutPrint::ShowAddrEntry( dwEntryIndex );
}

//��ʾ��������
API void showdlgpos( char* pchDlgName )
{
    COutPrint::ShowDlgName( pchDlgName );
}