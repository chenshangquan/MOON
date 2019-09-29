/*****************************************************************************
ģ����      : CMS����̨
�ļ���      : umsSession.h
����ļ�    : 
�ļ�ʵ�ֹ���: һ��ums�ĻỰ,1.����UMS 2.����������ӹ��̣��ж����򷢳�֪ͨ 3.��������ֱ�Ӻ�UMS�����Ľӿڣ�������Ϣ�ȣ�
����        : �����
�汾        : V1.0  Copyright(C) 2011-2012 KDC, All rights reserved.
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��      �汾        �޸���      �޸�����
2011/4/25  1.0          �����      ����
******************************************************************************/

#if !defined(AFX_UMSSESSION_H__5CE4C0CD_7295_4920_931F_35AFEF812B15__INCLUDED_)
#define AFX_UMSSESSION_H__5CE4C0CD_7295_4920_931F_35AFEF812B15__INCLUDED_
#include "umclib.h" 
#include "msgdriver.h"
#include "umssessionctrlif.h"

#include "confTemplateCtrlIF.h"
#include "confCtrlIF.h"
#include "userCtrlIF.h"
#include "tvwCtrlIF.h"
#include "umsConfigCtrlIF.h"
#include "cncaddrbookif.h"
#include "umsexportCtrlIF.h"
#include "umssysinfoCtrlIF.h"
#include "umstvwboardCtrlIF.h"
#include "umsboardCtrlIF.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CUmsSession:public  CUmsSessionCtrlIF,
                  public  CMsgDriver
{

/** @defgroup  USMSession ʵ�ֲ���
 *  @{
 */

public:
	CUmsSession( u16 wAppID = AID_CMS2UMS_APP, BOOL bUseAddr = TRUE );
	virtual ~CUmsSession();

public: 

  /**
	* ����   ���ӵ�UMS 
	* @param [in]  dwIP	������UMS��IP��ַ��������
	* @param [in]  strUser �û���	
	* @param [in]  strPwd	����
	* @return u16 �ɹ�����0;ʧ�ܷ��ط�0������ 
	*/
	virtual u16 ConnectUms(u32 dwIP, u16 dwPort,  LPCTSTR pStrUserName,
	                        	 LPCTSTR pStrUserPswd, BOOL32 bConnect = TRUE);


  /**
    * ����:	�Ͽ���UMS������
	* @return  u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks	��û�����ӵ�UMSʱ���ô˷����������κ�����
	*/
	virtual u16 DisconnectUms() ; 


  /**
	* ����:	��ѯ�Ƿ��ʼ�����
	* @return  TRUE:��ʼ�����   FALSE:û�г�ʼ�����
    */
	virtual BOOL IsInitFinish();
  

	/**
	* ����:	��ѯ�Ƿ�������UMS
	* @return  TRUE 	������UMS    FALSE	û������UMS
    */
	virtual BOOL IsConnectedUms();



  /**
	* ����:	�û��Ƿ��ǹ���Ա
	* @return  TRUE�ǹ���Ա    FALSEһ���û�
	*/
	virtual BOOL IsManagerUser();
    




  /**
	* ����:	��ȡ�ӿ�ģ��
	* @param [out]  �ӿ�ģ���Ӧ��ָ��
	* @return  u16 �ɹ�����0,ʧ�ܷ��ط�0������
    */
    virtual u16 GetCtrlInterface(CConfTemplateCtrlIF **ppCtrl) const;
	virtual u16 GetCtrlInterface(CConfCtrlIF **ppCtrl) const;
	virtual u16 GetCtrlInterface(CTvwCtrlIF **ppCtrl) const;
	virtual u16 GetCtrlInterface(CUserCtrlIF **ppCtrl) const;
	virtual u16 GetCtrlInterface(CUmsConfigCtrlIF **ppCtrl) const;
	virtual u16 GetCtrlInterface(CCncAddrbookIF **ppCtrl) const;
	virtual u16 GetCtrlInterface(CUmsSysInfoCtrlIF **ppCtrl) const;
	virtual u16 GetCtrlInterface(CUmsExportCtrlIF **ppCtrl) const;
	virtual u16 GetCtrlInterface(CUmsTvwBoardCtrlIF **ppCtrl) const;
	virtual u16 GetCtrlInterface(CUmsBoardCtrlIF **ppCtrl) const;
	virtual u16 GetCtrlInterface(CUmsNetMngCtrlIF **ppCtrl) const;
	virtual u16 GetCtrlInterface(CUmsVTRCtrlIF **ppCtrl) const;

	/**
	* ����:	��ȡums ��IP 
	* @return  u32  IP
    */
	virtual u32 GetUmsIP();

    
  /**
	* ����:	��ȡ���� ��IP 
	* @return  u32  IP
    */
	virtual u32 GetLocalIP() ;


	/**
	* ����:	��ȡ��¼���û���Ϣ
	* @return   
    */
	virtual const CLoginRequest& GetConnectedUser();


  /**
	* ����:	��ums������Ϣ�ӿ� 
	* @param [in]  ��Ϣ����
	* @return  u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks һ������¸���Ϣ���Բ��ظ������ȷ����Ҫ�ظ���ʹ��postCommand()�ӿڷ���
    */
   	u16  PostMsg( u32 dwType  = TYPE_CMESSAGE ); 
  
  /**
	* ����:	��UI������Ϣ
	* @param [in]  ��Ϣ
	* @return  ��
	* @remarks һ������¸���Ϣ���Բ��ظ������ȷ����Ҫ�ظ���ʹ��postCommand()�ӿڷ���
    */
	virtual void DispEvent(const CMessage &cMsg)  ;
	virtual void OnTimeOut(u16 wEvent);
	
protected:
	void  OnLinkBreak( const CMessage& cMsg);
    void  OnConnectRsp( const CMessage& cMsg );
    void  OnGrabLoginNotify(const CMessage& cMsg);
	void  OnUmsCommonReasonInd(const CMessage& cMsg);
private:
	
 
  /**
	* ����:	��ʼ��OSP,����app 
	* @return  �ɹ�����0��ʧ�ܷ��ش�����  
    */
	virtual u16 InitializeLib( u16 wAppID = AID_CMS2UMS_APP );
 
  /**
	* ����:	ע����Ϣ��Ӧ����
	* @return  ��
    */
	void  BuildEventsMap();
	 
   
private: 
	BOOL32 m_bSelfInitOsp;  ///<�Ƿ�����������initosp
	BOOL32 m_bLogin;        ///<�Ƿ��Ѿ���¼
	u32    m_dwLocalIP;
	u32    m_dwUmsIp;
	BOOL32 m_bUseAdddr;     //�Ƿ�ʹ�õ�ַ��,Ĭ��ʹ��
	
    CConfTemplateCtrlIF *m_pConfTemplate;
	CConfCtrlIF         *m_pConf;
	CTvwCtrlIF          *m_pTvw;
	CUserCtrlIF         *m_pUser;
    CUmsConfigCtrlIF    *m_pConfig;
	CCncAddrbookIF      *m_pAddr;
	CUmsSysInfoCtrlIF   *m_pUmsSysInfo;
    CUmsExportCtrlIF    *m_pUmsExport;
	CUmsTvwBoardCtrlIF  *m_pUmsTvwBoard;
	CUmsBoardCtrlIF     *m_pUmsSingleBoard;
	CUmsNetMngCtrlIF    *m_pUmsNetMng;
	CUmsVTRCtrlIF		*m_pUmsVTR;
    CLoginRequest m_cUser; ///<�����֤

/** @}*/   //umsSessionʵ�ֲ���
};

#endif // !defined(AFX_UMSSESSION_H__5CE4C0CD_7295_4920_931F_35AFEF812B15__INCLUDED_)
