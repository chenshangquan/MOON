/*****************************************************************************
ģ����      : umstool����ά������
�ļ���      : umstvwboardCtrl.h
����ļ�    : 
�ļ�ʵ�ֹ���: ums����ǽ�忨�����в���
����        : ����ӡ
�汾        : V1.0  Copyright(C) 2011-2012 KDC, All rights reserved.
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��      �汾        �޸���      �޸�����
2012/11/23  1.0         ����ӡ      ����
******************************************************************************/
#if !defined(AFX_TVWBOARDCTRL_H__EB116E65_7B63_4B3E_B267_9C0B112DA0C1__INCLUDED_)
#define AFX_TVWBOARDCTRL_H__EB116E65_7B63_4B3E_B267_9C0B112DA0C1__INCLUDED_

#include "umstvwboardCtrlIF.h"
#include "umsSession.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CUmsTvwBoardCtrl :public CUmsTvwBoardCtrlIF 
{  

/** @defgroup  ��������ǽ����ӿ�ʵ�ֲ���
 *  @{
 */
	friend class CUmsSession;
private:
	CUmsTvwBoardCtrl( const CUmsTvwBoardCtrl &){};
    CUmsTvwBoardCtrl( CUmsSession &cUmsSession );
	
public:
    ~CUmsTvwBoardCtrl();

		/**
    * ����:	 ��ȡ����ǽ�������
	* @param [out]  THduStyleData  ����ǽ�������
	* @return  u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks 
	*/
	virtual u16  GetUmsTvwStyleData( THduStyleData& tHduStyleData ) const;

		/**
    * ����:	 ��ȡ����ǽ��������
	* @param [out]  std::multimap<u8,THduCfg>  ����ǽ��Ϣ���㡢�ۡ�IP��ͨ����Ϣ�ȣ�
	* @return  u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks 
	*/
	virtual u16  GetUmsTvwBoardData( std::multimap<u8,THduCfg>& mulmapTHduCfg ) const;

    /**
    * ����:	 	        ������ӵ���ǽ��������
	* @param [in]       ������Ϣ
	* @return           u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks ��Ϣ��   
	*/
	virtual u16  TvwBoardAddReq( const TTPBrdPos& tTPBrdPos );

    /**
    * ����:	 	        �����޸ĵ���ǽ��������
	* @param [in]       ������Ϣ
	* @return           u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks ��Ϣ��   
	*/
	virtual u16  TvwBoardModifyReq( const TTPBrdPos& tTPBrdPos );

    /**
    * ����:	 	        ����ɾ������ǽ��������
	* @param [in]       ������Ϣ��
	* @return           u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks ��Ϣ��   
	*/
	virtual u16  TvwBoardDeleteReq( const TTPBrdPos& tTPBrdPos );

    /**
    * ����:	 	        ������ӵ���ǽ����ģʽ����
	* @param [in]       ģʽ��Ϣ
	* @return           u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks ��Ϣ��   
	*/
	virtual u16  TvwBoardModeAddReq( const THduInfo& tTHduInfo );

    /**
    * ����:	 	        �����޸ĵ���ǽ����ģʽ����
	* @param [in]       ģʽ��Ϣ
	* @return           u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks ��Ϣ��   
	*/
	virtual u16  TvwBoardModeModifyReq( const THduInfo& tTHduInfo );

    /**
    * ����:	 	        ����ɾ������ǽ����ģʽ����
	* @param [in]       ģʽλ��
	* @return           u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks ��Ϣ��   
	*/
	virtual u16  TvwBoardModeDeleteReq( const TTPBrdPos& tTPBrdPos );

	    /**
    * ����:	 	        ������������ǽ��������
	* @param [in]       TTPBrdPos ����λ��
	* @return           u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks ��Ϣ��   
	*/
	virtual u16  TvwBoardRebootReq( const TTPBrdPos& tTPbrdPos );

		    /**
    * ����:	 	        ����ǽ������������
	* @param [in]       const TTPBrdUpGrade& tBrdUpGrade   ������Ϣ
	* @return           u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks ��Ϣ��   
	*/
	virtual u16  TvwBoardUpgradeReq(const TTPBrdUpGrade& tBrdUpGrade);

	    /**
    * ����:	 	        ��ӵ���ǽ�������
	* @param [in]       tHduStyleData ����ǽ�����Ϣ
	* @return           u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks ��Ϣ��   
	*/
	virtual u16  AddTvwStyleReq( const THduStyleData& tHduStyleData );

	   /**
    * ����:	 	        ɾ������ǽԤ������
	* @param [in]       tHduStyleData ����ǽ�����Ϣ
	* @return           u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks ��Ϣ��   
	*/
	//virtual u16  TvwStyleDeleteReq();

protected:
 
	/**
    * ����:	  ����ǽ��������֪ͨ
	* @param [out]  cMsg	��Ϣ
	* @return  ��
	* @remarks   
	*/
	void  OnRefreshTvwBoardNotify(const CMessage& cMsg);
 
	/**
    * ����:	  ��ӵ���ǽ��������֪ͨ
	* @param [in]  cMsg	��Ϣ
	* @return  ��
	* @remarks   
	*/
    void  OnTvwBoardAddNotify(const CMessage& cMsg);

	/**
    * ����:	  �޸ĵ���ǽ��������֪ͨ
	* @param [in]  cMsg	��Ϣ
	* @return  ��
	* @remarks   
	*/
    void  OnTvwBoardModifyNotify(const CMessage& cMsg);

	/**
    * ����:	  ɾ������ǽ��������֪ͨ
	* @param [in]  cMsg	��Ϣ
	* @return  ��
	* @remarks   
	*/
    void  OnTvwBoardDeleteNotify(const CMessage& cMsg);

	/**
    * ����:	  ��ӵ���ǽ����ģʽ����֪ͨ
	* @param [in]  cMsg	��Ϣ
	* @return  ��
	* @remarks   
	*/
    void  OnTvwBoardModeAddNotify(const CMessage& cMsg);

	/**
    * ����:	 �޸ĵ���ǽ����ģʽ����֪ͨ
	* @param [in]  cMsg	��Ϣ
	* @return  ��
	* @remarks   
	*/
    void  OnTvwBoardModeModifyNotify(const CMessage& cMsg);

	/**
    * ����:	  ɾ������ǽ����ģʽ����֪ͨ
	* @param [in]  cMsg	��Ϣ
	* @return  ��
	* @remarks   
	*/
    void  OnTvwBoardModeDeleteNotify(const CMessage& cMsg);

    /**
    * ����:	  ����ǽ���֪ͨ
	* @param [in]  cMsg	��Ϣ
	* @return  ��
	* @remarks   
	*/
    void OnTvwStyleNotify(const CMessage& cMsg);


    /**
    * ����:	  ��ӵ���ǽ����Ӧ
	* @param [in]  cMsg	��Ϣ
	* @return  ��
	* @remarks   
	*/
    void OnAddTvwStyleRsp(const CMessage& cMsg);

    /**
    * ����:	  ɾ������ǽԤ��Ӧ��
	* @param [in]  cMsg	��Ϣ
	* @return  ��
	* @remarks   
	*/
//    void OnTvwStyleDeleteRsp(const CMessage& cMsg);

    /**
    * ����:	  ��������ǽ�忨��Ӧ
	* @param [in]  cMsg	��Ϣ
	* @return  ��
	* @remarks   
	*/
    void OnRebootTvwBoardRsp(const CMessage& cMsg);

    /**
    * ����:	  �������
	* @param [in]  cMsg	��Ϣ
	* @return  ��
	* @remarks   
	*/
    void OnTvwBoardUpgradeRsp(const CMessage& cMsg);

    /**
    * ����:	  ���µ���ǽԤ�����   by xhx
	* @param [in]  cMsg	��Ϣ
	* @return  ��
	* @remarks   
	*/
    void OnUpdateTvwStyleRsp(const CMessage& cMsg);

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

	void ResetMapTHduCfgData();

	/**
    * ����:	  ����ǽ����ģʽ�ı䣬ͬ�����µ���ǽԤ��    by xhx
	* @param   ��
	* @return  ��
	* @remarks   
	*/
	void UpdateUmsTvwStyleData();

private:
	CUmsSession *m_pUmsSession;
	
	std::multimap<u8,THduCfg> m_mulmapTHduCfg;    //��Ӧ��ż�����ǽ������Ϣ

 	TTPBrdPos m_tTPAddBrdPos;
 	TTPBrdPos m_tTPModifyBrdPos;
	TTPBrdPos m_tTPDelBrdPos;
	THduInfo m_tAddTvwBrdMdlTHduInfo;
	THduInfo m_tModifyTvwBrdMdlTHduInfo;
 	TTPBrdPos m_tDelTvwBrdMdlTPBrdPos;

 	TTPBrdPos m_tRebootTPBrdPos;

    THduStyleData m_tHduStyleData; //����ǽ���

/** @}*/ // ����ums����ǽ�忨��Ϣ�ӿ�ʵ�ֲ���
};

#endif // !defined(AFX_TVWBOARDCTRL_H__EB116E65_7B63_4B3E_B267_9C0B112DA0C1__INCLUDED_)
