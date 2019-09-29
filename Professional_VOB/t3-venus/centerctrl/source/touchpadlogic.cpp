// touchpadlogic.cpp: implementation of the CTouchPadLogic class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "centerctrl.h"
#include "touchpadlogic.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

const String CTouchPadLogic::m_stcUpdateImg = "WaitingDlg/stcAutoImg";
const String CTouchPadLogic::m_shmImg1 = "SchmPic1";
const String CTouchPadLogic::m_shmImg2 = "SchmPic2";
const String CTouchPadLogic::m_shmImg3 = "SchmPic3";
const String CTouchPadLogic::m_shmImg4 = "SchmPic4";
const String CTouchPadLogic::m_stcWaitingDlg= "WaitingDlg";
const String g_strCurtainUpOffBkg = "touchpad/CurtainUpOff.png";                      
const String g_strCurtainDownOffBkg = "touchpad/CurtainDownOff.png";          

CTouchPadLogic *CTouchPadLogic::m_pLogic = NULL;

static UINT g_nTmHandleWaiting;
VOID  CALLBACK  CWaitingTimerFun( HWND hwnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime )
{   
    if ( idEvent == g_nTmHandleWaiting )
    {
        CTouchPadLogic::GetLogicPtr()->UpdateWaitingImg();//更换呼叫图片
    } 
}
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTouchPadLogic::CTouchPadLogic()
{
    g_nTmHandleWaiting = 1;
    m_bPowerOn = FALSE;
    m_bLightOn = FALSE;
    m_bMainLightOn = FALSE;
    m_bAuxiLightOn = FALSE;
	m_bCurtainLogicExist = FALSE;
	m_bOff = FALSE;
    m_nUpdateTime = 0;
	m_wLocalTemp = 0;
	m_nCurNum = 0;

	memset( m_bIsCheck, 0, sizeof(m_bIsCheck) );
}

CTouchPadLogic::~CTouchPadLogic()
{
    if ( m_pLogic != NULL )
    {   
        UnRegMsg();
        UnRegFunc();
        delete m_pLogic;
        m_pLogic = NULL; 
    }
}

CTouchPadLogic* CTouchPadLogic::GetLogicPtr()
{
    if ( m_pLogic == NULL )
    {
        m_pLogic = new CTouchPadLogic(); 
    } 
    return m_pLogic;
}


void CTouchPadLogic::RegMsg()
{
    REG_MSG_HANDLER( UI_CNS_SCHSTATE_NTY, CTouchPadLogic::OnSchStateNty, m_pLogic, CTouchPadLogic ); 
    REG_MSG_HANDLER( UI_CNS_SCHPOWER_IND, CTouchPadLogic::OnSchPowerInd, m_pLogic, CTouchPadLogic ); 
    REG_MSG_HANDLER( UI_CNS_SCHALLLIGHT_IND, CTouchPadLogic::OnSchAllLightInd, m_pLogic, CTouchPadLogic ); 
    REG_MSG_HANDLER( UI_CNS_SCHMIDLIGHT_IND, CTouchPadLogic::OnSchMidLightInd, m_pLogic, CTouchPadLogic );
    REG_MSG_HANDLER( UI_CNS_SCHSCRLIGHT_IND, CTouchPadLogic::OnSchScrLightInd, m_pLogic, CTouchPadLogic );
    
    REG_MSG_HANDLER( UI_CNS_SCHTEMP_NTY, CTouchPadLogic::OnSchTempNty, m_pLogic, CTouchPadLogic ); 
	REG_MSG_HANDLER( UI_TPAD_CURTAINSTATE_NTY, CTouchPadLogic::OnCurtainStateNty, m_pLogic, CTouchPadLogic );
}

bool CTouchPadLogic::RegCBFun()
{   
    REG_GOBAL_MEMBER_FUNC( "CTouchPadLogic::InitWnd", CTouchPadLogic::InitWnd, m_pLogic, CTouchPadLogic );

    REG_GOBAL_MEMBER_FUNC( "CTouchPadLogic::OnBtnSysSwitch", CTouchPadLogic::OnBtnSysSwitch, m_pLogic, CTouchPadLogic );
    REG_GOBAL_MEMBER_FUNC( "CTouchPadLogic::OnBtnAllLight", CTouchPadLogic::OnBtnAllLight, m_pLogic, CTouchPadLogic );
    REG_GOBAL_MEMBER_FUNC( "CTouchPadLogic::OnBtnMainLight", CTouchPadLogic::OnBtnMainLight, m_pLogic, CTouchPadLogic );
    REG_GOBAL_MEMBER_FUNC( "CTouchPadLogic::OnBtnAuxiLight", CTouchPadLogic::OnBtnAuxiLight, m_pLogic, CTouchPadLogic );
	REG_GOBAL_MEMBER_FUNC( "CTouchPadLogic::OnBtnCancle", CTouchPadLogic::OnBtnCancle, m_pLogic, CTouchPadLogic );
	REG_GOBAL_MEMBER_FUNC( "CTouchPadLogic::OnBtnCurtainUp", CTouchPadLogic::OnBtnCurtainUp, m_pLogic, CTouchPadLogic );
	REG_GOBAL_MEMBER_FUNC( "CTouchPadLogic::OnBtnCurtainDown", CTouchPadLogic::OnBtnCurtainDown, m_pLogic, CTouchPadLogic );
    return true;
}


bool CTouchPadLogic::InitWnd( const IArgs & args )
{   
    CWndLogicBase::InitWnd( args );

	IWndTree* pTree = const_cast<IWndTree*>( UIFACTORYMGR_PTR->GetWindow( g_stcStrBtnCurtainCfg ) );

	if ( pTree != NULL )
	{
//		UIFACTORYMGR_PTR->SetTransStaticImage( _T("TouchPadDlg/StcMainLight"), g_strCurtainUpOffBkg, m_pWndTree );
//		UIFACTORYMGR_PTR->SetTransStaticImage( _T("TouchPadDlg/StcAuxiLight"), g_strCurtainDownOffBkg, m_pWndTree );
		UIFACTORYMGR_PTR->LoadScheme( "SchmCurLogicExist", m_pWndTree );
		m_bCurtainLogicExist = TRUE;
	}
	else
	{
		UIFACTORYMGR_PTR->LoadScheme( "SchmCurLogicUnExist", m_pWndTree );
		m_bCurtainLogicExist = FALSE;
	}
    
    return true;
}

void CTouchPadLogic::Clear()
{
    UIFACTORYMGR_PTR->EnableWindow( "StcAllLight", true, m_pWndTree );
    UIFACTORYMGR_PTR->EnableWindow( "StcMainLight", true, m_pWndTree );
    UIFACTORYMGR_PTR->EnableWindow( "StcAuxiLight", true, m_pWndTree );
	UIFACTORYMGR_PTR->LoadScheme( "SchmRecover", NULL, m_stcWaitingDlg );
//断链时不能设值，否则如果中控连上之后，注销tpad再重登，这个值不会再赋一遍
//	m_bCurtainLogicExist = FALSE;
    if ( UIFACTORYMGR_PTR->IsVisible( g_stcStrWaitingDlg ) )
    {
        EndWaiting();
    }
}

bool CTouchPadLogic::OnBtnSysSwitch( const IArgs& args )
{
//     if ( m_bPowerOn )
//     {
//         UIFACTORYMGR_PTR->LoadScheme( "SchmPowerOff", NULL, "WaitingDlg/StcMsg" );  
//     }
//     else
//     {
//         UIFACTORYMGR_PTR->LoadScheme( "SchmPowerOn", NULL, "WaitingDlg/StcMsg" );
//     }
	UIFACTORYMGR_PTR->LoadScheme( "SchmPowerPrepare", NULL, "WaitingDlg/StcMsg" );

	ComInterface->SetSysPower( emSchPowerToggle );

    Value_WindowOwer owerVal;
    owerVal.pWnd = UIFACTORYMGR_PTR->GetWindowPtr( g_stcStrTouchPadDlg );
    UIFACTORYMGR_PTR->SetPropertyValue( owerVal, g_stcStrWaitingDlg );

    CString strLeftTime = _T("请稍候...");
    UIFACTORYMGR_PTR->SetCaption( "WaitingDlg/StcSecond", (LPCTSTR)strLeftTime );
    
    m_nWaitTime = 0;
    m_nUpdateTime = 0;
    g_nTmHandleWaiting = SetTimer( NULL, 0, 500, CWaitingTimerFun );
	UIFACTORYMGR_PTR->Domodal( g_stcStrWaitingDlg, NULL, FALSE );
    
    return true;
}

bool CTouchPadLogic::OnBtnAllLight( const IArgs& args )
{
    if ( m_bLightOn )
    {
        ComInterface->SetSysAllLight( emSchLightOff );
    }
    else
    {
        ComInterface->SetSysAllLight( emSchLightOn );
    }

    UIFACTORYMGR_PTR->EnableWindow( "StcAllLight", false, m_pWndTree ); 

/*	ComInterface->SetSysAllLight( emSchLightToggle );*/

    return true;
}

bool CTouchPadLogic::OnBtnMainLight( const IArgs& args )
{

	if ( m_bMainLightOn )
	{
		ComInterface->SetSysMainLight( emSchMidLightOff );
	}
	else
	{
		ComInterface->SetSysMainLight( emSchMidLightOn );
	}
	
	UIFACTORYMGR_PTR->EnableWindow( "StcMainLight", false, m_pWndTree );

/*	ComInterface->SetSysMainLight( emSchMidLightToggle );*/

    return true;
}

bool CTouchPadLogic::OnBtnAuxiLight( const IArgs& args )
{

	if ( m_bAuxiLightOn )
	{
		ComInterface->SetSysAuxiLight( emSchScrLightOff );
	}
	else
	{
		ComInterface->SetSysAuxiLight( emSchScrLightOn );
	}
	
	UIFACTORYMGR_PTR->EnableWindow( "StcAuxiLight", false, m_pWndTree );

/*	ComInterface->SetSysAuxiLight( emSchScrLightToggle );*/

    return true;
}


HRESULT CTouchPadLogic::OnSchStateNty( WPARAM wparam, LPARAM lparam )
{
    if ( m_pWndTree == NULL )
    {
        return NO_ERROR;
    }
    
    TCentreSchCfg tSchCfg = *(TCentreSchCfg*)wparam;

    //电源
//     BOOL bPower = false;
//     if ( tSchCfg.emSchPower == emSchPowerOn )
//     {
//         bPower = true;
//     }
//     if ( m_bPowerOn != bPower )
//     {
//         m_bPowerOn = bPower;
//         if ( bPower )    
//         {
//             UIFACTORYMGR_PTR->LoadScheme( "SchmPowerOn", m_pWndTree );
//         }
//         else
//         {
//             UIFACTORYMGR_PTR->LoadScheme( "SchmPowerOff", m_pWndTree );
//         }
//   }

    //灯光
    BOOL bLight = false;
    if ( tSchCfg.emSchLight == emSchLightOn )
    {
        bLight = true;
    } 
    if ( m_bLightOn != bLight )
    {
        m_bLightOn = bLight;
        if ( bLight )    
        {
            UIFACTORYMGR_PTR->LoadScheme( "SchmLightOn", m_pWndTree );
        }
        else
        {
            UIFACTORYMGR_PTR->LoadScheme( "SchmLightOff", m_pWndTree );
        }
    }

	if ( !m_bCurtainLogicExist )
	{
		//主灯
		bLight = false;
		if ( tSchCfg.emSchMidLight == emSchMidLightOn )
		{
			bLight = true;
		} 
		if ( m_bMainLightOn != bLight )
		{
			m_bMainLightOn = bLight;
			if ( bLight )    
			{
				UIFACTORYMGR_PTR->LoadScheme( "SchmMainLightOn", m_pWndTree );
			}
			else
			{
				UIFACTORYMGR_PTR->LoadScheme( "SchmMainLightOff", m_pWndTree );
			}
		}
		
		//辅灯
		bLight = false;
		if ( tSchCfg.emSchScrLight == emSchScrLightOn )
		{
			bLight = true;
		} 
		if ( m_bAuxiLightOn != bLight )
		{
			m_bAuxiLightOn = bLight;
			if ( bLight )    
			{
				UIFACTORYMGR_PTR->LoadScheme( "SchmAuxiLightOn", m_pWndTree );
			}
			else
			{
				UIFACTORYMGR_PTR->LoadScheme( "SchmAuxiLightOff", m_pWndTree );
			}
		}
	}

	//初次登录时温度处理
	u16 wTemp = tSchCfg.wSchTem;
	
    if ( m_wLocalTemp != wTemp )
    {
        m_wLocalTemp = wTemp;
        UpdateTempImg( m_wLocalTemp );
    } 

    return NO_ERROR;
}


HRESULT CTouchPadLogic::OnSchPowerInd( WPARAM wParam, LPARAM lParam )
{
    BOOL bOk = (BOOL)wParam;  
	EmSchPower emPower = (EmSchPower)lParam;
    if ( !bOk )
    {    
		if ( emPower == emSchPowerOn )
		{
			UIFACTORYMGR_PTR->LoadScheme( "SchmOnDefault", NULL, m_stcWaitingDlg );
		}
		else
		{
			UIFACTORYMGR_PTR->LoadScheme( "SchmOffDefault", NULL, m_stcWaitingDlg );
		}
        return NO_ERROR;
    }
    
    if ( emPower == emSchPowerOn )
    {
		UIFACTORYMGR_PTR->LoadScheme( "SchmPowerOn", NULL, "WaitingDlg/StcMsg" );
        m_nWaitTime = 30 * 2;
		m_bOff = FALSE;
    }
    else
    {
		UIFACTORYMGR_PTR->LoadScheme( "SchmPowerOff", NULL, "WaitingDlg/StcMsg" );
        m_nWaitTime = 10 * 2;
		m_bOff = TRUE;
    }
    
    CString strLeftTime;
    strLeftTime.Format( "剩余 %d秒", m_nWaitTime / 2 );
    UIFACTORYMGR_PTR->SetCaption( "WaitingDlg/StcSecond", (LPCTSTR)strLeftTime );

    m_nUpdateTime = 0;

    return NO_ERROR;
}


HRESULT CTouchPadLogic::OnSchAllLightInd( WPARAM wParam, LPARAM lParam )
{
    UIFACTORYMGR_PTR->EnableWindow( "StcAllLight", true, m_pWndTree ); 
    return NO_ERROR;
}

HRESULT CTouchPadLogic::OnSchMidLightInd( WPARAM wParam, LPARAM lParam )
{
    UIFACTORYMGR_PTR->EnableWindow( "StcMainLight", true, m_pWndTree ); 
    return NO_ERROR;
}

HRESULT CTouchPadLogic::OnSchScrLightInd( WPARAM wParam, LPARAM lParam )
{
    UIFACTORYMGR_PTR->EnableWindow( "StcAuxiLight", true, m_pWndTree );    
    return NO_ERROR;
}



void CTouchPadLogic::UpdateWaitingImg()
{
    switch ( m_emImgSchm )
    {
    case emImgSchm1:
        m_emImgSchm = emImgSchm2;
        UIFACTORYMGR_PTR->LoadScheme( m_shmImg2, NULL, m_stcUpdateImg );
        break;
    case emImgSchm2:
        m_emImgSchm = emImgSchm3;
        UIFACTORYMGR_PTR->LoadScheme( m_shmImg3, NULL, m_stcUpdateImg );
        break;
    case emImgSchm3:
        m_emImgSchm = emImgSchm4;
        UIFACTORYMGR_PTR->LoadScheme( m_shmImg4, NULL, m_stcUpdateImg );
        break;  
    case emImgSchm4:
        m_emImgSchm = emImgSchm1;
        UIFACTORYMGR_PTR->LoadScheme( m_shmImg1, NULL, m_stcUpdateImg );
        break;  
    default:
        m_emImgSchm = emImgSchm1;
        UIFACTORYMGR_PTR->LoadScheme( m_shmImg1, NULL, m_stcUpdateImg );
        break;    
    } 
    
	
    if ( m_nWaitTime > 0 )
    {    
		m_nUpdateTime++;
		int nLeftTime = ( m_nWaitTime - m_nUpdateTime ) / 2;
        CString strLeftTime;
        strLeftTime.Format( "剩余 %d秒", nLeftTime );
        UIFACTORYMGR_PTR->SetCaption( "WaitingDlg/StcSecond", (LPCTSTR)strLeftTime );
        
        if ( m_nUpdateTime > m_nWaitTime )
        {
            //等待结束
            EndWaiting();
        }
    }

    if ( m_nWaitTime == 0 && m_nUpdateTime > 10 )
    {
		EndWaiting();
    }    
}


void CTouchPadLogic::EndWaiting()
{ 
    KillTimer( NULL, g_nTmHandleWaiting );
	UIFACTORYMGR_PTR->Endmodal( IDCANCEL, g_stcStrWaitingDlg );
	if ( 0 != m_nWaitTime && m_bOff )
	{
		ComInterface->DisConnectTpad();
	}
    m_nWaitTime = 0;
}

HRESULT CTouchPadLogic::OnSchTempNty( WPARAM wparam, LPARAM lparam )
{
    if ( m_pWndTree == NULL )
    {
        return NO_ERROR;
    }
    
    u16 wTemp = (u16)wparam;
    
    if ( m_wLocalTemp != wTemp )
    {
        m_wLocalTemp = wTemp;
        UpdateTempImg( m_wLocalTemp );
    }  
    
    return NO_ERROR;
}

void CTouchPadLogic::UpdateTempImg( u16 wTemp )
{
    if ( wTemp > 99 )
    {
        return;
    }
    
    u8 byHigh = wTemp / 10;
    u8 byLow = wTemp % 10;
    
    String strLeftNum = g_stcStrTouchPadDlg + "/StcLeftNum";
    String strRightNum = g_stcStrTouchPadDlg + "/StcRightNum";
    
    CString strImgPath = "air/normalnum/";
    
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

bool CTouchPadLogic::OnBtnCancle( const IArgs& args )
{
	EndWaiting();
	UIFACTORYMGR_PTR->LoadScheme( "SchmRecover", NULL, m_stcWaitingDlg );
	return true;
}

bool CTouchPadLogic::OnBtnCurtainUp( const IArgs& args )
{
	for ( int i=0; i< m_nCurNum; i++ )
	{
		m_bIsCheck[i] = TRUE;
	}	
	ComInterface->SetCurtainState( m_bIsCheck, emCurUp );

	return true;	
}

bool CTouchPadLogic::OnBtnCurtainDown( const IArgs& args )
{
	for ( int i=0; i< m_nCurNum; i++ )
	{
		m_bIsCheck[i] = TRUE;
	}	
	ComInterface->SetCurtainState( m_bIsCheck, emCurDown );

	return true;	
}

HRESULT CTouchPadLogic::OnCurtainStateNty( WPARAM wparam, LPARAM lparam )
{
	if ( m_pWndTree == NULL )
    {
        return NO_ERROR;
    }
	
	m_nCurNum = (u8)wparam;

	return NO_ERROR;
}

