// callservercfglogic.cpp: implementation of the CCallServerCfgLogic class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "callservercfgmodechooselogic.h"
#include "msgBoxLogic.h"

CCallServerCfgModeChooseLogic * CCallServerCfgModeChooseLogic::m_pLogic = NULL;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CCallServerCfgModeChooseLogic::CCallServerCfgModeChooseLogic()
{

}

CCallServerCfgModeChooseLogic::~CCallServerCfgModeChooseLogic()
{
	if ( m_pLogic != NULL )
	{   
		UnRegMsg();
		UnRegFunc();
		delete m_pLogic;
		m_pLogic = NULL;
	}
}


bool CCallServerCfgModeChooseLogic::RegCBFun()
{
	REG_GOBAL_MEMBER_FUNC( "CCallServerCfgModeChooseLogic::InitWnd", CCallServerCfgModeChooseLogic::InitWnd, m_pLogic, CCallServerCfgModeChooseLogic );
	REG_GOBAL_MEMBER_FUNC( "CCallServerCfgModeChooseLogic::OnBtnBack", CCallServerCfgModeChooseLogic::OnBtnBack, m_pLogic, CCallServerCfgModeChooseLogic );
//	REG_GOBAL_MEMBER_FUNC( "CCallServerCfgModeChooseLogic::OnSelectH264HP", CCallServerCfgModeChooseLogic::OnSelectH264HP, m_pLogic, CCallServerCfgModeChooseLogic );
	REG_GOBAL_MEMBER_FUNC( "CCallServerCfgModeChooseLogic::OnSelect4CIF", CCallServerCfgModeChooseLogic::OnSelect4CIF, m_pLogic, CCallServerCfgModeChooseLogic );
//	REG_GOBAL_MEMBER_FUNC( "CCallServerCfgModeChooseLogic::OnSelectH264BP", CCallServerCfgModeChooseLogic::OnSelectH264BP, m_pLogic, CCallServerCfgModeChooseLogic );
	REG_GOBAL_MEMBER_FUNC( "CCallServerCfgModeChooseLogic::OnNoSelect4CIF", CCallServerCfgModeChooseLogic::OnNoSelect4CIF, m_pLogic, CCallServerCfgModeChooseLogic );
	
	return true;
}

bool CCallServerCfgModeChooseLogic::UnRegFunc()
{
	
	return true;
}

void CCallServerCfgModeChooseLogic::RegMsg()
{
	REG_MSG_HANDLER( UI_CNC_CALLSVR2MODECHOOSE_MODE_NTY, CCallServerCfgModeChooseLogic::OnCallService2ModeChooseModeNty, m_pLogic, CCallServerCfgModeChooseLogic );
}


CCallServerCfgModeChooseLogic* CCallServerCfgModeChooseLogic::GetLogicPtr()
{
	if ( m_pLogic == NULL )
	{  
		m_pLogic = new CCallServerCfgModeChooseLogic();  
	}
	
	return m_pLogic;
}

void CCallServerCfgModeChooseLogic::Clear()
{
	UIManagePtr->LoadScheme( "SchmClear", m_pWndTree);
	memset( &m_tVidForamt, 0, sizeof(m_tVidForamt) );
}


bool CCallServerCfgModeChooseLogic::InitWnd( const IArgs & args )
{
	CWndLogicBase::InitWnd( args );
	UIManagePtr->LoadScheme( "SchmClear", m_pWndTree);
	return true;
}

bool CCallServerCfgModeChooseLogic::OnBtnBack( const IArgs & args )
{
	Args_MsgBox msgArg;
	msgArg.pOwnerWnd = m_pWndTree->GetItemData()->pWnd;
 	s32 nCheckState = 0;	
// 	UIFACTORYMGR_PTR->GetCheckState( _T("H.264 HP"), nCheckState, m_pWndTree );
// 	if ( 0 == nCheckState )
// 	{
// 		UIFACTORYMGR_PTR->GetCheckState( _T("H.264 BP"), nCheckState, m_pWndTree );
// 		if ( 0 == nCheckState )
// 		{		
// 			MSG_BOX( _T("格式设置错误！"), FALSE, &msgArg );
// 			return false;
// 		}
// 		else
// 		{
// 			m_tVidForamt.emTpVideoQualityLevel = emTPH264BP;
// 		}
// 	}
// 	else
// 	{
// 		m_tVidForamt.emTpVideoQualityLevel = emTPH264HP;
// 	}

	UIFACTORYMGR_PTR->GetCheckState( _T("1080P"), nCheckState, m_pWndTree );
	if ( 0 == nCheckState )
	{
		UIFACTORYMGR_PTR->GetCheckState( _T("720P"), nCheckState, m_pWndTree );
		if ( 0 == nCheckState )
		{		
			UIFACTORYMGR_PTR->GetCheckState( _T("4CIF"), nCheckState, m_pWndTree );
			if ( 0 == nCheckState )
			{
				MSG_BOX( _T("格式设置错误！"), FALSE, &msgArg );
				return false;
			}
			else
			{
				m_tVidForamt.emTpVideoResolution = emTPV4CIF;
			}
		}
		else
		{
			m_tVidForamt.emTpVideoResolution = emTPVHD720p1280x720;
		}
	}
	else
	{
		m_tVidForamt.emTpVideoResolution = emTPVHD1080p1920x1080;
	}

	UIFACTORYMGR_PTR->GetCheckState( _T("60fps"), nCheckState, m_pWndTree );
	if ( 0 == nCheckState )
	{
		UIFACTORYMGR_PTR->GetCheckState( _T("50fps"), nCheckState, m_pWndTree );
		if ( 0 == nCheckState )
		{	
			UIFACTORYMGR_PTR->GetCheckState( _T("30fps"), nCheckState, m_pWndTree );
			if ( 0 == nCheckState )
			{
				UIFACTORYMGR_PTR->GetCheckState( _T("25fps"), nCheckState, m_pWndTree );
				if ( 0 == nCheckState )
				{
					MSG_BOX( _T("格式设置错误！"), FALSE, &msgArg );
					return false;
				} 
				else
				{
					m_tVidForamt.wVidFrameRate = 25;
				}
			} 
			else
			{
				m_tVidForamt.wVidFrameRate = 30;
			}		
		}
		else
		{
			m_tVidForamt.wVidFrameRate = 50;
		}
	}
	else
	{
		m_tVidForamt.wVidFrameRate = 60;
	}

	UIManagePtr->ShowWindow( "CallServerCfgDlg", true );
	UIManagePtr->LoadScheme( _T("SchmCallServerCfg"), NULL, "SysCfgDlg" );
	UIManagePtr->ShowWindow( "CallServerCfgModeChooseDlg", false );
	CMsgDispatch::SendMessage( UI_CNC_MODECHOOSE2CALLSVR_MODE_NTY, (WPARAM)&m_tVidForamt, 0 );
	return true;
}

LRESULT CCallServerCfgModeChooseLogic::OnCallService2ModeChooseModeNty( WPARAM wParam, LPARAM lParam )
{
	TTPVidForamt tVidForamt = *(TTPVidForamt*)wParam;

	UIManagePtr->LoadScheme( "SchmClear", m_pWndTree);
	
// 	if ( emTPH264HP == tVidForamt.emTpVideoQualityLevel )
// 	{
// 		UIFACTORYMGR_PTR->SetCheckState( _T("H.264 HP"), 1, m_pWndTree );
// 		UIManagePtr->LoadScheme( "SchmH264HP", m_pWndTree);
// 	}
// 	else
// 	{
// 		UIFACTORYMGR_PTR->SetCheckState( _T("H.264 BP"), 1, m_pWndTree );
// 		UIManagePtr->LoadScheme( "SchmH264BP", m_pWndTree);
// 	}

	if ( emTPVHD1080p1920x1080 == tVidForamt.emTpVideoResolution )
	{
		UIFACTORYMGR_PTR->SetCheckState( _T("1080P"), 1, m_pWndTree );
		UIManagePtr->LoadScheme( "SchmNo4CIF", m_pWndTree);
	} 
	else if ( emTPVHD720p1280x720 == tVidForamt.emTpVideoResolution )
	{
		UIFACTORYMGR_PTR->SetCheckState( _T("720P"), 1, m_pWndTree );
		UIManagePtr->LoadScheme( "SchmNo4CIF", m_pWndTree);
	}
	else if ( emTPV4CIF == tVidForamt.emTpVideoResolution )
	{
		UIFACTORYMGR_PTR->SetCheckState( _T("4CIF"), 1, m_pWndTree );
		UIManagePtr->LoadScheme( "Schm4CIF", m_pWndTree);
	}

	if ( 60 == tVidForamt.wVidFrameRate )
	{
		UIFACTORYMGR_PTR->SetCheckState( _T("60fps"), 1, m_pWndTree );
	} 
	else if ( 50 == tVidForamt.wVidFrameRate )
	{
		UIFACTORYMGR_PTR->SetCheckState( _T("50fps"), 1, m_pWndTree );
	}
	else if ( 30 == tVidForamt.wVidFrameRate )
	{
		UIFACTORYMGR_PTR->SetCheckState( _T("30fps"), 1, m_pWndTree );
	}
	else if ( 25 == tVidForamt.wVidFrameRate )
	{
		UIFACTORYMGR_PTR->SetCheckState( _T("25fps"), 1, m_pWndTree );
	}

	return S_OK;
}

bool CCallServerCfgModeChooseLogic::OnSelectH264HP( const IArgs & args )
{
	UIManagePtr->LoadScheme( "SchmH264HP", m_pWndTree);
	UIFACTORYMGR_PTR->SetCheckState( _T("4CIF"), 0, m_pWndTree );
	s32 nCheckState = 0;
	UIFACTORYMGR_PTR->GetCheckState( _T("1080P"), nCheckState, m_pWndTree );
	if ( 0 == nCheckState )
	{
		UIFACTORYMGR_PTR->GetCheckState( _T("720P"), nCheckState, m_pWndTree );
		if ( 0 == nCheckState )
		{
			UIFACTORYMGR_PTR->SetCheckState( _T("1080P"), 1, m_pWndTree );
		}
	}
	return true;
}

bool CCallServerCfgModeChooseLogic::OnSelect4CIF( const IArgs & args )
{
	UIManagePtr->LoadScheme( "Schm4CIF", m_pWndTree);
	UIFACTORYMGR_PTR->SetCheckState( _T("60fps"), 0, m_pWndTree );
	UIFACTORYMGR_PTR->SetCheckState( _T("50fps"), 0, m_pWndTree );
	UIFACTORYMGR_PTR->SetCheckState( _T("30fps"), 0, m_pWndTree );
	UIFACTORYMGR_PTR->SetCheckState( _T("25fps"), 1, m_pWndTree );
	return true;
}

bool CCallServerCfgModeChooseLogic::OnSelectH264BP( const IArgs & args )
{
	UIManagePtr->LoadScheme( "SchmH264BP", m_pWndTree);
	return true;
}

bool CCallServerCfgModeChooseLogic::OnNoSelect4CIF( const IArgs & args )
{
	UIManagePtr->LoadScheme( "SchmNo4CIF", m_pWndTree);
	return true;
}
