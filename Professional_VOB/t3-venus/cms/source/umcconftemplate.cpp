/*****************************************************************************
模块名      : CMS控制台
文件名      : umcconftemplate.cpp
相关文件    : commoninterface.h
文件实现功能: 封装了umclib和cnclib接口，本文件主要封装会议模板相关接口
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

/*功  能	获取模板列表
参  数	 
返回值  返回模板列表指针
说  明	  
TplArray<TTPConfTemplate>* CCommonInterface::GetConfTemplateList()   
{
	return &m_tplConfTempList;
}
*/
/*功  能	根据会议模板ID获取会议模板
参  数	wConfTemplateID：会议模板ID
返回值  返回模板列表指针
说  明	 
TTPConfTemplate* CCommonInterface::GetConfTemplateByID( u16 wConfTemplateID ) const 
{
	 int nCont = m_tplConfTempList.Size();
	 for ( int i = 0 ; i< nCont; i++ )
	 {
         if ( m_tplConfTempList[i].m_wID == wConfTemplateID ) 
		 {
			 return &m_tplConfTempList[i];
			 break;
         }
     }
     
     return NULL;
}
*/ 
/**
* 功能:  废弃一个会议模板
* @param [in] temp	 要废弃的模板 
* @return 
    */  
void  CCommonInterface::InvalidConfTemp( TTPConfTemplate &temp) const 
{ 
    temp.Clear();
    memset( &temp.m_atAuxMixList,INVALID_WORD,sizeof(temp.m_atAuxMixList));
    temp.m_wID = INVALID_WORD;
}

/**
* 功能:  根据会议模板ID和cnsID 获取cns 别名信息
* @param [in] wConfTempID	 会议模板ID 
* @return	ID对应的会议模板
 
TTPAlias* CCommonInterface::GetCnsInfoFromTemplateByID( u16 wConfTemplateID , u16 wCnsID ) const 
{
    TTPConfTemplate *pTemp = GetConfTemplateByID( wConfTemplateID ) ;
    if ( pTemp == NULL  )
    {
        return NULL;
    }
  
    for ( int i = 0; i< pTemp->m_atEpList.m_wNum ; i++)
    {
        if ( pTemp->m_atEpList.m_tCnsList[i].m_wEpID == wCnsID )
        {
            return &(pTemp->m_atEpList.m_tCnsList[i].m_tAlias);
            break;
        }
    }
    
    return NULL;
}
*/ 
/*功  能	修改会议模板
参  数	tConfTem：会议模板 
返回值  0 表示向ums发送请求成功，非0 表示发送失败
说  明	 若会议模板已存在，则修改，若不存在，则添加
u16 CCommonInterface::ModifyConfTemplate( const TTPConfTemplate & tConfTem ) 
{
   if ( tConfTem.m_wID != INVALID_WORD )
   {
      return UpdateConfTemplate(tConfTem); 
   }
   else
     return AddConfTemplate(tConfTem); 
}
*/

/*功  能	添加会议模板
参  数	tConfTem：会议模板 
返回值  0 表示向ums发送请求成功，非0 表示发送失败
说  明	 
u16 CCommonInterface::AddConfTemplate( const TTPConfTemplate & tConfTem ) 
{
	if ( NULL == m_pConfTemplateCtrl ) 
	{
		return ERR_CMS;
	}
  
   u16 wRe = NO_ERROR;
 
   //e164 号是否重复
  // BOOL32 bE164Exist = IsConfTemplateE164Exist( tConfTem.m_achConfName );	

   BOOL32 bAliasExist = IsConfTemplateAliasExist( (s8*)tConfTem.m_achConfName );	
   if ( bAliasExist ) 
   {
	   wRe = ERR_CMS_CONFTEMP_ALIARS_REPEAT;
   }
   else
   {
	   wRe = m_pConfTemplateCtrl->AddConfTemplateReq( tConfTem );
   } 

   return wRe;
}*/

/*功  能	修改会议模板
参  数	tConfTem：会议模板 
返回值  0 表示向ums发送请求成功，非0 表示发送失败
说  明	 
u16 CCommonInterface::UpdateConfTemplate( const TTPConfTemplate & tConfTem )
{
	if ( NULL == m_pConfTemplateCtrl ) 
	{
		return ERR_CMS;
	}
   
    u16 wRe = CheckConfTemplateValidate( tConfTem );

	if ( NO_ERROR == wRe ) 
	{
	   wRe = m_pConfTemplateCtrl->ModifyConfTemplateReq( tConfTem );
	}
	
	return  wRe;
}
*/

/*功  能	删除改会议模板
参  数	wConfTemplateID：会议模板ID 
返回值  0 表示向ums发送请求成功，非0 表示发送失败
说  明	 */
/*
u16 CCommonInterface::DeleteConfTemplate( const u16 wConfTemplateID )
{
	if ( NULL == m_pConfTemplateCtrl ) 
	{
		return ERR_CMS;
	}
	
   return m_pConfTemplateCtrl->DeleteConfTemplateReq( wConfTemplateID );
}
*/

LRESULT CCommonInterface::OnRefreshConfTemplateLst(  WPARAM wParam, LPARAM lParam )
{ 
	/*
	m_tplConfTempList.Clear();
	if ( NULL == m_pConfTemplateCtrl ) 
	{  
		return ERR_CMS;
	} 

	m_pConfTemplateCtrl->GetConfTemplateList( m_tplConfTempList );
  
	CMsgDispatch::SendMessage(UI_UMS_REFRESH_CONFTEMPLATE_LIST,wParam,lParam); 
	*/

	if ( NULL == m_pSipInfoCtrl )
	{
		return ERR_CMS;
	}

	m_vctConfTempList = m_pSipInfoCtrl->GetUmsRegInfo();

	CMsgDispatch::SendMessage( UI_CNS_REFRESH_CONFTEMPLATE_LIST, wParam, lParam ); 

	return NO_ERROR;
}

/*功  能	会议模板别名是否已存在
参  数	Alias:会议模板别名
返回值  TRUE：存在，FALSE：不存在
说  明	 
BOOL32  CCommonInterface::IsConfTemplateAliasExist( const s8* Alias   ) const
{
	int nCont = m_tplConfTempList.Size();
	for ( int i = 0 ; i< nCont; i++ )
	{
		if ( strcmp(m_tplConfTempList.GetAt(i).m_achConfName, Alias) == 0 ) 
		{
			return TRUE;
			break;
		}
	}
	
	 return FALSE;
}
*/
 
/*功  能	会议模板E164号是否已存在
参  数	E164：会议模板E164号
返回值  TRUE：存在，FALSE：不存在
说  明	 
BOOL32  CCommonInterface::IsConfTemplateE164Exist( const s8* E164  ) const
{
	int nCont = m_tplConfTempList.Size();
	for ( int i = 0 ; i< nCont; i++ )
	{
		if ( strcmp(m_tplConfTempList.GetAt(i).m_achConfE164, E164) == 0 ) 
		{
			return TRUE;
			break;
		}
	}
	
	 return FALSE;
}
*/


/**
* 功能:  判断会议模板的主席cns 是否为本地主cns
* @param [in] tConfTem:会议模板 
* @return  成功返回0，失败返回非0错误码
* @remarks 主要使用该模板开会时
  
u16 CCommonInterface::CheckConfTemplateChairMan( TCMSConfTemplate & tConfTem )  
{
    TTPCnsInfo cns;
    GetLocalCnsInfo( cns );
    TEpAddr * pAddr = tConfTem.GetCnsAddrByID( tConfTem.m_wDefaultChairMan );
    if ( pAddr!= NULL )
    {
        if (  strlen(cns.m_achRoomName) != 0 && strcmp(pAddr->m_tAlias.m_abyAlias, cns.m_achRoomName) == 0 )
        {
            return NO_ERROR;
        }
        
    }

    return ERR_CMS_TEMPLATE_CHAIRMAN_NOT_LOCAL_CNS;
}
*/
/**
* 功能:  判断会议模板的主席cns 是否为本地主cns
* @param [in] wConfTemID:会议模板ID
* @return  成功返回0，失败返回非0错误码
* @remarks 主要使用该模板开会时
  
u16 CCommonInterface::CheckConfTemplateChairMan( const u16 & wConfTemID )  
{
   TTPConfTemplate* pTemp = GetConfTemplateByID( wConfTemID );
   if ( pTemp != NULL )
   { 
       TCMSConfTemplate temp = *((TCMSConfTemplate*)pTemp)  ;
       return CheckConfTemplateChairMan( temp );
   }

   return ERR_CMS_CONFTEMP_UNEXIST ;

} 
*/


 /*功  能	判断会议模板的别名和E164号是否可用
	参  数	主要用于修改时判断，且该模板的ID必须是UMS分配的 可用的 
	返回值  成功返回0，失败返回非0错误码
	说  明	 
u16 CCommonInterface::CheckConfTemplateValidate( const TTPConfTemplate & tConfTem ) const
{
	int nCont = m_tplConfTempList.Size();
	for ( int i = 0 ; i< nCont; i++ )
	{   

		if ( tConfTem.m_wID != m_tplConfTempList.GetAt(i).m_wID)
		{
		   if ( strcmp(m_tplConfTempList.GetAt(i).m_achConfName, tConfTem.m_achConfName) == 0) 
		   {
			   return ERR_CMS_CONFTEMP_ALIARS_REPEAT;
		   }
          
//		   //检查E164号
           if ( strlen(tConfTem.m_achConfE164) > 0 && strcmp(m_tplConfTempList.GetAt(i).m_achConfE164, tConfTem.m_achConfE164) == 0) 
           {
               return ERR_CMS_CONFTEMP_E164_REPEAT;
		   }
 
		}    
	 
	}
	
	 return NO_ERROR;
}
*/


vector<TTPAlias>* CCommonInterface::GetConfTempList()
{
	return &m_vctConfTempList;
}

u16 CCommonInterface::UpdateConfTemplate()
{
	if ( NULL == m_pSipInfoCtrl ) 
	{
		return ERR_CMS;
	}

	return m_pSipInfoCtrl->ReqSipRegInfo( emGetRegInfoType_UMS );
}