/*****************************************************************************
ģ����      : CCommonMgrIF
�ļ���      : commonmgrif.h
����ļ�    : 
�ļ�ʵ�ֹ���: umstool ��Ϣ������ģ��
����        : ����ӡ
�汾        : V1.0  Copyright(C) 2012-2013 KDV, All rights reserved.
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��         �汾        �޸���      �޸�����
2012/11/21     1.0         ����ӡ      ����
******************************************************************************/
#if !defined(AFX_DATAMGRIMP_H__0DA134CE_DB83_4357_B0E6_8A6707CBC456__INCLUDED_)
#define AFX_DATAMGRIMP_H__0DA134CE_DB83_4357_B0E6_8A6707CBC456__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "umclib.h" 

class CCommonMgrIF : public ISingleTon<CCommonMgrIF>
{
public:
	CCommonMgrIF();
	virtual ~CCommonMgrIF();

public:
	/*=============================================================================
    �� �� ��:DestroyCommMgr
    ��    ��:���ٹ�����Ϣ������ָ��
    ��    ��:��
    ע    ��:��
    �� �� ֵ:��
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���    �޸�����
    2012/11/21  1.0     ����ӡ    ����
    =============================================================================*/
    void DestroyCommMgr();

	u16 LinkUms();

	/*=============================================================================
    �� �� ��:Connect
    ��    ��:���ӵ�������
    ��    ��:LPCTSTR strIpAddr:        [in]        ��½������IP��ַ
			 u16 nPort:                [in]        ͨ�Ŷ˿�
			 LPCTSTR pStrUserName:     [in]        ��½�û���
		   	 LPCTSTR pStrPswd:         [in]        ��½����
    ע    ��:��
    �� �� ֵ:u16 �ɹ�����0;ʧ�ܷ��ط�0������ 
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���    �޸�����
    2012/11/21  1.0     ����ӡ    ����
    =============================================================================*/
	u16 Connect( u32 dwIp, u16 nPort, LPCTSTR pStrUserName, LPCTSTR pStrPswd ); 

	/*=============================================================================
    �� �� ��:DisConnect
    ��    ��:�Ͽ�����������
    ��    ��:��
    ע    ��:��
    �� �� ֵ:u16 �ɹ�����0;ʧ�ܷ��ط�0������ 
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���    �޸�����
    2012/11/21  1.0     ����ӡ    ����
    =============================================================================*/
	u16 DisConnect(); 

	/*=============================================================================
    �� �� ��:GetLoginInfo
    ��    ��:�õ���ǰ��½��������Ϣ
    ��    ��:��
    ע    ��:��
    �� �� ֵ:u16 �ɹ�����0;ʧ�ܷ��ط�0������ 
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���    �޸�����
    2012/12/14  1.0     ����ӡ    ����
    =============================================================================*/
	TLoginInfo GetLoginInfo(){ return m_tLoginInfo;};

	/*=============================================================================
    �� �� ��:Connect
    ��    ��:���ӵ�������
    ��    ��:const TTPTime& time:        [in]       ����ʱ�� 
    ע    ��:��
    �� �� ֵ:u16 �ɹ�����0;ʧ�ܷ��ط�0������ 
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���    �޸�����
    2012/11/21  1.0     ����ӡ    ����
    =============================================================================*/
	u16 SysTimeSetReq(const TTPTime& time); 

	/*=============================================================================
    �� �� ��:AuthCountReq
    ��    ��:��Ȩ��Ŀ����
    ��    ��:�� 
    ע    ��:��
    �� �� ֵ:u16 �ɹ�����0;ʧ�ܷ��ط�0������ 
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���    �޸�����
    2012/11/21  1.0     ����ӡ    ����
    =============================================================================*/
	u16 AuthCountReq();

	/*=============================================================================
    �� �� ��:ConfCountReq
    ��    ��:������Ŀ����
    ��    ��:��
    ע    ��:��
    �� �� ֵ:u16 �ɹ�����0;ʧ�ܷ��ط�0������ 
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���    �޸�����
    2012/11/21  1.0     ����ӡ    ����
    =============================================================================*/
	u16 ConfCountReq();

	/*=============================================================================
    �� �� ��:RefreshUmsSysInfoReq
    ��    ��:ˢ��ϵͳ��Ϣ����
    ��    ��:��
    ע    ��:��
    �� �� ֵ:u16 �ɹ�����0;ʧ�ܷ��ط�0������ 
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���    �޸�����
    2012/11/21  1.0     ����ӡ    ����
    =============================================================================*/
	u16 RefreshUmsSysInfoReq();

    /**
    * ����:	 	        ���͵���ǽռ���������
	* @param [in]       ��
	* @return           u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks ��Ϣ��   
	*/
	u16  TvwUsedCountReq();

	/*=============================================================================
    �� �� ��:RebootReq
    ��    ��:ums��������
    ��    ��:��
    ע    ��:��
    �� �� ֵ:u16 �ɹ�����0;ʧ�ܷ��ط�0������ 
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���    �޸�����
    2012/11/21  1.0     ����ӡ    ����
    =============================================================================*/
	u16 RebootReq();

	/**
    * ����:	 ��ȡ������Ϣ
	* @param [out]  ������Ϣ
	* @return  u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks 
	*/
	u16  GetTPBrdInfoData( TTPBrdInfo& tTPBrdInfo) const;


    /**
    * ����:	 	        �����޸ĵ�������
	* @param [in]       ������Ϣ
	* @return           u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks ��Ϣ��   
	*/
	u16  BoardModifyReq( const TTPBrdCfg& tTPbrdCfg );


	    /**
    * ����:	 	        ������������
	* @param [in]       const TTPBrdUpGrade& tBrdUpGrade   ������Ϣ
	* @return           u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks ��Ϣ��   
	*/
	u16  BoardUpgradeReq(const TTPBrdUpGrade& tBrdUpGrade);

    /**
    * ����:	 	        ����ɾ����������
	* @param [in]       ������Ϣ��
	* @return           u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks ��Ϣ��   
	*/
	u16  BoardDeleteReq( const TTPBrdCfg& tTPbrdCfg );

    /**
    * ����:	 	        ������ӵ�������
	* @param [in]       ������Ϣ
	* @return           u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks ��Ϣ��   
	*/
	u16  BoardAddReq( const TTPBrdCfg& tTPbrdCfg );

    /**
    * ����:	 	        ������ӵ���ģʽ����
	* @param [in]       ģʽ��Ϣ
	* @return           u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks ��Ϣ��   
	*/
//	u16  BoardModeAddReq( const TTPBrdMdlInfo& tTPbrdMdlInfo );

    /**
    * ����:	 	        �����޸ĵ���ģʽ����
	* @param [in]       ģʽ��Ϣ
	* @return           u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks ��Ϣ��   
	*/
	u16  BoardModeModifyReq( const TTPBrdMdlInfo& tTPbrdMdlInfo );

    /**
    * ����:	 	        ����ɾ������ģʽ����
	* @param [in]       ģʽ��Ϣ
	* @return           u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks ��Ϣ��   
	*/
	u16  BoardModeDeleteReq( const TTPBrdMdlInfo& tTPbrdMdlInfo );


	 /**
    * ����:	 	        ����������������
	* @param [in]       TTPBrdPos ����λ��
	* @return           u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks ��Ϣ��   
	*/
	u16  BoardRebootReq( const TTPBrdPos& tTPbrdPos );

	    /**
    * ����:	 	        ���ͻ�����ռ������
	* @param [in]       ��
	* @return           u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks ��Ϣ��   
	*/
	u16  BoardAudiomixReq();
	
	    /**
    * ����:	 	        ���ͻ���ϳ�ռ������
	* @param [in]       ��
	* @return           u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks ��Ϣ��   
	*/
	u16  BoardVmpReq();

	    /**
    * ����:	 	        ������������ռ������
	* @param [in]       ��
	* @return           u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks ��Ϣ��   
	*/
	u16  BoardBasStreamReq();

    /**
    * ����:	 	        ������ӵ���ǽ��������
	* @param [in]       ������Ϣ
	* @return           u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks ��Ϣ��   
	*/
	u16  TvwBoardAddReq( const TTPBrdPos& tTPBrdPos );

    /**
    * ����:	 	        �����޸ĵ���ǽ��������
	* @param [in]       ������Ϣ
	* @return           u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks ��Ϣ��   
	*/
	u16  TvwBoardModifyReq( const TTPBrdPos& tTPBrdPos );

    /**
    * ����:	 	        ����ɾ������ǽ��������
	* @param [in]       ������Ϣ��
	* @return           u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks ��Ϣ��   
	*/
	u16  TvwBoardDeleteReq( const TTPBrdPos& tTPBrdPos );

    /**
    * ����:	 	        ������ӵ���ǽ����ģʽ����
	* @param [in]       ģʽ��Ϣ
	* @return           u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks ��Ϣ��   
	*/
	u16  TvwBoardModeAddReq( const THduInfo& tTHduInfo );

    /**
    * ����:	 	        �����޸ĵ���ǽ����ģʽ����
	* @param [in]       ģʽ��Ϣ
	* @return           u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks ��Ϣ��   
	*/
	u16  TvwBoardModeModifyReq( const THduInfo& tTHduInfo );

    /**
    * ����:	 	        ����ɾ������ǽ����ģʽ����
	* @param [in]       ģʽλ��
	* @return           u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks ��Ϣ��   
	*/
	u16  TvwBoardModeDeleteReq( const TTPBrdPos& tTPBrdPos );

	    /**
    * ����:	 	        ������������ǽ��������
	* @param [in]       TTPBrdPos ����λ��
	* @return           u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks ��Ϣ��   
	*/
	u16  TvwBoardRebootReq( const TTPBrdPos& tTPbrdPos );

		    /**
    * ����:	 	        ����ǽ������������
	* @param [in]       const TTPBrdUpGrade& tBrdUpGrade   ������Ϣ
	* @return           u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks ��Ϣ��   
	*/
	u16  TvwBoardUpgradeReq(const TTPBrdUpGrade& tBrdUpGrade);


	    /**
    * ����:	 	        ��ӵ���ǽ�������
	* @param [in]       tHduStyleData ����ǽ�����Ϣ
	* @return           u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks ��Ϣ��   
	*/
	u16  AddTvwStyleReq( const THduStyleData& tHduStyleData  );

	    /**
    * ����:	 	        ɾ������ǽԤ������
	* @param [in]       tHduStyleData ����ǽ�����Ϣ
	* @return           u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks ��Ϣ��   
	*/
	//u16  TvwStyleDeleteReq();

	/** 
	* ����:  ����IP	 
	* @param [out]  cfg ��ip��Ϣ
	* @return u16 �ɹ�����0;ʧ�ܷ��ط�0������
	* @remarks	��� 
	*/ 
	u16  UpdateEthnetCfg( TTPEthnetInfo &tEthnetInfo );

    /* ����:	 gk ע������
    * @param [int]  tTvwInfo�����󲥷ŵĵ���ǽ��Ϣ
    * @return    
    * @remarks  �ɹ�����0��ʧ�ܷ��ش�����
    */
	u16 UpdateGKCfg( TTPGKCfg &tGkwInfo );

	/*��  ��	sipע��
	��  ��	 
	����ֵ	�ɹ�����0,ʧ�ܷ��ط�0������
	˵  ��	 */
	u16 UpdateSipCfg( TTPSipRegistrarCfg &tSipInfo );

	/**
    * ����:	 	        ���������������
	* @param [in]       ������Ϣ
	* @return           u16 �ɹ�����0,ʧ�ܷ��ط�0������
	*/
	u16  NetMngAddReq( const TTPNMServerCfg& tTPNMServerCfg );

    /**
    * ����:	 	        �����޸���������
	* @param [in]       ������Ϣ
	* @return           u16 �ɹ�����0,ʧ�ܷ��ط�0������
	*/
	u16  NetMngModifyReq( const TTPNMServerCfg& tTPNMServerCfg );

    /**
    * ����:	 	        ����ɾ����������
	* @param [in]       ������Ϣ
	* @return           u16 �ɹ�����0,ʧ�ܷ��ط�0������
	*/
	u16  NetMngDeleteReq( const TTPNMServerCfg& tTPNMServerCfg );

	/**
    * ����:	 	        �������¼�������
	* @param [in]       ¼�����Ϣ
	* @return           u16 �ɹ�����0,ʧ�ܷ��ط�0������
	*/
	u16  VTRAddReq( const TVcrCfg& tVTRCfg );

    /**
    * ����:	 	        �����޸�¼�������
	* @param [in]       ¼�����Ϣ
	* @return           u16 �ɹ�����0,ʧ�ܷ��ط�0������
	*/
	u16  VTRModifyReq( const TVcrCfg& tVTRCfgOld, const TVcrCfg& tVTRCfgNew );

    /**
    * ����:	 	        ����ɾ��¼�������
	* @param [in]       ¼�����Ϣ
	* @return           u16 �ɹ�����0,ʧ�ܷ��ط�0������
	*/
	u16  VTRDeleteReq( const TVcrCfg& tVTRCfg );

	
	/**
    * ����:  �������ģ������
	* @param [in]	const s8* strFileName	 ����ģ���ļ����� 
	* @return           u16 �ɹ�����0,ʧ�ܷ��ط�0������
	*/
	u16  ImportInfoReq(const s8* strFileName);

	/**
    * ����:  ��������ģ������
	* @param [in]	void 
	* @return           u16 �ɹ�����0,ʧ�ܷ��ط�0������
	*/
	u16  ExportInfoReq();

	/**
    * ����:  ������Ȩ����
	* @param [in]	void 
	* @return           u16 �ɹ�����0,ʧ�ܷ��ط�0������
	*/
	u16  ExportAuthReq();
	


private:
	TLoginInfo m_tLoginInfo;		//�洢��½������Ϣ



};

#define COMMONMGRIFPTR     CCommonMgrIF::GetSingletonPtr()          //�ӿ�ָ��

#endif // !defined(AFX_DATAMGRIMP_H__0DA134CE_DB83_4357_B0E6_8A6707CBC456__INCLUDED_)
