/*****************************************************************************
ģ����      : ������moon90�������ݵĽӿ�ģ��
�ļ���      : moonlibcommonif.h
����ļ�    : moonlib.h
�ļ�ʵ�ֹ���: UI����cnclib��cns�ķ���
����        : ���`�`
�汾        : V1.0  Copyright(C) 2011-2012 KDC, All rights reserved.
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��         �汾        �޸���      �޸�����
2014/11/26     1.0						����
******************************************************************************/
#include "rkclib.h"
#include "moonToolDll.h"
#ifndef CMOONLIBCOMMONIF_H
#define CMOONLIBCOMMONIF_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
class CMoonlibCommonIF
{
public:

	static CMoonlibCommonIF* GetComIF();
	~CMoonlibCommonIF();

    /**** rkcsysctrl ***/

    //����Socket����
    //u16 SocketConnect(s8* pchIP, u32 dwPort);
    //�Ͽ�Socket����
    //u16 CloseSocket();
    //����Socket��Ϣ
    //u16 SendLoginReq(TRK100LoginInfo tRK100LoginInfo);
    //�����޸�����������Ϣ
    //u16 SendModifyPasswordReq(TRK100LoginInfo tRK100LoginInfo);
    //�ж��Ƿ��¼
    //bool IsLoginState();
    
    //��õ�¼������
    //u16 GetLoginBackInfo(TRK100MsgHead& tRK100MsgHead);

    /**** camerconfig ***/

	u16 LinkMoon();
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

	/** 
	* ����: ��Ұ����
	* @param [in]  EmZoom ��Ϊ:Զ/��
	* @return  
	* @remarks 
	*/	
	u16 SetCamZoomCmd( const EmTPZOOM& emZoom, u8 byIndex);	

	u16 SetCamZoomValueCmd( const u32& dwZoom, u8 byIndex );

	u16 SetCamZoomStopCmd(u8 byIndex);

	/** 
	* ����: ������Զ��۽�
	* @param [in] 	 
	* @return  
	* @remarks 
	*/		
	u16 SetCamAutoFocusCmd(const EmTPMOOMMode& emFocusMode);

	/** 
	* ����: ѡ�������
	* @param [in] 	 TCameraMemInfo  
	* @return  
	* @remarks 
	*/		
	u16 CamSelCmd( const u8& byCameraIndx );

	/** 
	* ����: ͬ�����������
	* @param [in] 	 TCameraMemInfo  
	* @return  
	* @remarks 
	*/		
	u16 SetMoonCamCfgSyncCmd( const u8& byCameraIndx );

	/** 
	* ����: ѡ�������
	* @param [in] 	 TCameraMemInfo  
	* @return  
	* @remarks 
	*/		
	u16 CamStyleSelCmd( const EmTPMechanism& emTPMechanism );

	/** 
	* ����: ѡ��Gamma
	* @param [in] 	 TCameraMemInfo  
	* @return  
	* @remarks 
	*/		
	u16 GammaStyleSelCmd( const EmH650Gamma& enH650Gamma );
	/** 
	* ����: ���Dʱ����������Ϣ
	* @param [in] 	 TCameraMemInfo  
	* @return  
	* @remarks 
	*/	
	u16 SetCamFocusNearCmd();

	/** 
	* ����: ���Upʱ����������Ϣ
	* @param [in] 	 TCameraMemInfo  
	* @return  
	* @remarks 
	*/	
	u16 SetCamFocusStopCmd();

	/** 
	* ����: ���Dʱ������Զ��Ϣ
	* @param [in] 	 TCameraMemInfo  
	* @return  
	* @remarks 
	*/	
	u16 SetCamFocusFarCmd();

	/** 
	* ����: �Ƿ��Զ��ع�
	* @param [in] 	 TCameraMemInfo  
	* @return  
	* @remarks 
	*/
	u16 CamAutoExposureCmd( EmTPMOOMMode emExpAuto );

	/** 
	* ����: ��Ȧ�л���Ϣ����
	* @param [in] 	 TCameraMemInfo  
	* @return  
	* @remarks 
	*/
	u16 CamApertureCmd( const EmTPAperture &emTPAperture );

	/** 
	* ����: �����л���Ϣ����
	* @param [in] 	 TCameraMemInfo  
	* @return  
	* @remarks 
	*/
	u16 CamShutSpdCmd( const EmTPSOrThShutter& emShutSpd );

	u16 CamTwShutSpdCmd( const EmTPFOrTwShutter& emTwShutter);

	/** 
	* ����: �����л���Ϣ����
	* @param [in] 	 TCameraMemInfo  
	* @return  
	* @remarks 
	*/
	u16 CamGainCmd( const EmTPExpGain& emGain );

	/** 
	* ����: �Ƿ��Զ���ƽ��
	* @param [in] 	   
	* @return  
	* @remarks 
	*/
	u16 CamAutoWBCmd( const EmTPMOOMMode& emWBAuto );

	/** 
	* ����: ��ɫ�����������
	* @param [in] 	   
	* @return  
	* @remarks 
	*/
	u16 CamRGainCmd( const u32& dwRGain );

	/** 
	* ����: ��ɫ�����������
	* @param [in] 	   
	* @return  
	* @remarks 
	*/
	u16 CamBGainCmd( const u32& dwBGain );

	u16 CamAdjustRangeCmd( const u32& dwAdjustRange );

	u16 CamHoriStretchCmd( const u32& dwHoriStretch );

	/** 
	* ����: ͼƬ��������
	* @param [in] 	   
	* @return  
	* @remarks 
	*/
	u16 CamImageParaCmd( EmTPImagePara emImagePara, const u32& dwImagePara );

	/** 
	* ����: ͼƬ��������
	* @param [in] 	   
	* @return  
	* @remarks 
	*/
	u16 CamLightPensation( BOOL bIsOpen );

	u16 CamKeystoneAdjust(const TTPDistortParam& tTPDistortParam,EmTPCorrect emMyOpetion);

	u16 SetColorRGBDirectCmd(u8 nPosition, EmTPColorConsistency emMyCorConsOption, const u32& dwRGBDirectValue);

	/** 
	* ����: ����
	* @param [in] 	   
	* @return  
	* @remarks 
	*/
	u16 CamNRCmd(BOOL bIsOpen, EmTPFpgaReduNoise emTPReduNoise);

	/** 
	* ����: 2D����
	* @param [in] 	   
	* @return  
	* @remarks 
	*/
	u16 Cam2DNRCmd(BOOL bIsOpen, EmTPReduNoise emTPReduNoise);

	/** 
	* ����: 3D����
	* @param [in] 	   
	* @return  
	* @remarks 
	*/
	u16 Cam3DNRCmd(BOOL bIsOpen, EmTPReduNoise emTPReduNoise);

	u16 CamOrderPosCheckCmd( BOOL bCheck );

	u16 SetOutPortTypeCmd( EmTPDVIOutPortType emDVIOutPortType, EmTPMOONOutMode emMOONOutMode );

	u16 SetImageAdjustCmd( EmTPImageAdjust emImageAdjust );

	/** ����:  ������������
	*  @param[in] tInfo ��������
	*  @return �ɹ�����0,ʧ�ܷ��ط�0������
	*  @remarks 
	*/
	u16 UpdateEthnetCfg( const TTPEthnetInfo& tInfo );

	u16 CamPreSetSaveCmd( const TTPCamPre& tTPCamPre );

	u16 OrderPosDeleteReq( const TTPCamPre& tTPCamPre );

	u16 OrderPosInvokeCmd( const TTPCamPre& tTPCamPre );
	
	u16 CamPreSetModifyCmd( const TTPCamPre& tTPCamPre );

	u16 CamParamUploadCmd();
	
	u16 CamParamUploadNty(BOOL bSuccess);

	u16 UpgradeMoon( const s8* chVerFileInfo );

	u16 UpdateMoonMechanism( const s8* chVerFileInfo );

	/** ����   	����moon
	*  @param[in] 
	*  @return �ɹ�����0,ʧ�ܷ��ط�0������
	*/		
	u16 RebootMoon();

	u16 MoonCamResetCmd(u8 byIndex);
	/** ����   	����LVDS������
	*  @param[in] 
	*  @return �ɹ�����0,ʧ�ܷ��ط�0������
	*/
	u16 SetBaudRateCmd( EmTPLVDSBaud emBaudRate );
	/** ����   	�ο�������
	*  @param[in] 
	*  @return �ɹ�����0,ʧ�ܷ��ط�0������
	*/
	u16 SetReferenceLineCmd( BOOL bOpen );
	/** ����   	ˮƽ��ת����
	*  @param[in] 
	*  @return �ɹ�����0,ʧ�ܷ��ط�0������
	*/
	u16 SetHorizontalFlipCmd( BOOL bOpen );
	/** ����   	�������ν�����������
	*  @param[in] 
	*  @return �ɹ�����0,ʧ�ܷ��ط�0������
	*/
	u16 SetTrapezoidalCorCmd( BOOL bOpen );

    u16 SetShowRectRegionCmd( BOOL bOpen );

	u16 SetRgbConsistSwitchCmd(BOOL bOpen);
	/** ����   ���ӡ��������β���
	 *  @param[in] emMyCorOption ���ĸ��������в���  emChangeOption ���ӻ����
	 *  @return �ɹ�����0,ʧ�ܷ��ط�0������
	 *  @remarks 
	 */
	u16 SetTraCorParamCmd( EmTPCorrect emMyCorOption,EmTPCorrectChange emChangeOption );

	//������ɫһ����RGB
	u16 SetCorConsistRGBCmd( u8 nPosition, EmTPColorConsistency emMyCorConsOption,EmTPCorrectChange emChangeOption );

	u16 SetChangeDistortCmd( u8 byIndex, EmTPCorrectChange emTPCorrectChange, EmTPDistortPosition emTPDistortPosition );

	u16 SetDirectDistortCmd( const TTPDistortInfo& tTpDistortInfo );

	u16 SetAutoSetColorConstancyCmd();

	u16 SetChooseRectangleCmd(const TTPMoonRectRegion& tTPMoonRectRegion);

	u16 SnapShotCmd( );

	//������ʱ��������
    u16 SetDelayCorrectCmd( u8 nPosition, u32 dwDelay );


private:
	CMoonlibCommonIF();
private:
	static CMoonlibCommonIF*	m_pThis;
	TCamLoginInfo m_tCamLoginInfo;		//�洢��½������Ϣ(�˴�ֻ�õ�ip)
};

#define COMIFMGRPTR   CMoonlibCommonIF::GetComIF()

#endif