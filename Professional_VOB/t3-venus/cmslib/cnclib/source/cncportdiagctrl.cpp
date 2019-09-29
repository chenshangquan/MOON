#include "StdAfx.h"
#include "cncportdiagctrl.h"

CCncPortDiagCtrl::CCncPortDiagCtrl(CCnsSession &cSession)
:CCncPortDiagCtrlIF()
{
	m_pSession = &cSession;
	BuildEventsMap();
}

CCncPortDiagCtrl::~CCncPortDiagCtrl()
{
	
}

void CCncPortDiagCtrl::BuildEventsMap()
{
	REG_PFUN( ev_tppSetAudioPort_Ind, OnAudioPortInfoInd );
	REG_PFUN( ev_tppAudioRestoreDefaults_Ind, OnDefaultAudPortInd );
	REG_PFUN( ev_tppGetLostPacketInfo_Rsp, OnLostPacketInfoRsp );
	REG_PFUN( ev_tppGetUpDownstreamRate_Nty, OnUpDownstreamRateNty );
	REG_PFUN( ev_tppSelAVMatrixProject_Ind, OnAVMatrixInfoInd );
	REG_PFUN( ev_tppGetTPadIpList_Rsp, OnTpadListRsp );
	REG_PFUN( ev_tppGetTPadIpList_Nty, OnTpadListNty );
	REG_PFUN( ev_tppSetAudiotMixer_Ind, OnAudiotMixerInd );
	REG_PFUN( ev_tppMixRestoreDefaults_Ind, OnDefaulttMixerInd );	
	REG_PFUN( ev_tppSetAudioEqualizer_Ind, OnAudioEqualizerInd );
	REG_PFUN( ev_tppEqualizerReDefaults_Ind, OnDefaultEqInd );
	REG_PFUN( ev_tppUpdate_Ind, OnUpgradeCnsInd );
	REG_PFUN( ev_tppSetCallServerInfo_Ind, OnCallServerInd );
	REG_PFUN( ev_tppSetCallServerInfo_Nty, OnCallServerNty );
	REG_PFUN( ev_tppSetUpgradeServerInfo_Ind, OnUpgradeSerInd );
	REG_PFUN( ev_tppSetUpgradeServerInfo_Nty, OnUpgradeSerNty );
	REG_PFUN( ev_tppStopAVMatrixProject_Rsp, OnStopAVMatrixRsp );
	REG_PFUN( ev_CnCfgVideoFormat_Ind, OnVideoFormatInd );
	REG_PFUN( ev_CnCfgDualVideoFormat_Ind, OnDualVideoFormatInd );
	REG_PFUN( ev_CnCfgCallRate_Ind, OnCallRateInd );	
	REG_PFUN( ev_CnCfgDualCallRate_Ind, OnDualCallRateInd );
	REG_PFUN( ev_CnVerInfo_Nty, OnVerInfoNty );
	REG_PFUN( ev_CnCfgConfDis_Ind, OnConfDisInd );
	REG_PFUN( ev_CnCfgConfPoll_Ind, OnConfPollInd );
	REG_PFUN( ev_CnCfgAudioFormat_Ind, OnAudioFormatInd );
	

	REG_PFUN( OSP_DISCONNECT, OnLinkBreak );
}

void CCncPortDiagCtrl::DispEvent(const CMessage &cMsg)
{
	DISP_FUN( CCncPortDiagCtrl, cMsg);
}

void CCncPortDiagCtrl::OnTimeOut(u16 wEvent)
{

}
		
void CCncPortDiagCtrl::OnLinkBreak(const CMessage& cMsg)
{
	memset( m_aAudioMixerInfo, 0, sizeof(m_aAudioMixerInfo) );	
	memset( m_atAudioPortInfo, 0, sizeof(m_atAudioPortInfo) );
	memset( &m_LostPacketInfo, 0, sizeof(m_LostPacketInfo) );
	memset( &m_tAudioDiagInfo, 0, sizeof(m_tAudioDiagInfo) );
	memset( &m_tVideoDiagInfo, 0, sizeof(m_tVideoDiagInfo) );
    memset( &m_tTPadList, 0, sizeof(m_tTPadList) );
	memset( &m_tUpDownSpeedInfo, 0, sizeof(m_tUpDownSpeedInfo) );
	memset( &m_atEqualizer, 0, sizeof(m_atEqualizer) );
	memset( &m_tCallSerInfo, 0, sizeof(m_tCallSerInfo) );
	memset( &m_tUpgradeSer, 0, sizeof(m_tUpgradeSer) );
	memset( &m_tDualVidForamt, 0, sizeof(m_tDualVidForamt) );
	memset( &m_tVidForamt, 0, sizeof(m_tVidForamt) );
	memset( &m_tPollInfo, 0, sizeof(m_tPollInfo) );
    PrtMsg( OSP_DISCONNECT, emEventTypecnstoolRecv,"[CCncPortDiagCtrl::OnLinkBreak]清空配置信息" );
}

//音频接口配置
u16 CCncPortDiagCtrl::SetAudioPortInfoCmd( const TTpAudioPortInfo** atAudioPortInfo )
{
	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();  
    pcTpMsg->SetUserData( m_pSession->GetInst() );

    pcTpMsg->SetEvent( ev_tppSetAudioPort_Cmd );
	pcTpMsg->SetBody( *atAudioPortInfo, sizeof(TTpAudioPortInfo) );
	pcTpMsg->CatBody( (*atAudioPortInfo)+1, sizeof(TTpAudioPortInfo) );
	pcTpMsg->CatBody( (*atAudioPortInfo)+2, sizeof(TTpAudioPortInfo) );

	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	
	PrtMsg( ev_tppSetAudioPort_Cmd, emEventTypecnstoolSend, "SetAudioPortInfoCmd" );
	
	return wRet;
}

TTpAudioPortInfo* CCncPortDiagCtrl::GetAudioPortInfo()
{
	return m_atAudioPortInfo;
}

void CCncPortDiagCtrl::OnAudioPortInfoInd(const CMessage& cMsg)
{
	CTpMsg cTpMsg(&cMsg);

	BOOL bSuccess = *(BOOL*)( cTpMsg.GetBody() + 3 * sizeof(TTpAudioPortInfo) );
	if ( bSuccess )
	{
		memset( &m_atAudioPortInfo, 0, sizeof(m_atAudioPortInfo) );
		for ( int i = 0; i < 3; i++ )
		{
			TTpAudioPortInfo tAudioPortInfo = *(TTpAudioPortInfo*)( cTpMsg.GetBody() + i * sizeof(TTpAudioPortInfo) );
			m_atAudioPortInfo[i] = tAudioPortInfo;
		}
	}
	PrtMsg( ev_tppSetAudioPort_Ind, emEventTypecnstoolRecv, "AudioPortInfoInd:%d", bSuccess );

	PostEvent( UI_CNSTOOL_MSG_AudPort_NTY, 0, (LPARAM)&bSuccess );
}

u16 CCncPortDiagCtrl::DefaultAudioPortCmd( const TTpAudioPortInfo** atAudioPortInfo )
{
	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();  
    pcTpMsg->SetUserData( m_pSession->GetInst() );
	
    pcTpMsg->SetEvent( ev_tppAudioRestoreDefaults_Cmd );
	pcTpMsg->SetBody( *atAudioPortInfo, sizeof(TTpAudioPortInfo) );
	pcTpMsg->CatBody( (*atAudioPortInfo)+1, sizeof(TTpAudioPortInfo) );
	pcTpMsg->CatBody( (*atAudioPortInfo)+2, sizeof(TTpAudioPortInfo) );

	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	
	PrtMsg( ev_tppAudioRestoreDefaults_Cmd, emEventTypecnstoolSend, "DefaultAudioPortCmd" );
	
	return wRet;
}

void CCncPortDiagCtrl::OnDefaultAudPortInd(const CMessage& cMsg)
{
	CTpMsg cTpMsg(&cMsg);

	BOOL bSuccess = *(BOOL*)cTpMsg.GetBody();

	PrtMsg( ev_tppAudioRestoreDefaults_Ind, emEventTypecnstoolRecv, "DefaultAudPortInd:%d", bSuccess );
	
	PostEvent( UI_CNSTOOL_MSG_DftAudPort_NTY, 0, (LPARAM)&bSuccess );
}

//丢包
u16 CCncPortDiagCtrl::LostPacketInfoReq()
{
	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();  
    pcTpMsg->SetUserData( m_pSession->GetInst() );
	
    pcTpMsg->SetEvent( ev_tppSetAudioPort_Cmd );
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_tppGetLostPacketInfo_Req, emEventTypecnstoolSend, "" );
	return wRet;
}

const u8& CCncPortDiagCtrl::GetLostPacketInfo()const
{
	return m_LostPacketInfo;
}

void CCncPortDiagCtrl::OnLostPacketInfoRsp(const CMessage& cMsg)
{
	CTpMsg cTpMsg(&cMsg);

	u8 LostPacketInfo = *(u8*)( cTpMsg.GetBody() );
	m_LostPacketInfo = LostPacketInfo;
	PrtMsg( ev_tppGetLostPacketInfo_Rsp, emEventTypecnstoolRecv, "LostPacket:%d", LostPacketInfo );
	PostEvent( UI_CNSTOOL_MSG_LostPacket_Rsp, 0, 0 );
}

//检测上下行网络速率
const TTPUpDownSpeedInfo& CCncPortDiagCtrl::GetUpDownstreamRate()const
{
	return m_tUpDownSpeedInfo;
}

void CCncPortDiagCtrl::OnUpDownstreamRateNty(const CMessage& cMsg)
{
	CTpMsg cTpMsg(&cMsg);

	m_tUpDownSpeedInfo = *(TTPUpDownSpeedInfo*)( cTpMsg.GetBody() );
	PrtMsg( ev_tppGetUpDownstreamRate_Nty, emEventTypecnstoolRecv, "Up:%d, Down:%d", m_tUpDownSpeedInfo.m_wUpSpeed, m_tUpDownSpeedInfo.m_wDownSpeed );
	PostEvent( UI_CNSTOOL_MSG_UpDownstream_NTY, 0, 0 );	
}

//Tpad列表
u16 CCncPortDiagCtrl::UpdateTpadListReq()
{
	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();  
    pcTpMsg->SetUserData( m_pSession->GetInst() );
	
    pcTpMsg->SetEvent( ev_tppGetTPadIpList_Req );
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_tppGetTPadIpList_Req, emEventTypecnstoolSend, "" );
	return wRet;
}

const TTPTPadList& CCncPortDiagCtrl::GetTpadList()const
{
	return m_tTPadList;
}

void CCncPortDiagCtrl::OnTpadListRsp(const CMessage& cMsg)
{
	CTpMsg cTpMsg(&cMsg);

	TTPTPadList tTPadList = *(TTPTPadList*)(cTpMsg.GetBody());
	PrtMsg( ev_tppGetTPadIpList_Rsp, emEventTypecnstoolRecv, "" );
	PostEvent( UI_CNSTOOL_MSG_TPadIP_RSP, (WPARAM)&tTPadList, 0 );
}

void CCncPortDiagCtrl::OnTpadListNty(const CMessage& cMsg)
{
	CTpMsg cTpMsg(&cMsg);

	TTPTPadList tTPadList = *(TTPTPadList*)(cTpMsg.GetBody());
	m_tTPadList = tTPadList;
	PrtMsg( ev_tppGetTPadIpList_Nty, emEventTypecnstoolRecv, "" );
	PostEvent( UI_CNSTOOL_MSG_TPadIP_NTY, 0, 0 );
}

//音视频方案选择
u16 CCncPortDiagCtrl::SelAVMatrixCmd( const TTPVgaMixInfo& tVgaMixInfo )
{
	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();  
    pcTpMsg->SetUserData( m_pSession->GetInst() );
	pcTpMsg->SetBody( &tVgaMixInfo, sizeof(TTPVgaMixInfo) );

    pcTpMsg->SetEvent( ev_tppSelAVMatrixProject_Cmd );

	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_tppSelAVMatrixProject_Cmd, emEventTypecnstoolSend, "" );
	return wRet;
}

const TTPVideoDiagInfo& CCncPortDiagCtrl::GetVideoDiagInfo()const
{
	return m_tVideoDiagInfo;
}
const TTPAudioDiagInfo& CCncPortDiagCtrl::GetAudioDiagInfo()const
{
	return m_tAudioDiagInfo;
}

void CCncPortDiagCtrl::OnAVMatrixInfoInd(const CMessage& cMsg)
{
	CTpMsg cTpMsg(&cMsg);

	memset( &m_tAudioDiagInfo, 0, sizeof(m_tAudioDiagInfo) );
	memset( &m_tVideoDiagInfo, 0, sizeof(m_tVideoDiagInfo) );

	TTPVideoDiagInfo tVideoDiagInfo = *(TTPVideoDiagInfo*)( cTpMsg.GetBody() );
	TTPAudioDiagInfo tAudioDiagInfo = *(TTPAudioDiagInfo*)( cTpMsg.GetBody() + sizeof(TTPVideoDiagInfo) );
	
	m_tAudioDiagInfo = tAudioDiagInfo;
	m_tVideoDiagInfo = tVideoDiagInfo;
	
	PostEvent( UI_CNSTOOL_MSG_AVDiag_IND, 0, 0  );
	PrtMsg( ev_tppSelAVMatrixProject_Ind, emEventTypecnstoolRecv, 
		"\n VideoInput1:%d, %d, %d\n VideoInput2:%d, %d, %d\n VideoInput3:%d, %d, %d\n VideoInCurrent:%d, %d, %d, %d\n VideoOutput1:%d, %d, %d\n VideoOutput2:%d, %d, %d\n VideoOutput3:%d, %d, %d\n VideoOutCurrent:%d, %d, %d, %d",
		tVideoDiagInfo.m_atPrimVideoInputPort[0].m_bIsHaveVideoSrcOutput, tVideoDiagInfo.m_atPrimVideoInputPort[0].m_emRes, tVideoDiagInfo.m_atPrimVideoInputPort[0].m_byFrameRate,
		tVideoDiagInfo.m_atPrimVideoInputPort[1].m_bIsHaveVideoSrcOutput, tVideoDiagInfo.m_atPrimVideoInputPort[1].m_emRes, tVideoDiagInfo.m_atPrimVideoInputPort[1].m_byFrameRate,
		tVideoDiagInfo.m_atPrimVideoInputPort[2].m_bIsHaveVideoSrcOutput, tVideoDiagInfo.m_atPrimVideoInputPort[2].m_emRes, tVideoDiagInfo.m_atPrimVideoInputPort[2].m_byFrameRate,
		tVideoDiagInfo.m_tDemoVideoInputPort.m_bIsHaveVideoSrcOutput, tVideoDiagInfo.m_byInputDemoIndex, tVideoDiagInfo.m_tDemoVideoInputPort.m_emRes, tVideoDiagInfo.m_tDemoVideoInputPort.m_byFrameRate,
		tVideoDiagInfo.m_atPrimVideoOutputPort[0].m_bIsHaveVideoSrcOutput, tVideoDiagInfo.m_atPrimVideoOutputPort[0].m_emRes, tVideoDiagInfo.m_atPrimVideoOutputPort[0].m_byFrameRate,
		tVideoDiagInfo.m_atPrimVideoOutputPort[1].m_bIsHaveVideoSrcOutput, tVideoDiagInfo.m_atPrimVideoOutputPort[1].m_emRes, tVideoDiagInfo.m_atPrimVideoOutputPort[1].m_byFrameRate,
		tVideoDiagInfo.m_atPrimVideoOutputPort[2].m_bIsHaveVideoSrcOutput, tVideoDiagInfo.m_atPrimVideoOutputPort[2].m_emRes, tVideoDiagInfo.m_atPrimVideoOutputPort[2].m_byFrameRate,
		tVideoDiagInfo.m_tDemoVideoOutputPort.m_bIsHaveVideoSrcOutput, tVideoDiagInfo.m_byOutputDemoIndex, tVideoDiagInfo.m_tDemoVideoOutputPort.m_emRes, tVideoDiagInfo.m_tDemoVideoOutputPort.m_byFrameRate );
	PrtMsg( ev_tppSelAVMatrixProject_Ind, emEventTypecnstoolRecv,
		"\n AudioInput1:%d , %d\n AudioInput2:%d , %d\n AudioInput3:%d , %d\n AudioInput110:%d , %d\n AudioInput4:%d , %d\n AudioInput5:%d , %d\n AudioInput6:%d , %d\n AudioInput210:%d , %d\n AudioInput7:%d , %d\n AudioInput8:%d , %d\n AudioInput9:%d , %d\n AudioInput310:%d , %d\n AudioOutput1:%d , %d\n AudioOutput2:%d , %d\n AudioOutput3:%d , %d",
		tAudioDiagInfo.m_atPrimAudioInputPort[0].m_abAudioPort[0], tAudioDiagInfo.m_atPrimAudioInputPort[0].m_abyVolume[0],
		tAudioDiagInfo.m_atPrimAudioInputPort[0].m_abAudioPort[1], tAudioDiagInfo.m_atPrimAudioInputPort[0].m_abyVolume[1],
		tAudioDiagInfo.m_atPrimAudioInputPort[0].m_abAudioPort[2], tAudioDiagInfo.m_atPrimAudioInputPort[0].m_abyVolume[2],
		tAudioDiagInfo.m_atPrimAudioInputPort[0].m_abAudioPort[3], tAudioDiagInfo.m_atPrimAudioInputPort[0].m_abyVolume[3],
		tAudioDiagInfo.m_atPrimAudioInputPort[1].m_abAudioPort[0], tAudioDiagInfo.m_atPrimAudioInputPort[1].m_abyVolume[0],
		tAudioDiagInfo.m_atPrimAudioInputPort[1].m_abAudioPort[1], tAudioDiagInfo.m_atPrimAudioInputPort[1].m_abyVolume[1],
		tAudioDiagInfo.m_atPrimAudioInputPort[1].m_abAudioPort[2], tAudioDiagInfo.m_atPrimAudioInputPort[1].m_abyVolume[2],
		tAudioDiagInfo.m_atPrimAudioInputPort[1].m_abAudioPort[3], tAudioDiagInfo.m_atPrimAudioInputPort[1].m_abyVolume[3],
		tAudioDiagInfo.m_atPrimAudioInputPort[2].m_abAudioPort[0], tAudioDiagInfo.m_atPrimAudioInputPort[2].m_abyVolume[0],
		tAudioDiagInfo.m_atPrimAudioInputPort[2].m_abAudioPort[1], tAudioDiagInfo.m_atPrimAudioInputPort[2].m_abyVolume[1],
		tAudioDiagInfo.m_atPrimAudioInputPort[2].m_abAudioPort[2], tAudioDiagInfo.m_atPrimAudioInputPort[2].m_abyVolume[2],
		tAudioDiagInfo.m_atPrimAudioInputPort[2].m_abAudioPort[3], tAudioDiagInfo.m_atPrimAudioInputPort[2].m_abyVolume[3],		
		tAudioDiagInfo.m_atPrimAudioOutputPort[0].m_abAudioPort[0], tAudioDiagInfo.m_atPrimAudioOutputPort[0].m_abyVolume[0],
		tAudioDiagInfo.m_atPrimAudioOutputPort[1].m_abAudioPort[0], tAudioDiagInfo.m_atPrimAudioOutputPort[1].m_abyVolume[0],
		tAudioDiagInfo.m_atPrimAudioOutputPort[2].m_abAudioPort[0], tAudioDiagInfo.m_atPrimAudioOutputPort[2].m_abyVolume[0]);
}

//停止诊断测试命令			
u16 CCncPortDiagCtrl::StopAVMatrixReq()
{
	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();  
    pcTpMsg->SetUserData( m_pSession->GetInst() );	
    pcTpMsg->SetEvent( ev_tppStopAVMatrixProject_Req );	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);

	PrtMsg( ev_tppStopAVMatrixProject_Req, emEventTypecnstoolSend, "StopAVMatrixProjectReq" );
	
	return wRet;
}

void CCncPortDiagCtrl::OnStopAVMatrixRsp( const CMessage& cMsg )
{
	CTpMsg cTpMsg(&cMsg);

	PostEvent( UI_CNSTOOL_MSG_StopAVMatrix_RSP, 0, 0 );

	PrtMsg( ev_tppStopAVMatrixProject_Rsp, emEventTypecnstoolRecv, "StopAVMatrixProjectRsp" );
}

//重启Cns
u16 CCncPortDiagCtrl::RebootCns()
{
	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();  
    pcTpMsg->SetUserData( m_pSession->GetInst() );
	
    pcTpMsg->SetEvent( ev_tppReboot_Nty );
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_tppReboot_Nty, emEventTypecnstoolSend, "RebootCns" );
	return wRet;
}

//升级T300
u16 CCncPortDiagCtrl::UpgradeCns( const TTPFTPFileInfo& tVerFileInfo )
{
	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();  
    pcTpMsg->SetUserData( m_pSession->GetInst() );	
    pcTpMsg->SetEvent( ev_tppUpdate_Cmd );
	pcTpMsg->SetBody( &tVerFileInfo, sizeof(TTPFTPFileInfo) );	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_tppUpdate_Cmd, emEventTypecnstoolSend, "UpgradeCns" );
	return wRet;
}

void CCncPortDiagCtrl::OnUpgradeCnsInd( const CMessage& cMsg )
{
	CTpMsg cTpMsg(&cMsg);

	BOOL* bSuccess = (BOOL*)(cTpMsg.GetBody());
	if ( NULL != bSuccess )
	{
		PostEvent( UI_CNSTOOL_MSG_UpgradeCns_NTY, (WPARAM)bSuccess, 0 );
	}
	
	PrtMsg( ev_tppUpdate_Ind, emEventTypecnstoolRecv, "bSuccess:%d", *bSuccess );
}

//维护工具刷新界面请求
u16 CCncPortDiagCtrl::ReqRefresh()
{
	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();  
    pcTpMsg->SetUserData( m_pSession->GetInst() );
	
    pcTpMsg->SetEvent( ev_tppRefresh_Req );
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_tppRefresh_Req, emEventTypecnstoolSend, "RefreshCnsTool" );
	return wRet;
}

//混音配置
u16 CCncPortDiagCtrl::AudiotMixerCmd( const u8** aAudioMixerInfo )
{
	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();  
    pcTpMsg->SetUserData( m_pSession->GetInst() );	
    pcTpMsg->SetEvent( ev_tppSetAudiotMixer_Cmd );
	pcTpMsg->SetBody( *aAudioMixerInfo, sizeof(u8) );
	pcTpMsg->CatBody( (*aAudioMixerInfo)+1, sizeof(u8) );
	pcTpMsg->CatBody( (*aAudioMixerInfo)+2, sizeof(u8) );
	pcTpMsg->CatBody( (*aAudioMixerInfo)+3, sizeof(u8) );
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	
	PrtMsg( ev_tppSetAudiotMixer_Cmd, emEventTypecnstoolSend, "AudiotMixerCmd" );
	
	return wRet;
}

u8* CCncPortDiagCtrl::GetAudioMixerInfo()
{
	return m_aAudioMixerInfo;
}

void CCncPortDiagCtrl::OnAudiotMixerInd( const CMessage& cMsg )
{
	CTpMsg cTpMsg(&cMsg);

	BOOL bSuccess = *(BOOL*)( cTpMsg.GetBody() + 4 * sizeof(u8) );
	if ( bSuccess )
	{
		memset( &m_aAudioMixerInfo, 0, sizeof(m_aAudioMixerInfo) );
		for ( int i = 0; i < 4; i++ )
		{
			u8* pMixerInfo = (u8*)( cTpMsg.GetBody() + i * sizeof(u8) );
			if ( NULL != pMixerInfo )
			{
				m_aAudioMixerInfo[i] = *pMixerInfo;
			}     
		}
	}
	
	PrtMsg( ev_tppSetAudiotMixer_Ind, emEventTypecnstoolRecv, "AudiotMixerInd:%d", bSuccess );
	
	PostEvent( UI_CNSTOOL_MSG_AudMixer_NTY, 0, (LPARAM)&bSuccess );
}

u16 CCncPortDiagCtrl::DefaultMixerCmd( const u8** aAudioMixerInfo )
{
	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();  
    pcTpMsg->SetUserData( m_pSession->GetInst() );	
	pcTpMsg->SetEvent( ev_tppMixRestoreDefaults_Cmd );
	pcTpMsg->SetBody( *aAudioMixerInfo, sizeof(u8) );
	pcTpMsg->CatBody( (*aAudioMixerInfo)+1, sizeof(u8) );
	pcTpMsg->CatBody( (*aAudioMixerInfo)+2, sizeof(u8) );
	pcTpMsg->CatBody( (*aAudioMixerInfo)+3, sizeof(u8) );

	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	
	PrtMsg( ev_tppMixRestoreDefaults_Cmd, emEventTypecnstoolSend, "DefaultMixerCmd" );
	
	return wRet;
}

void CCncPortDiagCtrl::OnDefaulttMixerInd( const CMessage& cMsg )
{
	CTpMsg cTpMsg(&cMsg);

	BOOL bSuccess = *(BOOL*)cTpMsg.GetBody();

	PrtMsg( ev_tppMixRestoreDefaults_Ind, emEventTypecnstoolRecv, "DefaultMixerInd:%d", bSuccess );
	
	PostEvent( UI_CNSTOOL_MSG_DftMixer_NTY, 0, (LPARAM)&bSuccess );
}

//均衡器设置
u16 CCncPortDiagCtrl::AudioEqualizerCmd( const TTPEqualizer** atEqualizer )
{
	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();  
    pcTpMsg->SetUserData( m_pSession->GetInst() );
	pcTpMsg->SetBody( *atEqualizer, sizeof(TTPEqualizer) );
	pcTpMsg->CatBody( (*atEqualizer)+1, sizeof(TTPEqualizer) );
	pcTpMsg->CatBody( (*atEqualizer)+2, sizeof(TTPEqualizer) );
	
    pcTpMsg->SetEvent( ev_tppSetAudioEqualizer_Cmd );
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_tppSetAudioEqualizer_Cmd, emEventTypecnstoolSend, "AudioEqualizerCmd" );
	return wRet;
}

TTPEqualizer* CCncPortDiagCtrl::GetAudioEqualizer()
{
	return m_atEqualizer;
}

void CCncPortDiagCtrl::OnAudioEqualizerInd( const CMessage& cMsg )
{
	CTpMsg cTpMsg(&cMsg);

	BOOL bSuccess = *(BOOL*)( cTpMsg.GetBody() + 3 * sizeof(TTPEqualizer) );
	if ( bSuccess )
	{
		memset( &m_atEqualizer, 0, sizeof(m_atEqualizer) );	
		for ( int i = 0; i < 3; i++ )
		{
			TTPEqualizer* ptEqualizer = (TTPEqualizer*)( cTpMsg.GetBody() + i * sizeof(TTPEqualizer) );
			
			if ( NULL != ptEqualizer )
			{
				m_atEqualizer[i] = *ptEqualizer;
			}
		}
	}

	PostEvent( UI_CNSTOOL_MSG_AudEqualizer_NTY, 0, (LPARAM)&bSuccess  );
	PrtMsg( ev_tppSetAudioEqualizer_Ind, emEventTypecnstoolRecv, "AudioEqInd:%d", bSuccess );
}

u16 CCncPortDiagCtrl::DefaultEqCmd( const TTPEqualizer** atEqualizer )
{
	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();  
    pcTpMsg->SetUserData( m_pSession->GetInst() );
	pcTpMsg->SetBody( *atEqualizer, sizeof(TTPEqualizer) );
	pcTpMsg->CatBody( (*atEqualizer)+1, sizeof(TTPEqualizer) );
	pcTpMsg->CatBody( (*atEqualizer)+2, sizeof(TTPEqualizer) );
	
    pcTpMsg->SetEvent( ev_tppEqualizerReDefaults_Cmd );
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_tppEqualizerReDefaults_Cmd, emEventTypecnstoolSend, "DefaultEqCmd" );
	return wRet;
}

void CCncPortDiagCtrl::OnDefaultEqInd( const CMessage& cMsg )
{
	CTpMsg cTpMsg(&cMsg);

	BOOL bSuccess = *(BOOL*)cTpMsg.GetBody();

	PostEvent( UI_CNSTOOL_MSG_DftEq_NTY, 0, (LPARAM)&bSuccess  );
	PrtMsg( ev_tppEqualizerReDefaults_Ind, emEventTypecnstoolRecv, "DefaultEqInd:%d", bSuccess );
}

//呼叫服务器
u16 CCncPortDiagCtrl::CallServerCmd( const TTPCallSerInfo& tCallSerInfo )
{
	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();  
    pcTpMsg->SetUserData( m_pSession->GetInst() );
	pcTpMsg->SetBody( &tCallSerInfo, sizeof(TTPCallSerInfo) );
	
    pcTpMsg->SetEvent( ev_tppSetCallServerInfo_Cmd );
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);

	in_addr tAddr;
	tAddr.S_un.S_addr = tCallSerInfo.dwCallServiceIP;
	PrtMsg( ev_tppSetCallServerInfo_Cmd, emEventTypecnstoolSend, _T( "CallSerIP:%s" ), inet_ntoa(tAddr) );
	return wRet;
}

const TTPCallSerInfo& CCncPortDiagCtrl::GetCallServerInfo() const
{
	return m_tCallSerInfo;
}

void CCncPortDiagCtrl::OnCallServerNty( const CMessage& cMsg )
{
	CTpMsg cTpMsg(&cMsg);

	memset( &m_tCallSerInfo, 0, sizeof(m_tCallSerInfo) );

	m_tCallSerInfo = *(TTPCallSerInfo*)( cTpMsg.GetBody() );

	PostEvent( UI_CNSTOOL_MSG_CallSer_NTY, 0, 0  );
	in_addr tAddr;
	tAddr.S_un.S_addr = m_tCallSerInfo.dwCallServiceIP;
	PrtMsg( ev_tppSetCallServerInfo_Nty, emEventTypecnstoolRecv, _T("CallSerIP:%s"), inet_ntoa(tAddr) );
}

void CCncPortDiagCtrl::OnCallServerInd( const CMessage& cMsg )
{
	CTpMsg cTpMsg(&cMsg);

    memset( &m_tCallSerInfo, 0, sizeof(m_tCallSerInfo) );
	
	TTPCallSerInfo tCallSerInfo = *(TTPCallSerInfo*)( cTpMsg.GetBody() );
	BOOL bSuccess = *(BOOL*)( cTpMsg.GetBody() + sizeof(TTPCallSerInfo) );
	if ( TRUE == bSuccess )
	{
		m_tCallSerInfo = tCallSerInfo;
	}
	PostEvent( UI_CNSTOOL_MSG_CallSer_IND, (WPARAM)&tCallSerInfo, (LPARAM)&bSuccess );
	
	in_addr tAddr;
	tAddr.S_un.S_addr = tCallSerInfo.dwCallServiceIP;
	PrtMsg( ev_tppSetCallServerInfo_Ind, emEventTypecnstoolRecv,_T("CallSerIP: %s, BOOL:%d"), inet_ntoa(tAddr), bSuccess );

}

//升级服务器			
u16 CCncPortDiagCtrl::UpgradeSerCmd( const TTPUpgradeSer& tUpgradeSer )
{
	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();  
    pcTpMsg->SetUserData( m_pSession->GetInst() );
	pcTpMsg->SetBody( &tUpgradeSer, sizeof(TTPUpgradeSer) );
	
    pcTpMsg->SetEvent( ev_tppSetUpgradeServerInfo_Cmd );
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);

	in_addr tAddr;
	tAddr.S_un.S_addr = tUpgradeSer.dwSerIP;
	PrtMsg( ev_tppSetUpgradeServerInfo_Cmd, emEventTypecnstoolSend, "UpgradeSerIP: %s", inet_ntoa(tAddr) );

	return wRet;
}

const TTPUpgradeSer& CCncPortDiagCtrl::GetUpgradeSerInfo() const
{
	return m_tUpgradeSer;
}

void CCncPortDiagCtrl::OnUpgradeSerNty( const CMessage& cMsg )
{
	CTpMsg cTpMsg(&cMsg);

	m_tUpgradeSer = *(TTPUpgradeSer*)( cTpMsg.GetBody() );

	PostEvent( UI_CNSTOOL_MSG_UpgradeSer_NTY, 0, 0  );
	in_addr tAddr;
	tAddr.S_un.S_addr = m_tUpgradeSer.dwSerIP;
	PrtMsg( ev_tppSetUpgradeServerInfo_Nty, emEventTypecnstoolRecv, "UpgradeSerIP: %s", inet_ntoa(tAddr) );
}

void CCncPortDiagCtrl::OnUpgradeSerInd( const CMessage& cMsg )
{
	CTpMsg cTpMsg(&cMsg);

	TTPUpgradeSer tUpgradeSer = *(TTPUpgradeSer*)( cTpMsg.GetBody() );
	BOOL bSuccess = *(BOOL*)( cTpMsg.GetBody() + sizeof(TTPUpgradeSer) );
	if ( TRUE == bSuccess )
	{
		m_tUpgradeSer = tUpgradeSer;
	}
	PostEvent( UI_CNSTOOL_MSG_UpgradeSer_IND, 0, (LPARAM)bSuccess );

	in_addr tAddr;
	tAddr.S_un.S_addr = tUpgradeSer.dwSerIP;
	PrtMsg( ev_tppSetUpgradeServerInfo_Ind, emEventTypecnstoolRecv, "UpgradeSerIP: %s, BOOL:%d", inet_ntoa(tAddr), bSuccess );
}

u16 CCncPortDiagCtrl::ConfSignCmd( const BOOL& bOk, u8 byIndex )
{
	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();  
    pcTpMsg->SetUserData( m_pSession->GetInst() );
	pcTpMsg->SetBody( &bOk, sizeof(BOOL) );
	pcTpMsg->CatBody( &byIndex, sizeof(u8) );
    pcTpMsg->SetEvent( ev_tppSetBannerLogo_Cmd );
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_tppSetBannerLogo_Cmd, emEventTypecnstoolSend, "SetBannerLogoCmd:%d, From:%d ", bOk, byIndex );
	return wRet;
}

//会议优选格式
u16 CCncPortDiagCtrl::VideoFormatCmd( const TTPVidForamt& tVidForamt )
{
	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();  
    pcTpMsg->SetUserData( m_pSession->GetInst() );
	pcTpMsg->SetBody( &tVidForamt, sizeof(TTPVidForamt) );
    pcTpMsg->SetEvent( ev_CnCfgVideoFormat_Cmd );
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_CnCfgVideoFormat_Cmd, emEventTypecnstoolSend, _T( "u16:%d, EmTpVideoResolution:%d, EmTpVideoQualityLevel:%d" )
		, tVidForamt.wVidFrameRate, tVidForamt.emTpVideoResolution, tVidForamt.emTpVideoQualityLevel );
	return wRet;
}

void CCncPortDiagCtrl::OnVideoFormatInd( const CMessage& cMsg )
{
	CTpMsg cTpMsg(&cMsg);
	
	TTPVidForamt tVidForamt = *(TTPVidForamt*)( cTpMsg.GetBody() );
	m_tVidForamt = tVidForamt;

	PostEvent( UI_CNSTOOL_VIDEOFORMAT_IND, 0, 0 );

	PrtMsg( ev_CnCfgVideoFormat_Ind, emEventTypecnstoolRecv, _T( "u16:%d, EmTpVideoResolution:%d, EmTpVideoQualityLevel:%d" )
		, tVidForamt.wVidFrameRate, tVidForamt.emTpVideoResolution, tVidForamt.emTpVideoQualityLevel );
}

const TTPVidForamt& CCncPortDiagCtrl::GetVideoFormatInfo() const
{
	return m_tVidForamt;
}

//演示优选格式
u16 CCncPortDiagCtrl::DualVideoFormatCmd( const TTPVidForamt& tVidForamt )
{
	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();  
    pcTpMsg->SetUserData( m_pSession->GetInst() );
	pcTpMsg->SetBody( &tVidForamt, sizeof(TTPVidForamt) );
    pcTpMsg->SetEvent( ev_CnCfgDualVideoFormat_Cmd );
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_CnCfgDualVideoFormat_Cmd, emEventTypecnstoolSend, _T( "u16:%d, EmTpVideoResolution:%d, EmTpVideoQualityLevel:%d" )
		, tVidForamt.wVidFrameRate, tVidForamt.emTpVideoResolution, tVidForamt.emTpVideoQualityLevel );
	return wRet;
}

void CCncPortDiagCtrl::OnDualVideoFormatInd( const CMessage& cMsg )
{
	CTpMsg cTpMsg(&cMsg);
	
	TTPVidForamt tVidForamt = *(TTPVidForamt*)( cTpMsg.GetBody() );
	m_tDualVidForamt = tVidForamt;
	
	PostEvent( UI_CNSTOOL_DUALVIDEOFORMAT_IND, 0, 0 );
	
	PrtMsg( ev_CnCfgDualVideoFormat_Ind, emEventTypecnstoolRecv, _T( "u16:%d, EmTpVideoResolution:%d, EmTpVideoQualityLevel:%d" )
		, tVidForamt.wVidFrameRate, tVidForamt.emTpVideoResolution, tVidForamt.emTpVideoQualityLevel );
}

const TTPVidForamt& CCncPortDiagCtrl::GetDualVideoFormatInfo() const
{
	return m_tDualVidForamt;
}

//单屏码率
u16 CCncPortDiagCtrl::CallRateCmd( const u16 wCallRate )
{
	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();  
    pcTpMsg->SetUserData( m_pSession->GetInst() );
	pcTpMsg->SetBody( &wCallRate, sizeof(u16) );
    pcTpMsg->SetEvent( ev_CnCfgCallRate_Cmd );
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_CnCfgCallRate_Cmd, emEventTypecnstoolSend, _T( "wCallRate(send):%d" ), wCallRate );
	return wRet;
}

void CCncPortDiagCtrl::OnCallRateInd( const CMessage& cMsg )
{
	CTpMsg cTpMsg(&cMsg);
	
	u16 wCallRate = *(u16*)( cTpMsg.GetBody() );
	m_wCallRate = wCallRate;
	
	PostEvent( UI_CNSTOOL_CALLRATE_IND, 0, 0 );
	PrtMsg( ev_CnCfgCallRate_Ind, emEventTypecnstoolRecv, _T( "wCallRate(recv):%d" ), wCallRate );
}

const u16 CCncPortDiagCtrl::GetCallRate() const
{
	return m_wCallRate;
}

//演示码率
u16 CCncPortDiagCtrl::DualCallRateCmd( const u16 wDualCallRate )
{
	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();  
    pcTpMsg->SetUserData( m_pSession->GetInst() );
	pcTpMsg->SetBody( &wDualCallRate, sizeof(u16) );
    pcTpMsg->SetEvent( ev_CnCfgDualCallRate_Cmd );
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_CnCfgDualCallRate_Cmd, emEventTypecnstoolSend, _T( "wDualCallRate(send):%d" ), wDualCallRate );
	return wRet;
}

void CCncPortDiagCtrl::OnDualCallRateInd( const CMessage& cMsg )
{
	CTpMsg cTpMsg(&cMsg);
	
	u16 wDualCallRate = *(u16*)( cTpMsg.GetBody() );
	m_wDualCallRate = wDualCallRate;
	
	PostEvent( UI_CNSTOOL_DUALCALLRATE_IND, 0, 0 );
	PrtMsg( ev_CnCfgDualCallRate_Ind, emEventTypecnstoolRecv, _T( "wDualCallRate(recv):%d" ), wDualCallRate );
}

const u16 CCncPortDiagCtrl::GetDualCallRate() const
{
	return m_wDualCallRate;
}

//版本信息通知
void CCncPortDiagCtrl::OnVerInfoNty( const CMessage& cMsg )
{
	CTpMsg cTpMsg(&cMsg);
	
	s8* achVerInfo = (s8*)( cTpMsg.GetBody() );

	PostEvent( UI_CNSTOOL_VERINFO_NTY, (WPARAM)achVerInfo, 0 );
	PrtMsg( ev_CnVerInfo_Nty, emEventTypecnstoolRecv, _T( "achVerInfo: %s" ), achVerInfo );
}

//会议轮询
u16 CCncPortDiagCtrl::ConfPollCmd( const TTPPollInfo& tPollInfo )
{
	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();  
    pcTpMsg->SetUserData( m_pSession->GetInst() );
	pcTpMsg->SetBody( &tPollInfo, sizeof(TTPPollInfo) );
    pcTpMsg->SetEvent( ev_CnCfgConfPoll_Cmd );
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_CnCfgConfPoll_Cmd, emEventTypecnstoolSend, _T( "bIsPoll:%d, wPollExpire:%d" ), tPollInfo.bIsPoll, tPollInfo.wPollExpire );
	return wRet;
}

void CCncPortDiagCtrl::OnConfPollInd( const CMessage& cMsg )
{
	CTpMsg cTpMsg(&cMsg);
	
	TTPPollInfo tPollInfo = *(TTPPollInfo*)( cTpMsg.GetBody() );
	m_tPollInfo = tPollInfo;
	
	PostEvent( UI_CNSTOOL_CONFPOOL_IND, 0, 0 );
	PrtMsg( ev_CnCfgConfPoll_Ind, emEventTypecnstoolRecv, _T( "bIsPoll:%d, wPollExpire:%d" ), tPollInfo.bIsPoll, tPollInfo.wPollExpire );
}

const TTPPollInfo& CCncPortDiagCtrl::GetConfPollInfo() const
{
	return m_tPollInfo;
}

//会议讨论
u16 CCncPortDiagCtrl::ConfDisCmd( const BOOL& bDis )
{
	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();  
    pcTpMsg->SetUserData( m_pSession->GetInst() );
	pcTpMsg->SetBody( &bDis, sizeof(BOOL) );
    pcTpMsg->SetEvent( ev_CnCfgConfDis_Cmd );
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_CnCfgConfDis_Cmd, emEventTypecnstoolSend, _T( "bDis:%d" ), bDis );
	return wRet;
}

void CCncPortDiagCtrl::OnConfDisInd( const CMessage& cMsg )
{
	CTpMsg cTpMsg(&cMsg);
	
	BOOL bDis = *(BOOL*)( cTpMsg.GetBody() );
	m_bDis = bDis;
	
	PostEvent( UI_CNSTOOL_CONFDIS_IND, 0, 0 );
	PrtMsg( ev_CnCfgConfDis_Ind, emEventTypecnstoolRecv, _T( "bDis:%d" ), bDis );
}

const BOOL& CCncPortDiagCtrl::GetConfDisInfo() const
{
	return m_bDis;
}

//音频格式
u16 CCncPortDiagCtrl::AudioFormatCmd( const EmTpAudioFormat& emAudioFormat )
{
	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();  
    pcTpMsg->SetUserData( m_pSession->GetInst() );
	pcTpMsg->SetBody( &emAudioFormat, sizeof(EmTpAudioFormat) );
    pcTpMsg->SetEvent( ev_CnCfgAudioFormat_Cmd );
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_CnCfgAudioFormat_Cmd, emEventTypecnstoolSend, _T( "AudioFormat:%d( emTPAMpegAACLD:%d, emTPAG711a:%d, emTPAG711u:%d, \
emTPAG719:%d, emTPAG7221:%d, emTPAMP3:%d, emTPAMpegAACLC:%d )" ), emAudioFormat, emTPAMpegAACLD, emTPAG711a, emTPAG711u, emTPAG719, \
emTPAG7221, emTPAMP3, emTPAMpegAACLC );
	return wRet;
}

void CCncPortDiagCtrl::OnAudioFormatInd( const CMessage& cMsg )
{
	CTpMsg cTpMsg(&cMsg);
	
	EmTpAudioFormat emAudioFormat = *(EmTpAudioFormat*)( cTpMsg.GetBody() );
	m_emAudioFormat = emAudioFormat;
	
	PostEvent( UI_CNSTOOL_AUDIOFORMAT_IND, 0, 0 );
	PrtMsg( ev_CnCfgAudioFormat_Ind, emEventTypecnstoolRecv, _T( "AudioFormat:%d( emTPAMpegAACLD:%d, emTPAG711a:%d, emTPAG711u:%d, \
emTPAG719:%d, emTPAG7221:%d, emTPAMP3:%d, emTPAMpegAACLC:%d )" ), emAudioFormat, emTPAMpegAACLD, emTPAG711a, emTPAG711u, emTPAG719, \
emTPAG7221, emTPAMP3, emTPAMpegAACLC );
}

const EmTpAudioFormat& CCncPortDiagCtrl::GetAudioFormatInfo() const
{
	return m_emAudioFormat;
}