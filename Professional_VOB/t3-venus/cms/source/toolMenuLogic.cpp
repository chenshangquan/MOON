// toolMenuLogic.cpp: implementation of the CToolMenuLogic class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "cms.h"
#include "toolMenuLogic.h"
#include "msgBoxLogic.h"
#include "UIDataMgr.h"
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


const String CToolMenuLogic::m_strBtnConfManage = "btnConfManage";
const String CToolMenuLogic::m_strBtnSysSet = "btnSysSet";
const String CToolMenuLogic::m_strBtnLogoff = "btnLogoff";
const String CToolMenuLogic::m_strBtnPowerdown = "btnPowerdown";
const String CToolMenuLogic::m_strBtnShutdown = "btnShutdown";
 
 

CToolMenuLogic *CToolMenuLogic::m_pLogic = NULL;


 
CToolMenuLogic::CToolMenuLogic():m_bFirstShow(TRUE)
{
     
    UIDATAMGR->SetCurMainMenuType( g_schmMainMenuCnsManage );
}

CToolMenuLogic::~CToolMenuLogic()
{
	if ( m_pLogic != NULL )
	{   
		UnRegMsg();
		UnRegFunc();
		delete m_pLogic;
		m_pLogic = NULL;
	}

}

CToolMenuLogic* CToolMenuLogic::GetLogicPtr()
{
	if ( m_pLogic == NULL )
	{  
		m_pLogic = new CToolMenuLogic();  
	}
	
	return m_pLogic;
}


void CToolMenuLogic::RegMsg()
{     
    //REG_MSG_HANDLER( UI_UMS_DISCONNECTED, CToolMenuLogic::OnDisConnect, m_pLogic, CToolMenuLogic );
    REG_MSG_HANDLER( UI_CNS_DISCONNECTED, CToolMenuLogic::OnDisConnect, m_pLogic, CToolMenuLogic );
  
    REG_MSG_HANDLER( UI_CMS_CLICK_TOOL_BTN, CToolMenuLogic::OnMainMenuClickToolBtn, m_pLogic, CToolMenuLogic );   
	
}

void CToolMenuLogic::UnRegMsg()
{
	//UNREG_MSGHANDLER(  UI_UMS_START_CONFTEMPLATE_RSP ); 
}

bool CToolMenuLogic::RegCBFun()
{   	 
	REG_GOBAL_MEMBER_FUNC( "CToolMenuLogic::InitWnd", CToolMenuLogic::InitWnd, m_pLogic, CToolMenuLogic ) ; 
   
    //点击会场管理
    REG_GOBAL_MEMBER_FUNC( "CToolMenuLogic::BtnMeetingManageClick", CToolMenuLogic::BtnMeetingManageClick, m_pLogic, CToolMenuLogic ) ;
	REG_GOBAL_MEMBER_FUNC( "CToolMenuLogic::BtnCnsManageClick", CToolMenuLogic::BtnCnsManageClick, m_pLogic, CToolMenuLogic ) ; 
    REG_GOBAL_MEMBER_FUNC( "CToolMenuLogic::BtnShutDownClick", CToolMenuLogic::BtnShutDownClick, m_pLogic, CToolMenuLogic ); 
	REG_GOBAL_MEMBER_FUNC( "CToolMenuLogic::BtnSystemSetClick", CToolMenuLogic::BtnSystemSetClick, m_pLogic, CToolMenuLogic );
    REG_GOBAL_MEMBER_FUNC( "CToolMenuLogic::BtnLogoutClick", CToolMenuLogic::BtnLogoutClick, m_pLogic, CToolMenuLogic );
	REG_GOBAL_MEMBER_FUNC( "CToolMenuLogic::BtnHideToolBarClick", CToolMenuLogic::BtnHideToolBarClick, m_pLogic, CToolMenuLogic );

    REG_GOBAL_MEMBER_FUNC( "CToolMenuLogic::DisConnect", CToolMenuLogic::DisConnect, m_pLogic, CToolMenuLogic );
    REG_GOBAL_MEMBER_FUNC( "CToolMenuLogic::ShutDown", CToolMenuLogic::ShutDown, m_pLogic, CToolMenuLogic );
    
    REG_GOBAL_MEMBER_FUNC( "CToolMenuLogic::BtnMinmizeClick", CToolMenuLogic::BtnMinmizeClick, m_pLogic, CToolMenuLogic );

    REG_GOBAL_MEMBER_FUNC( "CToolMenuLogic::OnBtnExitClick", CToolMenuLogic::OnBtnExitClick, m_pLogic, CToolMenuLogic );
    REG_GOBAL_MEMBER_FUNC( "CToolMenuLogic::ExitCmc", CToolMenuLogic::ExitCmc, m_pLogic, CToolMenuLogic );

    REG_GOBAL_MEMBER_FUNC( "CToolMenuLogic::OnBtnCenterCtrl", CToolMenuLogic::OnBtnCenterCtrl, m_pLogic, CToolMenuLogic );
    
    REG_GOBAL_MEMBER_FUNC( "CToolMenuLogic::OnWndHide", CToolMenuLogic::OnWndHide, m_pLogic, CToolMenuLogic );

	return true;
}

bool CToolMenuLogic::UnRegFunc()
{
	return true;
}


bool CToolMenuLogic::InitWnd(  const IArgs & arg )
{   
	CWndLogicBase::InitWnd( arg );  
	//UIManagePtr->LoadScheme( g_schmMainFrameBlankBkg, NULL,g_stcStrMainFrameDlg); 
    UpdateDlg();
    m_bFirstShow = TRUE;
    return true;
}

void CToolMenuLogic::Clear()
{    
    if ( m_pWndTree != NULL ) 
    {
        UIManagePtr->ShowWindow( g_stcStrToolMenuDlg , false );
    }  
   
    UIDATAMGR->SetCurMainMenuType( g_schmMainMenuCnsManage );
   
    m_bFirstShow = TRUE;
}
 
 

void CToolMenuLogic::UpdateDlg()
{
	BOOL32 bManager = BusinessManagePtr->IsManagerUser();	 
	
    if ( UIDATAMGR->IsPcVersion() )
    {
        if ( bManager ) 
        {
            //管理员用户需要 显示：会议管理、系统配置 按钮 
	        UIManagePtr->LoadScheme( "SchmToolMenuDefault", NULL, g_stcStrToolMenuDlg );   
        } 
        else
        {
	        UIManagePtr->LoadScheme( "SchmToolMenuBase", NULL, g_stcStrToolMenuDlg ); 
        } 
    }
    else
    {
        if ( bManager ) 
        {
            UIManagePtr->LoadScheme( "SchmTPadMenuDefault", NULL, g_stcStrToolMenuDlg );   
        } 
        else
        {
            UIManagePtr->LoadScheme( "SchmTPadMenuUser", NULL, g_stcStrToolMenuDlg ); 
        } 
    }
  
}

//点击会议管理
bool CToolMenuLogic::BtnMeetingManageClick( const IArgs & arg )
{   
    //UIManagePtr->LoadScheme( g_schmMainFrameBlankBkg, NULL,g_stcStrMainFrameDlg);
	UIManagePtr->SetTransparentDlgImage( g_stcStrMainFrameDlg, g_strMainFrameConfManageBkg );

    UIManagePtr->LoadScheme( g_schmMainFrameBlankBkg, NULL, UIDATAMGR->GetCurSimulateDlgName()); 
   
   
    UIDATAMGR->SetCurMainMenuType( g_schmMainMenuConfManage );
    UIManagePtr->LoadScheme( g_schmMainMenuConfManage, NULL, g_stcStrMainMenuDlg ); 

    UIManagePtr->LoadScheme( "SchmConfManageShow", NULL, g_stcStrToolMenuDlg ); 
    
    return true;
}

 
bool CToolMenuLogic::BtnCnsManageClick( const IArgs & arg )
{  
    TCMSConf tConfInfo;
    BOOL32 bInConf = BusinessManagePtr->IsInConf( &tConfInfo );  
    BOOL32 bChairman = BusinessManagePtr->IsLocalCnsChairMan() ;
    
	UIManagePtr->SetTransparentDlgImage( g_stcStrMainFrameDlg, g_strMainFrameSimulateBkg );	
	UIManagePtr->LoadScheme( g_schmMainFrameCnsBkg, NULL, UIDATAMGR->GetCurSimulateDlgName() );
     
    if ( bInConf )
    {    
		//会议中方案，g_schmMainMenuCnsManageInconfBase方案已弃用	 
        UIDATAMGR->SetCurMainMenuType( g_schmMainMenuCnsManageInconf );
		UIManagePtr->LoadScheme( g_schmMainMenuCnsManageInconf, NULL, g_stcStrMainMenuDlg);       
    }
    else
    { 
		 
        UIDATAMGR->SetCurMainMenuType( g_schmMainMenuCnsManage );
		UIManagePtr->LoadScheme( g_schmMainMenuCnsManage, NULL, g_stcStrMainMenuDlg );       
    }
   
    CMsgDispatch::SendMessage( WM_CMS_UPDATE_CMAINMENU , 0 , 0 );

    UIManagePtr->LoadScheme( "SchmConfManageShow",NULL,g_stcStrToolMenuDlg ); 
    return true;
}


bool CToolMenuLogic::BtnSystemSetClick( const IArgs & arg )
{  
    //UIManagePtr->LoadScheme( g_schmMainFrameBlankBkg, NULL,g_stcStrMainFrameDlg); 
	UIManagePtr->SetTransparentDlgImage( g_stcStrMainFrameDlg, g_strMainFrameSysCfgBkg );	
    UIManagePtr->LoadScheme( g_schmMainFrameBlankBkg, NULL,UIDATAMGR->GetCurSimulateDlgName());

   
    UIDATAMGR->SetCurMainMenuType( g_schmMainMenuSysManage );
	UIManagePtr->LoadScheme( g_schmMainMenuSysManage, NULL, g_stcStrMainMenuDlg );
    UIManagePtr->LoadScheme( "SchmSysManageShow", NULL, g_stcStrToolMenuDlg ); 
    //PrtMsg(0,emEventTypeCmsWindow, "[CToolMenuLogic::BtnSystemSetClick]" );
	return true;
}


bool CToolMenuLogic::BtnShutDownClick( const IArgs & arg )
{
    Args_MsgBox args;
    args.pOwnerWnd = UIManagePtr->GetWindowPtr( g_stcStrToolMenuDlg );
    int nReslut = MSG_BOX( "是否要关机？",TRUE ,&args);
    if ( IDOK == nReslut )
	{
		IArgs arg("");
		ShutDown( arg );
	}

	return true;
}

bool CToolMenuLogic::ShutDown( const IArgs & arg )
{
//     UINT uExitCode = 0;
//     ExitProcess( uExitCode );
// 	return true;

    BusinessManagePtr->ShutDownOS();
    return true;

//     Window* p = UIManagePtr->GetWindowPtr( g_stcStrLoginDlg );
//     if ( p )
//     {
//         p->DestroyWindow();
//     }
//     else
//     {
//         UINT uExitCode = 0;
//         ExitProcess( uExitCode );
//     }
}

HRESULT CToolMenuLogic::OnMainMenuClickToolBtn( WPARAM wparam, LPARAM lparam )
{
    if ( m_bFirstShow )
    {
        UpdateDlg();        
    } 
      
	//如果是pc版则需要设置位置   2013.1.10 yjj
//	if ( UIDATAMGR->IsPcVersion() )
	{
	    POINT pt;
		pt.x = 24;
		Value_WindowSize val;
		UIManagePtr->GetPropertyValue(val,g_stcStrToolMenuDlg);
		
		Value_WindowSize valParent;
		UIManagePtr->GetPropertyValue(valParent,g_stcStrMainFrameDlg);

		pt.y =  valParent.nHeight - 9 - val.nHeight;
		UIFACTORYMGR_PTR->SetWndPos( pt, g_stcStrToolMenuDlg,NULL,g_stcStrMainFrameDlg );
	}

    UIManagePtr->ShowWindow( g_stcStrMainMenuDlg + "/btnToolMenu", false); //点击时隐藏工具箱

	UIManagePtr->ShowWindow( g_stcStrToolMenuDlg );
    
    m_bFirstShow = FALSE;

   	return NO_ERROR;
}



HRESULT CToolMenuLogic::OnDisConnect( WPARAM wparam, LPARAM lparam )
{
    //BusinessManagePtr->DisConnect();

    if (  UIManagePtr->IsVisible( g_stcStrMsgBox) )
	{
        if ( CMsgBoxLogic::GetLogicPtr()->IsDisCntMsgBoxShow() )
        {    
            PrtMsg(0,emEventTypeCmsWindow, "======[CToolMenuLogic::OnDisConnect] IsDisCntMsgBoxShow = TRUE,return" );
            return NO_ERROR;
        }
        else
        {
            HIDE_MSG_BOX
            PrtMsg(0,emEventTypeCmsWindow, "======[CToolMenuLogic::OnDisConnect] IsDisCntMsgBoxShow = FALSE,HIDE_MSG_BOX and go on" );
        }
		
    } 

    PrtMsg(0,emEventTypeCmsWindow, "======[CToolMenuLogic::OnDisConnect]HideAllWindow and show loginDlg" );

	//调用接口，隐藏所有窗体 
    UIManagePtr->HideAllWindow(); 
	
    m_bFirstShow = TRUE;

    if ( UIDATAMGR->IsPcVersion() )
    {
        UIManagePtr->ShowWindow( g_stcStrLoginDlg, true );
    } 
    else
    {
        UIManagePtr->ShowWindow( g_stcStrMainFrameDlg, false ); 
    }

	return NO_ERROR;
}


bool CToolMenuLogic::BtnLogoutClick( const IArgs & arg )
{  
    Args_MsgBox args;
    args.pOwnerWnd = UIManagePtr->GetWindowPtr( g_stcStrToolMenuDlg );
    int nReslut = MSG_BOX( "是否要注销？",TRUE ,&args);
	if ( IDOK == nReslut )
	{
		IArgs arg("");
		DisConnect( arg );
	}
	return true;
}


bool CToolMenuLogic::BtnHideToolBarClick( const IArgs & arg )
{  
    UIManagePtr->ShowWindow( g_stcStrToolMenuDlg, false);
    return true;
}


bool CToolMenuLogic::DisConnect( const IArgs & arg  )
{
    BusinessManagePtr->DisConnect();
    return true;
}

bool CToolMenuLogic::CloseDlg( const IArgs & arg  ) 
{
    return UIManagePtr->ShowWindow( g_stcStrToolMenuDlg, false);
}


bool CToolMenuLogic::BtnSaveToFileClick( const IArgs & arg )
{
    bool bRe = UIManagePtr->SaveToFile( g_stcStrToolMenuDlg  );   
    return bRe;
}


bool CToolMenuLogic::BtnMinmizeClick( const IArgs & arg )
{ 
//     UIManagePtr->ShowWindow( g_stcStrToolMenuDlg, false );
//     UIManagePtr->ShowWindow( g_stcStrMainFrameDlg, false ); 
//     
//     return true; 

    if ( UIDATAMGR->IsPcVersion() )
    {
        UIManagePtr->ShowWindow( "", false, m_pWndTree ); 
        
         Window*  pWnd = UIManagePtr->GetWindowPtr( g_stcStrMainFrameDlg );
         pWnd->PostMessage(WM_SYSCOMMAND,SC_MINIMIZE,0); 

    }
    else
    {
        UIManagePtr->ShowWindow( g_stcStrToolMenuDlg, false );
        UIManagePtr->ShowWindow( g_stcStrMainFrameDlg, false ); 
    }
	 
    return true;
}
 

bool CToolMenuLogic::OnBtnExitClick( const IArgs & arg )
{ 
    Args_MsgBox args;
    args.pOwnerWnd = UIManagePtr->GetWindowPtr( g_stcStrToolMenuDlg );
    int nReslut = MSG_BOX( "是否要退出？",TRUE ,&args);
	if ( IDOK == nReslut )
	{
		IArgs arg("");
		ExitCmc( arg );
	}
    return true;
}

bool CToolMenuLogic::ExitCmc( const IArgs & arg )
{
    BusinessManagePtr->ShutDownCmc();
    return true;
}


bool CToolMenuLogic::OnBtnCenterCtrl( const IArgs & arg )
{
    LPCSTR className = NULL;
    LPCSTR windName = _T("centerctrl");
          
    HWND hWnd = ::FindWindow( className, windName );

    if ( !IsWindow( hWnd ) )
    {
        UIManagePtr->ShowWindow( g_stcStrMainFrameDlg, false );
        UIManagePtr->ShowWindow( g_stcStrToolMenuDlg, false );
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
    SendMessage( hWnd, WM_REDRAW_UI, 0, 0 );

    //::ShowWindow(hWnd ,SW_MAXIMIZE);  
    //::ShowWindow( hWnd, SW_RESTORE );	
    ::SetForegroundWindow( hWnd );


    //Window* pWnd = UIManagePtr->GetWindowPtr( g_stcStrMainFrameDlg );
    //pWnd->PostMessage( WM_SYSCOMMAND, SC_MINIMIZE, 0 ); 
    //最小化再显示会闪一下，直接隐藏
    UIManagePtr->ShowWindow( g_stcStrMainFrameDlg, false );
    UIManagePtr->ShowWindow( g_stcStrToolMenuDlg, false );


    return true;
}


bool CToolMenuLogic::OnWndHide( const IArgs & arg )//隐藏按钮 dyy 2013.7.4
{
    UIManagePtr->ShowWindow( g_stcStrMainMenuDlg + "/btnToolMenu", true ); //toolmenu隐藏时，显示工具箱图标
    return true;
}