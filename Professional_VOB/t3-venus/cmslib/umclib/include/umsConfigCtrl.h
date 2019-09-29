/*****************************************************************************
ģ����      : CMS����̨
�ļ���      : umsconfigctrl.h
����ļ�    : 
�ļ�ʵ�ֹ���: ums������
����        : �����
�汾        : V1.0  Copyright(C) 2011-2012 KDC, All rights reserved.
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��      �汾        �޸���      �޸�����
2011/4/25  1.0          �����      ����
******************************************************************************/

#if !defined(AFX_UMSCONFIGCTRL_H__F54D1163_86D6_4D90_BDB4_104A0673B42A__INCLUDED_)
#define AFX_UMSCONFIGCTRL_H__F54D1163_86D6_4D90_BDB4_104A0673B42A__INCLUDED_
#include "umsConfigCtrlIF.h"
#include "umssession.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CUmsConfigCtrl:public CUmsConfigCtrlIF  
{ 

/** @defgroup  ums����ʵ�ֲ���
 *  @{
 */

	friend class CUmsSession;
private:
	CUmsConfigCtrl( const CUmsConfigCtrl &){};
    CUmsConfigCtrl( CUmsSession &cUmsSession );

public:
    ~CUmsConfigCtrl();
	/**	 
	* ����:  sipע��	 
	* @param [in]  tSipCfg sip����������
	* @return u16 �ɹ�����0;ʧ�ܷ��ط�0������ 
	* @remarks	 ��Ϣ��cms->ums    ev_umsreg_cmd \n
	*                   Ӧ�ظ���u��s ->cms  ev_umsRegResult_notify  
	*/ 
	virtual u16 RegSipService( const TTPSipRegistrarCfg &tSipCfg )    ;


  
	/**	 
	* ����:  ע��sip 	 
	* @param [in]  tSipCfg sip����������
	* @return u16 �ɹ�����0;ʧ�ܷ��ط�0������	 
	* @remarks	 
	*/ 
	virtual u16 UnRegSipService( const TTPSipRegistrarCfg &tSipCfg )  ;


 
	/** 
	* ����:  ��ȡsip����	 
	* @param [out]  tSipCfg sip����������
	* @return u16 �ɹ�����0;ʧ�ܷ��ط�0������
	* @remarks	 
	*/ 
	virtual u16 GetSipCfg( TTPSipRegistrarCfg &tSipCfg ) ;


    /* ����:  ��ȡIP����	 
        * @param [out]   
        * @return u16 �ɹ�����0;ʧ�ܷ��ط�0������
        * @remarks	 
        */ 
	virtual u16 GetEthnetCfg( TTPEthnetInfo &tEthnetCfg ) ;

	    /* ����:  ��ȡGK����	 
        * @param [out]   
        * @return u16 �ɹ�����0;ʧ�ܷ��ط�0������
        * @remarks	 
        */ 
	virtual u16 GetGkCfg( TTPGKCfg &tGKRegCfg ) ;

	/* ����:  ��ȡSipע����
    * @param
    * @return BOOL �ɹ�����TRUE;ʧ�ܷ���FALSE
    * @remarks	 
    */ 
	virtual BOOL GetSipRegRsp();

	/* ����:  ��ȡGKע����
    * @param
    * @return BOOL �ɹ�����TRUE;ʧ�ܷ���FALSE
    * @remarks	 
    */
	virtual BOOL GetGKRegRsp();

	/** 
	* ����  UI�õ�ϵͳʱ��ӿ�
	* @param [in]  
	* @return  
	*/
	virtual u16 GetUmsSystime(TTPTime& pTTime);

    
/** 
	* ����:  ����IP	 
	* @param [out]  cfg ��ip��Ϣ
	* @return u16 �ɹ�����0;ʧ�ܷ��ط�0������
	* @remarks	��� 
	*/ 
	virtual u16  UpdateEthnetCfg( const TTPEthnetInfo& cfg );


    /**
    * ����:	 	        ����ums��������
	* @param [in]       ��
	* @return           u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks ��Ϣ��   
	*/
	virtual u16  RebootReq();

protected:

     /**
    * ����:	  
    * @param [out]  cMsg ��Ϣ
    * @return  ��
    * @remarks   
    */
    void  OnUmsIPNotify(const CMessage& cMsg);



	/** 
	* ����:  ע��sip�������Ļظ� 
	* @param [in] cMsg:��Ϣ����
	* @return  ��	 
	* @remarks	 
	*/
   void OnRegSigServRsp( const CMessage& cMsg );


 
   /** 
	* ����:  ע��sip��������֪ͨ 
	* @param [in] cMsg:��Ϣ����
	* @return  ��
	* @remarks  ��Ϣ UMS->CMS: ev_umsreg_notify
	*/
   void OnRegSigServNotify( const CMessage& cMsg );

   void OnLinkBreak( const CMessage& cMsg );
    
   

	virtual void DispEvent(const CMessage &cMsg);
	
    virtual void OnTimeOut(u16 wEvent);


   	     /**
    * ����:	 gk ע������
    * @param [int]  TTPGKCfg��
    * @return    
    * @remarks  �ɹ�����0��ʧ�ܷ��ش�����
    */
	virtual u16 GkRegReq( const TTPGKCfg & tGkwInfo ); 

	    /**
    * ����:	  ע��gk ����������Ϣ ��Ӧev_umsGKReg_notify
    * @param [out]  cMsg ��Ϣ
    * @return  ��
    * @remarks   set TTPGKCfg Info
    */
    virtual void  OnGkRegNotify(const CMessage& cMsg);

	    /**
    * ����:	  �õ� ���������ص�gkע���Ӧ
    * @param [out]  cMsg ��Ϣ
    * @return  ��
    * @remarks   TUCSipRegResult
    */
    virtual void  OnGkRegRsp(const CMessage& cMsg);


	    /**
    * ����:	  ע��sip ���������    forά������   ����ע�� ��ע���IP δע�� BOOLΪFALSE     
    * @param [out]  cMsg ��Ϣ
    * @return  ��
    * @remarks   set TTPGKCfg Info
    */
    virtual void  OnSipRegResultNotify(const CMessage& cMsg);

	    /**
    * ����:	  ע��gk ���������    forά������   ����ע�� ��ע���IP δע�� BOOLΪFALSE     
    * @param [out]  cMsg ��Ϣ
    * @return  ��
    * @remarks   set TTPGKCfg Info
    */
    virtual void  OnGkRegResultNotify(const CMessage& cMsg);

		/**
    * ����:	  UMSϵͳʱ������
    * @param [out]  cMsg ��Ϣ
    * @return  ��
    * @remarks   
    */
	virtual u16 OnSysTimeSetReq(const TTPTime& time);

		/** 
	* ����  ��ȡCnsע����Ϣ
	* @param [in]  
	* @return  
	*/
	//virtual const vector<TTPAlias>& GetCnsRegInfo() const;

	/** 
	* ����  ��ȡUmsע����Ϣ
	* @param [in]  
	* @return  
	*/
	//virtual const vector<TTPAlias>& GetUmsRegInfo() const;

		/** 
	* ����  ��ȡ����ע����Ϣ
	* @param [in]  
	* @return  
	*/
	//virtual const vector<TTPAlias>& GetAllRegInfo() const;

	/** 
	* ����  ��ȡ����ע����Ϣ
	* @param [in]  
	* @return  
	*/
	virtual const vector<TAliasEx>& GetAllTAliasEx() const;

	/** 
	* ����  ����SIPע����Ϣ
	* @param [in]  
	* @return  
	* @remarks 
	*/
	virtual u16 ReqSipRegInfo( EmGetRegInfoType emType );

	//��Ϣ����
	//void OnRegInfoRsp(const CMessage& cMsg);

	//B2�汾UMSע����Ϣ
	void OnRegInfoUmsRspEx(const CMessage& cMsg);
	//B2�汾CNSע����Ϣ
	void OnRegInfoCnsRspEx(const CMessage& cMsg);
	//B2�汾MTע����Ϣ
	void OnRegInfoMtRspEx(const CMessage& cMsg);
	//B2�汾MCUע����Ϣ
	void OnRegInfoMcuRspEx(const CMessage& cMsg);
	
	
	/**
    * ����:	  �õ�UMSϵͳʱ��
    * @param [out]  cMsg ��Ϣ
    * @return  ��
    * @remarks   
    */
	void OnGetSystimeRsp(const CMessage& cMsg);

private:
	void  BuildEventsMap();
	TAliasEx* FindTAliasEx( TAliasEx tCMSAlias );

private:
	CUmsSession *m_pUmsSession;     
	TTPSipRegistrarCfg m_tSipRegCfg; ///< sip����������
    TTPEthnetInfo   m_tEthnet;
	TTPGKCfg m_tGKRegCfg;
	TTPTime			m_tTime;
	BOOL     m_bIsSipRegistered;   //Sipע����
	BOOL     m_bIsGKRegistered;    //Gkע����

// 	vector<TTPAlias>  m_vctCnsRegInfo;
// 	vector<TTPAlias>  m_vctUmsRegInfo;
// 	vector<TTPAlias>  m_vctAllRegInfo;


	vector<TAliasEx> m_vecAllTAliasEx;

/** @}*/ 
};

#endif // !defined(AFX_UMSCONFIGCTRL_H__F54D1163_86D6_4D90_BDB4_104A0673B42A__INCLUDED_)
