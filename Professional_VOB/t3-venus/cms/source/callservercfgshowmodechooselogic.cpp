// callservercfglogic.cpp: implementation of the CCallServerCfgLogic class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "callservercfgshowmodechooselogic.h"
#include "msgBoxLogic.h"

CCallServerCfgShowModeChooseLogic * CCallServerCfgShowModeChooseLogic::m_pLogic = NULL;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CCallServerCfgShowModeChooseLogic::CCallServerCfgShowModeChooseLogic()
{

}

CCallServerCfgShowModeChooseLogic::~CCallServerCfgShowModeChooseLogic()
{
	if ( m_pLogic != NULL )
	{   
		UnRegMsg();
		UnRegFunc();
		delete m_pLogic;
		m_pLogic = NULL;
	}
}


bool CCallServerCfgShowModeChooseLogic::RegCBFun()
{
	REG_GOBAL_MEMBER_FUNC( "CCallServerCfgShowModeChooseLogic::InitWnd", CCallServerCfgShowModeChooseLogic::InitWnd, m_pLogic, CCallServerCfgShowModeChooseLogic );
	REG_GOBAL_MEMBER_FUNC( "CCallServerCfgShowModeChooseLogic::OnBtnBack", CCallServerCfgShowModeChooseLogic::OnBtnBack, m_pLogic, CCallServerCfgShowModeChooseLogic );
//	REG_GOBAL_MEMBER_FUNC( "CCallServerCfgShowModeChooseLogic::OnSelectH264HP", CCallServerCfgShowModeChooseLogic::OnSelectH264HP, m_pLogic, CCallServerCfgShowModeChooseLogic );
	REG_GOBAL_MEMBER_FUNC( "CCallServerCfgShowModeChooseLogic::OnSelect4CIF", CCallServerCfgShowModeChooseLogic::OnSelect4CIF, m_pLogic, CCallServerCfgShowModeChooseLogic );
//	REG_GOBAL_MEMBER_FUNC( "CCallServerCfgShowModeChooseLogic::OnSelectH264BP", CCallServerCfgShowModeChooseLogic::OnSelectH264BP, m_pLogic, CCallServerCfgShowModeChooseLogic );
	REG_GOBAL_MEMBER_FUNC( "CCallServerCfgShowModeChooseLogic::On1080and720P", CCallServerCfgShowModeChooseLogic::On1080and720P, m_pLogic, CCallServerCfgShowModeChooseLogic );
	REG_GOBAL_MEMBER_FUNC( "CCallServerCfgShowModeChooseLogic::OnSelectXGA", CCallServerCfgShowModeChooseLogic::OnSelectXGA, m_pLogic, CCallServerCfgShowModeChooseLogic );
	REG_GOBAL_MEMBER_FUNC( "CCallServerCfgShowModeChooseLogic::OnSelectSXGA", CCallServerCfgShowModeChooseLogic::OnSelectSXGA, m_pLogic, CCallServerCfgShowModeChooseLogic );
	REG_GOBAL_MEMBER_FUNC( "CCallServerCfgShowModeChooseLogic::OnSelectWXGA", CCallServerCfgShowModeChooseLogic::OnSelectWXGA, m_pLogic, CCallServerCfgShowModeChooseLogic );
	REG_GOBAL_MEMBER_FUNC( "CCallServerCfgShowModeChooseLogic::OnSelectUXGA", CCallServerCfgShowModeChooseLogic::OnSelectUXGA, m_pLogic, CCallServerCfgShowModeChooseLogic );
	
	return true;
}

bool CCallServerCfgShowModeChooseLogic::UnRegFunc()
{
	
	return true;
}

void CCallServerCfgShowModeChooseLogic::RegMsg()
{
	REG_MSG_HANDLER( UI_CNC_CALLSVR2SHOWMODECHOOSE_MODE_NTY, CCallServerCfgShowModeChooseLogic::OnCallService2ShowModeChooseModeNty, m_pLogic, CCallServerCfgShowModeChooseLogic );
}


CCallServerCfgShowModeChooseLogic* CCallServerCfgShowModeChooseLogic::GetLogicPtr()
{
	if ( m_pLogic == NULL )
	{  
		m_pLogic = new CCallServerCfgShowModeChooseLogic();  
	}
	
	return m_pLogic;
}

void CCallServerCfgShowModeChooseLogic::Clear()
{
	UIManagePtr->LoadScheme( "SchmClear", m_pWndTree);
	memset( &m_tVidForamt, 0, sizeof(m_tVidForamt) );
}


bool CCallServerCfgShowModeChooseLogic::InitWnd( const IArgs & args )
{
	CWndLogicBase::InitWnd( args );
	UIManagePtr->LoadScheme( "SchmClear", m_pWndTree);
	return true;
}

bool CCallServerCfgShowModeChooseLogic::OnBtnBack( const IArgs & args )
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
			UIFACTORYMGR_PTR->GetCheckState( _T("UXGA"), nCheckState, m_pWndTree );
			if ( 0 == nCheckState )
			{
				UIFACTORYMGR_PTR->GetCheckState( _T("WXGA"), nCheckState, m_pWndTree );
				if ( 0 == nCheckState )
				{
					UIFACTORYMGR_PTR->GetCheckState( _T("SXGA"), nCheckState, m_pWndTree );
					if ( 0 == nCheckState )
					{
						UIFACTORYMGR_PTR->GetCheckState( _T("XGA"), nCheckState, m_pWndTree );
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
							m_tVidForamt.emTpVideoResolution = emTPVGA1024x768;
						}
					} 
					else
					{
						m_tVidForamt.emTpVideoResolution = emTPVGA1280x1024;
					}
				} 
				else
				{
					m_tVidForamt.emTpVideoResolution = emTPVGA1280x800;
				}
			} 
			else
			{
				m_tVidForamt.emTpVideoResolution = emTPVGA1600x1200;
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
					UIFACTORYMGR_PTR->GetCheckState( _T("5fps"), nCheckState, m_pWndTree );
					if ( 0 == nCheckState )
					{
						MSG_BOX( _T("格式设置错误！"), FALSE, &msgArg );
						return false;
					} 
					else
					{
						m_tVidForamt.wVidFrameRate = 5;
					}
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
	UIManagePtr->ShowWindow( "CallServerCfgShowModeChooseDlg", false );
	CMsgDispatch::SendMessage( UI_CNC_SHOWMODECHOOSE2CALLSVR_MODE_NTY, (WPARAM)&m_tVidForamt, 0 );
	
	return true;
}

LRESULT CCallServerCfgShowModeChooseLogic::OnCallService2ShowModeChooseModeNty( WPARAM wParam, LPARAM lParam )
{
	TTPVidForamt tDualVidForamt = *(TTPVidForamt*)wParam;
	
	UIManagePtr->LoadScheme( "SchmClear", m_pWndTree);
	
// 	if ( emTPH264HP == tDualVidForamt.emTpVideoQualityLevel )
// 	{
// 		UIFACTORYMGR_PTR->SetCheckState( _T("H.264 HP"), 1, m_pWndTree );
// 		UIManagePtr->LoadScheme( "SchmH264HP", m_pWndTree);
// 	}
// 	else
// 	{
// 		UIFACTORYMGR_PTR->SetCheckState( _T("H.264 BP"), 1, m_pWndTree );
// 		UIManagePtr->LoadScheme( "SchmH264BP", m_pWndTree);
// 	}
	
	if ( emTPVHD1080p1920x1080 == tDualVidForamt.emTpVideoResolution )
	{
		UIFACTORYMGR_PTR->SetCheckState( _T("1080P"), 1, m_pWndTree );
		UIManagePtr->LoadScheme( "Schm1080and720P", m_pWndTree);
	} 
	else if ( emTPVHD720p1280x720 == tDualVidForamt.emTpVideoResolution )
	{
		UIFACTORYMGR_PTR->SetCheckState( _T("720P"), 1, m_pWndTree );
		UIManagePtr->LoadScheme( "Schm1080and720P", m_pWndTree);
	}
	else if ( emTPVGA1600x1200 == tDualVidForamt.emTpVideoResolution )
	{
		UIFACTORYMGR_PTR->SetCheckState( _T("UXGA"), 1, m_pWndTree );
		UIManagePtr->LoadScheme( "SchmUXGA", m_pWndTree);
	}
	else if ( emTPVGA1280x1024 == tDualVidForamt.emTpVideoResolution )
	{
		UIFACTORYMGR_PTR->SetCheckState( _T("SXGA"), 1, m_pWndTree );
		UIManagePtr->LoadScheme( "SchmSXGA", m_pWndTree);
	}
	else if ( emTPVGA1280x800 == tDualVidForamt.emTpVideoResolution )
	{
		UIFACTORYMGR_PTR->SetCheckState( _T("WXGA"), 1, m_pWndTree );
		UIManagePtr->LoadScheme( "SchmWXGA", m_pWndTree);
	}
	else if ( emTPVGA1024x768 == tDualVidForamt.emTpVideoResolution )
	{
		UIFACTORYMGR_PTR->SetCheckState( _T("XGA"), 1, m_pWndTree );
		UIManagePtr->LoadScheme( "SchmXGA", m_pWndTree);
	}
	else if ( emTPV4CIF == tDualVidForamt.emTpVideoResolution )
	{
		UIFACTORYMGR_PTR->SetCheckState( _T("4CIF"), 1, m_pWndTree );
		UIManagePtr->LoadScheme( "Schm4CIF", m_pWndTree);
	}
	
	if ( 60 == tDualVidForamt.wVidFrameRate )
	{
		UIFACTORYMGR_PTR->SetCheckState( _T("60fps"), 1, m_pWndTree );
	} 
	else if ( 50 == tDualVidForamt.wVidFrameRate )
	{
		UIFACTORYMGR_PTR->SetCheckState( _T("50fps"), 1, m_pWndTree );
	}
	else if ( 30 == tDualVidForamt.wVidFrameRate )
	{
		UIFACTORYMGR_PTR->SetCheckState( _T("30fps"), 1, m_pWndTree );
	}
	else if ( 25 == tDualVidForamt.wVidFrameRate )
	{
		UIFACTORYMGR_PTR->SetCheckState( _T("25fps"), 1, m_pWndTree );
	}
	else if ( 5 == tDualVidForamt.wVidFrameRate )
	{
		UIFACTORYMGR_PTR->SetCheckState( _T("5fps"), 1, m_pWndTree );
	}

	return 0;
}

bool CCallServerCfgShowModeChooseLogic::OnSelectH264HP( const IArgs & args )
{
	UIManagePtr->LoadScheme( "SchmH264HP", m_pWndTree);
	UIFACTORYMGR_PTR->SetCheckState( _T("4CIF"), 0, m_pWndTree );
	UIFACTORYMGR_PTR->SetCheckState( _T("UXGA"), 0, m_pWndTree );
	UIFACTORYMGR_PTR->SetCheckState( _T("SXGA"), 0, m_pWndTree );
	UIFACTORYMGR_PTR->SetCheckState( _T("WXGA"), 0, m_pWndTree );
	UIFACTORYMGR_PTR->SetCheckState( _T("XGA"), 0, m_pWndTree );
	UIFACTORYMGR_PTR->SetCheckState( _T("5fps"), 0, m_pWndTree );

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
	On1080and720P(args);

	return true;
}

bool CCallServerCfgShowModeChooseLogic::OnSelectH264BP( const IArgs & args )
{
	UIManagePtr->LoadScheme( "SchmH264BP", m_pWndTree);
	s32 nCheckState = 0;
	UIFACTORYMGR_PTR->GetCheckState( _T("1080P"), nCheckState, m_pWndTree );
	if ( 1 == nCheckState )
	{
		On1080and720P(args);
	}
	else
	{
		UIFACTORYMGR_PTR->GetCheckState( _T("720P"), nCheckState, m_pWndTree );
		if ( 1 == nCheckState )
		{
			On1080and720P(args);
		}
	}

	return true;
}

bool CCallServerCfgShowModeChooseLogic::On1080and720P( const IArgs & args )
{
	UIManagePtr->LoadScheme( "Schm1080and720P", m_pWndTree);
	s32 nCheckState = 0;	
	UIFACTORYMGR_PTR->GetCheckState( _T("5fps"), nCheckState, m_pWndTree );
	if ( 1 == nCheckState )
	{
		UIFACTORYMGR_PTR->SetCheckState( _T("60fps"), 1, m_pWndTree );
		UIFACTORYMGR_PTR->SetCheckState( _T("5fps"), 0, m_pWndTree );
	} 

	return true;
}

bool CCallServerCfgShowModeChooseLogic::OnSelect4CIF( const IArgs & args )
{
	UIManagePtr->LoadScheme( "Schm4CIF", m_pWndTree);
	UIFACTORYMGR_PTR->SetCheckState( _T("60fps"), 0, m_pWndTree );
	UIFACTORYMGR_PTR->SetCheckState( _T("50fps"), 0, m_pWndTree );
	UIFACTORYMGR_PTR->SetCheckState( _T("30fps"), 0, m_pWndTree );
	UIFACTORYMGR_PTR->SetCheckState( _T("5fps"), 0, m_pWndTree );
	UIFACTORYMGR_PTR->SetCheckState( _T("25fps"), 1, m_pWndTree );
	return true;
}

bool CCallServerCfgShowModeChooseLogic::OnSelectXGA( const IArgs & args )
{
	UIManagePtr->LoadScheme( "SchmXGA", m_pWndTree);
	UIFACTORYMGR_PTR->SetCheckState( _T("25fps"), 0, m_pWndTree );
	UIFACTORYMGR_PTR->SetCheckState( _T("50fps"), 0, m_pWndTree );
	UIFACTORYMGR_PTR->SetCheckState( _T("30fps"), 0, m_pWndTree );
	UIFACTORYMGR_PTR->SetCheckState( _T("60fps"), 0, m_pWndTree );
	UIFACTORYMGR_PTR->SetCheckState( _T("5fps"), 1, m_pWndTree );
	return true;
}

bool CCallServerCfgShowModeChooseLogic::OnSelectSXGA( const IArgs & args )
{
	UIManagePtr->LoadScheme( "SchmSXGA", m_pWndTree);
	UIFACTORYMGR_PTR->SetCheckState( _T("60fps"), 0, m_pWndTree );
	UIFACTORYMGR_PTR->SetCheckState( _T("50fps"), 0, m_pWndTree );
	UIFACTORYMGR_PTR->SetCheckState( _T("25fps"), 0, m_pWndTree );
	s32 nCheckState = 0;	
	UIFACTORYMGR_PTR->GetCheckState( _T("5fps"), nCheckState, m_pWndTree );
	if ( 0 == nCheckState )
	{
		UIFACTORYMGR_PTR->SetCheckState( _T("30fps"), 1, m_pWndTree );
	} 
	return true;
}

bool CCallServerCfgShowModeChooseLogic::OnSelectWXGA( const IArgs & args )
{
	UIManagePtr->LoadScheme( "SchmWXGA", m_pWndTree);
	UIFACTORYMGR_PTR->SetCheckState( _T("60fps"), 0, m_pWndTree );
	UIFACTORYMGR_PTR->SetCheckState( _T("50fps"), 0, m_pWndTree );
	UIFACTORYMGR_PTR->SetCheckState( _T("25fps"), 0, m_pWndTree );
	s32 nCheckState = 0;	
	UIFACTORYMGR_PTR->GetCheckState( _T("5fps"), nCheckState, m_pWndTree );
	if ( 0 == nCheckState )
	{
		UIFACTORYMGR_PTR->SetCheckState( _T("30fps"), 1, m_pWndTree );
	} 

	return true;
}

bool CCallServerCfgShowModeChooseLogic::OnSelectUXGA( const IArgs & args )
{
	UIManagePtr->LoadScheme( "SchmUXGA", m_pWndTree);
	UIFACTORYMGR_PTR->SetCheckState( _T("25fps"), 0, m_pWndTree );
	UIFACTORYMGR_PTR->SetCheckState( _T("50fps"), 0, m_pWndTree );
	UIFACTORYMGR_PTR->SetCheckState( _T("30fps"), 0, m_pWndTree );
	UIFACTORYMGR_PTR->SetCheckState( _T("5fps"), 0, m_pWndTree );
	UIFACTORYMGR_PTR->SetCheckState( _T("60fps"), 1, m_pWndTree );
	return true;
}
