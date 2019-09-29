// cncuserctrl.h: interface for the CCncUserCtrl class.
//
//////////////////////////////////////////////////////////////////////
#if !defined(AFX_USERCTRL_H__EB116E65_7B63_4B3E_B267_9C0B112DA0C1__INCLUDED_)
#define AFX_USERCTRL_H__EB116E65_7B63_4B3E_B267_9C0B112DA0C1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "cnsSession.h"

class CCncUserCtrl :public CCncUserCtrlIF 
{  

/** @defgroup  �����û��ӿ�ʵ�ֲ���
 *  @{
 */
public:
    CCncUserCtrl( CCnsSession &cSession );
	virtual ~CCncUserCtrl();
 
  /**
    * ����:	 ��ȡ�û��б�
	* @param [out]  tplUserList	 �û��б�
	* @return  u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks 
	*/
	virtual u16  GetUserList( TplArray<CUserFullInfo>& tplUserList) const;
 
	
   /**
    * ����:	 	����û�
	* @param [in]  tUser	 �û� 
	* @return  u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks ��Ϣ��CMS->UMS  ev_UMSAddUserReq ����Ϣֱ����OSP���ͣ�������XML����� \n
	                   Ӧ�ظ�:UMS->CMS   ev_UMSAddUserRet \n
	                   ���ɹ�����Ӧ�ظ�:UMS->CMS   ev_UmsAddUser_Notify
	*/
	virtual u16  AddUserReq( const CUserFullInfo& tUser ) ;


  
  /**
    * ����:	 	�޸��û�
	* @param [in]  tUser	 �û� 
	* @return  u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks  ��Ϣ��CMS->UMS  ev_UMSChangePWDReq ����Ϣֱ����OSP���ͣ�������XML����� \n
                    	Ӧ�ظ�:��UMS->CMS   ev_UMSAddUserRet \n
	                    ���ɹ�����Ӧ�ظ�:��UMS->CMS   ev_UmsUpdateUser_Notify
	*/
	virtual u16  ModifyUserReq( const CUserFullInfo& tUser ) ;

	
 
  /**
    * ����:	  ɾ���û�
	* @param [out]  tUser	 �û� 
	* @return  u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks  ��Ϣ��CMS->UMS  ev_UMSDelUserReq ����Ϣֱ����OSP���ͣ�������XML�����  \n
                     	Ӧ�ظ�: UMS->CMS   ev_UMSDelUserRet \n
		            	���ɹ�����Ӧ�ظ�: UMS->CMS   ev_UmsDelUser_Notify  
	*/
	virtual u16  DeleteUserReq( const CUserFullInfo& tUser );


protected:
 
  /**
    * ����:	  �û����֪ͨ��������ӡ�ɾ�����޸ģ�
	* @param [out]  cMsg	��Ϣ
	* @return  ��
	* @remarks   
	*/
	void  OnUserChangedNotify(const CMessage& cMsg);

  /**
    * ����:	  �����û�����ظ���������ӡ�ɾ�����޸ģ�
	* @param [in]  cMsg	��Ϣ
	* @return  ��
	* @remarks   
	*/
    void  OnOperateUserRsp(const CMessage& cMsg);

	virtual void DispEvent(const CMessage &cMsg);
	
    virtual void OnTimeOut(u16 wEvent); 
   

    void  OnLinkBreak(const CMessage& cMsg);
private:
 
	/**
    * ����:	  ע����Ϣ��Ӧ����
	* @param [in]  cMsg	��Ϣ
	* @return  ��
	* @remarks   
	*/
	void  BuildEventsMap();
   
 
  /**
    * ����:	  �����û�������ȡ�û���Ϣ
	* @param [in]  wConfTemplateID��Ҫ���Ļ���ID�� 
	* @return  ��ȡ�����û����б��е�����
	* @remarks   
	*/
    s16  FindUserByName( char name[MAX_CHARLENGTH] );

private:
	CCnsSession *m_pSession;              
	TplArray<CUserFullInfo> m_tplUserList;   ///<�û��б�
 
/** @}*/ // �����û��ӿ�ʵ�ֲ���
};

#endif // !defined(AFX_USERCTRL_H__EB116E65_7B63_4B3E_B267_9C0B112DA0C1__INCLUDED_)
