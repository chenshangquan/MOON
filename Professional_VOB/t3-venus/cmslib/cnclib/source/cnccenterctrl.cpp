#include "StdAfx.h"
#include "cnccenterctrl.h"

CCncCenterCtrl::CCncCenterCtrl(CCnsSession &cSession):CCncCenterCtrlIF()
{
	m_pSession = &cSession;
	BuildEventsMap();
}

CCncCenterCtrl::~CCncCenterCtrl()
{

}

void CCncCenterCtrl::BuildEventsMap()
{ 
    REG_PFUN( ev_cns_centreSchStateNty, OnSchStateNty );
    REG_PFUN( ev_Cn_Sch_Temp_FB_Notify, OnSchTempNty );
    
    REG_PFUN( ev_Cn_Sch_Power_Ind, OnSchPowerInd );
    REG_PFUN( ev_Cn_Sch_Power_FB_Notify, OnSchPowerNty );
    REG_PFUN( ev_Cn_Sch_Light_Ind, OnSchLightInd );
    REG_PFUN( ev_Cn_Sch_Light_FB_Notify, OnSchLightNty );
    REG_PFUN( ev_Cn_Sch_MidLight_Ind, OnSchMainLightInd );
    REG_PFUN( ev_Cn_Sch_ScrLight_Ind, OnSchAuxiLightInd );

    REG_PFUN( ev_cns_centreTVStateNty, OnTvStateNty );
    REG_PFUN( ev_cns_centreselectTV_Ind, OnSeleteTvInd );
    REG_PFUN( ev_cns_centreTVMode_Ind, OnTvPowerModeInd );
    REG_PFUN( ev_cns_centreTVAudVisMode_Ind, OnTvAudVisModeInd );
    REG_PFUN( ev_cns_centreTVDisMode_Ind, OnTvDisModeInd );  
    REG_PFUN( ev_cns_centreTVInpSelect_Ind, OnTvAudInpSelectInd );  

    REG_PFUN( ev_Cn_DCamPower_Ind, OnDCamPowerInd );
    REG_PFUN( ev_Cn_DCamAFMode_Ind, OnDCamAFModeInd );
    REG_PFUN( ev_Cn_DCamWBMode_Ind, OnDCamWBModeInd );
    REG_PFUN( ev_Cn_DCamZoom_Ind, OnDCamZoomInd );
    REG_PFUN( ev_Cn_DCamPreset_Ind, OnDCamPresetInd );
    REG_PFUN( ev_Cn_DCamRecall_Ind, OnDCamRecallInd );
    REG_PFUN( ev_cns_centreDCamStateNty, OnDCamStateNty );

    REG_PFUN( ev_cns_centreACStateNty, OnACStateNty );
    REG_PFUN( ev_Cn_CentreSetACTempInd, OnACTempInd );
    REG_PFUN( ev_Cn_CentreSetACModeInd, OnACModeInd );
    REG_PFUN( ev_Cn_CentreSetAirVolInd, OnACAirVolInd );
	REG_PFUN( ev_Cn_CentreSetACPowerInd, OnAirPowerInd );
	REG_PFUN( ev_cns_centreSelectAC_Ind, OnSeleteAirInd );
	REG_PFUN( ev_cns_centreACCopyInd, OnApplyToAllInd);
 
	REG_PFUN( ev_Cn_CamPowerStateNty, OnCamStateNty );

	REG_PFUN( ev_CnCfgDisplay_Ind, OnDisplayInd );

	//REG_PFUN( ev_Cn_CentreSleepNty, OnCentreSleepNty ); //在cnssession中响应
	REG_PFUN( ev_Cn_centreCurNameNty, OnCurtainStateNty );
	REG_PFUN( ev_Cn_centreCurActInd, OnCurtainActInd );
    
	//断链通知
	REG_PFUN( OSP_DISCONNECT, OnLinkBreak );
}

void CCncCenterCtrl::DispEvent(const CMessage &cMsg)
{
	DISP_FUN(CCncCenterCtrl, cMsg);
}

void CCncCenterCtrl::OnLinkBreak(const CMessage& cMsg)
{
	m_bDisplay = FALSE;
	memset( &m_tDisplayType1, 0, sizeof(m_tDisplayType1) );
	memset( &m_tDisplayType3, 0, sizeof(m_tDisplayType3) );
	memset( m_atbIsCtrl, 0, sizeof(m_atbIsCtrl) );
    PrtMsg( OSP_DISCONNECT, emEventTypecnstoolRecv,"[CCncCenterCtrl::OnLinkBreak]清空配置信息" );
}

void CCncCenterCtrl::OnTimeOut(u16 wEvent)
{
	
}

//系统电源
u16 CCncCenterCtrl::SetSysPower( EmSchPower emPower )
{
    CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();  
    pcTpMsg->SetUserData( m_pSession->GetInst() );
    pcTpMsg->SetEvent( ev_Cn_Sch_Power_Cmd );
    pcTpMsg->SetBody( &emPower, sizeof(EmSchPower) );
    
    u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
    
    PrtMsg( ev_Cn_Sch_Power_Cmd, emEventTypeCnsSend, "EmSchPower: %d", emPower );
    
    return wRet;
}

void CCncCenterCtrl::OnSchPowerInd( const CMessage& cMsg )
{
    CTpMsg cTpMsg(&cMsg);

    BOOL bOk = *(BOOL*)( cTpMsg.GetBody() );

    EmSchPower emPower = *(EmSchPower*)( cTpMsg.GetBody() + sizeof(BOOL) );
    
    PrtMsg( ev_Cn_Sch_Power_Ind, emEventTypeCnsRecv, "BOOL: %d, EmSchPower: %d", bOk, emPower );

    PostEvent( UI_CNS_SCHPOWER_IND, bOk, emPower );
}

void CCncCenterCtrl::OnSchPowerNty( const CMessage& cMsg )
{
    CTpMsg cTpMsg(&cMsg);
    
    EmSchPower emPower = *(EmSchPower*)( cTpMsg.GetBody() );
    
    PrtMsg( ev_Cn_Sch_Power_FB_Notify, emEventTypeCnsRecv, "EmSchPower: %d", emPower );
}



u16 CCncCenterCtrl::SetSysAllLight( EmSchLight emLight )
{
    CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();  
    pcTpMsg->SetUserData( m_pSession->GetInst() );
    pcTpMsg->SetEvent( ev_Cn_Sch_Light_Cmd );
    pcTpMsg->SetBody( &emLight, sizeof(EmSchLight) );
    
    u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
    
    PrtMsg( ev_Cn_Sch_Light_Cmd, emEventTypeCnsSend, "EmSchLight: %d", emLight );
    
    return wRet;
}

void CCncCenterCtrl::OnSchLightInd( const CMessage& cMsg )
{
    CTpMsg cTpMsg(&cMsg);
    
    BOOL bOk = *(BOOL*)( cTpMsg.GetBody() );
    EmSchLight emLight = *(EmSchLight*)( cTpMsg.GetBody() + sizeof(BOOL) );
    
    PrtMsg( ev_Cn_Sch_Light_Ind, emEventTypeCnsRecv, "BOOL: %d, EmSchLight: %d", bOk, emLight );

    PostEvent( UI_CNS_SCHALLLIGHT_IND, bOk, emLight );
}

void CCncCenterCtrl::OnSchLightNty( const CMessage& cMsg )
{
    CTpMsg cTpMsg(&cMsg);
    
    EmSchLight emLight = *(EmSchLight*)( cTpMsg.GetBody() );
    
    PrtMsg( ev_Cn_Sch_Light_FB_Notify, emEventTypeCnsRecv, "EmSchLight: %d", emLight );

    PostEvent( UI_CNS_SCHLIGHT_NTY, emLight );
}

u16 CCncCenterCtrl::SetMainLight( EmSchMidLight emMidLight )
{
    CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();  
    pcTpMsg->SetUserData( m_pSession->GetInst() );
    pcTpMsg->SetEvent( ev_Cn_Sch_MidLight_Cmd );
    pcTpMsg->SetBody( &emMidLight, sizeof(EmSchMidLight) );
    
    u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
    
    PrtMsg( ev_Cn_Sch_MidLight_Cmd, emEventTypeCnsSend, "EmSchMidLight: %d", emMidLight );
    
    return wRet;
}

void CCncCenterCtrl::OnSchMainLightInd( const CMessage& cMsg )
{
    CTpMsg cTpMsg(&cMsg);
    
    BOOL bOk = *(BOOL*)( cTpMsg.GetBody() );
    EmSchMidLight emLight = *(EmSchMidLight*)( cTpMsg.GetBody() + sizeof(BOOL) );
    
    PrtMsg( ev_Cn_Sch_MidLight_Ind, emEventTypeCnsRecv, "BOOL: %d, EmSchMidLight: %d", bOk, emLight );

    PostEvent( UI_CNS_SCHMIDLIGHT_IND, bOk, emLight );
}

u16 CCncCenterCtrl::SetAuxiLight( EmSchScrLight emScrLight )
{
    CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();  
    pcTpMsg->SetUserData( m_pSession->GetInst() );
    pcTpMsg->SetEvent( ev_Cn_Sch_ScrLight_Cmd );
    pcTpMsg->SetBody( &emScrLight, sizeof(EmSchScrLight) );
    
    u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
    
    PrtMsg( ev_Cn_Sch_ScrLight_Cmd, emEventTypeCnsSend, "EmSchScrLight: %d", emScrLight );
    
    return wRet;
}

void CCncCenterCtrl::OnSchAuxiLightInd( const CMessage& cMsg )
{
    CTpMsg cTpMsg(&cMsg);
    
    BOOL bOk = *(BOOL*)( cTpMsg.GetBody() );
    EmSchScrLight emLight = *(EmSchScrLight*)( cTpMsg.GetBody() + sizeof(BOOL) );
    
    PrtMsg( ev_Cn_Sch_ScrLight_Ind, emEventTypeCnsRecv, "BOOL: %d, EmSchScrLight: %d", bOk, emLight );

    PostEvent( UI_CNS_SCHSCRLIGHT_IND, bOk, emLight );
}

void CCncCenterCtrl::OnSchTempNty( const CMessage& cMsg )
{
    CTpMsg cTpMsg(&cMsg);
    
    u16 wTemp = *(u16*)( cTpMsg.GetBody() );
    
    PrtMsg( ev_Cn_Sch_Temp_FB_Notify, emEventTypeCnsRecv, "Temp: %d", wTemp );

    PostEvent( UI_CNS_SCHTEMP_NTY, wTemp );
}

void CCncCenterCtrl::OnSchStateNty( const CMessage& cMsg )
{
    CTpMsg cTpMsg(&cMsg);
    
    TCentreSchCfg tSchCfg = *(TCentreSchCfg*)( cTpMsg.GetBody() );
    
    PrtMsg( ev_cns_centreSchStateNty, emEventTypeCnsRecv, "EmSchPower: %d, EmSchLight: %d, EmSchMidLight: %d, EmSchScrLight: %d, Temp: %d",
        tSchCfg.emSchPower, tSchCfg.emSchLight, tSchCfg.emSchMidLight, tSchCfg.emSchScrLight, tSchCfg.wSchTem );

    PostEvent( UI_CNS_SCHSTATE_NTY, (WPARAM)&tSchCfg );
}



//电视机
u16 CCncCenterCtrl::SelectTV( u8 byIndex )
{
    CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();  
    pcTpMsg->SetUserData( m_pSession->GetInst() );
    pcTpMsg->SetEvent( ev_cns_centreselectTV_cmd );
    pcTpMsg->SetBody( &byIndex, sizeof(u8) );
    
    u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
    
    PrtMsg( ev_cns_centreselectTV_cmd, emEventTypeCnsSend, "Index: %d", byIndex );
    
	return wRet;
}

u16 CCncCenterCtrl::SetTVPowerMode( u8 byIndex, EmTvPowerMode emMode )
{
    CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();  
    pcTpMsg->SetUserData( m_pSession->GetInst() );
    pcTpMsg->SetEvent( ev_cns_centreTVMode_cmd );  
    pcTpMsg->SetBody( &emMode, sizeof(EmTvPowerMode) );
    pcTpMsg->CatBody( &byIndex, sizeof(u8) );
    
    u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
    
    PrtMsg( ev_cns_centreTVMode_cmd, emEventTypeCnsSend, "Index: %d, EmTvPowerMode: %d", byIndex, emMode );
    
	return wRet;
}

u16 CCncCenterCtrl::SetTVAudVisMode( EmTVAudVisMode emMode )
{
    CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();  
    pcTpMsg->SetUserData( m_pSession->GetInst() );
    pcTpMsg->SetEvent( ev_cns_centreTVAudVisMode_cmd );
    pcTpMsg->SetBody( &emMode, sizeof(EmTVAudVisMode) );
    
    u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
    
    PrtMsg( ev_cns_centreTVAudVisMode_cmd, emEventTypeCnsSend, "EmAudVisMode: %d", emMode );
    
    return wRet;
}

u16 CCncCenterCtrl::SetTVDisMode( EmTVDisplayMode emMode )
{
    CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();  
    pcTpMsg->SetUserData( m_pSession->GetInst() );
    pcTpMsg->SetEvent( ev_cns_centreTVDisMode_cmd );
    pcTpMsg->SetBody( &emMode, sizeof(EmTVDisplayMode) );
    
    u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
    
    PrtMsg( ev_cns_centreTVDisMode_cmd, emEventTypeCnsSend, "EmDisplayMode: %d", emMode );
    
    return wRet;
}

u16 CCncCenterCtrl::SetTVInpSelect( u8 byIndex,  EmTVInputSelect emSelect )
{
    CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();  
    pcTpMsg->SetUserData( m_pSession->GetInst() );
    pcTpMsg->SetEvent( ev_cns_centreTVInpSelect_cmd );
    pcTpMsg->SetBody( &byIndex, sizeof(u8) );
	pcTpMsg->CatBody( &emSelect, sizeof(EmTVInputSelect) );
    u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
    
    PrtMsg( ev_cns_centreTVInpSelect_cmd, emEventTypeCnsSend,  "Index: %d, EmInputSelect: %d", byIndex, emSelect );
    
    return wRet;
}

void CCncCenterCtrl::OnTvStateNty(const CMessage& cMsg)
{
    CTpMsg cTpMsg(&cMsg);

    TCentreTVCfg *ptCentreTVCfg = reinterpret_cast<TCentreTVCfg *>(cTpMsg.GetBody());

    memcpy( m_atTVCfg, ptCentreTVCfg, sizeof(TCentreTVCfg)*MAX_CENTRETV_NUM );
    
    PrtMsg( ev_cns_centreTVStateNty, emEventTypeCnsRecv, "TvPowerMode1: %d, TvPowerMode2: %d, TvPowerMode3: %d",
        m_atTVCfg[0].emTvPowerMode, m_atTVCfg[1].emTvPowerMode, m_atTVCfg[2].emTvPowerMode );

    PostEvent( UI_CNS_TVSTATE_NTY );
}

TCentreTVCfg* CCncCenterCtrl::GetCentreTVCfg()
{
    return m_atTVCfg;
}


void CCncCenterCtrl::OnSeleteTvInd(const CMessage& cMsg)
{
    CTpMsg cTpMsg(&cMsg);

    u8 byIndex = *(u8*)( cTpMsg.GetBody() );
    BOOL bOk = *(BOOL*)( cTpMsg.GetBody() + sizeof(u8) );

    PrtMsg( ev_cns_centreselectTV_Ind, emEventTypeCnsRecv, "Index: %d, bOk: %d", byIndex, bOk );
	PostEvent( UI_CNS_SELETETV_IND, byIndex, bOk);
}

void CCncCenterCtrl::OnTvPowerModeInd(const CMessage& cMsg)
{
    CTpMsg cTpMsg(&cMsg);
    
    EmTvPowerMode emMode = *(EmTvPowerMode*)( cTpMsg.GetBody() );
    u8 byIndex = *(u8*)( cTpMsg.GetBody() + sizeof(EmTvPowerMode) );
    BOOL bOk = *(BOOL*)( cTpMsg.GetBody() + sizeof(EmTvPowerMode) + sizeof(u8) );
    
    PrtMsg( ev_cns_centreTVMode_Ind, emEventTypeCnsRecv, "EmTvPowerMode: %d, Index: %d, bOK: %d", emMode, byIndex, bOk );

    if ( !bOk )
    {
        PostEvent( UI_CNS_TVPOWERMODE_IND, byIndex, emMode );
    }   
}

void CCncCenterCtrl::OnTvAudVisModeInd(const CMessage& cMsg)
{
    CTpMsg cTpMsg(&cMsg);
    
    EmTVAudVisMode emMode = *(EmTVAudVisMode*)( cTpMsg.GetBody() );
    BOOL bOk = *(BOOL*)( cTpMsg.GetBody() + sizeof(EmTVAudVisMode) );
    
    PrtMsg( ev_cns_centreTVAudVisMode_Ind, emEventTypeCnsRecv, "EmTVAudVisMode: %d, bOK: %d", emMode, bOk );
}

void CCncCenterCtrl::OnTvDisModeInd(const CMessage& cMsg)
{
    CTpMsg cTpMsg(&cMsg);
    
    EmTVDisplayMode emMode = *(EmTVDisplayMode*)( cTpMsg.GetBody() );
    BOOL bOk = *(BOOL*)( cTpMsg.GetBody() + sizeof(EmTVDisplayMode) );
    
    PrtMsg( ev_cns_centreTVDisMode_Ind, emEventTypeCnsRecv, "EmTVDisplayMode: %d, bOK: %d", emMode, bOk );
}

void CCncCenterCtrl::OnTvAudInpSelectInd(const CMessage& cMsg)
{
    CTpMsg cTpMsg(&cMsg);
    
	u8 byIndex = *(u8*)( cTpMsg.GetBody() );
    EmTVInputSelect emMode = *(EmTVInputSelect*)( cTpMsg.GetBody() + sizeof(u8) );
    BOOL bOk = *(BOOL*)( cTpMsg.GetBody() + sizeof(EmTVInputSelect) + sizeof(u8) );
    
    PrtMsg( ev_cns_centreTVInpSelect_Ind, emEventTypeCnsRecv, "Index: %d, EmTVInputSelect: %d, bOK: %d", byIndex, emMode, bOk );
}


//文档摄像机
u16 CCncCenterCtrl::SetDCamPower( EmDCamPower emPower )
{
    CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();  
    pcTpMsg->SetUserData( m_pSession->GetInst() );
    pcTpMsg->SetEvent( ev_Cn_DCamPower_Cmd );
    pcTpMsg->SetBody( &emPower, sizeof(EmDCamPower) );
    
    u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
    
    PrtMsg( ev_Cn_DCamPower_Cmd, emEventTypeCnsSend, "EmDCamPower: %d", emPower );

    return wRet;
}

//自动焦距
u16 CCncCenterCtrl::SetDCamAFMode( EmDCamAFMode emMode )
{
    CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();  
    pcTpMsg->SetUserData( m_pSession->GetInst() );
    pcTpMsg->SetEvent( ev_Cn_DCamAFMode_Cmd );
    pcTpMsg->SetBody( &emMode, sizeof(EmDCamAFMode) );
    
    u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
    
    PrtMsg( ev_Cn_DCamAFMode_Cmd, emEventTypeCnsSend, "EmDCamAFMode: %d", emMode );
    
    return wRet;
}

//白平衡模式
u16 CCncCenterCtrl::SetDCamWBMode( EmDCamWBMode emMode )
{
    CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();  
    pcTpMsg->SetUserData( m_pSession->GetInst() );
    pcTpMsg->SetEvent( ev_Cn_DCamWBMode_Cmd );
    pcTpMsg->SetBody( &emMode, sizeof(EmDCamWBMode) );
    
    u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
    
    PrtMsg( ev_Cn_DCamWBMode_Cmd, emEventTypeCnsSend, "EmDCamWBMode: %d", emMode );
    
    return wRet;
}

//视野调节
u16 CCncCenterCtrl::SetDCamZoom( EmDCamZoom emZoom, EmCnAction emAction )
{
    CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();  
    pcTpMsg->SetUserData( m_pSession->GetInst() );
    pcTpMsg->SetEvent( ev_Cn_DCamZoom_Cmd );
    pcTpMsg->SetBody( &emAction, sizeof(EmCnAction) );
    pcTpMsg->CatBody( &emZoom, sizeof(EmDCamZoom) );
    
    u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);

    PrtMsg( ev_Cn_DCamZoom_Cmd, emEventTypeCnsSend,"EmCnAction: %d,EmZoom: %d",emAction, emZoom );
    
    return wRet;
}

//预置位
u16 CCncCenterCtrl::SetDCamPreset( EmDCamPresetNum emNum )
{
    CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();  
    pcTpMsg->SetUserData( m_pSession->GetInst() );
    pcTpMsg->SetEvent( ev_Cn_DCamPreset_Cmd );
    pcTpMsg->SetBody( &emNum, sizeof(EmDCamPresetNum) );
    
    u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
    
    PrtMsg( ev_Cn_DCamPreset_Cmd, emEventTypeCnsSend, "EmDCamPresetNum: %d", emNum  );
    
    return wRet;
}

u16 CCncCenterCtrl::SetDCamRecall( EmDCamRecallNum emNum )
{
    CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();  
    pcTpMsg->SetUserData( m_pSession->GetInst() );
    pcTpMsg->SetEvent( ev_Cn_DCamRecall_Cmd );
    pcTpMsg->SetBody( &emNum, sizeof(EmDCamRecallNum) );
    
    u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
    
    PrtMsg( ev_Cn_DCamRecall_Cmd, emEventTypeCnsSend, "EmDCamPresetNum: %d", emNum  );
    
    return wRet;
}


void CCncCenterCtrl::OnDCamPowerInd(const CMessage& cMsg)
{
    CTpMsg cTpMsg(&cMsg);

    BOOL bOk = *(BOOL*)( cTpMsg.GetBody() );
    EmDCamPower emPower = *(EmDCamPower*)( cTpMsg.GetBody() + sizeof(BOOL) );
    
    PrtMsg( ev_Cn_DCamPower_Ind, emEventTypeCnsRecv, "bOk: %d, EmDCamPower: %d", bOk, emPower );

    PostEvent( UI_CNS_DCAMPOWER_IND, bOk, emPower );
}

void CCncCenterCtrl::OnDCamAFModeInd(const CMessage& cMsg)
{
    CTpMsg cTpMsg(&cMsg);
    
    BOOL bOk = *(BOOL*)( cTpMsg.GetBody() );
    EmDCamAFMode emMode = *(EmDCamAFMode*)( cTpMsg.GetBody() + sizeof(BOOL) );
    
    PrtMsg( ev_Cn_DCamAFMode_Ind, emEventTypeCnsRecv, "bOk: %d, EmDCamAFMode: %d", bOk, emMode );
}

void CCncCenterCtrl::OnDCamWBModeInd(const CMessage& cMsg)
{
    CTpMsg cTpMsg(&cMsg);
    
    BOOL bOk = *(BOOL*)( cTpMsg.GetBody() );
    EmDCamWBMode emMode = *(EmDCamWBMode*)( cTpMsg.GetBody() + sizeof(BOOL) );
    
    PrtMsg( ev_Cn_DCamWBMode_Ind, emEventTypeCnsRecv, "bOk: %d, EmDCamWBMode: %d", bOk, emMode );
}

void CCncCenterCtrl::OnDCamZoomInd(const CMessage& cMsg)
{
    CTpMsg cTpMsg(&cMsg);
    
    BOOL bOk = *(BOOL*)( cTpMsg.GetBody() );
    EmDCamZoom emZoom = *(EmDCamZoom*)( cTpMsg.GetBody() + sizeof(BOOL) );
    
    PrtMsg( ev_Cn_DCamZoom_Ind, emEventTypeCnsRecv, "bOk: %d, EmDCamZoom: %d", bOk, emZoom );
}

void CCncCenterCtrl::OnDCamPresetInd(const CMessage& cMsg)
{
    CTpMsg cTpMsg(&cMsg);
    
    BOOL bOk = *(BOOL*)( cTpMsg.GetBody() );
    EmDCamPresetNum emNum = *(EmDCamPresetNum*)( cTpMsg.GetBody() + sizeof(BOOL) );
    
    PrtMsg( ev_Cn_DCamPreset_Ind, emEventTypeCnsRecv, "bOk: %d, EmDCamPresetNum: %d", bOk, emNum );
}

void CCncCenterCtrl::OnDCamRecallInd(const CMessage& cMsg)
{
    CTpMsg cTpMsg(&cMsg);
    
    BOOL bOk = *(BOOL*)( cTpMsg.GetBody() );
    EmDCamRecallNum emNum = *(EmDCamRecallNum*)( cTpMsg.GetBody() + sizeof(BOOL) );
    
    PrtMsg( ev_Cn_DCamRecall_Ind, emEventTypeCnsRecv, "bOk: %d, EmDCamRecallNum: %d", bOk, emNum );
}

void CCncCenterCtrl::OnDCamStateNty(const CMessage& cMsg)
{
    CTpMsg cTpMsg(&cMsg);

    TCentreDCamCfg tDCamCfg = *(TCentreDCamCfg*)( cTpMsg.GetBody() );
    
    PrtMsg( ev_cns_centreDCamStateNty, emEventTypeCnsRecv, "EmDCamPower: %d, EmDCamRecallNum: %d",
        tDCamCfg.emDCamPowerMode, tDCamCfg.emDCamRecallNum );

    PostEvent( UI_CNS_DCAMSTATE_NTY, (WPARAM)&tDCamCfg );
}


//空调
u16 CCncCenterCtrl::SetACTemp( u8 byTemp )
{
    CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();  
    pcTpMsg->SetUserData( m_pSession->GetInst() );
    pcTpMsg->SetEvent( ev_Cn_CentreSetACTempCmd );
    pcTpMsg->SetBody( &byTemp, sizeof(u8) );
    
    u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
    
    PrtMsg( ev_Cn_CentreSetACTempCmd, emEventTypeCnsSend, "Temp: %d", byTemp  );
    
    return wRet;
}

void CCncCenterCtrl::OnACTempInd(const CMessage& cMsg)
{
    CTpMsg cTpMsg(&cMsg);
    
    u8 byTemp = *(u8*)( cTpMsg.GetBody() );
    BOOL bOk = *(BOOL*)( cTpMsg.GetBody() + sizeof(u8) );
    
    PrtMsg( ev_Cn_CentreSetACTempInd, emEventTypeCnsRecv, "Temp: %d, bOk: %d", byTemp, bOk );
}

u16 CCncCenterCtrl::SetACMode( EmCentreACMode emMode )
{
    CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();  
    pcTpMsg->SetUserData( m_pSession->GetInst() );
    pcTpMsg->SetEvent( ev_Cn_CentreSetACModeCmd );
    pcTpMsg->SetBody( &emMode, sizeof(EmCentreACMode) );
    
    u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
    
    PrtMsg( ev_Cn_CentreSetACModeCmd, emEventTypeCnsSend, "EmCentreACMode: %d", emMode  );
    
    return wRet;
}

void CCncCenterCtrl::OnACModeInd(const CMessage& cMsg)
{
    CTpMsg cTpMsg(&cMsg);
    
    EmCentreACMode emMode = *(EmCentreACMode*)( cTpMsg.GetBody() );
    BOOL bOk = *(BOOL*)( cTpMsg.GetBody() + sizeof(EmCentreACMode) );
    
    PrtMsg( ev_Cn_CentreSetACModeInd, emEventTypeCnsRecv, "EmCentreACMode: %d, bOk: %d", emMode, bOk );
}

u16 CCncCenterCtrl::SetACAirVol( EmCentreACAirVol emAirVol )
{
    CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();  
    pcTpMsg->SetUserData( m_pSession->GetInst() );
    pcTpMsg->SetEvent( ev_Cn_CentreSetACAirVolCmd );
    pcTpMsg->SetBody( &emAirVol, sizeof(EmCentreACAirVol) );
    
    u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
    
    PrtMsg( ev_Cn_CentreSetACAirVolCmd, emEventTypeCnsSend, "EmCentreACAirVol: %d", emAirVol );
    
    return wRet;
}

void CCncCenterCtrl::OnACAirVolInd(const CMessage& cMsg)
{
    CTpMsg cTpMsg(&cMsg);
    
    EmCentreACAirVol emAirVol = *(EmCentreACAirVol*)( cTpMsg.GetBody() );
    BOOL bOk = *(BOOL*)( cTpMsg.GetBody() + sizeof(EmCentreACAirVol) );
    
    PrtMsg( ev_Cn_CentreSetAirVolInd, emEventTypeCnsRecv, "EmCentreACAirVol: %d, bOk: %d", emAirVol, bOk );
}


// void CCncCenterCtrl::OnACStateNty(const CMessage& cMsg)
// {
//     CTpMsg cTpMsg(&cMsg);
//     
//     TCentreACCfg tACCfg = *(TCentreACCfg*)( cTpMsg.GetBody() );
//     
//     PrtMsg( ev_cns_centreACStateNty, emEventTypeCnsRecv, "ACPower:%d, EmCentreACMode: %d, SetTemp: %d, CurTemp: %d, AirVol: %d",
//         tACCfg.emACPower ,tACCfg.emACMode, tACCfg.bySetTemp, tACCfg.byCurTemp, tACCfg.emACAirVol );
//     
//     PostEvent( UI_CNS_ACSTATE_NTY, (WPARAM)&tACCfg );
// }

//空调界面电源开关控制 by wqq
// u16 CCncCenterCtrl::SetAirPower( EmCentreACPower emPower )
// {
//     CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();  
//     pcTpMsg->SetUserData( m_pSession->GetInst() );
//     pcTpMsg->SetEvent( ev_Cn_CentreSetACPowerCmd );
//     pcTpMsg->SetBody( &emPower, sizeof( EmCentreACPower ) );
//     
//     u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
//     
//     PrtMsg( ev_Cn_CentreSetACPowerCmd, emEventTypeCnsSend, "EmCentreACPower: %d", emPower );
// 	
//     return wRet;
// }

u16 CCncCenterCtrl::SelectAir( u8 byIndex )
{
    CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();  
    pcTpMsg->SetUserData( m_pSession->GetInst() );
    pcTpMsg->SetEvent( ev_cns_centreSelectAC_Cmd );
    pcTpMsg->SetBody( &byIndex, sizeof(u8) );
    
    u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
    
    PrtMsg( ev_cns_centreSelectAC_Cmd, emEventTypeCnsSend, "Index: %d", byIndex );
    
	return wRet;
}

//选择空调项回复消息
void CCncCenterCtrl::OnSeleteAirInd(const CMessage& cMsg)
{
    CTpMsg cTpMsg(&cMsg);
	
    u8 byIndex = *(u8*)( cTpMsg.GetBody() );
    BOOL bOk = *(BOOL*)( cTpMsg.GetBody() + sizeof(u8) );
	
    PrtMsg( ev_cns_centreSelectAC_Ind, emEventTypeCnsRecv, "Index: %d, bOk: %d", byIndex, bOk );

	PostEvent( UI_CNS_SELECTAIR_IND, byIndex, bOk );
}

void CCncCenterCtrl::OnACStateNty(const CMessage& cMsg)
{
    CTpMsg cTpMsg(&cMsg);
	
	for ( int i = 0; i < MAX_AC_NUM; i++ )
	{
		TCentreACCfg tCentreACCfg = *reinterpret_cast<TCentreACCfg *>(cTpMsg.GetBody() + sizeof(TCentreACCfg)*i);
		
		BOOL bIsExist = *(BOOL *)(cTpMsg.GetBody() + sizeof(TCentreACCfg)*MAX_AC_NUM + sizeof(BOOL)*i);
		
		
		if ( bIsExist == TRUE)
		{
			m_vecTCentreACCfg.push_back( tCentreACCfg );
		}
	}
    
    PrtMsg( ev_cns_centreACStateNty, emEventTypeCnsRecv, "OnACStateNty" );
	
	PostEvent( UI_CNS_ACSTATE_NTY );
}

void CCncCenterCtrl::GetCentreACCfg( vector<TCentreACCfg> &vecTCentreACCfg )const
{
     vecTCentreACCfg = m_vecTCentreACCfg;
	 return;
}

u16 CCncCenterCtrl::SetACPowerMode( u8 byIndex, EmCentreACPower emMode )
{
    CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();  
    pcTpMsg->SetUserData( m_pSession->GetInst() );
    pcTpMsg->SetEvent( ev_Cn_CentreSetACPowerCmd );  
	pcTpMsg->SetBody( &byIndex, sizeof(u8) );
    pcTpMsg->CatBody( &emMode, sizeof(EmCentreACPower) );
    
    u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
    
    PrtMsg( ev_Cn_CentreSetACPowerCmd, emEventTypeCnsSend, "Index: %d, EmCentreACPower: %d", byIndex, emMode );
    
	return wRet;
}

void CCncCenterCtrl::OnAirPowerInd(const CMessage& cMsg)
{
    CTpMsg cTpMsg(&cMsg);
	u8 byIndex = *(u8*)( cTpMsg.GetBody() );
	EmCentreACPower emPower = *(EmCentreACPower*)( cTpMsg.GetBody() + sizeof( u8 ) );
    BOOL bOk = *(BOOL*)( cTpMsg.GetBody() +sizeof(u8) +sizeof( EmCentreACPower ) );
	
    PrtMsg( ev_Cn_CentreSetACPowerInd, emEventTypeCnsRecv, "Index: %d, EmCentreACPower: %d, bOk: %d", byIndex, emPower, bOk );
	
    //PostEvent( UI_CNS_ACPOWERSTATE_IND, emPower, bOk );
}

u16 CCncCenterCtrl::SetApplyToAll( u8 byIndex, BOOL** atbIsCtrl )
{
	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr(); 
	pcTpMsg->SetUserData( m_pSession->GetInst() );

	pcTpMsg->SetEvent( ev_cns_centreACCopyCmd ); 
	pcTpMsg->SetBody( &byIndex, sizeof(u8) );
	pcTpMsg->CatBody( *atbIsCtrl, sizeof(BOOL) );
	pcTpMsg->CatBody( (*atbIsCtrl)+1, sizeof(BOOL) );
	pcTpMsg->CatBody( (*atbIsCtrl)+2, sizeof(BOOL) );
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_cns_centreACCopyCmd, emEventTypeCnsSend,"Index: %d, SetApplyToAll", byIndex );
	return wRet;
}

void CCncCenterCtrl::OnApplyToAllInd(const CMessage& cMsg)
{
	CTpMsg cTpMsg(&cMsg);
	for ( int i = 0; i < MAX_AC_NUM; i++ )
	{
		BOOL bIsInCtrl = *(BOOL*)( cTpMsg.GetBody()+sizeof(BOOL)*i );
		m_atbIsCtrl[i] = bIsInCtrl;
		BOOL bSuccess = *(BOOL*)( cTpMsg.GetBody()+3*sizeof(BOOL)+sizeof(BOOL)*i );
	}
	PrtMsg( ev_cns_centreACCopyInd, emEventTypeCnsRecv,"OnApplyToAllInd" );

//	PostEvent( UI_CNS_APPLYTOALL_IND );
}

BOOL* CCncCenterCtrl::GetApplyToAllInfo()
{
	return m_atbIsCtrl;
}

//摄像机
void CCncCenterCtrl::OnCamStateNty( const CMessage& cMsg )
{
	CTpMsg cTpMsg(&cMsg);
	EmCamPowerMode aemCam[MAX_CNCAMERA_NUM];
	for ( int i=0; i<MAX_CNCAMERA_NUM; i++ )
	{
		aemCam[i] = *(EmCamPowerMode*)( cTpMsg.GetBody() + i*sizeof(EmCamPowerMode) );
	}
     
    PrtMsg( ev_Cn_CamPowerStateNty, emEventTypeCnsRecv, "Cam1: %d, Cam2: %d, Cam3: %d", aemCam[0], aemCam[1], aemCam[2] );
	
    PostEvent( UI_CNSTOOL_MSG_CamPowerState_NTY, (WPARAM)aemCam );
}


void CCncCenterCtrl::OnCentreSleepNty(const CMessage& cMsg)
{
    CTpMsg cTpMsg(&cMsg);
    
    PrtMsg( ev_Cn_CentreSleepNty, emEventTypeCnsRecv, "" );
    
    PostEvent( UI_TPAD_CENTRESLEEP_NTY );
}

//中控电视墙
u16 CCncCenterCtrl::SetDisplayCmd( BOOL bDisplay, const TTPDisplayType& tDisplayType1, const TTPDisplayType& tDisplayType3 )
{
    CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();  
    pcTpMsg->SetUserData( m_pSession->GetInst() );
    pcTpMsg->SetEvent( ev_CnCfgDisplay_Cmd );  
	pcTpMsg->SetBody( &bDisplay, sizeof(BOOL) );
    pcTpMsg->CatBody( &tDisplayType1, sizeof(TTPDisplayType) );
    pcTpMsg->CatBody( &tDisplayType3, sizeof(TTPDisplayType) );
    
    u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
    
    PrtMsg( ev_CnCfgDisplay_Cmd, emEventTypeCnsSend, "bDisplay: %d, tDisplayType1: %d,%d, tDisplayType3: %d,%d \
<emTVHDMI1:%d,emTVHDMI2:%d,emTVHDMI3:%d,emTVHDMI4:%d,emTVYpbPr:%d,emTVCVBS1:%d,emTVCVBS2:%d,emTVComputer:%d>", 
bDisplay, tDisplayType1.emTPT300Type, tDisplayType1.emTPHduType, tDisplayType3.emTPT300Type, tDisplayType3.emTPHduType, \
emTVHDMI1, emTVHDMI2, emTVHDMI3, emTVHDMI4, emTVYpbPr, emTVCVBS1, emTVCVBS2, emTVComputer );
    
	return wRet;
}

const BOOL& CCncCenterCtrl::GetDisplayState() const
{
	return m_bDisplay;
}

const TTPDisplayType& CCncCenterCtrl::GetDisplayType1() const
{
	return m_tDisplayType1;
}

const TTPDisplayType& CCncCenterCtrl::GetDisplayType3() const
{
	return m_tDisplayType3;
}

void CCncCenterCtrl::OnDisplayInd( const CMessage& cMsg )
{
	CTpMsg cTpMsg(&cMsg);
	m_bDisplay = *(BOOL*)cTpMsg.GetBody();
	m_tDisplayType1 = *(TTPDisplayType*)( cTpMsg.GetBody() + sizeof(BOOL) );
	m_tDisplayType3 = *(TTPDisplayType*)( cTpMsg.GetBody() + sizeof(TTPDisplayType) + sizeof(BOOL) );
	BOOL bSuccess = *(BOOL*)( cTpMsg.GetBody() + sizeof(TTPDisplayType)*2 + sizeof(BOOL) );

    PrtMsg( ev_CnCfgDisplay_Ind, emEventTypeCnsRecv, "bDisplay: %d, tDisplayType1: %d,%d, tDisplayType3: %d,%d \
<emTVHDMI1:%d,emTVHDMI2:%d,emTVHDMI3:%d,emTVHDMI4:%d,emTVYpbPr:%d,emTVCVBS1:%d,emTVCVBS2:%d,emTVComputer:%d>", 
m_bDisplay, m_tDisplayType1.emTPT300Type, m_tDisplayType1.emTPHduType, m_tDisplayType3.emTPT300Type, m_tDisplayType3.emTPHduType, \
emTVHDMI1, emTVHDMI2, emTVHDMI3, emTVHDMI4, emTVYpbPr, emTVCVBS1, emTVCVBS2, emTVComputer );
	
    PostEvent( UI_CNSTOOL_MSG_DISPLAY_IND, bSuccess, 0 );
}

//577 3/10
void CCncCenterCtrl::GetCentreCurName( vector<TCentreCurName> &vecTCentreCurName ) const
{
	vecTCentreCurName = m_vecTCentreCurName;
}

void CCncCenterCtrl::OnCurtainStateNty( const CMessage& cMsg )
{
	CTpMsg cTpMsg(&cMsg);

	m_vecTCentreCurName.clear();
	for ( int i=0; i < MAX_CURTAIN_NUM; i++ )
	{
		TCentreCurName tCentreCurName = *(TCentreCurName*)(cTpMsg.GetBody() + sizeof(TCentreCurName)*i);

		m_vecTCentreCurName.push_back( tCentreCurName );
		PrtMsg( ev_Cn_centreCurNameNty, emEventTypeCnsRecv, "%s ", tCentreCurName.achCurName );
	}

	u8 nCurNum = *(u8*)(cTpMsg.GetBody() + sizeof(TCentreCurName)*MAX_CURTAIN_NUM);

	PrtMsg( ev_Cn_centreCurNameNty, emEventTypeCnsRecv, "\n CurtainNum: %d", nCurNum );

	PostEvent( UI_TPAD_CURTAINSTATE_NTY, nCurNum );
}

u16 CCncCenterCtrl::SetCurtainState( BOOL** bIsCtrl, EmCurAction emCurAction )
{
	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr(); 
	pcTpMsg->SetUserData( m_pSession->GetInst() );
	
	pcTpMsg->SetEvent( ev_Cn_centreCurActCmd ); 
	pcTpMsg->SetBody( *bIsCtrl, sizeof(BOOL) );
	pcTpMsg->CatBody( (*bIsCtrl)+1, sizeof(BOOL) );
	pcTpMsg->CatBody( (*bIsCtrl)+2, sizeof(BOOL) );
	pcTpMsg->CatBody( (*bIsCtrl)+3, sizeof(BOOL) );
	pcTpMsg->CatBody( (*bIsCtrl)+4, sizeof(BOOL) );
	pcTpMsg->CatBody( (*bIsCtrl)+5, sizeof(BOOL) );
	pcTpMsg->CatBody( &emCurAction, sizeof(EmCurAction));
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_Cn_centreCurActCmd, emEventTypeCnsSend,"SetCurtainState" );
	return wRet;
}

void CCncCenterCtrl::OnCurtainActInd(const CMessage& cMsg)
{
	CTpMsg cTpMsg(&cMsg);
	for ( int i = 0; i < MAX_CURTAIN_NUM; i++ )
	{
		BOOL bIsCtrl = *(BOOL*)( cTpMsg.GetBody()+sizeof(BOOL)*i );
		m_bIsCtrl[i] = bIsCtrl;
		EmCurAction emCurAction = *(EmCurAction*)( cTpMsg.GetBody() + 6*sizeof(BOOL) );
		BOOL bSuccess = *(BOOL*)( cTpMsg.GetBody()+6*sizeof(BOOL)+sizeof(EmCurAction)+sizeof(BOOL)*i );
	}
	PrtMsg( ev_Cn_centreCurActInd, emEventTypeCnsRecv,"IsCtrl1: %d, IsCtrl2: %d, IsCtrl3: %d, IsCtrl4: %d, IsCtrl5: %d, IsCtrl6: %d", m_bIsCtrl[0], m_bIsCtrl[1], m_bIsCtrl[2], m_bIsCtrl[3], m_bIsCtrl[4], m_bIsCtrl[5] );
}



