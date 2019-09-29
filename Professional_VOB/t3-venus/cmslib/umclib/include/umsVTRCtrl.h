/*****************************************************************************
ģ����      : umstool����ά������
�ļ���      : umsVTRCtrl.h
����ļ�    : 
�ļ�ʵ�ֹ���: ums¼��������в���
����        : ʯ��
�汾        : V1.0  Copyright(C) 2013-2014 KDC, All rights reserved.
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��      �汾        �޸���      �޸�����
2013/3/5    1.0         ʯ��         ����
******************************************************************************/
#if !defined(UMCLIB_VTRCTRL_H)
#define UMCLIB_VTRCTRL_H

#include "umsVTRCtrlIF.h"
#include "umsSession.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CUmsVTRCtrl :public CUmsVTRCtrlIF
{  

/** @defgroup  ��������ӿ�ʵ�ֲ���
 *  @{
 */
	friend class CUmsSession;
private:
	CUmsVTRCtrl( const CUmsVTRCtrl &){};
    CUmsVTRCtrl( CUmsSession &cUmsSession );
	
public:
    ~CUmsVTRCtrl();
	
	/**
    * ����:	 	        �������¼�������
	* @param [in]       ������Ϣ
	* @return           u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks ��Ϣ��   ev_VTRAdd_req
	*/
	virtual u16  VTRAddReq( const TVcrCfg& tVTRCfg );

    /**
    * ����:	 	        �����޸�¼�������
	* @param [in]       �޸�ǰ���޸ĺ��������Ϣ
	* @return           u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks ��Ϣ��   ev_VTRMdy_req
	*/
	virtual u16  VTRModifyReq( const TVcrCfg& tVTRCfgOld, const TVcrCfg& tVTRCfgNew );

    /**
    * ����:	 	        ����ɾ��¼�������
	* @param [in]       ������Ϣ
	* @return           u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks ��Ϣ��   ev_VTRDel_req
	*/
	virtual u16  VTRDeleteReq( const TVcrCfg& tVTRCfg );

	/** 
	* ����  ��ȡ��һ��¼�����Ϣ
	* @param [in]  
	* @return  
	*/
	virtual u16 GetUmsVTRData( TVcrCfg& tVTRCfg );

	/** 
	* ����  ��ȡȫ��¼�����Ϣ
	* @param [in]  
	* @return  
	*/
	virtual u16 GetUmsVTRData( vector<TVcrCfg> &vecTVcrCfg );

	/** 
	* ����  ��ȡ¼��������ע��״̬
	* @param [in]  
	* @return  
	*/
	virtual u16 GetVtrRegState( BOOL32 &bRegState );

	/** 
	* ����  ��ȡ¼��������������Ϣ
	* @param [in]  
	* @return  
	*/
	virtual u16 GetRecBaseInfo( vector<TRecBaseInfo> &vecTRecBaseInfo );

	/** 
	* ����  ��ȡ¼���������ļ��б�
	* @param [in]  
	* @return  
	*/
	virtual u16 GetRecFileListInfo( vector<TRecFileInfo> &vecTVtrFileInfo );

	/** 
	* ����  ��ȡ¼���������ļ��б�(�޺�׺)
	* @param [in]  
	* @return  
	*/
	virtual u16 GetRecFileListInfoNoSuffix( vector<TRecFileInfo> &vecTVtrFileInfoNoSuffix );

	/**
    * ����:	 	        ɾ���ļ�����
	* @param [in]       �ļ���Ϣ
	* @return           u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks ��Ϣ��   ev_rec_del_file_req
	*/
	virtual u16  RecDelFileReq( const TRecFileInfo& tRecFileInfo );

	/**
    * ����:	 	        �޸��ļ�����
	* @param [in]       �ļ���Ϣ
	* @return           u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks ��Ϣ��   ev_rec_mdy_file_req
	*/
	virtual u16  RecMdyFileReq( const TRecFileInfo& tRecFileInfoOld, const TRecFileInfo& tRecFileInfoNew );

	/**
    * ����:	 	        ¼������
	* @param [in]       ¼����Ϣ
	* @return           u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks ��Ϣ��   ev_rec_recorder_conf_req
	*/
	virtual u16 RecStartConfReq( const TRecConfInfo& tRecConfInfo );

	/**
    * ����:	 	        ��ͣ¼������
	* @param [in]       ¼����Ϣ
	* @return           u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks ��Ϣ��   ev_rec_pause_conf_req
	*/
	virtual u16 RecPauseConfReq( const TRecConfRes& tRecConfRes );

	/**
    * ����:	 	        ����¼������
	* @param [in]       ¼����Ϣ
	* @return           u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks ��Ϣ��   ev_rec_resume_conf_req
	*/
	virtual u16 RecResumeConfReq( const TRecConfRes& tRecConfRes );

	/**
    * ����:	 	        ����¼������
	* @param [in]       ¼����Ϣ
	* @return           u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks ��Ϣ��   ev_rec_stop_conf_req
	*/
	virtual u16 RecStopConfReq( const TRecConfRes& tRecConfRes );

	/**
    * ����:	 	        ��ȡ¼����Ϣ
	* @param [in]       ¼����Ϣ
	* @return           u16 �ɹ�����0,ʧ�ܷ��ط�0������
	*/
	virtual u16 GetRecConfInfo( vector<TConRecState>& vecTConRecState );

	/**
    * ����:	 	        ��ȡ������Ϣ
	* @param [in]       ������Ϣ
	* @return           u16 �ɹ�����0,ʧ�ܷ��ط�0������
	*/
	virtual u16 GetPlayConfInfo( vector<TConfPlayStatus>& vecTConfPlayStatus );

	/**
    * ����:	 	        ��ʼ��������
	* @param [in]       ������Ϣ
	* @return           u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks ��Ϣ��   ev_rec_start_play_req
	*/
	virtual u16 RecStartPlayReq( const TRecPlayInfo& tRecPlayInfo );
	
	/**
    * ����:	 	        ��ͣ��������
	* @param [in]       ������Ϣ
	* @return           u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks ��Ϣ��   ev_rec_pause_play_req
	*/
	virtual u16 RecPausePlayReq( const TPlayStatusMdyInfo& tPlayStatusMdyInfo );
	
	/**
    * ����:	 	        ������������
	* @param [in]       ������Ϣ
	* @return           u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks ��Ϣ��   ev_rec_resume_play_req
	*/
	virtual u16 RecResumePlayReq( const TPlayStatusMdyInfo& tPlayStatusMdyInfo );
	
	/**
    * ����:	 	        ������������
	* @param [in]       ������Ϣ
	* @return           u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks ��Ϣ��   ev_rec_stop_play_req
	*/
	virtual u16 RecStopPlayReq( const TPlayStatusMdyInfo& tPlayStatusMdyInfo );

	/**
    * ����:	 	        �᳡��ʽ����
	* @param [in]       wConfID:����ID, wMtID:�᳡ID
	* @return           u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks ��Ϣ��   ev_rec_mt_format
	*/
	virtual u16 RecMtFormatReq( const u16& wConfID, const u16& wMtID );

	/**
    * ����:	 	        ��ȡ¼���ID
	* @param [in]       ¼���ID
	* @return           u16 �ɹ�����0,ʧ�ܷ��ط�0������
	*/
	virtual u16 GetEqpID( u8& byEqpID );
	
	//��m_vecTRecFileInfo�в���strFileNameNoSuffix��Ӧ��TRecFileInfo
	virtual TRecFileInfo FindFileName( CString strFileNameNoSuffix );

	/**
    * ����:	 	        �õ�û��ǰ׺�ͺ�׺��¼���ļ���
	* @param [in]       ¼���ļ���
	* @return           û��ǰ׺�ͺ�׺��¼���ļ���
	*/
	virtual CString GetNoSuffixString( CString strFileName );


protected:
 
	/**
    * ����:	  ���¼���֪ͨ
	* @param [out]  cMsg	��Ϣ
	* @return  ��
	* @remarks   
	*/
	void  OnAddVTRRsp(const CMessage& cMsg);
 
	/**
    * ����:	  ɾ��¼���֪ͨ
	* @param [in]  cMsg	��Ϣ
	* @return  ��
	* @remarks   
	*/
    void  OnDelVTRRsp(const CMessage& cMsg);

	/**
    * ����:	  �޸�¼���֪ͨ
	* @param [in]  cMsg	��Ϣ
	* @return  ��
	* @remarks   
	*/
    void  OnModifyVTRRsp(const CMessage& cMsg);

	/**
    * ����:	  ����¼���֪ͨ
	* @param [in]  cMsg	��Ϣ
	* @return  ��
	* @remarks   
	*/
    void  OnVTRNty(const CMessage& cMsg);

	/**
    * ����:	  ¼��������������Ϣ֪ͨ
	* @param [in]  cMsg	��Ϣ
	* @return  ��
	* @remarks   
	*/
    void  OnRecBaseInfoNty(const CMessage& cMsg);

	/**
    * ����:	  ¼��������ע��״̬֪ͨ
	* @param [in]  cMsg	��Ϣ
	* @return  ��
	* @remarks   
	*/
	void OnRecRegStatusNty(const CMessage& cMsg);

	/**
    * ����:	  ¼���������ļ��б�֪ͨ
	* @param [in]  cMsg	��Ϣ
	* @return  ��
	* @remarks   
	*/
	void OnRecFileListInfoNty(const CMessage& cMsg);

	/**
    * ����:	  �޸��ļ�ʧ�ܻظ�
	* @param [in]  cMsg	��Ϣ
	* @return  ��
	* @remarks   
	*/
	void OnRecMdyFileNack(const CMessage& cMsg);

	/**
    * ����:	  �޸��ļ��ɹ��ظ�
	* @param [in]  cMsg	��Ϣ
	* @return  ��
	* @remarks   
	*/
	void OnRecMdyFileAck(const CMessage& cMsg);

	/**
    * ����:	  ����¼����Ϣ֪ͨ
	* @param [in]  cMsg	��Ϣ
	* @return  ��
	* @remarks   
	*/
	void OnRecConfRecInfoNty(const CMessage& cMsg);

	/**
    * ����:	  ���������Ϣ֪ͨ
	* @param [in]  cMsg	��Ϣ
	* @return  ��
	* @remarks   
	*/
	void OnRecConfPlayInfoNty(const CMessage& cMsg);
	

	/**
    * ����:	  ��ʼ¼��ظ�
	* @param [in]  cMsg	��Ϣ
	* @return  ��
	* @remarks   
	*/
	void OnRecStartConfRsp( const CMessage& cMsg );

	/**
    * ����:	  ��ͣ¼��ظ�
	* @param [in]  cMsg	��Ϣ
	* @return  ��
	* @remarks   
	*/
	void OnRecPauseConfRsp( const CMessage& cMsg );

	/**
    * ����:	  �ָ�¼��ظ�
	* @param [in]  cMsg	��Ϣ
	* @return  ��
	* @remarks   
	*/
	void OnRecResumeConfRsp( const CMessage& cMsg );

	/**
    * ����:	  ����¼��ظ�
	* @param [in]  cMsg	��Ϣ
	* @return  ��
	* @remarks   
	*/
	void OnRecStopConfRsp( const CMessage& cMsg );

	/**
    * ����:	  ��ʼ����ظ�
	* @param [in]  cMsg	��Ϣ
	* @return  ��
	* @remarks   
	*/
	void OnRecStartPlayRsp( const CMessage& cMsg );

	/**
    * ����:	  ��ͣ����ظ�
	* @param [in]  cMsg	��Ϣ
	* @return  ��
	* @remarks   
	*/
	void OnRecPausePlayRsp( const CMessage& cMsg );

	/**
    * ����:	  ��������ظ�
	* @param [in]  cMsg	��Ϣ
	* @return  ��
	* @remarks   
	*/
	void OnRecResumePlayRsp( const CMessage& cMsg );

	/**
    * ����:	  ��������ظ�
	* @param [in]  cMsg	��Ϣ
	* @return  ��
	* @remarks   
	*/
	void OnRecStopPlayRsp( const CMessage& cMsg );

	/**
    * ����:	  ����Ҷϻظ�
	* @param [in]  cMsg	��Ϣ
	* @return  ��
	* @remarks   
	*/
	void OnHungUpConfRsp( const CMessage& cMsg );

	/**
    * ����:	  �᳡��ʽ�ظ�
	* @param [in]  cMsg	��Ϣ
	* @return  ��
	* @remarks   
	*/
	void OnMtFormatRsp( const CMessage& cMsg );

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

	TConRecState* FindRecInfo( TRecConfRes tRecConfRes );
	TConfPlayStatus* FindPlayInfo( TPlayStatusMdyInfo& tPlayStatusMdyInfo );

	//��m_vecTRecFileInfo����m_vecTRecFileInfoNoSuffix
	void SetRecFileListNoSuffix();

	//ת��(�޺�׺)TRecFileInfoΪ(�к�׺)TRecFileInfo
	void TRecFileInfoNoSuffix2TRecFileInfo( const TRecFileInfo& tRecFileInfoNoSuffix, TRecFileInfo& tRecFileInfo );

	
private:
	CUmsSession *m_pUmsSession;

	vector<TVcrCfg> m_vecTVTRCfg;					//���ܷ�������Ϣ
	vector<TRecBaseInfo> m_vecTRecBaseInfo;			//¼��������������Ϣ
	vector<TRecFileInfo> m_vecTRecFileInfo;			//¼���������ļ��б�
	vector<TRecFileInfo> m_vecTRecFileInfoNoSuffix;			//¼���������ļ��б�(�޺�׺)
	int m_nLeft;									//¼���������ļ��б�ʣ�������0��ʾ�ѽ�����
	vector<TConRecState> m_vecTConRecState;			//¼����Ϣ
	vector<TConfPlayStatus> m_vecTConfPlayStatus;	//������Ϣ

	BOOL32 m_bRegState;

/** @}*/ // ����ums¼�����Ϣ�ӿ�ʵ�ֲ���
};

#endif // !defined(UMCLIB_VTRCTRL_H)
