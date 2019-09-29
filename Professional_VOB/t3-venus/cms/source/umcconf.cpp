/*****************************************************************************
ģ����      : CMS����̨
�ļ���      : umcconf.cpp
����ļ�    : commoninterface.h
�ļ�ʵ�ֹ���: ��װ��umclib��cnclib�ӿڣ����ļ���Ҫ��װ���������ؽӿ�
����        : �����
�汾        : V1.0  Copyright(C) 2011-2012 KDC, All rights reserved.
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��      �汾        �޸���      �޸�����
2011/4/28  1.0          �����      ����
******************************************************************************/


#include "stdafx.h"
#include "cms.h"
#include "commoninterface.h"
#include "cmsConst.h"
#include "evcmslib.h"
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

 

u16 CCommonInterface::IsThisCnsHaveConf() const
{
    TTPCnsInfo tCnsInfo;
    GetLocalCnsInfo( tCnsInfo );
    if ( strlen(tCnsInfo.m_achRoomName) == 0 || m_tplConfList.size() <= 0 )
    {
        return INVALID_WORD;
    } 

    ARRAY<TCMSConf>::iterator it =  const_cast<TCMSConf*>( m_tplConfList.end() );
    while ( 1 )
    {  
        it--;
        
        s8*  pName = it->GetChairManAliars();
        if ( pName != NULL && strcmp(tCnsInfo.m_achRoomName, pName) == 0 )
        {
            return it->m_wConfID;
        } 

        if ( it == m_tplConfList.begin() )
        {
            return INVALID_WORD;
        }
    }
   return INVALID_WORD;
}
 

/**
* ����:  �ж� �Ƿ�Ϊ������cns
* @param strAliars ����
* @return   
* @remarks  
*/
BOOL32 CCommonInterface::IsLocalCns( String strAliars )
{
    TTPCnsInfo  tCnsInfo;
    GetLocalCnsInfo( tCnsInfo );
    if ( strcmp( tCnsInfo.m_achRoomName,strAliars.c_str() ) == 0 )
    {
        return TRUE;
    }
    return FALSE;
    
}

 


/**
* ����:  �ж� cns�Ƿ�Ϊ �������ϯ
* @param  
* @return   
* @remarks  
*/
BOOL32 CCommonInterface::IsCnsChairMan( u16 wCnsID )
{
     
    if ( IsInConf() )
    {
        if ( m_tConfInfo.GetChairCnsID() == wCnsID )
        {
            return TRUE;
        }
    }
    
    return FALSE;
}


BOOL32 CCommonInterface::IsInConf( TCMSConf *pConf/* = NULL*/ )
{   
    BOOL32 bIn = FALSE;

    TTPCnsConfStatus status = GetLocalCnsConfState() ;
    if ( status.emState == em_CALL_CONNECTED )
    {
        if ( pConf != NULL )
        {
            *pConf =  m_tConfInfo;
           
        }
        
        bIn = TRUE;
    }
    
    return bIn;
}
 

/*��  ��  ʹ�û���ģ�忪��
��  ��	achTempName ģ����
����ֵ  �ɹ�����0��ʧ�ܷ��ش�����
˵  ��	 */
u16 CCommonInterface::StartTemplateConf( s8* achTempName )  
{  
	if ( NULL == m_pCnsConfCtrl ) 
	{
		return ERR_CMS;
    } 
  
    if ( achTempName == NULL )
    {
        return ERR_CMS;
    }
    
    TTPDialParam  tTPDialParam;
    
    _snprintf( tTPDialParam.tCalledAddr.achAlias, sizeof(tTPDialParam.tCalledAddr.achAlias), "%s", achTempName );
    
    tTPDialParam.emProtocol = emTpSIP;
    tTPDialParam.emCallType = emTpInvite;
    tTPDialParam.tCalledAddr.emType = emTpAlias; 
    //  strncpy( (char*)tTPDialParam.tCalledAddr.achAlias, (char*)achIp, TP_MAX_H323ALIAS_LEN ); 
    tTPDialParam.tCalledAddr.wPort = TP_UMS_SIP_LISTIEN_PORT ;
    
    tTPDialParam.tCallingAddr.emType = emTpAlias; 
    tTPDialParam.tCallingAddr.wPort = CNS_SIP_STACK_LISTION_PORT ; 
    
    u16 wRe  = m_pCnsConfCtrl->MakeCall( tTPDialParam );
	return wRe;
}

 
u16 CCommonInterface::StartTemplateConf( const TTPAlias& tTemp )  
{  
	return	MakeCall( tTemp ); 
}

 
	
/*��  ��  ����һ����ʱ����
��  ��	tCnsList :�����ն��б� ,���᳡Ϊ��һ����Ա��������Ϊ���᳡
����ֵ  �ɹ�����0��ʧ�ܷ��ش�����
˵  ��	umsԤ��һ�����ڿ�����ʱ����Ļ���ģ�壨IDΪ0�����û���ģ����治��ʾ*/
u16 CCommonInterface::StartInstantConf( const /*TEpAddrList&*/ vector<TCnAddr>& tCnsList ) 
{   
     
	TTPCnsInfo tCnsInfo;
	GetLocalCnsInfo( tCnsInfo );
    
    TTPDialParam  tTPDialParam;
    _snprintf( tTPDialParam.tConfInfo.achConfName, sizeof(tTPDialParam.tConfInfo.achConfName), "%s%s", tCnsInfo.m_achRoomName, INSTANT_CONFTEMPLATE_NAME );
  
    tTPDialParam.bCreateConf = TRUE;
    tTPDialParam.emProtocol = emTpSIP;
    tTPDialParam.emCallType = emTpCreate;
    tTPDialParam.tCalledAddr.emType = emTpIPAddr; 
    //  strncpy( (char*)tTPDialParam.tCalledAddr.achAlias, (char*)achIp, TP_MAX_H323ALIAS_LEN ); 
    tTPDialParam.tCalledAddr.wPort = TP_UMS_SIP_LISTIEN_PORT ;

	TTPCallSerInfo tCallSerInfo;
	GetCallServerInfo( tCallSerInfo );
	tTPDialParam.tCalledAddr.dwIP = tCallSerInfo.dwCallServiceIP;
    
    tTPDialParam.tCallingAddr.emType = emTpAlias; 
    tTPDialParam.tCallingAddr.wPort = CNS_SIP_STACK_LISTION_PORT ; 
    
    tTPDialParam.byTerNum = tCnsList.size(); 
    
    for ( int i = 0; i < tCnsList.size() ; i++ )
    {   
        /*
        if ( tCnsList.m_tCnsList[i].m_tAlias.m_byType == tp_Alias_h323 )
        {
            tTPDialParam.atList[i].emType = emTpAlias;
        }
        else
        {
            tTPDialParam.atList[i].emType = emTpE164Num;
        }
        _snprintf( tTPDialParam.atList[i].achAlias, sizeof( tTPDialParam.atList[i].achAlias ) ,tCnsList.m_tCnsList[i].m_tAlias.m_abyAlias );
        */

        tTPDialParam.atList[i] = tCnsList[i];           
    }

	tTPDialParam.tConfInfo.emTpVideoFormat = emTPVH264;
	tTPDialParam.tConfInfo.emTpAudioFormat = GetAudioFormatInfo();

	TTPVidForamt tVidForamt, tDualVidForamt; 
	GetVideoFormatInfo( tVidForamt );
	GetDualVideoFormatInfo( tDualVidForamt );
	tTPDialParam.tConfInfo.byPriVidFps = tVidForamt.wVidFrameRate;
	tTPDialParam.tConfInfo.bySecVidFps = tDualVidForamt.wVidFrameRate;
	tTPDialParam.tConfInfo.emDualVideoQualityLevel = emTPH264HP;		//���治������HP��BP,�˴��̶�HP  ---2014.5.21 JYY
	tTPDialParam.tConfInfo.emPriVideoQualityLevel = emTPH264HP;
	tTPDialParam.tConfInfo.emTpResolution = tVidForamt.emTpVideoResolution;
	tTPDialParam.tConfInfo.emTpSecVidRes = tDualVidForamt.emTpVideoResolution;

	GetCallRateInfo( tTPDialParam.tConfInfo.wCallRate );
	GetDualCallRateInfo( tTPDialParam.tConfInfo.wDualCallRate );
	GetConfPollInfo( tTPDialParam.tConfInfo.tPollInfo );
	GetConfDisInfo( tTPDialParam.tConfInfo.tConfAudMixInfo.m_atAuxMixList.m_bAudMixOn );
	if ( tTPDialParam.tConfInfo.tConfAudMixInfo.m_atAuxMixList.m_bAudMixOn )
	{
		tTPDialParam.tConfInfo.tConfAudMixInfo.m_atAuxMixList.m_wSpeakerIndex = 0;
		tTPDialParam.tConfInfo.tConfAudMixInfo.m_atAuxMixList.m_awList[0] = 0;
	} 
	else
	{
		tTPDialParam.tConfInfo.tConfAudMixInfo.m_atAuxMixList.m_wSpeakerIndex = TP_INVALID_INDEX;
		tTPDialParam.tConfInfo.tConfAudMixInfo.m_atAuxMixList.m_awList[0] = TP_INVALID_INDEX;
	}
	tTPDialParam.tConfInfo.tConfAudMixInfo.m_atAuxMixList.m_awList[1] = TP_INVALID_INDEX;
	tTPDialParam.tConfInfo.tConfAudMixInfo.m_atAuxMixList.m_awList[2] = TP_INVALID_INDEX;
	tTPDialParam.tConfInfo.tConfAudMixInfo.m_atAuxMixList.m_awList[3] = TP_INVALID_INDEX;

    u16 wRe  = m_pCnsConfCtrl->MakeCall( tTPDialParam);
    return wRe;
   
}
 


/*��  ��  �Ҷϻ���
��  ��	dwConfID������ID
����ֵ  �ɹ�����0��ʧ�ܷ��ش�����
˵  ��	�������飬ע����û����Ƿ�Ϊ��ʱ���飬�������ʱ���飬����Ҫɾ��ģ�� */
u16 CCommonInterface::HangupConf( )   
{   
	if ( NULL == m_pUmsConfCtrl ) 
	{
		return ERR_CMS;
	}
	
	u16 wRe = m_pUmsConfCtrl->HangupConfReq();
	return wRe;
}



/*��  ��  ����ĳ�᳡�������
��  ��	tEp:�᳡��Ϣ
����ֵ  �ɹ�����0��ʧ�ܷ��ش�����
˵  ��	�����᳡Ϊ���᳡ʱ���ɲ��� */
u16 CCommonInterface::InviteCns( const TConfCallEpAddr &tEp ) 
{
	if ( NULL == m_pUmsConfCtrl ) 
	{
		return ERR_CMS;
	}
	
	u16 wRe = m_pUmsConfCtrl->InviteCnsReq(tEp);
	return wRe;
}



/**
* ����:	���л������Ѿ����ڵ�cns�᳡����ĳ����
* @param [int]  tEp	 ����ͻ᳡��Ϣ
* @return  u16 �ɹ�����0,ʧ�ܷ��ط�0������
* @remarks ��Ϣ��cms->ums  evtp_CallEP_cmd  \n
Ӧ�ظ���ums->cms evtp_CallEP_result   \n
���ɹ�����Ӧ����ums->cms evtp_UpdateConfCnsList_Notify
*/ 
u16 CCommonInterface::CallConfCns( const TConfEpID &tEp )
{
    if ( NULL == m_pUmsConfCtrl ) 
    {
        return ERR_CMS;
    }
    
    u16 wRe = m_pUmsConfCtrl->CallConfCnsReq(tEp);
	return wRe;
}


/**
* ����:  ��ȡ������cns����Ϣ
* @param [in] tEp:�᳡��Ϣ
* @param [out] tCnsInfo:�᳡��Ϣ
* @return �ɹ�����0��ʧ�ܷ��ش�����
* @remarks �����᳡Ϊ���᳡ʱ���ɲ���
*/
u16 CCommonInterface::GetConfCnsByID( const TConfEpID &tConfEpInfo , TCnsInfo* pTCnsInfo)
{
     
    if( !IsInConf() )
    {
       return ERR_CMS_CONF_UNEXIST;
    }

    for ( int i = 0; i< m_tConfInfo.m_tplCnsList.Size(); i++ )
    {
        if ( m_tConfInfo.m_tplCnsList.GetAt(i).m_wEpID == tConfEpInfo.m_wEpID )
        {
            if( pTCnsInfo != NULL )
            {
                *pTCnsInfo = m_tConfInfo.m_tplCnsList.GetAt(i);
            }

            return NO_ERROR;

        }
    }

    return errCmsCnsUneixt;
}

/**
* ����:  �������᳡������� 
* @param [in] tEp:�᳡��Ϣ
* @return �ɹ�����0��ʧ�ܷ��ش�����
* @remarks �����᳡Ϊ���᳡ʱ���ɲ���
*/
u16 CCommonInterface::InviteCns( const TConfCallEpAddrList &tEp )
{  
    if ( tEp.m_wConfID == INVALID_WORD )
    {
        return ERR_CMS;
    }

   TConfCallEpAddr tadr;
   tadr.m_wConfID = tEp.m_wConfID;
   for ( u16 i = 0 ; i< tEp.m_tEpAdrLst.m_wNum; i++)
   {
		//���л᳡ֻ��E164��  ----JYY  2014.7.10
		if ( strcmp( tEp.m_tEpAdrLst.m_tCnsList[i].m_tAlias.m_abyAlias, "" ) == 0 )
		{
		   tadr.m_tAlias = tEp.m_tEpAdrLst.m_tCnsList[i].m_tE164;
		} 
		else
		{
		   tadr.m_tAlias = tEp.m_tEpAdrLst.m_tCnsList[i].m_tAlias;
		}
		InviteCns(tadr);
   }

   return NO_ERROR;
}



/*��  ��	�Ҷ�ĳ�᳡
��  ��	tConfEpInfo: eqID ����ID
����ֵ	�ɹ�����0,ʧ�ܷ��ط�0������
˵  ��	�����б�����Ȼ���ڸû᳡��ֻ�ǲ�����*/
u16 CCommonInterface::HangupCNS( const TConfEpID &tConfEpInfo ) 
{
	if ( NULL == m_pUmsConfCtrl ) 
	{
		return ERR_CMS;
	}
	
	u16 wRe = m_pUmsConfCtrl->HangupCNSReq(tConfEpInfo);
	return wRe;
}


/*��  ��	�ӻ������Ƴ�ĳ�᳡
��  ��	tConfEpInfo: eqID ����ID
����ֵ	�ɹ�����0,ʧ�ܷ��ط�0������
˵  ��	�����б��в����ڸû᳡ */
u16 CCommonInterface::RemoveCNS( const TConfEpID &tConfEpInfo ) 
{
	if ( NULL == m_pUmsConfCtrl ) 
	{
		return ERR_CMS;
	}
	
	u16 wRe = m_pUmsConfCtrl->RemoveCNSReq(tConfEpInfo);
	return wRe;
}


/*��  ��	���÷�����ϯ
��  ��	wConfID	 ����ID
����ֵ	�ɹ�����0,ʧ�ܷ��ط�0������
˵  ��	 */
u16 CCommonInterface::SetSpokeCns( const TConfEpID &tConfEpInfo ) 
{
    if ( NULL == m_pUmsConfCtrl ) 
    {
        return ERR_CMS;
    }
    
    u16 wRe = m_pUmsConfCtrl->SetSpokeCnsReq(tConfEpInfo);
    return wRe;
}


/**
* ����:	����Զ��cns����
* @param [int]  wConfID	 ����ID
* @param [int]  bQuiet  TRUE:����������FALSE��ֹͣ����
* @return  u16 �ɹ�����0,ʧ�ܷ��ط�0������
* @remarks  
*/
u16 CCommonInterface::SetQuietCns( const TConfEpID &tConfEpInfo, BOOL32 bQuiet)
{
    if ( NULL == m_pUmsConfCtrl ) 
    {
        return ERR_CMS;
    }
    
    u16 wRe = m_pUmsConfCtrl->SetQuietCnsReq(tConfEpInfo,bQuiet);
    return wRe;
}

/**
* ����:	����Զ��cns����
* @param [int]  wConfID	 ����ID
* @param [int]  bMute  TRUE:����������FALSE��ֹͣ����
* @return  u16 �ɹ�����0,ʧ�ܷ��ط�0������
* @remarks  
*/
u16 CCommonInterface::SetMuteCns( const TConfEpID &tConfEpInfo , BOOL32 bMute)
{
    if ( NULL == m_pUmsConfCtrl ) 
    {
        return ERR_CMS;
    }
    
    u16 wRe = m_pUmsConfCtrl->SetMuteCnsReq(tConfEpInfo,bMute);
    return wRe;
}




/**
* ����:	����Զ��cns����˫��
* @param [int]  wConfID	 ����ID
* @param [int]  bStart  TRUE:����˫����FALSE��ֹͣ˫��
* @return  u16 �ɹ�����0,ʧ�ܷ��ط�0������
* @remarks  
*/
u16 CCommonInterface::SetDualCns( const TConfEpID &tConfEpInfo, BOOL32 bStart )
{
    if ( NULL == m_pUmsConfCtrl ) 
    {
        return ERR_CMS;
    }
    
    u16 wRe = m_pUmsConfCtrl->SetDualCnsReq(tConfEpInfo,bStart);
    return wRe;
}


/*��  ��	���»����б�����
��  ��	tMixInfo	 �����б�
����ֵ	�ɹ�����0,ʧ�ܷ��ط�0������
˵  ��	 */
u16 CCommonInterface::UpdateAudMixList( const TConfAuxMixInfo &tMixInfoList ) 
{
	if ( NULL == m_pUmsConfCtrl ) 
	{
		return ERR_CMS;
	}
	
	u16 wRe = m_pUmsConfCtrl->UpdateAudMixListReq(tMixInfoList);
	return wRe;
}


u16 CCommonInterface::AudMixDisListOpr( const TTPDisListOpr &tDisListOpr )
{
	if ( NULL == m_pUmsConfCtrl ) 
	{
		return ERR_CMS;
	}
	
	u16 wRe = m_pUmsConfCtrl->AudMixDisListOprCmd( tDisListOpr );
	return wRe;
}


/*��  ��	������ѯ�б�����
��  ��	tTurnInfoList	 ��ѯ�б�
����ֵ	�ɹ�����0,ʧ�ܷ��ط�0������
˵  ��	 */
u16 CCommonInterface::UpdatePollList( const TConfTurnInfo &tTurnInfoList ) 
{
	if ( NULL == m_pUmsConfCtrl ) 
	{
		return ERR_CMS;
	}
	
	u16 wRe = m_pUmsConfCtrl->UpdatePollListReq(tTurnInfoList);
	return wRe;
}



// /*��  ��	�������� 
// ��  ��	wConfID	 ����ID
// ����ֵ	�ɹ�����0,ʧ�ܷ��ط�0������
// ˵  ��	 */
// u16 CCommonInterface::StartAuxMix( const u16 wConfID ) 
// {
// 	if ( NULL == m_pUmsConfCtrl ) 
// 	{
// 		return ERR_CMS;
// 	}
// 	
// 	u16 wRe = m_pUmsConfCtrl->StartAuxMixReq(wConfID);
// 	return wRe;
// }
// 
// /*��  ��	ֹͣ���� 
// ��  ��	wConfID	 ����ID
// ����ֵ	�ɹ�����0,ʧ�ܷ��ط�0������
// ˵  ��	 */
// u16 CCommonInterface::StopAuxMix( const u16 wConfID ) 
// {
// 	if ( NULL == m_pUmsConfCtrl ) 
// 	{
// 		return ERR_CMS;
// 	}
// 	
// 	u16 wRe = m_pUmsConfCtrl->StopAuxMixReq(wConfID);
// 	return wRe;
// }


/*��  ��	������ѯ 
��  ��	wConfID	 ����ID
����ֵ	�ɹ�����0,ʧ�ܷ��ط�0������
˵  ��	 */
u16 CCommonInterface::StartPoll( const u16 wConfID ) 
{
	if ( NULL == m_pUmsConfCtrl ) 
	{
		return ERR_CMS;
	}
	
	u16 wRe = m_pUmsConfCtrl->StartPollReq(wConfID);
	return wRe;
}


/*��  ��  ֹͣ��ѯ 
��  ��	wConfID	 ����ID
����ֵ	�ɹ�����0,ʧ�ܷ��ط�0������
˵  ��	 */
u16 CCommonInterface::StopPoll( const u16 wConfID ) 
{
	if ( NULL == m_pUmsConfCtrl ) 
	{
		return ERR_CMS;
	}
	
	u16 wRe = m_pUmsConfCtrl->StopPollReq(wConfID);
	return wRe;
}

 
 
 
 


/*��  ��  ��ȡ�����cns�б�
��  ��	 
����ֵ	�ɹ����ػ�����Ϣָ��,ʧ�ܷ���NULL
˵  ��	 */
TplArray<TCnsInfo>* CCommonInterface::GetConfCnsList( const u16 wConfID )    
{    
 
	if ( !IsInConf() )
	{
		return NULL;   
	} 

	return &m_tConfInfo.m_tplCnsList;
}

LRESULT CCommonInterface::OnRefreshConf( WPARAM wParam, LPARAM lParam ) 
{ 
	
	if ( NULL == m_pUmsConfCtrl ) 
	{
		return ERR_CMS;
	} 
 
   m_tConfInfo.Clear();
   m_pUmsConfCtrl->GetConf( m_tConfInfo );
    

 	CMsgDispatch::SendMessage(UI_UMS_UPDATE_CONFINFO ,wParam,lParam);
    

	return 0;
}


LRESULT CCommonInterface::OnSpeakerNotify( WPARAM wParam, LPARAM lParam ) 
{ 
     
    if ( NULL == m_pUmsConfCtrl ) 
    {
        return ERR_CMS;
    } 
    
     
    u16 wRe = m_pUmsConfCtrl->GetConf( m_tConfInfo ); 

    CMsgDispatch::SendMessage(UI_UMS_CHANGE_SPEAKER_NOTIFY,wParam,lParam);
    return wRe;
}



LRESULT CCommonInterface::OnRefreshConfCnsLst ( WPARAM wParam, LPARAM lParam ) 
{   
	u16 wConfID =  (u16)wParam;
	if ( wConfID <0  || NULL == m_pUmsConfCtrl) 
	{
		return ERR_CMS;
	}

   
   m_tConfInfo.Clear();
   u16 wRe = m_pUmsConfCtrl->GetConf( m_tConfInfo );  
 

	CMsgDispatch::SendMessage(UI_UMS_REFRESH_CONFCNS_LIST,wParam,lParam); 

	return wRe;
}

LRESULT CCommonInterface::OnRefreshConfAudMixLst ( WPARAM wParam, LPARAM lParam ) 
{
	u16 wConfID =  (u16)wParam;
	if ( wConfID <0  || NULL == m_pUmsConfCtrl) 
	{
		return ERR_CMS;
	}
	
  
	
	m_tConfInfo.m_bStartAudmix = (BOOL32)lParam;
	u16 wRe = m_pUmsConfCtrl->GetConfAudmixList(  m_tConfInfo.m_tAudmixList  );  
	CMsgDispatch::SendMessage(UI_UMS_REFRESH_CONFAUDMIX_LIST,wParam,lParam);
 
	return  wRe;
} 

LRESULT CCommonInterface::OnRefreshConfPollLst ( WPARAM wParam, LPARAM lParam ) 
{
	u16 wConfID =  (u16)wParam;
	if ( wConfID <0  || NULL == m_pUmsConfCtrl) 
	{
		return ERR_CMS;
    } 
	 

	m_tConfInfo.m_tplPollList.Clear();
	u16 wRe = m_pUmsConfCtrl->GetConfPollList(  m_tConfInfo.m_tplPollList  );  
	CMsgDispatch::SendMessage(UI_UMS_REFRESH_CONFPOLL_LIST,wParam,lParam);
 
	return  wRe;
} 



/* ���÷����˽��
			wParam = confID 
			lparam =  EmTpApplySpeakerRet*/
LRESULT CCommonInterface::OnSetSpeakerRsp( WPARAM wParam, LPARAM lParam ) 
{
    u16 wConfID =  (u16)wParam;
    if ( wConfID <0  || NULL == m_pUmsConfCtrl) 
    {
        return ERR_CMS;
    }
    
   
    u16 wRe = m_pUmsConfCtrl->GetConf(m_tConfInfo);
    
    CMsgDispatch::SendMessage(UI_UMS_SET_SPEAKER_RSP,wParam,lParam);
     
    return  wRe;
}  


LRESULT CCommonInterface::OnSetMuteCnsRsp( WPARAM wParam, LPARAM lParam )
{
    u16 wConfID =  (u16)wParam;
    if ( wConfID <0  || NULL == m_pUmsConfCtrl) 
    {
        return ERR_CMS;
    }
    
   
    
    u16 wRe = m_pUmsConfCtrl->GetConf(m_tConfInfo);
    
    CMsgDispatch::SendMessage(UI_UMS_SET_MUTE_CNS_RSP,wParam,lParam);
    
    return  wRe;
}   


LRESULT CCommonInterface::OnSetSlienceCnsRsp( WPARAM wParam, LPARAM lParam )
{
    u16 wConfID =  (u16)wParam;
    if ( wConfID <0  || NULL == m_pUmsConfCtrl) 
    {
        return ERR_CMS;
    }
    
    
    
    u16 wRe = m_pUmsConfCtrl->GetConf (m_tConfInfo);
    
    CMsgDispatch::SendMessage(UI_UMS_SET_QUIET_CNS_RSP,wParam,lParam);
    
    return  wRe;
}  


LRESULT CCommonInterface::OnSetDaulCnsRsp( WPARAM wParam, LPARAM lParam )
{
    u16 wConfID =  (u16)wParam;
    if ( wConfID <0  || NULL == m_pUmsConfCtrl) 
    {
        return ERR_CMS;
    }
    
    
    u16 wRe = m_pUmsConfCtrl->GetConf (m_tConfInfo );
    
    CMsgDispatch::SendMessage(UI_UMS_SET_DUAL_CNS_RSP,wParam,lParam);
    
    return  wRe;
} 

  
LRESULT CCommonInterface::OnDaulCnsUpdateNotify( WPARAM wParam, LPARAM lParam )
{
    u16 wConfID =  (u16)wParam;
    if ( wConfID <0  || NULL == m_pUmsConfCtrl) 
    {
        return ERR_CMS;
    }
     
    
    u16 wRe = m_pUmsConfCtrl->GetConf (m_tConfInfo);
    
    CMsgDispatch::SendMessage(UI_UMS_DUAL_CNS_NOTIFY,wParam,lParam);
    
    return  wRe;
}  

 
