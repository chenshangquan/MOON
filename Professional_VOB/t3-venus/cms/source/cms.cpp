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
//  //写异常
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
// //功    能: 异常捕获 
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
    // 异常处理
    // g_ExceptionFilter = SetUnhandledExceptionFilter( MyExceptionFilter);
   
    // AutoRun( TRUE );

	//只开启一个程序实例
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

    //异常处理
    CString strFullPath = GetModuleFullPath();
    strFullPath += EXCEPTION_FILE_PATH;
    CExceptionCatch::LogToFile( (LPSTR)(LPCSTR)strFullPath );
    CExceptionCatch::Start();   
//cnc 单独出pc版本，去除钩子，把这部分添加到tpad上   2013.1.7 yjj 
//     //禁用部分组合键和功能键
//    #ifndef _DEBUG    
// //    // 用于禁用任务管理器  2012.8.16 by yjj  由系统改造时禁用
// //     BusinessManagePtr->DisableTaskMgr( /*TRUE*/FALSE );
//       m_hk = ::SetWindowsHookEx(WH_KEYBOARD_LL,LowLevelKeyboardProc, AfxGetApp()->m_hInstance, 0);  
//    #endif

    //---初始化-----------begin---    
	//初始化窗口信息
	UIManagePtr->GetUiManagePtr();
   
	//初始化窗口管理逻辑信息
	CLogicManage::GetLogicManagePtr()->CreateLogic();

    //创建usm 和cns session
	BusinessManagePtr->CreateSession();	

    //---初始化-----------end---
  
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
    case WM_KEYDOWN: //禁掉回车键和ESC键，防止子窗口消失 
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
			//隐藏双流窗口 2013.2.1 yjj
			CMsgDispatch::SendMessage( WM_CMS_HIDE_VEDIO ,0 , 0 );
		} 

    }
    break;
    case WM_RBUTTONDOWN:  //解决【Bug00079096 】鼠标左键点开CMC一个控件，再用右键在另外一个控件或同个控件上点击，则原界面被关闭而新控件高亮显示且不打开相应界面
        pMsg->message = WM_LBUTTONDOWN;
        break;
    case WM_RBUTTONUP:
        pMsg->message = WM_LBUTTONUP;
        break;
//     case WM_TOUCH_BUTTONDOWN:
//         pMsg->message = WM_LBUTTONDOWN;
        break;
	case WM_COMMAND:
		if ( pMsg->wParam == WM_DESTROY )		//任务栏右键点击关闭程序  2013年11月8日 JYY
		{
			BusinessManagePtr->ShutDownCmc();
		}
		break;


//     case WM_KEYUP:
//     {   
//         //当键盘切换大小写时，软键盘也同步切换    
//         if (  pMsg->wParam == VK_CAPITAL  )
//         {  
//             CSoftKeyboardDlg::GetSingleTon()->RedrawUI(); 
//         }
// 
//         break;
//     }
//     case WM_LBUTTONDOWN:
//     {
//        //判断当前hwnd是否是可编辑的，如果是，则弹出软键盘，如果不是，则隐藏软键盘
//         s8 pName[256]={0};
//         GetClassName(  pMsg->hwnd,pName,sizeof(pName) ); 
//         if ( strcmp(pName,"Edit") == 0  )
//         {   
//             WINDOWINFO pwi; 
//             if ( GetWindowInfo( pMsg->hwnd,&pwi ) )
//             { 
//                 if ( pwi.dwStyle & ES_READONLY || !::IsWindowVisible( pMsg->hwnd ) )  //只读属性的编辑框不弹出键盘
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




//从某个窗口中是否含有 默认按钮
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
       //  没有此键，未禁用
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
            // 用于禁用任务管理器策略的注册表键值对 
            if (RegOpenKey(HKEY_CURRENT_USER, KEY_DisableTaskMgr,&hk)!=ERROR_SUCCESS)
            {
                RegCreateKey(HKEY_CURRENT_USER, KEY_DisableTaskMgr, &hk);
            }
            
            // 禁用任务管理器（disable TM）： set policy = 1
            DWORD val=1;
            RegSetValueEx(hk, VAL_DisableTaskMgr, NULL, REG_DWORD, (BYTE*)&val, sizeof(val));
        }
        else
        {
            // 启用任务管理器（enable TM）
            RegDeleteValue(hk,VAL_DisableTaskMgr);
        }
    } 

}
*/

BOOL OnlyStartOne()
{  
	HANDLE  hSem  =  CreateSemaphore(NULL,  1,  1, AfxGetApp()->m_pszAppName);   
	 
	//   信号量存在，则程序已有一个实例运行   
	if (GetLastError()   ==   ERROR_ALREADY_EXISTS)   
	{  		
		//   关闭信号量句柄   
		CloseHandle(hSem);   
		//   寻找先前实例的主窗口   
		HWND   hWndPrevious = ::GetWindow(::GetDesktopWindow(),GW_CHILD);   
		while   (::IsWindow(hWndPrevious))   
		{   
			//   检查窗口是否有预设的标记?   
			//   有，则是我们寻找的主窗   
			if   (::GetProp(hWndPrevious, AfxGetApp()->m_pszAppName))   
			{    		 
				//BOOL re = ((CIPSetterDlg)(CWnd::FromHandle(hWndPrevious))).setDestroyFlagEx(FALSE);
				//(CWnd::FromHandle(hWndPrevious))->SendMessage(WM_DESTROY_FLAG,FALSE,TRUE); 
				
				//   主窗口已最小化，则恢复其大小   
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
			//   继续寻找下一个窗口   
			hWndPrevious   =   ::GetWindow(hWndPrevious,GW_HWNDNEXT); 
		}   
		//   前一实例已存在，但找不到其主窗   
		//   退出本实例   
		return   FALSE;   
	} 
	return TRUE;
}

 

//实现开机自启动
BOOL  AutoRun( bool bAutoRun )
{

     BOOL bRe = TRUE; 
//#ifndef _DEBUG  
   
    char CurrentPath [sizeof(WCHAR)*100] = {0}; //程序当前路径
    
    HKEY   hRegKey;   //注册key
    BOOL   bResult;   //打开注册表返回值
    CString str;
    str= "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Winlogon" ;//注册表   
   
    if ( bAutoRun )
    {
        GetModuleFileName(NULL,CurrentPath,MAX_PATH); //获得运用程序路径
      
    }
    else
    {
        sprintf ( CurrentPath, "explorer.exe");
    }
    
    
    if(bResult=RegOpenKey(HKEY_LOCAL_MACHINE,   str,   &hRegKey)   !=   ERROR_SUCCESS)//打开注册表     
    {   	 
        bRe = FALSE;
        return bRe;   
    }  
    
    if(bResult=::RegSetValueEx(hRegKey,_T("Shell"),0,REG_SZ,(const unsigned char *)CurrentPath, MAX_PATH) != ERROR_SUCCESS)   //打开成功写信息到注册表
    {   //写入失败
        RegCloseKey(hRegKey);   //关闭注册表key 
        bRe = FALSE;
        return bRe;
    }   
    //成功后执行释放内存
    RegCloseKey(hRegKey);   

//#endif   
    return bRe;

}


API void help()
{
    PrtMsg( "\nshowver: 显示版本和编译时间");
    PrtMsg( "\ntask 1/0: 是否启用任务管理器；1：启用 ，0：禁用");
    PrtMsg( "\nprt: 打印所有级别为3以上的消息");
    PrtMsg( "\nprtlevel nLevel: 打印级别为nLevel的消息；消息级别 1-3，\n \
    1为级别最高的消息，该级别的消息对系统可能产生致命影响\n \
    2为一般级别的消息\n \
    3为最低级别消息 " );
    PrtMsg( "\nprtid msgID: 打印消息号是msgID的消息");
    PrtMsg( "\nprtrange beginID endID: 打印消息号范围在 beginID 和 endID 之间的消息");
    PrtMsg( "\nstopprt: 停止打印所有消息");
    PrtMsg( "\nprtrecive 0 / 1: 打印所有接受到的消息, 0:不打印，1:打印");
    PrtMsg( "\nprtsend 0 / 1: 打印所有发送出去的消息, 0:不打印，1:打印"); 
    PrtMsg( "\nshowallconf: 显示所有会议信息");
    PrtMsg( "\nshowcns: 显示本地会场信息");
    PrtMsg( "\nshowconf wConfID: 显示ID为wConfID的会议信息");
    PrtMsg( "\nhangupep wConfID epID: 挂断会议中的会场，wConfID：会议ID，epID：会议中cns的ID"); 
    PrtMsg( "\nhangupconf wConfID: 挂断会议，wConfID：会议ID");  
    PrtMsg( "\nshowconfcns wConfID wCnsID: 显示会议中会场信息，wConfID：会议ID，wCnsID：会议中cns的ID");
    PrtMsg( "\nshowcnsstate: cns会议状态");
    //PrtMsg( "\nshowalltemp: 显示相应的模板信息，否则，显示所有模板信息" );
    //PrtMsg( "\nshowtemp ID: 则显示相应的模板信息 " );
    PrtMsg( "\nshowscrninfo: 显示屏信息 ");
    PrtMsg( "\nshowallcns: 显示连接的所有会场" );
    PrtMsg( "\nshowalluser: 显示所有用户信息" );
    PrtMsg( "\nshowlocalip: 显示本地PC机IP" );
    PrtMsg( "\nsetdecvol 0-255: 设置解码器音量，范围 0-255" );
    PrtMsg( "\nshowdecvol :显示当前解码器音量，范围 0-255" );
    PrtMsg( "\nshowalarm: 显示当前所有告警信息" );
    PrtMsg( "\nshowaddrbook: 显示当前地址簿信息" );
    PrtMsg( "\nshowonlineaddr: 显示全局地址簿信息" );
    PrtMsg( "\nshowaddrentry dwEntryIndex: 显示地址簿会场信息, dwEntryIndex:会场索引" );
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

// 显示所有会议
API void showallconf()
{
    COutPrint::GetAllConfInfo();
}

//显示某ID的会议信息
API void showconf( u16 wConfID )
{
    COutPrint::GetConfInfo( wConfID );
    COutPrint::GetConfCnsInfo( wConfID );
}



//显示会议中cns的信息
API void showconfcns( u16 wConfID , u16 wCnsID )
{
    COutPrint::GetConfCnsInfo( wConfID , wCnsID);
}

//显示 会场信息
API void showcns()
{
    COutPrint::GetLocalCnsInfo();
}

//显示CNS上所有会场
API void showallcns()
{
	COutPrint::ShowCnsList();
}

//显示本地cns状态
API void showcnsstate()
{
    COutPrint::IsLocalCnsInConf();
}

/*
API void showtemp( u16 tempID )   //显示会议模板
{
    COutPrint::ShowConfTemp( tempID );
}

API void showalltemp( )  //显示会议模板
{
     COutPrint::ShowConfTemp( -1 );
}
*/

//显示屏信息
API void showscrninfo()
{
    COutPrint::ShowScrnInfo();
}

//显示所有用户信息
API void showalluser()
{
     COutPrint::ShowAllUseInfo();
}

API void  showlocalip()
{
    COutPrint::ShowLocalIP();
}

//设置解码器音量
API void  setdecvol( u8 abyVol )
{
    COutPrint::SetDecVol( abyVol );
}

//显示当前解码器音量
API void  showdecvol()
{
    COutPrint::ShowDecVol();
}


//挂断某会议中的某个会场
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

//结束会议
API void hangupconf( u16 wConfID )
{   
    u16 re = BusinessManagePtr->HangupConf(   );
    if ( re != NO_ERROR )
    {
        PrtMsg("\n[API void hangupconf]re = %d \n", re );
    }
    
}

//显示告警信息
API void showalarm()
{
    COutPrint::ShowAlarmInfoLst();
}

//显示地址簿信息
API void showaddrbook()
{
    COutPrint::ShowAddrbook();
}

//显示全局地址簿信息
API void showonlineaddr()
{
    COutPrint::ShowOnlineAddr();
}

API void showaddrentry( u32 dwEntryIndex )
{
    COutPrint::ShowAddrEntry( dwEntryIndex );
}

//显示窗口坐标
API void showdlgpos( char* pchDlgName )
{
    COutPrint::ShowDlgName( pchDlgName );
}