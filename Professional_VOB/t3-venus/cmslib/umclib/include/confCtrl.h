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
#include "umssession.h"
#include "confctrlif.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CConfCtrl:public CConfCtrlIF  
{

/** @defgroup  �������ʵ�ֲ���
 *   @{
 */

	friend class CUmsSession;
private:
	CConfCtrl( CUmsSession &cUmsSession );
	CConfCtrl( const CConfCtrl &){};

public:
	~CConfCtrl();
  /**
    * ����:	��ȡ�����б�
	* @param [out]  tplConfList	 �����б�
	* @return  u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks 
	*/
	virtual u16 GetConfList( ARRAY<TCMSConf> &tplConfList ) const ; 

  /**
    * ����:	��ȡ������cns�б�
	* @param [int]  tplConfList	 �����б�
    * @param [out]  tplConfList	 CNS�б�
	* @return  u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks 
	*/
   virtual u16 GetConfCnsList( u16 wConfID, TplArray<TCnsInfo> &tplConfCnsList ) const ;

    /**
    * ����:	��ȡ��������б�
	* @param [int]  wConfID:����ID  
    * @param [out]  tConfAudmixList	 �����б�
	* @return  u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks 
	*/
   virtual u16 GetConfAudmixList(  u16 wConfID, TAuxMixList&tConfAudmixList ) const ;

  /**
    * ����:	��ȡ������ѯ�б�
	* @param [int]  wConfID:����ID  
    * @param [out]  tplConfPollList	 ��ѯ�б�
	* @return  u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks 
	*/
   virtual u16 GetConfPollList(  u16 wConfID, TplArray<u16> &tplConfPollList ) const ;



  
   /**
    * ����:	�ٿ�����
	* @param [int]  wConfTemplateID	 ����ģ��ID 
	* @return  u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks  ��Ϣ��cms->ums  evtp_StartConfTemplate_Req \n
	                   Ӧ�ظ���ums->cms  evtp_StartConfTemplate_Ret
	*/	 
	virtual u16 StartTemplateConfReq( const u16 wConfTemplateID ) ; 
   
	 
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
	virtual u16 HangupConfReq( const u16 wConfID );



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

    


   /**
    * ����:	��ջ����б�
	* @param [int]  vcConfLst 
	* @return  void 
	* @remarks  
	*/
   virtual void  ClearConfLst( vector<TCMSConf> &vcConfLst );
 
protected:

     /**
    * ����:	ɾ��һ������
	* @param [int]  wConfID	 ����ID
	* @return  u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks  
	*/
   virtual BOOL32 DeleteConfByID( const u16 wConfID );


	void OnStartConfTemplateRsp( const CMessage& cMsg ); 
	void OnHungUpConfRsp( const CMessage& cMsg ); 
	void OnHungUpConfNotify( const CMessage& cMsg ); 
	void OnInviteCnsRsp( const CMessage& cMsg ); 
	
	void OnAddConfListNotify( const CMessage& cMsg ); 
	void OnDelConfListNotify( const CMessage& cMsg ); 
	
	void OnUpdateConfCnsListNotify( const CMessage& cMsg ); 
	void OnUpdateConfAuxMixlistNotify( const CMessage& cMsg ); 
	void OnUpdateConfPolllistNotify( const CMessage& cMsg ); 
    void OnUpdateConfSpeakerNotify( const CMessage& cMsg ); 
	
   
	void OnSetSpokeCnsRsp( const CMessage& cMsg ); 
    void OnSetMuteCnsRsp( const CMessage& cMsg ); 
    void OnSetSilenceCnsRsp( const CMessage& cMsg ); 
    void OnSetDualCnsRsp( const CMessage& cMsg ); 
    void OnDualCnsNotify( const CMessage& cMsg ); 
    void OnCasadeNotify( const CMessage& cMsg ); 

    void OnLinkBreak( const CMessage& cMsg ); 

	virtual void DispEvent(const CMessage &cMsg);
	
    virtual void OnTimeOut(u16 wEvent);
    
private:
	 void  BuildEventsMap();

 
  /**
    * ����:	ͨ��confID ��ȡ����m_tplConfList�е�
	* @param [int]  wConfID	 ����ID
	* @return  s32 �ɹ�����index��,ʧ�ܷ���-1
	* @remarks  
	*/
     s32  GetConfIndexByID( u16 wConfID ) const;
	 
private:
    CUmsSession *m_pUmsSession;
	ARRAY<TCMSConf> m_tplConfList;// ����� Bug00073719:ͬһ���᳡��������6�����޷��ٹҶϸû᳡�� 

/** @}*/ //�������ʵ�ֲ���
};

#endif // !defined(AFX_CONFCTRL_H__CAFB9774_3218_4A07_80D4_B5B6EEE1ABE7__INCLUDED_)
