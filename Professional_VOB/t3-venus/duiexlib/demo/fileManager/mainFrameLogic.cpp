#include "StdAfx.h"
#include "mainFrameLogic.h"


//控件类消息
BEGIN_CONTROL_MSG_MAP(CMainFrameLogic)
	 CTRL_MSG( DUI_MSGTYPE_CLICK, _T("backBtn"), OnCancleClick)
	  CTRL_MSG( DUI_MSGTYPE_CLICK, _T("backBtn3"), OnTestClick)
END_CONTROL_MSG_MAP()


//业务类消息
BEGIN_BUSINESS_MSG_MAP(CMainFrameLogic)
	BUSI_MSG( 1000, OnMsgNotify )
END_BUSINESS_MSG_MAP()



CMainFrameLogic::CMainFrameLogic( ):CMsgHandler( )
{

}


CMainFrameLogic::~CMainFrameLogic(void)
{
}


void CMainFrameLogic::OnCancleClick(  TNotifyUI& tMsg )
{
	 
	//CDlgManager::GetSingletonPtr()->DoCase(_T("caseTest"), _T("mainframe"));
	int n = CDlgManager::GetSingletonPtr()->DoModal(_T("testDlg"));
	 
	int i=0;
}


void CMainFrameLogic::OnTestClick(  TNotifyUI& tMsg )
{

	//CDlgManager::GetSingletonPtr()->DoCase(_T("caseTest"), _T("mainframe"));
	CDlgManager::GetSingletonPtr()->EndModal(_T("testDlg"),2);

	int i=0;
}

LRESULT CMainFrameLogic::OnMsgNotify( WPARAM wparam, LPARAM lparam )
{
	return 0;

}
