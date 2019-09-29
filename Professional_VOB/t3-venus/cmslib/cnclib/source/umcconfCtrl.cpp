// confCtrl.cpp: implementation of the CConfCtrl class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "umcconfCtrl.h"
#include "cmsConst.h"
#include "eventoutcnssipdual.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
 
CUmcConfCtrl::CUmcConfCtrl(CCnsSession &cUmsSession)
          :CUmcConfCtrlIF(),
		  m_pCncSession(NULL),
		  m_tConfInfo()
{
	m_pCncSession = &cUmsSession;
	BuildEventsMap();
}
 
void CUmcConfCtrl::BuildEventsMap()
{
	REG_PFUN( ev_CnConfState_Nty, OnConfStateNty );

    REG_PFUN( ev_CnConfEpList_Nty, OnUpdateConfCnsListNotify ); 
    REG_PFUN( ev_TppConfAMixUpdate_Nty, OnUpdateConfAuxMixlistNotify ); 
    REG_PFUN( ev_TppConfAMixUpdate_Ind, OnUpdateConfAuxMixlistInd ); 

	REG_PFUN( ev_TppAudMixDisListOpr_Ind, OnAudMixDisListOprNotify );

    REG_PFUN( ev_TppInviteCnsByAlias_Ind, OnInviteCnsRsp );
    REG_PFUN( ev_TppInviteCnsByEpId_Ind, OnCallConfCnsRsp ); 

    REG_PFUN( ev_TppHangupCns_Ind, OnHangupCnsInd );
    //	REG_PFUN(evtp_HungUpConf_result, OnHungUpConfRsp ); 
    // 	REG_PFUN(evtp_UpdateConfTurnlist_Notify, OnUpdateConfPolllistNotify ); 

    REG_PFUN(ev_TppConfMute_Ind, OnSetMuteCnsRsp ); 
    REG_PFUN(ev_TppConfQuiet_Ind, OnSetSilenceCnsRsp ); 
    
    REG_PFUN(ev_TppConfStartDual_Ind, OnSetDualCnsRsp ); 
    REG_PFUN(ev_TppConfStopDual_Ind, OnSetDualCnsRsp ); 

    REG_PFUN( ev_TppConfDualEp_Nty, OnDualCnsNotify );  

    REG_PFUN(ev_TppConfApplySpeaker_Nty, OnUpdateConfSpeakerNotify ); 
    
    REG_PFUN(ev_TppConfApplySpeaker_Ind, OnSetSpokeCnsRsp ); 
    
    REG_PFUN(ev_TppChairConfInfo_Nty, OnChairCnsNotify ); 

    REG_PFUN( ev_TppModuleterminalLeftConf, OnCnsLeaveNotify ); 

    REG_PFUN( ev_TppUmsCommonReasonToUI_Ind, OnUmsCommonReasonInd );

    //���������Դ
    REG_PFUN(OSP_DISCONNECT, OnLinkBreak); 
		
}







void CUmcConfCtrl::OnLinkBreak( const CMessage& cMsg )
{
    m_tConfInfo.Clear();
    m_tConfInfo.m_wConfID = INVALID_WORD;
   
    PrtMsg( OSP_DISCONNECT, emEventTypeCnsRecv,"[CUmcConfCtrl::OnLinkBreak]��ջ�����Ϣ" );
}

 
 

u16 CUmcConfCtrl::GetConf( TCMSConf &tplConfList )  const
{      
    tplConfList = m_tConfInfo; 

	return NO_ERROR;
} 


u16 CUmcConfCtrl::GetConfCnsList(  TplArray<TCnsInfo> &tplConfCnsList )  const
{
	 
   tplConfCnsList = m_tConfInfo.m_tplCnsList;
   return NO_ERROR;	
}


u16 CUmcConfCtrl::GetConfAudmixList(  TAuxMixList&tConfAudmixList )  const
{
	 
	tConfAudmixList = m_tConfInfo.m_tAudmixList;
   return NO_ERROR;	
}


u16 CUmcConfCtrl::GetConfPollList(   TplArray<u16> &tplConfPollList )  const
{ 
	
	tplConfPollList = m_tConfInfo.m_tplPollList ;
    return NO_ERROR;	
}

 

u16 CUmcConfCtrl::InviteCnsReq( const TConfCallEpAddr &tEp )  
{
	if ( NULL == m_pCncSession ) 
	{
		return ERR_CMS;
	}

    CTpMsg *pcTpMsg = m_pCncSession->GetKdvMsgPtr();
    pcTpMsg->SetUserData( m_pCncSession->GetInst() );
    pcTpMsg->SetEvent( ev_TppInviteCnsByAlias_Cmd );
    pcTpMsg->SetBody( &tEp.m_tAlias, sizeof(TTPAlias) );

    u16 wRet = m_pCncSession->PostMsg(TYPE_TPMSG); 
	
	PrtMsg( ev_TppInviteCnsByAlias_Cmd,emEventTypeCnsSend,"confID=%d, callType=%d(tp_Alias_Unknow,tp_Alias_e164,tp_Alias_h323,tp_Alias_IP), EPAlias=%s ",
		tEp.m_wConfID, tEp.m_tAlias.m_byType, tEp.m_tAlias.m_abyAlias );

	return  wRet;
}


u16 CUmcConfCtrl::CallConfCnsReq( const TConfEpID &tEp )
{
    if ( NULL == m_pCncSession ) 
    {
        return ERR_CMS;
    }
    
    CTpMsg *pcTpMsg = m_pCncSession->GetKdvMsgPtr();
    pcTpMsg->SetUserData( m_pCncSession->GetInst() );
    pcTpMsg->SetEvent( ev_TppInviteCnsByEpId_Cmd );
    pcTpMsg->SetBody( &tEp.m_wEpID, sizeof(u16) );
    
    u16 wRet = m_pCncSession->PostMsg(TYPE_TPMSG); 
    
    PrtMsg( ev_TppInviteCnsByEpId_Cmd, emEventTypeCnsSend, "confID=%d, CnsID=%d", tEp.m_wConfID,tEp.m_wEpID );
    
	return 0 ;//wRe;
}


u16 CUmcConfCtrl::HangupConfReq(  )
{
	if ( NULL == m_pCncSession ) 
	{
		return ERR_CMS;
	}
	
    
    CTpMsg *pcTpMsg = m_pCncSession->GetKdvMsgPtr();
    pcTpMsg->SetUserData( m_pCncSession->GetInst() );
    pcTpMsg->SetEvent( ev_TppHangupConf_Cmd ); 
    
    u16 wRet = m_pCncSession->PostMsg(TYPE_TPMSG); 
    
   	PrtMsg( ev_TppHangupConf_Cmd, emEventTypeCnsSend," " );
 

	return  wRet;
}


u16 CUmcConfCtrl::HangupCNSReq( const TConfEpID &tConfEpInfo )
{
	if ( NULL == m_pCncSession ) 
	{
		return ERR_CMS;
	}
	
    CTpMsg *pcTpMsg = m_pCncSession->GetKdvMsgPtr();
    pcTpMsg->SetUserData( m_pCncSession->GetInst() );
    pcTpMsg->SetEvent( ev_TppHangupCns_Cmd ); 
    pcTpMsg->SetBody( &tConfEpInfo.m_wEpID, sizeof(u16) );
    
    u16 wRet = m_pCncSession->PostMsg(TYPE_TPMSG); 
    
   	PrtMsg( ev_TppHangupCns_Cmd, emEventTypeCnsSend,"CnsID = %d",tConfEpInfo.m_wEpID );
	
	return  wRet;
}


u16 CUmcConfCtrl::RemoveCNSReq( const TConfEpID &tConfEpInfo )
{
	if ( NULL == m_pCncSession ) 
	{
		return ERR_CMS;
	}
	
	
	return 0; 
}


u16 CUmcConfCtrl::SetSpokeCnsReq( const TConfEpID &tConfEpInfo )  
{
	if ( NULL == m_pCncSession ) 
	{
		return ERR_CMS;
	}
	
	CTpMsg *pMsg = m_pCncSession->GetKdvMsgPtr();
    pMsg->SetUserData( m_pCncSession->GetInst() );
	pMsg->SetEvent( ev_TppConfApplySpeaker_Cmd );
	pMsg->SetBody(&tConfEpInfo,sizeof(tConfEpInfo));

	u16 awEvent[1];
    awEvent[0] = ev_TppConfApplySpeaker_Ind;   

	u16 wRe = m_pCncSession->PostCommand( this,awEvent,1,TYPE_TPMSG );
 
	
	PrtMsg( ev_TppConfApplySpeaker_Cmd, emEventTypeCnsSend, "confID=%d, CNSID=%d", tConfEpInfo.m_wConfID,tConfEpInfo.m_wEpID );
	
    return wRe;
    
}



u16 CUmcConfCtrl::SetQuietCnsReq( const TConfEpID &tConfEpInfo, BOOL32 bQuiet)
{
    if ( NULL == m_pCncSession ) 
    {
        return ERR_CMS;
    }
    
    CTpMsg *pMsg = m_pCncSession->GetKdvMsgPtr();
    pMsg->SetUserData( m_pCncSession->GetInst() );
    pMsg->SetEvent( ev_TppConfQuiet_Cmd );
    pMsg->SetBody( &tConfEpInfo,sizeof(TConfEpID) );
    pMsg->CatBody(&bQuiet,sizeof(BOOL32));
    
    u16 wRe = m_pCncSession->PostMsg(TYPE_TPMSG ); 
    
    PrtMsg( ev_TppConfQuiet_Cmd, emEventTypeCnsSend, "confID=%d , cnsID=%d,isStart=%d", 
        tConfEpInfo.m_wConfID,tConfEpInfo.m_wEpID,bQuiet); 
	return wRe; 
}


u16 CUmcConfCtrl::SetMuteCnsReq( const TConfEpID &tConfEpInfo , BOOL32 bMute)
{
    if ( NULL == m_pCncSession ) 
    {
        return ERR_CMS;
    }
    
    CTpMsg *pMsg = m_pCncSession->GetKdvMsgPtr();
    pMsg->SetUserData( m_pCncSession->GetInst() );
    pMsg->SetEvent( ev_TppConfMute_Cmd );
    pMsg->SetBody( &tConfEpInfo,sizeof(TConfEpID) );
    pMsg->CatBody(&bMute,sizeof(BOOL32));
    
    u16 wRe = m_pCncSession->PostMsg(TYPE_TPMSG ); 
    
    PrtMsg( ev_TppConfMute_Cmd, emEventTypeCnsSend, "confID=%d , cnsID=%d,isStart=%d", 
        tConfEpInfo.m_wConfID,tConfEpInfo.m_wEpID,bMute); 
	return wRe; 
}


u16 CUmcConfCtrl::SetDualCnsReq( const TConfEpID &tConfEpInfo, BOOL32 bStart )
{
    if ( NULL == m_pCncSession ) 
    {
        return ERR_CMS;
    }
    
    u16 wCmd = ev_TppConfStopDual_Cmd; 
    if ( bStart )
    {
        wCmd = ev_TppConfStartDual_Cmd;
    }

    CTpMsg *pMsg = m_pCncSession->GetKdvMsgPtr();
    pMsg->SetUserData( m_pCncSession->GetInst() );
    pMsg->SetEvent( wCmd );
    pMsg->SetBody( &tConfEpInfo,sizeof(TConfEpID) );
     
    
    u16 wRe = m_pCncSession->PostMsg(TYPE_TPMSG ); 
    
    PrtMsg( wCmd, emEventTypeCnsSend, "confID=%d , cnsID=%d ", 
        tConfEpInfo.m_wConfID,tConfEpInfo.m_wEpID ); 
	return wRe; 
}



u16 CUmcConfCtrl::UpdateAudMixListReq( const TConfAuxMixInfo &tMixInfoList )
{
	if ( NULL == m_pCncSession ) 
	{
		return ERR_CMS;
	}
	
	CTpMsg *pMsg = m_pCncSession->GetKdvMsgPtr();
	pMsg->SetUserData( m_pCncSession->GetInst() );
	pMsg->SetEvent( ev_TppConfAMixUpdate_Cmd );
	pMsg->SetBody( &tMixInfoList, sizeof(TConfAuxMixInfo) );
 
	u16 wRe = m_pCncSession->PostMsg(TYPE_TPMSG ); 
	
	PrtMsg( ev_TppConfAMixUpdate_Cmd, emEventTypeCnsSend, "confID= %d, bStart= %d ", tMixInfoList.m_wConfID, tMixInfoList.m_bStart );

	PrtMsg( "AudSpeakerIndex= %d, AudList : %d, %d, %d, %d\n", tMixInfoList.m_atAuxMixList.m_wSpeakerIndex,
			tMixInfoList.m_atAuxMixList.m_awList[0], tMixInfoList.m_atAuxMixList.m_awList[1], tMixInfoList.m_atAuxMixList.m_awList[2], tMixInfoList.m_atAuxMixList.m_awList[3] );		
	
	return wRe;
}

u16 CUmcConfCtrl::AudMixDisListOprCmd( const TTPDisListOpr &tDisListOpr )
{
	if ( NULL == m_pCncSession ) 
	{
		return ERR_CMS;
	}
	CTpMsg *pMsg = m_pCncSession->GetKdvMsgPtr();
	pMsg->SetUserData( m_pCncSession->GetInst() );
	pMsg->SetEvent( ev_TppAudMixDisListOpr_Cmd );
	pMsg->SetBody( &tDisListOpr, sizeof(TTPDisListOpr) );

	u16 wRe = m_pCncSession->PostMsg(TYPE_TPMSG ); 

	PrtMsg( ev_TppAudMixDisListOpr_Cmd, emEventTypeCnsSend, "confID= %d, EpID= %d, wIndex= %d, OprType= %d (%d:DisListOpr_Add, %d:em_DisListOpr_Del )",
		tDisListOpr.m_wConfID, tDisListOpr.m_wEpID, tDisListOpr.m_wIndex, tDisListOpr.m_emOprType, em_DisListOpr_Add, em_DisListOpr_Del );

	return wRe;
}


u16 CUmcConfCtrl::UpdatePollListReq( const TConfTurnInfo &tTurnInfoList )
{
   	if ( NULL == m_pCncSession ) 
	{
		return ERR_CMS;
	}
	
// 	CTpMsg *pMsg = m_pCncSession->GetKdvMsgPtr();
// 	pMsg->SetEvent( evtp_UpdateTurn_cmd );
// 	pMsg->SetBody( &tTurnInfoList,sizeof(TConfTurnInfo) );
// 	
// 	u16 wRe = m_pCncSession->PostMsg(TYPE_TPMSG ); 
// 	
// 	PrtMsg( evtp_UpdateTurn_cmd, emEventTypeUmsSend, "confID=%d, PollCount=%d", tTurnInfoList.m_wConfID,tTurnInfoList.m_atTurnList.m_wNum);
	
	return 0 ;//wRe;
}



u16 CUmcConfCtrl::StartAuxMixReq( const u16 wConfID )
{
   	if ( NULL == m_pCncSession ) 
	{
		return ERR_CMS;
	}
	
// 	CTpMsg *pMsg = m_pCncSession->GetKdvMsgPtr();
// 	pMsg->SetEvent( ev_TppConfAMixUpdate_Cmd );
// 	pMsg->SetBody( &wConfID,sizeof(u16) );
//     BOOL32 bStart = TRUE;
// 	pMsg->CatBody(&bStart,sizeof(BOOL32));
// 	u16 wRe = m_pCncSession->PostMsg(TYPE_TPMSG ); 
// 	
//  	PrtMsg( evtp_StartAuxMix_cmd, emEventTypeUmsSend, "confID=%d ", wConfID);
	
	return 0 ; //wRe;
}

u16 CUmcConfCtrl::StopAuxMixReq( const u16 wConfID )
{
    if ( NULL == m_pCncSession ) 
    {
        return ERR_CMS;
    }
    
//     CTpMsg *pMsg = m_pCncSession->GetKdvMsgPtr();
//     pMsg->SetEvent( evtp_UpdateAudMixInfo_cmd );
//     pMsg->SetBody( &wConfID,sizeof(u16) );
//     BOOL32 bStart = FALSE;
//     pMsg->CatBody(&bStart,sizeof(BOOL32));
//     u16 wRe = m_pCncSession->PostMsg(TYPE_TPMSG ); 
    
//    PrtMsg( evtp_StartAuxMix_cmd, emEventTypeUmsSend, "confID=%d ", wConfID);
    
	return 0 ; //wRe; 
}


u16 CUmcConfCtrl::StartPollReq( const u16 wConfID )
{
	if ( NULL == m_pCncSession ) 
	{
		return ERR_CMS;
	}
	
// 	CTpMsg *pMsg = m_pCncSession->GetKdvMsgPtr();
// 	pMsg->SetEvent( evtp_StartTurn_cmd );
// 	pMsg->SetBody( &wConfID,sizeof(u16) );
// 	
// 	u16 wRe = m_pCncSession->PostMsg(TYPE_TPMSG ); 
// 	
// 	PrtMsg( evtp_StartTurn_cmd, emEventTypeUmsSend, "confID=%d ", wConfID);
	
	return 0;//wRe;
}

u16 CUmcConfCtrl::StopPollReq( const u16 wConfID )
{	
	//wait 
	return NO_ERROR;
}


 
void CUmcConfCtrl::OnConfStateNty( const CMessage& cMsg )
{
    CTpMsg cTpMsg(&cMsg);
    
    TTPCnsConfStatus tConfStatus = *reinterpret_cast<TTPCnsConfStatus*>(cTpMsg.GetBody()); 
    
    if ( tConfStatus.emState == em_CALL_CONNECTED )
    {
        m_tConfInfo.m_wConfID = tConfStatus.wConfID;
        m_tConfInfo.m_emConfType = tConfStatus.m_emCallType;
        _snprintf( m_tConfInfo.m_achConfName , sizeof( m_tConfInfo.m_achConfName ), tConfStatus.achConfName );
        //m_tConfInfo.m_tStartTime = tConfStatus.m_tmStartTime;
        //tConfStatus.m_tmStartTimeֵ��Ϊ�������ʱ�䣬�뱾�ص�ǰʱ�任��󣬵õ���Ա��صĿ�ʼ����ʱ�䴫�� dyy 2013-9-11
        time_t tCurTime = time(NULL);
        m_tConfInfo.m_tStartTime = difftime ( tCurTime, tConfStatus.m_tmStartTime ); 
        //��ֹtime_tԽ��
        if ( m_tConfInfo.m_tStartTime < 0 )
        {
            m_tConfInfo.m_tStartTime = 0;
        }
    }
    else
    {
        m_tConfInfo.Clear();
        m_tConfInfo.m_wConfID = INVALID_WORD;
    } 
    
    //em_CALL_CALLING״̬���治��Ҫˢ��
    if ( tConfStatus.emState != em_CALL_CALLING )
    {
        PostEvent(UI_UMS_UPDATE_CONFINFO, 0, 0 );
    }

}
 
/*
//�Ҷϻ�����
enum EmTpDropConfRet
{
TP_DropConf_Success,
TP_DropConf_ConfUnExit,	//����ģ�岻����
};*/
void CUmcConfCtrl::OnHungUpConfRsp( const CMessage& cMsg )
{  
// 	CTpMsg kdvMsg(&cMsg);
// 	u16 wConfID = * reinterpret_cast<u16*>( kdvMsg.GetBody() );
// 	EmTpDropConfRet emRe = *reinterpret_cast<EmTpDropConfRet*>( kdvMsg.GetBody() + sizeof(u16) );
// 
//     PrtMsg(evtp_HungUpConf_result,emEventTypeUmsRecv,"ConfID=%d, errCode=%d ( %d:Success, %d:ConfUnExit )",
//                      wConfID, emRe,TP_DropConf_Success,TP_DropConf_ConfUnExit) ; 
//     
//     u32 dwErrID = NO_ERROR;
//     if ( emRe == TP_DropConf_ConfUnExit )
//     {
//         dwErrID= ERR_UMC_HUNGUP_CONF_UNEXIST;
//     }
//     else
//     {  
//             
//        PrtMsg(evtp_HungUpConf_result,emEventTypeUmsRecv,"[CConfCtrl::OnHungUpConfRsp] umcLib ɾ�� ConfID=%d �Ļ���", wConfID ) ; 
//         
//     }
   
//	PostEvent(UI_UMS_HANGUP_CONF_RSP,wConfID,dwErrID);
}


void CUmcConfCtrl::OnHangupCnsInd( const CMessage& cMsg )
{
    CTpMsg cTpMsg(&cMsg);  

    u16 wCnsId = *reinterpret_cast<u16*>(cTpMsg.GetBody()); 
    EmCnsCallReason emReason = *reinterpret_cast<EmCnsCallReason*>(cTpMsg.GetBody() + sizeof(u16) );
    
    PrtMsg( ev_TppHangupCns_Ind, emEventTypeCnsRecv, "CnsId: %d, EmCnsCallReason: %d",wCnsId, emReason );   
}


/*
//���н��
enum EmCnsCallReason	
{
EmCnsCallReason_success,
EmCnsCallReason_hungup,			//�Զ˲����ܻ��������Ҷ�
EmCnsCallReason_Unreachable,	//�Զ˲����ߣ��޷�����
EmCnsCallReason_resourcefull,	//�Զ��޿�����Դ
EmCnsCallReason_dstnotfind,		//Ŀ�겻����
EmCnsCallReason_Busy,			//�Զ�æ
EmCnsCallReason_Local,			//����ԭ��
EmCnsCallReason_NoConf,			//���鲻����
EmCnsCallReason_Exist,			//�Զ����ڱ�������
EmCnsCallReason_Rejected,		//�Զ˾ܾ�
EmCnsCallReason_peerhungup,		//�Զ˹Ҷ�
EmCnsCallReason_Abnormal,       //���ص��߹Ҷ�
EmCnsCallReason_PeerAbnormal,   //�Զ˵��߹Ҷ�
EmCnsCallReason_unknown,   
};
*/
void CUmcConfCtrl::OnInviteCnsRsp( const CMessage& cMsg )
{   

	CTpMsg kdvMsg(&cMsg);

	TTPAlias tInviteInfo = * reinterpret_cast<TTPAlias*>( kdvMsg.GetBody() );

	EmCnsCallReason emRe = * reinterpret_cast<EmCnsCallReason*>( kdvMsg.GetBody() + sizeof(TTPAlias) );

	CString cnsInfo;
    cnsInfo.Format("%s",tInviteInfo.m_abyAlias);

    PrtMsg( ev_TppInviteCnsByAlias_Ind, emEventTypeCnsRecv," EPAlias=%s, errCode=%d ( \
%d:success, %d:hungup, %d:Unreachable, %d:resourcefull, %d:dstnotfind, %d:Busy, %d:Local, %d:NoConf, %d:Existed, \
%d:Rejected, %d:peerhungup, %d:Abnormal, %d:PeerAbnormal, %d:ConfOver, %d:cncallexception, %d:ConfExist, %d:unknown )",
                                                        cnsInfo, emRe,
                                                        EmCnsCallReason_success, EmCnsCallReason_hungup, 
                                                        EmCnsCallReason_Unreachable, EmCnsCallReason_resourcefull, EmCnsCallReason_dstnotfind,
                                                        EmCnsCallReason_Busy, EmCnsCallReason_Local,EmCnsCallReason_NoConf,EmCnsCallReason_Exist,
														EmCnsCallReason_Rejected, EmCnsCallReason_peerhungup, EmCnsCallReason_Abnormal, EmCnsCallReason_PeerAbnormal,
														EmCnsCallReason_ConfOver, EmCnsCallReason_cncallexception, EmCnsCallReason_ConfExist, EmCnsCallReason_unknown);
    u32 dwErrID = NO_ERROR;
    switch( emRe )
    {
    case EmCnsCallReason_hungup:
        dwErrID = ERR_UMC_CALLCNS_HUNGUP;
        break;
    case EmCnsCallReason_Unreachable:
        dwErrID = ERR_CMS_CALLCNS_UNREACHABLE;
        break;
    case EmCnsCallReason_resourcefull:
        dwErrID = ERR_UMC_CALLCNS_RESOURCE_FULL;
        break;
    case EmCnsCallReason_dstnotfind:
        dwErrID = ERR_UMC_CALLCNS_DST_NOT_FOUND;
        break;
    case EmCnsCallReason_Busy:
        dwErrID = ERR_UMC_CALLCNS_BUSY;
        break;
    case EmCnsCallReason_Local:
        dwErrID = ERR_UMC_CALLCNS_LOCAL;
        break;
    case EmCnsCallReason_NoConf:
        dwErrID = ERR_CMS_CALLCNS_NO_CONF;
        break;
    case EmCnsCallReason_Exist:
        dwErrID = ERR_UMC_CALLCNS_CNS_EXIST;
        break;
	case EmCnsCallReason_Rejected:
        dwErrID = ERR_UMC_CALLCNS_CNS_REJECTED;
        break;
	case EmCnsCallReason_peerhungup:
        dwErrID = ERR_UMC_CALLCNS_CNS_PEERHUNGUP;
        break;
	case EmCnsCallReason_Abnormal:
        dwErrID = ERR_UMC_CALLCNS_CNS_ABNORMAL;
        break;
	case EmCnsCallReason_PeerAbnormal:
        dwErrID = ERR_UMC_CALLCNS_CNS_PEERABNORMAL;
        break;
	case EmCnsCallReason_ConfOver:
        dwErrID = ERR_UMC_CALLCNS_CNS_CONFOVER;
        break;
	case EmCnsCallReason_cncallexception:
        dwErrID = ERR_UMC_CALLCNS_CNS_CALLEXCEPTION;
        break;
	case EmCnsCallReason_ConfExist:
        dwErrID = ERR_UMC_CALLCNS_CNS_CONFEXIST;
        break;
	case EmCnsCallReason_unknown:
		dwErrID = ERR_UMC_CALLCNS_CNS_UNKNOWN;
        break;
	default:
		break;
    }
   
	PostEvent( UI_UMS_INVITE_CNS_RSP, (WPARAM)&cnsInfo, dwErrID );
} 

 
void CUmcConfCtrl::OnCallConfCnsRsp( const CMessage& cMsg )
{
    CTpMsg kdvMsg(&cMsg);

    u16 wID = * reinterpret_cast<u16*>( kdvMsg.GetBody() );
    
    EmCnsCallReason emRe = * reinterpret_cast<EmCnsCallReason*>( kdvMsg.GetBody() + sizeof(u16) );
     
    TCnsInfo *pTCnsInfo = m_tConfInfo.GetCnsInfoByID( wID );
    if ( pTCnsInfo == NULL )
    {
        PrtMsg( ev_TppInviteCnsByEpId_Ind,emEventTypeCnsRecv," EpID=%d, �����в����ڸ�ID",  wID );    
        return;
    }
     
    
    CString cnsInfo;
    cnsInfo.Format("%s",pTCnsInfo->m_achRoomName );
    
    PrtMsg( ev_TppInviteCnsByEpId_Ind,emEventTypeCnsRecv," EPAlias=%s, errCode=%d ( \
%d:success, %d:hungup, %d:Unreachable, %d:resourcefull, %d:dstnotfind, %d:Busy, %d:LocalReason, %d:NoConf, %d:Existe \
%d:Rejected, %d:peerhungup, %d:Abnormal, %d:PeerAbnormal, %d:ConfOver, %d:cncallexception, %d:ConfExist, %d:unknown )",
        cnsInfo, emRe,
        EmCnsCallReason_success, EmCnsCallReason_hungup, 
        EmCnsCallReason_Unreachable, EmCnsCallReason_resourcefull, EmCnsCallReason_dstnotfind,
        EmCnsCallReason_Busy, EmCnsCallReason_Local,EmCnsCallReason_NoConf,EmCnsCallReason_Exist,
		EmCnsCallReason_Rejected, EmCnsCallReason_peerhungup, EmCnsCallReason_Abnormal, EmCnsCallReason_PeerAbnormal,
		EmCnsCallReason_ConfOver, EmCnsCallReason_cncallexception, EmCnsCallReason_ConfExist, EmCnsCallReason_unknown);
    u32 dwErrID = NO_ERROR;
    switch( emRe )
    {
    case EmCnsCallReason_hungup:
        dwErrID = ERR_UMC_CALLCNS_HUNGUP;
        break;
    case EmCnsCallReason_Unreachable:
        dwErrID = ERR_CMS_CALLCNS_UNREACHABLE;
        break;
    case EmCnsCallReason_resourcefull:
        dwErrID = ERR_UMC_CALLCNS_RESOURCE_FULL;
        break;
    case EmCnsCallReason_dstnotfind:
        dwErrID = ERR_UMC_CALLCNS_DST_NOT_FOUND;
        break;
    case EmCnsCallReason_Busy:
        dwErrID = ERR_UMC_CALLCNS_BUSY;
        break;
    case EmCnsCallReason_Local:
        dwErrID = ERR_UMC_CALLCNS_LOCAL;
        break;
    case EmCnsCallReason_NoConf:
        dwErrID = ERR_CMS_CALLCNS_NO_CONF;
        break;
    case EmCnsCallReason_Exist:
        dwErrID = ERR_UMC_CALLCNS_CNS_EXIST;
        break;
	case EmCnsCallReason_Rejected:
        dwErrID = ERR_UMC_CALLCNS_CNS_REJECTED;
        break;
	case EmCnsCallReason_peerhungup:
        dwErrID = ERR_UMC_CALLCNS_CNS_PEERHUNGUP;
        break;
	case EmCnsCallReason_Abnormal:
        dwErrID = ERR_UMC_CALLCNS_CNS_ABNORMAL;
        break;
	case EmCnsCallReason_PeerAbnormal:
        dwErrID = ERR_UMC_CALLCNS_CNS_PEERABNORMAL;
        break;
	case EmCnsCallReason_ConfOver:
        dwErrID = ERR_UMC_CALLCNS_CNS_CONFOVER;
        break;
	case EmCnsCallReason_cncallexception:
        dwErrID = ERR_UMC_CALLCNS_CNS_CALLEXCEPTION;
        break;
	case EmCnsCallReason_ConfExist:
        dwErrID = ERR_UMC_CALLCNS_CNS_CONFEXIST;
        break;
	case EmCnsCallReason_unknown:
		dwErrID = ERR_UMC_CALLCNS_CNS_UNKNOWN;
        break;
	default:
		break;
    }
    
	PostEvent( UI_UMS_INVITE_CNS_RSP, (WPARAM)&cnsInfo, dwErrID );
}
 
void CUmcConfCtrl::OnUpdateConfCnsListNotify( const CMessage& cMsg )
{   
    CTpMsg kdvMsg(&cMsg);
    BOOL bRefreshUI = FALSE;

	/*
#ifdef _DEBUG
    for ( int k = 0; k< m_tplConfList.Size(); k++ )
    {
        for ( int j = 0; j< m_tplConfList.GetAt(k).m_tplCnsList.Size(); j++ )
        {
            TRACE("\n[CConfCtrl::OnUpdateConfCnsListNotify]before update: confID=%d ,cnsID= %d ,cnsAliars=%s, bOnLine=%d \n",m_tplConfList.GetAt(k).m_wConfID,
                m_tplConfList.GetAt(k).m_tplCnsList.GetAt(j).m_wEpID,
                m_tplConfList.GetAt(k).m_tplCnsList.GetAt(j).m_achRoomName, m_tplConfList.GetAt(k).m_tplCnsList.GetAt(j).m_bOnline);
        }
    }

#endif
 */

	
    TConfCnsInfo tConfCns = *reinterpret_cast<TConfCnsInfo*>( kdvMsg.GetBody() );
/*    
    PrtMsg( evtp_UpdateConfCnsList_Notify,emEventTypeUmsRecv,"ConfID=%d, CNS Count=%d, operateType=%d (0:Add, 1: Del, 2: Update ) ",
		                                                         tConfCns.m_wConfID, tConfCns.m_wNum,tConfCns.m_emOpr);

//#ifdef _DEBUG
    for ( int j = 0; j< tConfCns.m_wNum; j++ )
    {
        PrtMsg("\n[CConfCtrl::OnUpdateConfCnsListNotify]msginfo: confID=%d ,cnsID= %d ,cnsAliars=%s, bOnLine=%d \n",tConfCns.m_wConfID,
            tConfCns.m_tConfCnsList[j].m_wEpID,
            tConfCns.m_tConfCnsList[j].m_achRoomName,tConfCns.m_tConfCnsList[j].m_bOnline);
      }
//#endif
*/

	if ( tConfCns.m_wNum <= 0 || tConfCns.m_wNum > TP_REFRESH_LIST_THREE ) 
	{  
		PrtMsg("\n[CConfCtrl::OnUpdateConfCnsListNotify]msginfo: confID=%d, m_wNum =%d , m_wNum �Ƿ��� return\n", 
			tConfCns.m_wConfID, tConfCns.m_wNum );
		return;
	}

  
	u16 wAddNum = tConfCns.m_wNum;
	switch( tConfCns.m_emOpr ) 
	{
	case tp_OprType_Del:			//ɾ��
        {   
            bRefreshUI = TRUE;
			for ( int i = 0; i< tConfCns.m_wNum ;  i++ )
			{   
				s32 nCnsIndex = m_tConfInfo.GetCnsIndexFrmCnsLst( tConfCns.m_tConfCnsList[i].m_wEpID );
				if ( nCnsIndex >= 0 ) 
				{
					m_tConfInfo.m_tplCnsList.Delete( nCnsIndex );
				}
				
			}
			
		}
		break;
	case tp_OprType_Add:			//����
//         {
// 		    m_tConfInfo.m_tplCnsList.Add(tConfCns.m_tConfCnsList,tConfCns.m_wNum);	
//             bRefreshUI = TRUE;
//         }
// 		break;

	case tp_OprType_Update:   // ����
        {   
            
			for ( int i = 0; i< tConfCns.m_wNum ;  i++ )
			{   
                //if ( m_tConfInfo.m_wConfID == INVALID_WORD ) 
                //{
                //    return ;
                //}

				//UMS��֮��ŷ���������
				//if ( tConfCns.m_tConfCnsList[i].m_emEpType != emTPEndpointTypeCNS)
				//{
				//	return ;
				//}

				s32 Index =	m_tConfInfo.GetCnsIndexFrmCnsLst( tConfCns.m_tConfCnsList[i].m_wEpID );
				if ( Index >= 0 ) 
                {  
                    if (    m_tConfInfo.m_tplCnsList.GetAt( Index ).m_bOnline != tConfCns.m_tConfCnsList[i].m_bOnline 
                         || strcmp( m_tConfInfo.m_tplCnsList.GetAt( Index ).m_achRoomName, tConfCns.m_tConfCnsList[i].m_achRoomName ) != 0  
                         || m_tConfInfo.m_tplCnsList.GetAt( Index ).m_bMute != tConfCns.m_tConfCnsList[i].m_bMute 
                         || m_tConfInfo.m_tplCnsList.GetAt( Index ).m_bQuiet != tConfCns.m_tConfCnsList[i].m_bQuiet
						 || m_tConfInfo.m_tplCnsList.GetAt( Index ).m_emEpType != tConfCns.m_tConfCnsList[i].m_emEpType )
                    {
                        bRefreshUI = TRUE;
                    }

					m_tConfInfo.m_tplCnsList.SetAt( Index, &tConfCns.m_tConfCnsList[i] );
				}
				else
				{
					bRefreshUI = TRUE;
					m_tConfInfo.m_tplCnsList.Add( &(tConfCns.m_tConfCnsList[i]) );	
				}
			}
		}
		break;
	default:
		 ;
	}

/*
#ifdef _DEBUG
    for ( int i = 0; i< m_tplConfList.Size(); i++ )
    {
        for ( int j = 0; j< m_tplConfList.GetAt(i).m_tplCnsList.Size(); j++ )
        {
            TRACE("\n[CConfCtrl::OnUpdateConfCnsListNotify]afterUpdate confID=%d ,cnsID= %d ,cnsAliars=%s, bOnLine=%d \n",m_tplConfList.GetAt(i).m_wConfID,
                m_tplConfList.GetAt(i).m_tplCnsList.GetAt(j).m_wEpID,
                m_tplConfList.GetAt(i).m_tplCnsList.GetAt(j).m_achRoomName, m_tplConfList.GetAt(i).m_tplCnsList.GetAt(j).m_bOnline);
        }
    }
#endif
*/
	if ( bRefreshUI )
	{
		PrtMsg( ev_CnConfEpList_Nty,emEventTypeCnsRecv,"ConfID=%d, CNS Count=%d, operateType=%d (0: Add, 1: Del, 2: Update ) ",
		                                                         tConfCns.m_wConfID, tConfCns.m_wNum,tConfCns.m_emOpr);

		for ( int j = 0; j< tConfCns.m_wNum; j++ )
		{
			PrtMsg("\n[CConfCtrl::OnUpdateConfCnsListNotify]msginfo: confID=%d, cnsID= %d, EpType=%d, cnsRoomName=%s, bOnLine=%d, emCallReason=%d \n", tConfCns.m_wConfID,
				tConfCns.m_tConfCnsList[j].m_wEpID, tConfCns.m_tConfCnsList[j].m_emEpType,
				tConfCns.m_tConfCnsList[j].m_achRoomName, tConfCns.m_tConfCnsList[j].m_bOnline, tConfCns.m_tConfCnsList[j].m_emCallReason );
		}

        PostEvent( UI_UMS_REFRESH_CONFCNS_LIST, tConfCns.m_wConfID ); 

        //����cns��Ϣ ����Ǳ��� ��Ҫ����ʾ
        if ( tp_OprType_Update == tConfCns.m_emOpr )
        {
            PostEvent( UI_UMS_UPDATE_CONFCNS_LIST, tConfCns.m_wConfID, (LPARAM)&tConfCns );
        }
	}
	  
} 


void CUmcConfCtrl::OnUpdateConfAuxMixlistNotify( const CMessage& cMsg )
{   
 	CTpMsg cTpMsg(&cMsg);

    TConfAuxMixInfo tConfAudList = *reinterpret_cast<TConfAuxMixInfo*>( cTpMsg.GetBody() );
 
 	PrtMsg( ev_TppConfAMixUpdate_Nty, emEventTypeCnsRecv, "ConfID= %d, bStart= %d, AudSpeakerIndex= %d",
 		                                                         tConfAudList.m_wConfID, tConfAudList.m_bStart, tConfAudList.m_atAuxMixList.m_wSpeakerIndex );
 
 	PrtMsg( "\tAudList : %d, %d, %d, %d\n",  tConfAudList.m_atAuxMixList.m_awList[0], tConfAudList.m_atAuxMixList.m_awList[1], 
 			tConfAudList.m_atAuxMixList.m_awList[2], tConfAudList.m_atAuxMixList.m_awList[3] );		
 
     
	m_tConfInfo.m_bStartAudmix = tConfAudList.m_bStart;
	memcpy( &m_tConfInfo.m_tAudmixList, &tConfAudList.m_atAuxMixList, sizeof(TAuxMixList) );

	PostEvent( UI_UMS_REFRESH_CONFAUDMIX_LIST, tConfAudList.m_wConfID, tConfAudList.m_bStart );   
} 


void CUmcConfCtrl::OnUpdateConfAuxMixlistInd( const CMessage& cMsg )
{
	CTpMsg cTpMsg(&cMsg);

    TConfAuxMixInfo tConfAudList = *reinterpret_cast<TConfAuxMixInfo*>( cTpMsg.GetBody() );
	
	PrtMsg( ev_TppConfAMixUpdate_Ind, emEventTypeCnsRecv, "ConfID= %d, bStart= %d, AudSpeakerIndex= %d",
		tConfAudList.m_wConfID, tConfAudList.m_bStart, tConfAudList.m_atAuxMixList.m_wSpeakerIndex );
	
	PrtMsg( "\tAudList : %d, %d, %d, %d\n",  tConfAudList.m_atAuxMixList.m_awList[0], tConfAudList.m_atAuxMixList.m_awList[1], 
		tConfAudList.m_atAuxMixList.m_awList[2], tConfAudList.m_atAuxMixList.m_awList[3] );		

    //�յ�Indʱ�����½���
	//m_tConfInfo.m_bStartAudmix = tConfAudList.m_bStart;
	//memcpy( &m_tConfInfo.m_tAudmixList, &tConfAudList.m_atAuxMixList, sizeof(TAuxMixList) );
	   
	//PostEvent( UI_UMS_REFRESH_CONFAUDMIX_LIST, tConfAudList.m_wConfID, tConfAudList.m_bStart );   
}

void CUmcConfCtrl::OnAudMixDisListOprNotify( const CMessage& cMsg )
{
	CTpMsg cTpMsg(&cMsg);

	TTPDisListOpr tDisListOpr = *reinterpret_cast<TTPDisListOpr*>( cTpMsg.GetBody() );
	
	PrtMsg( ev_TppAudMixDisListOpr_Ind, emEventTypeCnsRecv, "confID= %d, EpID= %d, wIndex= %d, OprType= %d (%d:DisListOpr_Add, %d:em_DisListOpr_Del ), EmDisListOprReslt = %d",
		tDisListOpr.m_wConfID, tDisListOpr.m_wEpID, tDisListOpr.m_wIndex, tDisListOpr.m_emOprType, em_DisListOpr_Add, em_DisListOpr_Del, tDisListOpr.m_emOprReslt );
}


void CUmcConfCtrl::OnUpdateConfPolllistNotify( const CMessage& cMsg )
{
 
// 	CTpMsg kdvMsg(&cMsg);
//     TConfTurnInfo tConfPollList = *reinterpret_cast<TConfTurnInfo*>( kdvMsg.GetBody() );
// 	
// 	PrtMsg( evtp_UpdateTurn_cmd,emEventTypeUmsRecv,"ConfID=%d, pollMemCount=%d",
// 		tConfPollList.m_wConfID, tConfPollList.m_atTurnList.m_wNum );
// 	
// 	if ( tConfPollList.m_atTurnList.m_wNum <= 0 ) 
// 	{ 
// 		return;
// 	}
//     
// 	s32 nIndex = GetConfIndexByID( tConfPollList.m_wConfID );
// 	if ( nIndex < 0 ) 
// 	{
// 		return;
// 	}
// 	
//     
// 	m_tplConfList.at( nIndex ).m_tplPollList.Clear();
//     m_tplConfList.at( nIndex ).m_tplPollList.Add(tConfPollList.m_atTurnList.m_awList,tConfPollList.m_atTurnList.m_wNum);
// 	
//     
// 	PostEvent(UI_UMS_REFRESH_CONFPOLL_LIST,tConfPollList.m_wConfID);
} 


void CUmcConfCtrl::OnUpdateConfSpeakerNotify( const CMessage& cMsg )
{
    
    CTpMsg kdvMsg(&cMsg); 

    TConfEpID tConfEp = *reinterpret_cast<TConfEpID*>( kdvMsg.GetBody() );
    
    PrtMsg( ev_TppConfApplySpeaker_Nty,emEventTypeCnsRecv,"ConfID=%d, SpeakerCnsID=%d",
        tConfEp.m_wConfID, tConfEp.m_wEpID );
     
    m_tConfInfo.m_wSpeaker = tConfEp.m_wEpID;
    
    
    PostEvent(UI_UMS_CHANGE_SPEAKER_NOTIFY,tConfEp.m_wConfID,tConfEp.m_wEpID);
} 

 
/*
enum EmTpApplySpeakerRet
{
TP_ApplySpeaker_Success,		
TP_ApplySpeaker_ConfUnExist,		//���鲻����
TP_ApplySpeaker_EpIDError,			//�᳡������
TP_ApplySpeaker_EpStateError,		//�᳡δ���߻�ͨ����δ����
};
*/
void CUmcConfCtrl::OnSetSpokeCnsRsp( const CMessage& cMsg )
{
	
 	CTpMsg kdvMsg(&cMsg);

 	TConfEpID  tConfEpInfo  = * reinterpret_cast<TConfEpID*>( kdvMsg.GetBody() ); 
 	EmTpApplySpeakerRet emRe = * reinterpret_cast<EmTpApplySpeakerRet*>( kdvMsg.GetBody() + sizeof(TConfEpID) );
    PrtMsg(ev_TppConfApplySpeaker_Ind,emEventTypeCnsRecv,"ConfID=%d, CNSID=%d , \
         result=%d (%d:Success, %d:ConfUnExist, %d:EpIDError, %d:EpStateError)",
         tConfEpInfo.m_wConfID, tConfEpInfo.m_wEpID,emRe,TP_ApplySpeaker_Success,TP_ApplySpeaker_ConfUnExist,TP_ApplySpeaker_EpIDError,TP_ApplySpeaker_EpStateError) ; 
 	
    if ( emRe == TP_ApplySpeaker_Success )
    {

       
       m_tConfInfo.m_wSpeaker = tConfEpInfo.m_wEpID;
    }

 	PostEvent(UI_UMS_SET_SPEAKER_RSP,tConfEpInfo.m_wConfID,emRe);	
	return;
} 

void CUmcConfCtrl::OnSetMuteCnsRsp( const CMessage& cMsg ) 
{ 
    CTpMsg kdvMsg(&cMsg);

    TConfEpID  tConfEpInfo  = * reinterpret_cast<TConfEpID*>( kdvMsg.GetBody() ); 
    BOOL32 bRe = * reinterpret_cast<BOOL32*>( kdvMsg.GetBody() + sizeof(TConfEpID) );
    PrtMsg(ev_TppConfMute_Ind,emEventTypeCnsRecv,"ConfID=%d, CNSID=%d ,bStart=%d  ",
        tConfEpInfo.m_wConfID, tConfEpInfo.m_wEpID,bRe ) ; 
    
    int CnsIndex = m_tConfInfo.GetCnsIndexFrmCnsLst( tConfEpInfo.m_wEpID );
    m_tConfInfo.m_tplCnsList.GetAt(CnsIndex).m_bMute = bRe;

    PostEvent(UI_UMS_SET_MUTE_CNS_RSP,tConfEpInfo.m_wConfID,bRe);	
    return;
} 
 
void CUmcConfCtrl::OnSetSilenceCnsRsp( const CMessage& cMsg )
{
    CTpMsg kdvMsg(&cMsg);

    TConfEpID  tConfEpInfo  = * reinterpret_cast<TConfEpID*>( kdvMsg.GetBody() ); 
    BOOL32 bRe = * reinterpret_cast<BOOL32*>( kdvMsg.GetBody() + sizeof(TConfEpID) );
    PrtMsg(ev_TppConfQuiet_Ind,emEventTypeCnsRecv,"ConfID=%d, CNSID=%d ,bStart=%d  ",
        tConfEpInfo.m_wConfID, tConfEpInfo.m_wEpID,bRe ) ; 
 
    
    int CnsIndex = m_tConfInfo.GetCnsIndexFrmCnsLst( tConfEpInfo.m_wEpID );
	if ( -1 == CnsIndex )
	{
		return;
	}
    m_tConfInfo.m_tplCnsList.GetAt(CnsIndex).m_bQuiet = bRe; 

    PostEvent(UI_UMS_SET_QUIET_CNS_RSP,tConfEpInfo.m_wConfID,bRe);	
    return;
    
} 


/*
enum EmTPDualReason
{
emTpDualAccept,
		emTpDualBusy,
		emTpDualPreemptive,
		emTpDualPeerReject,
		emTpDualPeerStop,
        emTpDualNoVideo,
        emTpDualLocalStop,
		emTpDualSndFail,       //����˫��ʧ��
};
*/
void CUmcConfCtrl::OnSetDualCnsRsp( const CMessage& cMsg )
{
    CTpMsg kdvMsg(&cMsg);

	u16 wEvent = kdvMsg.GetEvent();
    TConfEpID  tConfEpInfo  = * reinterpret_cast<TConfEpID*>( kdvMsg.GetBody() ); 
    EmTPDualReason emRe = * reinterpret_cast<EmTPDualReason*>( kdvMsg.GetBody() + sizeof(TConfEpID) );
    PrtMsg(kdvMsg.GetEvent(),emEventTypeCnsRecv,"ConfID=%d, CNSID=%d ,erroCode=%d \
        (%d:Accept, %d:DualBusy,%d:Preemptive, %d:PeerReject, %d:PeerStop,%d:NoVideo,%d:lLocalStop,%d:SndFail)",
        tConfEpInfo.m_wConfID, tConfEpInfo.m_wEpID,emRe ,emTpDualAccept,
        emTpDualBusy,emTpDualPreemptive,emTpDualPeerReject,emTpDualPeerStop,emTpDualNoVideo,emTpDualLocalStop,emTpDualSndFail) ; 
    /* ��ͨ������Ϣ���û����е�˫��ID -2013.7.5 xcr
    if ( emRe == emTpDualAccept )
    {
         
        if ( ev_TppConfStartDual_Ind == wEvent )
        {
			m_tConfInfo.m_wDual = tConfEpInfo.m_wEpID;
        }
		else
		{
			m_tConfInfo.m_wDual = INVALID_WORD;
		}
    }*/

    PostEvent( UI_UMS_SET_DUAL_CNS_RSP, tConfEpInfo.m_wConfID, emRe );	
    return;
    
}  

void CUmcConfCtrl::OnDualCnsNotify( const CMessage& cMsg )
{
    CTpMsg kdvMsg(&cMsg);

    TConfEpID  tConfEpInfo  = * reinterpret_cast<TConfEpID*>( kdvMsg.GetBody() );  
    PrtMsg(ev_TppConfDualEp_Nty,emEventTypeCnsRecv,"ConfID=%d, CNSID=%d ",
        tConfEpInfo.m_wConfID, tConfEpInfo.m_wEpID ) ; 
    
    
    m_tConfInfo.m_wDual = tConfEpInfo.m_wEpID;

    PostEvent(UI_UMS_DUAL_CNS_NOTIFY,tConfEpInfo.m_wConfID,tConfEpInfo.m_wEpID);	
    return;
    
}  

  

void CUmcConfCtrl::OnChairCnsNotify( const CMessage& cMsg )
{
    CTpMsg kdvMsg(&cMsg);
    
    TChairConfInfo tChairInfo = *reinterpret_cast<TChairConfInfo*>( kdvMsg.GetBody() );
    
    PrtMsg( ev_TppChairConfInfo_Nty, emEventTypeCnsRecv, "ConfID:%d, ConfName:%s, ChairName:%s",tChairInfo.m_wConfID, tChairInfo.m_tConfName.m_abyAlias, tChairInfo.m_tChairName.m_abyAlias);  
    
    
    if ( m_tConfInfo.m_wConfID == tChairInfo.m_wConfID )
    {
        //ֻ������ϯ����
        m_tConfInfo.SetChairInfo( tChairInfo.m_tChairName );
    }

	//_snprintf( m_tConfInfo.m_achConfName, sizeof(m_tConfInfo.m_achConfName), tChairInfo.m_tConfName.m_abyAlias);
    
    PostEvent(UI_UMS_UPDATE_CONFINFO);	
    return;
  
}

 
void CUmcConfCtrl::OnCnsLeaveNotify( const CMessage& cMsg )
{
	CTpMsg kdvMsg(&cMsg);
    
    TCnsInfo tInfo = *reinterpret_cast<TCnsInfo*>( kdvMsg.GetBody() );
    
    PrtMsg( ev_TppModuleterminalLeftConf, emEventTypeCnsRecv, "ID=%d, �᳡��=%s",tInfo.m_wEpID, tInfo.m_achRoomName );  
     
    PostEvent(UI_CNS_LEAVECONF_NOTIFY, tInfo.m_wEpID,(LPARAM)tInfo.m_achRoomName );	
    return;
}


void CUmcConfCtrl::OnUmsCommonReasonInd( const CMessage& cMsg )
{
    CTpMsg kdvMsg(&cMsg);
        
    TTPUmsReasonInd tReason = *reinterpret_cast<TTPUmsReasonInd*>( kdvMsg.GetBody() );
    
    PrtMsg( ev_TppUmsCommonReasonToUI_Ind, emEventTypeCnsRecv, "ReasonId: %d", tReason.m_dwReason );  
    
    PostEvent( UI_CNS_UMSREASON_IND, (WPARAM)&tReason, 0 );	

    return;
}


void CUmcConfCtrl::DispEvent(const CMessage &cMsg)
{
	DISP_FUN(CUmcConfCtrl, cMsg);
}

void CUmcConfCtrl::OnTimeOut(u16 wEvent)
{
    // ���ͳ�ʱ�¼�֪ͨ
    PostEvent(UI_UMS_CMD_TIMEOUT, wEvent);
}


 
