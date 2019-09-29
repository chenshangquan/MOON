// alarminfologic.cpp: implementation of the CAlarmInfoLogic class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "alarminfologic.h"

#define MAX_ALARM_SIZE    10

CAlarmInfoLogic * CAlarmInfoLogic::m_pLogic = NULL;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CAlarmInfoLogic::CAlarmInfoLogic()
{
	m_bLoginOK = FALSE;
}

CAlarmInfoLogic::~CAlarmInfoLogic()
{

}


void CAlarmInfoLogic::RegMsg()
{    
    REG_MSG_HANDLER( WM_CMS_UI_LOGIN_OK, CAlarmInfoLogic::OnConnectOk, m_pLogic, CAlarmInfoLogic );  
    
}

bool CAlarmInfoLogic::RegCBFun()
{
	REG_GOBAL_MEMBER_FUNC( "CAlarmInfoLogic::InitWnd", CAlarmInfoLogic::InitWnd, m_pLogic, CAlarmInfoLogic );	
	REG_GOBAL_MEMBER_FUNC( "CAlarmInfoLogic::OnHideDlg", CAlarmInfoLogic::OnHideDlg, m_pLogic, CAlarmInfoLogic );
	
	return true;
}



bool CAlarmInfoLogic::UnRegFunc()
{
	return true;
}

 

CAlarmInfoLogic* CAlarmInfoLogic::GetLogicPtr()
{
	if ( m_pLogic == NULL )
	{  
		m_pLogic = new CAlarmInfoLogic();  
	}
	
	return m_pLogic;
}

bool CAlarmInfoLogic::InitWnd( const IArgs & args )
{
	CWndLogicBase::InitWnd( args );
	return true;
}

void CAlarmInfoLogic::Clear()
{  
	//m_vctAlarm.clear();

	if ( m_bLoginOK )
	{
		UIManagePtr->ShowWindow( g_stcStrAlarmInfoDlg, false );
	}
	m_bLoginOK = FALSE;
}	

HRESULT CAlarmInfoLogic::OnConnectOk( WPARAM wparam, LPARAM lparam )
{
	m_vctAlarm.clear();
	Value_TouchListAlarm touchListAlarm( &m_vctAlarm );
	UIManagePtr->SetPropertyValue( touchListAlarm , "AlarmList", m_pWndTree );

	Value_TransparentListOffset val;
	val.nOffset = 0;
	UIManagePtr->SetPropertyValue( val, "AlarmList", m_pWndTree );

	if ( UIManagePtr->IsVisible( g_stcStrAlarmInfoDlg ) )
	{
		UIManagePtr->ShowWindow( g_stcStrAlarmInfoDlg, false );
	}

	m_bLoginOK = TRUE;

	return NO_ERROR;
}

void CAlarmInfoLogic::AddMsg( CString strMsg, BOOL bShowNow )
{
	if ( m_pWndTree == NULL )
	{
		UIManagePtr->ShowWindow( g_stcStrAlarmInfoDlg, false );
	}

	if ( m_vctAlarm.size() >= MAX_ALARM_SIZE )
	{
		m_vctAlarm.pop_back();
	}
	

	//系统消息前加上时间
	SYSTEMTIME st;
    GetLocalTime(&st);  
    CString strTime = "";
    strTime.Format("%.2d:%.2d:%.2d  ", st.wHour, st.wMinute, st.wSecond );

	strMsg = strTime + strMsg;

	m_vctAlarm.insert( m_vctAlarm.begin(), (LPCTSTR)strMsg );

	Value_TouchListAlarm touchListAlarm( &m_vctAlarm );
	UIManagePtr->SetPropertyValue( touchListAlarm , "AlarmList", m_pWndTree );

	if ( bShowNow || UIManagePtr->IsVisible( g_stcStrAlarmInfoDlg ) )
	{
        ShowPosByVersion();
		UIManagePtr->ShowWindow( g_stcStrAlarmInfoDlg, true );		
	}
	else
	{
		//UIManagePtr->ShowWindow( g_stcStrMainMenuDlg + "/btnAlarm", true );
		CMsgDispatch::SendMessage( UI_CMS_SHOW_ALARM_DLG , 0 , 0 );
	}	

    //提示新消息时列表位置置顶
    Value_TransparentListOffset valueOffset;
    valueOffset.nOffset = 0;
	UIManagePtr->SetPropertyValue( valueOffset, "AlarmList", m_pWndTree );
}

bool CAlarmInfoLogic::OnHideDlg( const IArgs & args )
{
	UIManagePtr->ShowWindow( g_stcStrAlarmInfoDlg, false );
// 	if ( UIManagePtr->IsVisible( /*g_stcStrMainFrameDlg*/ g_stcStrMainMenuDlg ) )
// 	{
// 		UIManagePtr->ShowWindow( g_stcStrMainMenuDlg + "/btnAlarm", false );
// 	}
//   点击“隐藏”后，弹出框消失，但告警图标仍存在，只是在没有新的信息来之前不闪烁。
//    保留目前点击弹出框以外区域隐藏弹出框的设定。
	return true;
}

void CAlarmInfoLogic::ShowPosByVersion()
{
	//判断其是否为pc版本
//	if ( UIDATAMGR->IsPcVersion() )
	{
		POINT pt;
		Value_WindowSize val;
		UIManagePtr->GetPropertyValue( val, g_stcStrAlarmInfoDlg );
		
		Value_WindowSize valParent;
		UIManagePtr->GetPropertyValue( valParent, g_stcStrMainFrameDlg );
		
		pt.x = valParent.nWidth - val.nWidth - 19 ;
		
		pt.y = valParent.nHeight - val.nHeight - 80 ;
		UIFACTORYMGR_PTR->SetWndPos( pt, g_stcStrAlarmInfoDlg, NULL, g_stcStrMainFrameDlg );
	}
}