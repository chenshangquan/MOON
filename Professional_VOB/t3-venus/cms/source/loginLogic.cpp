// loginLogic.cpp: implementation of the CLoginLogic class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "cms.h"
#include "loginLogic.h"
#include "msgBoxLogic.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CLoginLogic *CLoginLogic::m_pLogic;   

//本界面中的控件
const String  CLoginLogic::m_strDlgLoginFrame = "DlgLoginFrame";
const String  CLoginLogic::m_strIpServIP = "IPCtrlServIP";
const String  CLoginLogic::m_strEdtUserName = "EdtUserName";
const String  CLoginLogic::m_strEdtPswd = "EdtPswd";
const String  CLoginLogic::m_strBtnLogin = "BtnLogin"; 
const String  CLoginLogic::m_strBtnPower = "BtnPowerOff";   
const String  CLoginLogic::m_strSwtchBtnMemPswd = "BtnScreenPswdSwitch";    ///<是否记用户密码
const String  CLoginLogic::m_strSwtchBtnAutoLog = "BtnAutoLogSwitch";  //进入上次登录会场

const String  CLoginLogic::m_strStcSysName = "StcSysName";     
 

CLoginLogic::CLoginLogic()
{
	const_cast<String&>(m_strIpServIP) = m_strDlgLoginFrame + "/" + m_strIpServIP;
	const_cast<String&>(m_strEdtUserName) = m_strDlgLoginFrame + "/" + m_strEdtUserName;
	const_cast<String&>(m_strEdtPswd) = m_strDlgLoginFrame + "/" + m_strEdtPswd;
	const_cast<String&>(m_strSwtchBtnMemPswd) = m_strDlgLoginFrame + "/" + m_strSwtchBtnMemPswd;
	const_cast<String&>(m_strSwtchBtnAutoLog) = m_strDlgLoginFrame + "/" + m_strSwtchBtnAutoLog;
	const_cast<String&>(m_strBtnLogin) = m_strDlgLoginFrame + "/" + m_strBtnLogin;
 
	m_bAutoLogin = FALSE;
	m_emAutoLoginState = emNotLogin;
}

CLoginLogic::~CLoginLogic()
{
	if ( m_pLogic != NULL )
	{   
		UnRegMsg();
		UnRegFunc();
		delete m_pLogic;
		m_pLogic = NULL; 
	}
}



CLoginLogic* CLoginLogic::GetLogicPtr()
{
	if ( m_pLogic == NULL )
	{  
		m_pLogic = new CLoginLogic();    
	}
	
	return m_pLogic;
}
 
 

void CLoginLogic::RegMsg()
{    
 	REG_MSG_HANDLER( UI_CONNECT_RSP, CLoginLogic::OnConnectRep, m_pLogic, CLoginLogic ); 
    REG_MSG_HANDLER( UI_CNS_LOGIN_TIMEOUT, CLoginLogic::OnCnsLoginTimeOut, m_pLogic, CLoginLogic );
    //REG_MSG_HANDLER( UI_UMS_LOGIN_TIMEOUT, CLoginLogic::OnUmsLoginTimeOut, m_pLogic, CLoginLogic );
	
    //REG_MSG_HANDLER( UI_UMS_DISCONNECTED, CLoginLogic::OnDisConnect, m_pLogic, CLoginLogic );
    REG_MSG_HANDLER( UI_CNS_DISCONNECTED, CLoginLogic::OnDisConnect, m_pLogic, CLoginLogic );
	REG_MSG_HANDLER( UI_CNS_CNLIST_NOTIFY, CLoginLogic::OnCnListNotify, m_pLogic, CLoginLogic ); 

}

void CLoginLogic::UnRegMsg()
{
    UN_REG_MSG_HANDLER(  UI_CONNECT_RSP, CLoginLogic::OnConnectRep, m_pLogic, CLoginLogic); 
}

bool CLoginLogic::RegCBFun()
{   	 
	REG_GOBAL_MEMBER_FUNC( "CLoginLogic::InitWnd", CLoginLogic::InitWnd, m_pLogic, CLoginLogic);
	REG_GOBAL_MEMBER_FUNC( "CLoginLogic::BtnSaveToFileClick", CLoginLogic::BtnSaveToFileClick, m_pLogic, CLoginLogic ) ; 
	REG_GOBAL_MEMBER_FUNC( "CLoginLogic::Login", CLoginLogic::Login, m_pLogic, CLoginLogic ) ;  
    REG_GOBAL_MEMBER_FUNC( "CLoginLogic::Exit", CLoginLogic::Exit, m_pLogic, CLoginLogic ) ;  
	REG_GOBAL_MEMBER_FUNC( "CLoginLogic::BtnPowerOff", CLoginLogic::BtnPowerOff, m_pLogic, CLoginLogic ) ; 	
    REG_GOBAL_MEMBER_FUNC( "CLoginLogic::BtnSetIP", CLoginLogic::BtnSetIP, m_pLogic, CLoginLogic ); 
	REG_GOBAL_MEMBER_FUNC( "CLoginLogic::BtnBackLogin", CLoginLogic::BtnBackLogin, m_pLogic, CLoginLogic );	

	return true;
}

bool CLoginLogic::UnRegFunc()
{
	return true;
}


bool CLoginLogic::InitWnd(  const IArgs & arg )
{   
	CWndLogicBase::InitWnd( arg );
	 
    return true;
}

void CLoginLogic::Clear()
{
	if ( m_pWndTree != NULL )
	{
        UIManagePtr->LoadScheme( "SchmPowerOff", m_pWndTree, m_strBtnPower );
        UIManagePtr->ShowWindow( m_strDlgLoginFrame, true, m_pWndTree ); 

        m_bAutoLogin = FALSE;
        m_emAutoLoginState = emNotLogin;
	}	
}


bool CLoginLogic::Login( const IArgs & arg )
{    
    //登录后把焦点设置在登录按钮 Bug00079681
    UIManagePtr->SetFocus( m_strBtnLogin, m_pWndTree );

	UIManagePtr->LoadScheme( "SchmLogin",m_pWndTree, m_strBtnLogin)  ;

	Value_WindowCaption valIpName;
	UIManagePtr->GetPropertyValue(valIpName, m_strIpServIP, m_pWndTree);   
	if ( valIpName.strCaption.empty() )
	{   
		UIManagePtr->LoadScheme( "", m_pWndTree, m_strBtnLogin);
		ShowPopMsgNow("IP地址不可以为空"); 
		return false;
	}

	Value_IpEditData valIp;
	UIManagePtr->GetPropertyValue(valIp, m_strIpServIP, m_pWndTree);   
	//if ( !CCallAddr::IsValidIpV4(valIp.dwIP) )
	if ( !CCallAddr::IsValidCallIP(valIp.dwIP) )
	{  
		UIManagePtr->LoadScheme( "", m_pWndTree, m_strBtnLogin);
		ShowPopMsgNow("IP地址非法");
		return false;
	}

	Value_WindowCaption valName;
	UIManagePtr->GetPropertyValue(valName,m_strEdtUserName,m_pWndTree);   
	if ( valName.strCaption.empty() )
	{   
		UIManagePtr->LoadScheme( "",m_pWndTree, m_strBtnLogin);
		ShowPopMsgNow("用户名不可以为空"); 
		return false;
	}

	Value_WindowCaption valPswd;
	UIManagePtr->GetPropertyValue(valPswd,m_strEdtPswd,m_pWndTree);   
	if ( valPswd.strCaption.empty() )
	{  
		UIManagePtr->LoadScheme( "",m_pWndTree, m_strBtnLogin);
		ShowPopMsgNow("密码不可以为空");
		return false;
	}

	bool bState = false;
	UIManagePtr->GetSwitchState( m_strSwtchBtnAutoLog, bState, m_pWndTree ); 
	if ( bState )
	{
		m_bAutoLogin = TRUE;
	}
	else
	{
		m_bAutoLogin = FALSE;
	}
	
	u16 uRe = BusinessManagePtr->Connect(valIp.dwIP,CONNETCT_SERVER_PORT,valName.strCaption.c_str(),valPswd.strCaption.c_str());
	if ( uRe != NO_ERROR )
	{   
		UIManagePtr->LoadScheme( "", m_pWndTree, m_strBtnLogin );
		HANDLE_ERROR_NOW( uRe ); 
		return false;
	}

	IArgs * pArg = NULL;
	BtnSaveToFileClick( *pArg );

	return true;
}


bool CLoginLogic::BtnSetIP( const IArgs & arg )
{
	UIManagePtr->LoadScheme( "shcmHideLoginFrm", m_pWndTree);
	UIManagePtr->ShowWindow( g_stcStrIpCfgDlg );
	return true;
}

bool CLoginLogic::BtnPowerOff( const IArgs & arg )
{
	Args_MsgBox args;
    args.pOwnerWnd = UIManagePtr->GetWindowPtr( g_stcStrLoginDlg );
    int nReslut = MSG_BOX( "是否要关机？", TRUE, &args );
	if ( IDOK == nReslut )
	{
		IArgs arg("");
		Exit( arg );
	}
	return true;
}

bool CLoginLogic::BtnBackLogin( const IArgs & arg )
{
	BusinessManagePtr->DisConnect();

	return true;
}


bool  CLoginLogic::Exit( const IArgs & arg )
{   
  //(m_pWndTree->GetItemData()->pWnd)->DestroyWindow();
//   UIManagePtr->DestoryWnd( m_pWndTree );
//   ::PostMessage(m_pWndTree->GetItemData()->pWnd->m_hWnd,WM_CLOSE,0,0);
//   ::TerminateProcess ()
//    UINT uExitCode = 0;
//   ExitProcess( uExitCode ); 
 
//	BusinessManagePtr->ShutDownOS();
   // PrtMsg( 0, emEventTypeCmsWindow, "[CLoginLogic::Exit]" );

    BusinessManagePtr->ShutDownCmc();
 //   (m_pWndTree->GetItemData()->pWnd)->DestroyWindow();
    return true;
}

bool CLoginLogic::BtnSaveToFileClick( const IArgs & arg )
{ 
    bool bState = false;
    UIManagePtr->GetSwitchState( m_strSwtchBtnMemPswd, bState, m_pWndTree ); 
    if ( !bState )
    {
		UIManagePtr->SetCaption( m_strEdtPswd, "", m_pWndTree );
    }
    
    UIManagePtr->SaveToFile( g_stcStrLoginDlg, "", "WindowCaption", TRUE );  
//     UIManagePtr->SaveToFile( g_stcStrLoginDlg, m_strEdtUserName, "WindowCaption"  );  
//     UIManagePtr->SaveToFile( g_stcStrLoginDlg, m_strEdtPswd, "WindowCaption"  );  
    UIManagePtr->SaveToFile( g_stcStrLoginDlg, m_strSwtchBtnMemPswd, "SwitchState", TRUE ); 
	UIManagePtr->SaveToFile( g_stcStrLoginDlg, m_strSwtchBtnAutoLog, "SwitchState", TRUE ); 
	return true;
}


HRESULT CLoginLogic::OnConnectRep( WPARAM wparam, LPARAM lparam )
{
    
    UIManagePtr->LoadScheme( "", m_pWndTree, m_strBtnLogin );
    
	if ( wparam == NO_ERROR )
    {     
		if ( m_bAutoLogin )
		{
			if ( m_emAutoLoginState == emReceiveCnList )
			{
				m_emAutoLoginState = emLogin;
				CMsgDispatch::SendMessage( UI_CMS_AUTOLOG_CNSINS, 0, 0 );
			}
			else
			{	
				m_emAutoLoginState = emReceiveLoginRsp;
			}			
		}
		else
		{
			UIManagePtr->ShowWindow( m_strDlgLoginFrame, false, m_pWndTree );
			UIManagePtr->ShowWindow( g_stcStrConnectCnsDlg, true );	
			UIManagePtr->LoadScheme( "SchmBackLogin", m_pWndTree, m_strBtnPower );
            UIManagePtr->LoadScheme( "", NULL, g_stcStrMainMenuDlg); //还原控件状态 eg 告警显示框 2012-3-12 by yjj
		}		
		
/*       
          UIManagePtr->ShowWindow( g_stcStrLoginDlg, FALSE ); 
 	    
          UIManagePtr->SetTransparentDlgImage( g_stcStrMainFrameDlg, g_strMainFrameSimulateBkg );	

	      UIManagePtr->LoadScheme( g_schmMainFrameCnsBkg, NULL, g_strSimulateCnsDlgName ); 

          UIManagePtr->ShowWindow( g_stcStrMainMenuDlg ); 
          UIManagePtr->ShowWindow( g_stcStrTitleBarDlg );

          CMsgDispatch::SendMessage( WM_CMS_UI_LOGIN_OK , 0, 0 );
*/             
	}
	else
    {   
        if ( !UIDATAMGR->IsPcVersion() || !UIManagePtr->IsVisible( g_stcStrLoginDlg ) )//dyy Bug00168747
        {
            return NO_ERROR;
        }

        Window*  pWnd = NULL;
        switch( lparam )
        {
           case ERR_UMC_LOGIN_UMS_PSWD_ERR:
               {
                   pWnd = UIManagePtr->GetWindowPtr( m_strEdtPswd, m_pWndTree );                  
               }
               break;
           case ERR_UMC_LOGIN_UMS_USER_ERR:
               {
                  pWnd = UIManagePtr->GetWindowPtr( m_strEdtUserName, m_pWndTree );                   
               }
               break; 
           default:
               {
                   pWnd = UIManagePtr->GetWindowPtr( m_strIpServIP, m_pWndTree );               
               }
               break; 
        }

        if ( pWnd != NULL  )
        {
            SetFocus( pWnd->GetSafeHwnd() );
        }

		HANDLE_ERROR_NOW( lparam ); 
        
	}

    return NO_ERROR;
}


HRESULT CLoginLogic::OnUmsLoginTimeOut( WPARAM wparam, LPARAM lparam)
{ 
	UIManagePtr->LoadScheme( "",m_pWndTree, m_strBtnLogin)  ;
	ShowPopMsgNow( "连接 UMS 超时 " ); 
	return NO_ERROR;
}


HRESULT CLoginLogic::OnCnsLoginTimeOut( WPARAM wparam, LPARAM lparam)
{ 
	UIManagePtr->LoadScheme( "",m_pWndTree, m_strBtnLogin)  ;
	ShowPopMsgNow( "连接 CNS 超时 " ); 
	return NO_ERROR;
}
    
HRESULT CLoginLogic::OnDisConnect( WPARAM wparam, LPARAM lparam)
{  
    UIManagePtr->LoadScheme( "",m_pWndTree, m_strBtnLogin)  ;
    return NO_ERROR;
}

HRESULT CLoginLogic::OnCnListNotify( WPARAM wparam, LPARAM lparam )
{
	if ( m_bAutoLogin )
	{
		if ( m_emAutoLoginState == emReceiveLoginRsp )
		{
			m_emAutoLoginState = emLogin;
			CMsgDispatch::SendMessage( UI_CMS_AUTOLOG_CNSINS, 0, 0 );
		}
		else
		{
			m_emAutoLoginState = emReceiveCnList;
		}	
	}
	return NO_ERROR;
}


//保存系统名到文件中
//note：供用户自定义界面使用 
void  CLoginLogic::SaveSysNameToFile( String strSysName )
{
   UIManagePtr->SetCaption( m_strStcSysName, strSysName,m_pWndTree );
   UIManagePtr->SaveToFile( g_stcStrLoginDlg, m_strStcSysName, "WindowCaption" );
}