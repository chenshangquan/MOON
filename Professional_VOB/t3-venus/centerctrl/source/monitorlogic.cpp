// monitorlogic.cpp: implementation of the CMonitorLogic class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "centerctrl.h"
#include "monitorlogic.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CMonitorLogic *CMonitorLogic::m_pLogic = NULL;

const String CMonitorLogic::m_strBtnTVSwitch1 = "btnSwitch1";
const String CMonitorLogic::m_strBtnTVSwitch2 = "btnSwitch2";
const String CMonitorLogic::m_strBtnTVSwitch3 = "btnSwitch3";
const String CMonitorLogic::m_strBtnScreen1 = "btnScreen1";
const String CMonitorLogic::m_strBtnScreen2 = "btnScreen2";
const String CMonitorLogic::m_strBtnScreen3 = "btnScreen3";
const String CMonitorLogic::m_strStcMonitorTitle = "MonitorCtrlDlg/StcTitle";
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMonitorLogic::CMonitorLogic()
{
	m_byIndex = -1; 	
}

CMonitorLogic::~CMonitorLogic()
{
    if ( m_pLogic != NULL )
    {   
        UnRegMsg();
        UnRegFunc();
        delete m_pLogic;
        m_pLogic = NULL; 
    }
}

CMonitorLogic* CMonitorLogic::GetLogicPtr()
{
    if ( m_pLogic == NULL )
    {
        m_pLogic = new CMonitorLogic(); 
    } 
    return m_pLogic;
}


void CMonitorLogic::RegMsg()
{
    REG_MSG_HANDLER( UI_CNS_TVSTATE_NTY, CMonitorLogic::OnTvStateNty, m_pLogic, CMonitorLogic );
    REG_MSG_HANDLER( UI_CNS_TVPOWERMODE_IND, CMonitorLogic::OnTvPowerInd, m_pLogic, CMonitorLogic );  
	REG_MSG_HANDLER( UI_CNS_SELETETV_IND, CMonitorLogic::OnSeleteTvInd, m_pLogic, CMonitorLogic );
}

bool CMonitorLogic::RegCBFun()
{   
    REG_GOBAL_MEMBER_FUNC( "CMonitorLogic::InitWnd", CMonitorLogic::InitWnd, m_pLogic, CMonitorLogic );
    REG_GOBAL_MEMBER_FUNC( "CMonitorLogic::OnBtnTv1Monitor", CMonitorLogic::OnBtnTv1Monitor, m_pLogic, CMonitorLogic );
    REG_GOBAL_MEMBER_FUNC( "CMonitorLogic::OnBtnTv2Monitor", CMonitorLogic::OnBtnTv2Monitor, m_pLogic, CMonitorLogic );
    REG_GOBAL_MEMBER_FUNC( "CMonitorLogic::OnBtnTv3Monitor", CMonitorLogic::OnBtnTv3Monitor, m_pLogic, CMonitorLogic );
    REG_GOBAL_MEMBER_FUNC( "CMonitorLogic::OnBtnTv1Power", CMonitorLogic::OnBtnTv1Power, m_pLogic, CMonitorLogic );
    REG_GOBAL_MEMBER_FUNC( "CMonitorLogic::OnBtnTv2Power", CMonitorLogic::OnBtnTv2Power, m_pLogic, CMonitorLogic );
    REG_GOBAL_MEMBER_FUNC( "CMonitorLogic::OnBtnTv3Power", CMonitorLogic::OnBtnTv3Power, m_pLogic, CMonitorLogic );

    REG_GOBAL_MEMBER_FUNC( "CMonitorLogic::OnBtnNormalView", CMonitorLogic::OnBtnNormalView, m_pLogic, CMonitorLogic );
    REG_GOBAL_MEMBER_FUNC( "CMonitorLogic::OnBtnMovieView", CMonitorLogic::OnBtnMovieView, m_pLogic, CMonitorLogic );
    REG_GOBAL_MEMBER_FUNC( "CMonitorLogic::OnBtnUserView", CMonitorLogic::OnBtnUserView, m_pLogic, CMonitorLogic );
    REG_GOBAL_MEMBER_FUNC( "CMonitorLogic::OnBtnComputerView", CMonitorLogic::OnBtnComputerView, m_pLogic, CMonitorLogic );

    REG_GOBAL_MEMBER_FUNC( "CMonitorLogic::OnBtnFullScreen", CMonitorLogic::OnBtnFullScreen, m_pLogic, CMonitorLogic );
    REG_GOBAL_MEMBER_FUNC( "CMonitorLogic::OnBtnPanoramic", CMonitorLogic::OnBtnPanoramic, m_pLogic, CMonitorLogic );
    REG_GOBAL_MEMBER_FUNC( "CMonitorLogic::OnBtnPointwise", CMonitorLogic::OnBtnPointwise, m_pLogic, CMonitorLogic );
    REG_GOBAL_MEMBER_FUNC( "CMonitorLogic::OnBtnNormalDis", CMonitorLogic::OnBtnNormalDis, m_pLogic, CMonitorLogic );

    REG_GOBAL_MEMBER_FUNC( "CMonitorLogic::OnBtnHDMI1", CMonitorLogic::OnBtnHDMI1, m_pLogic, CMonitorLogic );
    REG_GOBAL_MEMBER_FUNC( "CMonitorLogic::OnBtnHDMI2", CMonitorLogic::OnBtnHDMI2, m_pLogic, CMonitorLogic );
    REG_GOBAL_MEMBER_FUNC( "CMonitorLogic::OnBtnHDMI3", CMonitorLogic::OnBtnHDMI3, m_pLogic, CMonitorLogic );
    REG_GOBAL_MEMBER_FUNC( "CMonitorLogic::OnBtnHDMI4", CMonitorLogic::OnBtnHDMI4, m_pLogic, CMonitorLogic );
    REG_GOBAL_MEMBER_FUNC( "CMonitorLogic::OnBtnYPbPr", CMonitorLogic::OnBtnYPbPr, m_pLogic, CMonitorLogic );
    REG_GOBAL_MEMBER_FUNC( "CMonitorLogic::OnBtnCVBS1", CMonitorLogic::OnBtnCVBS1, m_pLogic, CMonitorLogic );
    REG_GOBAL_MEMBER_FUNC( "CMonitorLogic::OnBtnCVBS2", CMonitorLogic::OnBtnCVBS2, m_pLogic, CMonitorLogic );
    REG_GOBAL_MEMBER_FUNC( "CMonitorLogic::OnBtnComputerSrc", CMonitorLogic::OnBtnComputerSrc, m_pLogic, CMonitorLogic );
    return true;
}


bool CMonitorLogic::InitWnd( const IArgs & args )
{   
    CWndLogicBase::InitWnd( args );

	OSVERSIONINFOEX osvi;
    //利用OSVERSIONINFOEX结构调用GetVersionEx()函数
    //如果调用失败，可尝试使用OSVERSIONINFO结构
    ZeroMemory( &osvi, sizeof(OSVERSIONINFOEX) );
    osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
    if( !GetVersionEx((OSVERSIONINFO*)&osvi) )
    {
        osvi.dwOSVersionInfoSize=sizeof(OSVERSIONINFO);
        if(!GetVersionEx((OSVERSIONINFO*)&osvi))
            return false;
    }
    //xp以上版本才有触摸事件
    if ( osvi.dwMajorVersion > 5 )
    {  
        //注册响应WM_TOUCH的窗口
        Window* pWnd = UIFACTORYMGR_PTR->GetWindowPtr( m_strBtnScreen1, m_pWndTree ); 
        Window* pWnd1 = UIFACTORYMGR_PTR->GetWindowPtr( m_strBtnScreen2, m_pWndTree ); 
		Window* pWnd2 = UIFACTORYMGR_PTR->GetWindowPtr( m_strBtnScreen3, m_pWndTree );
        if ( pWnd->GetSafeHwnd() != NULL && pWnd1->GetSafeHwnd() != NULL && pWnd2->GetSafeHwnd() != NULL )
        {
            WINSDK_RegTouchWindow _WINSDK_RegTouchWindow;
            
            HINSTANCE hInstLibrary = LoadLibrary("windowsexsdk.dll");
            if (hInstLibrary != NULL)
            {
                _WINSDK_RegTouchWindow = (WINSDK_RegTouchWindow)GetProcAddress( hInstLibrary, "WINSDK_RegTouchWindow" );
                if ( _WINSDK_RegTouchWindow != NULL )
                {
                    _WINSDK_RegTouchWindow( pWnd->GetSafeHwnd() );
                    _WINSDK_RegTouchWindow( pWnd1->GetSafeHwnd() );
					_WINSDK_RegTouchWindow( pWnd2->GetSafeHwnd() );
                }
                FreeLibrary( hInstLibrary );
            }
        } 
    }

    return true;
}

void CMonitorLogic::Clear()
{  
	UIFACTORYMGR_PTR->LoadScheme( "SchmDataClear", m_pWndTree );
}


bool CMonitorLogic::OnBtnTv1Monitor( const IArgs& args )
{
    ComInterface->SelectTVMonitor( 0 );
    /*UIFACTORYMGR_PTR->SetCaption( m_strStcMonitorTitle, "显示器1", m_pWndTree );*/
    return true;
}

bool CMonitorLogic::OnBtnTv2Monitor( const IArgs& args )
{
    ComInterface->SelectTVMonitor( 1 );
    /*UIFACTORYMGR_PTR->SetCaption( m_strStcMonitorTitle, "显示器2", m_pWndTree );*/
    return true;
}

bool CMonitorLogic::OnBtnTv3Monitor( const IArgs& args )
{
    ComInterface->SelectTVMonitor( 2 );
    /*UIFACTORYMGR_PTR->SetCaption( m_strStcMonitorTitle, "显示器3", m_pWndTree );*/
    return true;
}

bool CMonitorLogic::OnBtnTv1Power( const IArgs& args )
{
    bool bOn = false;
    UIFACTORYMGR_PTR->GetSwitchState( m_strBtnTVSwitch1, bOn, m_pWndTree );

    UIFACTORYMGR_PTR->EnableWindow( m_strBtnTVSwitch1, false, m_pWndTree );

    if ( bOn )
    {
        ComInterface->SetTVPowerMode( 0, emTVPowerON );
    }
    else
    {
        ComInterface->SetTVPowerMode( 0, emTVPowerOFF );
    }

    return true;
}

bool CMonitorLogic::OnBtnTv2Power( const IArgs& args )
{
    bool bOn = false;
    UIFACTORYMGR_PTR->GetSwitchState( m_strBtnTVSwitch2, bOn, m_pWndTree );

    UIFACTORYMGR_PTR->EnableWindow( m_strBtnTVSwitch2, false, m_pWndTree );

    if ( bOn )
    {
        ComInterface->SetTVPowerMode( 1, emTVPowerON );
    }
    else
    {
        ComInterface->SetTVPowerMode( 1, emTVPowerOFF );
    }
    return true;
}

bool CMonitorLogic::OnBtnTv3Power( const IArgs& args )
{
    bool bOn = false;
    UIFACTORYMGR_PTR->GetSwitchState( m_strBtnTVSwitch3, bOn, m_pWndTree );

    UIFACTORYMGR_PTR->EnableWindow( m_strBtnTVSwitch3, false, m_pWndTree );

    if ( bOn )
    {
        ComInterface->SetTVPowerMode( 2, emTVPowerON );
    }
    else
    {
        ComInterface->SetTVPowerMode( 2, emTVPowerOFF );
    }
    return true;
}

bool CMonitorLogic::OnBtnNormalView( const IArgs& args )
{
    ComInterface->SetTVAudVisMode( emTVAVStandardMode );
    return true;
}

bool CMonitorLogic::OnBtnMovieView( const IArgs& args )
{
    ComInterface->SetTVAudVisMode( emTVAVMovieMode );
    return true;
}

bool CMonitorLogic::OnBtnUserView( const IArgs& args )
{
    ComInterface->SetTVAudVisMode( emTVAVUserMode );
    return true;
}

bool CMonitorLogic::OnBtnComputerView( const IArgs& args )
{
    ComInterface->SetTVAudVisMode( emTVAVComputerMode );
    return true;
}

bool CMonitorLogic::OnBtnFullScreen( const IArgs& args )
{
    ComInterface->SetTVDisMode( emTVDisFullScrMode );
    return true;
}

bool CMonitorLogic::OnBtnPanoramic( const IArgs& args )
{
    ComInterface->SetTVDisMode( emTVDisPanoramaMode );
    return true;
}

bool CMonitorLogic::OnBtnPointwise( const IArgs& args )
{
    ComInterface->SetTVDisMode( emTVDisPointMode );
    return true;
}

bool CMonitorLogic::OnBtnNormalDis( const IArgs& args )
{
    ComInterface->SetTVDisMode( emTVDisStandardMode );
    return true;   
}

bool CMonitorLogic::OnBtnHDMI1( const IArgs& args )
{
    ComInterface->SetTVInpSelect( m_byIndex, emTVHDMI1 );
    return true;
}

bool CMonitorLogic::OnBtnHDMI2( const IArgs& args )
{
    ComInterface->SetTVInpSelect( m_byIndex, emTVHDMI2 );
    return true;
}

bool CMonitorLogic::OnBtnHDMI3( const IArgs& args )
{
    ComInterface->SetTVInpSelect( m_byIndex, emTVHDMI3 );
    return true;
}

bool CMonitorLogic::OnBtnHDMI4( const IArgs& args )
{
    ComInterface->SetTVInpSelect( m_byIndex, emTVHDMI4 );
    return true;
}

bool CMonitorLogic::OnBtnYPbPr( const IArgs& args )
{
    ComInterface->SetTVInpSelect( m_byIndex, emTVYpbPr );
    return true;
}

bool CMonitorLogic::OnBtnCVBS1( const IArgs& args )
{
    ComInterface->SetTVInpSelect( m_byIndex, emTVCVBS1 );
    return true;
}

bool CMonitorLogic::OnBtnCVBS2( const IArgs& args )
{
    ComInterface->SetTVInpSelect( m_byIndex, emTVCVBS2 );
    return true;
}

bool CMonitorLogic::OnBtnComputerSrc( const IArgs& args )
{
    ComInterface->SetTVInpSelect( m_byIndex, emTVComputer );
    return true;
}

HRESULT CMonitorLogic::OnTvStateNty( WPARAM wparam, LPARAM lparam )
{
    if ( m_pWndTree == NULL )
    {
        return NO_ERROR;
    }
    
    TCentreTVCfg  atTVCfg[MAX_CENTRETV_NUM];
    memcpy( atTVCfg , ComInterface->GetCentreTVCfg(), sizeof(TCentreTVCfg) * MAX_CENTRETV_NUM );

  
    if ( atTVCfg[0].emTvPowerMode == emTVPowerON )
    {
        UIFACTORYMGR_PTR->LoadScheme( "SchmScreen1On", m_pWndTree );
    }
    else if ( atTVCfg[0].emTvPowerMode == emTVPowerOFF  )
    {	
        UIFACTORYMGR_PTR->LoadScheme( "SchmScreen1Off", m_pWndTree );
    }
    else
    {
        UIFACTORYMGR_PTR->LoadScheme( "SchmScreen1Down", m_pWndTree );

		if ( 0 == m_byIndex )
		{
			UIFACTORYMGR_PTR->LoadScheme( "SchmScreenDlgOff", m_pWndTree );
		}
    }

    
    if ( atTVCfg[1].emTvPowerMode == emTVPowerON )
    {
        UIFACTORYMGR_PTR->LoadScheme( "SchmScreen2On", m_pWndTree );
    }
    else if ( atTVCfg[1].emTvPowerMode == emTVPowerOFF  )
    {
        UIFACTORYMGR_PTR->LoadScheme( "SchmScreen2Off", m_pWndTree );
    }
    else
    {
        UIFACTORYMGR_PTR->LoadScheme( "SchmScreen2Down", m_pWndTree );

		if ( 1 == m_byIndex )
		{
			UIFACTORYMGR_PTR->LoadScheme( "SchmScreenDlgOff", m_pWndTree );
		}
    }

    if ( atTVCfg[2].emTvPowerMode == emTVPowerON )
    {
        UIFACTORYMGR_PTR->LoadScheme( "SchmScreen3On", m_pWndTree );
    }
    else if ( atTVCfg[2].emTvPowerMode == emTVPowerOFF  )
    {
        UIFACTORYMGR_PTR->LoadScheme( "SchmScreen3Off", m_pWndTree );
    }
    else
    {
        UIFACTORYMGR_PTR->LoadScheme( "SchmScreen3Down", m_pWndTree );

		if ( 2 == m_byIndex )
		{
			UIFACTORYMGR_PTR->LoadScheme( "SchmScreenDlgOff", m_pWndTree );
		}
    }

	//点击显示屏对应的开关关闭显示屏时，清空显示屏选中状态，故只有当无选中时清空下方操作框

    s32 nCheckState = 0;

	UIFACTORYMGR_PTR->GetCheckState( _T("btnScreen1"), nCheckState, m_pWndTree );

	if ( 0 == nCheckState  )
	{
		UIFACTORYMGR_PTR->GetCheckState( _T("btnScreen2"), nCheckState, m_pWndTree );
		if ( 0 == nCheckState )
		{
			UIFACTORYMGR_PTR->GetCheckState( _T("btnScreen3"), nCheckState, m_pWndTree);
			if ( 0 == nCheckState )
			{
				UIFACTORYMGR_PTR->LoadScheme( "SchmScreenDlgOff", m_pWndTree );
			}
		}
    }

    memcpy( m_atTVCfg, atTVCfg, sizeof(TCentreTVCfg) * MAX_CENTRETV_NUM );

    return NO_ERROR;
}


HRESULT CMonitorLogic::OnTvPowerInd( WPARAM wparam, LPARAM lparam )
{    
    //Ind回false时不会再有Nty消息，恢复按钮状态
    u8 byIndex = (u8)wparam; 
    EmTvPowerMode emPower = (EmTvPowerMode)lparam;

    CString strSchme;
    strSchme.Format( "SchmScreen%d", byIndex + 1 );

    if ( emPower == emTVPowerON )
    {
        strSchme += "Off";
        UIFACTORYMGR_PTR->LoadScheme( (LPCTSTR)strSchme, m_pWndTree );
    }
    else
    {
        strSchme += "On";
        UIFACTORYMGR_PTR->LoadScheme( (LPCTSTR)strSchme, m_pWndTree );
    }
    
    return NO_ERROR;
}

HRESULT CMonitorLogic::OnSeleteTvInd( WPARAM wparam, LPARAM lparam )
{
	m_byIndex = (u8)wparam;
	BOOL bok = (BOOL)lparam;
    
    if ( bok )
    {
		switch ( m_byIndex )
		{
		case 0:
			{
				UIFACTORYMGR_PTR->LoadScheme( "SchmScreenDlgOn", m_pWndTree );
				UIFACTORYMGR_PTR->SetCaption( m_strStcMonitorTitle, "显示器1", m_pWndTree );
				break;
			}
		case 1:
			{
				UIFACTORYMGR_PTR->LoadScheme( "SchmScreenDlgOn", m_pWndTree );
				UIFACTORYMGR_PTR->SetCaption( m_strStcMonitorTitle, "显示器2", m_pWndTree );
				break;
			}
		case 2:
			{
				UIFACTORYMGR_PTR->LoadScheme( "SchmScreenDlgOn", m_pWndTree );
				UIFACTORYMGR_PTR->SetCaption( m_strStcMonitorTitle, "显示器3", m_pWndTree );
				break;
			}
		default:
			break;
		}
	}
	
	return NO_ERROR;
}