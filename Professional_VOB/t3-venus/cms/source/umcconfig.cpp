/*****************************************************************************
ģ����      : CMS����̨
�ļ���      : umcumsconfig.cpp
����ļ�    : commoninterface.h
�ļ�ʵ�ֹ���: ��װ��umclib��cnclib�ӿڣ����ļ���Ҫ��װums������ؽӿ�
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



u16 CCommonInterface::UmsRegSipService( const TTPSipRegistrarCfg &tSipCfg )
{
	if ( NULL == m_pUmsConfigCtrl ) 
	{
		return ERR_CMS;
	}

  u16 wRe =	m_pUmsConfigCtrl->RegSipService( tSipCfg );

  return wRe;
}


 

LRESULT CCommonInterface::OnUmsRegSigServNotify( WPARAM wParam, LPARAM lParam )
{  
	if ( NULL == m_pUmsConfigCtrl ) 
	{
		return ERR_CMS;
	}

	u16 wRe  = m_pUmsConfigCtrl->GetSipCfg( m_tSipRegCfg );
    
    CMsgDispatch::SendMessage( UI_UMS_REG_INFO_NOTIFY, wParam, lParam ) ;

	return wRe;
}

 
LRESULT CCommonInterface::OnUmsEthnetInfoNotify( WPARAM wParam, LPARAM lParam )
{
    if( NULL == m_pUmsConfigCtrl )
    {
        return ERR_CMS;
    }
    
    m_pUmsConfigCtrl->GetEthnetCfg( m_tServEthnetInfo );

    CMsgDispatch::SendMessage( UI_UMS_ETHNETINFO_NOTIFY, wParam, lParam ) ;

    return NO_ERROR;
}