/*****************************************************************************
ģ����      : CMS����̨
�ļ���      : confCtrl.h
����ļ�    : 
�ļ�ʵ�ֹ���: ������ص����в���
����        : �����
�汾        : V1.0  Copyright(C) 2011-2012 KDC, All rights reserved.
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��         �汾        �޸���      �޸�����
2011/4/25  1.0          �����      ����
******************************************************************************/

#if !defined(AFX_CONFCTRL_H__CAFB9774_3218_4A07_80D4_B5B6EEE1ABE7__INCLUDED_)
#define AFX_CONFCTRL_H__CAFB9774_3218_4A07_80D4_B5B6EEE1ABE7__INCLUDED_
#include "cnsSession.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CUmcConfCtrl : public CUmcConfCtrlIF  
{

/** @defgroup  �������ʵ�ֲ���
 *   @{
 */
public:
 	friend class CCncSession; 
 
	CUmcConfCtrl( CCnsSession &cCnsSession );
	CUmcConfCtrl( const CUmcConfCtrl &){};
    

public:
  /**
    * ����:	��ȡ�����б�
	* @param [out]  tplConfList	 �����б�
	* @return  u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks 
	*/
	virtual u16 GetConf(  TCMSConf &tplConfList ) const ; 

  /**
    * ����:	��ȡ������cns�б�
	* @param [int]  tplConfList	 �����б�
    * @param [out]  tplConfList	 CNS�б�
	* @return  u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks 
	*/
   virtual u16 GetConfCnsList(  TplArray<TCnsInfo> &tplConfCnsList ) const ;

    /**
    * ����:	��ȡ��������б�
	* @param [int]  wConfID:����ID  
    * @param [out]  tConfAudmixList	 �����б�
	* @return  u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks 
	*/
   virtual u16 GetConfAudmixList( TAuxMixList&tConfAudmixList ) const ;

  /**
    * ����:	��ȡ������ѯ�б�
	* @param [int]  wConfID:����ID  
    * @param [out]  tplConfPollList	 ��ѯ�б�
	* @return  u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks 
	*/
   virtual u16 GetConfPollList(  TplArray<u16> &tplConfPollList ) const ;


 
   
	 
  /**
    * ����:	����ĳcns�᳡����ĳ����
	* @param [int]  tEp	 ����ͻ᳡��Ϣ
	* @return  u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks ��Ϣ��cms->ums  evtp_CallEP_cmd  \n
                       Ӧ�ظ���ums->cms evtp_CallEP_result   \n
	                   ���ɹ�����Ӧ����ums->cms evtp_UpdateConfCnsList_Notify
	*/ 
	virtual u16 InviteCnsReq( const TConfCallEpAddr &tEp );




    /**
    * ����:	���л������Ѿ����ڵ�cns�᳡����ĳ����
	* @param [int]  tEp	 ����ͻ᳡��Ϣ
	* @return  u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks ��Ϣ��cms->ums  evtp_CallEP_cmd  \n
                       Ӧ�ظ���ums->cms evtp_CallEP_result   \n
	                   ���ɹ�����Ӧ����ums->cms evtp_UpdateConfCnsList_Notify
	*/ 
	virtual u16 CallConfCnsReq( const TConfEpID &tEp );
   



  /**
    * ����:	�Ҷϻ���
	* @param [int]  wConfID ����ID
	* @return  u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks 
	*/
	virtual u16 HangupConfReq( );



   /**
    * ����:	�Ҷ�ĳ�᳡
	* @param [int]  tConfEpInfo �����᳡ID �� ����ID
	* @return  u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks �����б�����Ȼ���ڸû᳡��ֻ�ǲ�����
	*/
	virtual u16 HangupCNSReq( const TConfEpID &tConfEpInfo );


	/**
    * ����:	�ӻ������Ƴ�ĳ�᳡
	* @param [int]  tConfEpInfo �����᳡ID �� ����ID
	* @return  u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks �����б��в����ڸû᳡
	*/
	virtual u16 RemoveCNSReq( const TConfEpID &tConfEpInfo ) ;



  	/**
    * ����:	���÷��Ի᳡
	* @param [int]  wConfID	 ����ID
	* @return  u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks  
	*/
	virtual u16 SetSpokeCnsReq( const TConfEpID &tConfEpInfo ) ;

   
    /**
    * ����:	����Զ��cns����
	* @param [int]  wConfID	 ����ID
    * @param [int]  bQuiet  TRUE:����������FALSE��ֹͣ����
	* @return  u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks  
	*/
	virtual u16 SetQuietCnsReq( const TConfEpID &tConfEpInfo, BOOL32 bQuiet) ;


    /**
    * ����:	����Զ��cns����
	* @param [int]  wConfID	 ����ID
    * @param [int]  bMute  TRUE:����������FALSE��ֹͣ����
	* @return  u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks  
	*/
	virtual u16 SetMuteCnsReq( const TConfEpID &tConfEpInfo , BOOL32 bMute) ;



     /**
    * ����:	����Զ��cns����˫��
	* @param [int]  wConfID	 ����ID
    * @param [int]  bStart  TRUE:����˫����FALSE��ֹͣ˫��
	* @return  u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks  
	*/
	virtual u16 SetDualCnsReq( const TConfEpID &tConfEpInfo, BOOL32 bStart ) ;


	/**
    * ����:	���»����б�����
	* @param [int]  tMixInfo	 �����б�
	* @return  u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks  
	*/
	virtual u16 UpdateAudMixListReq( const TConfAuxMixInfo &tMixInfoList );


	/**
    * ����:	���������б�����
	* @param [int]  tDisListOpr	 һ�������б����
	* @return  u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks  
	*/
	virtual u16 AudMixDisListOprCmd( const TTPDisListOpr &tDisListOpr );

  /**
    * ����:	������ѯ�б�����
	* @param [int]  tTurnInfoList	 ��ѯ�б�
	* @return  u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks  
	*/
	virtual u16 UpdatePollListReq( const TConfTurnInfo &tTurnInfoList );


	
  /**
    * ����:	��������
	* @param [int]  wConfID	 ����ID
	* @return  u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks  
	*/
	virtual u16 StartAuxMixReq( const u16 wConfID );

 /**
    * ����:	ֹͣ����
	* @param [int]  wConfID	 ����ID
	* @return  u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks  
	*/
	virtual u16 StopAuxMixReq( const u16 wConfID );


   /**
    * ����:	������ѯ
	* @param [int]  wConfID	 ����ID
	* @return  u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks  
	*/
	virtual u16 StartPollReq( const u16 wConfID );


  /**
    * ����:	ֹͣ��ѯ 
	* @param [int]  wConfID	 ����ID
	* @return  u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks  
	*/
	virtual u16 StopPollReq( const u16 wConfID );

    
 
 
protected: 

    void OnChairCnsNotify( const CMessage& cMsg );
	void OnConfStateNty( const CMessage& cMsg );

	void OnHungUpConfRsp( const CMessage& cMsg ); 
	void OnInviteCnsRsp( const CMessage& cMsg ); 
    void OnCallConfCnsRsp( const CMessage& cMsg ); 
    void OnHangupCnsInd( const CMessage& cMsg );
	void OnUpdateConfCnsListNotify( const CMessage& cMsg ); 
	void OnUpdateConfAuxMixlistNotify( const CMessage& cMsg ); 
	void OnUpdateConfAuxMixlistInd( const CMessage& cMsg ); 
	void OnUpdateConfPolllistNotify( const CMessage& cMsg ); 
    void OnUpdateConfSpeakerNotify( const CMessage& cMsg ); 
	void OnAudMixDisListOprNotify( const CMessage& cMsg );
   
	void OnSetSpokeCnsRsp( const CMessage& cMsg ); 
    void OnSetMuteCnsRsp( const CMessage& cMsg ); 
    void OnSetSilenceCnsRsp( const CMessage& cMsg ); 
    void OnSetDualCnsRsp( const CMessage& cMsg ); 
    void OnDualCnsNotify( const CMessage& cMsg ); 
    
	void OnCnsLeaveNotify( const CMessage& cMsg ); 

    void OnUmsCommonReasonInd( const CMessage& cMsg ); 

    void OnLinkBreak( const CMessage& cMsg ); 

	virtual void DispEvent(const CMessage &cMsg);
	
    virtual void OnTimeOut(u16 wEvent);
    
private:
	 void  BuildEventsMap();
  
	 
private:
    CCnsSession *m_pCncSession;
	TCMSConf     m_tConfInfo; 

/** @}*/ //�������ʵ�ֲ���
};

#endif // !defined(AFX_CONFCTRL_H__CAFB9774_3218_4A07_80D4_B5B6EEE1ABE7__INCLUDED_)
