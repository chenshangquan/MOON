// cncconfctrl.h: interface for the CCncConfCtrl class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CNCCONFCTRL_H__2EF9234D_820A_40F3_9DC4_967387311945__INCLUDED_)
#define AFX_CNCCONFCTRL_H__2EF9234D_820A_40F3_9DC4_967387311945__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "cnsSession.h"

class CCncConfCtrl : public CCncConfCtrlIF 
{
public:
	CCncConfCtrl(CCnsSession &cSession);
	virtual ~CCncConfCtrl();

    
    /** 
	* ����  ������Ե����
	* @return tDialParam ��Ӧ����
	* @remarks 
	*/
    virtual const u16 MakeCall( TTPDialParam &tDialParam )  ;

    virtual const u16 HungupPtpConf();
	

	/** 
	* ����  ���û᳡�ڷ�����
	* @param [in]  byIndex  ���
	* @return 
	* @remarks 
	*/
	virtual u16 SetInnerSpeaker( u8 byIndex );


	/** 
	* ����  ����/�رձ�������
	* @param [in]  bMute  ����/�ر�
	* @return  
	* @remarks 
	*/
	virtual u16 SetCnsMute( BOOL bMute = TRUE );
	/** 
	* ����  ����/�رձ��ؾ���
	* @param [in]  bQutie  ����/�ر�
	* @return  
	* @remarks 
	*/
    virtual u16 SetCnsQutie( BOOL bQutie = TRUE );

	/** 
	* ����  ������������
	* @return byVolume ����
	* @remarks 
	*/
	virtual u16 AdjustInputVol( u8 byVolume );

	/** 
	* ����  �����������
	* @return byVolume ����
	* @remarks 
	*/
	virtual u16 AdjustOutputVol( u8 byVolum );

	/** 
	* ����  �������Ϣ
	* @remarks 
	*/
	virtual void ClearCnsScreenInfo();


    /** 
	* ����  ����ѡ��
    * @param [in]  byScreenID  ����
    * @param [in]  wEpID  ѡ����cnsID
	* @return  
	* @remarks 
	*/
	virtual u16 SetSelView( u8 byScreenID, u16 wEpID );

    /** 
	* ����  ȡ��ѡ��
    * @param [in]  byScreenID  ���� 
	* @return  
	* @remarks 
	*/
	virtual u16 CancleSelView( u8 byScreenID );

   /** 
	* ����  ����/ֹͣ��ѯ
    * @param [in]  bStart   true:������false���ر�
	* @return  
	*/
	virtual u16 StartPoll( BOOL  bStart );

	

    /** 
	* ����  ����/ֹͣ˫��
    * @param [in]  bStart   true:������false���ر�
	* @return  
	*/
	virtual u16 StartDual( BOOL  bStart );
 


    /** 
	* ����  ����/ֹͣ˫������
	* @return  BOOL  TRUE:������ FALSE:ֹͣ
	* @remarks 
	*/
    virtual u16 StartDualCodeStream( const TTPCnMediaTransPort  &tVideoTransAddr , const TTPCnMediaTransPort  &tAudioTransAddr ) const;
   
    virtual u16 StopDualCodeStream() const  ;

	/** 
	* ����  ����ؼ�֡
	* @return  BOOL  TRUE:���ܹؼ�֡����Լ����ǿ�Ʒ��͹ؼ�֡�� FALSE:�ܹؼ�֡����Լ�� 2012.8.16 by yjj
	* @remarks 
	*/
    virtual u16 ReqKeyFrame( BOOL32 bForce ) const ;


     /** 
	* ����  ��Ļ��ʾ˫��ͼ��
	* @return    
	* @remarks 
	*/
    virtual u16 ScrnDisplayDual( const u16 wScrnID ) const ;


    /** 
	* ����  ��Ļ��ʾ˫��ͼ��
	* @return  
	* @remarks 
	*/
    virtual u16 ScrnStopDisplayDual( const u16 wScrnID ) const ;

     
    /** 
	* ����  ��Ļ����
	* @return    
	* @remarks 
	*/
    virtual u16 ScrnDisplayLocal( const u16 wScrnID ) const ;


    /** 
	* ����  ȡ����Ļ����
	* @return    
	* @remarks 
	*/
    virtual u16 ScrnStopDisplayLocal( const u16 wScrnID ) const ;
 
	//�������л�
	virtual u16 ViewLocalPIPCmd( const u8 byScrnID, const BOOL bLocalP );

    /** 
	* ����  ����ѡ������ǽ
    * @param [in]  byScreenID  ����
	* @return  
	* @remarks 
	*/
	virtual u16 SelTVSView( u8 byScreenID );

    /** 
	* ����  ȡ��ѡ������ǽ
    * @param [in]  byScreenID  ���� 
	* @return  
	* @remarks 
	*/
	virtual u16 CancelSelTVSView( u8 byScreenID );

public: //��ȡlib�л�����Ϣ
   /** 
	* ����  ��ȡ�������
	* @return  u8  ����
	* @remarks 
	*/
	virtual const u8& GetOutputVol() const;


   /** 
	* ����  ��ȡ��������
	* @return  u8  ����
	* @remarks 
	*/
	virtual const u8& GetInputVol() const;


   /** 
	* ����  ��ȡ�᳡�ڷ�����
	* @return byIndex  ���
	* @remarks 
	*/
	virtual u8 GetInnerSpeaker() const;

	/** 
	* ����  ����CNS�Ƿ�����
	* @return  BOOL  �Ƿ�����
	* @remarks 
	*/
	virtual BOOL IsLocalCnsMute() const;
	/** 
	* ����  ����CNS�Ƿ���
	* @return  BOOL  �Ƿ���
	* @remarks 
	*/
    virtual BOOL IsLocalCnsQuite() const;

	/** 
	* ����  ���ػ��л��Ƿ���
	* @return  
	* @remarks 
	*/
    virtual BOOL IsViewLocalPIP() const;

    /** 
	* ����  ��ȡCNS����״̬
	* @return TTPCnsConfStatus ����״̬
	* @remarks 
	*/
	virtual const TTPCnsConfStatus& GetCnsConfStatus() const;


   /** 
	* ����  ��ȡ����Ϣ
	* @return vector<TScreenInfo> ����Ϣ
	* @remarks 
	*/
	virtual const vector<TScreenInfo>& GetCnsScreenInfo() const;


    /** 
	* ����  ����CNS�Ƿ�����ѯ
	* @return  BOOL  �Ƿ���
	* @remarks 
	*/
	virtual BOOL IsLocalCnsPoll() const;

   /** 
	* ����  ����CNS�Ƿ���˫��
	* @return  BOOL  �Ƿ���
	* @remarks 
	*/
    virtual BOOL IsLocalCnsDual() const;

    virtual TTPCnMediaTransPort GetVedioTransAddr() const { return m_tVideoTranAddr ;}
    virtual TTPCnMediaTransPort GetAudioTransAddr() const { return m_tAudioTranAddr ;}


    virtual TScreenInfo *GetScreenInfoByID( const u8 byScreenID )  ;

    virtual BOOL32 IsRcvDual() const { return m_bRecvDual; }

protected:
    virtual void OnTimeOut(u16 wEvent); 
    virtual void DispEvent(const CMessage &cMsg);
	void BuildEventsMap();

	void OnLinkBreak(const CMessage& cMsg);

	/** ����  ����״̬֪ͨ
	* @param [in]  cMsg  ��Ϣ����
	* @return 
	* @remarks ��Ϣ  cns->cms  ev_CnConfState_Nty
	*/
	void OnConfStateNty(const CMessage& cMsg);
	/**
    * ����: ����֪ͨ 
	* @param [in]	cMsg:��Ϣ����
	* @return  ��
	* @remarks ��Ϣ  cns->cms  ev_tppMuteInd
	*/
	void OnMuteInd(const CMessage &cMsg);
	/**
    * ����: ����֪ͨ 
	* @param [in]	cMsg:��Ϣ����
	* @return  ��
	* @remarks ��Ϣ  cns->cms  ev_tppQuietInd
	*/
	void OnQuietInd(const CMessage &cMsg);
	/**
    * ����: ��������֪ͨ 
	* @param [in]	cMsg:��Ϣ����
	* @return  ��
	* @remarks ��Ϣ  cns->cms  ev_tppInputVolumeInd  
	*/
	void OnInputVolInd(const CMessage &cMsg);
	/**
	* ����: �������֪ͨ 
	* @param [in]	cMsg:��Ϣ����
	* @return  ��
	* @remarks ��Ϣ  cns->cms  ev_tppOutputVolumeInd  
	*/
	void OnOutPutVolInd(const CMessage &cMsg);
	/**
	* ����: ���û᳡������֪ͨ 
	* @param [in]	cMsg:��Ϣ����
	* @return  ��
	* @remarks ��Ϣ  cns->cms  ev_CnSetInnerSpeaker_Ind  
	*/
	void OnSetInnerSpeaker( const CMessage &cMsg);
	/**
	* ����: ����ʾ�᳡֪ͨ 
	* @param [in]	cMsg:��Ϣ����
	* @return  ��
	* @remarks ��Ϣ  cns->cms  ev_CnYouAreSeeing_Ind  
	*/
	void OnScreenDisplayInd(const CMessage &cMsg);

	void UpdateScreenInfo( u8 byScreen, s8* achCnsName );
    void UpdateScreenInfo( u8 byScreen, s8* achCnsName,EMPosPic emPic );
	void UpdateScreenInfo( u8 byScreen, EmTPPosStatus emStatus, EMPosPic emPos );
     
    void OnScreenStateNotify( const CMessage &cMsg );
    void OnSetSelViewRsp( const CMessage &cMsg );
    void OnStartPollRsp( const CMessage &cMsg );
    void OnStartDualRsp( const CMessage &cMsg );
	void OnPollStatusNty( const CMessage &cMsg ); 
	void OnDualStatusNty( const CMessage &cMsg );
    void OnHungupNotify( const CMessage &cMsg );

    void OnStartDualCdStrmRsp( const CMessage &cMsg );
    void OnStopDualCdStrmRsp( const CMessage &cMsg );

    void OnScrnDisplayDualRsp( const CMessage &cMsg );
    void OnStopScrnDisplayDualRsp( const CMessage &cMsg );
    
    void OnScrnDisplayLocalRsp( const CMessage &cMsg );
    void OnStopDisplayLocalRsp( const CMessage &cMsg );

    void OnRecvDualNty( const CMessage &cMsg );
	void OnCnDualOfflineNty( const CMessage &cMsg );
    void OnDualRcvInterruptNty( const CMessage &cMsg );

	void OnViewLocalPIPInd( const CMessage &cMsg );
	void OnViewLocalPIPNty( const CMessage &cMsg );
	void OnSetSelTVSViewRsp( const CMessage &cMsg );
private:
	CCnsSession      *m_pSession;

	TTPCnsConfStatus m_tCnsConfStatus;

    TTPCnMediaTransPort m_tVideoTranAddr;
    TTPCnMediaTransPort m_tAudioTranAddr;
    u16              m_nVideoNode;
    u16              m_nAudioNode;
	u8               m_bySpeakSeat; //������ϯID
	u8	             m_byInputVol;	//��������
	u8				 m_byOutputVol;	//�������
	BOOL32			 m_bMute;	    //�Ƿ�����		
	BOOL32			 m_bQuite;      //�Ƿ���
    BOOL32           m_bPoll;       //�Ƿ�����ѯ
    BOOL32           m_bDual;
    BOOL32           m_bRecvDual;
	vector<TScreenInfo>  m_vctScreenInfo;
	vector<TTPNMServerCfg> m_vecTTPNMServerCfg;		//���ܷ�������Ϣ
    BOOL32           m_bLocalPIP;	//�Ƿ������л�
};

#endif // !defined(AFX_CNCCONFCTRL_H__2EF9234D_820A_40F3_9DC4_967387311945__INCLUDED_)
