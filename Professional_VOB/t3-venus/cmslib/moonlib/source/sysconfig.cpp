// sysconfig.cpp: implementation of the CSysConfig class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "sysconfig.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSysConfig::CSysConfig( CMoonSession &cSession) : CSysConfigIF()                                                 
{
	m_pSession = &cSession;

	BuildEventsMap();
} 

CSysConfig::~CSysConfig()
{
	
}


void CSysConfig::BuildEventsMap()
{  
	//断链清空资源
	REG_PFUN(OSP_DISCONNECT, OnLinkBreak); 
	REG_PFUN(ev_TpMoonVerInfo_Nty, OnSoftWareVerInfoNty);
	REG_PFUN(ev_TpCamOutPortInfo_Nty, OnCamOutputInfoNty);
	REG_PFUN(ev_TpCamImageAdjust_Nty, OnCamImageAdjustNty);
	REG_PFUN(ev_TpCamImageAdjust_Ind, OnCamImageAdjustInd);	
	REG_PFUN(ev_TpCamOutPortInfo_Ind, OnCamOutputInfoInd);
	REG_PFUN(ev_TpMoonCfgEthnet_Ind, OnEthnetInfoInd);
	REG_PFUN(ev_TpSetLVDSBaud_Ind, OnLVDBaudInd);
	REG_PFUN( ev_TpSetLVDSBaud_Nty, OnLVDBaudNty);
}

void CSysConfig::OnLinkBreak(const CMessage& cMsg)
{

}

void CSysConfig::DispEvent(const CMessage &cMsg)
{
	DISP_FUN( CSysConfig, cMsg) ;
}

void CSysConfig::OnTimeOut(u16 wEvent)
{
    // 发送超时事件通知
   PostEvent(UI_UMS_CMD_TIMEOUT, wEvent);
} 

void CSysConfig::OnSoftWareVerInfoNty( const CMessage& cMsg )
{
	CTpMsg cTpMsg(&cMsg);
	s8 *achSoftWareVer = (s8*)( cTpMsg.GetBody() );

	EmTpVer emMoonVer = *(EmTpVer*)( cTpMsg.GetBody()+sizeof(s8)*MOON_MAX_DEVICEVER_LEN);
	PrtMsg( ev_TpMoonVerInfo_Nty, emEventTypemoontoolRecv, "SoftWareVer:%s", achSoftWareVer );

	PostEvent( UI_MOONTOOL_VERINFO_NTY, (WPARAM)achSoftWareVer, (LPARAM)&emMoonVer );
}

void CSysConfig::OnCamOutputInfoNty( const CMessage& cMsg )
{
	CTpMsg cTpMsg(&cMsg);
	EmTPDVIOutPortType emOutputType = *(EmTPDVIOutPortType*)( cTpMsg.GetBody() );
	EmTPMOONOutMode emMoonOutMode = *(EmTPMOONOutMode*)( cTpMsg.GetBody()+sizeof(EmTPDVIOutPortType) );

	PrtMsg( ev_TpCamOutPortInfo_Nty, emEventTypemoontoolRecv, "EmTPDVIOutPortType:%d, EmTPMOONOutMode:%d", emOutputType, emMoonOutMode );

	PostEvent( UI_MOONTOOL_CAMOUTPUT_INFO_NTY, (WPARAM)emOutputType, (LPARAM)emMoonOutMode );

}

void CSysConfig::OnCamImageAdjustNty( const CMessage& cMsg )
{
	CTpMsg cTpMsg(&cMsg);
	EmTPImageAdjust emImageAdjust = *(EmTPImageAdjust*)( cTpMsg.GetBody() );

	PrtMsg( ev_TpCamImageAdjust_Nty, emEventTypemoontoolRecv, "EmTPImageAdjust:%d", emImageAdjust );

	PostEvent( UI_MOONTOOL_IMAGE_ADJUST_NTY, (WPARAM)emImageAdjust, NULL );
}

void CSysConfig::OnEthnetInfoInd( const CMessage& cMsg )
{
	CTpMsg cTpMsg(&cMsg);	
	
    u8 uInst = cTpMsg.GetHomeplace();
	
    TTPEthnetInfo tEthnetInfo = *reinterpret_cast<TTPEthnetInfo*>(cTpMsg.GetBody());

	m_tEthnetInfo = tEthnetInfo;
	PostEvent( UI_MOONTOOL_ETHNETINFO_NOTIFY );
	
	in_addr tAddr;
	tAddr.S_un.S_addr = tEthnetInfo.dwIP;
	PrtMsg( ev_TpMoonCfgEthnet_Ind, emEventTypemoontoolRecv, "TTPEthnetInfo: Ip: %s, Inst: %d", inet_ntoa(tAddr), uInst );

}

const TTPEthnetInfo& CSysConfig::GetEthnetCfg() const
{
	return m_tEthnetInfo;
}
 
u16 CSysConfig::SetOutPortTypeCmd( EmTPDVIOutPortType emDVIOutPortType, EmTPMOONOutMode emMOONOutMode )
{
	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData(m_pSession->GetInst());
	pcTpMsg->SetBody(&emDVIOutPortType, sizeof(EmTPDVIOutPortType));
	pcTpMsg->CatBody(&emMOONOutMode, sizeof(EmTPMOONOutMode));
	pcTpMsg->SetEvent(ev_TpCamOutPortInfo_Cmd);
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_TpCamOutPortInfo_Cmd, emEventTypemoontoolSend, "EmTPDVIOutPortType:%d,EmTPMOONOutMode:%d", emDVIOutPortType, emMOONOutMode );
	return wRet;
}

void CSysConfig::OnCamOutputInfoInd( const CMessage& cMsg )
{
	CTpMsg cTpMsg(&cMsg);	
	
    u8 uInst = cTpMsg.GetHomeplace();
	
    EmTPDVIOutPortType emDVIOutPortType = *reinterpret_cast<EmTPDVIOutPortType*>(cTpMsg.GetBody());

	EmTPMOONOutMode	emMOONOutMode = *reinterpret_cast<EmTPMOONOutMode*>(cTpMsg.GetBody()+sizeof(EmTPDVIOutPortType));

	BOOL bOk = *(BOOL*)(cTpMsg.GetBody()+sizeof(EmTPDVIOutPortType)+sizeof(EmTPMOONOutMode));

	PrtMsg( ev_TpCamOutPortInfo_Ind, emEventTypemoontoolRecv, "EmTPDVIOutPortType:%d, EmTPMOONOutMode:%d, bOk:%d", emDVIOutPortType, emMOONOutMode, bOk );

	PostEvent( UI_MOONTOOL_CAMOUTPUT_INFO_IND, (WPARAM)emDVIOutPortType, (LPARAM)emMOONOutMode );

}

u16 CSysConfig::SetImageAdjustCmd( EmTPImageAdjust emImageAdjust )
	{
	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData(m_pSession->GetInst());
	pcTpMsg->SetBody(&emImageAdjust, sizeof(EmTPImageAdjust));
	pcTpMsg->SetEvent(ev_TpCamImageAdjust_Cmd);
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_TpCamImageAdjust_Cmd, emEventTypemoontoolSend, "EmTPImageAdjust:%d", emImageAdjust );
	return wRet;
}

void CSysConfig::OnCamImageAdjustInd( const CMessage& cMsg )
{
	CTpMsg cTpMsg(&cMsg);	
	
    u8 uInst = cTpMsg.GetHomeplace();
	
    EmTPImageAdjust emImageAdjust = *reinterpret_cast<EmTPImageAdjust*>(cTpMsg.GetBody());
	
	BOOL bOk = *(BOOL*)(cTpMsg.GetBody()+sizeof(EmTPImageAdjust));
	
	PrtMsg( ev_TpCamImageAdjust_Ind, emEventTypemoontoolRecv, "EmTPImageAdjust:%d, bOk:%d", emImageAdjust, bOk );
	
	PostEvent( UI_MOONTOOL_IMAGE_ADJUST_IND, (WPARAM)emImageAdjust, NULL );
}

u16 CSysConfig::UpdateEthnetCfg( const TTPEthnetInfo& cfg )
{
	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData( m_pSession->GetInst() );
	pcTpMsg->SetEvent( ev_TpMoonCfgEthnet_Cmd );
	pcTpMsg->SetBody( &cfg, sizeof(TTPEthnetInfo) );
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	
	in_addr tAddr;
	tAddr.S_un.S_addr = cfg.dwIP;
	PrtMsg( ev_TpMoonCfgEthnet_Cmd, emEventTypemoontoolSend, "MoonIP: %s", inet_ntoa(tAddr) );
	return wRet;
}

u16 CSysConfig::SetBaudRateCmd( EmTPLVDSBaud emBaudRate )
{
	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData( m_pSession->GetInst() );
	pcTpMsg->SetEvent( ev_TpSetLVDSBaud_Cmd );
	pcTpMsg->SetBody( &emBaudRate, sizeof(EmTPLVDSBaud) );
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	
	PrtMsg( ev_TpSetLVDSBaud_Cmd, emEventTypemoontoolSend, "emBaudRate: %d<em_LVDSBaud_9600bps: %d,\
 em_LVDSBaud_19200bps: %d, em_LVDSBaud_38400bps:%d, em_LVDSBaud_115200bps :%d>", emBaudRate,em_LVDSBaud_9600bps,
 em_LVDSBaud_19200bps,em_LVDSBaud_38400bps,em_LVDSBaud_115200bps);
	return wRet;
}

void CSysConfig::OnLVDBaudInd( const CMessage& cMsg )
{
	CTpMsg cTpMsg(&cMsg);	
	
    EmTPLVDSBaud emTpBaudRate = *reinterpret_cast<EmTPLVDSBaud*>(cTpMsg.GetBody());
	
	BOOL bOk = *(BOOL*)(cTpMsg.GetBody()+sizeof(EmTPLVDSBaud));
	
	PrtMsg( ev_TpSetLVDSBaud_Ind, emEventTypemoontoolRecv, "EmTPLVDSBaud:%d, bOk:%d", emTpBaudRate, bOk );
	
//	PostEvent( UI_MOONTOOL_LVDSBAUD_IND, (WPARAM)&emTpBaudRate, (LPARAM)&bOk );
}

void CSysConfig::OnLVDBaudNty( const CMessage& cMsg )
{
	CTpMsg cTpMsg(&cMsg);	
	
    EmTPLVDSBaud emTpBaudRate = *reinterpret_cast<EmTPLVDSBaud*>(cTpMsg.GetBody());
	BOOL bOk = TRUE;

	PrtMsg( ev_TpSetLVDSBaud_Nty, emEventTypemoontoolRecv, "EmTPLVDSBaud:%d", emTpBaudRate );
	
//	PostEvent( UI_MOONTOOL_LVDSBAUD_IND, (WPARAM)&emTpBaudRate, (LPARAM)&bOk );
}
