// mainmenulogic.cpp: implementation of the CMainMenuLogic class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "centerctrl.h"
#include "mainmenulogic.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CMainMenuLogic *CMainMenuLogic::m_pLogic = NULL;

typedef VOID (*WINSDK_RegTouchWindow)(HWND hWnd);

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

const String CMainMenuLogic::m_strBtnTouchPad = "MainMenuDlg/BtnTouchPad";
const String CMainMenuLogic::m_strBtnMonitor = "MainMenuDlg/BtnMonitor";
const String CMainMenuLogic::m_strBtnCamera = "MainMenuDlg/BtnCamera";
const String CMainMenuLogic::m_strBtnCurtainCfg = "MainMenuDlg/BtnCurtainCfg";

CMainMenuLogic::CMainMenuLogic()
{

}

CMainMenuLogic::~CMainMenuLogic()
{
    if ( m_pLogic != NULL )
    {   
        UnRegMsg();
        UnRegFunc();
        delete m_pLogic;
        m_pLogic = NULL; 
    }
}


CMainMenuLogic* CMainMenuLogic::GetLogicPtr()
{
    if ( m_pLogic == NULL )
    {
        m_pLogic = new CMainMenuLogic(); 
    } 
    return m_pLogic;
}


void CMainMenuLogic::RegMsg()
{
    
}

bool CMainMenuLogic::RegCBFun()
{   
    REG_GOBAL_MEMBER_FUNC( "CMainMenuLogic::InitWnd", CMainMenuLogic::InitWnd, m_pLogic, CMainMenuLogic );
    REG_GOBAL_MEMBER_FUNC( "CMainMenuLogic::OnClickAirCondition", CMainMenuLogic::OnClickAirCondition, m_pLogic, CMainMenuLogic );
    REG_GOBAL_MEMBER_FUNC( "CMainMenuLogic::OnClickCamera", CMainMenuLogic::OnClickCamera, m_pLogic, CMainMenuLogic );
    REG_GOBAL_MEMBER_FUNC( "CMainMenuLogic::OnClickMonitor", CMainMenuLogic::OnClickMonitor, m_pLogic, CMainMenuLogic );
    REG_GOBAL_MEMBER_FUNC( "CMainMenuLogic::OnClickTouchPad", CMainMenuLogic::OnClickTouchPad, m_pLogic, CMainMenuLogic );
	REG_GOBAL_MEMBER_FUNC( "CMainMenuLogic::OnClickCurtainCfg", CMainMenuLogic::OnClickCurtainCfg, m_pLogic, CMainMenuLogic );

    REG_GOBAL_MEMBER_FUNC( "CMainMenuLogic::OnBtnToCnc", CMainMenuLogic::OnBtnToCnc, m_pLogic, CMainMenuLogic );
    REG_GOBAL_MEMBER_FUNC( "CMainMenuLogic::OnBtnMinimize", CMainMenuLogic::OnBtnMinimize, m_pLogic, CMainMenuLogic );
    REG_GOBAL_MEMBER_FUNC( "CMainMenuLogic::OnBtnExit", CMainMenuLogic::OnBtnExit, m_pLogic, CMainMenuLogic );

    return true;
}


bool CMainMenuLogic::InitWnd( const IArgs & args )
{   
    CWndLogicBase::InitWnd( args );

	OSVERSIONINFOEX osvi;
    //利用OSVERSIONINFOEX结构调用GetVersionEx()函数
    //如果调用失败，可尝试使用OSVERSIONINFO结构
    ZeroMemory( &osvi, sizeof(OSVERSIONINFOEX) );
    osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
    if( !GetVersionEx((OSVERSIONINFO*)&osvi) )
    {
        osvi.dwOSVersionInfoSize=sizeof(OSVERSIONINFO);
        if(!GetVersionEx((OSVERSIONINFO*)&osvi))
            return false;
    }
    //xp以上版本才有触摸事件
    if ( osvi.dwMajorVersion > 5 )
    {  
        //注册响应WM_TOUCH的窗口
        Window* pWnd = UIFACTORYMGR_PTR->GetWindowPtr( m_strBtnTouchPad, m_pWndTree ); 
        Window* pWnd1 = UIFACTORYMGR_PTR->GetWindowPtr( m_strBtnMonitor, m_pWndTree ); 
		Window* pWnd2 = UIFACTORYMGR_PTR->GetWindowPtr( m_strBtnCamera, m_pWndTree ); 
        Window* pWnd3 = UIFACTORYMGR_PTR->GetWindowPtr( m_strBtnCurtainCfg, m_pWndTree ); 
        if ( pWnd->GetSafeHwnd() != NULL && pWnd1->GetSafeHwnd() != NULL )
        {
            WINSDK_RegTouchWindow _WINSDK_RegTouchWindow;
            
            HINSTANCE hInstLibrary = LoadLibrary("windowsexsdk.dll");
            if (hInstLibrary != NULL)
            {
                _WINSDK_RegTouchWindow = (WINSDK_RegTouchWindow)GetProcAddress( hInstLibrary, "WINSDK_RegTouchWindow" );
                if ( _WINSDK_RegTouchWindow != NULL )
                {
                    _WINSDK_RegTouchWindow( pWnd->GetSafeHwnd() );
                    _WINSDK_RegTouchWindow( pWnd1->GetSafeHwnd() );    
					_WINSDK_RegTouchWindow( pWnd2->GetSafeHwnd() );
                    _WINSDK_RegTouchWindow( pWnd3->GetSafeHwnd() );  
                }
                FreeLibrary( hInstLibrary );
            }
        } 
    }
    
    return true;
}

void CMainMenuLogic::Clear()
{   
}


bool CMainMenuLogic::OnClickAirCondition( const IArgs& args )
{
    UIFACTORYMGR_PTR->LoadScheme( "SchmAirCondition", NULL, g_stcStrCenterCtrlDlg );
    return true;
}

bool CMainMenuLogic::OnClickCamera( const IArgs& args )
{
    UIFACTORYMGR_PTR->LoadScheme( "SchmCamera", NULL, g_stcStrCenterCtrlDlg );
    return true;
}

bool CMainMenuLogic::OnClickMonitor( const IArgs& args )
{
    UIFACTORYMGR_PTR->LoadScheme( "SchmMonitor", NULL, g_stcStrCenterCtrlDlg );
    return true;
}

bool CMainMenuLogic::OnClickTouchPad( const IArgs& args )
{                 
    UIFACTORYMGR_PTR->LoadScheme( "SchmTouchPad", NULL, g_stcStrCenterCtrlDlg );

    return true;
}


bool CMainMenuLogic::OnClickCurtainCfg( const IArgs& args )
{
	UIFACTORYMGR_PTR->LoadScheme( "SchmCurtainCfg", NULL, g_stcStrCenterCtrlDlg );
	
    return true;
	
}

bool CMainMenuLogic::OnBtnToCnc( const IArgs& args )
{
    LPCSTR className = NULL;
    LPCSTR windName = "cnc";
    
    HWND hWnd = ::FindWindow( className , windName );
    if ( !IsWindow( hWnd ) )
    {
        CString strMsg;
        strMsg.Format( "\n CMainMenuLogic::OnBtnToCnc, No FindWindow: hWNd = %x \n", hWnd );
        PrtMsg( (LPSTR)(LPCTSTR)strMsg );

        UIFACTORYMGR_PTR->ShowWindow( g_stcStrCenterCtrlDlg, false );
        return false;
    }
    
    if (::IsIconic(hWnd)) 			
    {
        ::ShowWindow( hWnd, SW_RESTORE );
    }
    else
    {
        ::ShowWindow( hWnd, SW_SHOW );
    }
    //::ShowWindow(hWnd ,SW_MAXIMIZE);  
    //::ShowWindow( hWnd, SW_RESTORE );	
    ::SetForegroundWindow( hWnd );

    //Window*  pWnd = UIFACTORYMGR_PTR->GetWindowPtr( g_stcStrCenterCtrlDlg );
    //pWnd->PostMessage(WM_SYSCOMMAND,SC_MINIMIZE,0); 
    //最小化再显示会闪一下，直接隐藏
    UIFACTORYMGR_PTR->ShowWindow( g_stcStrCenterCtrlDlg, false );

    return true;
}

bool CMainMenuLogic::OnBtnMinimize( const IArgs& args )
{
    Window*  pWnd = UIFACTORYMGR_PTR->GetWindowPtr( g_stcStrCenterCtrlDlg );
    pWnd->PostMessage( WM_SYSCOMMAND, SC_MINIMIZE, 0 ); 

    return true;
}

bool CMainMenuLogic::OnBtnExit( const IArgs& args )
{
    //UINT uExitCode = 0;
	//ExitProcess( uExitCode );

    //最小化再显示会闪一下，直接隐藏
    UIFACTORYMGR_PTR->ShowWindow( g_stcStrCenterCtrlDlg, false );

    return true;
}


