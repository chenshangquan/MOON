/*****************************************************************************
模块名      : CMS控制台
文件名      : umcumsconfig.cpp
相关文件    : commoninterface.h
文件实现功能: 封装了umclib和cnclib接口，本文件主要封装ums设置相关接口
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