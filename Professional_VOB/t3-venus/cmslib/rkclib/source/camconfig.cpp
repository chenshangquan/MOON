// cncconfig.cpp: implementation of the CCncConfig class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "camconfig.h"
#include "socketmanager.h"
#include "rkcevent.h"
#include "rkcprintctrl.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CCamConfig::CCamConfig(CRkcSession &cSession) : CCamConfigIF()
{
	m_pSession = &cSession;
	m_pTPMoonCamCfg = NULL;
	m_byCameraSel = 0;
	m_byCameraSyncSel = 0;

	BuildEventsMap();
}

CCamConfig::~CCamConfig()
{

}

void CCamConfig::BuildEventsMap()
{   
    REG_PFUN( OSP_DISCONNECT, CCamConfig::OnLinkBreak ); 
	REG_PFUN( ev_TpMoonCamInfo_Nty, CCamConfig::OnMoonCamCfgNty );
	REG_PFUN( ev_TpMechanismSelect_Nty, CCamConfig::OnMechanismSelectNty );
	REG_PFUN( ev_TpMechVer_Nty, CCamConfig::OnTpMechverNty );
	REG_PFUN( ev_TpCamSelect_Nty, CCamConfig::OnCamSelNty );
	REG_PFUN( ev_CamParaSynchronize_Ind, CCamConfig::OnCamParaSynchronizeInd );
	REG_PFUN( ev_TpCamSelect_Ind, CCamConfig::OnCamSelInd );
	REG_PFUN( ev_TpMechanismSelect_Ind, CCamConfig::OnCamStyleSelInd );
	REG_PFUN( ev_TpCamSetGamma_Ind, CCamConfig::OnGammaSelInd );
	REG_PFUN( ev_TpCamSetZoonStart_Ind, CCamConfig::OnCamZoomInd );
	REG_PFUN( ev_TpCamSetZoonStop_Ind, CCamConfig::OnCamZoomStopInd );
	REG_PFUN( ev_TpCamSetDrectZoon_Ind, CCamConfig::OnCamZoomValueInd );
	REG_PFUN( ev_TpCamFocusMode_Ind, CCamConfig::OnCamAutoFocusInd );
	REG_PFUN( ev_TpCamFocusNear_Ind, CCamConfig::OnCamFocusNearInd );
	REG_PFUN( ev_TpCamFocusStop_Ind, CCamConfig::OnCamFocusStopInd );
	REG_PFUN( ev_TpCamFocusFar_Ind, CCamConfig::OnCamFocusFarInd );
	REG_PFUN( ev_TpCamExpMode_Ind, CCamConfig::OnAutoExposureInd );
	REG_PFUN( ev_TpCamExpAperture_Ind, CCamConfig::OnCamApertureInd );
	REG_PFUN( ev_TpCamExpGain_Ind, CCamConfig::OnCamGainInd );	
	REG_PFUN( ev_TpCamExpSOrThShutter_Ind, CCamConfig::OnCamShutSpdCInd );
	REG_PFUN( ev_TpCamExpFOrTwShutter_Ind, CCamConfig::OnCamTwShutSpdCInd );
	REG_PFUN( ev_TpCamWhiteBalanceMode_Ind, CCamConfig::OnCamAutoWBInd );
	REG_PFUN( ev_TpCamWhiteBalanceRGain_Ind, CCamConfig::OnCamRGainInd );
	REG_PFUN( ev_TpCamWhiteBalanceBGain_Ind, CCamConfig::OnCamBGainInd );
	REG_PFUN( ev_TpCamImagePara_Ind, CCamConfig::OnCamImageParaInd ); 
	REG_PFUN( ev_TpCamBackLight_Ind, CCamConfig::OnCamLightPensationInd );
	REG_PFUN( ev_TpCamReduNoise_Ind, CCamConfig::OnCamNRInd );
	REG_PFUN( ev_TpSetCam2DNoiseLevle_Ind, CCamConfig::OnCam2DNRInd );
	REG_PFUN( ev_TpSetCam3DNoiseLevle_Ind, CCamConfig::OnCam3DNRInd );
	REG_PFUN( ev_TpCamInitPreset_Ind, CCamConfig::OnCamOrderPosSelInd );
	REG_PFUN( ev_TpCamPreSet_Nty, CCamConfig::OnCamPreSetNty );
	REG_PFUN( ev_TpCamPreSet_Ind, CCamConfig::OnCamPreSetInd );
	REG_PFUN( ev_TpCamPreReset_Ind, CCamConfig::OnCamPreResetInd );
	REG_PFUN( ev_TpCamPreRecall_Ind, CCamConfig::OnCamPreRecallInd );
	REG_PFUN( ev_TpCamPreModify_Ind, CCamConfig::OnCamPreSetModifyInd );	
	REG_PFUN( ev_TpCamParamDefault_Ind, CCamConfig::OnCamParamDefaultInd );
	REG_PFUN( ev_TpImageDistortCorrect_Ind, CCamConfig::OnCamDistortAdjustInd );
	REG_PFUN( ev_TPChangeSideRGB_Nty, CCamConfig::OnChangeSideRGBNty );
	REG_PFUN( ev_TPDirectSetColorRGB_Ind, CCamConfig::OnSetColorRGBDirectInd );
	REG_PFUN( ev_TPSetColorRGB_Ind, CCamConfig::OnSetColorRGBInd );
	REG_PFUN( ev_TPChooseRectangle_Ind, CCamConfig::OnChooseRectangleInd );
	REG_PFUN( ev_TPAutoSetColorConstancy_Ind, CCamConfig::OnSetAutoColorConstancyInd );
	REG_PFUN( ev_TpMoonUpgrade_Ind, CCamConfig::OnMoonUpgradeInd );	
	REG_PFUN( ev_CamUpgrade_Ind, CCamConfig::OnUpdateMechanismInd );
	REG_PFUN( ev_TpSetRefer_Ind, CCamConfig::OnReferenceLineInd );
	REG_PFUN( ev_TpSetRefer_Nty, CCamConfig::OnReferenceLineNty );
	REG_PFUN( ev_TpFlatTurn_Ind, CCamConfig::OnHorizontalFlipInd );
	REG_PFUN( ev_TpFlatTurn_Nty, CCamConfig::OnHorizontalFlipNty );
	REG_PFUN( ev_TpDisortSwitch_Ind, CCamConfig::OnTrapezoidalCorInd );
	REG_PFUN( ev_TPMoonShowRectRegion_Ind, CCamConfig::OnShowRectRegionInd );
	REG_PFUN( ev_TpColorSwich_Ind, CCamConfig::OnColorSwitchInd );
	REG_PFUN( ev_TpSetDisort_Ind, CCamConfig::OnTraCorParamInd );
	REG_PFUN( ev_TpCamSnapshot_Ind, CCamConfig::SnapShotInd );
	REG_PFUN( ev_TPChangeDistor_Ind, CCamConfig::OnChangeDistortInd );
	REG_PFUN( ev_TPDirectSetDistor_Ind, CCamConfig::OnDirectSetDistortInd );
	REG_PFUN( ev_TpSecDefault_Nty, CCamConfig::OnSecDefaultNty );
	REG_PFUN( ev_TpSecBoundary_Nty, CCamConfig::OnSecBoundaryNty );
	//延时矫正
    REG_PFUN( ev_TpFpgaDelayCorrect_Ind, CCamConfig::OnDelayCorrectInd );
	REG_PFUN( ev_TpFpgaDelayCorrect_Nty, CCamConfig::OnDelayCorrectNty );
}

void CCamConfig::DispEvent(const CMessage &cMsg)
{
    DISP_FUN(CCamConfig, cMsg);
}

void CCamConfig::OnLinkBreak(const CMessage& cMsg)
{
	PrtRkcMsg( OSP_DISCONNECT, emEventTypeScoketRecv,"[CCamConfig::OnLinkBreak]清空配置信息" );	
	memset( &m_tCnCameraCfg1, 0, sizeof(TTPMoonCamInfo) );
	memset( &m_tCnCameraCfg2, 0, sizeof(TTPMoonCamInfo) );
	memset( &m_tCnCameraCfg3, 0, sizeof(TTPMoonCamInfo) );
	memset( &m_atTPCamPre, 0, sizeof(TTPCamPre) );	
	m_pTPMoonCamCfg = NULL;
//	再次登陆记住已选择机芯
//	m_byCameraSel = 0;
	//PostEvent(UI_CNS_DISCONNECTED);
}

void CCamConfig::OnTimeOut(u16 wEvent)
{

}

// Moon90摄像机信息
void CCamConfig::OnMoonCamCfgNty( const CMessage& cMsg )
{
	// 收到三条机芯的nty消息 进一次存一次
	//CTpMsg cTpMsg(&cMsg);
	//TTPMoonCamInfo tTPMoonCamInfo = *(TTPMoonCamInfo*)(cTpMsg.GetBody());
	//u8 byIndex = 0;

	//switch( tTPMoonCamInfo.byIndex )
	//{
	//case 0:
	//	{
	//		m_tCnCameraCfg1 = tTPMoonCamInfo;
	//		byIndex = 0;
	//		//PostEvent( UI_DISTORTZOOM_NTY, (WPARAM)&byIndex, (LPARAM)&tTPMoonCamInfo.dwZoom ); //设置左图梯形矫正值
	//		PostEvent( UI_DISTORTZOOM_NTY, (WPARAM)&tTPMoonCamInfo, NULL );
	//		break;
	//	}
	//case 1:
	//	{
	//		m_tCnCameraCfg2 = tTPMoonCamInfo;
	//		byIndex = 1;
	//		//PostEvent( UI_DISTORTZOOM_NTY, (WPARAM)&byIndex, (LPARAM)&tTPMoonCamInfo.dwZoom ); //设置左图梯形矫正值
	//		PostEvent( UI_DISTORTZOOM_NTY, (WPARAM)&tTPMoonCamInfo, NULL );
	//		break;
	//	}
	//case 2:
	//	{
	//		m_tCnCameraCfg3 = tTPMoonCamInfo;
	//		byIndex = 2;
	//		//PostEvent( UI_DISTORTZOOM_NTY, (WPARAM)&byIndex, (LPARAM)&tTPMoonCamInfo.dwZoom ); //设置左图梯形矫正值
	//		PostEvent( UI_DISTORTZOOM_NTY, (WPARAM)&tTPMoonCamInfo, NULL );
	//		break;
	//	}
	//default:
	//	break;
	//}	

	//if ( m_byCameraSel == tTPMoonCamInfo.byIndex )
	//{
	//	PostEvent( UI_MOONTOOL_CAMINFO_NTY, NULL, NULL );
	//}

	//PrtMsg( ev_TpMoonCamInfo_Nty, emEventTypemoontoolRecv, _T("ev_TpMoonCamInfo_Nty") );
	TRK100MsgHead tMsgHead = *reinterpret_cast<TRK100MsgHead*>( cMsg.content );
	tMsgHead.dwEvent = ntohl(tMsgHead.dwEvent);
	tMsgHead.dwHandle = ntohl(tMsgHead.dwHandle);
	tMsgHead.dwProtocolVer = ntohl(tMsgHead.dwProtocolVer);
	tMsgHead.dwRsvd = ntohl(tMsgHead.dwRsvd);
	tMsgHead.dwSerial = ntohl(tMsgHead.dwSerial);
	tMsgHead.nArgv = ntohl(tMsgHead.nArgv);
	tMsgHead.wExtLen = ntohs(tMsgHead.wExtLen);
	tMsgHead.wMsgLen = ntohs(tMsgHead.wMsgLen);
	tMsgHead.wOptRtn = ntohs(tMsgHead.wOptRtn);
	tMsgHead.wReserved1 = ntohs(tMsgHead.wReserved1);

	TTPMoonCamInfo tTPMoonCamInfo;
	u8 byIndex = 0;
	if (tMsgHead.wMsgLen != 0)
	{
		tTPMoonCamInfo = *reinterpret_cast<TTPMoonCamInfo*>( cMsg.content + sizeof(TTPMoonCamInfo) );
	}

	tTPMoonCamInfo.dwBGain = ntohl(tTPMoonCamInfo.dwBGain);
	tTPMoonCamInfo.dwBright = ntohl(tTPMoonCamInfo.dwBright);
	tTPMoonCamInfo.dwContrast = ntohl(tTPMoonCamInfo.dwContrast);
	tTPMoonCamInfo.dwCorrectLevel = ntohl(tTPMoonCamInfo.dwCorrectLevel);
	tTPMoonCamInfo.dwFocusValue = ntohl(tTPMoonCamInfo.dwFocusValue);
	tTPMoonCamInfo.dwHorizonCorrect = ntohl(tTPMoonCamInfo.dwHorizonCorrect);
	tTPMoonCamInfo.dwHorizonStretch = ntohl(tTPMoonCamInfo.dwHorizonStretch);
	tTPMoonCamInfo.dwRGain = ntohl(tTPMoonCamInfo.dwRGain);
	tTPMoonCamInfo.dwSaturat = ntohl(tTPMoonCamInfo.dwSaturat);
	tTPMoonCamInfo.dwSharp = ntohl(tTPMoonCamInfo.dwSharp);
	tTPMoonCamInfo.dwStretchRegion = ntohl(tTPMoonCamInfo.dwStretchRegion);
	tTPMoonCamInfo.dwVerticalCorrect = ntohl(tTPMoonCamInfo.dwVerticalCorrect);
	tTPMoonCamInfo.dwVerticalStretch = ntohl(tTPMoonCamInfo.dwVerticalStretch);
	tTPMoonCamInfo.dwZoom = ntohl(tTPMoonCamInfo.dwZoom);
	tTPMoonCamInfo.dwZoomPos = ntohl(tTPMoonCamInfo.dwZoomPos);
	// emtype ntohl

	switch( tTPMoonCamInfo.byIndex )
	{
	case 0:
		{
			m_tCnCameraCfg1 = tTPMoonCamInfo;
			byIndex = 0;
			//PostEvent( UI_DISTORTZOOM_NTY, (WPARAM)&byIndex, (LPARAM)&tTPMoonCamInfo.dwZoom ); //设置左图梯形矫正值
			PostEvent( UI_DISTORTZOOM_NTY, (WPARAM)&tTPMoonCamInfo, NULL );
			break;
		}
	case 1:
		{
			m_tCnCameraCfg2 = tTPMoonCamInfo;
			byIndex = 1;
			//PostEvent( UI_DISTORTZOOM_NTY, (WPARAM)&byIndex, (LPARAM)&tTPMoonCamInfo.dwZoom ); //设置左图梯形矫正值
			PostEvent( UI_DISTORTZOOM_NTY, (WPARAM)&tTPMoonCamInfo, NULL );
			break;
		}
	case 2:
		{
			m_tCnCameraCfg3 = tTPMoonCamInfo;
			byIndex = 2;
			//PostEvent( UI_DISTORTZOOM_NTY, (WPARAM)&byIndex, (LPARAM)&tTPMoonCamInfo.dwZoom ); //设置左图梯形矫正值
			PostEvent( UI_DISTORTZOOM_NTY, (WPARAM)&tTPMoonCamInfo, NULL );
			break;
		}
	default:
		break;
	}	

	if ( m_byCameraSel == tTPMoonCamInfo.byIndex )
	{
		PostEvent( UI_MOONTOOL_CAMINFO_NTY, NULL, NULL );
	}

	PrtRkcMsg( ev_TpMoonCamInfo_Nty, emEventTypeScoketRecv, _T("ev_TpMoonCamInfo_Nty"));
}

void CCamConfig::OnCamSelNty( const CMessage& cMsg )
{
	/*CTpMsg cTpMsg(&cMsg);

	m_byCameraSel = *(u8*)( cTpMsg.GetBody() );
	SetCameraCfgPtr();

	PrtMsg( ev_TpCamSelect_Nty, emEventTypemoontoolRecv, "byCameraSel:%d", m_byCameraSel );*/
	//if send to the interface
	//PostEvent( UI_MOONTOOL_CamSel_IND, NULL, (LPARAM)bSuccess );
	TRK100MsgHead tMsgHead = *reinterpret_cast<TRK100MsgHead*>( cMsg.content );
	tMsgHead.dwEvent = ntohl(tMsgHead.dwEvent);
	tMsgHead.dwHandle = ntohl(tMsgHead.dwHandle);
	tMsgHead.dwProtocolVer = ntohl(tMsgHead.dwProtocolVer);
	tMsgHead.dwRsvd = ntohl(tMsgHead.dwRsvd);
	tMsgHead.dwSerial = ntohl(tMsgHead.dwSerial);
	tMsgHead.nArgv = ntohl(tMsgHead.nArgv);
	tMsgHead.wExtLen = ntohs(tMsgHead.wExtLen);
	tMsgHead.wMsgLen = ntohs(tMsgHead.wMsgLen);
	tMsgHead.wOptRtn = ntohs(tMsgHead.wOptRtn);
	tMsgHead.wReserved1 = ntohs(tMsgHead.wReserved1);

	if (tMsgHead.wMsgLen != 0)
	{
		m_byCameraSel = *reinterpret_cast<u8*>( cMsg.content + sizeof(u8) );
		SetCameraCfgPtr();
	}

	PrtRkcMsg( ev_TpCamSelect_Nty, emEventTypeScoketRecv, "byCameraSel:%d", m_byCameraSel);
}

u16 CCamConfig::CamSelCmd( const u8& byCameraIndx )
{
	/*CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData(m_pSession->GetInst());
	pcTpMsg->SetBody( &byCameraIndx, sizeof(u8) );
	pcTpMsg->SetEvent(ev_TpCamSelect_Cmd);
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_TpCamSelect_Cmd, emEventTypemoontoolSend, "" );
	return wRet;*/
	return true;
}

void CCamConfig::OnCamSelInd(const CMessage& cMsg)
{
	/*CTpMsg cTpMsg(&cMsg);
	
	m_byCameraSel = *(u8*)( cTpMsg.GetBody() );
	BOOL bSelCam = *(BOOL*)( cTpMsg.GetBody() + sizeof(u8) );
	SetCameraCfgPtr();
	
	PrtMsg( ev_TpCamSelect_Ind, emEventTypemoontoolRecv, "byCameraSel:%d", m_byCameraSel );
	PostEvent( UI_MOONTOOL_CamSel_IND, NULL, (LPARAM)bSelCam );*/
}

u16 CCamConfig::SetMoonCamCfgSyncCmd(const u8& byCameraIndx)
{
	
	/*CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData(m_pSession->GetInst());
	pcTpMsg->SetBody( &byCameraIndx, sizeof(u8) );
	pcTpMsg->SetEvent(ev_CamParaSynchronize_Cmd);
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_CamParaSynchronize_Cmd, emEventTypemoontoolSend, "" );
	return wRet;*/
	return true;
}

void CCamConfig::OnCamParaSynchronizeInd(const CMessage& cMsg)
{
	/*CTpMsg cTpMsg(&cMsg);
	
	m_byCameraSyncSel = *(u8*)( cTpMsg.GetBody() );
	BOOL bSelCamSync = *(BOOL*)( cTpMsg.GetBody() + sizeof(u8) );

	SetCameraParamSync();
	
	PrtMsg( ev_CamParaSynchronize_Ind, emEventTypemoontoolRecv, "byCameraSyncSel:%d", m_byCameraSyncSel );
	PostEvent( UI_MOONTOOL_CamParamSync_IND, (WPARAM)&m_byCameraSyncSel, (LPARAM)bSelCamSync );*/
}

TTPMoonCamInfo CCamConfig::GetCamCfg()
{
	SetCameraCfgPtr();
	return *m_pTPMoonCamCfg;
}

u8 CCamConfig::GetCamSel()const
{
	return m_byCameraSel;
}

void CCamConfig::SetCameraCfgPtr()
{
	switch ( m_byCameraSel )
	{
	case 0:
		{
			m_pTPMoonCamCfg = &m_tCnCameraCfg1;
			break;
		}
	case 1:
		{
			m_pTPMoonCamCfg = &m_tCnCameraCfg2;
			break;
		}
	case 2:
		{
			m_pTPMoonCamCfg = &m_tCnCameraCfg3;
			break;
		}
	default:
		break;
	}
	
	return;
}

void CCamConfig::SetCameraParamSync()
{
	if( m_byCameraSyncSel == 0 )
	{
		m_tCnCameraCfg2 = m_tCnCameraCfg1;
		m_tCnCameraCfg3 = m_tCnCameraCfg1;
		m_tCnCameraCfg2.byIndex = 1;
		m_tCnCameraCfg3.byIndex = 2;
	}
	else if( m_byCameraSyncSel == 1 )
	{
		m_tCnCameraCfg1 = m_tCnCameraCfg2;
		m_tCnCameraCfg3 = m_tCnCameraCfg2;
		m_tCnCameraCfg1.byIndex = 0;
		m_tCnCameraCfg3.byIndex = 2;
	}
	else
	{
		m_tCnCameraCfg1 = m_tCnCameraCfg3;
		m_tCnCameraCfg2 = m_tCnCameraCfg3;
		m_tCnCameraCfg1.byIndex = 0;
		m_tCnCameraCfg2.byIndex = 1;
	}
}

u16 CCamConfig::CamStyleSelCmd( const EmTPMechanism& emTPMechanism )
{
	/*CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData(m_pSession->GetInst());
	pcTpMsg->SetBody( &emTPMechanism, sizeof(EmTPMechanism) );
	pcTpMsg->SetEvent(ev_TpMechanismSelect_Cmd);
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_TpMechanismSelect_Cmd, emEventTypemoontoolSend, "emTPMechanism: %d", emTPMechanism); 
	return wRet;*/
    TRK100MsgHead tRK100MsgHead;//定义消息头结构体
    memset(&tRK100MsgHead,0,sizeof(TRK100MsgHead));
    //整型传数据集的转网络序
    tRK100MsgHead.dwEvent = htonl(ev_TpMechanismSelect_Cmd);
    tRK100MsgHead.wMsgLen = htons(sizeof(EmTPMechanism));
    CRkMessage rkmsg;//定义消息
    rkmsg.SetBody(&tRK100MsgHead, sizeof(TRK100MsgHead));//添加头内容
    rkmsg.CatBody(&emTPMechanism, sizeof(EmTPMechanism));//添加消息体
    
    PrtRkcMsg( ev_TpMechanismSelect_Cmd, emEventTypeScoketSend , "emTPMechanism: %d", emTPMechanism);
    
    SOCKETWORK->SendDataPack(rkmsg);//消息发送
	return NOERROR;
}

void CCamConfig::OnCamStyleSelInd(const CMessage& cMsg)
{
	/*CTpMsg cTpMsg(&cMsg);
	
	EmTPMechanism emTPMechanism = *(EmTPMechanism*)( cTpMsg.GetBody() );
	BOOL bSelStyleCam = *(BOOL*)( cTpMsg.GetBody() + sizeof(EmTPMechanism) );
	SetCameraCfgPtr();
	
	PrtMsg( ev_TpMechanismSelect_Ind, emEventTypemoontoolRecv, "emTPMechanism: %d, bSelStyleCam: %d", emTPMechanism, bSelStyleCam );
	PostEvent( UI_MOONTOOL_CamStyleSel_IND, (WPARAM)&emTPMechanism, (LPARAM)bSelStyleCam );*/

    TRK100MsgHead tMsgHead = *reinterpret_cast<TRK100MsgHead*>( cMsg.content );
    tMsgHead.dwEvent = ntohl(tMsgHead.dwEvent);
    tMsgHead.dwHandle = ntohl(tMsgHead.dwHandle);
    tMsgHead.dwProtocolVer = ntohl(tMsgHead.dwProtocolVer);
    tMsgHead.dwRsvd = ntohl(tMsgHead.dwRsvd);
    tMsgHead.dwSerial = ntohl(tMsgHead.dwSerial);
    tMsgHead.nArgv = ntohl(tMsgHead.nArgv);
    tMsgHead.wExtLen = ntohs(tMsgHead.wExtLen);
    tMsgHead.wMsgLen = ntohs(tMsgHead.wMsgLen);
    tMsgHead.wOptRtn = ntohs(tMsgHead.wOptRtn);
    tMsgHead.wReserved1 = ntohs(tMsgHead.wReserved1);
    
    EmTPMechanism emTPMechanism = emH650;
    if (tMsgHead.wMsgLen != 0)
    {
        emTPMechanism = *reinterpret_cast<EmTPMechanism*>( cMsg.content + sizeof(EmTPMechanism) );
        SetCameraCfgPtr();
    }
    
	PrtRkcMsg( ev_TpMechanismSelect_Ind, emEventTypeScoketRecv, "emTPMechanism: %d, bSelStyleCam: %d", emTPMechanism, tMsgHead.wOptRtn);
}

u16 CCamConfig::SetCamZoomCmd( const EmTPZOOM& emZoom, u8 byIndex)
{
	/*CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData(m_pSession->GetInst());
	pcTpMsg->SetBody( &emZoom, sizeof(EmTPZOOM) );
	pcTpMsg->CatBody( &byIndex, sizeof(u8));
	pcTpMsg->SetEvent(ev_TpCamSetZoonStart_Cmd);
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_TpCamSetZoonStart_Cmd, emEventTypemoontoolSend, "emZoom:%d, byIndex:%d", emZoom, byIndex );
	return wRet;*/
	return true;
}

u16 CCamConfig::SetCamZoomStopCmd(u8 byIndex)
{
	/*CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData(m_pSession->GetInst());
	pcTpMsg->SetBody(&byIndex, sizeof(u8));
	pcTpMsg->SetEvent(ev_TpCamSetZoonStop_Cmd);
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_TpCamSetZoonStop_Cmd, emEventTypemoontoolSend, "byIndex: %d", byIndex );
	return wRet;*/
	return true
}

void CCamConfig::OnCamZoomInd(const CMessage& cMsg)
{
	/*if ( m_pTPMoonCamCfg == NULL )
	{
		SetCameraCfgPtr();
	}
	
	CTpMsg cTpMsg(&cMsg);
	
	EmTPZOOM emZoom = *(EmTPZOOM*)( cTpMsg.GetBody() );
	u8 byIndex = *(u8*)( cTpMsg.GetBody() + sizeof(EmTPZOOM) );
	BOOL bCamZoom = *(BOOL*)( cTpMsg.GetBody() + sizeof(EmTPZOOM) + sizeof(u8) );
	PrtMsg( ev_TpCamSetZoonStart_Ind, emEventTypemoontoolRecv, "EmTPZOOM:%d, byIndex:%d, BOOL:%d", emZoom, byIndex, bCamZoom );*/
}

void CCamConfig::OnCamZoomStopInd(const CMessage& cMsg)
 {
	//CTpMsg cTpMsg(&cMsg);

	//u8 byIndex = *(u8*)( cTpMsg.GetBody() );
	//u32 dwZoom = *(u32*)( cTpMsg.GetBody() + sizeof(u8) );
	//BOOL bCamZoom = *(BOOL*)( cTpMsg.GetBody() + sizeof(u8) + sizeof(u32) );
	//u32 dwZoomPos = *(u32*)(cTpMsg.GetBody() + sizeof(u8) + sizeof(u32) + sizeof(BOOL) );

	//switch(byIndex)
	//{
	//case 0:
	//	{
	//		m_tCnCameraCfg1.dwZoom = dwZoom;
	//		m_tCnCameraCfg1.dwZoomPos = dwZoomPos;
	//		PostEvent( UI_MOONTOOL_CAMSETZOON_STOP_IND, (WPARAM)&m_tCnCameraCfg1, (LPARAM)&bCamZoom );
	//		break;
	//	}
	//case 1:
	//	{
	//		m_tCnCameraCfg2.dwZoom = dwZoom;
	//		m_tCnCameraCfg2.dwZoomPos = dwZoomPos;
	//		m_tCnCameraCfg2.byIndex = 1;
	//		PostEvent( UI_MOONTOOL_CAMSETZOON_STOP_IND, (WPARAM)&m_tCnCameraCfg2, (LPARAM)&bCamZoom );
	//		break;
	//	}
	//case 2:
	//	{
	//		m_tCnCameraCfg3.dwZoom = dwZoom;
	//		m_tCnCameraCfg3.dwZoomPos = dwZoomPos;
	//		m_tCnCameraCfg3.byIndex = 2;
	//		PostEvent( UI_MOONTOOL_CAMSETZOON_STOP_IND, (WPARAM)&m_tCnCameraCfg3, (LPARAM)&bCamZoom );
	//		break;
	//	}
	//default:break;
	//}

	//if (m_pTPMoonCamCfg->byIndex == byIndex)
	//{
	//	m_pTPMoonCamCfg->dwZoom = dwZoom;
	//	m_pTPMoonCamCfg->dwZoomPos = dwZoomPos;
	//}
	////m_pTPMoonCamCfg->dwZoom = *(u32*)( cTpMsg.GetBody() + sizeof(u8) );
	//PrtMsg( ev_TpCamSetZoonStop_Ind, emEventTypemoontoolRecv, "byIndex:%d, dwZoom: %d, dwZoomPos: %d\n", byIndex, dwZoom, dwZoomPos );

	//if ( byIndex == m_byCameraSel )
	//{
	//	PostEvent( UI_MOONTOOL_SET_CAMERA_ZOOM_IND, 0, (LPARAM)bCamZoom );
	//}
}

u16 CCamConfig::SetCamZoomValueCmd( const u32& dwZoom, u8 byIndex)
{
	/*CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData(m_pSession->GetInst());
	pcTpMsg->SetBody( &dwZoom, sizeof(u32) );
	pcTpMsg->CatBody( &byIndex, sizeof(u8) );
	pcTpMsg->SetEvent(ev_TpCamSetDrectZoon_Cmd);
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_TpCamSetDrectZoon_Cmd, emEventTypemoontoolSend, "dwZoom:%d, byIndex: %d", dwZoom, byIndex);
	return wRet;*/
	return true;
}

void CCamConfig::OnCamZoomValueInd(const CMessage& cMsg)
{
	/*if ( m_pTPMoonCamCfg == NULL )
	{
		SetCameraCfgPtr();
	}
	
	CTpMsg cTpMsg(&cMsg);

	u32 dwZoom = *(u32*)( cTpMsg.GetBody());

	u8 byIndex = *(u8*)( cTpMsg.GetBody()+ sizeof(u32) );

	BOOL bOk = *(BOOL*)( cTpMsg.GetBody()+ sizeof(u32) + sizeof(u8) );

	u32 dwZoomPos = *(u32*)( cTpMsg.GetBody()+ sizeof(u32) + sizeof(u8) + sizeof(BOOL) );

	if( 0 == byIndex )
	{
		m_tCnCameraCfg1.dwZoom = dwZoom;
		m_tCnCameraCfg1.dwZoomPos = dwZoomPos;
		m_tCnCameraCfg1.byIndex = 0;
		PostEvent( UI_MOONTOOL_CAMSETZOON_STOP_IND, (WPARAM)&m_tCnCameraCfg1, (LPARAM)&bOk );
	}
	else if( 1 == byIndex )
	{
		m_tCnCameraCfg2.dwZoom = dwZoom;
		m_tCnCameraCfg2.dwZoomPos = dwZoomPos;
		m_tCnCameraCfg2.byIndex = 1;
		PostEvent( UI_MOONTOOL_CAMSETZOON_STOP_IND, (WPARAM)&m_tCnCameraCfg2, (LPARAM)&bOk );
	}
	else
	{
		m_tCnCameraCfg3.dwZoom = dwZoom;
		m_tCnCameraCfg3.byIndex = 2;
		m_tCnCameraCfg3.dwZoomPos = dwZoomPos;
		PostEvent( UI_MOONTOOL_CAMSETZOON_STOP_IND, (WPARAM)&m_tCnCameraCfg3, (LPARAM)&bOk );
	}

	if (m_pTPMoonCamCfg->byIndex == byIndex)
	{
		m_pTPMoonCamCfg->dwZoom = dwZoom;
		m_pTPMoonCamCfg->dwZoomPos = dwZoomPos;
	}

	PrtMsg( ev_TpCamSetDrectZoon_Ind, emEventTypemoontoolRecv, "byIndex:%d, dwZoom: %d, bOk: %d, dwZoomPos: %d", byIndex, dwZoom, bOk, dwZoomPos );
	
	if ( byIndex == m_byCameraSel )
	{
		PostEvent( UI_MOONTOOL_SET_CAMERA_ZOOM_IND, 0, (LPARAM)bOk );
	}	*/
}

u32 CCamConfig::GetCamZoom()
{
	if (m_pTPMoonCamCfg == NULL)
	{
		SetCameraCfgPtr();
	}
	
	return m_pTPMoonCamCfg->dwZoom;	
}

u32 CCamConfig::GetExtCamZoom()
{
	if (m_pTPMoonCamCfg == NULL)
	{
		SetCameraCfgPtr();
	}

	return m_pTPMoonCamCfg->dwZoomPos;	
}

//聚焦 手动/自动
u16 CCamConfig::SetCamAutoFocusCmd(const EmTPMOOMMode& emFocusMode)
{
	/*CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData(m_pSession->GetInst());
	pcTpMsg->SetBody( &emFocusMode, sizeof(EmTPMOOMMode) );
	
	pcTpMsg->SetEvent(ev_TpCamFocusMode_Cmd);
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_TpCamFocusMode_Cmd, emEventTypemoontoolSend, "EmTPMOOMMode:%d", emFocusMode );
	return wRet;*/
	return true;
}

void CCamConfig::OnCamAutoFocusInd(const CMessage& cMsg)
{
	/*if ( m_pTPMoonCamCfg == NULL )
	{
		SetCameraCfgPtr();
	}

	CTpMsg cTpMsg(&cMsg);
	
	m_pTPMoonCamCfg->emFocusMode = *(EmTPMOOMMode*)( cTpMsg.GetBody() );

	BOOL bOk = *(BOOL*)( cTpMsg.GetBody() + sizeof(u8) + sizeof(EmTPMOOMMode) );

	PrtMsg( ev_TpCamFocusMode_Ind, emEventTypemoontoolRecv, "EmTPMOOMMode:%d, BOOL:%d", m_pTPMoonCamCfg->emFocusMode, bOk );
	PostEvent( UI_MOONTOOL_CAMERA_AUTO_FOCUS_IND, (WPARAM)(m_pTPMoonCamCfg->emFocusMode), (LPARAM)bOk );*/
}

//聚焦 拉近/拉远
u16 CCamConfig::SetCamFocusNearCmd()
{
	/*CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData(m_pSession->GetInst());
	
	pcTpMsg->SetEvent(ev_TpCamFocusNear_Cmd);
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_TpCamFocusNear_Cmd, emEventTypemoontoolSend, "" );
	return wRet;*/
	return true;
}

u16 CCamConfig::SetCamFocusStopCmd()
{
	/*CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData(m_pSession->GetInst());
	
	pcTpMsg->SetEvent(ev_TpCamFocusStop_Cmd);
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_TpCamFocusStop_Cmd, emEventTypemoontoolSend, "" );
	return wRet;*/
	return true;
}

u16 CCamConfig::SetCamFocusFarCmd()
{
	/*CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData(m_pSession->GetInst());
	
	pcTpMsg->SetEvent(ev_TpCamFocusFar_Cmd);
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_TpCamFocusFar_Cmd, emEventTypemoontoolSend, "" );
	return wRet;*/
	return true;
}

void CCamConfig::OnCamFocusNearInd( const CMessage& cMsg )
{
	/*if ( m_pTPMoonCamCfg == NULL )
	{
		SetCameraCfgPtr();
	}
	
	CTpMsg cTpMsg(&cMsg);	
	BOOL bFocusNear =  *(BOOL*)( cTpMsg.GetBody() + sizeof(u8) );
	PrtMsg( ev_TpCamFocusNear_Ind, emEventTypemoontoolRecv, "bFocusNear:%d", bFocusNear );*/
}

void CCamConfig::OnCamFocusStopInd( const CMessage& cMsg )
{
	/*if ( m_pTPMoonCamCfg == NULL )
	{
		SetCameraCfgPtr();
	}
	
	CTpMsg cTpMsg(&cMsg);	
	BOOL bIsStop =  *(BOOL*)( cTpMsg.GetBody() + sizeof(u8) );
	PrtMsg( ev_TpCamFocusStop_Ind, emEventTypemoontoolRecv, "bIsStop:%d", bIsStop );*/
}

void CCamConfig::OnCamFocusFarInd( const CMessage& cMsg )
{
	/*if ( m_pTPMoonCamCfg == NULL )
	{
		SetCameraCfgPtr();
	}
	
	CTpMsg cTpMsg(&cMsg);	
	BOOL bFocusFar =  *(BOOL*)( cTpMsg.GetBody() + sizeof(u8) );
	PrtMsg( ev_TpCamFocusFar_Ind, emEventTypemoontoolRecv, "bFocusFar:%d", bFocusFar );	*/
}


//是否开启自动曝光
u16 CCamConfig::CamAutoExposureCmd( const EmTPMOOMMode& emExpAuto )
{
	/*CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData(m_pSession->GetInst());
	pcTpMsg->SetBody( &emExpAuto, sizeof(EmTPMOOMMode) );	
	pcTpMsg->SetEvent(ev_TpCamExpMode_Cmd);
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_TpCamExpMode_Cmd, emEventTypemoontoolSend, "CamAutoExposureCmd:%d", emExpAuto );
	return wRet;*/
	return true;
}

EmTPMOOMMode CCamConfig::GetCamMoonMode()
{
	if ( m_pTPMoonCamCfg == NULL )
	{
		SetCameraCfgPtr();
	}
	
	return m_pTPMoonCamCfg->emExpMode;
}

void CCamConfig::OnAutoExposureInd(const CMessage& cMsg)
{
	/*if ( m_pTPMoonCamCfg == NULL )
	{
		SetCameraCfgPtr();
	}
	
	CTpMsg cTpMsg(&cMsg);
	
	m_pTPMoonCamCfg->emExpMode = *(EmTPMOOMMode*)( cTpMsg.GetBody() );
	BOOL bAutoExposure = *(BOOL*)( cTpMsg.GetBody() + sizeof(u8) + sizeof(EmTPMOOMMode) );
	
	PrtMsg( ev_TpCamExpMode_Ind, emEventTypemoontoolRecv, "EmExpMode:%d, AutoExposureInd:%d", m_pTPMoonCamCfg->emExpMode, bAutoExposure );
	PostEvent( UI_MOONTOOL_CAMERA_AUTO_EXPOSURE_IND, NULL, (LPARAM)bAutoExposure );*/
}

//光圈
u16 CCamConfig::CamApertureCmd( const EmTPAperture& emAperture )
{
	/*CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData(m_pSession->GetInst());
	pcTpMsg->SetBody( &emAperture, sizeof(EmTPAperture) );
	pcTpMsg->SetEvent(ev_TpCamExpAperture_Cmd);
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_TpCamExpAperture_Cmd, emEventTypemoontoolSend, "CamApertureCmd:%d", emAperture );
	return wRet;*/
	return true;
}

EmTPAperture CCamConfig::GetCamAperture()
{
	if (m_pTPMoonCamCfg == NULL)
	{
		SetCameraCfgPtr();
	}
	
	return m_pTPMoonCamCfg->emAper;
}

void CCamConfig::OnCamApertureInd(const CMessage& cMsg)
{
	//if (m_pTPMoonCamCfg == NULL)
	//{
	//	SetCameraCfgPtr();
	//}
	//
	//CTpMsg cTpMsg(&cMsg);
	//
	//m_pTPMoonCamCfg->emAper = *(EmTPAperture*)( cTpMsg.GetBody() );
	//BOOL bCamAperture = *(BOOL*)( cTpMsg.GetBody() +sizeof(u8) +sizeof(EmTPAperture) );
	//PrtMsg( ev_TpCamExpAperture_Ind, emEventTypemoontoolRecv, "EmTPAperture:%d, BOOL:%d", m_pTPMoonCamCfg->emAper, bCamAperture );
	//// 通知界面操作成功与否
	//PostEvent( UI_MOONTOOL_CAMERA_APERTURE_IND, NULL, (LPARAM)bCamAperture );
}

// 快门
u16 CCamConfig::CamShutSpdCmd( const EmTPSOrThShutter& emShutSpd )
{
	/*CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData(m_pSession->GetInst());
	pcTpMsg->SetBody( &emShutSpd, sizeof(EmTPSOrThShutter) );
	pcTpMsg->SetEvent(ev_TpCamExpSOrThShutter_Cmd);
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_TpCamExpSOrThShutter_Cmd, emEventTypemoontoolSend, "CamShutSpdCmd:%d", emShutSpd );
	return wRet;*/
	return true;
}

u16 CCamConfig::CamTwShutSpdCmd( const EmTPFOrTwShutter& emTwShutter )
{
	/*CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData(m_pSession->GetInst());
	pcTpMsg->SetBody( &emTwShutter, sizeof(EmTPFOrTwShutter) );
	pcTpMsg->SetEvent(ev_TpCamExpFOrTwShutter_Cmd);
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_TpCamExpFOrTwShutter_Cmd, emEventTypemoontoolSend, "CamTwShutSpdCmd:%d", emTwShutter );
	return wRet;*/
	return true;
}

EmTPSOrThShutter CCamConfig::GetCamShutSpd()
{
	if (m_pTPMoonCamCfg == NULL)
	{
		SetCameraCfgPtr();
	}
	
	return m_pTPMoonCamCfg->emSOrThShutSpd;
}

EmTPFOrTwShutter CCamConfig::GetTwCamShutSpd()
{
	if (m_pTPMoonCamCfg == NULL)
	{
		SetCameraCfgPtr();
	}
	
	return m_pTPMoonCamCfg->emFOrTwShutSpd;
}

void CCamConfig::OnCamShutSpdCInd(const CMessage& cMsg)
{
	/*if (m_pTPMoonCamCfg == NULL)
	{
		SetCameraCfgPtr();
	}
	
	CTpMsg cTpMsg(&cMsg);
	
	m_pTPMoonCamCfg->emSOrThShutSpd = *(EmTPSOrThShutter*)( cTpMsg.GetBody() );
	BOOL bCamShutSpdC = *(BOOL*)( cTpMsg.GetBody() +sizeof(u8) +sizeof(EmTPSOrThShutter) );
	PrtMsg( ev_TpCamExpSOrThShutter_Ind, emEventTypemoontoolRecv, "EmShutSpd:%d, BOOL:%d", m_pTPMoonCamCfg->emSOrThShutSpd, bCamShutSpdC );
	PostEvent( UI_MOONTOOL_CAMERA_SHUT_SPD_IND, NULL, (LPARAM)bCamShutSpdC );*/
}

void CCamConfig::OnCamTwShutSpdCInd( const CMessage& cMsg )
{
	/*if (m_pTPMoonCamCfg == NULL)
	{
		SetCameraCfgPtr();
	}
	
	CTpMsg cTpMsg(&cMsg);
	
	m_pTPMoonCamCfg->emFOrTwShutSpd = *(EmTPFOrTwShutter*)( cTpMsg.GetBody() );
	BOOL bCamShutSpdC = *(BOOL*)( cTpMsg.GetBody() +sizeof(u8) +sizeof(EmTPFOrTwShutter) );
	PrtMsg( ev_TpCamExpFOrTwShutter_Ind, emEventTypemoontoolRecv, "EmShutSpd:%d, BOOL:%d", m_pTPMoonCamCfg->emFOrTwShutSpd, bCamShutSpdC );
	PostEvent( UI_MOONTOOL_CAMERA_SHUT_SPD_IND, NULL, (LPARAM)bCamShutSpdC );*/	
}

//增益
u16 CCamConfig::CamGainCmd( const EmTPExpGain& emExpGain )
{
	/*CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData(m_pSession->GetInst());
	pcTpMsg->SetBody( &emExpGain, sizeof(EmTPExpGain) );
	pcTpMsg->SetEvent(ev_TpCamExpGain_Cmd);
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_TpCamExpGain_Cmd, emEventTypemoontoolSend, "CamGainCmd:%d", emExpGain );
	return wRet;*/
	return true;
}

EmTPExpGain CCamConfig::GetCamGain()
{
	if (m_pTPMoonCamCfg == NULL)
	{
		SetCameraCfgPtr();
	}
	
	return m_pTPMoonCamCfg->emGain;
}

void CCamConfig::OnCamGainInd(const CMessage& cMsg)
{
	/*if (m_pTPMoonCamCfg == NULL)
	{
		SetCameraCfgPtr();
	}
	
	CTpMsg cTpMsg(&cMsg);
	
	m_pTPMoonCamCfg->emGain = *(EmTPExpGain*)( cTpMsg.GetBody() );
	BOOL bCamGain = *(BOOL*)( cTpMsg.GetBody() +sizeof(u8) +sizeof(EmTPExpGain) );
	PrtMsg( ev_TpCamExpGain_Ind, emEventTypemoontoolRecv, "EmShutSpd:%d, BOOL:%d", m_pTPMoonCamCfg->emGain, bCamGain );
	PostEvent( UI_MOONTOOL_CAMERA_GAIN_IND, NULL, (LPARAM)bCamGain );*/
}

// 白平衡
u16 CCamConfig::CamAutoWBCmd( const EmTPMOOMMode& emWBMode )
{
	/*CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData(m_pSession->GetInst());
	pcTpMsg->SetBody( &emWBMode, sizeof(EmTPMOOMMode) );
	pcTpMsg->SetEvent(ev_TpCamWhiteBalanceMode_Cmd);
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_TpCamWhiteBalanceMode_Cmd, emEventTypemoontoolSend, "CamAutoWBCmd:%d", emWBMode );
	return wRet;*/
	return true;
}

EmTPMOOMMode CCamConfig::GetCamWBMode()
{
	if (m_pTPMoonCamCfg == NULL)
	{
		SetCameraCfgPtr();
	}
	
	return m_pTPMoonCamCfg->emWBMode;
}

void CCamConfig::OnCamAutoWBInd(const CMessage& cMsg)
{
	/*if ( m_pTPMoonCamCfg == NULL )
	{
		SetCameraCfgPtr();
	}
	
	CTpMsg cTpMsg(&cMsg);
	
	m_pTPMoonCamCfg->emWBMode = *(EmTPMOOMMode*)( cTpMsg.GetBody() );
	BOOL bCamAutoWB = *(BOOL*)( cTpMsg.GetBody() + sizeof(u8) + sizeof(EmTPMOOMMode) );
	
	PrtMsg( ev_TpCamWhiteBalanceMode_Ind, emEventTypemoontoolRecv, "EmWBMode:%d, CamAutoWBInd:%d", m_pTPMoonCamCfg->emWBMode, bCamAutoWB );
	PostEvent( UI_MOONTOOL_CAMERA_AUTO_WB_IND, NULL, (LPARAM)bCamAutoWB );*/
}

u16 CCamConfig::CamRGainCmd( const u32& dwRGain )
{
	/*CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData(m_pSession->GetInst());
	pcTpMsg->SetBody(&dwRGain, sizeof(u32));
	pcTpMsg->SetEvent(ev_TpCamWhiteBalanceRGain_Cmd);
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_TpCamWhiteBalanceRGain_Cmd, emEventTypemoontoolSend, "dwRGain:%d", dwRGain );
	return wRet;*/
	return true;
}

u32 CCamConfig::GetCamRGain()
{
	if ( m_pTPMoonCamCfg == NULL )
	{
		SetCameraCfgPtr();
	}
	return m_pTPMoonCamCfg->dwRGain;
}

void CCamConfig::OnCamRGainInd(const CMessage& cMsg)
{
	/*if ( m_pTPMoonCamCfg == NULL )
	{
		SetCameraCfgPtr();
	}
	
	CTpMsg cTpMsg(&cMsg);
	m_pTPMoonCamCfg->dwRGain = *(u32*)( cTpMsg.GetBody() );
	BOOL bCamRGain = *(BOOL*)( cTpMsg.GetBody() + sizeof(u32) +sizeof(u8) );

	PrtMsg( ev_TpCamWhiteBalanceRGain_Ind, emEventTypemoontoolRecv, "dwRGain:%d, bCamRGain:%d", m_pTPMoonCamCfg->dwRGain, bCamRGain );
	PostEvent( UI_MOONTOOL_CAMERA_RGAIN_IND, NULL, (LPARAM)bCamRGain );*/
}

u16 CCamConfig::CamAdjustRangeCmd( const u32& dwAdjustRange )
{
	/*CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData(m_pSession->GetInst());
	
	TTPDistortParam tTPDistortParam;
	tTPDistortParam.dwCorrectLevel = dwAdjustRange;
	tTPDistortParam.dwEnable = 1;

	pcTpMsg->SetBody(&tTPDistortParam, sizeof(TTPDistortParam));
	pcTpMsg->SetEvent(ev_TpImageDistortCorrect_Cmd);
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_TpImageDistortCorrect_Cmd, emEventTypemoontoolSend, "dwAdjustRange:%d", dwAdjustRange );
	return wRet;*/
	return true;
}

u16 CCamConfig::CamHoriStretchCmd( const u32& dwHoriStretch )
{
	/*CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData(m_pSession->GetInst());
	
	TTPDistortParam tTPDistortParam;
	tTPDistortParam.dwStretchRegion = dwHoriStretch;
	
	pcTpMsg->SetBody(&tTPDistortParam, sizeof(TTPDistortParam));
	pcTpMsg->SetEvent(ev_TpImageDistortCorrect_Cmd);
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_TpImageDistortCorrect_Cmd, emEventTypemoontoolSend, "dwHoriStretch:%d", dwHoriStretch );
	return wRet;*/
	return true;
}

u16 CCamConfig::CamBGainCmd( const u32& dwBGain )
{
	/*CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData(m_pSession->GetInst());
	pcTpMsg->SetBody(&dwBGain, sizeof(u32));
	pcTpMsg->SetEvent(ev_TpCamWhiteBalanceBGain_Cmd);
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_TpCamWhiteBalanceBGain_Cmd, emEventTypemoontoolSend, "dwBGain:%d", dwBGain );
	return wRet;*/
	return true;
}

u32 CCamConfig::GetCamBGain()
{
	if ( m_pTPMoonCamCfg == NULL )
	{
		SetCameraCfgPtr();
	}
	
	return m_pTPMoonCamCfg->dwBGain;
}

u32 CCamConfig::GetCamAdjustRange()
{
	if ( m_pTPMoonCamCfg == NULL )
	{
		SetCameraCfgPtr();
	}
	
	return m_pTPMoonCamCfg->dwCorrectLevel;
}

u32 CCamConfig::GetCamHoriStretch()
{
	if ( m_pTPMoonCamCfg == NULL )
	{
		SetCameraCfgPtr();
	}
	
	return m_pTPMoonCamCfg->dwStretchRegion;
}

void CCamConfig::OnCamBGainInd(const CMessage& cMsg)
{
	/*if ( m_pTPMoonCamCfg == NULL )
	{
		SetCameraCfgPtr();
	}
	
	CTpMsg cTpMsg(&cMsg);
	
	m_pTPMoonCamCfg->dwBGain = *(u32*)( cTpMsg.GetBody() );
	BOOL bCamBGain = *(BOOL*)( cTpMsg.GetBody() + sizeof(u32) +sizeof(u8) );

	PrtMsg( ev_TpCamWhiteBalanceBGain_Ind, emEventTypemoontoolRecv, "dwBGain:%d, bCamBGain:%d", m_pTPMoonCamCfg->dwBGain, bCamBGain );
	PostEvent( UI_MOONTOOL_CAMERA_BGAIN_IND, NULL, (LPARAM)bCamBGain );*/
}

// 图片参数
u16 CCamConfig::CamImageParaCmd( EmTPImagePara emImagePara, const u32& dwImagePara )
{
	/*CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData(m_pSession->GetInst());
	pcTpMsg->SetBody(&emImagePara, sizeof(EmTPImagePara));
	pcTpMsg->CatBody(&dwImagePara, sizeof(u32));
	pcTpMsg->SetEvent(ev_TpCamImagePara_Cmd);
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_TpCamImagePara_Cmd, emEventTypemoontoolSend, "emImagePara:%d, dwImagePara:%d", emImagePara, dwImagePara );
	return wRet;*/
	return true;
}

void CCamConfig::OnCamImageParaInd(const CMessage& cMsg)
{
	//if ( m_pTPMoonCamCfg == NULL )
	//{
	//	SetCameraCfgPtr();
	//}
	//
	//CTpMsg cTpMsg(&cMsg);
	//
	//EmTPImagePara emTPImagePara = *(EmTPImagePara*)( cTpMsg.GetBody() );
	////值是否要设置到具体的摄像机
	//u32 dwValue = *(u32*)( cTpMsg.GetBody() + sizeof(EmTPImagePara) );
	//switch ( emTPImagePara )
	//{
	//case emBlight:
	//	{
	//		m_pTPMoonCamCfg->dwBright = dwValue;
	//		PostEvent( UI_MOONTOOL_IMAGE_BLIGHT_IND, 0, (LPARAM)(m_pTPMoonCamCfg->dwBright) );
	//		break;
	//	}
	//case emContrast:
	//	{
	//		m_pTPMoonCamCfg->dwContrast = dwValue;
	//		PostEvent( UI_MOONTOOL_IMAGE_CONTRAST_IND, 0, (LPARAM)(m_pTPMoonCamCfg->dwContrast) );
	//		break;
	//	}
	//case emSharp:
	//	{
	//		m_pTPMoonCamCfg->dwSharp = dwValue;
	//		PostEvent( UI_MOONTOOL_IMAGE_Sharp_IND, 0, (LPARAM)(m_pTPMoonCamCfg->dwSharp) );
	//		break;
	//	}
	//case emSaturat:
	//	{
	//		m_pTPMoonCamCfg->dwSaturat = dwValue;
	//		PostEvent( UI_MOONTOOL_IMAGE_SATURAT_IND, 0, (LPARAM)(m_pTPMoonCamCfg->dwSaturat) );
	//		break;
	//	}
	//default:
	//	break;
	//}

	//
	//BOOL bCamImagePara = *(BOOL*)( cTpMsg.GetBody() + sizeof(EmTPImagePara) + sizeof(u32) + sizeof(u8) );
	//PrtMsg( ev_TpCamImagePara_Ind, emEventTypemoontoolRecv, "bCamImagePara:%d", bCamImagePara);
	//PostEvent( UI_MOONTOOL_IMAGEPARA_IND, (WPARAM)emTPImagePara, (LPARAM)bCamImagePara );
}

//背光补偿
u16 CCamConfig::CamLightPensation( BOOL bIsOpen)
{
	/*CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData(m_pSession->GetInst());
	pcTpMsg->SetBody(&bIsOpen, sizeof(BOOL));
	pcTpMsg->SetEvent(ev_TpCamBackLight_Cmd);
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_TpCamBackLight_Cmd, emEventTypemoontoolSend, "bIsOpen:%d", bIsOpen );
	return wRet;*/
	return true;
}

//梯形校正
u16 CCamConfig::CamKeystoneAdjust(const TTPDistortParam& tTPDistortParam ,EmTPCorrect emMyOption )
{
	/*CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData(m_pSession->GetInst());
	pcTpMsg->SetBody(&tTPDistortParam, sizeof(TTPDistortParam));
	pcTpMsg->CatBody(&emMyOption, sizeof(EmTPCorrect));
	pcTpMsg->SetEvent(ev_TpImageDistortCorrect_Cmd);
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_TpImageDistortCorrect_Cmd, emEventTypemoontoolSend, "Correction Value %d ; Tensile value %d ; \
MyOpetion:%d <em_HorizonCorrect:%d ; em_HorizonStretch:%d ; em_VerticalCorrect:%d ; em_VerticalStretch:%d > ",
tTPDistortParam.dwCorrectLevel,tTPDistortParam.dwStretchRegion,emMyOption,em_HorizonCorrect,em_HorizonStretch,em_VerticalCorrect,em_VerticalStretch);
	return wRet;*/
	return true;
}

u16 CCamConfig::SetCorConsistRGBCmd(u8 nPosition, EmTPColorConsistency emMyCorConsOption, EmTPCorrectChange emChangeOption)
{
	/*CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData(m_pSession->GetInst());
	pcTpMsg->SetBody(&nPosition, sizeof(u8));
	pcTpMsg->CatBody(&emMyCorConsOption, sizeof(EmTPColorConsistency));
	pcTpMsg->CatBody(&emChangeOption, sizeof(EmTPCorrectChange));
	pcTpMsg->SetEvent( ev_TPSetColorRGB_Cmd );
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_TPSetColorRGB_Cmd, emEventTypemoontoolSend, "nPositon:%d, emMyCorConsOption: %d, emChangeOption:%d", nPosition, emMyCorConsOption, emChangeOption );
	
	return wRet;*/
	return true;
}

u16 CCamConfig::SetChangeDistortCmd(u8 byIndex, EmTPCorrectChange emTPCorrectChange, EmTPDistortPosition emTPDistortPosition)
{
	/*CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData(m_pSession->GetInst());
	pcTpMsg->SetBody(&byIndex, sizeof(u8));	
	pcTpMsg->CatBody(&emTPDistortPosition, sizeof(EmTPDistortPosition));
	pcTpMsg->CatBody(&emTPCorrectChange, sizeof(EmTPCorrectChange));	
	pcTpMsg->SetEvent( ev_TPChangeDistor_Cmd );

	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_TPChangeDistor_Cmd, emEventTypemoontoolSend, "byIndex:%d, emTPDistortPosition: %d, emTPCorrectChange:%d", byIndex, emTPDistortPosition, emTPCorrectChange );

	return wRet;*/
	return true;
}

u16 CCamConfig::SetDirectDistortCmd( const TTPDistortInfo&tTpDistortInfo )
{
	/*CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData(m_pSession->GetInst());
	pcTpMsg->SetBody(&tTpDistortInfo, sizeof(TTPDistortInfo));
	pcTpMsg->SetEvent( ev_TPDirectSetDistor_Cmd );

	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_TPChangeDistor_Cmd, emEventTypemoontoolSend, "byIndex: %d, emDistortType: %d, dwValue: %d", tTpDistortInfo.byIndex, tTpDistortInfo.emDistortType, tTpDistortInfo.dwValue );

	return wRet;*/
	return true;
}

u16 CCamConfig::SetAutoSetColorConstancyCmd()
{
	/*CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData(m_pSession->GetInst());
	pcTpMsg->SetEvent( ev_TPAutoSetColorConstancy_Cmd );

	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_TPAutoSetColorConstancy_Cmd, emEventTypemoontoolSend, "" );

	return wRet;*/
	return true;
}

u16 CCamConfig::SetChooseRectangleCmd(const TTPMoonRectRegion& tTPMoonRectRegion)
{
	/*CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData(m_pSession->GetInst());
	pcTpMsg->SetBody(&tTPMoonRectRegion, sizeof(TTPMoonRectRegion));
	pcTpMsg->SetEvent(ev_TPChooseRectangle_Cmd);

	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_TPChooseRectangle_Cmd, emEventTypemoontoolSend, "byIndex: %d, dwXCoordinate: %d, dwYCoordinate: %d, dwLenth: %d, dwWidth: %d",
		tTPMoonRectRegion.byIndex, tTPMoonRectRegion.dwXCoordinate, tTPMoonRectRegion.dwYCoordinate, tTPMoonRectRegion.dwLenth, tTPMoonRectRegion.dwWidth );
	return wRet;*/
	return true;
}

void CCamConfig::OnChooseRectangleInd(const CMessage& cMsg)
{
	/*CTpMsg cTpMsg(&cMsg);
	TTPMoonRectRegion tTPMoonRectRegion = *(TTPMoonRectRegion*)(cTpMsg.GetBody());
	BOOL bOk = *(BOOL*)( cTpMsg.GetBody() + sizeof(TTPMoonRectRegion));

	PrtMsg( ev_TPChooseRectangle_Ind, emEventTypemoontoolRecv, "byIndex: %d, dwXCoordinate: %d, dwYCoordinate: %d, dwLenth: %d, dwWidth: %d, bOk: %d",
		tTPMoonRectRegion.byIndex, tTPMoonRectRegion.dwXCoordinate, tTPMoonRectRegion.dwYCoordinate, tTPMoonRectRegion.dwLenth, tTPMoonRectRegion.dwWidth, bOk );

	PostEvent( UI_CHOOSERECTANGLE_IND, (WPARAM)&tTPMoonRectRegion, (LPARAM)&bOk );*/
}

void CCamConfig::OnSetColorRGBInd(const CMessage& cMsg)
{
	/*CTpMsg cTpMsg(&cMsg);
	
	u8 nPosition = *(u8*)(cTpMsg.GetBody());
	EmTPColorConsistency emMyColorOption = *(EmTPColorConsistency*)(cTpMsg.GetBody()+sizeof(u8));
	u32 dwRGBDirectVal = *(u32*)(cTpMsg.GetBody()+sizeof(u8)+sizeof(EmTPColorConsistency));
	BOOL bSuccess = *(BOOL *)(cTpMsg.GetBody()+sizeof(u8)+sizeof(EmTPColorConsistency)+sizeof(u32));

	TTPColorRGBCoeff tTPColorRGBCoeff;
	tTPColorRGBCoeff.byIndex = nPosition;
	tTPColorRGBCoeff.emColorType = emMyColorOption;
	tTPColorRGBCoeff.dwValue = dwRGBDirectVal;
	
	PrtMsg( ev_TPSetColorRGB_Ind, emEventTypemoontoolRecv, "nPosition: %d, emMyColorOption: %d, dwRGBDirectVal: %d, bSuccess: %d",
		nPosition, emMyColorOption, dwRGBDirectVal, bSuccess);
	
	PostEvent(UI_SETCOLORRGB_IND, (WPARAM)&tTPColorRGBCoeff, (LPARAM)&bSuccess);*/
		
}

void CCamConfig::OnSetAutoColorConstancyInd(const CMessage& cMsg)
{
	/*CTpMsg cTpMsg(&cMsg);

	u32 dwRGBColorValue[MOON_COLOR_COEFF_NUM];

	BOOL bSuccess = *(BOOL*)(cTpMsg.GetBody() + sizeof(u32) * MOON_COLOR_COEFF_NUM );
	for( int i=0; i<MOON_COLOR_COEFF_NUM; i++ )
	{
		dwRGBColorValue[i] = *(u32*)( cTpMsg.GetBody() + sizeof(u32)*i);
	}

	PrtMsg( ev_TPAutoSetColorConstancy_Ind, emEventTypemoontoolRecv, "dwRGBColorValue1: %d, dwRGBColorValue2: %d, dwRGBColorValue3: %d, dwRGBColorValue4: %d,\
         dwRGBColorValue5: %d, dwRGBColorValue6: %d, dwRGBColorValue7: %d, dwRGBColorValue8: %d, dwRGBColorValue9: %d, bSuccess : %d", dwRGBColorValue[0], dwRGBColorValue[1], dwRGBColorValue[2],
				  dwRGBColorValue[3], dwRGBColorValue[4], dwRGBColorValue[5], dwRGBColorValue[6], dwRGBColorValue[7], dwRGBColorValue[8], bSuccess );

	PostEvent( UI_AUTOSETCOLORCONSTANCY_IND, (WPARAM)&bSuccess, (LPARAM)&dwRGBColorValue );*/

}

void CCamConfig::OnChangeSideRGBNty(const CMessage& cMsg)
{
	/*CTpMsg cTpMsg(&cMsg);

	u32 dwSideColorVal[2];
	EmTPColorConsistency emMyColorOption = *(EmTPColorConsistency*)(cTpMsg.GetBody());
	dwSideColorVal[0] = *(u32*)(cTpMsg.GetBody()+sizeof(EmTPColorConsistency));
	dwSideColorVal[1] = *(u32*)(cTpMsg.GetBody()+sizeof(EmTPColorConsistency)+sizeof(u32));

	PrtMsg(ev_TPChangeSideRGB_Nty, emEventTypemoontoolRecv, "emMyColorOption: %d, dwSideColorVal[0]: %d, dwSideColorVal[1]: %d", emMyColorOption, dwSideColorVal[0], dwSideColorVal[1]);

	PostEvent(UI_CHANGESIDERGB_NTY, (WPARAM)&emMyColorOption, (LPARAM)&dwSideColorVal);*/

}

u16 CCamConfig::SetColorRGBDirectCmd(u8 nPosition, EmTPColorConsistency emMyCorConsOption, const u32& dwRGBDirectValue)
{
	/*CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData(m_pSession->GetInst());
	pcTpMsg->SetBody(&nPosition, sizeof(u8));
	pcTpMsg->CatBody(&emMyCorConsOption, sizeof(EmTPColorConsistency));
	pcTpMsg->CatBody(&dwRGBDirectValue, sizeof(u32));
	pcTpMsg->SetEvent(ev_TPDirectSetColorRGB_Cmd);
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg(ev_TPDirectSetColorRGB_Cmd, emEventTypemoontoolSend, "nPosition:%d, emMyCorConsOption: %d, emMyCorConsOption: %d", nPosition, emMyCorConsOption, emMyCorConsOption);
	
	return wRet;*/
	return true;
}

void CCamConfig::OnSetColorRGBDirectInd(const CMessage& cMsg)
{
	/*CTpMsg cTpMsg(&cMsg);
	
	u8 nPosition = *(u8*)(cTpMsg.GetBody());
	EmTPColorConsistency emMyColorOption = *(EmTPColorConsistency*)(cTpMsg.GetBody()+sizeof(u8));
	u32 dwRGBDirectVal = *(u32*)(cTpMsg.GetBody()+sizeof(u8)+sizeof(EmTPColorConsistency));
	BOOL bSuccess = *(BOOL *)(cTpMsg.GetBody()+sizeof(u8)+sizeof(EmTPColorConsistency)+sizeof(u32));

	TTPColorRGBCoeff tTPColorRGBCoeff;
	tTPColorRGBCoeff.byIndex = nPosition;
	tTPColorRGBCoeff.emColorType = emMyColorOption;
	tTPColorRGBCoeff.dwValue = dwRGBDirectVal;
    
	PrtMsg(ev_TPDirectSetColorRGB_Ind, emEventTypemoontoolRecv, "nPosition: %d, emMyColorOption: %d, dwRGBDirectVal: %d, bSuccess: %d",
		nPosition, emMyColorOption, dwRGBDirectVal, bSuccess);

	PostEvent(UI_DIRECT_SETCOLORRGB_IND, (WPARAM)&tTPColorRGBCoeff, (LPARAM)&bSuccess);*/
}

void CCamConfig::OnCamDistortAdjustInd( const CMessage& cMsg )
{
//	if ( m_pTPMoonCamCfg == NULL )
//	{
//		SetCameraCfgPtr();
//	}
//	
//	CTpMsg cTpMsg(&cMsg);
//	TTPDistortParam tDistortParam = *(TTPDistortParam*)( cTpMsg.GetBody());
//	EmTPCorrect emMyOption = *(EmTPCorrect*)(cTpMsg.GetBody()+sizeof(TTPDistortParam));
//	BOOL bSuccess = *(BOOL *)(cTpMsg.GetBody()+sizeof(TTPDistortParam)+sizeof(EmTPCorrect)+sizeof(u8));
//	if ( bSuccess == TRUE )
//	{
//		if (( emMyOption == em_HorizonCorrect) || ( emMyOption == em_HorizonStretch ))
//		{
//			m_pTPMoonCamCfg->dwHorizonCorrect = tDistortParam.dwCorrectLevel;
//			m_pTPMoonCamCfg->dwHorizonStretch = tDistortParam.dwStretchRegion;
//		}
//		else
//		{
//			m_pTPMoonCamCfg->dwVerticalCorrect = tDistortParam.dwCorrectLevel;
//			m_pTPMoonCamCfg->dwVerticalStretch = tDistortParam.dwStretchRegion;
//		}
//	}
//
////	m_pTPMoonCamCfg->bIsCorrect = tDistortParam.dwEnable;
//	
//	PrtMsg( ev_TpImageDistortCorrect_Ind, emEventTypemoontoolRecv, "Success %d ; Correction Value %d ; Tensile value %d ;MyOpetion:%d <em_HorizonCorrect:%d ; em_HorizonStretch:%d ;\
//		em_VerticalCorrect:%d ; em_VerticalStretch:%d > ",bSuccess,tDistortParam.dwCorrectLevel,tDistortParam.dwStretchRegion,
//		emMyOption,em_HorizonCorrect,em_HorizonStretch,em_VerticalCorrect,em_VerticalStretch );
//	PostEvent( UI_MOONTOOL_CAMERA_DISTORTPARAM_IND, (WPARAM)(&emMyOption), (LPARAM)&bSuccess );	
}


void CCamConfig::OnCamLightPensationInd(const CMessage& cMsg)
{
	/*if ( m_pTPMoonCamCfg == NULL )
	{
		SetCameraCfgPtr();
	}
	
	CTpMsg cTpMsg(&cMsg);
	m_pTPMoonCamCfg->bIsBLCSwitch = *(BOOL*)( cTpMsg.GetBody());
	BOOL bIsOk = *(BOOL*)( cTpMsg.GetBody() +sizeof(BOOL) +sizeof(u8) );
	PrtMsg( ev_TpCamBackLight_Ind, emEventTypemoontoolRecv, "bIsOpen:%d", m_pTPMoonCamCfg->bIsBLCSwitch );
	PostEvent( UI_MOONTOOL_CAMERA_BACKLIGHT_IND, (WPARAM)(m_pTPMoonCamCfg->bIsBLCSwitch), (LPARAM)bIsOk );*/
}

//降噪
u16 CCamConfig::CamNRCmd( BOOL bIsOpen, EmTPFpgaReduNoise emTPReduNoise )
{
	/*CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData(m_pSession->GetInst());
	pcTpMsg->SetBody(&bIsOpen, sizeof(BOOL));
	pcTpMsg->CatBody(&emTPReduNoise, sizeof(EmTPFpgaReduNoise));
	pcTpMsg->SetEvent(ev_TpCamReduNoise_Cmd);

	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_TpCamReduNoise_Cmd, emEventTypemoontoolSend, "bIsOpen:%d, emTPReduNoise:%d", bIsOpen, emTPReduNoise );
	return wRet;*/
	return true;
}

u16 CCamConfig::Cam2DNRCmd( BOOL bIsOpen, EmTPReduNoise emTPReduNoise )
{
	/*CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData(m_pSession->GetInst());
	pcTpMsg->SetBody(&bIsOpen, sizeof(BOOL));
	pcTpMsg->CatBody(&emTPReduNoise, sizeof(EmTPReduNoise));
	pcTpMsg->SetEvent(ev_TpSetCam2DNoiseLevle_Cmd);
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_TpSetCam2DNoiseLevle_Cmd, emEventTypemoontoolSend, "bIsOpen:%d, emTPReduNoise:%d", bIsOpen, emTPReduNoise );
	return wRet;*/
	return true;
}

u16 CCamConfig::Cam3DNRCmd( BOOL bIsOpen, EmTPReduNoise emTPReduNoise )
{
	/*CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData(m_pSession->GetInst());
	pcTpMsg->SetBody(&bIsOpen, sizeof(BOOL));
	pcTpMsg->CatBody(&emTPReduNoise, sizeof(EmTPReduNoise));
	pcTpMsg->SetEvent(ev_TpSetCam3DNoiseLevle_Cmd);
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_TpSetCam3DNoiseLevle_Cmd, emEventTypemoontoolSend, "bIsOpen:%d, emTPReduNoise:%d", bIsOpen, emTPReduNoise );
	return wRet;*/
	return true;
}

void CCamConfig::OnCamNRInd(const CMessage& cMsg)
{
	/*if ( m_pTPMoonCamCfg == NULL )
	{
		SetCameraCfgPtr();
	}

	CTpMsg cTpMsg(&cMsg);
	BOOL bIsOpen = *(BOOL*)( cTpMsg.GetBody());
	m_pTPMoonCamCfg->emReduNoise = *(EmTPFpgaReduNoise*)(cTpMsg.GetBody()+ sizeof(BOOL));

	PrtMsg( ev_TpCamReduNoise_Ind, emEventTypemoontoolRecv, "bIsOpen:%d emTPReduNoise:%d", bIsOpen, m_pTPMoonCamCfg->emReduNoise );
	PostEvent( UI_MOONTOOL_CAMERA_NR_IND, (WPARAM)(m_pTPMoonCamCfg->emReduNoise), (LPARAM)bIsOpen );*/
}

void CCamConfig::OnCam2DNRInd(const CMessage& cMsg)
{
	/*if ( m_pTPMoonCamCfg == NULL )
	{
		SetCameraCfgPtr();
	}
	
	CTpMsg cTpMsg(&cMsg);
	BOOL bIsOpen = *(BOOL*)( cTpMsg.GetBody());
	m_pTPMoonCamCfg->em2DNoiseLevle = *(EmTPReduNoise*)(cTpMsg.GetBody()+ sizeof(BOOL));
	
	PrtMsg( ev_TpSetCam2DNoiseLevle_Ind, emEventTypemoontoolRecv, "bIsOpen:%d emTPReduNoise:%d", bIsOpen, m_pTPMoonCamCfg->em2DNoiseLevle );
	PostEvent( UI_MOONTOOL_CAMERA_2DNR_IND, (WPARAM)(m_pTPMoonCamCfg->em2DNoiseLevle), (LPARAM)bIsOpen );*/
}

void CCamConfig::OnCam3DNRInd(const CMessage& cMsg)
{
	/*if ( m_pTPMoonCamCfg == NULL )
	{
		SetCameraCfgPtr();
	}
	
	CTpMsg cTpMsg(&cMsg);
	BOOL bIsOpen = *(BOOL*)( cTpMsg.GetBody());
	m_pTPMoonCamCfg->em3DNoiseLevle = *(EmTPReduNoise*)(cTpMsg.GetBody()+ sizeof(BOOL));
	
	PrtMsg( ev_TpSetCam3DNoiseLevle_Ind, emEventTypemoontoolRecv, "bIsOpen:%d emTPReduNoise:%d", bIsOpen, m_pTPMoonCamCfg->em3DNoiseLevle );
	PostEvent( UI_MOONTOOL_CAMERA_3DNR_IND, (WPARAM)(m_pTPMoonCamCfg->em3DNoiseLevle), (LPARAM)bIsOpen );*/
}

//预置位
u16 CCamConfig::CamOrderPosCheckCmd( BOOL bCheck )
{
	/*CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData(m_pSession->GetInst());
	pcTpMsg->SetBody(&bCheck, sizeof(BOOL));
	pcTpMsg->SetEvent(ev_TpCamInitPreset_Cmd);
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_TpCamInitPreset_Cmd, emEventTypemoontoolSend, "bCheck:%d", bCheck );
	return wRet;*/
	return true;
}

void CCamConfig::OnCamOrderPosSelInd( const CMessage& cMsg )
{
	/*if ( m_pTPMoonCamCfg == NULL )
	{
		SetCameraCfgPtr();
	}
	
	CTpMsg cTpMsg(&cMsg);
	m_pTPMoonCamCfg->bIsPreUsed = *(BOOL*)( cTpMsg.GetBody());
	BOOL bOk = *(BOOL*)(cTpMsg.GetBody()+ sizeof(BOOL));
	
	PrtMsg( ev_TpCamInitPreset_Ind, emEventTypemoontoolRecv, "bIsUsed:%d, bOk:%d", m_pTPMoonCamCfg->bIsPreUsed, bOk );
	PostEvent( UI_MOONTOOL_CAMERA_INITPRESET_IND, (WPARAM)(m_pTPMoonCamCfg->bIsPreUsed), (LPARAM)bOk );*/
}

//重启MOON
u16 CCamConfig::RebootMoon( )
{
	/*CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();  
    pcTpMsg->SetUserData( m_pSession->GetInst() );
	
    pcTpMsg->SetEvent( ev_tpMoonReboot_Cmd );
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_tpMoonReboot_Cmd, emEventTypemoontoolSend, "RebootMoon" );
	return wRet;*/
	return true;
}

u16 CCamConfig::MoonCamResetCmd(u8 byIndex)
{
	/*CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData(m_pSession->GetInst());
	pcTpMsg->SetBody( &byIndex, sizeof(u8) );
	
	pcTpMsg->SetEvent(ev_TpCamParamDefault_Cmd);
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_TpCamParamDefault_Cmd, emEventTypemoontoolSend, "MoonCamReset, byIndex: %d", byIndex );
	return wRet;*/
	return true;
}

void CCamConfig::OnCamPreSetNty( const CMessage& cMsg )
{
	/*CTpMsg cTpMsg(&cMsg);
	TTPPreParam tTpPreParam = *(TTPPreParam*)(cTpMsg.GetBody());
	memcpy( m_atTPCamPre, &tTpPreParam, sizeof(TTPCamPre)*MAX_CAMERA_Pre_NUM );

	PrtMsg( ev_TpCamPreSet_Nty, emEventTypemoontoolRecv, "TTPPreParam1: %d, TTPPreParam2: %d, TTPPreParam3: %d",
        m_atTPCamPre[0].achachDescription, m_atTPCamPre[1].achachDescription, m_atTPCamPre[2].achachDescription );

	PostEvent( UI_MOONTOOL_CAMPRESET_NTY );*/

}

TTPCamPre* CCamConfig::GetCamPreInfo()
{
    return m_atTPCamPre;
}

//保存预置位列表
u16 CCamConfig::CamPreSetSaveCmd( const TTPCamPre& tTPCamPre )
{
	/*CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData(m_pSession->GetInst());	
	pcTpMsg->SetBody(&tTPCamPre, sizeof(TTPCamPre));
	pcTpMsg->SetEvent(ev_TpCamPreSet_Cmd);
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_TpCamPreSet_Cmd, emEventTypemoontoolSend, "TTPCamPre:%d", tTPCamPre.byPre );
	return wRet;	*/
	return true;
}

void CCamConfig::OnCamPreSetInd( const CMessage& cMsg )
{
	/*CTpMsg cTpMsg(&cMsg);

	TTPCamPre tTPCamPre = *(TTPCamPre*)(cTpMsg.GetBody());
	BOOL bOk = *(BOOL*)(cTpMsg.GetBody()+sizeof(TTPCamPre));

	PrtMsg( ev_TpCamPreSet_Ind, emEventTypemoontoolRecv, "Index:%d, bOk:%d, achachDescription:%s", tTPCamPre.byPre, bOk, tTPCamPre.achachDescription );	

	PostEvent( UI_MOONTOOL_PRESET_IND, (WPARAM)&tTPCamPre, (LPARAM)bOk );*/
}

u16 CCamConfig::OrderPosDeleteReq( const TTPCamPre& tTPCamPre )
{
	/*CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData(m_pSession->GetInst());	
	pcTpMsg->SetBody(&tTPCamPre, sizeof(TTPCamPre));
	pcTpMsg->SetEvent(ev_TpCamPreReset_Cmd);
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_TpCamPreReset_Cmd, emEventTypemoontoolSend, "TTPCamPre:%d", tTPCamPre.byPre );
	return wRet;*/	
	return true;
}

void CCamConfig::OnCamPreResetInd( const CMessage& cMsg )
{
	/*CTpMsg cTpMsg(&cMsg);

	TTPCamPre tTPCamPre = *(TTPCamPre*)(cTpMsg.GetBody());
	BOOL bOk = *(BOOL*)(cTpMsg.GetBody()+sizeof(TTPCamPre));

	PrtMsg( ev_TpCamPreReset_Ind, emEventTypemoontoolRecv, "Index:%d, bOk:%d, achachDescription:%s", tTPCamPre.byPre, bOk, tTPCamPre.achachDescription  );

	PostEvent( UI_MOONTOOL_PREDEL_IND, (WPARAM)&tTPCamPre, (LPARAM)bOk );*/

}

u16 CCamConfig::OrderPosInvokeCmd( const TTPCamPre& tTPCamPre )
{
	/*CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData(m_pSession->GetInst());	
	pcTpMsg->SetBody(&tTPCamPre, sizeof(TTPCamPre));
	pcTpMsg->SetEvent(ev_TpCamPreRecall_Cmd);
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_TpCamPreRecall_Cmd, emEventTypemoontoolSend, "TTPCamPre:%d", tTPCamPre );
	return wRet;	*/
	return true;
}

void CCamConfig::OnCamPreRecallInd( const CMessage& cMsg )
{
	/*CTpMsg cTpMsg(&cMsg);
	
	TTPCamPre tTPCamPre = *(TTPCamPre*)(cTpMsg.GetBody());
	BOOL bOk = *(BOOL*)(cTpMsg.GetBody()+sizeof(TTPCamPre));
	
	PrtMsg( ev_TpCamPreRecall_Ind, emEventTypemoontoolRecv, "Index:%d, bOk:%d, achachDescription:%s",
		tTPCamPre.byPre, bOk, tTPCamPre.achachDescription  );	*/
}

u16 CCamConfig::CamPreSetModifyCmd( const TTPCamPre& tTPCamPre )
{
	/*CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData(m_pSession->GetInst());	
	pcTpMsg->SetBody(&tTPCamPre, sizeof(TTPCamPre));
	pcTpMsg->SetEvent(ev_TpCamPreModify_Cmd);
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_TpCamPreModify_Cmd, emEventTypemoontoolSend, "TTPCamPre:%d", tTPCamPre );
	return wRet;*/	
	return true;
}

void CCamConfig::OnCamPreSetModifyInd( const CMessage& cMsg )
{
	/*CTpMsg cTpMsg(&cMsg);
	
	TTPCamPre tTPCamPre = *(TTPCamPre*)(cTpMsg.GetBody());
	BOOL bOk = *(BOOL*)(cTpMsg.GetBody()+sizeof(TTPCamPre));
	
	PrtMsg( ev_TpCamPreModify_Ind, emEventTypemoontoolRecv, "Index:%d, bOk:%d, achachDescription:%s", tTPCamPre.byPre, bOk, tTPCamPre.achachDescription  );	

	PostEvent( UI_MOONTOOL_PREMODIFY_IND, (WPARAM)&tTPCamPre, (LPARAM)bOk );*/
}



void CCamConfig::OnCamParamDefaultInd( const CMessage& cMsg )
{
	/*CTpMsg cTpMsg(&cMsg);
	
	TTPMoonCamInfo tTPMoonCamInfo = *(TTPMoonCamInfo*)(cTpMsg.GetBody());

	switch( tTPMoonCamInfo.byIndex )
	{
	case 0:
		{
			m_tCnCameraCfg1 = tTPMoonCamInfo;
			break;
		}
	case 1:
		{
			m_tCnCameraCfg2 = tTPMoonCamInfo;
			break;
		}
	case 2:
		{
			m_tCnCameraCfg3 = tTPMoonCamInfo;
			break;
		}
	default:
		break;
	}

	BOOL bIsOk = *(BOOL*)( cTpMsg.GetBody()+ sizeof(TTPMoonCamInfo) );

	PrtMsg( ev_TpCamParamDefault_Ind, emEventTypemoontoolRecv, " bOk:%d ", bIsOk );	

	PostEvent( UI_MOONTOOL_CAMPARAMDEFAULT_IND, (WPARAM)&tTPMoonCamInfo, (LPARAM)bIsOk );*/
}



u16 CCamConfig::CamParamUploadCmd()
{
	/*CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData(m_pSession->GetInst());
	
	pcTpMsg->SetEvent(ev_TpCamParamUpload_Cmd);
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_TpCamParamUpload_Cmd, emEventTypemoontoolSend, "");
	return wRet;	*/
	return true;
}

u16 CCamConfig::UpgradeMoon( const s8* chVerFileInfo )
{
	/*CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData(m_pSession->GetInst());	
	pcTpMsg->SetBody(chVerFileInfo, TP_MAX_FILENAME_LEN+1);
	pcTpMsg->SetEvent(ev_TpMoonUpgrade_Cmd);
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_TpMoonUpgrade_Cmd, emEventTypemoontoolSend, "chVerFileInfo:%s", chVerFileInfo );
	return wRet;*/
	return true;
}

u16 CCamConfig::UpdateMoonMechanism(const s8* chVerFileInfo)
{
	/*CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData(m_pSession->GetInst());	
	pcTpMsg->SetBody(chVerFileInfo, TP_MAX_FILENAME_LEN+1);
	pcTpMsg->SetEvent(ev_CamUpgrade_Cmd);
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_CamUpgrade_Cmd, emEventTypemoontoolSend, "chVerFileInfo:%s", chVerFileInfo );
	return wRet;*/
	return true;
}

u16 CCamConfig::CamParamUploadNty(BOOL bSuccess)
{
	/*CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData(m_pSession->GetInst());
	pcTpMsg->SetBody(&bSuccess, sizeof(BOOL));
	pcTpMsg->SetEvent(ev_TpCamParamUpload_Nty);
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_TpCamParamUpload_Nty, emEventTypemoontoolSend, "bSuccess:%d", bSuccess );
	return wRet;*/
	return true;
}

void CCamConfig::OnMoonUpgradeInd( const CMessage& cMsg )
{
	/*CTpMsg cTpMsg(&cMsg);
	
	BOOL bOk = *(BOOL*)(cTpMsg.GetBody());
	
	PrtMsg( ev_TpMoonUpgrade_Ind, emEventTypemoontoolRecv, "bOk:%d",  bOk );
	
	PostEvent( UI_MOONTOOL_UPGRADE_IND, NULL, (LPARAM)bOk );*/
}

void CCamConfig::OnUpdateMechanismInd(const CMessage& cMsg)
{
	/*CTpMsg cTpMsg(&cMsg);
	
	BOOL bOk = *(BOOL*)(cTpMsg.GetBody());
	
	PrtMsg( ev_CamUpgrade_Ind, emEventTypemoontoolRecv, "bOk:%d",  bOk );
	
	PostEvent( UI_CAMMECHANISM_UPGRADE_IND, NULL, (LPARAM)bOk );*/
}

u16 CCamConfig::SetReferenceLineCmd( BOOL bOpen )
{
	/*u8 byCount = 3;
	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData(m_pSession->GetInst());
	pcTpMsg->SetBody(&bOpen, sizeof(BOOL));
	pcTpMsg->CatBody(&byCount,sizeof(u8));
	pcTpMsg->SetEvent(ev_TpSetRefer_Cmd );
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_TpSetRefer_Cmd, emEventTypemoontoolSend, "Reference Line Open :%d ", bOpen );
	return wRet;*/
	return true;
}

void CCamConfig::OnReferenceLineInd( const CMessage& cMsg )
{
	/*CTpMsg cTpMsg(&cMsg);
	
	BOOL bOpen = *(BOOL*)(cTpMsg.GetBody());
	BOOL bSuccess = *(BOOL*)(cTpMsg.GetBody()+sizeof(BOOL));
	PrtMsg( ev_TpSetRefer_Ind, emEventTypemoontoolRecv, "Reference line open:%d  success :%d",  bOpen,bSuccess );
	
	PostEvent( UI_MoonTool_ReferenceLine_IND, (WPARAM)&bOpen,(LPARAM)&bSuccess);*/
}

void CCamConfig::OnReferenceLineNty( const CMessage& cMsg )
{
	/*CTpMsg cTpMsg(&cMsg);
	
	BOOL bOpen = *(BOOL*)(cTpMsg.GetBody());
	BOOL bSuccess = TRUE;
	PrtMsg( ev_TpSetRefer_Nty, emEventTypemoontoolRecv, "Reference line open:%d ",  bOpen );
	
	PostEvent( UI_MoonTool_ReferenceLine_IND, (WPARAM)&bOpen,(LPARAM)&bSuccess);*/
}

u16 CCamConfig::SetHorizontalFlipCmd( BOOL bOpen )
{
	/*CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData(m_pSession->GetInst());	
	pcTpMsg->SetBody(&bOpen, sizeof(BOOL));
	pcTpMsg->SetEvent(ev_TpFlatTurn_Cmd );
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_TpFlatTurn_Cmd, emEventTypemoontoolSend, "Horizontal Flip Line Open :%d ", bOpen );
	return wRet;*/
	return true;
}

void CCamConfig::OnHorizontalFlipInd( const CMessage& cMsg )
{
	/*CTpMsg cTpMsg(&cMsg);
	
	BOOL bOpen = *(BOOL*)(cTpMsg.GetBody());
	BOOL bSuccess = *(BOOL*)(cTpMsg.GetBody()+sizeof(BOOL));
	PrtMsg( ev_TpFlatTurn_Ind, emEventTypemoontoolRecv, "Reference line open:%d  success :%d",  bOpen,bSuccess );
	
	PostEvent( UI_MoonTool_HorizontalFlip_IND, (WPARAM)&bOpen,(LPARAM)&bSuccess);*/
}

void CCamConfig::OnHorizontalFlipNty( const CMessage& cMsg )
{
	/*CTpMsg cTpMsg(&cMsg);
	
	BOOL bOpen = *(BOOL*)(cTpMsg.GetBody());
	BOOL bSuccess = TRUE;
	PrtMsg( ev_TpFlatTurn_Nty, emEventTypemoontoolRecv, "Reference line open:%d ",  bOpen );
	
	PostEvent( UI_MoonTool_HorizontalFlip_IND, (WPARAM)&bOpen,(LPARAM)&bSuccess);*/
}

u16 CCamConfig::SetTrapezoidalCorCmd( BOOL bOpen )
{
	/*CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData(m_pSession->GetInst());	
	pcTpMsg->SetBody(&bOpen, sizeof(BOOL));
	pcTpMsg->SetEvent(ev_TpDisortSwitch_Cmd );
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_TpDisortSwitch_Cmd, emEventTypemoontoolSend, "Trapezoidal Correction Open :%d ", bOpen );
	return wRet;*/
	return true;
}

u16 CCamConfig::SetShowRectRegionCmd(BOOL bOpen)
{
	/*CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData(m_pSession->GetInst());	
	pcTpMsg->SetBody(&bOpen, sizeof(BOOL));
	pcTpMsg->SetEvent( ev_TPMoonShowRectRegion_Cmd );

	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_TPMoonShowRectRegion_Cmd, emEventTypemoontoolSend, " ShowRectRegion Open :%d ", bOpen );
	return wRet;*/
	return true;
}

u16 CCamConfig::SetRgbConsistSwitchCmd(BOOL bOpen)
{
	/*CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData(m_pSession->GetInst());	
	pcTpMsg->SetBody(&bOpen, sizeof(BOOL));
	pcTpMsg->SetEvent( ev_TpColorSwich_Cmd );
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_TpColorSwich_Cmd, emEventTypemoontoolSend, " ShowRgbConsistSwitch Open :%d ", bOpen );

	return wRet;*/
	return true;
}

void CCamConfig::OnTrapezoidalCorInd( const CMessage& cMsg )
{
	/*CTpMsg cTpMsg(&cMsg);

	BOOL bOpen = *(BOOL*)(cTpMsg.GetBody());
	BOOL bSuccess = *(BOOL*)(cTpMsg.GetBody()+sizeof(BOOL));
	PrtMsg( ev_TpDisortSwitch_Ind, emEventTypemoontoolRecv, "Trapezoidal Correction open:%d  success :%d",  bOpen,bSuccess );
	
	if ( bSuccess == TRUE )
	{
		if ( m_pTPMoonCamCfg == NULL )
		{
			SetCameraCfgPtr();
		}
		m_pTPMoonCamCfg->bIsCorrect = bOpen;
	}

	PostEvent( UI_MoonTool_TrapezoidalCor_IND, (WPARAM)&bOpen,(LPARAM)&bSuccess);*/
}

void CCamConfig::OnShowRectRegionInd(const CMessage& cMsg)
{
	/*CTpMsg cTpMsg(&cMsg);
	
	BOOL bOpen = *(BOOL*)(cTpMsg.GetBody());
	BOOL bSuccess = *(BOOL*)(cTpMsg.GetBody()+sizeof(BOOL));
	PrtMsg( ev_TPMoonShowRectRegion_Ind, emEventTypemoontoolRecv, "ShowRectRegion open:%d  success :%d",  bOpen, bSuccess );

	PostEvent( UI_MoonTool_ShowRectRegion_IND, (WPARAM)&bOpen,(LPARAM)&bSuccess );*/
}

void CCamConfig::OnColorSwitchInd(const CMessage& cMsg)
{
	/*CTpMsg cTpMsg(&cMsg);
	
	BOOL bOpen = *(BOOL*)(cTpMsg.GetBody());
	BOOL bSuccess = *(BOOL*)(cTpMsg.GetBody()+sizeof(BOOL));
	PrtMsg( ev_TpColorSwich_Ind, emEventTypemoontoolRecv, "ColorSwitch open:%d  success :%d",  bOpen, bSuccess );
	
	PostEvent( UI_MoonTool_ColorSwitch_IND, (WPARAM)&bOpen,(LPARAM)&bSuccess );*/
}

u16 CCamConfig::SetTraCorParamCmd( EmTPCorrect emMyCorOption,EmTPCorrectChange emChangeOption )
{
	/*CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData(m_pSession->GetInst());	
	pcTpMsg->SetBody(&emMyCorOption, sizeof(EmTPCorrect));
	pcTpMsg->CatBody(&emChangeOption, sizeof(EmTPCorrectChange));
	pcTpMsg->SetEvent( ev_TpSetDisort_Cmd );
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_TpSetDisort_Cmd, emEventTypemoontoolSend, "My Trapezoidal Correction Option :%d <em_HorizonCorrect %d ; \
		em_HorizonStretch %d ; em_VerticalCorrect %d ; em_VerticalStretch %d > ; Increase or decrease %d <emCorrectEnlarge %d ; emCorrectReduce %d >", 
		emMyCorOption,em_HorizonCorrect, em_HorizonStretch,em_VerticalCorrect,em_VerticalStretch,emChangeOption,emCorrectEnlarge,emCorrectReduce);
	return wRet;*/
	return true;
}

void CCamConfig::OnTraCorParamInd( const CMessage& cMsg )
{
	/*CTpMsg cTpMsg(&cMsg);
	
	u32 dwValue = *(u32*)(cTpMsg.GetBody());
	EmTPCorrect emMyOption = *(EmTPCorrect*)(cTpMsg.GetBody()+sizeof(u32));

	if ( m_pTPMoonCamCfg == NULL )
	{
		SetCameraCfgPtr();
	}

	if ( emMyOption == em_HorizonCorrect)
	{
		m_pTPMoonCamCfg->dwHorizonCorrect = dwValue;
	}
	else if ( emMyOption == em_HorizonStretch )
	{
		m_pTPMoonCamCfg->dwHorizonStretch = dwValue;
	}
	else if ( emMyOption == em_VerticalCorrect)
	{
		m_pTPMoonCamCfg->dwVerticalCorrect = dwValue;
	}
	else
	{
		m_pTPMoonCamCfg->dwVerticalStretch = dwValue;
	}

	PrtMsg( ev_TpSetDisort_Ind, emEventTypemoontoolRecv, "My Trapezoidal Correction Option :%d <em_HorizonCorrect %d ; \
		em_HorizonStretch %d ; em_VerticalCorrect %d ; em_VerticalStretch %d > ; Value %lu ", emMyOption
		,em_HorizonCorrect, em_HorizonStretch,em_VerticalCorrect,em_VerticalStretch, dwValue );
	
	PostEvent( UI_MoonTool_TraCorValue_IND, (WPARAM)&emMyOption ,NULL);*/
}

u16 CCamConfig::SnapShotCmd( )
{
	/*TTPSnapshotInfo tSnapShotInfo;
	tSnapShotInfo.byIndex = 3;
	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData(m_pSession->GetInst());
	pcTpMsg->SetBody(&tSnapShotInfo,sizeof(TTPSnapshotInfo));
	pcTpMsg->SetEvent( ev_TpCamSnapshot_Cmd );
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_TpCamSnapshot_Cmd, emEventTypemoontoolRecv ,"ev_TpCamSnapshot_Cmd");
	
	return wRet;*/
	return true;
}

void CCamConfig::SnapShotInd( const CMessage& cMsg )
{
	/*CTpMsg cTpMsg(&cMsg);
	
	BOOL bSuccess = *(BOOL*)(cTpMsg.GetBody()+sizeof(TTPSnapshotInfo));

	TTPSnapshotInfo tSnapShotInfo = *(TTPSnapshotInfo*)( cTpMsg.GetBody());
	if ( tSnapShotInfo.byIndex == 3 )
	{
		PrtMsg( ev_TpCamSnapshot_Ind, emEventTypemoontoolRecv, "Success:%d",bSuccess );
	}
	else
	{
		PrtMsg( ev_TpCamSnapshot_Ind, emEventTypemoontoolRecv, "Success:%d,Index %d ,name %s",bSuccess,tSnapShotInfo.byIndex,tSnapShotInfo.achFileNme);
	}

	PostEvent( UI_MoonTool_SnapShot_IND, (WPARAM)&bSuccess,(LPARAM)&tSnapShotInfo);*/
}

void CCamConfig::OnDirectSetDistortInd(const CMessage& cMsg)
{
	/*CTpMsg cTpMsg(&cMsg);
	TTPDistortInfo tTPDistortInfo = *(TTPDistortInfo*)(cTpMsg.GetBody());
	BOOL bOk = *(BOOL*)( cTpMsg.GetBody() + sizeof(TTPDistortInfo) );
    
	PrtMsg( ev_TPDirectSetDistor_Ind, emEventTypemoontoolRecv, "byIndex: %d, emDistortType: %d, dwValue: %d", tTPDistortInfo.byIndex, tTPDistortInfo.emDistortType, tTPDistortInfo.dwValue );

	PostEvent( UI_DIRECTSETDISTORT_IND, (WPARAM)&tTPDistortInfo, (LPARAM)&bOk );*/
}

void CCamConfig::OnSecDefaultNty(const CMessage& cMsg)
{
	/*CTpMsg cTpMsg(&cMsg);
	TTPSecBoundaryInfo tTPSecBoundaryInfo = *(TTPSecBoundaryInfo*)(cTpMsg.GetBody());
	BOOL bOk = *(BOOL*)(cTpMsg.GetBody() + sizeof(TTPSecBoundaryInfo));

	PrtMsg( ev_TpSecDefault_Nty, emEventTypemoontoolRecv, "");

	PostEvent( UI_MoonSecDefault_Nty, (WPARAM)&tTPSecBoundaryInfo, (LPARAM)&bOk );*/
}

void CCamConfig::OnSecBoundaryNty(const CMessage& cMsg)
{
	/*CTpMsg cTpMsg(&cMsg);
	
	TTPSecBoundaryInfo tTPSecBoundaryInfo = *(TTPSecBoundaryInfo*)(cTpMsg.GetBody());
	PrtMsg( ev_TpSecBoundary_Nty, emEventTypemoontoolRecv,"");
	PostEvent( UI_SecBoundary_Nty, (WPARAM)&tTPSecBoundaryInfo, NULL );*/
}

void CCamConfig::OnChangeDistortInd(const CMessage& cMsg)
{
	/*CTpMsg cTpMsg(&cMsg);
	TTPDistortInfo tTPDistortInfo = *(TTPDistortInfo*)(cTpMsg.GetBody());
	BOOL bOk = *(BOOL*)( cTpMsg.GetBody() + sizeof(TTPDistortInfo) );
    
	PrtMsg( ev_TPChangeDistor_Ind, emEventTypemoontoolRecv, "byIndex: %d, emDistortType: %d, dwValue: %d", tTPDistortInfo.byIndex, tTPDistortInfo.emDistortType, tTPDistortInfo.dwValue );

	PostEvent(UI_CHANGEDISTORT_IND, (WPARAM)&tTPDistortInfo, (LPARAM)&bOk );*/	
}

u16 CCamConfig::GammaStyleSelCmd( const EmH650Gamma& enH650Gamma)
{
	/*CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData(m_pSession->GetInst());
	pcTpMsg->SetBody( &enH650Gamma, sizeof( EmH650Gamma) );
	pcTpMsg->SetEvent( ev_TpCamSetGamma_Cmd );
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_TpCamSetGamma_Cmd, emEventTypemoontoolSend, "emH650Gamma:%d", enH650Gamma ); 

	return wRet;*/
	return true;
}

void CCamConfig::OnGammaSelInd(const CMessage& cMsg)
{
	/*CTpMsg cTpMsg(&cMsg);
	
	EmH650Gamma emH650Gamma;
	emH650Gamma = *(EmH650Gamma*)( cTpMsg.GetBody() );
	BOOL bSelGamma = *(BOOL*)( cTpMsg.GetBody() + sizeof(EmH650Gamma) + sizeof(u8) );

	m_pTPMoonCamCfg->emGamma = emH650Gamma;

	if ( m_pTPMoonCamCfg == NULL )
	{
		SetCameraCfgPtr();		
	}
	
	PrtMsg( ev_TpCamSetGamma_Ind, emEventTypemoontoolRecv, "emGammaSel:%d", emH650Gamma );
	PostEvent( UI_MOONTOOL_GammaStyleSel_IND, NULL, (LPARAM)bSelGamma );*/
}

void CCamConfig::OnMechanismSelectNty(const CMessage& cMsg)
{
	/*CTpMsg cTpMsg(&cMsg);
	
	EmTPMechanism emTPMechanism= *(EmTPMechanism*)( cTpMsg.GetBody() );

	PrtMsg( ev_TpMechanismSelect_Nty, emEventTypemoontoolRecv, "emTPMechanism:%d", emTPMechanism);
	PostEvent( UI_TpMechanismSelect_NTY, NULL, (LPARAM)emTPMechanism);*/
}

void CCamConfig::OnTpMechverNty(const CMessage& cMsg)
{
	/*CTpMsg cTpMsg(&cMsg);

	TTPMechVer tTpMechver;
	
	tTpMechver.byIndex = *(u8*)( cTpMsg.GetBody() );
	s8 *achHardwaerVer = (s8*)( cTpMsg.GetBody() + sizeof(u8) );
	s8 *achSoftWareVer = (s8*)( cTpMsg.GetBody() + sizeof(u8) + sizeof(s8)*MOON_MAX_DEVICEVER_LEN  ); 

	memcpy( tTpMechver.achMechHWVer, achHardwaerVer, MOON_MAX_DEVICEVER_LEN );
	memcpy( tTpMechver.achMechSWVer, achSoftWareVer, MOON_MAX_DEVICEVER_LEN );
	
	PrtMsg( ev_TpMechVer_Nty, emEventTypemoontoolRecv, "byIndex:%d, achHardwaerVer:%s, achSoftWareVer:%s", m_byCameraSel, tTpMechver.achMechHWVer, tTpMechver.achMechSWVer);
	PostEvent( UI_TpMechVer_NTY, (WPARAM)&tTpMechver, NULL );*/
}

void CCamConfig::OnDelayCorrectInd( const CMessage& cMsg )
{
	/*CTpMsg cTpMsg(&cMsg);
	
	u8 nPosition = *(u8*)(cTpMsg.GetBody());
	u32 dwDelayCorrectVal = *(u32*)(cTpMsg.GetBody()+sizeof(u8));
	BOOL bSuccess = *(BOOL *)(cTpMsg.GetBody()+sizeof(u8)+sizeof(u32));
	
	TTPFpgaDelay tTPDelayInfo;
	tTPDelayInfo.byIndex = nPosition;
	tTPDelayInfo.dwDelay = dwDelayCorrectVal;
	
	PrtMsg( ev_TpFpgaDelayCorrect_Ind, emEventTypemoontoolRecv, "nPosition: %d, dwDelayCorrectVal: %d, bSuccess: %d",
		nPosition, dwDelayCorrectVal, bSuccess);
	
	PostEvent(UI_SETDELAYCORRECT_IND, (WPARAM)&tTPDelayInfo, (LPARAM)&bSuccess);*/
}

void CCamConfig::OnDelayCorrectNty( const CMessage& cMsg )
{
	/*CTpMsg cTpMsg(&cMsg);
	
	u8 nPosition = *(u8*)(cTpMsg.GetBody());
	u32 dwDelayCorrectVal = *(u32*)(cTpMsg.GetBody()+sizeof(u8));
	
	TTPFpgaDelay tTPDelayInfo;
	tTPDelayInfo.byIndex = nPosition;
	tTPDelayInfo.dwDelay = dwDelayCorrectVal;
	
	PrtMsg( ev_TpFpgaDelayCorrect_Nty, emEventTypemoontoolRecv, "nPosition: %d, dwDelayCorrectVal: %d",
		nPosition, dwDelayCorrectVal);
	
	PostEvent(UI_SETDELAYCORRECT_NTY, (WPARAM)&tTPDelayInfo, NULL);*/
}

u16 CCamConfig::SetDelayCorrectCmd( u8 nPosition, u32 dwDelay )
{
	/*CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData(m_pSession->GetInst());

	pcTpMsg->SetBody(&nPosition, sizeof(u8));
	pcTpMsg->CatBody(&dwDelay, sizeof(u32));
	pcTpMsg->SetEvent( ev_TpFpgaDelayCorrect_Cmd );
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_TpFpgaDelayCorrect_Cmd, emEventTypemoontoolSend, "nPosition: %d, dwDelay: %d", nPosition, dwDelay);
	
	return wRet;*/
	return true;
}