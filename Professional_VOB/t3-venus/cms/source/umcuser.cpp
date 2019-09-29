/*****************************************************************************
ģ����      : CMS����̨
�ļ���      : umcuser.cpp
����ļ�    : commoninterface.h
�ļ�ʵ�ֹ���: ��װ��umclib��cnclib�ӿڣ����ļ���Ҫ��װ�û���ؽӿ�
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



/*��  ��	��ȡ�û��б�
��  ��	 
����ֵ  �ɹ������û��б�ָ�룬ʧ�ܷ��ؿ�
˵  ��	 */
TplArray<CUserFullInfo>* CCommonInterface::GetUserList()   
{
	return &m_tplUserList;
}


/*��  ��	����û�
��  ��	user
����ֵ  �ɹ�����0��ʧ�ܷ��ش�����
˵  ��	 */
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


/*��  ��	�޸��û���Ϣ
��  ��	user
����ֵ  �ɹ�����0��ʧ�ܷ��ش�����
˵  ��	 */
u16 CCommonInterface::UpdateUser( const CUserFullInfo& user )   
{
	if ( NULL == m_pCnsUserCtrl ) 
	{
		return ERR_CMS;
	}
	
	u16 wRe = m_pCnsUserCtrl->ModifyUserReq( user );
	
	return wRe;
}
 
/*��  ��	ɾ���û�
��  ��	user
����ֵ  �ɹ�����0��ʧ�ܷ��ش�����
˵  ��	 */
u16 CCommonInterface::DeleteUser( const CUserFullInfo & user )   
{
    if ( NULL == m_pCnsUserCtrl ) 
	{
		return ERR_CMS;
	}
	
	u16 wRe = m_pCnsUserCtrl->DeleteUserReq( user );
	
	return wRe;
}
 

/*��  ��	�����û�����ȡ�û���Ϣ
��  ��	pUserName
����ֵ  �ɹ������û���Ϣָ�룬ʧ�ܷ��ؿ�ָ��
˵  ��	 */
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



/*��  ��	�ж��û����Ƿ��Դ���
��  ��	pUserName
����ֵ  �ɹ�����TREU��ʧ�ܷ���FLASE
˵  ��	 */
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