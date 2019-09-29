// centerctrllogic.cpp: implementation of the CCenterCtrlLogic class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "centerctrl.h"
#include "centerctrllogic.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CCenterCtrlLogic *CCenterCtrlLogic::m_pLogic = NULL;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCenterCtrlLogic::CCenterCtrlLogic()
{

}

CCenterCtrlLogic::~CCenterCtrlLogic()
{
    if ( m_pLogic != NULL )
    {   
        UnRegMsg();
        UnRegFunc();
        delete m_pLogic;
        m_pLogic = NULL;
	}
}

CCenterCtrlLogic* CCenterCtrlLogic::GetLogicPtr()
{
    if ( m_pLogic == NULL )
    {
        m_pLogic = new CCenterCtrlLogic(); 
    } 
    return m_pLogic;
}


void CCenterCtrlLogic::RegMsg()
{
    REG_MSG_HANDLER( UI_CNS_CONNECTED, CCenterCtrlLogic::OnConnectRsp, m_pLogic, CCenterCtrlLogic );    
    REG_MSG_HANDLER( UI_CNS_DISCONNECTED, CCenterCtrlLogic::OnDisConnect, m_pLogic, CCenterCtrlLogic );    
}

void CCenterCtrlLogic::UnRegMsg()
{
    
}

bool CCenterCtrlLogic::RegCBFun()
{   
    REG_GOBAL_MEMBER_FUNC( "CCenterCtrlLogic::InitWnd", CCenterCtrlLogic::InitWnd, m_pLogic, CCenterCtrlLogic );
    return true;
}

bool CCenterCtrlLogic::UnRegFunc()
{
    return true;
}

bool CCenterCtrlLogic::InitWnd( const IArgs & args )
{   
    CWndLogicBase::InitWnd( args );
    
    CreateWnd();

    //最小化窗口
    //Window* pWnd = UIFACTORYMGR_PTR->GetWindowPtr( g_stcStrCenterCtrlDlg );
    //pWnd->PostMessage( WM_SYSCOMMAND, SC_MINIMIZE, 0 ); 
    //最小化再显示会闪一下，直接隐藏
    UIFACTORYMGR_PTR->ShowWindow( g_stcStrCenterCtrlDlg, false );

    //连接TPad
    ComInterface->ConnectTPad();
    
    return true;
}

void CCenterCtrlLogic::Clear()
{   
}

void CCenterCtrlLogic::CreateWnd()
{
    UIFACTORYMGR_PTR->ShowWindow( g_stcStrMainMenuDlg, false );
    UIFACTORYMGR_PTR->ShowWindow( g_stcStrAirConditionDlg, false );
	UIFACTORYMGR_PTR->ShowWindow( g_stcStrCameraDlg, false );
    UIFACTORYMGR_PTR->ShowWindow( g_stcStrMonitorDlg, false );   
    UIFACTORYMGR_PTR->ShowWindow( g_stcStrTouchPadDlg, false );
	UIFACTORYMGR_PTR->ShowWindow( g_stcStrCurtainCfgDlg, false );
}


HRESULT CCenterCtrlLogic::OnConnectRsp( WPARAM wparam, LPARAM lparam )
{
    BOOL bLogin = (BOOL)wparam;
    if ( bLogin )
    {
        UIFACTORYMGR_PTR->ShowWindow( g_stcStrMainMenuDlg, true );
        UIFACTORYMGR_PTR->ShowWindow( g_stcStrTouchPadDlg, true ); 
    }

    return NO_ERROR;
}

HRESULT CCenterCtrlLogic::OnDisConnect( WPARAM wparam, LPARAM lparam )
{
    UIFACTORYMGR_PTR->LoadScheme( "SchmTouchPad", NULL, g_stcStrCenterCtrlDlg );
    UIFACTORYMGR_PTR->ShowWindow( g_stcStrMainMenuDlg, false );
    UIFACTORYMGR_PTR->ShowWindow( g_stcStrTouchPadDlg, false );
    //断链后隐藏
    UIFACTORYMGR_PTR->ShowWindow( g_stcStrCenterCtrlDlg, false );

    return NO_ERROR;
}