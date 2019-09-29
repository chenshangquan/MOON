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


/**��Ե����
*  @param[in] 
*  @return  
*/
u16 CCommonInterface::MakeCall( TCnAddr& tCnAddr )
{
    if( NULL == m_pCnsConfCtrl )
    {
        return ERR_CMS;
    }


    TTPDialParam tTPDialParam;

    tTPDialParam.tCalledAddr = tCnAddr;
    //_snprintf( tTPDialParam.tCalledAddr.achAlias, sizeof(tTPDialParam.tCalledAddr.achAlias), "%s", pCalledCnsAliars );

    tTPDialParam.emProtocol = emTpSIP;
    tTPDialParam.emCallType = emTpInvite;
    //tTPDialParam.tCalledAddr.emType = emTpAlias; 
    //strncpy( (char*)tTPDialParam.tCalledAddr.achAlias, (char*)achIp, TP_MAX_H323ALIAS_LEN ); 
    tTPDialParam.tCalledAddr.wPort = TP_UMS_SIP_LISTIEN_PORT;
    
    tTPDialParam.tCallingAddr.emType = emTpAlias; 
    tTPDialParam.tCallingAddr.wPort = CNS_SIP_STACK_LISTION_PORT; 
   
    u16 re  = m_pCnsConfCtrl->MakeCall( tTPDialParam );
    
	return re;
}

/*TTPAlias.m_byType
tp_Alias_Unknow,
tp_Alias_e164,
tp_Alias_h323,
tp_Alias_IP,
*/

/*EmTPAddrType
emTpUnknown =0,
emTpIPAddr, 
emTpDomain,
emTpAlias,
emTpE164Num,
emTpIP6Addr
*/
u16 CCommonInterface::MakeCall(  const TTPAlias& tAlias )
{
    if( NULL == m_pCnsConfCtrl )
    {
        return ERR_CMS;
    } 
    
    TTPDialParam  tTPDialParam;
    

	switch ( tAlias.m_byType )
	{
	case tp_Alias_h323:
		tTPDialParam.tCalledAddr.emType = emTpAlias; 
		_snprintf( tTPDialParam.tCalledAddr.achAlias, sizeof(tTPDialParam.tCalledAddr.achAlias), "%s", tAlias.m_abyAlias );
		break;
	case tp_Alias_e164:
		tTPDialParam.tCalledAddr.emType = emTpE164Num;
		_snprintf( tTPDialParam.tCalledAddr.achE164, sizeof(tTPDialParam.tCalledAddr.achE164), "%s", tAlias.m_abyAlias );
		break;
	default:
		break;
	} 
    
    tTPDialParam.emProtocol = emTpSIP;
    tTPDialParam.emCallType = emTpInvite;
	  
    //  strncpy( (char*)tTPDialParam.tCalledAddr.achAlias, (char*)achIp, TP_MAX_H323ALIAS_LEN ); 
    tTPDialParam.tCalledAddr.wPort = TP_UMS_SIP_LISTIEN_PORT;
    
    tTPDialParam.tCallingAddr.emType = emTpAlias; 
    tTPDialParam.tCallingAddr.wPort = CNS_SIP_STACK_LISTION_PORT; 
    
    u16 wRe  = m_pCnsConfCtrl->MakeCall( tTPDialParam ); 
    
	return wRe;
}

 
u16 CCommonInterface::HungupPtpConf(  )
{
    if( NULL == m_pCnsConfCtrl )
    {
        return ERR_CMS;
    }

    return m_pCnsConfCtrl->HungupPtpConf();
}

/** 
* ����  ����ѡ��
* @param [in]  byScreenID  ����
* @param [in]  wEpID  ѡ����cnsID
* @return  
* @remarks 
*/
u16 CCommonInterface::SetSelView( u8 byScreenID, u16 wEpID ) 
{
    if( NULL == m_pCnsConfCtrl )
    {
        return ERR_CMS;
    }
    
    u16 re  = m_pCnsConfCtrl->SetSelView( byScreenID, wEpID );
    
	return re;
}


/** 
* ����  ����ѡ��
* @param [in]  byScreenID  ����
* @param [in]  wEpID  ѡ����cnsID
* @return  
* @remarks 
*/
u16 CCommonInterface::CancleSelView( u8 byScreenID ) 
{
    if( NULL == m_pCnsConfCtrl )
    {
        return ERR_CMS;
    }
    
    u16 re  = m_pCnsConfCtrl->CancleSelView( byScreenID );
    
	return re;
}



/** 
* ����  ����/ֹͣ��ѯ
* @param [in]  bStart   true:������false���ر�
* @return  
* @remarks 
*/
u16 CCommonInterface::StartPoll( BOOL  bStart )
{
    if( NULL == m_pCnsConfCtrl )
    {
        return ERR_CMS;
    }
    
    u16 re  = m_pCnsConfCtrl->StartPoll( bStart );
    
	return re;

}

BOOL CCommonInterface::IsLocalCnsPoll()
{
    if( NULL == m_pCnsConfCtrl )
    {
        return ERR_CMS;
    }
     
	return m_pCnsConfCtrl->IsLocalCnsPoll();
}

/** 
* ����  ����/ֹͣ˫��
* @param [in]  bStart   true:������false���ر�
* @return  
* @remarks 
*/
u16 CCommonInterface::StartDual( BOOL  bStart )
{
    if( NULL == m_pCnsConfCtrl )
    {
        return ERR_CMS;
    }
    
	u16 wRe = 0;
	TCMSConf tConfInfo;
	BOOL32 bInConf = BusinessManagePtr->IsInConf( &tConfInfo );
	if ( bInConf )
	{
		 
	//	if ( tConfInfo.m_wConfID == INVALID_WORD )
        {
			wRe = m_pCnsConfCtrl->StartDual( bStart );
		}
// 		else
// 		{
// 			TConfEpID  tConfEpInfo;
// 			tConfEpInfo.m_wConfID = tConfInfo.m_wConfID;
// 			tConfEpInfo.m_wEpID = tConfInfo.m_wDefaultChairMan;
// 
// 			wRe = BusinessManagePtr->SetDualCns( tConfEpInfo, bStart);
// 		}
	}
       
	return wRe;
}


BOOL CCommonInterface::IsLocalCnsDual() const
{
    if( NULL == m_pCnsConfCtrl )
    {
        return ERR_CMS;
    }

	BOOL32 bInDual = FALSE;

	TCMSConf tConfInfo;
	BOOL32 bRe = BusinessManagePtr->IsInConf( &tConfInfo );
	if ( bRe )
	{   
		//��Ե����ȡ��CNS��������ȡ��UMS
// 		if ( tConfInfo.m_emConfType == emCallType_P2P )
//         {
			bInDual = m_pCnsConfCtrl->IsLocalCnsDual();
// 		}
// 		else
// 		{
// 			bInDual = BusinessManagePtr->IsLocalCnsDualInConf( );
// 		}
	}
	else
	{
		bInDual = FALSE;
	}
	
	return bInDual;
}


//��������
u16 CCommonInterface::StartDualCodeStream(   const TTPCnMediaTransPort  &tVedioTransAddr, const TTPCnMediaTransPort  &tAudioTransAddr  ) const  
{
    if( NULL == m_pCnsConfCtrl )
    {
        return ERR_CMS;
    }  
    
     
	u16 wRe = m_pCnsConfCtrl->StartDualCodeStream( tVedioTransAddr , tAudioTransAddr);

    return wRe;
}

u16 CCommonInterface::StopDualCodeStream() const
{
    if( NULL == m_pCnsConfCtrl )
    {
        return ERR_CMS;
    }  
    
    
    u16 wRe = m_pCnsConfCtrl->StopDualCodeStream( );
    
    return wRe;
}

u16 CCommonInterface::ReqKeyFrame( BOOL32 bForce ) const
{
    if( NULL == m_pCnsConfCtrl )
    {
        return ERR_CMS;
    }  
    
    
    u16 wRe = m_pCnsConfCtrl->ReqKeyFrame( bForce );
    
    return wRe;
}

TTPCnMediaTransPort CCommonInterface::GetVedioTransAddr() const  
{
    TTPCnMediaTransPort tAdddr;
    if( NULL == m_pCnsConfCtrl )
    {
        return  tAdddr;
    } 
    
    tAdddr = m_pCnsConfCtrl->GetVedioTransAddr( );

    return tAdddr;
}

 
TTPCnMediaTransPort CCommonInterface::GetAudioTransAddr() const  
{
    TTPCnMediaTransPort tAdddr;
    if( NULL == m_pCnsConfCtrl )
    {
        return  tAdddr;
    } 
    
    tAdddr = m_pCnsConfCtrl->GetAudioTransAddr( );
    
    return tAdddr;
}


 
u16 CCommonInterface::ScrnDisplayDual( const u16 wScrnID ) const  
{
    if( NULL == m_pCnsConfCtrl )
    {
        return ERR_CMS;
    }  
    
    
    u16 wRe = m_pCnsConfCtrl->ScrnDisplayDual( wScrnID );
    
    return wRe;
}

 
u16 CCommonInterface::ScrnStopDisplayDual( const u16 wScrnID ) const 
{
    if( NULL == m_pCnsConfCtrl )
    {
        return ERR_CMS;
    }  
    
    
    u16 wRe = m_pCnsConfCtrl->ScrnStopDisplayDual( wScrnID );
    
    return wRe;
}
 
 
u16 CCommonInterface::ScrnDisplayLocal( const u16 wScrnID ) const  
{
    if( NULL == m_pCnsConfCtrl )
    {
        return ERR_CMS;
    }  
    
    
    u16 wRe = m_pCnsConfCtrl->ScrnDisplayLocal( wScrnID );
    
    return wRe;
}
 
u16 CCommonInterface::ScrnStopDisplayLocal( const u16 wScrnID ) const 
{
    if( NULL == m_pCnsConfCtrl )
    {
        return ERR_CMS;
    }  
    
    
    u16 wRe = m_pCnsConfCtrl->ScrnStopDisplayLocal( wScrnID );
    
    return wRe;
}

BOOL32 CCommonInterface::IsRcvDual() const 
{
    if( NULL == m_pCnsConfCtrl )
    {
        return FALSE;
    }  
    
    
    return  m_pCnsConfCtrl->IsRcvDual(  );
    
}

u16 CCommonInterface::ViewLocalPIPCmd( const u8 byScrnID, const BOOL bLocalP )
{
	if( NULL == m_pCnsConfCtrl )
    {
        return FALSE;
    } 
	u16 re = m_pCnsConfCtrl->ViewLocalPIPCmd( byScrnID, bLocalP );
	return re;
}

u16 CCommonInterface::SetSelTVSView( u8 byScreenID )
{
	if( NULL == m_pCnsConfCtrl )
    {
        return ERR_CMS;
    }
    
    u16 re  = m_pCnsConfCtrl->SelTVSView( byScreenID );
    
	return re;
}

u16 CCommonInterface::CancleSelTVSView( u8 byScreenID )
{
	if( NULL == m_pCnsConfCtrl )
    {
        return ERR_CMS;
    }
    
    u16 re  = m_pCnsConfCtrl->CancelSelTVSView( byScreenID );
    
	return re;
}
