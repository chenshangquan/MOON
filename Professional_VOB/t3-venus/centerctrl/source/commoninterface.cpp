// commoninterface.cpp: implementation of the CCommonInterface class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "centerctrl.h"
#include "commoninterface.h"
#include "tpmsginit.h"
#include "evCmsLib.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CCommonInterface* CCommonInterface::m_pMySelf = NULL;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CCommonInterface::CCommonInterface()
{
    m_pCnsSession = NULL;
    m_pCenterCtrl = NULL;
}

CCommonInterface::~CCommonInterface()
{
    m_pCnsSession = NULL;
    m_pCenterCtrl = NULL;

    DestroyCommIF();
}

BEGIN_MESSAGE_MAP(CCommonInterface, CWnd)

END_MESSAGE_MAP()


CCommonInterface* CCommonInterface::GetCommIF()
{
    if ( NULL != m_pMySelf )
    {
        return m_pMySelf ;
    }
    
    m_pMySelf = new CCommonInterface;
    
    if ( NULL != m_pMySelf )
    {
        VERIFY( m_pMySelf->CreateEx( 0, AfxRegisterWndClass(CS_DBLCLKS), _T("centerctrl"),
            WS_OVERLAPPEDWINDOW, CRect(10, 10, 10, 10), NULL, NULL, NULL ) );
    } 
    
    return m_pMySelf;
}


void CCommonInterface::DestroyCommIF()
{   
    DesdroySession();
    
    if ( NULL != m_pMySelf )
    {
        m_pMySelf->DestroyWindow();
        
        delete m_pMySelf;
        m_pMySelf = NULL;
    }  
}

BOOL CCommonInterface::PreCreateWindow( CREATESTRUCT& cs )
{
    cs.style &= ~WS_SYSMENU; 
    return CWnd::PreCreateWindow(cs);
}

LRESULT CCommonInterface::DefWindowProc( UINT message, WPARAM wParam, LPARAM lParam )
{
    CMsgDispatch::SendMessage(message,wParam,lParam);
    
    return CWnd::DefWindowProc( message, wParam, lParam );  
}

void CCommonInterface::CreateSession()
{
    InitTpEvent();

    //´´½¨cnssession
    CCncLib::CreateSession( &m_pCnsSession );
    if ( NULL == m_pCnsSession )
    {
        return;
	}

    m_pCnsSession->SetUseAddrbook( FALSE );
    m_pCnsSession->InitEnv( AID_TPAD_CENTERCTRL, MAKEIID( AID_TPAD_MSGTRANS, 1 ) );
    m_pCnsSession->SetNotifyWnd( GetRecvWnd() );

    m_pCnsSession->CncGetInterface( &m_pCenterCtrl );
    if ( m_pCenterCtrl != NULL ) 
    {
        m_pCenterCtrl->SetNotifyWnd( GetRecvWnd() );
	}
}

void CCommonInterface::DesdroySession()
{   	   
    CCncLib::DestroySession( &m_pCnsSession );
}

u16 CCommonInterface::ConnectTPad()
{
    if( NULL == m_pCnsSession )
    {
        return ERR_CMS;
    } 
    
    u32 dwIp = ntohl( inet_addr( "127.0.0.1" ) );
    
    TTPadSubInfo tTPadSubInfo;
    tTPadSubInfo.dwIp = dwIp;
    tTPadSubInfo.dwPort = TPAD_LISTEN_PORT;
    tTPadSubInfo.emType = emTPad_centerctrl;

    u16 re = m_pCnsSession->ConnectTPad( tTPadSubInfo );
    
    return re;
}



u16 CCommonInterface::SetSysPower( EmSchPower emPower )
{
    if ( NULL == m_pCenterCtrl )
    {
        return ERR_CMS;
    }
    
    return m_pCenterCtrl->SetSysPower( emPower );
}

u16 CCommonInterface::SetSysAllLight( EmSchLight emLight )
{
    if ( NULL == m_pCenterCtrl )
    {
        return ERR_CMS;
    }
    
    return m_pCenterCtrl->SetSysAllLight( emLight );
}

u16 CCommonInterface::SetSysMainLight( EmSchMidLight emLight )
{
    if ( NULL == m_pCenterCtrl )
    {
        return ERR_CMS;
    }
    
    return m_pCenterCtrl->SetMainLight( emLight );
}

u16 CCommonInterface::SetSysAuxiLight( EmSchScrLight emLight )
{
    if ( NULL == m_pCenterCtrl )
    {
        return ERR_CMS;
    }
    
    return m_pCenterCtrl->SetAuxiLight( emLight );
}

u16 CCommonInterface::SelectTVMonitor( u8 byIndex )
{
    if ( NULL == m_pCenterCtrl )
    {
        return ERR_CMS;
    }

    return m_pCenterCtrl->SelectTV( byIndex );
}

u16 CCommonInterface::SetTVPowerMode( u8 byIndex, EmTvPowerMode emMode )
{
    if ( NULL == m_pCenterCtrl )
    {
        return ERR_CMS;
    }
    
    return m_pCenterCtrl->SetTVPowerMode( byIndex, emMode );
}


u16 CCommonInterface::SetTVAudVisMode( EmTVAudVisMode emMode )
{
    if ( NULL == m_pCenterCtrl )
    {
        return ERR_CMS;
    }
    
    return m_pCenterCtrl->SetTVAudVisMode( emMode );
}

u16 CCommonInterface::SetTVDisMode( EmTVDisplayMode emMode )
{
    if ( NULL == m_pCenterCtrl )
    {
        return ERR_CMS;
    }
    
    return m_pCenterCtrl->SetTVDisMode( emMode );
}

u16 CCommonInterface::SetTVInpSelect( u8 byIndex, EmTVInputSelect emSelect )
{
    if ( NULL == m_pCenterCtrl )
    {
        return ERR_CMS;
    }
    
    return m_pCenterCtrl->SetTVInpSelect( byIndex, emSelect );
}

TCentreTVCfg* CCommonInterface::GetCentreTVCfg()
{
    if ( NULL == m_pCenterCtrl )
    {
        return NULL;
    }
    
    return m_pCenterCtrl->GetCentreTVCfg();
}


u16 CCommonInterface::SetDCamPower( EmDCamPower emPower )
{
    if ( NULL == m_pCenterCtrl )
    {
        return ERR_CMS;
    }
    
    return m_pCenterCtrl->SetDCamPower( emPower );
}

u16 CCommonInterface::SetDCamAFMode( EmDCamAFMode emMode )
{
    if ( NULL == m_pCenterCtrl )
    {
        return ERR_CMS;
    }
    
    return m_pCenterCtrl->SetDCamAFMode( emMode );
}

u16 CCommonInterface::SetDCamWBMode( EmDCamWBMode emMode )
{
    if ( NULL == m_pCenterCtrl )
    {
        return ERR_CMS;
    }
    
    return m_pCenterCtrl->SetDCamWBMode( emMode );
}

u16 CCommonInterface::SetDCamZoom( EmDCamZoom emZoom, EmCnAction emAction )
{
    if ( NULL == m_pCenterCtrl )
    {
        return ERR_CMS;
    }
    
    return m_pCenterCtrl->SetDCamZoom( emZoom, emAction );
}

u16 CCommonInterface::SetDCamPreset( EmDCamRecallNum emNum )
{
    if ( NULL == m_pCenterCtrl )
    {
        return ERR_CMS;
    }
    
    return m_pCenterCtrl->SetDCamPreset( (EmDCamPresetNum)emNum );
}

u16 CCommonInterface::SetDCamRecall( EmDCamRecallNum emNum )
{
    if ( NULL == m_pCenterCtrl )
    {
        return ERR_CMS;
    }
    
    return m_pCenterCtrl->SetDCamRecall( emNum );
}

// u16 CCommonInterface::SetAirPower( EmCentreACPower emPower )
// {
// 	if ( NULL == m_pCenterCtrl )
// 	{
// 		return ERR_CMS;
// 	}
// 	return m_pCenterCtrl->SetAirPower( emPower );
// }

u16 CCommonInterface::SetACMode( EmCentreACMode emMode )
{
	if ( NULL == m_pCenterCtrl )
	{
		return ERR_CMS;
	}
	return m_pCenterCtrl->SetACMode( emMode );
}

u16 CCommonInterface::SetACTemp( u8 byTemp )
{
    if ( NULL == m_pCenterCtrl )
    {
        return ERR_CMS;
    }
	
    return m_pCenterCtrl->SetACTemp( byTemp );
}

u16 CCommonInterface::SetACAirVol( EmCentreACAirVol emAirVol )
{
    if ( NULL == m_pCenterCtrl )
    {
        return ERR_CMS;
    }
	
    return m_pCenterCtrl->SetACAirVol( emAirVol );
}

u16 CCommonInterface::SelectAirMonitor( u8 byIndex )
{
    if ( NULL == m_pCenterCtrl )
    {
        return ERR_CMS;
    }
	
    return m_pCenterCtrl->SelectAir( byIndex );
}

u16 CCommonInterface::GetCentreACCfg( vector<TCentreACCfg> &vecTCentreACCfg )
{
    if ( NULL == m_pCenterCtrl )
    {
        return NULL;
    }
    
     m_pCenterCtrl->GetCentreACCfg( vecTCentreACCfg );
	 return NO_ERROR;
}

u16 CCommonInterface::SetACPowerMode( u8 byIndex, EmCentreACPower emMode )
{
    if ( NULL == m_pCenterCtrl )
    {
        return ERR_CMS;
    }
    
    return m_pCenterCtrl->SetACPowerMode( byIndex, emMode );
}

u16 CCommonInterface::SetApplyToAll( u8 byIndex, BOOL* atbIsCtrl )
{
    if ( NULL == m_pCenterCtrl )
    {
        return ERR_CMS;
    }
    
    return m_pCenterCtrl->SetApplyToAll( byIndex, &atbIsCtrl );
}

u16 CCommonInterface::GetApplyToAllInfo( BOOL** pIsCtrl )
{
	*pIsCtrl = m_pCenterCtrl->GetApplyToAllInfo();
	return NO_ERROR;
}

u16 CCommonInterface::SetCurtainState( BOOL* bIsCtrl, EmCurAction emCurAction )
{
    if ( NULL == m_pCenterCtrl )
    {
        return ERR_CMS;
    }
	
	return m_pCenterCtrl->SetCurtainState( &bIsCtrl, emCurAction );
}

u16 CCommonInterface::GetCentreCurName( vector<TCentreCurName> &vecTCentreCurName )
{
    if ( NULL == m_pCenterCtrl )
    {
        return NULL;
    }
    
	m_pCenterCtrl->GetCentreCurName( vecTCentreCurName );
	return NO_ERROR;
}

u16 CCommonInterface::DisConnectTpad()
{
	if ( NULL == m_pCnsSession )
    {
        return ERR_CMS;
    }

	m_pCnsSession->DisConnectTpad();

	return NO_ERROR;
}


