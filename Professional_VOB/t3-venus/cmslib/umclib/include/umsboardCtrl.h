/*****************************************************************************
ģ����      : umstool����ά������
�ļ���      : umsboardCtrl.h
����ļ�    : 
�ļ�ʵ�ֹ���: ums��������в���
����        : ����ӡ
�汾        : V1.0  Copyright(C) 2011-2012 KDC, All rights reserved.
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��      �汾        �޸���      �޸�����
2012/11/23  1.0         ����ӡ      ����
******************************************************************************/
#if !defined(AFX_BOARDCTRL_H__EB116E65_7B63_4B3E_B267_9C0B112DA0C1__INCLUDED_)
#define AFX_BOARDCTRL_H__EB116E65_7B63_4B3E_B267_9C0B112DA0C1__INCLUDED_

#include "umsboardCtrlIF.h"
#include "umsSession.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CUmsBoardCtrl :public CUmsBoardCtrlIF 
{  

/** @defgroup  ��������ӿ�ʵ�ֲ���
 *  @{
 */
	friend class CUmsSession;
private:
	CUmsBoardCtrl( const CUmsBoardCtrl &){};
    CUmsBoardCtrl( CUmsSession &cUmsSession );
	
public:
    ~CUmsBoardCtrl();
	

		/**
    * ����:	 ��ȡ����ռ�������Ϣ����
	* @param [out]  TTPBrdUsedInfo	����ռ����Ϣ(����������������ϳɡ�����������ռ��)
	* @return  u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks 
	*/
	virtual u16  GetUmsBoardUsedData( TTPBrdUsedInfo& tBoardUsed) const;


    /**
    * ����:	 	        �����޸ĵ�������
	* @param [in]       ������Ϣ
	* @return           u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks ��Ϣ��   
	*/
	virtual u16  BoardModifyReq( const TTPBrdCfg& tTPbrdCfg );

    /**
    * ����:	 	        ����ɾ����������
	* @param [in]       ������Ϣ��
	* @return           u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks ��Ϣ��   
	*/
	virtual u16  BoardDeleteReq( const TTPBrdCfg& tTPbrdCfg );

    /**
    * ����:	 	        ������ӵ�������
	* @param [in]       ������Ϣ
	* @return           u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks ��Ϣ��   
	*/
	virtual u16  BoardAddReq( const TTPBrdCfg& tTPbrdCfg );

    /**
    * ����:	 	        ������ӵ���ģʽ����
	* @param [in]       ģʽ��Ϣ
	* @return           u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks ��Ϣ��   
	*/
//	virtual u16  BoardModeAddReq( const TTPBrdMdlInfo& tTPbrdMdlInfo );

    /**
    * ����:	 	        �����޸ĵ���ģʽ����
	* @param [in]       ģʽ��Ϣ
	* @return           u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks ��Ϣ��   
	*/
	virtual u16  BoardModeModifyReq( const TTPBrdMdlInfo& tTPbrdMdlInfo );

    /**
    * ����:	 	        ����ɾ������ģʽ����
	* @param [in]       ģʽ��Ϣ
	* @return           u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks ��Ϣ��   
	*/
	virtual u16  BoardModeDeleteReq( const TTPBrdMdlInfo& tTPbrdMdlInfo );

	    /**
    * ����:	 	        ����������������
	* @param [in]       TTPBrdPos ����λ��
	* @return           u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks ��Ϣ��   
	*/
	virtual u16  BoardRebootReq( const TTPBrdPos& tTPbrdPos );

	    /**
    * ����:	 	        ���ͻ�����ռ������
	* @param [in]       ��
	* @return           u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks ��Ϣ��   
	*/
	virtual u16  BoardAudiomixReq();
	
	    /**
    * ����:	 	        ���ͻ���ϳ�ռ������
	* @param [in]       ��
	* @return           u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks ��Ϣ��   
	*/
	virtual u16  BoardVmpReq();

	    /**
    * ����:	 	        ������������ռ������
	* @param [in]       ��
	* @return           u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks ��Ϣ��   
	*/
	virtual u16  BoardBasStreamReq();

	    /**
    * ����:	 	        ������������
	* @param [in]       const TTPBrdUpGrade& tBrdUpGrade   ������Ϣ
	* @return           u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks ��Ϣ��   
	*/
	virtual u16  BoardUpgradeReq(const TTPBrdUpGrade& tBrdUpGrade);


protected:
 
	/**
    * ����:	  ��������֪ͨ
	* @param [out]  cMsg	��Ϣ
	* @return  ��
	* @remarks   
	*/
	void  OnRefreshboardNotify(const CMessage& cMsg);
 
	/**
    * ����:	  �޸ĵ�������֪ͨ
	* @param [in]  cMsg	��Ϣ
	* @return  ��
	* @remarks   
	*/
    void  OnBoardModifyNotify(const CMessage& cMsg);

	/**
    * ����:	  ɾ����������֪ͨ
	* @param [in]  cMsg	��Ϣ
	* @return  ��
	* @remarks   
	*/
    void  OnBoardDeleteNotify(const CMessage& cMsg);

	/**
    * ����:	  ��ӵ�������֪ͨ
	* @param [in]  cMsg	��Ϣ
	* @return  ��
	* @remarks   
	*/
    void  OnBoardAddNotify(const CMessage& cMsg);

	/**
    * ����:	  ��ӵ���ģʽ����֪ͨ
	* @param [in]  cMsg	��Ϣ
	* @return  ��
	* @remarks   
	*/
//  void  OnBoardModeAddNotify(const CMessage& cMsg);


	/**
    * ����:	  �޸ĵ���ģʽ����֪ͨ
	* @param [in]  cMsg	��Ϣ
	* @return  ��
	* @remarks   
	*/
    void  OnBoardModeModifyNotify(const CMessage& cMsg);

	/**
    * ����:	  ɾ������ģʽ����֪ͨ
	* @param [in]  cMsg	��Ϣ
	* @return  ��
	* @remarks   
	*/
    void  OnBoardModeDeleteNotify(const CMessage& cMsg);

		/**
    * ����:	  ����ռ����Ϣ����֪ͨ
	* @param [in]  cMsg	��Ϣ
	* @return  ��
	* @remarks   
	*/
    void  OnBoardUsedNotify(const CMessage& cMsg);

    /**
    * ����:	  �������
	* @param [in]  cMsg	��Ϣ
	* @return  ��
	* @remarks   
	*/
    void OnBoardUpgradeRsp(const CMessage& cMsg);

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
	
	TTPBrdInfo m_tTPBrdInfo;
	TTPBrdCfg m_tTPBrdCfgModify;
	TTPBrdCfg m_tTPBrdCfgAdd;
	TTPBrdCfg m_tTPBrdCfgDelete;
	TTPBrdMdlInfo m_tTPBrdModeCfgModify;
	TTPBrdMdlInfo m_tTPBrdModeCfgAdd;
	TTPBrdMdlInfo m_tTPBrdModeCfgDelete;

	TTPBrdUsedInfo m_tBoardUsed;

/** @}*/ // ����ums������Ϣ�ӿ�ʵ�ֲ���
};

#endif // !defined(AFX_BOARDCTRL_H__EB116E65_7B63_4B3E_B267_9C0B112DA0C1__INCLUDED_)
