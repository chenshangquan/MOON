/*****************************************************************************
ģ����      : CMS����̨
�ļ���      : umcconftemplate.cpp
����ļ�    : commoninterface.h
�ļ�ʵ�ֹ���: ��װ��umclib��cnclib�ӿڣ����ļ���Ҫ��װ����ģ����ؽӿ�
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

/*��  ��	��ȡģ���б�
��  ��	 
����ֵ  ����ģ���б�ָ��
˵  ��	  
TplArray<TTPConfTemplate>* CCommonInterface::GetConfTemplateList()   
{
	return &m_tplConfTempList;
}
*/
/*��  ��	���ݻ���ģ��ID��ȡ����ģ��
��  ��	wConfTemplateID������ģ��ID
����ֵ  ����ģ���б�ָ��
˵  ��	 
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
* ����:  ����һ������ģ��
* @param [in] temp	 Ҫ������ģ�� 
* @return 
    */  
void  CCommonInterface::InvalidConfTemp( TTPConfTemplate &temp) const 
{ 
    temp.Clear();
    memset( &temp.m_atAuxMixList,INVALID_WORD,sizeof(temp.m_atAuxMixList));
    temp.m_wID = INVALID_WORD;
}

/**
* ����:  ���ݻ���ģ��ID��cnsID ��ȡcns ������Ϣ
* @param [in] wConfTempID	 ����ģ��ID 
* @return	ID��Ӧ�Ļ���ģ��
 
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
/*��  ��	�޸Ļ���ģ��
��  ��	tConfTem������ģ�� 
����ֵ  0 ��ʾ��ums��������ɹ�����0 ��ʾ����ʧ��
˵  ��	 ������ģ���Ѵ��ڣ����޸ģ��������ڣ������
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

/*��  ��	��ӻ���ģ��
��  ��	tConfTem������ģ�� 
����ֵ  0 ��ʾ��ums��������ɹ�����0 ��ʾ����ʧ��
˵  ��	 
u16 CCommonInterface::AddConfTemplate( const TTPConfTemplate & tConfTem ) 
{
	if ( NULL == m_pConfTemplateCtrl ) 
	{
		return ERR_CMS;
	}
  
   u16 wRe = NO_ERROR;
 
   //e164 ���Ƿ��ظ�
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

/*��  ��	�޸Ļ���ģ��
��  ��	tConfTem������ģ�� 
����ֵ  0 ��ʾ��ums��������ɹ�����0 ��ʾ����ʧ��
˵  ��	 
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

/*��  ��	ɾ���Ļ���ģ��
��  ��	wConfTemplateID������ģ��ID 
����ֵ  0 ��ʾ��ums��������ɹ�����0 ��ʾ����ʧ��
˵  ��	 */
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

/*��  ��	����ģ������Ƿ��Ѵ���
��  ��	Alias:����ģ�����
����ֵ  TRUE�����ڣ�FALSE��������
˵  ��	 
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
 
/*��  ��	����ģ��E164���Ƿ��Ѵ���
��  ��	E164������ģ��E164��
����ֵ  TRUE�����ڣ�FALSE��������
˵  ��	 
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
* ����:  �жϻ���ģ�����ϯcns �Ƿ�Ϊ������cns
* @param [in] tConfTem:����ģ�� 
* @return  �ɹ�����0��ʧ�ܷ��ط�0������
* @remarks ��Ҫʹ�ø�ģ�忪��ʱ
  
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
* ����:  �жϻ���ģ�����ϯcns �Ƿ�Ϊ������cns
* @param [in] wConfTemID:����ģ��ID
* @return  �ɹ�����0��ʧ�ܷ��ط�0������
* @remarks ��Ҫʹ�ø�ģ�忪��ʱ
  
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


 /*��  ��	�жϻ���ģ��ı�����E164���Ƿ����
	��  ��	��Ҫ�����޸�ʱ�жϣ��Ҹ�ģ���ID������UMS����� ���õ� 
	����ֵ  �ɹ�����0��ʧ�ܷ��ط�0������
	˵  ��	 
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
          
//		   //���E164��
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