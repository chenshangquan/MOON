/*****************************************************************************
模块名      : CMS控制台
文件名      : umcuser.cpp
相关文件    : commoninterface.h
文件实现功能: 封装了umclib和cnclib接口，本文件主要封装用户相关接口
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



/*功  能	获取用户列表
参  数	 
返回值  成功返回用户列表指针，失败返回空
说  明	 */
TplArray<CUserFullInfo>* CCommonInterface::GetUserList()   
{
	return &m_tplUserList;
}


/*功  能	添加用户
参  数	user
返回值  成功返回0，失败返回错误码
说  明	 */
u16 CCommonInterface::AddUser( const CUserFullInfo& user )    
{
	if ( NULL == m_pCnsUserCtrl ) 
	{
		return ERR_CMS;
	}

	u16 wRe = NO_ERROR;

	BOOL32 bIexist = IsExistUser( (s8*)user.name );
   
	if ( bIexist ) 
	{
       wRe = ERR_CMS_UI_NAME_REPEAT;
	}
	else
	{
		wRe = m_pCnsUserCtrl->AddUserReq( user );
	} 

	return wRe;

}


/*功  能	修改用户信息
参  数	user
返回值  成功返回0，失败返回错误码
说  明	 */
u16 CCommonInterface::UpdateUser( const CUserFullInfo& user )   
{
	if ( NULL == m_pCnsUserCtrl ) 
	{
		return ERR_CMS;
	}
	
	u16 wRe = m_pCnsUserCtrl->ModifyUserReq( user );
	
	return wRe;
}
 
/*功  能	删除用户
参  数	user
返回值  成功返回0，失败返回错误码
说  明	 */
u16 CCommonInterface::DeleteUser( const CUserFullInfo & user )   
{
    if ( NULL == m_pCnsUserCtrl ) 
	{
		return ERR_CMS;
	}
	
	u16 wRe = m_pCnsUserCtrl->DeleteUserReq( user );
	
	return wRe;
}
 

/*功  能	根据用户名获取用户信息
参  数	pUserName
返回值  成功返回用户信息指针，失败返回空指针
说  明	 */
CUserFullInfo *CCommonInterface::GetUserByName (   s8 *pUserName ) const 
{
	s16 nCont = m_tplUserList.Size();
	for ( s16 i = 0; i< nCont; i++)
	{   
		bool re = m_tplUserList.GetAt(i).IsEqualName(pUserName);
		if ( re ) 
		{
			return &m_tplUserList.GetAt(i); 
		}
	}

	return NULL;
}



/*功  能	判断用户名是否以存在
参  数	pUserName
返回值  成功返回TREU，失败返回FLASE
说  明	 */
BOOL32 CCommonInterface::IsExistUser ( s8 *pUserName ) const 
{
	s16 nCont = m_tplUserList.Size();
	for ( s16 i = 0; i< nCont; i++)
	{  
		bool re = m_tplUserList.GetAt(i).IsEqualName(pUserName);
		if ( re ) 
		{
			return TRUE; 
		}
	}
	
	return FALSE;
}


LRESULT CCommonInterface::OnRefreshUserLst(  WPARAM wParam, LPARAM lParam )
{
	m_tplUserList.Clear();

	if ( NULL == m_pCnsUserCtrl ) 
	{
		return ERR_CMS;
	}

	u16 wRe = m_pCnsUserCtrl->GetUserList( m_tplUserList );

	CMsgDispatch::SendMessage(UI_UMS_REFRESH_USER_LIST,wParam,lParam);
	return wRe; 
} 