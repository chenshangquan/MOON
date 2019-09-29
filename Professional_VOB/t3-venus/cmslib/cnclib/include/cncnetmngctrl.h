/*****************************************************************************
ģ����      : cnclib�ӿ�
�ļ���      : cncnetmngctrl.h
����ļ�    : 
�ļ�ʵ�ֹ���: cns��������
����        : ʯ��
�汾        : V1.0  Copyright(C) 2013-2014 KDC, All rights reserved.
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��      �汾        �޸���      �޸�����
2013/1/17   1.0         ʯ��         ����
******************************************************************************/
#if !defined(AFX_CNCNETMNGCTRL_H__EB116E65_7B63_4B3E_B267_9C0B112DA0C1__INCLUDED_)
#define AFX_CNCNETMNGCTRL_H__EB116E65_7B63_4B3E_B267_9C0B112DA0C1__INCLUDED_

#include "cncnetmngctrlif.h"
#include "cnsSession.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CCncNetMngCtrl :public CCncNetMngCtrlIF
{
public:
	CCncNetMngCtrl(CCnsSession &cSession);
	virtual ~CCncNetMngCtrl();
	
	/**
    * ����:	 	        ���������������
	* @param [in]       ������Ϣ
	* @return           u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks ��Ϣ��   ev_CnAgtAddNMServerCmd
	*/
	virtual u16  NetMngAddCmd( const TTPNMServerCfg& tTPNMServerCfg );

    /**
    * ����:	 	        �����޸���������
	* @param [in]       ������Ϣ
	* @return           u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks ��Ϣ��   ev_CnAgtDelNMServerCmd
	*/
	virtual u16  NetMngModifyCmd( const TTPNMServerCfg& tTPNMServerCfg );

    /**
    * ����:	 	        ����ɾ����������
	* @param [in]       ������Ϣ
	* @return           u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks ��Ϣ��   ev_CnAgtModifyNMServerCmd
	*/
	virtual u16  NetMngDeleteCmd( const TTPNMServerCfg& tTPNMServerCfg );

	/** 
	* ����  ��ȡ������Ϣ
	* @param [in]  
	* @return  
	*/
	virtual void GetNetMngData( vector<TTPNMServerCfg> &vecTTPNMServerCfg )const;


protected:
 
	/**
    * ����:	  �������֪ͨ
	* @param [out]  cMsg	��Ϣ
	* @return  ��
	* @remarks   
	*/
	void  OnAddNetMngInd(const CMessage& cMsg);
 
	/**
    * ����:	  ɾ������֪ͨ
	* @param [in]  cMsg	��Ϣ
	* @return  ��
	* @remarks   
	*/
    void  OnDelNetMngInd(const CMessage& cMsg);

	/**
    * ����:	  �޸�����֪ͨ
	* @param [in]  cMsg	��Ϣ
	* @return  ��
	* @remarks   
	*/
    void  OnModifyNetMngInd(const CMessage& cMsg);

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
	CCnsSession				*m_pSession;

	vector<TTPNMServerCfg>	m_vecTTPNMServerCfg;		//���ܷ�������Ϣ
};

#endif // !defined(AFX_CNCNETMNGCTRL_H__EB116E65_7B63_4B3E_B267_9C0B112DA0C1__INCLUDED_)
