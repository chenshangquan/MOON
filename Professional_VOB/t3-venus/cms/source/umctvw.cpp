/*****************************************************************************
模块名      : CMS控制台
文件名      : umctvw.cpp
相关文件    : commoninterface.h
文件实现功能: 封装了umclib和cnclib接口，本文件主要封装电视墙相关接口
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

/*
//获取电视墙预案列表
TplArray<TCmsTvwInfo>* CCommonInterface::GetTvwList()   
{
    return &m_tplTvwList;   
}

/**
* 功能:  判断cns是否在电视墙上
* @return 成功返回会场名,失败返回NULL
* @remarks 

BOOL32 CCommonInterface::IsCnsInTvw( s8 *abyCnsAliars )
{   
    if ( abyCnsAliars == NULL )
    {
        return false;
    }


    int nCount = m_tplTvwList.Size();
    for ( int i = 0; i< nCount; i++ )
    {
        if ( strcmp(m_tplTvwList.GetAt(i).m_achAlias, abyCnsAliars) == 0 )
        {  
            if ( m_tplTvwList.GetAt(i).m_bIsOnline )
            {
                return TRUE;
            }
            else
            {
                return FALSE;
            }
            
        }
    }

    
    return false;
}

TCmsTvwInfo *CCommonInterface::GetTvwInfoByHandleID( const u32 dwHandleID ) const
{
    int nCount = m_tplTvwList.Size();
    for ( int i = 0; i< nCount; i++ )
    {
        if (  m_tplTvwList.GetAt(i).m_dwChannelHandle == dwHandleID )
        {
            return &m_tplTvwList.GetAt(i);
        }
    }
   return NULL;
}
*/ 

/*
//播放电视墙预案
u16 CCommonInterface::PlayTvw( const TTPHduPlayReq & tTvwInfo )
{
    if ( NULL == m_pTvwCtrl ) 
    {
        return ERR_CMS;
    }
    
    return  m_pTvwCtrl->PlayHduReq(tTvwInfo);
}


//删除电视墙预案
u16 CCommonInterface::DeleteTvw( const TTPHduPlayReq & tTvwInfo ) 
{
    if ( NULL == m_pTvwCtrl ) 
    {
        return ERR_CMS;
    }
    
   return  m_pTvwCtrl->StopHduReq(tTvwInfo);
    
}

LRESULT CCommonInterface::OnRefreshTvw(WPARAM wParam, LPARAM lParam)
{
    if ( NULL == m_pTvwCtrl ) 
    {
        return ERR_CMS;
    }
    
    m_tplTvwList.Clear();
    m_pTvwCtrl->GetTvwLst(  m_tplTvwList );

//     int nCount = m_tplTvwList.Size();
//     for( int i = 0; i < nCount ; i++)
//     {
//         PrtMsg(0,emEventTypeCmsWindow,"ChannelHandle=%d, achAlias=%s, bOnline=%d , bHaveCodeStream=%d", 
//             m_tplTvwList.GetAt(i).m_dwChannelHandle, m_tplTvwList.GetAt(i).m_achAlias,m_tplTvwList.GetAt(i).m_bIsOnline ,m_tplTvwList.GetAt(i).bCodeStream) ; 
//     }
 
    CMsgDispatch::SendMessage( UI_UMS_REFRESH_TVW_LIST_NOTITFY, wParam, lParam );
    return NO_ERROR;
}

LRESULT CCommonInterface::OnPlayHduRsp(WPARAM wParam, LPARAM lParam)
{
    if ( NULL == m_pTvwCtrl ) 
    {
        return ERR_CMS;
    }
    
    m_tplTvwList.Clear();
    m_pTvwCtrl->GetTvwLst(  m_tplTvwList );
    
    CMsgDispatch::SendMessage( UI_UMS_PLAY_HDU_RSP, wParam, lParam );
    return NO_ERROR;
}

 
LRESULT CCommonInterface::OnStopHduRsp(WPARAM wParam, LPARAM lParam)
{
    if ( NULL == m_pTvwCtrl ) 
    {
        return ERR_CMS;
    }
    
    m_tplTvwList.Clear();
    m_pTvwCtrl->GetTvwLst(  m_tplTvwList );
    
    CMsgDispatch::SendMessage( UI_UMS_STOP_PLAY_HDU_RSP, wParam, lParam );
    return NO_ERROR;
} 
     
LRESULT CCommonInterface::OnHduCodeStreamNotify(WPARAM wParam, LPARAM lParam)
{
    if ( NULL == m_pTvwCtrl ) 
    {
        return ERR_CMS;
    }
    
    m_tplTvwList.Clear();
    m_pTvwCtrl->GetTvwLst(  m_tplTvwList );
    
    CMsgDispatch::SendMessage( UI_UMS_HDU_CODE_STREAM_NOTIFY, wParam, lParam );
    return NO_ERROR;
}
*/