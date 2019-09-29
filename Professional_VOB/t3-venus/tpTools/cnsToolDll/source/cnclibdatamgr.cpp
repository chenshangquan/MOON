#include "StdAfx.h"
#include "cnclibdatamgr.h"
#include "sessionmgr.h"


CCnclibDataMgr* CCnclibDataMgr::m_pThis = NULL;

CCnclibDataMgr::CCnclibDataMgr()
{   
	VERIFY( CreateEx( 0, AfxRegisterWndClass(CS_DBLCLKS), _T("cnstool"),
			WS_OVERLAPPEDWINDOW, CRect(10, 10, 10, 10), NULL, NULL, NULL ) );
	InitDataMgr();
}

CCnclibDataMgr::~CCnclibDataMgr()
{

}

void CCnclibDataMgr::InitDataMgr()
{
	CNCSESSION_MGR_PTR->GetSessionIF()->SetNotifyWnd( GetSafeHwnd() );
	CNCSESSION_MGR_PTR->GetConfCtrlIF()->SetNotifyWnd( GetSafeHwnd() );	
	CNCSESSION_MGR_PTR->GetCenterCtrlIF()->SetNotifyWnd( GetSafeHwnd() );
	CNCSESSION_MGR_PTR->GetConfigIF()->SetNotifyWnd( GetSafeHwnd() );
	CNCSESSION_MGR_PTR->GetSipInfoCtrlIF()->SetNotifyWnd( GetSafeHwnd() );
	CNCSESSION_MGR_PTR->GetSysCtrlIF()->SetNotifyWnd( GetSafeHwnd() );
	CNCSESSION_MGR_PTR->GetPortDiagCtrlIF()->SetNotifyWnd( GetSafeHwnd() );
	CNCSESSION_MGR_PTR->GetNetMngCtrlIF()->SetNotifyWnd( GetSafeHwnd() );
	
}

CCnclibDataMgr* CCnclibDataMgr::GetDataMgrIF()
{
	if ( NULL == m_pThis )
    {
        m_pThis = new CCnclibDataMgr;
		
    }
	return m_pThis;
}

u16 CCnclibDataMgr::GetSipCfg( TTPSipRegistrarCfg& tSipCfg ) const
{
	tSipCfg = CNCSESSION_MGR_PTR->GetConfigIF()->GetSipRegCfg();
	return NO_ERROR;
}

u16 CCnclibDataMgr::GetGkCfg( TTPGKCfg& tGkCfg ) const
{
	tGkCfg = CNCSESSION_MGR_PTR->GetConfigIF()->GetGkCfg();
	return NO_ERROR;
}

u16 CCnclibDataMgr::GetLoginIp( u32 &dwIP ) const
{
	dwIP = CNCSESSION_MGR_PTR->GetSessionIF()->GetLoginIp();
	return NO_ERROR;
}

u16 CCnclibDataMgr::GetLocalCnsInfo( TTPCnsInfo& tCnsInfo ) const
{
	tCnsInfo = CNCSESSION_MGR_PTR->GetConfigIF()->GetLocalCnsInfo();
	return NO_ERROR;
}

u16 CCnclibDataMgr::GetNATCfg( TTPNatCfg& tInfo ) const
{
	tInfo = CNCSESSION_MGR_PTR->GetConfigIF()->GetNATCfg();
	return NO_ERROR;
}

TCentreTVCfg* CCnclibDataMgr::GetCentreTVCfg()const
{
return CNCSESSION_MGR_PTR->GetCenterCtrlIF()->GetCentreTVCfg();
}

u16 CCnclibDataMgr::GetCamInfo( vector<TCnCameraCfg>& vecTCnCameraCfg )const
{
	u16 wRe = CNCSESSION_MGR_PTR->GetSysCtrlIF()->GetCamCfgAll( vecTCnCameraCfg );
	return wRe;
}

u16 CCnclibDataMgr::GetAudioPortInfo( TTpAudioPortInfo** pAudioPortInfo )const
{
	*pAudioPortInfo = CNCSESSION_MGR_PTR->GetPortDiagCtrlIF()->GetAudioPortInfo();
	return NO_ERROR;
}

u16 CCnclibDataMgr::GetAudioEqualizer( TTPEqualizer** pEqualizer ) const
{
	*pEqualizer = CNCSESSION_MGR_PTR->GetPortDiagCtrlIF()->GetAudioEqualizer();
	return NO_ERROR;
}

u16 CCnclibDataMgr::GetAudiotMixer( u8** pAudioMixerInfo ) const
{
	*pAudioMixerInfo = CNCSESSION_MGR_PTR->GetPortDiagCtrlIF()->GetAudioMixerInfo();
	return NO_ERROR;
}

u16 CCnclibDataMgr::GetLostPacketInfo( u8& tLostPacketInfo )const
{
	tLostPacketInfo = CNCSESSION_MGR_PTR->GetPortDiagCtrlIF()->GetLostPacketInfo();
	return NO_ERROR;
}

u16 CCnclibDataMgr::GetUpDownstreamRate( TTPUpDownSpeedInfo& tUpDownSpeedInfo )const
{
	tUpDownSpeedInfo = CNCSESSION_MGR_PTR->GetPortDiagCtrlIF()->GetUpDownstreamRate();
	return NO_ERROR;
}

u16 CCnclibDataMgr::GetVideoDiagInfo( TTPVideoDiagInfo& tVideoDiagInfo )const
{
	tVideoDiagInfo = CNCSESSION_MGR_PTR->GetPortDiagCtrlIF()->GetVideoDiagInfo();
	return NO_ERROR;
}


u16 CCnclibDataMgr::GetAudioDiagInfo( TTPAudioDiagInfo& tAudioDiagInfo )const
{
	tAudioDiagInfo = CNCSESSION_MGR_PTR->GetPortDiagCtrlIF()->GetAudioDiagInfo();
	return NO_ERROR;
}


u16 CCnclibDataMgr::GetTpadList( TTPTPadList& tTPadList )const
{
	tTPadList = CNCSESSION_MGR_PTR->GetPortDiagCtrlIF()->GetTpadList();
	return NO_ERROR;
}


u16 CCnclibDataMgr::GetCnConfStatus( TTPCnsConfStatus& tCnsConfStatus )const
{
	tCnsConfStatus = CNCSESSION_MGR_PTR->GetSysCtrlIF()->GetCnConfStatus();
	return NO_ERROR;
}

u16 CCnclibDataMgr::GetCnConfVideoParam( TTPCnConfInfo& tCnVideoParam )const
{
	tCnVideoParam = CNCSESSION_MGR_PTR->GetSysCtrlIF()->GetCnConfVideoParam();
	return NO_ERROR;
}

u16 CCnclibDataMgr::GetSysInfo( TTPSysInfo& tSysInfo ) const
{
	tSysInfo = CNCSESSION_MGR_PTR->GetSysCtrlIF()->GetSysInfo();
	return NO_ERROR;
}

u16 CCnclibDataMgr::GetCamSel( u8& byCameraIndx )const
{
	byCameraIndx = CNCSESSION_MGR_PTR->GetSysCtrlIF()->GetCamSel();
	return NO_ERROR;
}

u16 CCnclibDataMgr::GetCamOSD( EmOSDShow& emOSDShow )const
{
	emOSDShow = CNCSESSION_MGR_PTR->GetSysCtrlIF()->GetCamOSD();
	return NO_ERROR;
}

u16 CCnclibDataMgr::GetCamPresetMove( BOOL& bUsed )const
{
	bUsed = CNCSESSION_MGR_PTR->GetSysCtrlIF()->GetCamPresetMove();
	return NO_ERROR;
}

u16 CCnclibDataMgr::GetCamGain( EmGain& emGain )const
{
	emGain = CNCSESSION_MGR_PTR->GetSysCtrlIF()->GetCamGain();
	return NO_ERROR;
}

u16 CCnclibDataMgr::GetCamShutSpd( EmShutSpd& emShutSpd )const
{
	emShutSpd = CNCSESSION_MGR_PTR->GetSysCtrlIF()->GetCamShutSpd();
	return NO_ERROR;
}

u16 CCnclibDataMgr::GetCamBackLightType( EmBackLightType& emBackLightType )const
{
	emBackLightType = CNCSESSION_MGR_PTR->GetSysCtrlIF()->GetCamBackLightType();
	return NO_ERROR;
}

u16 CCnclibDataMgr::GetCamBackLightIndex( u8& byMulti)const
{
	byMulti = CNCSESSION_MGR_PTR->GetSysCtrlIF()->GetCamBackLightIndex();
	return NO_ERROR;
}

u16 CCnclibDataMgr::GetCamAperture( u8& byAperture )const
{
	byAperture = CNCSESSION_MGR_PTR->GetSysCtrlIF()->GetCamAperture();
	return NO_ERROR;
}

u16 CCnclibDataMgr::GetCamRGain( u16& wRGain )const
{
	wRGain = CNCSESSION_MGR_PTR->GetSysCtrlIF()->GetCamRGain();
	return NO_ERROR;
}

u16 CCnclibDataMgr::GetCamBGain( u16& wBGain)const
{
	wBGain = CNCSESSION_MGR_PTR->GetSysCtrlIF()->GetCamBGain();
	return NO_ERROR;
}

u16 CCnclibDataMgr::GetCamPicSceneMode( EmPicSceMode& emPicSceMode )const
{
	emPicSceMode = CNCSESSION_MGR_PTR->GetSysCtrlIF()->GetCamPicSceneMode();
	return NO_ERROR;
}

u16 CCnclibDataMgr::GetCamGamma( EmGamma& emGamma )const
{
	emGamma = CNCSESSION_MGR_PTR->GetSysCtrlIF()->GetCamGamma();
	return NO_ERROR;
}

u16 CCnclibDataMgr::GetCamPicSceApt( u8& byPicSceApt )const
{
	byPicSceApt = CNCSESSION_MGR_PTR->GetSysCtrlIF()->GetCamPicSceApt();
	return NO_ERROR;
}

u16 CCnclibDataMgr::GetCamContrast( u16& wContrast )const
{
	wContrast = CNCSESSION_MGR_PTR->GetSysCtrlIF()->GetCamContrast();
	return NO_ERROR;
}

u16 CCnclibDataMgr::GetCamHue( u16& wHue )const
{
	wHue = CNCSESSION_MGR_PTR->GetSysCtrlIF()->GetCamHue();
	return NO_ERROR;
}

u16 CCnclibDataMgr::GetCamSaturat( u16& wSaturat )const
{
	wSaturat = CNCSESSION_MGR_PTR->GetSysCtrlIF()->GetCamSaturat();
	return NO_ERROR;
}

u16 CCnclibDataMgr::GetCamBright( u16& wBright )const
{
	wBright = CNCSESSION_MGR_PTR->GetSysCtrlIF()->GetCamBright();
	return NO_ERROR;
}

u16 CCnclibDataMgr::GetCamNRStmClean( EmStmClean& emStmClean )const
{
	emStmClean = CNCSESSION_MGR_PTR->GetSysCtrlIF()->GetCamNRStmClean();
	return NO_ERROR;
}

u16 CCnclibDataMgr::GetCam3DNR( Em3DNR& em3DNR )const	
{
	em3DNR = CNCSESSION_MGR_PTR->GetSysCtrlIF()->GetCam3DNR();
	return NO_ERROR;
}

u16 CCnclibDataMgr::GetCamCfg( TCnCameraCfg& tCnCameraCfg )const
{
	tCnCameraCfg = CNCSESSION_MGR_PTR->GetSysCtrlIF()->GetCamCfg();
	return NO_ERROR;
}

u16 CCnclibDataMgr::GetCamExpMode( EmExpMode& emExpMode )const
{
	emExpMode = CNCSESSION_MGR_PTR->GetSysCtrlIF()->GetCamExpMode();
	return NO_ERROR;
}

u16 CCnclibDataMgr::GetCamWBMode( EmWBMode& emExpMode )const
{
	emExpMode = CNCSESSION_MGR_PTR->GetSysCtrlIF()->GetCamWBMode();
	return NO_ERROR;
}

u16 CCnclibDataMgr::GetCamZoom( u16& wZoom )const
{
	wZoom = CNCSESSION_MGR_PTR->GetSysCtrlIF()->GetCamZoom();
	return NO_ERROR;
}

u16 CCnclibDataMgr::GetNetMngData( vector<TTPNMServerCfg> &vecTTPNMServerCfg )const
{
	CNCSESSION_MGR_PTR->GetNetMngCtrlIF()->GetNetMngData( vecTTPNMServerCfg );
	return NO_ERROR;
}

BOOL CCnclibDataMgr::PreCreateWindow( CREATESTRUCT& cs )
{
    cs.style &= ~WS_SYSMENU; 
    return CWnd::PreCreateWindow(cs);
}

LRESULT CCnclibDataMgr::DefWindowProc( UINT message, WPARAM wParam, LPARAM lParam )
{
	//if ( message > CMS_MSG_BEGIN ) 
	{
		CMsgDispatch::SendMessage( message, wParam, lParam );
	}
	
    return CWnd::DefWindowProc( message, wParam, lParam );
}

u16 CCnclibDataMgr::GetEthnetCfg( TTPEthnetInfo& tInfo )
{
	tInfo = CNCSESSION_MGR_PTR->GetConfigIF()->GetEthnetCfg();
	return NO_ERROR;
}

BOOL32 CCnclibDataMgr::IsInConf()
{
	BOOL32 bIn = FALSE;
	
	TTPCnsConfStatus status;
	GetCnConfStatus(status);
	if ( status.emState == em_CALL_CONNECTED )
	{
		bIn = TRUE;
	}
	
	return bIn;
}

TTPCnsConfStatus CCnclibDataMgr::GetLocalCnsConfState() const
{
//  TTPCnsConfStatus tConfStatus;	
    return CNCSESSION_MGR_PTR->GetConfCtrlIF()->GetCnsConfStatus();
}

u16 CCnclibDataMgr::GetVgaMixInfo( TTPVgaMixInfo &tVgaMixInfo ) const
{
	tVgaMixInfo = CNCSESSION_MGR_PTR->GetConfigIF()->GetVgaMixInfo();
	return NO_ERROR;
}

u16 CCnclibDataMgr::GetDualSrcInfo( TDualSrcInfo& tDualSrcinfo )
{	
	tDualSrcinfo = CNCSESSION_MGR_PTR->GetConfigIF()->GetDualSrcInfo();
	return NO_ERROR;
}

u16 CCnclibDataMgr::GetCallServerInfo( TTPCallSerInfo& tCallSerInfo ) const
{
	tCallSerInfo = CNCSESSION_MGR_PTR->GetPortDiagCtrlIF()->GetCallServerInfo();
	return NO_ERROR;
}

u16 CCnclibDataMgr::GetUpgradeSerInfo( TTPUpgradeSer& tUpgradeSer ) const
{
	tUpgradeSer = CNCSESSION_MGR_PTR->GetPortDiagCtrlIF()->GetUpgradeSerInfo();
	return NO_ERROR;
}

u16 CCnclibDataMgr::GetVideoFormatInfo( TTPVidForamt& tVidForamt ) const
{
	tVidForamt = CNCSESSION_MGR_PTR->GetPortDiagCtrlIF()->GetVideoFormatInfo();
	return NO_ERROR;
}

u16 CCnclibDataMgr::GetDualVideoFormatInfo( TTPVidForamt& tVidForamt ) const
{
	tVidForamt = CNCSESSION_MGR_PTR->GetPortDiagCtrlIF()->GetDualVideoFormatInfo();
	return NO_ERROR;
}

u16 CCnclibDataMgr::GetCallRateInfo( u16& wCallRate ) const
{
	wCallRate = CNCSESSION_MGR_PTR->GetPortDiagCtrlIF()->GetCallRate();
	return NO_ERROR;
}

u16 CCnclibDataMgr::GetDualCallRateInfo( u16& wDualCallRate ) const
{
	wDualCallRate = CNCSESSION_MGR_PTR->GetPortDiagCtrlIF()->GetDualCallRate();
	return NO_ERROR;
}

u16 CCnclibDataMgr::GetConfPollInfo( TTPPollInfo& tPollInfo ) const
{
	tPollInfo = CNCSESSION_MGR_PTR->GetPortDiagCtrlIF()->GetConfPollInfo();
	return NO_ERROR;
}

u16 CCnclibDataMgr::GetConfDisInfo( BOOL& bDis ) const
{
	bDis = CNCSESSION_MGR_PTR->GetPortDiagCtrlIF()->GetConfDisInfo();
	return NO_ERROR;
}

EmTpAudioFormat CCnclibDataMgr::GetAudioFormatInfo() const
{
	return CNCSESSION_MGR_PTR->GetPortDiagCtrlIF()->GetAudioFormatInfo();
}

bool CCnclibDataMgr::IsRcvDual()
{
	return CNCSESSION_MGR_PTR->GetConfCtrlIF()->IsRcvDual();
}

BOOL CCnclibDataMgr::GetDisplayState() const
{
	return CNCSESSION_MGR_PTR->GetCenterCtrlIF()->GetDisplayState();
}

TTPDisplayType CCnclibDataMgr::GetDisplayType1() const
{
	return CNCSESSION_MGR_PTR->GetCenterCtrlIF()->GetDisplayType1();
}

TTPDisplayType CCnclibDataMgr::GetDisplayType3() const
{
	return CNCSESSION_MGR_PTR->GetCenterCtrlIF()->GetDisplayType3();
}

