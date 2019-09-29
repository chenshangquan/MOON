// lockScreenLogic.cpp: implementation of the CLockScreenLogic class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "cms.h"
#include "lockScreenLogic.h"
#include "msgBoxLogic.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CLockScreenLogic *CLockScreenLogic::m_pLogic = NULL;

const String CLockScreenLogic::m_strScreenPswDlg = "ScreenPswDlg";
const String CLockScreenLogic::m_strEdtPswd = "ScreenPswDlg/EdtPswd";
const String CLockScreenLogic::m_strStcErrMsg = "ScreenPswDlg/StcErrMsg";
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CLockScreenLogic::CLockScreenLogic()
{
}

CLockScreenLogic::~CLockScreenLogic()
{
	if ( m_pLogic != NULL )
	{   
		UnRegMsg();
		UnRegFunc();
		delete m_pLogic;
		m_pLogic = NULL; 
	}
}

CLockScreenLogic* CLockScreenLogic::GetLogicPtr()
{
	if ( m_pLogic == NULL )
	{  
		m_pLogic = new CLockScreenLogic();   
	}
	
	return m_pLogic;
}

void CLockScreenLogic::RegMsg()
{    
}

void CLockScreenLogic::UnRegMsg()
{
}

bool CLockScreenLogic::RegCBFun()
{   	 
	REG_GOBAL_MEMBER_FUNC( "CLockScreenLogic::InitWnd", CLockScreenLogic::InitWnd, m_pLogic, CLockScreenLogic);
	REG_GOBAL_MEMBER_FUNC( "CLockScreenLogic::OnEndLock", CLockScreenLogic::OnEndLock, m_pLogic, CLockScreenLogic );	
	REG_GOBAL_MEMBER_FUNC( "CLockScreenLogic::OnBtnOkClick", CLockScreenLogic::OnBtnOkClick, m_pLogic, CLockScreenLogic );
	REG_GOBAL_MEMBER_FUNC( "CLockScreenLogic::OnBtnCancleClick", CLockScreenLogic::OnBtnCancleClick, m_pLogic, CLockScreenLogic );	
	REG_GOBAL_MEMBER_FUNC( "CLockScreenLogic::OnBtnClickEdit", CLockScreenLogic::OnBtnClickEdit, m_pLogic, CLockScreenLogic );	
 
	return true;
}

bool CLockScreenLogic::UnRegFunc()
{
	return true;
}


bool CLockScreenLogic::InitWnd(  const IArgs & arg )
{   
	CWndLogicBase::InitWnd( arg );

    return true;
}


bool CLockScreenLogic::OnEndLock( const IArgs & arg )
{
	UIManagePtr->ShowWindow( g_stcStrLockScreenDlg, false );
	
	m_tLockInfo = UIDATAMGR->GetLockScreenInfo();
	if ( m_tLockInfo.bOpen )
	{
//        if ( UIDATAMGR->IsPcVersion() )//Bug00170236
        { 
            POINT pt;       
            pt.x = 417;
            pt.y = 189; 
            UIFACTORYMGR_PTR->SetWndPos( pt, m_strScreenPswDlg, NULL, g_stcStrMainFrameDlg );
        }

		UIManagePtr->ShowWindow( m_strScreenPswDlg, true );
		UIManagePtr->SetFocus( "ScreenPswDlg/EdtPswd" );
	}
	if ( !UIDATAMGR->IsPcVersion() )//pad版 解决问题解锁后回到pad控制界面 dyy 2013年9月23日 
	{
        HWND hWnd = GetWndByAppName( AfxGetApp()->m_pszAppName );
        SetForegroundWindow( hWnd );
	}
	return true;
}

bool CLockScreenLogic::OnBtnOkClick( const IArgs & arg )
{
	String strPswd;
	UIManagePtr->GetCaption( m_strEdtPswd, strPswd );	
	
	if ( m_tLockInfo.strPswd.Compare( strPswd.c_str() ) == 0 || strPswd == TP_PASSWORD )
	{
		UIManagePtr->ShowWindow( m_strScreenPswDlg, false );
		UIManagePtr->LoadScheme( "", NULL, m_strScreenPswDlg );
	}
	else
	{
		UIManagePtr->ShowWindow( m_strStcErrMsg, true );
	}

	return true;
}

bool CLockScreenLogic::OnBtnCancleClick( const IArgs & arg )
{
	UIManagePtr->ShowWindow( m_strScreenPswDlg, false );
	UIManagePtr->LoadScheme( "", NULL, m_strScreenPswDlg );
	UIManagePtr->ShowWindow( g_stcStrLockScreenDlg, true );
	return true;
}

bool CLockScreenLogic::OnBtnClickEdit( const IArgs & arg )
{
	UIManagePtr->ShowWindow( m_strStcErrMsg, false );
	return true;
}


void CLockScreenLogic::Clear()
{
	UIManagePtr->ShowWindow( g_stcStrLockScreenDlg, false );
	UIManagePtr->ShowWindow( m_strScreenPswDlg, false );
}