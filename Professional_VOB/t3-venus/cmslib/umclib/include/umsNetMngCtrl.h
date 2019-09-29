/*****************************************************************************
ģ����      : umstool����ά������
�ļ���      : umsNetMngCtrl.h
����ļ�    : 
�ļ�ʵ�ֹ���: ums���ܵ����в���
����        : ʯ��
�汾        : V1.0  Copyright(C) 2011-2012 KDC, All rights reserved.
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��      �汾        �޸���      �޸�����
2013/1/8    1.0         ʯ��         ����
******************************************************************************/
#if !defined(AFX_NETMNGCTRL_H__EB116E65_7B63_4B3E_B267_9C0B112DA0C1__INCLUDED_)
#define AFX_NETMNGCTRL_H__EB116E65_7B63_4B3E_B267_9C0B112DA0C1__INCLUDED_

#include "umsNetMngCtrlIF.h"
#include "umsSession.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CUmsNetMngCtrl :public CUmsNetMngCtrlIF
{  

/** @defgroup  ��������ӿ�ʵ�ֲ���
 *  @{
 */
	friend class CUmsSession;
private:
	CUmsNetMngCtrl( const CUmsNetMngCtrl &){};
    CUmsNetMngCtrl( CUmsSession &cUmsSession );
	
public:
    ~CUmsNetMngCtrl();
	
	/**
    * ����:	 	        ���������������
	* @param [in]       ������Ϣ
	* @return           u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks ��Ϣ��   ev_CnAgtAddNMServerCmd
	*/
	virtual u16  NetMngAddReq( const TTPNMServerCfg& tTPNMServerCfg );

    /**
    * ����:	 	        �����޸���������
	* @param [in]       ������Ϣ
	* @return           u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks ��Ϣ��   ev_CnAgtDelNMServerCmd
	*/
	virtual u16  NetMngModifyReq( const TTPNMServerCfg& tTPNMServerCfg );

    /**
    * ����:	 	        ����ɾ����������
	* @param [in]       ������Ϣ
	* @return           u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks ��Ϣ��   ev_CnAgtModifyNMServerCmd
	*/
	virtual u16  NetMngDeleteReq( const TTPNMServerCfg& tTPNMServerCfg );

	/** 
	* ����  ��ȡ������Ϣ
	* @param [in]  
	* @return  
	*/
	virtual u16 GetUmsNetMngData( vector<TTPNMServerCfg> &vecTTPNMServerCfg );


protected:
 
	/**
    * ����:	  �������֪ͨ
	* @param [out]  cMsg	��Ϣ
	* @return  ��
	* @remarks   
	*/
	void  OnAddNetMngRsp(const CMessage& cMsg);
 
	/**
    * ����:	  ɾ������֪ͨ
	* @param [in]  cMsg	��Ϣ
	* @return  ��
	* @remarks   
	*/
    void  OnDelNetMngRsp(const CMessage& cMsg);

	/**
    * ����:	  �޸�����֪ͨ
	* @param [in]  cMsg	��Ϣ
	* @return  ��
	* @remarks   
	*/
    void  OnModifyNetMngRsp(const CMessage& cMsg);

	/**
    * ����:	  ������Ϣ֪ͨ
	* @param [in]  cMsg	��Ϣ
	* @return  ��
	* @remarks   
	*/
    void  OnNetMngNty(const CMessage& cMsg);

	/**
    * ����:	  ����֪ͨ
	* @param [in]  cMsg	��Ϣ
	* @return  ��
	* @remarks   
	*/
    void  OnLinkBreak(const CMessage& cMsg);

	/**
    * ����:	 ��ʱ֪ͨ
	* @param [in]  u16 wEvent
	* @return  ��
	* @remarks   
	*/
	virtual void OnTimeOut(u16 wEvent);

	virtual void DispEvent(const CMessage &cMsg);
   	


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

	vector<TTPNMServerCfg> m_vecTTPNMServerCfg;		//���ܷ�������Ϣ

/** @}*/ // ����ums������Ϣ�ӿ�ʵ�ֲ���
};

#endif // !defined(AFX_NETMNGCTRL_H__EB116E65_7B63_4B3E_B267_9C0B112DA0C1__INCLUDED_)
