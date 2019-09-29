// callservercfglogic.cpp: implementation of the CCallServerCfgLogic class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "callservercfglogic.h"
#include "msgBoxLogic.h"

CCallServerCfgLogic * CCallServerCfgLogic::m_pLogic = NULL;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CCallServerCfgLogic::CCallServerCfgLogic()
{

}

CCallServerCfgLogic::~CCallServerCfgLogic()
{
	if ( m_pLogic != NULL )
	{   
		UnRegMsg();
		UnRegFunc();
		delete m_pLogic;
		m_pLogic = NULL;
	}
}


bool CCallServerCfgLogic::RegCBFun()
{
	REG_GOBAL_MEMBER_FUNC( "CCallServerCfgLogic::InitWnd", CCallServerCfgLogic::InitWnd, m_pLogic, CCallServerCfgLogic );
	REG_GOBAL_MEMBER_FUNC( "CCallServerCfgLogic::OnSysCfg", CCallServerCfgLogic::OnSysCfg, m_pLogic, CCallServerCfgLogic );
	REG_GOBAL_MEMBER_FUNC( "CCallServerCfgLogic::OnEdit", CCallServerCfgLogic::OnEdit, m_pLogic, CCallServerCfgLogic );
	REG_GOBAL_MEMBER_FUNC( "CCallServerCfgLogic::OnCancel", CCallServerCfgLogic::OnCancel, m_pLogic, CCallServerCfgLogic );
	REG_GOBAL_MEMBER_FUNC( "CCallServerCfgLogic::OnSave", CCallServerCfgLogic::OnSave, m_pLogic, CCallServerCfgLogic );
	REG_GOBAL_MEMBER_FUNC( "CCallServerCfgLogic::OnCloseDlg", CCallServerCfgLogic::OnCloseDlg, m_pLogic, CCallServerCfgLogic );
	REG_GOBAL_MEMBER_FUNC( "CCallServerCfgLogic::OnBtnCallMode", CCallServerCfgLogic::OnBtnCallMode, m_pLogic, CCallServerCfgLogic );
	REG_GOBAL_MEMBER_FUNC( "CCallServerCfgLogic::OnBtnCallShowMode", CCallServerCfgLogic::OnBtnCallShowMode, m_pLogic, CCallServerCfgLogic );
	REG_GOBAL_MEMBER_FUNC( "CCallServerCfgLogic::OnBtnAudioMode", CCallServerCfgLogic::OnBtnAudioMode, m_pLogic, CCallServerCfgLogic );
	REG_GOBAL_MEMBER_FUNC( "CCallServerCfgLogic::OnConfAdd", CCallServerCfgLogic::OnConfAdd, m_pLogic, CCallServerCfgLogic );
	//REG_GOBAL_MEMBER_FUNC( "CCallServerCfgLogic::OnConfAddHold", CCallServerCfgLogic::OnConfAdd , m_pLogic, CCallServerCfgLogic );
	REG_GOBAL_MEMBER_FUNC( "CCallServerCfgLogic::OnConfMinus", CCallServerCfgLogic::OnConfMinus, m_pLogic, CCallServerCfgLogic );
	//REG_GOBAL_MEMBER_FUNC( "CCallServerCfgLogic::OnConfMinusHold", CCallServerCfgLogic::OnConfMinus , m_pLogic, CCallServerCfgLogic );
	REG_GOBAL_MEMBER_FUNC( "CCallServerCfgLogic::OnConfHoldEnd", CCallServerCfgLogic::OnConfHoldEnd , m_pLogic, CCallServerCfgLogic );
	//REG_GOBAL_MEMBER_FUNC( "CCallServerCfgLogic::OnConfRateNoFocus", CCallServerCfgLogic::OnConfRateNoFocus, m_pLogic, CCallServerCfgLogic ); 
	REG_GOBAL_MEMBER_FUNC( "CCallServerCfgLogic::OnShowAdd", CCallServerCfgLogic::OnShowAdd, m_pLogic, CCallServerCfgLogic );
	//REG_GOBAL_MEMBER_FUNC( "CCallServerCfgLogic::OnShowAddHold", CCallServerCfgLogic::OnShowAdd , m_pLogic, CCallServerCfgLogic );
	REG_GOBAL_MEMBER_FUNC( "CCallServerCfgLogic::OnShowMinus", CCallServerCfgLogic::OnShowMinus, m_pLogic, CCallServerCfgLogic );
	//REG_GOBAL_MEMBER_FUNC( "CCallServerCfgLogic::OnShowMinusHold", CCallServerCfgLogic::OnShowMinus , m_pLogic, CCallServerCfgLogic );
	REG_GOBAL_MEMBER_FUNC( "CCallServerCfgLogic::OnShowHoldEnd", CCallServerCfgLogic::OnShowHoldEnd , m_pLogic, CCallServerCfgLogic );
	//REG_GOBAL_MEMBER_FUNC( "CCallServerCfgLogic::OnShowRateNoFocus", CCallServerCfgLogic::OnShowRateNoFocus, m_pLogic, CCallServerCfgLogic ); 
	//REG_GOBAL_MEMBER_FUNC( "CCallServerCfgLogic::OnBtnSwitchPolling", CCallServerCfgLogic::OnBtnSwitchPolling, m_pLogic, CCallServerCfgLogic );
	REG_GOBAL_MEMBER_FUNC( "CCallServerCfgLogic::OnPollAdd", CCallServerCfgLogic::OnPollAdd, m_pLogic, CCallServerCfgLogic );
	REG_GOBAL_MEMBER_FUNC( "CCallServerCfgLogic::OnPollMinus", CCallServerCfgLogic::OnPollMinus, m_pLogic, CCallServerCfgLogic ); 
 	REG_GOBAL_MEMBER_FUNC( "CCallServerCfgLogic::OnPollAddHold", CCallServerCfgLogic::OnPollAdd , m_pLogic, CCallServerCfgLogic  );
 	REG_GOBAL_MEMBER_FUNC( "CCallServerCfgLogic::OnPollMinusHold", CCallServerCfgLogic::OnPollMinus, m_pLogic, CCallServerCfgLogic );
 	REG_GOBAL_MEMBER_FUNC( "CCallServerCfgLogic::OnPollAddHoldEnd", CCallServerCfgLogic::OnBtnHoldEnd , m_pLogic, CCallServerCfgLogic );
 	REG_GOBAL_MEMBER_FUNC( "CCallServerCfgLogic::OnPollMinusHoldEnd", CCallServerCfgLogic::OnBtnHoldEnd, m_pLogic, CCallServerCfgLogic );
	REG_GOBAL_MEMBER_FUNC( "CCallServerCfgLogic::OnPollTimeChange", CCallServerCfgLogic::OnPollTimeChange, m_pLogic, CCallServerCfgLogic );
	REG_GOBAL_MEMBER_FUNC( "CCallServerCfgLogic::OnConfRateChange", CCallServerCfgLogic::OnConfRateChange, m_pLogic, CCallServerCfgLogic );
	REG_GOBAL_MEMBER_FUNC( "CCallServerCfgLogic::OnShowRateChange", CCallServerCfgLogic::OnShowRateChange, m_pLogic, CCallServerCfgLogic );
	return true;
}

bool CCallServerCfgLogic::UnRegFunc()
{
	
	return true;
}

void CCallServerCfgLogic::RegMsg()
{
	REG_MSG_HANDLER( UI_CNSTOOL_VIDEOFORMAT_IND, CCallServerCfgLogic::OnUpdateVideoFormat, m_pLogic, CCallServerCfgLogic );
	REG_MSG_HANDLER( UI_CNSTOOL_DUALVIDEOFORMAT_IND, CCallServerCfgLogic::OnUpdateDualVideoFormat, m_pLogic, CCallServerCfgLogic );
	REG_MSG_HANDLER( UI_CNC_MODECHOOSE2CALLSVR_MODE_NTY, CCallServerCfgLogic::OnModeChoose2CallServerModeNty, m_pLogic, CCallServerCfgLogic );
	REG_MSG_HANDLER( UI_CNC_SHOWMODECHOOSE2CALLSVR_MODE_NTY, CCallServerCfgLogic::OnShowModeChoose2CallServerModeNty, m_pLogic, CCallServerCfgLogic );
	REG_MSG_HANDLER( UI_CNSTOOL_CALLRATE_IND, CCallServerCfgLogic::OnUpdateCallRate, m_pLogic, CCallServerCfgLogic );
	REG_MSG_HANDLER( UI_CNSTOOL_DUALCALLRATE_IND, CCallServerCfgLogic::OnUpdateDualCallRate, m_pLogic, CCallServerCfgLogic );
	REG_MSG_HANDLER( UI_CNSTOOL_CONFDIS_IND, CCallServerCfgLogic::OnUpdateConfDis, m_pLogic, CCallServerCfgLogic );
	REG_MSG_HANDLER( UI_CNSTOOL_CONFPOOL_IND, CCallServerCfgLogic::OnUpdateConfPoll, m_pLogic, CCallServerCfgLogic );
	REG_MSG_HANDLER( UI_CNC_AUDIO2CALLSVR_MODE_NTY, CCallServerCfgLogic::OnAudioMode2CallSerNty, m_pLogic, CCallServerCfgLogic );
	REG_MSG_HANDLER( UI_CNSTOOL_AUDIOFORMAT_IND, CCallServerCfgLogic::OnUpdateAudioFormat, m_pLogic, CCallServerCfgLogic );

}

CCallServerCfgLogic* CCallServerCfgLogic::GetLogicPtr()
{
	if ( m_pLogic == NULL )
	{  
		m_pLogic = new CCallServerCfgLogic();  
	}
	
	return m_pLogic;
}

void CCallServerCfgLogic::Clear()
{
	if ( m_pWndTree != NULL )
	{
		UIManagePtr->LoadScheme( "SchmNormal", m_pWndTree);
		UIManagePtr->LoadScheme( "SchmClear", m_pWndTree);
		UIManagePtr->ShowWindow( "CallServerCfgModeChooseDlg", false );
		UIManagePtr->ShowWindow( "CallServerCfgShowModeChooseDlg", false );
		memset( &m_tVidForamt, 0, sizeof(m_tVidForamt) );
		memset( &m_tDualVidForamt, 0, sizeof(m_tDualVidForamt) );
		m_emAudioFormat = emTPAEnd;
	}
}


bool CCallServerCfgLogic::InitWnd( const IArgs & args )
{
	CWndLogicBase::InitWnd( args );

	UIManagePtr->ShowWindow( _T("CallServerCfgModeChooseDlg"), false );
	UIManagePtr->ShowWindow( _T("CallServerCfgShowModeChooseDlg"), false );
	UIManagePtr->ShowWindow( _T("CallServerCfgAudioModeDlg"), false );

	return true;
}

bool CCallServerCfgLogic::OnSysCfg( const IArgs& args )
{   
    if ( ! UIManagePtr->IsVisible( "CallServerCfgDlg/BtnEdit" ) )
    {
		int nChangeNum = 0;
		bool bChange = false;		
		//会议格式
		bChange = IsVideoFomatChange();
		if ( bChange )
		{
			nChangeNum++;
		}		
		//演示格式
		bChange = IsDualVideoFomatChange();
		if ( bChange )
		{
			nChangeNum++;
		}	
		//单屏码率
		bChange = IsCallRateChange();
		if ( bChange )
		{
			nChangeNum++;
		}	
		//演示码率
		bChange = IsDualCallRateChange();
		if ( bChange )
		{
			nChangeNum++;
		}	
		//会议讨论
		bChange = IsConfDisChange();
		if ( bChange )
		{
			nChangeNum++;
		}	
		//会议轮询
		bChange = IsConfPollChange();
		if ( bChange )
		{
			nChangeNum++;
		}		
		//音频格式
		bChange = IsAudioFormatChange();
		if ( bChange )
		{
			nChangeNum++;
		}	
		if ( nChangeNum > 0 )
		{
			CString strMsg = "是否对编辑进行保存?";
            Args_MsgBox argMsg;
            argMsg.pOwnerWnd = UIManagePtr->GetWindowPtr( "CallServerCfgDlg" );
            int nResult = MSG_BOX( strMsg, TRUE, &argMsg);
            if ( IDOK == nResult )
            {
                if ( !OnSave(args) )
                {
                    return false;
                }
            }
            else
            {
                OnCancel(args);
            }
        }
        else
        {
            UIManagePtr->LoadScheme( "SchmNormal", m_pWndTree);
        }
    }  

	UIManagePtr->LoadScheme( _T("SchmSysCfg"), NULL, _T("SysCfgDlg") );
	return true;
}

bool CCallServerCfgLogic::OnEdit( const IArgs& args )
{	
	Args_MsgBox msgArg;
	msgArg.pOwnerWnd = m_pWndTree->GetItemData()->pWnd;

	BOOL bInConf = BusinessManagePtr->IsInConf();
	if ( bInConf )
	{		
		msgArg.pOwnerWnd = UIManagePtr->GetWindowPtr( _T(""), m_pWndTree );
		MSG_BOX( "会议中，不能修改呼叫配置", FALSE, &msgArg );
		return false;
	}
	
	UIManagePtr->LoadScheme( "SchmEdit", m_pWndTree);
// 	   bool bUse = false;
//     UIFACTORYMGR_PTR->GetSwitchState( "BtnPolling", bUse, m_pWndTree );
// 	   if ( bUse )
//     {
        UIFACTORYMGR_PTR->LoadScheme( "SchmEdit", m_pWndTree, "EdtPollTime"); 
		UIFACTORYMGR_PTR->LoadScheme( "SchmEdit", m_pWndTree, "btnPDel");
		UIFACTORYMGR_PTR->LoadScheme( "SchmEdit", m_pWndTree, "btnPAdd");
//     }
//     else
//     {   
//         UIFACTORYMGR_PTR->LoadScheme( "SchmNormal", m_pWndTree,"EdtPollTime");
// 		UIFACTORYMGR_PTR->LoadScheme( "SchmNormal", m_pWndTree, "btnPDel");
// 		UIFACTORYMGR_PTR->LoadScheme( "SchmNormal", m_pWndTree, "btnPAdd");
//     }

	return true;
}

bool CCallServerCfgLogic::OnCancel( const IArgs& args )
{
	OnUpdateVideoFormat( 0, 0 );
	OnUpdateDualVideoFormat( 0, 0 );
	OnUpdateCallRate( 0, 0 );
	OnUpdateDualCallRate( 0, 0 );
	OnUpdateConfDis( 0, 0 );
	OnUpdateConfPoll( 0, 0 );
	OnUpdateAudioFormat( 0, 0 );

	UIManagePtr->LoadScheme( "SchmNormal", m_pWndTree);
	return true;
}

bool CCallServerCfgLogic::OnSave( const IArgs& args )
{   
	Args_MsgBox msgArg;
	msgArg.pOwnerWnd = UIManagePtr->GetWindowPtr( _T(""), m_pWndTree );
    BOOL bInConf = BusinessManagePtr->IsInConf();
    if ( bInConf )
    {
        msgArg.pOwnerWnd = UIManagePtr->GetWindowPtr( _T(""), m_pWndTree );
        MSG_BOX( "会议中，不能修改注呼叫配置", FALSE, &msgArg );
        return false;
    }
 
	//单屏码率
	bool bOk = RateIsDividedBy64();
	if ( !bOk )
	{
		return false;
	}
	String strCaption;
	UIManagePtr->GetCaption( "EdtConfRate", strCaption, m_pWndTree );
	u16 wVal = atoi( strCaption.c_str() );
	UIManagePtr->GetCaption( "EdtShowRate", strCaption, m_pWndTree );
	u16 wDualVal = atoi( strCaption.c_str() );
// 	if ( wVal < 64 )
// 	{
// 		MSG_BOX( "单屏码率必须为64～8192间的整数", FALSE, &msgArg );
// 		UIManagePtr->SetFocus( _T("EdtConfRate"), m_pWndTree );
// 		return false;
// 	}
// 	if ( wDualVal < 64 )
// 	{
// 		MSG_BOX( "演示码率必须为64～8192间的整数", FALSE, &msgArg );
// 		UIManagePtr->SetFocus( _T("EdtShowRate"), m_pWndTree );
// 		return false;
// 	}
	if ( wVal + wDualVal > 8192 )
	{
		MSG_BOX( "单屏码率+演示码率必须小于等于8192Kbps", FALSE, &msgArg );
		UIManagePtr->SetFocus( _T("EdtConfRate"), m_pWndTree );
		return false;
	}
	if ( wVal + wDualVal < 64 )
	{
		MSG_BOX( "单屏码率+演示码率必须大于等于64Kbps", FALSE, &msgArg );
		UIManagePtr->SetFocus( _T("EdtConfRate"), m_pWndTree );
		return false;
	}
	UIFACTORYMGR_PTR->GetCaption( "EdtPollTime", strCaption, m_pWndTree );
	wVal = atoi( strCaption.c_str() );
	if ( wVal < 5 || wVal > 7200 )
	{
		MSG_BOX( "轮询间隔为 5～7200 间的整数", FALSE, &msgArg );
		UIManagePtr->SetFocus( _T("EdtPollTime"), m_pWndTree );
		return false;
	}
	bool bSucceed = true;
	bSucceed = SaveConfRate();
	if (false == bSucceed)
	{
		return false;
	}
	//演示码率
	bSucceed = SaveShowRate();
	if (false == bSucceed)
	{
		return false;
	}
	//会议优选格式
	bSucceed = SaveVideoFormat();
	if (false == bSucceed)
	{
		return false;
	}
	//演示优选格式
	bSucceed = SaveDualVideoFormat();
	if (false == bSucceed)
	{
		return false;
	}
	//会议讨论
	bSucceed = SaveConfDis();
	if (false == bSucceed)
	{
		return false;
	}
	//会议轮询
	bSucceed = SaveConfPoll();
	if (false == bSucceed)
	{
		return false;
	}
	//音频格式
	bSucceed = SaveAudioFormat();
	if (false == bSucceed)
	{
		return false;
	}

	UIManagePtr->LoadScheme( "SchmNormal", m_pWndTree);
	return true;
}

bool CCallServerCfgLogic::OnCloseDlg( const IArgs& args )
{
	return UIManagePtr->ShowWindow( _T("CallServerCfgDlg"), false );
}

bool CCallServerCfgLogic::OnBtnCallMode( const IArgs & arg )
{
	UIManagePtr->ShowWindow( "CallServerCfgDlg", false );	
	UIManagePtr->ShowWindow( "CallServerCfgModeChooseDlg", true );
	UIManagePtr->LoadScheme( _T("SchmModeCfg"), NULL, _T("SysCfgDlg") );
	return true;
}

bool CCallServerCfgLogic::OnBtnCallShowMode( const IArgs & arg )
{
	UIManagePtr->ShowWindow( "CallServerCfgDlg", false );
	
	UIManagePtr->ShowWindow( "CallServerCfgShowModeChooseDlg", true );
	UIManagePtr->LoadScheme( _T("SchmShowModeCfg"), NULL, _T("SysCfgDlg") );
	return true;
}

bool CCallServerCfgLogic::OnBtnAudioMode( const IArgs & arg )
{
	UIManagePtr->ShowWindow( "CallServerCfgDlg", false );
	
	UIManagePtr->ShowWindow( "CallServerCfgAudioModeDlg", true );
	UIManagePtr->LoadScheme( _T("SchmAudioModeCfg"), NULL, _T("SysCfgDlg") );
	return true;	
}

LRESULT CCallServerCfgLogic::OnModeChoose2CallServerModeNty( WPARAM wParam, LPARAM lParam )
{
	m_tVidForamt = *(TTPVidForamt*)wParam;
	
	SetCallServerMode();

	return S_OK;
}

LRESULT CCallServerCfgLogic::OnShowModeChoose2CallServerModeNty( WPARAM wParam, LPARAM lParam )
{
	m_tDualVidForamt = *(TTPVidForamt*)wParam;
	
	SetCallServerShowMode();
	
	return S_OK;
}

void CCallServerCfgLogic::SetCallServerMode()
{
	CString strMode;
// 	switch ( m_tVidForamt.emTpVideoQualityLevel )
// 	{
// 	case emTPH264HP:
// 		{
// 			strMode += "H.264 HP ";
// 			break;
// 		}
// 	case emTPH264BP:
// 		{
// 			strMode += "H.264 BP ";
// 			break;
// 		}
// 	default:
// 		break;
// 	}

	switch ( m_tVidForamt.emTpVideoResolution )
	{
	case emTPVHD1080p1920x1080:
		{
			strMode += "1080P@";
			break;
		}
	case emTPVHD720p1280x720:
		{
			strMode += "720P@";
			break;
		}
	case emTPV4CIF:
		{
			strMode += "4CIF@";
			break;
		}
	default:
		break;		
	}

	switch ( m_tVidForamt.wVidFrameRate )
	{
	case 60:
		{
			strMode += "60fps";
			break;
		}
	case 50:
		{
			strMode += "50fps";
			break;
		}
	case 30:
		{
			strMode += "30fps";
			break;
		}
	case 25:
		{
			strMode += "25fps";
			break;
		}
	default:
		break;		
	}

	UIFACTORYMGR_PTR->SetCaption( ("ExCallModeReal"), (LPCTSTR)strMode, m_pWndTree );
}

void CCallServerCfgLogic::SetCallServerShowMode()
{
	CString strMode;
// 	switch ( m_tDualVidForamt.emTpVideoQualityLevel )
// 	{
// 	case emTPH264HP:
// 		{
// 			strMode += "H.264 HP ";
// 			break;
// 		}
// 	case emTPH264BP:
// 		{
// 			strMode += "H.264 BP ";
// 			break;
// 		}
// 	default:
// 		break;
// 	}

	
	switch ( m_tDualVidForamt.emTpVideoResolution )
	{
	case emTPVHD1080p1920x1080:
		{
			strMode += "1080P@";
			break;
		}
	case emTPVHD720p1280x720:
		{
			strMode += "720P@";
			break;
		}
	case emTPVGA1600x1200:
		{
			strMode += "UXGA@";
			break;
		}
	case emTPVGA1280x800:
		{
			strMode += "WXGA@";
			break;
		}
	case emTPVGA1280x1024:
		{
			strMode += "SXGA@";
			break;
		}
	case emTPVGA1024x768:
		{
			strMode += "XGA@";
			break;
		}
	case emTPV4CIF:
		{
			strMode += "4CIF@";
			break;
		}
	default:
		break;		
	}
	
	switch ( m_tDualVidForamt.wVidFrameRate )
	{
	case 60:
		{
			strMode += "60fps";
			break;
		}
	case 50:
		{
			strMode += "50fps";
			break;
		}
	case 30:
		{
			strMode += "30fps";
			break;
		}
	case 25:
		{
			strMode += "25fps";
			break;
		}
	case 5:
		{
			strMode += "5fps";
			break;
		}
	default:
		break;		
	}
	
	UIFACTORYMGR_PTR->SetCaption( ("ExCallShowModeReal"), (LPCTSTR)strMode, m_pWndTree );
}

HRESULT CCallServerCfgLogic::OnUpdateVideoFormat( WPARAM wparam, LPARAM lparam )
{
	ComInterface->GetVideoFormatInfo(m_tVidForamt);
	SetCallServerMode();
	CMsgDispatch::SendMessage( UI_CNC_CALLSVR2MODECHOOSE_MODE_NTY, (WPARAM)&m_tVidForamt, 0 );
	return S_OK;
}

HRESULT CCallServerCfgLogic::OnUpdateDualVideoFormat( WPARAM wparam, LPARAM lparam )
{
	ComInterface->GetDualVideoFormatInfo(m_tDualVidForamt);
	SetCallServerShowMode();
	CMsgDispatch::SendMessage( UI_CNC_CALLSVR2SHOWMODECHOOSE_MODE_NTY, (WPARAM)&m_tDualVidForamt, 0 );
	return S_OK;
}

bool CCallServerCfgLogic::OnConfMinus( const IArgs& args )
{
	String  strConfRate;
    UIManagePtr->GetCaption( "EdtConfRate", strConfRate, m_pWndTree );
    
    s32 nRate  = atoi( strConfRate.c_str() );
	if( nRate <= 64 )
	{
        nRate = 64;		
	}
	else
	{
		u16 wRateMultiple = nRate / 1024;
		u16 wRateExtra = nRate % 1024;
		if ( 0 == wRateExtra )
		{
			nRate = 1024 * ( wRateMultiple - 1);//nRate - 1024;	
		}
		else
		{
			nRate = 1024 * wRateMultiple;
		}
        
		if( nRate <= 64 )
		{
			nRate = 64;		
		}
	}

	s8 pRate[5] = {0} ;
	sprintf( pRate, "%d", nRate );
	UIManagePtr->SetCaption( "EdtConfRate", pRate, m_pWndTree );
	return true;
}

bool CCallServerCfgLogic::OnConfAdd( const IArgs& args )
{
	String  strConfRate;
    UIManagePtr->GetCaption( "EdtConfRate", strConfRate, m_pWndTree );
    
    s32 nRate  = atoi( strConfRate.c_str() );
	if( nRate >= 8192 )
	{
        nRate = 8192;		
	}
	else
	{
		u16 wRateMultiple = nRate / 1024;
        nRate = 1024 * ( wRateMultiple + 1);//nRate + 1024;
		if( nRate >= 8192 )
		{
			nRate = 8192;		
		}
	}

	s8 pRate[5] = {0} ;
	sprintf( pRate, "%d", nRate );
	UIManagePtr->SetCaption( "EdtConfRate", pRate, m_pWndTree );
	return true;
}

bool CCallServerCfgLogic::OnConfRateNoFocus( const IArgs& args )
{
//	bool bIs = UIManagePtr->IsVisible( "", m_pWndTree );
// 	if ( !bIs )
// 	{
// 		UIManagePtr->SetCaption( "EdtConfRate", "8192", m_pWndTree );
// 		return false;
// 	}
	String  strConfRate;
	Args_MsgBox msgArg;
	msgArg.pOwnerWnd = UIManagePtr->GetWindowPtr( "", m_pWndTree );
    UIManagePtr->GetCaption( "EdtConfRate", strConfRate, m_pWndTree );
	s32 nRate = atoi( strConfRate.c_str() );
	u16 wValue = nRate%64;
	if ( wValue != 0 && nRate <= 8192 )
	{	
		MSG_BOX("码率必须为64的倍数", FALSE, &msgArg );	
// 		if ( wValue <= 32 )
// 		{
// 			nRate -= wValue;
// 		} 
// 		else
// 		{
			nRate += 64 - wValue;
//		}
		s8 pRate[5] = {0} ;
		sprintf( pRate, "%d", nRate );
		UIManagePtr->SetCaption( "EdtConfRate", pRate, m_pWndTree );
		UIManagePtr->SetFocus( _T("EdtConfRate"), m_pWndTree );
	}
	
	return true;
}

bool CCallServerCfgLogic::OnShowMinus( const IArgs& args )
{
	String  strShowRate;
    UIManagePtr->GetCaption( "EdtShowRate", strShowRate, m_pWndTree );
    
    s32 nRate  = atoi( strShowRate.c_str() );
	if( nRate <= 0 )
	{
        nRate = 0;		
	}
	else
	{
		u16 wRateMultiple = nRate / 1024;
		u16 wRateExtra = nRate % 1024;
		if ( 0 == wRateExtra )
		{
			nRate = 1024 * ( wRateMultiple - 1);//nRate - 1024;	
		}
		else
		{
			nRate = 1024 * wRateMultiple;
		}
	}

	s8 pRate[5] = {0} ;
	sprintf( pRate, "%d", nRate );
	UIManagePtr->SetCaption( "EdtShowRate", pRate, m_pWndTree );
	return true;
}

bool CCallServerCfgLogic::OnShowAdd( const IArgs& args )
{
	String  strShowRate;
    UIManagePtr->GetCaption( "EdtShowRate", strShowRate, m_pWndTree );
    
    s32 nRate  = atoi( strShowRate.c_str() );
	if( nRate >= 8192 )
	{
        nRate = 8192;		
	}
	else
	{
		u16 wRateMultiple = nRate / 1024;
        nRate = 1024 * ( wRateMultiple + 1);//nRate + 1024;
		if( nRate >= 8192 )
		{
			nRate = 8192;		
		}
	}

	s8 pRate[5] = {0} ;
	sprintf( pRate, "%d", nRate );
	UIManagePtr->SetCaption( "EdtShowRate", pRate, m_pWndTree );
	return true;
}

bool CCallServerCfgLogic::OnShowRateNoFocus( const IArgs& args )
{
	String  strShowRate;
	Args_MsgBox msgArg;
	msgArg.pOwnerWnd = UIManagePtr->GetWindowPtr( "", m_pWndTree );
    UIManagePtr->GetCaption( "EdtShowRate", strShowRate, m_pWndTree );
	s32 nRate = atoi( strShowRate.c_str() );
	u16 wValue = nRate%64;
	if ( wValue != 0 && nRate <= 8192 )
	{		
		MSG_BOX("码率必须为64的倍数", FALSE, &msgArg );
		if ( wValue <= 32 )
		{
			nRate -= wValue;
		} 
		else
		{
			nRate += 64 - wValue;
		}
		s8 pRate[5] = {0} ;
		sprintf( pRate, "%d", nRate );
		UIManagePtr->SetCaption( "EdtShowRate", pRate, m_pWndTree );
		UIManagePtr->SetFocus( _T("EdtShowRate"), m_pWndTree );
	}
	
	return true;
}

bool CCallServerCfgLogic::OnBtnSwitchPolling( const IArgs& args )
{
	bool bUse = false;
    UIFACTORYMGR_PTR->GetSwitchState( "BtnPolling", bUse, m_pWndTree );
	if ( bUse )
    {
        UIFACTORYMGR_PTR->LoadScheme( "SchmEdit", m_pWndTree, "EdtPollTime"); 
		UIFACTORYMGR_PTR->LoadScheme( "SchmEdit", m_pWndTree, "btnPDel");
		UIFACTORYMGR_PTR->LoadScheme( "SchmEdit", m_pWndTree, "btnPAdd");
    }
    else
    {   
        UIFACTORYMGR_PTR->LoadScheme( "SchmNormal", m_pWndTree,"EdtPollTime");
		UIFACTORYMGR_PTR->LoadScheme( "SchmNormal", m_pWndTree, "btnPDel");
		UIFACTORYMGR_PTR->LoadScheme( "SchmNormal", m_pWndTree, "btnPAdd");
    }

	return true;	
}

bool CCallServerCfgLogic::OnPollMinus( const IArgs& args )
{
	String  strSecond ;	
    UIManagePtr->GetCaption( "EdtPollTime", strSecond, m_pWndTree );
    
    int nSec = atoi( strSecond.c_str() );
	nSec -= 5;
	if ( nSec < 5 )
	{
// 		Args_MsgBox msgArg;
// 		msgArg.pOwnerWnd = UIManagePtr->GetWindowPtr( _T(""), m_pWndTree );
// 		MSG_BOX( "轮询间隔为 5～7200 间的整数", FALSE, &msgArg );
// 		UIManagePtr->SetFocus( _T("EdtPollTime"), m_pWndTree );
// 		return false;
		nSec = 5;
	}
	s8 pSec[5] = {0};
	sprintf( pSec, "%d", nSec );
	UIManagePtr->SetCaption( "EdtPollTime", pSec, m_pWndTree );
	return true;
}

bool CCallServerCfgLogic::OnPollAdd( const IArgs& args )
{
	String  strSecond ;	
    UIManagePtr->GetCaption( "EdtPollTime", strSecond, m_pWndTree );
    
    int nSec = atoi( strSecond.c_str() );
	nSec += 5;
	if ( nSec > 7200 )
	{
// 		Args_MsgBox msgArg;
// 		msgArg.pOwnerWnd = UIManagePtr->GetWindowPtr( _T(""), m_pWndTree );
// 		MSG_BOX( "轮询间隔为 5～7200 间的整数", FALSE, &msgArg );
// 		UIManagePtr->SetFocus( _T("EdtPollTime"), m_pWndTree );
// 		return false;
		nSec = 7200;
	}
	s8 pSec[5] = {0};
	sprintf( pSec, "%d", nSec );
	UIManagePtr->SetCaption( "EdtPollTime", pSec, m_pWndTree );
	return true;
}

bool CCallServerCfgLogic::OnBtnHoldEnd( const IArgs& args )
{
	Window* pWnd;
    pWnd = UIManagePtr->GetWindowPtr( "EdtPollTime", m_pWndTree );
	if ( pWnd )
	{
		pWnd->SetFocus();
		CEdit* pEd = ( CEdit* )pWnd;
		pEd->SetSel( 0, -1 );
	}
	return 0;
}

HRESULT CCallServerCfgLogic::OnUpdateCallRate( WPARAM wparam, LPARAM lparam )
{
	u16 wCallRate;
	ComInterface->GetCallRateInfo( wCallRate );
	s8 chCallRate[8] = {0};
	sprintf( chCallRate, "%u", wCallRate );
	
	UIManagePtr->SetCaption( "EdtConfRate", chCallRate, m_pWndTree );
	return S_OK;
}

HRESULT CCallServerCfgLogic::OnUpdateDualCallRate( WPARAM wparam, LPARAM lparam )
{
	u16 wDualCallRate;
	ComInterface->GetDualCallRateInfo( wDualCallRate );
	s8 chDualCallRate[8] = {0};
	sprintf( chDualCallRate, "%u", wDualCallRate );

	UIManagePtr->SetCaption( "EdtShowRate", chDualCallRate, m_pWndTree );
	return S_OK;
}

HRESULT CCallServerCfgLogic::OnUpdateConfDis( WPARAM wparam, LPARAM lparam )
{
	BOOL bDis;
	ComInterface->GetConfDisInfo( bDis );
	UIManagePtr->SetSwitchState( "BtnDiscuss", bDis, m_pWndTree );
	return S_OK;
}

HRESULT CCallServerCfgLogic::OnUpdateConfPoll( WPARAM wparam, LPARAM lparam )
{
	TTPPollInfo tPollInfo;
	ComInterface->GetConfPollInfo( tPollInfo );
	
	s8 chPollTime[8] = {0};
	sprintf( chPollTime, "%u", tPollInfo.wPollExpire );
	UIManagePtr->SetCaption( "EdtPollTime", chPollTime, m_pWndTree);
	
	UIFACTORYMGR_PTR->SetSwitchState( "BtnPolling", tPollInfo.bIsPoll, m_pWndTree );

	return S_OK;
}

bool CCallServerCfgLogic::OnPollTimeChange( const IArgs& args )
{
	String strCaption;
	UIFACTORYMGR_PTR->GetCaption( "EdtPollTime", strCaption, m_pWndTree );
	u16 wVal = atoi( strCaption.c_str() );
	if ( wVal > 7200 )
	{
		wVal = 7200;
		UIFACTORYMGR_PTR->SetCaption( "EdtPollTime", "7200", m_pWndTree);
	
		UIFACTORYMGR_PTR->SetEditFocusEnd( "EdtPollTime", m_pWndTree ); 
	}
	return true;
}

bool CCallServerCfgLogic::OnConfRateChange( const IArgs& args )
{
	String strCaption;
	UIFACTORYMGR_PTR->GetCaption( "EdtConfRate", strCaption, m_pWndTree );
	u32 nVal = atoi( strCaption.c_str() );
	if ( nVal > 8192 )
	{
		nVal = 8192;
		UIFACTORYMGR_PTR->SetCaption( "EdtConfRate", "8192", m_pWndTree );
		UIFACTORYMGR_PTR->SetEditFocusEnd( "EdtConfRate", m_pWndTree ); 
	}
	return true;
}

bool CCallServerCfgLogic::OnShowRateChange( const IArgs& args )
{
	String strCaption;
	UIFACTORYMGR_PTR->GetCaption( "EdtShowRate", strCaption, m_pWndTree );
	u32 nVal = atoi( strCaption.c_str() );
	if ( nVal > 8192 )
	{
		nVal = 8192;
		UIFACTORYMGR_PTR->SetCaption( "EdtShowRate", "8192", m_pWndTree );
		UIFACTORYMGR_PTR->SetEditFocusEnd( "EdtShowRate", m_pWndTree ); 
	}
	return true;
}

bool CCallServerCfgLogic::RateIsDividedBy64()
{
	String  strRate;
	Args_MsgBox msgArg;
	msgArg.pOwnerWnd = UIManagePtr->GetWindowPtr( "", m_pWndTree );

	BOOL bConf = FALSE;
    UIManagePtr->GetCaption( "EdtConfRate", strRate, m_pWndTree );
	s32 nConfRate = atoi( strRate.c_str() );
	if ( nConfRate >= 0 && nConfRate < 64 )
	{
		nConfRate = 64;
		MSG_BOX("单屏码率必须为64～8192间的整数", FALSE, &msgArg );
		s8 pRate[5] = {0} ;
		sprintf( pRate, "%d", nConfRate );
		UIManagePtr->SetCaption( "EdtConfRate", pRate, m_pWndTree );
		UIManagePtr->SetFocus( _T("EdtConfRate"), m_pWndTree );
		return false;			
	} 

	u16 wConfValue = nConfRate%64;
	if ( wConfValue != 0 && nConfRate <= 8192 )
	{	
		bConf = TRUE;
		if ( wConfValue <= 32 )
		{
			nConfRate -= wConfValue;
		} 
		else
		{
			nConfRate += 64 - wConfValue;
		}
	}

	BOOL bShow = FALSE;
    UIManagePtr->GetCaption( "EdtShowRate", strRate, m_pWndTree );
	s32 nRate = atoi( strRate.c_str() );
// 	if ( nRate >= 0 && nRate < 64 )
// 	{
// 		nRate = 64;
// 		MSG_BOX("演示码率必须为0～8192间的整数", FALSE, &msgArg );
// 		s8 pRate[5] = {0} ;
// 		sprintf( pRate, "%d", nRate );
// 		UIManagePtr->SetCaption( "EdtShowRate", pRate, m_pWndTree );
// 		UIManagePtr->SetFocus( _T("EdtShowRate"), m_pWndTree );
// 		return false;			
// 	}
	u16 wValue = nRate%64;
	if ( wValue != 0 && nRate <= 8192 )
	{	
		bShow = TRUE;
		if ( wValue <= 32 )
		{
			nRate -= wValue;
		} 
		else
		{
			nRate += 64 - wValue;
		}
	}

	if ( bConf == TRUE && bShow == FALSE )
	{
		MSG_BOX("码率必须为64的倍数", FALSE, &msgArg );
		s8 pConfRate[5] = {0} ;
		sprintf( pConfRate, "%d", nConfRate );
		UIManagePtr->SetCaption( "EdtConfRate", pConfRate, m_pWndTree );
		UIManagePtr->SetFocus( _T("EdtConfRate"), m_pWndTree );
		return false;
	} 
	else if ( bConf == FALSE && bShow == TRUE )
	{
		MSG_BOX("码率必须为64的倍数", FALSE, &msgArg );
		s8 pRate[5] = {0} ;
		sprintf( pRate, "%d", nRate );
		UIManagePtr->SetCaption( "EdtShowRate", pRate, m_pWndTree );
		UIManagePtr->SetFocus( _T("EdtShowRate"), m_pWndTree );
		return false;
	}
	else if ( bConf == TRUE && bShow == TRUE )
	{
		MSG_BOX("码率必须为64的倍数", FALSE, &msgArg );

		s8 pConfRate[5] = {0} ;
		sprintf( pConfRate, "%d", nConfRate );
		UIManagePtr->SetCaption( "EdtConfRate", pConfRate, m_pWndTree );

		s8 pRate[5] = {0} ;
		sprintf( pRate, "%d", nRate );
		UIManagePtr->SetCaption( "EdtShowRate", pRate, m_pWndTree );

		UIManagePtr->SetFocus( _T("EdtConfRate"), m_pWndTree );
		return false;
	}

	return true;
}

LRESULT CCallServerCfgLogic::OnAudioMode2CallSerNty( WPARAM wParam, LPARAM lParam )
{
	m_emAudioFormat = *(EmTpAudioFormat*)wParam;
	
	SetAudioFormat();
	
	return S_OK;
}

void CCallServerCfgLogic::SetAudioFormat()
{
	CString strFormat = "";
	switch ( m_emAudioFormat )
	{
	case emTPAMpegAACLD:
		{
			strFormat += "MPEG4 AAC-LD单声道";
			break;
		}
	case emTPAG711a:
		{
			strFormat += "G.711A";
			break;
		}
	case emTPAG711u:
		{
			strFormat += "G.711U";
			break;
		}
	case emTPAG719:
		{
			strFormat += "G.719";
			break;
		}
	case emTPAG7221:
		{
			strFormat += "G.722.1 Annex C Polycom Siren14";
			break;
		}
	case emTPAMP3:
		{
			strFormat += "MP3";
			break;
		}
	case emTPAMpegAACLC:
		{
			strFormat += "MPEG4 AAC-LC单声道";
			break;
		}
	default:
		break;
	}
	UIFACTORYMGR_PTR->SetCaption( ("ExAudioModeReal"), (LPCTSTR)strFormat, m_pWndTree );
}

HRESULT CCallServerCfgLogic::OnUpdateAudioFormat( WPARAM wparam, LPARAM lparam )
{
	m_emAudioFormat = ComInterface->GetAudioFormatInfo();
	SetAudioFormat();
	CMsgDispatch::SendMessage( UI_CNC_CALLSVR2AUDIO_MODE_NTY, (WPARAM)&m_emAudioFormat, 0 );	
	return S_OK;
}

bool CCallServerCfgLogic::SaveConfRate()
{
	bool bChange = false;
	bChange = IsCallRateChange();
	if ( bChange )
	{
		String strCaption;
		UIManagePtr->GetCaption( "EdtConfRate", strCaption, m_pWndTree );
		u16 wVal = atoi( strCaption.c_str() );
		u16 wRet = ComInterface->CallRateCmd(wVal);
		if (wRet != NO_ERROR)
		{
			Args_MsgBox msgArg;
			msgArg.pOwnerWnd = UIManagePtr->GetWindowPtr( _T(""), m_pWndTree );
			MSG_BOX( "保存单屏码率请求发送失败", FALSE, &msgArg );
			UIManagePtr->SetFocus( _T("EdtConfRate"), m_pWndTree );
			return false;
		}
	} 
	return true;
}

bool CCallServerCfgLogic::SaveShowRate()
{
	bool bChange = false;
	bChange = IsDualCallRateChange();
	if ( bChange )
	{
		String strCaption;
		UIManagePtr->GetCaption( "EdtShowRate", strCaption, m_pWndTree );
		u16 wDualVal = atoi( strCaption.c_str() );
		u16 wRet = ComInterface->DualCallRateCmd(wDualVal);
		if (wRet != NO_ERROR)
		{
			Args_MsgBox msgArg;
			msgArg.pOwnerWnd = UIManagePtr->GetWindowPtr( _T(""), m_pWndTree );
			MSG_BOX( "保存演示码率请求发送失败", FALSE, &msgArg );
			UIManagePtr->SetFocus( _T("EdtShowRate"), m_pWndTree );
			return false;
		}
	} 
	return true;
}

bool CCallServerCfgLogic::SaveVideoFormat()
{
	bool bChange = false;
	bChange = IsVideoFomatChange();
	if ( bChange )
	{
		u16 wRet = ComInterface->VideoFormatCmd( m_tVidForamt );
		if (wRet != NO_ERROR)
		{
			Args_MsgBox msgArg;
			msgArg.pOwnerWnd = UIManagePtr->GetWindowPtr( _T(""), m_pWndTree );
			MSG_BOX( "保存会议优选格式请求发送失败", FALSE, &msgArg );
			return false;
		}
	} 
	return true;
}

bool CCallServerCfgLogic::SaveDualVideoFormat()
{
	bool bChange = false;
	bChange = IsDualVideoFomatChange();
	if ( bChange )
	{
		u16 wRet = ComInterface->DualVideoFormatCmd( m_tDualVidForamt );
		if (wRet != NO_ERROR)
		{
			Args_MsgBox msgArg;
			msgArg.pOwnerWnd = UIManagePtr->GetWindowPtr( _T(""), m_pWndTree );
			MSG_BOX( "保存演示优选格式请求发送失败", FALSE, &msgArg );
			return false;
		}
	} 
	return true;
}

bool CCallServerCfgLogic::SaveConfDis()
{
	bool bChange = false;
	bChange = IsConfDisChange();
	if ( bChange )
	{
		bool bUse = false;
		UIFACTORYMGR_PTR->GetSwitchState( "BtnDiscuss", bUse, m_pWndTree );
		u16 wRet = ComInterface->ConfDisCmd(bUse);
		if (wRet != NO_ERROR)
		{
			Args_MsgBox msgArg;
			msgArg.pOwnerWnd = UIManagePtr->GetWindowPtr( _T(""), m_pWndTree );
			MSG_BOX( "保存会议讨论设置请求发送失败", FALSE, &msgArg );
			return false;
		}
	} 
	return true;
}

bool CCallServerCfgLogic::SaveConfPoll()
{
	bool bChange = false;
	bChange = IsConfPollChange();
	if ( bChange )
	{
		bool bUse = false;
		String strCaption;
		TTPPollInfo tPollInfo;
		UIFACTORYMGR_PTR->GetSwitchState( "BtnPolling", bUse, m_pWndTree );
		UIFACTORYMGR_PTR->GetCaption( "EdtPollTime", strCaption, m_pWndTree );
		tPollInfo.wPollExpire = atoi( strCaption.c_str() );
		tPollInfo.bIsPoll = (BOOL)bUse;
		u16 wRet = ComInterface->ConfPollCmd(tPollInfo);
		if (wRet != NO_ERROR)
		{
			Args_MsgBox msgArg;
			msgArg.pOwnerWnd = UIManagePtr->GetWindowPtr( _T(""), m_pWndTree );
			MSG_BOX( "保存会议轮询设置请求发送失败", FALSE, &msgArg );
			UIManagePtr->SetFocus( _T("EdtPollTime"), m_pWndTree );
			return false;
		}
	} 
	return true;
}

bool CCallServerCfgLogic::SaveAudioFormat()
{
	bool bChange = false;
	bChange = IsAudioFormatChange();
	if ( bChange )
	{
		u16 wRet = ComInterface->AudioFormatCmd(m_emAudioFormat);
		if (wRet != NO_ERROR)
		{
			Args_MsgBox msgArg;
			msgArg.pOwnerWnd = UIManagePtr->GetWindowPtr( _T(""), m_pWndTree );
			MSG_BOX( "保存音频格式设置请求发送失败", FALSE, &msgArg );
			return false;
		}
	}
	return true;
}

bool CCallServerCfgLogic::IsVideoFomatChange()
{
	bool bChange = false;
	TTPVidForamt tVidForamt;
	ComInterface->GetVideoFormatInfo(tVidForamt);
	if ( m_tVidForamt.emTpVideoResolution != tVidForamt.emTpVideoResolution || m_tVidForamt.emTpVideoQualityLevel != tVidForamt.emTpVideoQualityLevel
		|| m_tVidForamt.wVidFrameRate != tVidForamt.wVidFrameRate)
	{
		bChange = true;	
	}	
	return bChange;
}

bool CCallServerCfgLogic::IsDualVideoFomatChange()
{
	bool bChange = false;
	TTPVidForamt tDualVidForamt;
	ComInterface->GetDualVideoFormatInfo(tDualVidForamt);
	if ( m_tDualVidForamt.emTpVideoResolution != tDualVidForamt.emTpVideoResolution || m_tDualVidForamt.emTpVideoQualityLevel != tDualVidForamt.emTpVideoQualityLevel
		|| m_tDualVidForamt.wVidFrameRate != tDualVidForamt.wVidFrameRate)
	{
		bChange = true;	
	}	
	return bChange;
}

bool CCallServerCfgLogic::IsCallRateChange()
{
	bool bChange = false;
	String strCaption;
	u16 wCallRate;
	ComInterface->GetCallRateInfo( wCallRate );		
	UIManagePtr->GetCaption( "EdtConfRate", strCaption, m_pWndTree );
	u32 nVal = atoi( strCaption.c_str() );
	if ( wCallRate != nVal )
	{
		bChange = true;
	}
	return bChange;
}

bool CCallServerCfgLogic::IsDualCallRateChange()
{
	bool bChange = false;
	String strCaption;
	u16 wShowRate;
	ComInterface->GetDualCallRateInfo( wShowRate );
	UIManagePtr->GetCaption( "EdtShowRate", strCaption, m_pWndTree );
	u32 nVal = atoi( strCaption.c_str() );
	//演示码率为0，再删成空,edit框内值置为0，防止能保存空值 Bug00186546 
	if ( strCaption.empty() )
	{
		s8 pVal[5] = {0} ;
		sprintf( pVal, "%d", nVal );
		UIManagePtr->SetCaption( "EdtShowRate", pVal, m_pWndTree );
	}
	if ( wShowRate != nVal ) 
	{
		bChange = true;
	}	
	return bChange;
}

bool CCallServerCfgLogic::IsConfDisChange()
{
	bool bChange = false; 
	bool bUse = false;
	BOOL bDis;
	ComInterface->GetConfDisInfo( bDis );		
	UIFACTORYMGR_PTR->GetSwitchState( "BtnDiscuss", bUse, m_pWndTree );
	if ( bDis != (BOOL)bUse )
	{
		bChange = true;
	}
	return bChange;
}

bool CCallServerCfgLogic::IsConfPollChange()
{
	bool bChange = false; 
	bool bUse = false;
	String strCaption;
	TTPPollInfo tPollInfo;
	ComInterface->GetConfPollInfo( tPollInfo );
	UIFACTORYMGR_PTR->GetSwitchState( "BtnPolling", bUse, m_pWndTree );
	UIFACTORYMGR_PTR->GetCaption( "EdtPollTime", strCaption, m_pWndTree );
	u16 wVal = atoi( strCaption.c_str() );
	if ( tPollInfo.wPollExpire != wVal ||  tPollInfo.bIsPoll != (BOOL)bUse  )
	{
		bChange = true;
	}
	return bChange;
}

bool CCallServerCfgLogic::IsAudioFormatChange()
{
	bool bChange = false; 
	EmTpAudioFormat emAudioFormat;
	emAudioFormat = ComInterface->GetAudioFormatInfo();
	if ( emAudioFormat != m_emAudioFormat )
	{
		bChange = true;
	}	
	return bChange;
}

bool CCallServerCfgLogic::OnConfHoldEnd( const IArgs& args )
{
	Window* pWnd;
    pWnd = UIManagePtr->GetWindowPtr( "EdtConfRate", m_pWndTree );
	if ( pWnd )
	{
		pWnd->SetFocus();
		CEdit* pEd = ( CEdit* )pWnd;
		pEd->SetSel( 0, -1 );
	}
	return 0;
}

bool CCallServerCfgLogic::OnShowHoldEnd( const IArgs& args )
{
	Window* pWnd;
    pWnd = UIManagePtr->GetWindowPtr( "EdtShowRate", m_pWndTree );
	if ( pWnd )
	{
		pWnd->SetFocus();
		CEdit* pEd = ( CEdit* )pWnd;
		pEd->SetSel( 0, -1 );
	}
	return 0;
}


