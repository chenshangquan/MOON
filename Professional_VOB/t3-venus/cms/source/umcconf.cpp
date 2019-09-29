/*****************************************************************************
模块名      : CMS控制台
文件名      : umcconf.cpp
相关文件    : commoninterface.h
文件实现功能: 封装了umclib和cnclib接口，本文件主要封装会议控制相关接口
作者        : 俞锦锦
版本        : V1.0  Copyright(C) 2011-2012 KDC, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
日  期      版本        修改人      修改内容
2011/4/28  1.0          俞锦锦      创建
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
* 功能:  判断 是否为本地主cns
* @param strAliars 别名
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
* 功能:  判断 cns是否为 会议的主席
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
 

/*功  能  使用会议模板开会
参  数	achTempName 模板名
返回值  成功返回0，失败返回错误码
说  明	 */
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

 
	
/*功  能  开启一个即时会议
参  数	tCnsList :与会的终端列表 ,本会场为第一个成员，并设置为主会场
返回值  成功返回0，失败返回错误码
说  明	ums预存一个用于开启临时会议的会议模板（ID为0），该会议模板界面不显示*/
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
	tTPDialParam.tConfInfo.emDualVideoQualityLevel = emTPH264HP;		//界面不在配置HP和BP,此处固定HP  ---2014.5.21 JYY
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
 


/*功  能  挂断会议
参  数	dwConfID：会议ID
返回值  成功返回0，失败返回错误码
说  明	结束会议，注意检查该会议是否为临时会议，如果是临时会议，则需要删除模板 */
u16 CCommonInterface::HangupConf( )   
{   
	if ( NULL == m_pUmsConfCtrl ) 
	{
		return ERR_CMS;
	}
	
	u16 wRe = m_pUmsConfCtrl->HangupConfReq();
	return wRe;
}



/*功  能  邀请某会场参与会议
参  数	tEp:会场信息
返回值  成功返回0，失败返回错误码
说  明	当本会场为主会场时方可操作 */
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
* 功能:	呼叫会议中已经存在的cns会场加入某会议
* @param [int]  tEp	 会议和会场信息
* @return  u16 成功返回0,失败返回非0错误码
* @remarks 消息：cms->ums  evtp_CallEP_cmd  \n
应回复：ums->cms evtp_CallEP_result   \n
若成功，还应发：ums->cms evtp_UpdateConfCnsList_Notify
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
* 功能:  获取会议中cns的信息
* @param [in] tEp:会场信息
* @param [out] tCnsInfo:会场信息
* @return 成功返回0，失败返回错误码
* @remarks 当本会场为主会场时方可操作
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
* 功能:  邀请多个会场参与会议 
* @param [in] tEp:会场信息
* @return 成功返回0，失败返回错误码
* @remarks 当本会场为主会场时方可操作
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
		//呼叫会场只有E164号  ----JYY  2014.7.10
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



/*功  能	挂断某会场
参  数	tConfEpInfo: eqID 会议ID
返回值	成功返回0,失败返回非0错误码
说  明	会议列表中依然存在该会场，只是不在线*/
u16 CCommonInterface::HangupCNS( const TConfEpID &tConfEpInfo ) 
{
	if ( NULL == m_pUmsConfCtrl ) 
	{
		return ERR_CMS;
	}
	
	u16 wRe = m_pUmsConfCtrl->HangupCNSReq(tConfEpInfo);
	return wRe;
}


/*功  能	从会议中移除某会场
参  数	tConfEpInfo: eqID 会议ID
返回值	成功返回0,失败返回非0错误码
说  明	会议列表中不存在该会场 */
u16 CCommonInterface::RemoveCNS( const TConfEpID &tConfEpInfo ) 
{
	if ( NULL == m_pUmsConfCtrl ) 
	{
		return ERR_CMS;
	}
	
	u16 wRe = m_pUmsConfCtrl->RemoveCNSReq(tConfEpInfo);
	return wRe;
}


/*功  能	设置发言坐席
参  数	wConfID	 会议ID
返回值	成功返回0,失败返回非0错误码
说  明	 */
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
* 功能:	设置远程cns静音
* @param [int]  wConfID	 会议ID
* @param [int]  bQuiet  TRUE:开启静音，FALSE：停止静音
* @return  u16 成功返回0,失败返回非0错误码
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
* 功能:	设置远程cns哑音
* @param [int]  wConfID	 会议ID
* @param [int]  bMute  TRUE:开启哑音，FALSE：停止哑音
* @return  u16 成功返回0,失败返回非0错误码
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
* 功能:	设置远程cns发起双流
* @param [int]  wConfID	 会议ID
* @param [int]  bStart  TRUE:开启双流，FALSE：停止双流
* @return  u16 成功返回0,失败返回非0错误码
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


/*功  能	更新混音列表请求
参  数	tMixInfo	 混音列表
返回值	成功返回0,失败返回非0错误码
说  明	 */
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


/*功  能	更新轮询列表请求
参  数	tTurnInfoList	 轮询列表
返回值	成功返回0,失败返回非0错误码
说  明	 */
u16 CCommonInterface::UpdatePollList( const TConfTurnInfo &tTurnInfoList ) 
{
	if ( NULL == m_pUmsConfCtrl ) 
	{
		return ERR_CMS;
	}
	
	u16 wRe = m_pUmsConfCtrl->UpdatePollListReq(tTurnInfoList);
	return wRe;
}



// /*功  能	开启混音 
// 参  数	wConfID	 会议ID
// 返回值	成功返回0,失败返回非0错误码
// 说  明	 */
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
// /*功  能	停止混音 
// 参  数	wConfID	 会议ID
// 返回值	成功返回0,失败返回非0错误码
// 说  明	 */
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


/*功  能	开启轮询 
参  数	wConfID	 会议ID
返回值	成功返回0,失败返回非0错误码
说  明	 */
u16 CCommonInterface::StartPoll( const u16 wConfID ) 
{
	if ( NULL == m_pUmsConfCtrl ) 
	{
		return ERR_CMS;
	}
	
	u16 wRe = m_pUmsConfCtrl->StartPollReq(wConfID);
	return wRe;
}


/*功  能  停止轮询 
参  数	wConfID	 会议ID
返回值	成功返回0,失败返回非0错误码
说  明	 */
u16 CCommonInterface::StopPoll( const u16 wConfID ) 
{
	if ( NULL == m_pUmsConfCtrl ) 
	{
		return ERR_CMS;
	}
	
	u16 wRe = m_pUmsConfCtrl->StopPollReq(wConfID);
	return wRe;
}

 
 
 
 


/*功  能  获取会议的cns列表
参  数	 
返回值	成功返回会议信息指针,失败返回NULL
说  明	 */
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



/* 设置发言人结果
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

 
