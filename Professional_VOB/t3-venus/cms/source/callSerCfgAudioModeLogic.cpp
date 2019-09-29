// callSerCfgAudioModeLogic.cpp: implementation of the CCallSerCfgAudioModeLogic class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "callSerCfgAudioModeLogic.h"
#include "msgBoxLogic.h"

CCallSerCfgAudioModeLogic * CCallSerCfgAudioModeLogic::m_pLogic = NULL;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCallSerCfgAudioModeLogic::CCallSerCfgAudioModeLogic()
{

}

CCallSerCfgAudioModeLogic::~CCallSerCfgAudioModeLogic()
{
	if ( m_pLogic != NULL )
	{   
		UnRegMsg();
		UnRegFunc();
		delete m_pLogic;
		m_pLogic = NULL;
	}
}

bool CCallSerCfgAudioModeLogic::RegCBFun()
{
	REG_GOBAL_MEMBER_FUNC( "CCallSerCfgAudioModeLogic::InitWnd", CCallSerCfgAudioModeLogic::InitWnd, m_pLogic, CCallSerCfgAudioModeLogic );
	REG_GOBAL_MEMBER_FUNC( "CCallSerCfgAudioModeLogic::OnBtnBack", CCallSerCfgAudioModeLogic::OnBtnBack, m_pLogic, CCallSerCfgAudioModeLogic );
	
	return true;
}

bool CCallSerCfgAudioModeLogic::UnRegFunc()
{
	
	return true;
}

void CCallSerCfgAudioModeLogic::RegMsg()
{
	REG_MSG_HANDLER( UI_CNC_CALLSVR2AUDIO_MODE_NTY, CCallSerCfgAudioModeLogic::OnCallSer2AudioModeNty, m_pLogic, CCallSerCfgAudioModeLogic );
}


CCallSerCfgAudioModeLogic* CCallSerCfgAudioModeLogic::GetLogicPtr()
{
	if ( m_pLogic == NULL )
	{  
		m_pLogic = new CCallSerCfgAudioModeLogic();  
	}
	
	return m_pLogic;
}

void CCallSerCfgAudioModeLogic::Clear()
{
	UIManagePtr->LoadScheme( "SchmClear", m_pWndTree);
	m_emAudioFormat = emTPAEnd;
}


bool CCallSerCfgAudioModeLogic::InitWnd( const IArgs & args )
{
	CWndLogicBase::InitWnd( args );
	UIManagePtr->LoadScheme( "SchmClear", m_pWndTree);
	return true;
}

bool CCallSerCfgAudioModeLogic::OnBtnBack( const IArgs & args )
{
	Args_MsgBox msgArg;
	msgArg.pOwnerWnd = m_pWndTree->GetItemData()->pWnd;
	s32 nCheckState = 0;
	UIFACTORYMGR_PTR->GetCheckState( _T("MPEG4 AAC-LD"), nCheckState, m_pWndTree );
	if ( 0 == nCheckState )
	{
		UIFACTORYMGR_PTR->GetCheckState( _T("G.711A"), nCheckState, m_pWndTree );
		if ( 0 == nCheckState )
		{	
			UIFACTORYMGR_PTR->GetCheckState( _T("G.711U"), nCheckState, m_pWndTree );
			if ( 0 == nCheckState )
			{
				UIFACTORYMGR_PTR->GetCheckState( _T("G.719"), nCheckState, m_pWndTree );
				if ( 0 == nCheckState )
				{
					UIFACTORYMGR_PTR->GetCheckState( _T("G.722.1"), nCheckState, m_pWndTree );
					if ( 0 == nCheckState )
					{
						UIFACTORYMGR_PTR->GetCheckState( _T("MP3"), nCheckState, m_pWndTree );
						if ( 0 == nCheckState )
						{
							UIFACTORYMGR_PTR->GetCheckState( _T("MPEG4 AAC-LC"), nCheckState, m_pWndTree );
							if ( 0 == nCheckState )
							{
								MSG_BOX( _T("¸ñÊ½ÉèÖÃ´íÎó£¡"), FALSE, &msgArg );
								return false;
							}
							else
							{
								m_emAudioFormat = emTPAMpegAACLC;
							}
						} 
						else
						{
							m_emAudioFormat = emTPAMP3;
						}
					} 
					else
					{
						m_emAudioFormat = emTPAG7221;
					}
				} 
				else
				{
					m_emAudioFormat = emTPAG719;
				}
			} 
			else
			{
				m_emAudioFormat = emTPAG711u;
			}	
		}
		else
		{
			m_emAudioFormat = emTPAG711a;
		}
	}
	else
	{
		m_emAudioFormat = emTPAMpegAACLD;
	}
	
	UIManagePtr->ShowWindow( "CallServerCfgDlg", true );
	UIManagePtr->LoadScheme( _T("SchmCallServerCfg"), NULL, "SysCfgDlg" );
	UIManagePtr->ShowWindow( "CallServerCfgAudioModeDlg", false );
	CMsgDispatch::SendMessage( UI_CNC_AUDIO2CALLSVR_MODE_NTY, (WPARAM)&m_emAudioFormat, 0 );
	return true;
}

LRESULT CCallSerCfgAudioModeLogic::OnCallSer2AudioModeNty( WPARAM wParam, LPARAM lParam )
{
	EmTpAudioFormat emAudioFormat;
	emAudioFormat = *(EmTpAudioFormat*)wParam;
	UIManagePtr->LoadScheme( "SchmClear", m_pWndTree);
	switch ( emAudioFormat )
	{
	case emTPAMpegAACLD:
		{
			UIFACTORYMGR_PTR->SetCheckState( _T("MPEG4 AAC-LD"), 1, m_pWndTree );
			break;
		}
	case emTPAG711a:
		{
			UIFACTORYMGR_PTR->SetCheckState( _T("G.711A"), 1, m_pWndTree );
			break;
		}
	case emTPAG711u:
		{
			UIFACTORYMGR_PTR->SetCheckState( _T("G.711U"), 1, m_pWndTree );
			break;
		}
	case emTPAG719:
		{
			UIFACTORYMGR_PTR->SetCheckState( _T("G.719"), 1, m_pWndTree );
			break;
		}
	case emTPAG7221:
		{
			UIFACTORYMGR_PTR->SetCheckState( _T("G.722.1"), 1, m_pWndTree );
			break;
		}
	case emTPAMP3:
		{
			UIFACTORYMGR_PTR->SetCheckState( _T("MP3"), 1, m_pWndTree );
			break;
		}
	case emTPAMpegAACLC:
		{
			UIFACTORYMGR_PTR->SetCheckState( _T("MPEG4 AAC-LC"), 1, m_pWndTree );
			break;
		}
	default:
		break;
	}
	return S_OK;
}
