/*****************************************************************************
ģ����      : umstool����ά������
�ļ���      : umsexportCtrl.h
����ļ�    : 
�ļ�ʵ�ֹ���: ums���뵼�������в���
����        : ����ӡ
�汾        : V1.0  Copyright(C) 2011-2012 KDC, All rights reserved.
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��      �汾        �޸���      �޸�����
2012/11/23  1.0         ����ӡ      ����
******************************************************************************/
#if !defined(AFX_EXPORTCTRL_H__EB116E65_7B63_4B3E_B267_9C0B112DA0C1__INCLUDED_)
#define AFX_EXPORTCTRL_H__EB116E65_7B63_4B3E_B267_9C0B112DA0C1__INCLUDED_

#include "umsexportCtrlIF.h"
#include "umsSession.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CUmsExportCtrl :public CUmsExportCtrlIF 
{  

/** @defgroup  ����ums���뵼���ӿ�ʵ�ֲ���
 *  @{
 */


	friend class CUmsSession;
private:
	CUmsExportCtrl( const CUmsExportCtrl &){};
    CUmsExportCtrl( CUmsSession &cUmsSession );
	
public:
    ~CUmsExportCtrl();
	
	/**
    * ����:  ��������ģ������
	* @param [in]	void
	* @return           u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks ��Ϣ��   CMS->UMS  ev_UMSAddUserReq ����Ϣֱ����OSP���ͣ�������XML����� \n
	                      Ӧ�ظ�:UMS->CMS   ev_UMSAddUserRet \n
	                      ���ɹ�����Ӧ�ظ�:UMS->CMS   ev_UmsAddUser_Notify
	*/
	virtual u16  ExportInfoReq();

	/**
    * ����:  �������ģ������
	* @param [in]	const s8* strFileName	 ����ģ���ļ����� 
	* @return           u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks ��Ϣ��   CMS->UMS  ev_UMSAddUserReq ����Ϣֱ����OSP���ͣ�������XML����� \n
	                      Ӧ�ظ�:UMS->CMS   ev_UMSAddUserRet \n
	                      ���ɹ�����Ӧ�ظ�:UMS->CMS   ev_UmsAddUser_Notify
	*/
	virtual u16  ImportInfoReq(const s8* strFileName);

	/**
    * ����:  ������Ȩ����
	* @param [in]	void
	* @return           u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks ��Ϣ��   CMS->UMS  ev_licenseOutput_req ����Ϣֱ����OSP���ͣ�������XML����� \n
	                      Ӧ�ظ�:UMS->CMS   ev_licenseOutput_Ind \n
	*/
	virtual u16  ExportAuthReq();

protected:
 
  /**
    * ����:	  
	* @param [out]  cMsg	��Ϣ
	* @return  ��
	* @remarks   
	*/
	void  OnExportInfoRsp(const CMessage& cMsg);

 
  /**
    * ����:	  
	* @param [in]  cMsg	��Ϣ
	* @return  ��
	* @remarks   
	*/
    void  OnImportInfoRsp(const CMessage& cMsg);

	/**
    * ����:	  
	* @param [out]  cMsg	��Ϣ
	* @return  ��
	* @remarks   
	*/
	void  OnExportAuthRsp(const CMessage& cMsg);

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

private:
	CUmsSession *m_pUmsSession;              
 
/** @}*/ // ����ums���뵼���ӿ�ʵ�ֲ���
};

#endif // !defined(AFX_EXPORTCTRL_H__EB116E65_7B63_4B3E_B267_9C0B112DA0C1__INCLUDED_)
