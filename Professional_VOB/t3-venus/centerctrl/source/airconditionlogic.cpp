// airconditionlogic.cpp: implementation of the CAirConditionLogic class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "centerctrl.h"
#include "airconditionlogic.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CAirConditionLogic *CAirConditionLogic::m_pLogic = NULL;
const String CAirConditionLogic::m_strDlgAirTemp1 = "BtnAirScreen1";
const String CAirConditionLogic::m_strDlgAirTemp2 = "BtnAirScreen2";
const String CAirConditionLogic::m_strDlgAirTemp3 = "BtnAirScreen3";
const String CAirConditionLogic::m_strBtnAirSwitch1 = "btnAirSwitch1";
const String CAirConditionLogic::m_strBtnAirSwitch2 = "btnAirSwitch2";
const String CAirConditionLogic::m_strBtnAirSwitch3 = "btnAirSwitch3";
const String CAirConditionLogic::m_strDlgAirVolume = "FreshAirCtrlDlg/AirVolumeDlg";
const String CAirConditionLogic::m_strStcAirCtrlTitle = "AirTempCtrlDlg/StcTitle";
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


CAirConditionLogic::CAirConditionLogic()
{
    m_wLocalTemp = 0;
    m_wAirTemp = 0;
	m_wAirTemp1 = 0;
	m_wAirTemp2 = 0;
	m_wAirTemp3 = 0;
    m_byAirVol = 0;
    m_byAirVol1 = 0;
	m_byAirVol2 = 0;
	m_byAirVol3 = 0;
	m_byIndex = 0;
	m_byIndex1 = 0;
	m_byIndex2 = 0; 
	m_byNum = 0;
}

CAirConditionLogic::~CAirConditionLogic()
{
    if ( m_pLogic != NULL )
    {   
        UnRegMsg();
        UnRegFunc();
        delete m_pLogic;
        m_pLogic = NULL; 
    }
}


CAirConditionLogic* CAirConditionLogic::GetLogicPtr()
{
    if ( m_pLogic == NULL )
    {
        m_pLogic = new CAirConditionLogic(); 
    } 
    return m_pLogic;
}


void CAirConditionLogic::RegMsg()
{
    REG_MSG_HANDLER( UI_CNS_ACSTATE_NTY, CAirConditionLogic::OnACStateNty, m_pLogic, CAirConditionLogic ); 
	REG_MSG_HANDLER( UI_CNS_SELECTAIR_IND, CAirConditionLogic::OnSelectAirInd, m_pLogic, CAirConditionLogic );
//	REG_MSG_HANDLER( UI_CNS_APPLYTOALL_IND, CAirConditionLogic::OnApplyToAllInd, m_pLogic, CAirConditionLogic );
//  REG_MSG_HANDLER( UI_CNS_SCHSTATE_NTY, CAirConditionLogic::OnSchStateNty, m_pLogic, CAirConditionLogic ); 
//  REG_MSG_HANDLER( UI_CNS_SCHTEMP_NTY, CAirConditionLogic::OnSchTempNty, m_pLogic, CAirConditionLogic ); 
}

bool CAirConditionLogic::RegCBFun()
{   
    REG_GOBAL_MEMBER_FUNC( "CAirConditionLogic::InitWnd", CAirConditionLogic::InitWnd, m_pLogic, CAirConditionLogic );
    REG_GOBAL_MEMBER_FUNC( "CAirConditionLogic::OnBtnMinusTemp", CAirConditionLogic::OnBtnMinusTemp, m_pLogic, CAirConditionLogic );
	REG_GOBAL_MEMBER_FUNC( "CAirConditionLogic::OnBtnAddTemp", CAirConditionLogic::OnBtnAddTemp, m_pLogic, CAirConditionLogic );
    REG_GOBAL_MEMBER_FUNC( "CAirConditionLogic::OnBtnAirScreen1", CAirConditionLogic::OnBtnAirScreen1, m_pLogic, CAirConditionLogic );
    REG_GOBAL_MEMBER_FUNC( "CAirConditionLogic::OnBtnAirScreen2", CAirConditionLogic::OnBtnAirScreen2, m_pLogic, CAirConditionLogic );
	REG_GOBAL_MEMBER_FUNC( "CAirConditionLogic::OnBtnAirScreen3", CAirConditionLogic::OnBtnAirScreen3, m_pLogic, CAirConditionLogic );
    REG_GOBAL_MEMBER_FUNC( "CAirConditionLogic::OnBtnSwitch1", CAirConditionLogic::OnBtnSwitch1, m_pLogic, CAirConditionLogic );
    REG_GOBAL_MEMBER_FUNC( "CAirConditionLogic::OnBtnSwitch2", CAirConditionLogic::OnBtnSwitch2, m_pLogic, CAirConditionLogic );
    REG_GOBAL_MEMBER_FUNC( "CAirConditionLogic::OnBtnSwitch3", CAirConditionLogic::OnBtnSwitch3, m_pLogic, CAirConditionLogic );
    REG_GOBAL_MEMBER_FUNC( "CAirConditionLogic::OnBtnCold", CAirConditionLogic::OnBtnCold, m_pLogic, CAirConditionLogic );
    REG_GOBAL_MEMBER_FUNC( "CAirConditionLogic::OnBtnWarm", CAirConditionLogic::OnBtnWarm, m_pLogic, CAirConditionLogic );
	REG_GOBAL_MEMBER_FUNC( "CAirConditionLogic::OnBtnWind", CAirConditionLogic::OnBtnWind, m_pLogic, CAirConditionLogic );
    REG_GOBAL_MEMBER_FUNC( "CAirConditionLogic::OnBtnWet", CAirConditionLogic::OnBtnWet, m_pLogic, CAirConditionLogic );
    REG_GOBAL_MEMBER_FUNC( "CAirConditionLogic::OnBtnAuto", CAirConditionLogic::OnBtnAuto, m_pLogic, CAirConditionLogic );
    REG_GOBAL_MEMBER_FUNC( "CAirConditionLogic::OnBtnMinusVolume", CAirConditionLogic::OnBtnMinusVolume, m_pLogic, CAirConditionLogic );
    REG_GOBAL_MEMBER_FUNC( "CAirConditionLogic::OnBtnAddVolume", CAirConditionLogic::OnBtnAddVolume, m_pLogic, CAirConditionLogic );
    REG_GOBAL_MEMBER_FUNC( "CAirConditionLogic::OnBtnApplyToAll", CAirConditionLogic::OnBtnApplyToAll, m_pLogic, CAirConditionLogic );
	REG_GOBAL_MEMBER_FUNC( "CAirConditionLogic::OnDragEnd", CAirConditionLogic::OnDragEnd, m_pLogic, CAirConditionLogic );
//	REG_GOBAL_MEMBER_FUNC( "CAirConditionLogic::OnDragItemOut", CAirConditionLogic::OnDragItemOut, m_pLogic, CAirConditionLogic );
    return true;
}


bool CAirConditionLogic::InitWnd( const IArgs & args )
{   
    CWndLogicBase::InitWnd( args );
	u8 byIndex = 0;
	CString strAirTempWnd;
	strAirTempWnd.Format( "BtnAirScreen%d", byIndex+1 );
	CWnd * pList = UIFACTORYMGR_PTR->GetWindowPtr( (LPCTSTR)strAirTempWnd, m_pWndTree );
	CDragWindow * p = CDragWindow::GetDragWindow();
	if ( p != NULL )
	{
		p->RegisterDropWindow( pList );
	}
    return true;
}

void CAirConditionLogic::Clear()
{   
}


bool CAirConditionLogic::OnBtnMinusTemp( const IArgs& args )
{
	if ( m_wAirTemp3 > 16 )
	{
		u8 wTemp = m_wAirTemp3;
		wTemp--;
		ComInterface->SetACTemp( wTemp );
	}

    return true;
}

bool CAirConditionLogic::OnBtnAddTemp( const IArgs& args )
{
	if ( m_wAirTemp3 < 23 )
	{
		u8 wTemp = m_wAirTemp3;
		wTemp++;
		ComInterface->SetACTemp( wTemp );
	}

	return true;
}

bool CAirConditionLogic::OnBtnCold( const IArgs& args )
{
	ComInterface->SetACMode( emCenAcref );
    return true;
}

bool CAirConditionLogic::OnBtnWarm( const IArgs& args )
{
	ComInterface->SetACMode( emCenACheat );
    return true;
}

bool CAirConditionLogic::OnBtnWet( const IArgs& args )
{
	ComInterface->SetACMode( emCenACdeh );
    return true;
}

bool CAirConditionLogic::OnBtnAuto( const IArgs& args )
{
	ComInterface->SetACMode( emCenACAuto );
    return true;
}

bool CAirConditionLogic::OnBtnWind( const IArgs& args )
{
	ComInterface->SetACMode( emCenACBlowIn );
	return true;	
}

bool CAirConditionLogic::OnBtnMinusVolume( const IArgs& args )
{
	TCentreACCfg tACCfg;
	if ( m_byAirVol3 > 0 )
	{
		u8 byAirVol = m_byAirVol3;
		byAirVol--;
		tACCfg.emACAirVol =static_cast<EmCentreACAirVol>(byAirVol);
		ComInterface->SetACAirVol( tACCfg.emACAirVol );
	}

    return true;
}

bool CAirConditionLogic::OnBtnAddVolume( const IArgs& args )
{
	TCentreACCfg tACCfg;
	if ( m_byAirVol3 < 5)
	{
		u8 byAirVol = m_byAirVol3;
		byAirVol++;
		tACCfg.emACAirVol =static_cast<EmCentreACAirVol>(byAirVol);
		ComInterface->SetACAirVol( tACCfg.emACAirVol );
	}

    return true;
}

void CAirConditionLogic::UpdateTempImg( u16 wTemp, String strTempDlg )
{
    if ( wTemp > 23 || wTemp < 16 )
    {
        return;
    }

    u8 byHigh = wTemp / 10;
    u8 byLow = wTemp % 10;

    String strLeftNum = strTempDlg + "/StcLeftNum";
    String strRightNum = strTempDlg + "/StcRightNum";

    CString strImgPath;
    strImgPath = "air/lightnum/";


    //左边数字
    CString strImage;
    strImage.Format( "%d.png", byHigh );
    strImage = strImgPath + strImage;
    
    UIFACTORYMGR_PTR->SetTransStaticImage( strLeftNum, (LPCTSTR)strImage, m_pWndTree );

    //右边数字
    strImage.Format( "%d.png", byLow );
    strImage = strImgPath + strImage;
  
    UIFACTORYMGR_PTR->SetTransStaticImage( strRightNum, (LPCTSTR)strImage, m_pWndTree );

}


void CAirConditionLogic::UpdateAirVol( u8 byVol, String strTempDlg )
{
    if ( byVol > 5 || byVol < 0 )
    {
        return;
    }
   
    CString strImage;
    strImage.Format( "air/btnWindSize/%d.png", byVol );
    String strNum = strTempDlg + "/StcWindSize";
    
    UIFACTORYMGR_PTR->SetTransStaticImage( strNum, (LPCTSTR)strImage, m_pWndTree );
}

HRESULT CAirConditionLogic::OnACStateNty( WPARAM wparam, LPARAM lparam )
{
    if ( m_pWndTree == NULL )
    {
        return NO_ERROR;
    }
	vector<TCentreACCfg> vecTCentreACCfg;
	ComInterface->GetCentreACCfg( vecTCentreACCfg );
	m_byNum = vecTCentreACCfg.size();
	switch ( m_byNum )
	{		
	case 1:
		{
			UIFACTORYMGR_PTR->LoadScheme( "Schm1AirScreenExist", m_pWndTree );
			UIFACTORYMGR_PTR->SetCaption( m_strStcAirCtrlTitle, "空调", m_pWndTree );
			if ( vecTCentreACCfg[0].emACPower == emCenACPowerOn )
			{
				UIFACTORYMGR_PTR->LoadScheme( "SchmAirScreen1On", m_pWndTree );
				m_wAirTemp = vecTCentreACCfg[0].bySetTemp;
				m_byAirVol = vecTCentreACCfg[0].emACAirVol;
				m_byIndex = vecTCentreACCfg[0].byID;
				UpdateTempImg( m_wAirTemp, m_strDlgAirTemp1);
				UpdateAirVol( m_byAirVol, m_strDlgAirTemp1 );
			}
			else
			{
				UIFACTORYMGR_PTR->LoadScheme( "SchmAirScreen1Off", m_pWndTree );
			}
			break;
		}
	case 2:
		{
			UIFACTORYMGR_PTR->LoadScheme( "Schm2AirScreenExist", m_pWndTree );
			if ( vecTCentreACCfg[0].emACPower == emCenACPowerOn )
			{
				UIFACTORYMGR_PTR->LoadScheme( "SchmAirScreen1On", m_pWndTree );
				m_byIndex = vecTCentreACCfg[0].byID;
				m_wAirTemp = vecTCentreACCfg[0].bySetTemp;
				m_byAirVol = vecTCentreACCfg[0].emACAirVol;
				UpdateTempImg( vecTCentreACCfg[0].bySetTemp, m_strDlgAirTemp1);
				UpdateAirVol( vecTCentreACCfg[0].emACAirVol, m_strDlgAirTemp1 );
			}
			else
			{
				UIFACTORYMGR_PTR->LoadScheme( "SchmAirScreen1Off", m_pWndTree );
			}
			if ( vecTCentreACCfg[1].emACPower == emCenACPowerOn )
			{
				UIFACTORYMGR_PTR->LoadScheme( "SchmAirScreen2On", m_pWndTree );
				m_byIndex1 = vecTCentreACCfg[1].byID; 	
				m_wAirTemp1 = vecTCentreACCfg[1].bySetTemp;
				m_byAirVol1 = vecTCentreACCfg[1].emACAirVol;
				UpdateTempImg( vecTCentreACCfg[1].bySetTemp, m_strDlgAirTemp2 );
			    UpdateAirVol( vecTCentreACCfg[1].emACAirVol, m_strDlgAirTemp2 );
			}
			else
			{
				UIFACTORYMGR_PTR->LoadScheme( "SchmAirScreen2Off", m_pWndTree );
			}
			break;
		}
	case 3:
		{
			if ( vecTCentreACCfg[0].emACPower == emCenACPowerOn )
			{
				UIFACTORYMGR_PTR->LoadScheme( "SchmAirScreen1On", m_pWndTree );
				m_wAirTemp = vecTCentreACCfg[0].bySetTemp;
				m_byAirVol = vecTCentreACCfg[0].emACAirVol;
				UpdateTempImg( vecTCentreACCfg[0].bySetTemp, m_strDlgAirTemp1 );
				UpdateAirVol( vecTCentreACCfg[0].emACAirVol, m_strDlgAirTemp1 );
			}
			else
			{
				UIFACTORYMGR_PTR->LoadScheme( "SchmAirScreen1Off", m_pWndTree );
			}

			if ( vecTCentreACCfg[1].emACPower == emCenACPowerOn )
			{	
				UIFACTORYMGR_PTR->LoadScheme( "SchmAirScreen2On", m_pWndTree );
				m_wAirTemp1 = vecTCentreACCfg[1].bySetTemp;
				m_byAirVol1 = vecTCentreACCfg[1].emACAirVol;
				UpdateTempImg( vecTCentreACCfg[1].bySetTemp, m_strDlgAirTemp2 );
				UpdateAirVol( vecTCentreACCfg[1].emACAirVol, m_strDlgAirTemp2 );
			}
			else
			{
				UIFACTORYMGR_PTR->LoadScheme( "SchmAirScreen2Off", m_pWndTree );
			}

			if ( vecTCentreACCfg[2].emACPower == emCenACPowerOn )
			{
				UIFACTORYMGR_PTR->LoadScheme( "SchmAirScreen3On", m_pWndTree );
				m_wAirTemp2 = vecTCentreACCfg[2].bySetTemp;
				m_byAirVol2 = vecTCentreACCfg[2].emACAirVol;
				UpdateTempImg( vecTCentreACCfg[2].bySetTemp, m_strDlgAirTemp3 );
				UpdateAirVol( vecTCentreACCfg[2].emACAirVol, m_strDlgAirTemp3 );
			}
			else
			{
				UIFACTORYMGR_PTR->LoadScheme( "SchmAirScreen3Off", m_pWndTree );
			}
			break;
		}
	default:
		break;
	}
	for ( u8 Index = 0; Index < vecTCentreACCfg.size(); Index++ )
	{
		if ( vecTCentreACCfg[Index].emACPower == emCenACPowerOn )
		{
			CString strCold;
			strCold.Format( "BtnAirScreen%d/StcCold", Index+1 );
			CString strWarm;
			strWarm.Format( "BtnAirScreen%d/StcWarm", Index+1 );
			CString strWind;
			strWind.Format( "BtnAirScreen%d/StcWind", Index+1 );
			CString strWet;
			strWet.Format( "BtnAirScreen%d/StcWind", Index+1 );
			switch( vecTCentreACCfg[Index].emACMode )
			{
				case emCenAcref:
					{
						UIFACTORYMGR_PTR->SetCaption( (LPCTSTR)strCold, "制冷", m_pWndTree );
						break;
					}
				case emCenACheat:
					{
						UIFACTORYMGR_PTR->SetCaption( (LPCTSTR)strWarm, "制热", m_pWndTree );
						break;
					}
				case emCenACBlowIn:
					{
						UIFACTORYMGR_PTR->SetCaption( (LPCTSTR)strWind, "送风", m_pWndTree );
						CString strSchmWind;
						strSchmWind.Format( "SchmWind%d", Index+1 );
						UIFACTORYMGR_PTR->LoadScheme( (LPCTSTR)strSchmWind, m_pWndTree );
						break;
					}
				case emCenACdeh:
					{
						UIFACTORYMGR_PTR->SetCaption( (LPCTSTR)strWet, "除湿", m_pWndTree );
						CString strSchmWet;
						strSchmWet.Format( "SchmWet%d", Index+1 );
						UIFACTORYMGR_PTR->LoadScheme( (LPCTSTR)strSchmWet, m_pWndTree );
						break;
					}
				default:
					break;
			}			
		}	 
	}
	return NO_ERROR;
}

bool CAirConditionLogic::OnBtnAirScreen1( const IArgs& args )
{
	UIFACTORYMGR_PTR->LoadScheme( "SchmBtnAirScreen1", m_pWndTree );
	UIFACTORYMGR_PTR->SetCaption( m_strStcAirCtrlTitle, "空调1", m_pWndTree, true );
	if ( m_byNum == 3 )
	{
		ComInterface->SelectAirMonitor( 0 );
	}
	else
	{
		ComInterface->SelectAirMonitor( m_byIndex );
	}
	m_wAirTemp3 = m_wAirTemp;
	m_byAirVol3 = m_byAirVol;
	return true;
}

bool CAirConditionLogic::OnBtnAirScreen2( const IArgs& args )
{
	UIFACTORYMGR_PTR->LoadScheme( "SchmBtnAirScreen2", m_pWndTree );
	UIFACTORYMGR_PTR->SetCaption( m_strStcAirCtrlTitle, "空调2", m_pWndTree, true );
	if ( m_byNum == 3 )
	{
		ComInterface->SelectAirMonitor( 1 );
	}
    else
	{
		ComInterface->SelectAirMonitor( m_byIndex1 );
	}
	m_wAirTemp3 = m_wAirTemp1;
	m_byAirVol3 = m_byAirVol1;
	return true;	
}

bool CAirConditionLogic::OnBtnAirScreen3( const IArgs& args )
{
	UIFACTORYMGR_PTR->LoadScheme( "SchmBtnAirScreen3", m_pWndTree );
	UIFACTORYMGR_PTR->SetCaption( m_strStcAirCtrlTitle, "空调3", m_pWndTree, true );
	ComInterface->SelectAirMonitor( 2 );
	m_wAirTemp3 = m_wAirTemp2;
	m_byAirVol3 = m_byAirVol2;
	return true;
}

bool CAirConditionLogic::OnBtnSwitch1( const IArgs& args )
{
	bool bOn = false;
	UIFACTORYMGR_PTR->GetSwitchState( m_strBtnAirSwitch1, bOn, m_pWndTree );
	if ( bOn )
    {
		if ( m_byNum == 3)
		{
			ComInterface->SetACPowerMode( 0, emCenACPowerOn );
		}
		else
		{
			ComInterface->SetACPowerMode( m_byIndex, emCenACPowerOn );
		}

    }
	else
    {
		if ( m_byNum == 3 )
		{
			ComInterface->SetACPowerMode( 0, emCenACPowerOff );
		}
		else
		{
			ComInterface->SetACPowerMode( m_byIndex, emCenACPowerOff );
		}

    }
	return true;	
}

bool CAirConditionLogic::OnBtnSwitch2( const IArgs& args )
{
	bool bOn = false;
	UIFACTORYMGR_PTR->GetSwitchState( m_strBtnAirSwitch2, bOn, m_pWndTree );
	if ( bOn )
    {
		if ( m_byNum == 3 )
		{
			ComInterface->SetACPowerMode( 1, emCenACPowerOn );
		}
		else
		{
			ComInterface->SetACPowerMode( m_byIndex1, emCenACPowerOn );
		}
    }
    else
    {
		if ( m_byNum == 3 )
		{
			ComInterface->SetACPowerMode( 1, emCenACPowerOff );
		}
		else
		{
			ComInterface->SetACPowerMode( m_byIndex1, emCenACPowerOff );
		}

    }
	return true;	
}

bool CAirConditionLogic::OnBtnSwitch3( const IArgs& args )
{
	bool bOn = false;
	UIFACTORYMGR_PTR->GetSwitchState( m_strBtnAirSwitch3, bOn, m_pWndTree );
	if ( bOn )
    {
		ComInterface->SetACPowerMode( 2, emCenACPowerOn );
    }
    else
    {
		ComInterface->SetACPowerMode( 2, emCenACPowerOff );
    }
	return true;
}

bool CAirConditionLogic::OnBtnApplyToAll( const IArgs& args )
{
	BOOL m_atbIsCtrl[MAX_AC_NUM] = { FALSE };
	vector<TCentreACCfg> vecTCentreACCfg;
	ComInterface->GetCentreACCfg( vecTCentreACCfg );

	for( int i = 0; i < vecTCentreACCfg.size(); i ++ )
	{
		u8 byID = vecTCentreACCfg.at(i).byID;
		if ( byID < MAX_AC_NUM /*&& byID != m_byIndex2*/ )
		{
			if ( vecTCentreACCfg.at(i).emACPower == emCenACPowerOn )
			{
				m_atbIsCtrl[byID] = TRUE;
			}
		}
	}

	ComInterface->SetApplyToAll( m_byIndex2, m_atbIsCtrl );

	return true;
}

bool CAirConditionLogic::OnDragEnd( const IArgs& args )
{
	Args_WindowMsg WinMsg = *dynamic_cast<const Args_WindowMsg*>(&args);
	WindowMsg msg = WinMsg.m_Msg;
	s32 x = LOWORD(msg.lParam);
	s32 y = HIWORD(msg.lParam);
	CPoint point(x, y);
	CRect rect;
	Window* pWnd = UIFACTORYMGR_PTR->GetWindowPtr( m_strDlgAirTemp1, m_pWndTree );
	pWnd->GetWindowRect(&rect);
	if ( !rect.PtInRect(point) )
	{
		TCentreACCfg tACCfg = *(TCentreACCfg*)(msg.wParam);
		m_wLocalTemp = tACCfg.bySetTemp;
		UpdateTempImg( m_wLocalTemp, m_strDlgAirTemp1 );
	}
	return true;	
}

HRESULT CAirConditionLogic::OnSelectAirInd( WPARAM wparam, LPARAM lparam )
{
	m_byIndex2 = (u8)wparam;    
	return NO_ERROR;
}

// HRESULT CAirConditionLogic::OnApplyToAllInd( WPARAM wparam, LPARAM lparam )
// {
// 	if ( m_pWndTree == NULL )
// 	{
// 		return S_FALSE;
// 	}
// 	BOOL* pIsCtrl = NULL;
// 	ComInterface->GetApplyToAllInfo( &pIsCtrl );
// 	BOOL atbIsCtrl[3];
// 	for ( int i = 0; i < 3; i++ )
// 	{
// 		BOOL bIsCtrl = *( pIsCtrl + i );
// 		atbIsCtrl[i] = bIsCtrl;
// 
// 	}
// 	return NO_ERROR;
// }

// bool CAirConditionLogic::OnDragItemOut( const IArgs& args )
// {
// 	Args_WindowMsg WinMsg = *dynamic_cast< const Args_WindowMsg* >(&args);
// 	WindowMsg msg = WinMsg.m_Msg;
// 	s32 x = LOWORD(msg.lParam);
// 	s32 y = HIWORD(msg.lParam);
// 	CPoint point(x, y);
// 	Window* pWnd = UIFACTORYMGR_PTR->GetWindowPtr( m_strDlgLocalTemp, m_pWndTree );
// 	if ( pWnd->GetSafeHwnd() == msg.hwnd )
// 	{
// 		CRect rect;
// 		pWnd->GetWindowRect(&rect);
// 		if ( !rect.PtInRect(point) )
// 		{
// 			TCentreACCfg tACCfg = *(TCentreACCfg*)(msg.wParam);
// 			m_wLocalTemp = tACCfg.bySetTemp;
// 			UpdateTempImg( m_wLocalTemp, m_strDlgLocalTemp );
// 		}
// 	}
// 	
// 	return true;	
// }

