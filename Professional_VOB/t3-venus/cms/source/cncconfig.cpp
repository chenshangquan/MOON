/*****************************************************************************
模块名      : CMS控制台
文件名      : cncconfig.cpp
相关文件    : commoninterface.h
文件实现功能: 封装了umclib和cnclib接口，本文件主要封装CNS配置相关接口
作者        : 肖楚然
版本        : V1.0  Copyright(C) 2011-2012 KDC, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
  日  期      版本        修改人      修改内容
2011/05/10    1.0         肖楚然        创建
******************************************************************************/

#include "stdafx.h"
#include "cms.h"
#include "commoninterface.h"
#include "evcmslib.h"
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif



u16 CCommonInterface::CnsRegSipService(const TTPSipRegistrarCfg &tSipCfg)
{
    if( NULL == m_pCnsConfigCtrl )
	{
		return ERR_CMS;
	}
	
	u16 re  = m_pCnsConfigCtrl->RegSipService( tSipCfg );
	
	return re;
}

 
u16 CCommonInterface::CnsRegGkService( const TTPGKCfg &tCfg  )
{
    if( NULL == m_pCnsConfigCtrl )
    {
        return ERR_CMS;
    }
    
    u16 re  = m_pCnsConfigCtrl->RegGk( tCfg );
    
    return re;
}

u16 CCommonInterface::CnsUnRegSipService()
{
    if( NULL == m_pCnsConfigCtrl )
	{
		return ERR_CMS;
	}
	
	u16 re  = m_pCnsConfigCtrl->UnRegSipService();
	
	return re;
}


LRESULT CCommonInterface::OnCnsRegSigServNotify( WPARAM wParam, LPARAM lParam )
{
 	if( NULL == m_pCnsConfigCtrl )
    {
 		return ERR_CMS;
    }
    
    m_tSipRegCfg = m_pCnsConfigCtrl->GetSipRegCfg();

    CMsgDispatch::SendMessage( UI_CNS_REGSIP_NOTIFY, wParam, lParam ) ;

    return NO_ERROR;
}


LRESULT CCommonInterface::OnCnsEthnetInfoNotify( WPARAM wParam, LPARAM lParam )
{
    if( NULL == m_pCnsConfigCtrl )
    {
        return ERR_CMS;
    }
    
    m_tServEthnetInfo = m_pCnsConfigCtrl->GetEthnetCfg();

    CMsgDispatch::SendMessage( UI_CNS_ETHNETINFO_NOTIFY, wParam, lParam ) ;
    
    return NO_ERROR;
}


u16 CCommonInterface::UpdateEthnetCfg( const TTPEthnetInfo& tInfo )
{
	if( NULL == m_pCnsConfigCtrl )
	{
		return ERR_CMS;
	}
 
	u16 re  = m_pCnsConfigCtrl->UpdateEthnetCfg( tInfo );

	return re;
}


u16 CCommonInterface::GetEthnetCfg( TTPEthnetInfo& tInfo )
{
	if( NULL == m_pCnsConfigCtrl )
	{
		return ERR_CMS;
	}

	tInfo = m_tServEthnetInfo;

	return NO_ERROR;
}

u16 CCommonInterface::GetLocalCnsInfo( TTPCnsInfo& tCnsInfo ) const
{
	if ( NULL == m_pCnsConfigCtrl )
	{
		return ERR_CMS;
	}

	tCnsInfo = m_pCnsConfigCtrl->GetLocalCnsInfo();
	return NO_ERROR;
}

u16 CCommonInterface::GetLocalCnsList( vector<TTPCnsInfo>& vctCnsList ) const
{
	if ( NULL == m_pCnsConfigCtrl )
	{
		return ERR_CMS;	
	}

	vctCnsList = m_pCnsConfigCtrl->GetLocalCnsList();
	return NO_ERROR;
}

u16 CCommonInterface::UpdateCnsInfo( const TTPCnsInfo& tInfo, u8 byIndex )
{
	if ( NULL == m_pCnsConfigCtrl )
	{
		return ERR_CMS;	
	}
	
	u16 wRe = m_pCnsConfigCtrl->UpdateCnsInfo( tInfo, byIndex );
	return wRe;
}

u16 CCommonInterface::SetMainCns( s8* pbyRoomName )
{
	if ( NULL == m_pCnsConfigCtrl )
	{
		return ERR_CMS;
	}

	if ( NULL == pbyRoomName )
	{
		return ERR_CMS;
	}

	return m_pCnsConfigCtrl->SetMainCns( pbyRoomName );
}

const s8* CCommonInterface::GetMainCnsName()
{
	if ( NULL == m_pCnsConfigCtrl )
	{
		return NULL;
	}
	return m_pCnsConfigCtrl->GetMainCnsName();
}


 

BOOL32 CCommonInterface::IsCnsInConf( s8* achRoomName )  
{

	BOOL32 bInConf = IsInConf() ;
    if ( bInConf )
    {
        u16 wID = m_tConfInfo.GetCnsIDByAlias( achRoomName );
        if( wID != INVALID_WORD )
        {
            bInConf = TRUE;
        }
        else
        {
            bInConf = FALSE;
        }
             

    }

	return bInConf;
}


/**
* 功能:  本级cns是否是发言人
* @param [int]wConfID 会议信息 
* @return 成功返回TRUE,失败返回FALSE
* @remarks  
*/
BOOL32 CCommonInterface::IsLocalCnsSpeaker(  )  
{
     
    
    if (  IsInConf() )
    { 
        s8 *Alairs = m_tConfInfo.GetSpeakerAliars();
        if ( Alairs != NULL  )
        {
            TTPCnsInfo  tCnsInfo;
            GetLocalCnsInfo( tCnsInfo );
            if ( strcmp(tCnsInfo.m_achRoomName,Alairs) == 0 )
            {
                return TRUE;
            }
        }
    }

    return FALSE;
}

/**
* 功能:  多点会议中本地cns是否在发双流
* @param [int]wConfID 会议信息 
* @return 成功返回TRUE,失败返回FALSE
* @remarks  
*/
BOOL32 CCommonInterface::IsLocalCnsDualInConf( ) 
{
   
    if ( IsInConf() )
    {
        s8 *Alairs = m_tConfInfo.GetDualAliars();
        if ( Alairs != NULL  )
        {
            TTPCnsInfo  tCnsInfo;
            GetLocalCnsInfo( tCnsInfo );
            if ( strcmp(tCnsInfo.m_achRoomName,Alairs) == 0 )
            {
                return TRUE;
            }
        }
    }
    
    return FALSE;
}


 


 /**
	* 功能:  获取本地cns会议状态
	* @param [out]tConfInfo  本级cns参加的会议信息
	* @return 成功返回TRUE,失败返回FALSE
	* @remarks 
	*/
TTPCnsConfStatus CCommonInterface::GetLocalCnsConfState() const
{  
    TTPCnsConfStatus tConfStatus;
   	if ( NULL == m_pCnsConfCtrl )
    {
        return tConfStatus;
    }
	
   return m_pCnsConfCtrl->GetCnsConfStatus();
}
 
BOOL32 CCommonInterface::IsLocalCnsChairMan()  
{
    
    if( !IsInConf() )
    {
        return FALSE;
    }

    
    TTPCnsInfo tCnsInfo;
    GetLocalCnsInfo(tCnsInfo);  
    //TCnsInfo* pCns = m_tConfInfo.GetCnsInfoByID( m_tConfInfo.m_wDefaultChairMan );

    //if (pCns != NULL)
    {
		if ( strcmp(m_tConfInfo.m_tChairName.m_abyAlias, tCnsInfo.m_achRoomName) == 0 )
        {
			return TRUE;
        }
    }

    return FALSE;  
}


LRESULT CCommonInterface::OnCnsInfoNotify( WPARAM wParam, LPARAM lParam ) 
{
	if ( NULL == m_pCnsConfigCtrl )
	{
		return ERR_CMS;
	}
//	m_tCnsInfo = m_pCnsConfigCtrl->GetLocalCnsInfo();

	CMsgDispatch::SendMessage(UI_CNS_CNSINFO_NOTIFY,wParam,lParam);
	return NO_ERROR;
}


BOOL32 CCommonInterface::IsLocalCnsQuite()
{
	if ( NULL == m_pCnsConfCtrl )
	{
		return ERR_CMS;
	}
	return m_pCnsConfCtrl->IsLocalCnsQuite();
}


BOOL32 CCommonInterface::IsLocalCnsMute()
{
	if ( NULL == m_pCnsConfCtrl )
	{
		return ERR_CMS;
	}
	return m_pCnsConfCtrl->IsLocalCnsMute();
}


u16 CCommonInterface::SetLocalCnsQuite( BOOL bQuite )
{
	if ( NULL == m_pCnsConfCtrl )
	{
		return ERR_CMS;
	}
	return m_pCnsConfCtrl->SetCnsQutie( bQuite );
}


u16 CCommonInterface::SetLocalCnsMute( BOOL bMute )
{
	if ( NULL == m_pCnsConfCtrl )
	{
		return ERR_CMS;
	}
	return m_pCnsConfCtrl->SetCnsMute( bMute );
}


u16 CCommonInterface::AdjustInputVol( u8 byVolume )
{
	if ( NULL == m_pCnsConfCtrl )
	{
		return ERR_CMS;
	}
	return m_pCnsConfCtrl->AdjustInputVol( byVolume );
}


u16 CCommonInterface::AdjustOutputVol( u8 byVolume )
{
	if ( NULL == m_pCnsConfCtrl )
	{
		return ERR_CMS;
	}
	return m_pCnsConfCtrl->AdjustOutputVol( byVolume );
}

u8 CCommonInterface::GetInputVol()
{
	if ( NULL == m_pCnsConfCtrl )
	{
		return 0;
	}
	return m_pCnsConfCtrl->GetInputVol();
}

u8 CCommonInterface::GetOutputVol()
{
	if ( NULL == m_pCnsConfCtrl )
	{
		return 0;
	}
	return m_pCnsConfCtrl->GetOutputVol();
}

u16 CCommonInterface::SetCnsInnerSpeaker( u8 bySeatId )
{
	if ( NULL == m_pCnsConfCtrl )
	{
		return 0;
	}
	return m_pCnsConfCtrl->SetInnerSpeaker( bySeatId );
}

u8 CCommonInterface::GetCnsInnerSpeaker()
{
	if ( NULL == m_pCnsConfCtrl )
	{
		return 0;
	}
	return m_pCnsConfCtrl->GetInnerSpeaker();
}

u16 CCommonInterface::GetCnsScreenInfo( vector<TScreenInfo>& vctScreenInfo ) const
{	
	if ( NULL == m_pCnsConfCtrl )
	{
		return ERR_CMS;	
	}
	
	vctScreenInfo = m_pCnsConfCtrl->GetCnsScreenInfo();
	return NO_ERROR;
}


u16 CCommonInterface::GetCnsScreenInfoByID( u8 screenID, TScreenInfo& tScreenInfo ) const
{	
    if ( NULL == m_pCnsConfCtrl )
    {
        return ERR_CMS;	
    }
    
    vector<TScreenInfo> vctScreenInfo = m_pCnsConfCtrl->GetCnsScreenInfo();
    
    vector<TScreenInfo>::iterator it = vctScreenInfo.begin();
    while ( it != vctScreenInfo.end() )
    {
       if ( it->byScreenID == screenID )
       {
            tScreenInfo = *it;
            return NO_ERROR;
       }

       it++;
    }

    return ERR_CMS_NOT_FIND;
}


void CCommonInterface::ClearCnsScreenInfo()
{
	if ( NULL == m_pCnsConfCtrl )
	{
		return;	
	}
	
	m_pCnsConfCtrl->ClearCnsScreenInfo();
}


/** 功能   设置系统时间
 *  @return 成功返回会场名,失败返回NULL
 *  @remarks 
 */
 u16 CCommonInterface::UpdateSysTime( const TTPTime& time )
 {
   	if ( NULL == m_pCnsConfigCtrl )
	{
		return ERR_CMS;
	}
    return m_pCnsConfigCtrl->UpdateSysTime( time );
  
 }



/** 功能   获取系统时间
 *  @return 成功返回会场名,失败返回NULL
 *  @remarks 
 */
u16 CCommonInterface::ReqSysTime()
{
    if ( NULL == m_pCnsConfigCtrl )
	{
		return ERR_CMS;
	}
    return m_pCnsConfigCtrl->ReqSysTime( );
}

u16 CCommonInterface::UpgradeSerCmd( const TTPUpgradeSer& tUpgradeSer )
{
	if ( NULL == m_pPortDiagCtrl )
	{
		return ERR_CMS;
	}
	return m_pPortDiagCtrl->UpgradeSerCmd( tUpgradeSer );
}

u16 CCommonInterface::GetUpgradeSerInfo( TTPUpgradeSer& tUpgradeSer )
{
	if ( NULL == m_pPortDiagCtrl )
	{
		return ERR_CMS;
	}

	tUpgradeSer = m_pPortDiagCtrl->GetUpgradeSerInfo();
	return NO_ERROR;
}

u16 CCommonInterface::CallServerCmd( const TTPCallSerInfo& tCallSerInfo )
{
	if ( NULL == m_pPortDiagCtrl )
	{
		return ERR_CMS;
	}
	return m_pPortDiagCtrl->CallServerCmd( tCallSerInfo );
}

u16 CCommonInterface::GetCallServerInfo( TTPCallSerInfo& tCallSerInfo )
{
	if ( NULL == m_pPortDiagCtrl )
	{
		return ERR_CMS;
	}
	
	tCallSerInfo = m_pPortDiagCtrl->GetCallServerInfo();
	return NO_ERROR;
}

u16 CCommonInterface::GetDualSrcInfo( TDualSrcInfo& tDualSrcinfo )
{
    if ( NULL == m_pCnsConfigCtrl )
    {
        return ERR_CMS;
    }

    tDualSrcinfo = m_pCnsConfigCtrl->GetDualSrcInfo();
    return NO_ERROR;
}

u16 CCommonInterface::SelDualInputPort( EmVgaType emType )
{
    if ( NULL == m_pCnsConfigCtrl )
    {
        return ERR_CMS;
    }
    
    return m_pCnsConfigCtrl->SelDualInputPort( emType );
}

u16 CCommonInterface::SetDualPortInfo( const TVgaInfo& tVgaInfo, BOOL bDefault )
{
    if ( NULL == m_pCnsConfigCtrl )
    {
        return ERR_CMS;
    }
    
    return m_pCnsConfigCtrl->SetDualPortInfo( tVgaInfo, bDefault );
}

u16 CCommonInterface::UpdateNATCfg( const TTPNatCfg& tInfo )
{
	if( NULL == m_pCnsConfigCtrl )
	{
		return ERR_CMS;
	}
 
	u16 re  = m_pCnsConfigCtrl->UpdateNATCfg( tInfo );

	return re;
}

u16 CCommonInterface::GetNATCfg( TTPNatCfg& tInfo )
{
	if( NULL == m_pCnsConfigCtrl )
	{
		return ERR_CMS;
	}

	tInfo = m_pCnsConfigCtrl->GetNATCfg();

	return NO_ERROR;
}

u16 CCommonInterface::GetNetMngData( vector<TTPNMServerCfg> &vecTTPNMServerCfg )
{
	if( NULL == m_pNetMngCtrl )
	{
		return ERR_CMS;
	}

	m_pNetMngCtrl->GetNetMngData( vecTTPNMServerCfg ); 

	return NO_ERROR;
}

u16 CCommonInterface::NetMngAddCmd( const TTPNMServerCfg& tTPNMServerCfg )
{
	if( NULL == m_pNetMngCtrl )
	{
		return ERR_CMS;
	}
	
	u16 wRe = m_pNetMngCtrl->NetMngAddCmd( tTPNMServerCfg );
	
	return wRe;
}

u16 CCommonInterface::NetMngModifyCmd( const TTPNMServerCfg& tTPNMServerCfg )
{
	if( NULL == m_pNetMngCtrl )
	{
		return ERR_CMS;
	}
		
	u16 wRe = m_pNetMngCtrl->NetMngModifyCmd( tTPNMServerCfg );
	
	return wRe;
}

u16 CCommonInterface::NetMngDeleteCmd( const TTPNMServerCfg& tTPNMServerCfg )
{
	if( NULL == m_pNetMngCtrl )
	{
		return ERR_CMS;
	}
	
	u16 wRe = m_pNetMngCtrl->NetMngDeleteCmd( tTPNMServerCfg );
	
	return wRe;
}

u16 CCommonInterface::SetSysSleepInfo( const TCenDevSleepInfo& tCenDevSleepInfo )
{
    if ( NULL == m_pCnsConfigCtrl )
    {
        return ERR_CMS;
    }
    
    return m_pCnsConfigCtrl->SetSysSleepInfo( tCenDevSleepInfo );
}

u16 CCommonInterface::GetSysSleepInfo( TCenDevSleepInfo& tCenDevSleepInfo )
{
    if ( NULL == m_pCnsConfigCtrl )
    {
        return ERR_CMS;
    }
	
    tCenDevSleepInfo = m_pCnsConfigCtrl->GetSysSleepInfo();
    return NO_ERROR;
}
