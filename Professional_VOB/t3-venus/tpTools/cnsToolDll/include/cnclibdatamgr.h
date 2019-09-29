/*****************************************************************************
ģ����      : ������ص�cnclib����ģ��
�ļ���      : cnclibdatamgr.h
����ļ�    : cnclib.h
�ļ�ʵ�ֹ���: ת������cnclib����Ϣ���ṩ����cnclib�Ľӿ�
����        : ������
�汾        : V1.0  Copyright(C) 2011-2012 KDC, All rights reserved.
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��         �汾        �޸���      �޸�����
2012/11/23     1.0						����
******************************************************************************/
#include "cnsToolDll.h"
#include "cnclib.h"
#include "msgdispatch.h"
#include "sessionmgr.h"

#ifndef CCNCLIBDATAMGR_H
#define CCNCLIBDATAMGR_H

class CCnclibDataMgr : public CWnd
{
public:

	~CCnclibDataMgr();
	/** ����   ��ʼ��CCnclibDataMgr��
	*  @param[out]
	*  @return 
	*/
	void InitDataMgr();
	    

    /**
	* ����:  ��ȡ����cns����״̬
	* @param [out]tConfInfo  ����cns�μӵĻ�����Ϣ
	* @return �ɹ�����TRUE,ʧ�ܷ���FALSE
	* @remarks 
	*/
    TTPCnsConfStatus GetLocalCnsConfState() const; 

   
	/** ����:  �жϱ���cns�����Ƿ����� 
	*  @param[in] 
	*  @return �ɹ�����true,ʧ�ܷ���false
	*/
	BOOL32 IsInConf();
    
	/** ����   �����������
	*  @param[out] tInfo ��������
	*  @return �ɹ�����0,ʧ�ܷ��ط�0������
	*/
	u16 GetEthnetCfg( TTPEthnetInfo& tInfo );

	/** ����   ���SIP����
	*  @param[in] tSipCfg SIP����
	*  @return �ɹ�����0,ʧ�ܷ��ط�0������
	*/
	u16 GetSipCfg( TTPSipRegistrarCfg& tSipCfg )const;


    /** ����   ���Gk����
	*  @param[in] tGkCfg
	*  @return �ɹ�����0,ʧ�ܷ��ط�0������
	*/
	u16 GetGkCfg( TTPGKCfg& tGkCfg )const;
	
	/** ����   ���CCnclibDataMgr�����ָ��
	*  @param[in] 
	*  @return �ɹ�����CCnclibDataMgr���͵�ָ��
	*/
	static CCnclibDataMgr* GetDataMgrIF();

	/**
	* ����:	��ȡ��¼cns��IP
	*  @param[in] u32  IP
	*  @return  
    */
	u16 GetLoginIp( u32 &dwIP )const;

	/**
	* ����:  ��ȡcns��Ϣ:CNS�᳡���ơ����롢��ַ���������Ƿ���˫��Դ 
	*  @param[in] tCnsInfo����CNS��Ϣ
	*  @return �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks 
	*/
	u16 GetLocalCnsInfo( TTPCnsInfo& tCnsInfo )const;

	/** ����   ���NAT����
	*  @param[in] tInfo NAT����
	*  @return �ɹ�����0,ʧ�ܷ��ط�0������
	*/
	u16 GetNATCfg( TTPNatCfg& tInfo )const;

	/** ����   ��ȡ�п���ʾ����Ϣ
	*  @param[in]tCentreTVCfg  ��ʾ������״̬��Ϣ
	*  @return �ɹ�����0,ʧ�ܷ��ط�0������
	*/
	TCentreTVCfg* GetCentreTVCfg()const;

	/** ����   ��ȡ�п��������Ϣ
	*  @param[in]vecTCnCameraCfg  ���������״̬��Ϣ
	*  @return �ɹ�����0,ʧ�ܷ��ط�0������
	*/
	u16 GetCamInfo( vector<TCnCameraCfg>& vecTCnCameraCfg )const;

	/** ����   �����Ƶ�ӿ���Ϣ
	*  @param[in]pAudioPortInfo   ��Ƶ�ӿ���Ϣ
	*  @return �ɹ�����0,ʧ�ܷ��ط�0������
	*/
	u16 GetAudioPortInfo( TTpAudioPortInfo** pAudioPortInfo )const;

	/** ����   �����Ƶ��������Ϣ
	*  @param[in]pAudioPortInfo   ��Ƶ��������Ϣ
	*  @return �ɹ�����0,ʧ�ܷ��ط�0������
	*/
	u16 GetAudioEqualizer( TTPEqualizer** pEqualizer )const;

	/** ����   �����Ƶ��������Ϣ
	*  @param[in]pAudioPortInfo   ��Ƶ��������Ϣ
	*  @return �ɹ�����0,ʧ�ܷ��ط�0������
	*/
	u16 GetAudiotMixer( u8** pAudioMixerInfo )const;

	/** ����   ������綪����Ϣ
	*  @param[in]tLostPacketInfo  ���綪����Ϣ
	*  @return �ɹ�����0,ʧ�ܷ��ط�0������
	*/
	u16 GetLostPacketInfo( u8& tLostPacketInfo )const;

	/** ����   ���������������Ϣ
	*  @param[in]TTPUpDownSpeedInfo   �ϴ�������Ϣ
	*  @return �ɹ�����0,ʧ�ܷ��ط�0������
	*/
	u16 GetUpDownstreamRate( TTPUpDownSpeedInfo& tUpDownSpeedInfo )const;

	/** ����   ��ȡ��Ƶ�˿���Ͻ��
	*  @param[in]tVideoDiagInfo  ��Ƶ�˿������Ϣ
	*  @return �ɹ�����0,ʧ�ܷ��ط�0������
	*/
	u16 GetVideoDiagInfo( TTPVideoDiagInfo& tVideoDiagInfo )const;

	/** ����   ��ȡ��Ƶ�˿���Ͻ��
	*  @param[in]tAudioDiagInfo  ��Ƶ�˿������Ϣ
	*  @return �ɹ�����0,ʧ�ܷ��ط�0������
	*/
	u16 GetAudioDiagInfo( TTPAudioDiagInfo& tAudioDiagInfo )const;

	/** ����   ���Tpad�б���Ϣ
	*  @param[in]tTPadList   Tpad�б���Ϣ
	*  @return �ɹ�����0,ʧ�ܷ��ط�0������
	*/
	u16 GetTpadList( TTPTPadList& tTPadList )const;

	/** ����   ���CPU/�ڴ���Ϣ
	*  @param[in]
	*  @return �ɹ�����0,ʧ�ܷ��ط�0������
	*/
	u16 GetSysInfo( TTPSysInfo& tSysInfo )const;


	/** ����   ��û�����Ϣ
	*  @param[in]
	*  @return �ɹ�����0,ʧ�ܷ��ط�0������
	*/
	u16 GetCnConfStatus( TTPCnsConfStatus& tCnsConfStatus )const;

	/** ����   ��û�����Ϣ2
	*  @param[in]
	*  @return �ɹ�����0,ʧ�ܷ��ط�0������
	*/
	u16 GetCnConfVideoParam( TTPCnConfInfo& tCnVideoParam )const;

	/** 
	* ����  	��ȡ��ѡ�е������
	* @param [in] 	 
	* @return  �ɹ�����0,ʧ�ܷ��ط�0������
	*/		
	u16 GetCamSel( u8& byCameraIndx )const;

	/** 
	* ����  	��ȡ��Ұ�Ƿ���OSD����ʾ����
	* @param [in] 	 
	* @return  �ɹ�����0,ʧ�ܷ��ط�0������
	*/	
	u16 GetCamOSD( EmOSDShow& emOSDShow )const;

	/** 
	* ����  	��ȡ�����Ƿ����Ԥ��λ1״̬
	* @param [in] 	 
	* @return  �ɹ�����0,ʧ�ܷ��ط�0������
	*/	
	u16 GetCamPresetMove( BOOL& bUsed )const;

	/** 
	* ����  	��ȡ���������ֵ
	* @param [in] 	 
	* @return  �ɹ�����0,ʧ�ܷ��ط�0������ 
	*/	
	u16 GetCamGain( EmGain& emGain )const;

	/** 
	* ����  	��ȡ���������ֵ
	* @param [in] 	 
	* @return  �ɹ�����0,ʧ�ܷ��ط�0������ 
	*/	
	u16 GetCamShutSpd( EmShutSpd& emShutSpd )const;

	/** 
	* ����  	��ȡ���������ģʽ
	* @param [in] 	 
	* @return  �ɹ�����0,ʧ�ܷ��ط�0������
	*/	
	u16 GetCamBackLightType( EmBackLightType& emBackLightType )const;

	/** 
	* ����  	��ȡ���������ģʽ��Ӧ��ֵ
	* @param [in] 	 
	* @return  �ɹ�����0,ʧ�ܷ��ط�0������
	*/	
	u16 GetCamBackLightIndex( u8& byMulti)const;

	/** 
	* ����  	��ȡ�������Ȧ��С
	* @param [in] 	 
	* @return  �ɹ�����0,ʧ�ܷ��ط�0������
	*/	
	u16 GetCamAperture( u8& byAperture )const;

	/** 
	* ����  	��ȡ�������ƽ�����ģʽRGain
	* @param [in] 	 
	* @return  
	*/	
	u16 GetCamRGain( u16& wRGain )const;

	/** 
	* ����  	��ȡ�������ƽ�����ģʽBGain
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	virtual u16 GetCamBGain( u16& wBGain)const;

	/** 
	* ����  	��ȡ�����Picģʽ����״̬
	* @param [in] 	 
	* @return  EmPicSceMode  ��Ϊ:�չ��/̫����/�ֶ�
	* @remarks 
	*/	
	u16 GetCamPicSceneMode( EmPicSceMode& emPicSceMode )const;

	/** 
	* ����  	��ȡ�����PicģʽCAMMA����״̬
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	u16 GetCamGamma( EmGamma& emGamma )const;

	/** 
	* ����  	��ȡ�����Picģʽ��Ȧ����ֵ
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	u16 GetCamPicSceApt( u8& byPicSceApt )const;

	/** 
	* ����  	��ȡ�����ͼƬ�����еĶԱȶ�ֵ
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	u16 GetCamContrast( u16& wContrast )const;

	/** 
	* ����  	��ȡ�����ͼƬ�����е�ɫ��ֵ
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	u16 GetCamHue( u16& wHue )const;

	/** 
	* ����  	��ȡ�����ͼƬ�����еı��Ͷ�ֵ
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	u16 GetCamSaturat( u16& wSaturat )const;

	/** 
	* ����  	��ȡ�����ͼƬ�����е�����ֵ
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	u16 GetCamBright( u16& wBright )const;

	/** 
	* ����  	��ȡ�����������ģʽ
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	u16 GetCamNRStmClean( EmStmClean& emStmClean )const;

	/** 
	* ����  	��ȡ�����3D�������ģʽ
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	u16 GetCam3DNR( Em3DNR& em3DNR )const;	

	/** 
	* ����  	��ȡ��ǰ���������
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	u16 GetCamCfg( TCnCameraCfg& tCnCameraCfg )const;

	/** 
	* ����  	��ȡ�ع�ģʽ
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	u16 GetCamExpMode( EmExpMode& emExpMode )const;

	/** 
	* ����  	��ȡ��ƽ��ģʽ
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	u16 GetCamWBMode( EmWBMode& emExpMode )const;

	/** 
	* ����  	��ȡzoom
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	u16 GetCamZoom( u16& wZoom )const;

	/** 
	* ����  	��ȡ���ܷ���������
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	u16 GetNetMngData( vector<TTPNMServerCfg> &vecTTPNMServerCfg )const;


    /** ����   �����ʾԴ��Ϣ
	*  @param[out] tDualSrcinfo ��ʾԴ����
	*  @return �ɹ�����0,ʧ�ܷ��ط�0������
	*/
    u16 GetDualSrcInfo( TDualSrcInfo& tDualSrcinfo );

	/** 
	* ����  	��ȡ��ʾԴ����ӿ���Ϣ
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	u16 GetVgaMixInfo( TTPVgaMixInfo &tVgaMixInfo )const;
	/** 
	* ����  	��ȡ���з�������Ϣ
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	u16 GetCallServerInfo( TTPCallSerInfo& tCallSerInfo )const;
	/** 
	* ����  	��ȡ������������ַ
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	u16 GetUpgradeSerInfo( TTPUpgradeSer& tUpgradeSer )const;
	/** 
	* ����  	��ȡ������ѡ��ʽ
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	u16 GetVideoFormatInfo( TTPVidForamt& tVidForamt )const;
	/** 
	* ����  	��ȡ��ʾ��ѡ��ʽ
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	u16 GetDualVideoFormatInfo( TTPVidForamt& tVidForamt )const;
	/** 
	* ����  	��ȡ��������
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	u16 GetCallRateInfo( u16& wCallRate )const;
	/** 
	* ����  	��ȡ��ʾ����
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	u16 GetDualCallRateInfo( u16& wDualCallRate )const;
	/** 
	* ����  	��ȡ������ѯ��Ϣ
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	u16 GetConfPollInfo( TTPPollInfo& tPollInfo )const;
	/** 
	* ����  	��ȡ����������Ϣ
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	u16 GetConfDisInfo( BOOL& bDis )const;
	/** 
	* ����  	��ȡ��Ƶ��ʽ��Ϣ
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	EmTpAudioFormat GetAudioFormatInfo()const;
	/** 
	* ����  	��ȡ�᳡�Ƿ������ʾ
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	bool IsRcvDual();
	/** 
	* ����  	��ȡ�пص���ǽ����״̬
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	BOOL GetDisplayState() const;
	/** 
	* ����  	��ȡ�пص���ǽ��ʾ��1���ź�Դ
	* @param [in] 	 
	* @return  
	* @remarks 
	*/		
	TTPDisplayType GetDisplayType1() const;
	/** 
	* ����  	��ȡ�пص���ǽ��ʾ��3���ź�Դ
	* @param [in] 	 
	* @return  
	* @remarks 
	*/		
	TTPDisplayType GetDisplayType3() const;

protected:
    virtual BOOL PreCreateWindow( CREATESTRUCT& cs );
    virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam); 
private:
	CCnclibDataMgr();

private:
	static CCnclibDataMgr* m_pThis;
};

#define LIBDATAMGRPTR   CCnclibDataMgr::GetDataMgrIF()

#endif