/*****************************************************************************
ģ����      : umstool����ά������
�ļ���      : umssysinfoCtrl.h
����ļ�    : 
�ļ�ʵ�ֹ���: umsϵͳ��Ϣ�����в���
����        : ����ӡ
�汾        : V1.0  Copyright(C) 2011-2012 KDC, All rights reserved.
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��      �汾        �޸���      �޸�����
2012/11/23  1.0         ����ӡ      ����
******************************************************************************/
#if !defined(AFX_SYSINFOCTRL_H__EB116E65_7B63_4B3E_B267_9C0B112DA0C1__INCLUDED_)
#define AFX_SYSINFOCTRL_H__EB116E65_7B63_4B3E_B267_9C0B112DA0C1__INCLUDED_

#include "umssysinfoCtrlIF.h"
#include "umsSession.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CUmsSysInfoCtrl :public CUmsSysInfoCtrlIF 
{  

/** @defgroup  ����umsϵͳ��Ϣʵ�ֲ���
 *  @{
 */


	friend class CUmsSession;
private:
	CUmsSysInfoCtrl( const CUmsSysInfoCtrl &){};
    CUmsSysInfoCtrl( CUmsSession &cUmsSession );
	
public:
    ~CUmsSysInfoCtrl();

	/**
    * ����:	 ��ȡums�汾��Ϣ����
	* @param [out]  tUmsVer	 ums�汾
	* @return  u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks 
	*/
	virtual u16  GetUmsVerData( TUmsVersion& tUmsVer) const;

	/**
    * ����:	 ��ȡums CPU���ڴ����Ϣ����
	* @param [out]  tUmsSysInfo	 ums cpu���ڴ���Ϣ
	* @return  u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks 
	*/
	virtual u16  GetUmsSysInfoData( TToolSysInfo& tUmsSysInfo) const;

	
    /**
    * ����:	 	        ˢ��umsϵͳ��Ϣ����
	* @param [in]       ��
	* @return           u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks ��Ϣ��   
	*/
	virtual u16  RefreshUmsSysInfoReq();
	
    /**
    * ����:	 	        ��ȡums������Ŀ
	* @param [in]       ��
	* @return           u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks ��Ϣ��   
	*/
	virtual u16  ConfCountReq();

	/**
    * ����:	 ��ȡums������Ŀ
	* @param [out]  body	u32   ��Ŀ 
	* @return  ������Ŀ
	* @remarks 
	*/
	virtual u32  GetConfCountData(){ return m_nConfCount;};


    /**
    * ����:	 	        ������Ȩ��Ŀ����
	* @param [in]       ��
	* @return           u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks ��Ϣ��   
	*/
	virtual u16  AuthCountReq();

	/**
    * ����:	 ��ȡums��Ȩ��Ŀ
	* @param [out]  body	u32   ��Ŀ 
	* @return  ������Ŀ
	* @remarks 
	*/
	virtual std::pair<int,int>  GetAuthCountData(){ return m_nAuthCount;};

    /**
    * ����:	 	        ���͵���ǽռ���������
	* @param [in]       ��
	* @return           u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks ��Ϣ��   
	*/
	virtual u16  TvwUsedCountReq();

		/**
    * ����:	 ��ȡ����ǽռ�������Ϣ����
	* @param [out]  TTPBrdUsedInfo	����ǽ��ռ����Ϣ
	* @return  u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks 
	*/
	virtual u16  GetUmsTvwUsedData( TTPBrdUsedInfo& tTvwUsed) const;


protected:
 
  /**
    * ����:	  
	* @param [out]  cMsg	��Ϣ
	* @return  ��
	* @remarks   
	*/
	void  OnRefreshUmsVerNotify(const CMessage& cMsg);

  /**
    * ����:	  ˢ��ums CPU���ڴ������Ϣ֪ͨ
	* @param [out]  cMsg	��Ϣ
	* @return  ��
	* @remarks   
	*/
	void  OnRefreshUmsSysInfoNotify(const CMessage& cMsg);

  /**
    * ����:	  ˢ��ums CPU���ڴ������Ϣ֪ͨ
	* @param [in]  cMsg	��Ϣ
	* @return  ��
	* @remarks   
	*/
    void  OnConfCountNotify(const CMessage& cMsg);
	
  /**
    * ����:	  ��Ȩ��Ŀ֪ͨ
	* @param [in]  cMsg	��Ϣ
	* @return  ��
	* @remarks   
	*/
    void  OnAuthCountNotify(const CMessage& cMsg);

  /**
    * ����:	  ����ǽʹ�����֪ͨ
	* @param [in]  cMsg	��Ϣ
	* @return  ��
	* @remarks   
	*/
    void  OnTvwUsedNotify(const CMessage& cMsg);



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
	
	TUmsVersion m_tUmsVer;				//ums�汾��Ϣ
	TToolSysInfo m_tUmsSysInfo;			//ums CPU���ڴ���Ϣ
	u32 m_nConfCount;
	std::pair<int,int> m_nAuthCount;    //��Ŀ������
	TTPBrdUsedInfo m_tTvwUsed;          //����ǽռ�����
 
/** @}*/ // ����umsϵͳ��Ϣ�ӿ�ʵ�ֲ���
};

#endif // !defined(AFX_SYSINFOCTRL_H__EB116E65_7B63_4B3E_B267_9C0B112DA0C1__INCLUDED_)
