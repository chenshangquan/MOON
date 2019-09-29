/*****************************************************************************
ģ����      : ������cns�������ݵĽӿ�ģ��
�ļ���      : cnclibcommonif.h
����ļ�    : cnclib.h
�ļ�ʵ�ֹ���: UI����cnclib��cns�ķ���
����        : ������
�汾        : V1.0  Copyright(C) 2011-2012 KDC, All rights reserved.
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��         �汾        �޸���      �޸�����
2012/11/23     1.0						����
******************************************************************************/
#include "cnclib.h"
#include "cnsToolDll.h"
#ifndef CCNCLIBCOMMONIF_H
#define CCNCLIBCOMMONIF_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
class CCnclibCommonIF
{
public:

	static CCnclibCommonIF* GetComIF();
	~CCnclibCommonIF();
	u16 LinkCns();
	/** ����:  ����cns 
	*  @param[in] dwIp��¼IP,nPort��¼�˿�
	*  @return �ɹ�����0,ʧ�ܷ��ط�0������
	*/
	u16 connect( u32 dwIp, u32 dwPort);

	/** ����:  �Ͽ�cns 
	*  @param[in] 
	*  @return �ɹ�����0,ʧ�ܷ��ط�0������
	*/
	u16	DisConnect(); 
	
	/** ����:  ������������
	*  @param[in] tInfo ��������
	*  @return �ɹ�����0,ʧ�ܷ��ط�0������
	*  @remarks 
	*/
	u16 UpdateEthnetCfg( const TTPEthnetInfo& tInfo );

	/** ����:  CNS����SIPע������ 
	*  @param[in] tSipCfg Sipע������
	*  @return �ɹ�����0,ʧ�ܷ��ط�0������
	*/
	u16 CnsRegSipService( const TTPSipRegistrarCfg &tSipCfg );


	/** ����:  CNS����Gkע������ 
	*  @param[in] tSipCfg Sipע������
	*  @return �ɹ�����0,ʧ�ܷ��ط�0������
	*/
	u16 CnsRegGkService( const TTPGKCfg &tCfg );

	/**
	* ����:  ����cns��Ϣ 
	* @param[in] tInfo CNS��Ϣ  byIndex ��Ϣ��������(0Ϊcnc 1Ϊά������)
	* @return �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks 
	*/
	u16 UpdateCnsInfo( const TTPCnsInfo& tInfo, u8 byIndex );

	/** ����:  ����NAT����
	*  @param[in] tInfo NAT����
	*  @return �ɹ�����0,ʧ�ܷ��ط�0������
	*  @remarks 
	*/
	u16 UpdateNATCfg( const TTPNatCfg& tInfo );

	/** ����   ������Ƶ�ӿ�
	*  @param[in] atAudioPortInfo[3]  3����Ƶ�ӿ���Ϣ
	*  @return �ɹ�����0,ʧ�ܷ��ط�0������
	*/						
	u16 SetAudioPortInfoCmd( const TTpAudioPortInfo* atAudioPortInfo );		
	
	/** ����   ������Ƶ������
	*  @param[in] atAudioEqualizer[3]  3����Ƶ��������Ϣ
	*  @return �ɹ�����0,ʧ�ܷ��ط�0������
	*/						
	u16 SetAudioEqualizerCmd( const TTPEqualizer* atAudioEqualizer );		
				
	/** ����   ������Ƶ������
	*  @param[in] aAudioMixerInfo[4]  4�������
	*  @return �ɹ�����0,ʧ�ܷ��ط�0������
	*/					
	u16 SetAudiotMixerCmd( const u8* aAudioMixerInfo );		
					
	/** ����   ����Ĭ����Ƶ������
	*  @param[in] 
	*  @return �ɹ�����0,ʧ�ܷ��ط�0������
	*/					
	u16 SetDefaultMixerCmd( const u8* aAudioMixerInfo );		
						
	/** ����   ����Ĭ����Ƶ�ӿ�
	*  @param[in] 
	*  @return �ɹ�����0,ʧ�ܷ��ط�0������
	*/					
	u16 SetDefaultAudioPortCmd( const TTpAudioPortInfo* atAudioPortInfo );		
						
	/** ����   ����Ĭ����Ƶ������
	*  @param[in] 
	*  @return �ɹ�����0,ʧ�ܷ��ط�0������
	*/					
	u16 SetDefaultEqCmd( const TTPEqualizer* atAudioEqualizer );		
	
	/** ����   �������綪����Ϣ
	*  @param[in] 
	*  @return �ɹ�����0,ʧ�ܷ��ط�0������
	*/
	u16 LostPacketInfoReq();

	/** ����   ��������Ƶ���󷽰�
	*  @param[in] tVideoDiagInfo  ��Ƶ����
				  tAudioDiagInfo  ��Ƶ����
	*  @return �ɹ�����0,ʧ�ܷ��ط�0������
	*/	
	u16 SelAVMatrixCmd( const TTPVgaMixInfo& tVgaMixInfo );

	/** ����   ֹͣ��ϲ�������
	*  @param[in]
	*  @return �ɹ�����0,ʧ�ܷ��ط�0������
	*/	
	u16 StopAVMatrixReq();

	/** ����   ����Tpad�б�	
	*  @param[in] 
	*  @return �ɹ�����0,ʧ�ܷ��ط�0������
	*/								
	u16 UpdateTpadListReq();	

	/** ����   	����cns
	*  @param[in] 
	*  @return �ɹ�����0,ʧ�ܷ��ط�0������
	*/		
	u16 RebootCns();

	/** ����   	����cns
	*  @param[in] 
	*  @return �ɹ�����0,ʧ�ܷ��ط�0������
	*/		
	u16 UpgradeCns( const TTPFTPFileInfo& tVerFileInfo );

	/** ����   	���»�����Ϣҳ����Ϣ
	*  @param[in] 
	*  @return �ɹ�����0,ʧ�ܷ��ط�0������
	*/		
	u16 RefreshBasicInfo();
	/** 
	* ����  	ѡ�������
	* @param [in] 	 TCameraMemInfo  
	* @return  
	* @remarks 
	*/		
	u16 CamSelCmd( const u8& byCameraIndx );	
	/** 
	* ����  	�ָ������Ĭ�ϲ���
	* @param [in] 	   
	* @return  
	* @remarks 
	*/	
	u16 CamResetCmd();	

	/** 
	* ����  	��Ұ����
	* @param [in] 	 EmZoom  ��Ϊ:Զ����
	* @return  
	* @remarks 
	*/	
	u16 SetCamZoomCmd( const EmZoom& emZoom );	

	/** 
	* ����  	��Ұ�Ƿ���OSD����ʾ����
	* @param [in] 	 EmOSDShow  ��Ϊ:on��off
	* @return  
	* @remarks 
	*/	
	u16 SetCamOSDCmd( const EmOSDShow& emOSDShow );	
	/** 
	* ����  	������Զ��۽�
	* @param [in] 	 
	* @return  
	* @remarks 
	*/		
	u16 SetCamAutoFocusCmd(const EmFocusMode& emFocusMode);
	/** 
	* ����  	������ֶ��۽�
	* @param [in] 	 EmFocus : Զ��/����	EmCnAction :  ��ʼ/ֹͣ
	* @return  
	* @remarks 
	*/	
	u16 SetCamFocusCmd( const EmFocus& emFocus, const EmCnAction& emCnAction );	

	/** 
	* ����  	����Ԥ��λ����
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	u16 CamPresetSaveCmd();		
	/** 
	* ����  	���ÿ�������Ԥ��λ1
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	u16 SetCamPresetMoveCmd( const BOOL& bPresetMove );	
	/** 
	* ����  	�����Զ��ع�
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	u16 CamAutoExposureCmd( EmExpMode emExpAuto );
	/** 
	* ����  	����
	* @param [in] 	 EmGain ���淶Χ 0dB  3dB  6dB ������42dB
	* @return  
	* @remarks 
	*/	
	u16 CamGainCmd( const EmGain& emGain );	

	/** 
	* ����  ���ŵ���	���ŷ�Χ 1/60  1/120 1/250.....1/4000  1/10000
	* @param [in]  EmShutSpd
	* @return  
	* @remarks 
	*/
	u16 CamShutSpdCmd( const EmShutSpd& emShutSpd );

	/** 
	* ����  ����ģʽ����
	* @param [in]  EmBackLightType  ����ģʽ:�رգ�multi��Ĭ��7����Χ0-15����center��face detect
	*			   u8  = TP_INVALID_INDEX ��multiģʽ  0--15 multiģʽ����
	* @return  
	* @remarks 
	*/
	u16 CamBackLightCmd( const EmBackLightType& emBackLightType, const u8& byMulti );

	/** 
	* ����  ��Ȧ��С����
	* @param [in]  u8  ��Ȧ��С ��Χ 0--100			   
	* @return  
	* @remarks 
	*/	
	u16 CamAperture( const u8& byAperture);	

	/** 
	* ����  ��ƽ�����(��Ϊ�Զ����ֶ�)
	* @param [in] 		   
	* @return  
	* @remarks 
	*/		
	u16 CamAutoWBCmd( const EmWBMode& emWBMode );	

	/** 
	* ����  R+����
	* @param [in] 	u16  R Gain ��Χ 0--100	   
	* @return  
	* @remarks 
	*/		
	u16 CamRGainCmd( const u16& wRGain );

	/** 
	* ����  B+����
	* @param [in] 	u16  B Gain ��Χ 0--100	   
	* @return  
	* @remarks 
	*/		
	u16 CamBGainCmd( const u16& wBGain );

	/** 
	* ����  ģʽ����  
	* @param [in] 	EmPicSceMode  ��Ϊ:�չ��/̫����/�ֶ�
	* @return  
	* @remarks 
	*/	
	u16 CamPicSceneModeCmd( const EmPicSceMode& emPicSceMode );	

	/** 
	* ����  �ֶ�ģʽ�е�CAMMA����  
	* @param [in] 	EmGamma  ��Ϊ:emGammaOff��emGammaOn ��emSmart1�� emStrat2
	* @return  
	* @remarks 
	*/	
	u16 CamGammaCmd( const EmGamma& emGamma );

	/** 
	* ����  �ֶ�ģʽ�еĹ�Ȧ����  
	* @param [in]   u8 ��Ȧ��С  1--15
	* @return  
	* @remarks 
	*/	
    u16 CamPicSceAptCmd( const u8& byPicSceApt );

	/** 
	* ����  ͼƬ�����еĶԱȶȵ���
	* @param [in]   u16  ��С  0--200
	* @return  
	* @remarks 
	*/		
	u16 CamContrastCmd( const u16& wContrast );	

	/** 
	* ����  ͼƬ�����е�ɫ�ȵ���
	* @param [in]   u16  ��С  0--200
	* @return  
	* @remarks 
	*/		
	u16 CamHueCmd( const u16& wHue );

	/** 
	* ����  ͼƬ�����еı��Ͷȵ���
	* @param [in]   u16  ��С  0--200
	* @return  
	* @remarks 
	*/	
	u16 CamSaturatCmd( const u16& wSaturat );

	/** 
	* ����  ͼƬ�����е����ȵ���
	* @param [in]   u16  ��С  0--200
	* @return  
	* @remarks 
	*/	
	u16 CamBrightCmd( const u16& wBright );	

	/** 
	* ����  ����---����������˵�������
	* @param [in]   EmStmClean  Ĭ��LOW  ��ΧOFF,LOW,MID,HIGH
	* @return  
	* @remarks 
	*/	
	u16 CamNRStmCleanCmd( const EmStmClean& emStmClean );

	/** 
	* ����  ����---3D�����������
	* @param [in]   Em3DNR   em3DNROff ��OFF��em3DNROn ��
	* @return  
	* @remarks 
	*/	
	u16 Cam3DNRCmd( const Em3DNR& em3DNR );	

	/** 
	* ����  	����������͵���֪ͨ
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	u16 SetLoadCameraFileNty();

	/** 
	* ����  ����zoom
	* @param [in]
	* @return  
	* @remarks 
	*/	
	u16 SetCamZoomCmd( const u16& wZoom );	

	/**
    * ����:	 	        ���������������
	* @param [in]       ������Ϣ
	* @return           u16 �ɹ�����0,ʧ�ܷ��ط�0������
	*/
	u16  NetMngAddCmd( const TTPNMServerCfg& tTPNMServerCfg );

    /**
    * ����:	 	        �����޸���������
	* @param [in]       ������Ϣ
	* @return           u16 �ɹ�����0,ʧ�ܷ��ط�0������
	*/
	u16  NetMngModifyCmd( const TTPNMServerCfg& tTPNMServerCfg );

    /**
    * ����:	 	        ����ɾ����������
	* @param [in]       ������Ϣ
	* @return           u16 �ɹ�����0,ʧ�ܷ��ط�0������
	*/
	u16  NetMngDeleteCmd( const TTPNMServerCfg& tTPNMServerCfg );

    /**
    * ����:	 	        ���ú��з�������ַ�����и�ʽ
	* @param [in]       ���з�������Ϣ
	* @return           u16 �ɹ�����0,ʧ�ܷ��ط�0������
	*/
	u16  CallServerCmd( const TTPCallSerInfo& tCallSerInfo );
   
	/**
    * ����:	 	        ����������������ַ
	* @param [in]       ������������ַ
	* @return           u16 �ɹ�����0,ʧ�ܷ��ط�0������
	*/
	u16  UpgradeSerCmd( const TTPUpgradeSer& tUpgradeSer );

	/** ����   ̨���ļ��ϴ��ɹ�֪ͨ
	*  @param[in] byIndex ��Ϣ��������(0Ϊcnc 1Ϊά������)
	*  @return �ɹ�����0,ʧ�ܷ��ط�0������
	*/
	u16 ConfSignCmd( const BOOL& bOk, u8 byIndex );
 
	/**
    * ����:	 	        ���û�����ѡ��ʽ
	* @param [in]       
	* @return           u16 �ɹ�����0,ʧ�ܷ��ط�0������
	*/
	u16  VideoFormatCmd( const TTPVidForamt& tVidForamt );
 
	/**
    * ����:	 	        ������ʾ��ѡ��ʽ
	* @param [in]       
	* @return           u16 �ɹ�����0,ʧ�ܷ��ط�0������
	*/
	u16  DualVideoFormatCmd( const TTPVidForamt& tVidForamt );
 
	/**
    * ����:	 	        ���õ�������
	* @param [in]       
	* @return           u16 �ɹ�����0,ʧ�ܷ��ط�0������
	*/
	u16  CallRateCmd( const u16 wCallRate );
 
	/**
    * ����:	 	        ������ʾ����
	* @param [in]       
	* @return           u16 �ɹ�����0,ʧ�ܷ��ط�0������
	*/
	u16  DualCallRateCmd( const u16 wDualCallRate );
 
	/**
    * ����:	 	        ���û�������״̬
	* @param [in]       
	* @return           u16 �ɹ�����0,ʧ�ܷ��ط�0������
	*/
	u16  ConfDisCmd( const BOOL& bDis );
 
	/**
    * ����:	 	        ���û�����ѯ��Ϣ
	* @param [in]       
	* @return           u16 �ɹ�����0,ʧ�ܷ��ط�0������
	*/
	u16  ConfPollCmd( const TTPPollInfo& tPollInfo );
  
	/**
    * ����:	 	        ������Ƶ��ʽ��Ϣ
	* @param [in]       
	* @return           u16 �ɹ�����0,ʧ�ܷ��ط�0������
	*/
	u16  AudioFormatCmd( const EmTpAudioFormat& emAudioFormat );
  
	/**
    * ����:	 	        �����пص���ǽ��Ϣ
	* @param [in]       
	* @return           u16 �ɹ�����0,ʧ�ܷ��ط�0������
	*/
	u16  SetDisplayCmd( BOOL bDisplay, const TTPDisplayType& tDisplayType1, const TTPDisplayType& tDisplayType3 );
 
private:
	CCnclibCommonIF();
private:
	static CCnclibCommonIF*	m_pThis;
	TLoginInfo m_tLoginInfo;		//�洢��½������Ϣ

};

#define COMIFMGRPTR   CCnclibCommonIF::GetComIF()

#endif