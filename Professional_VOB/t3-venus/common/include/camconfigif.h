/*****************************************************************************
ģ����      : moon90 moonlib�ӿ�
�ļ���      : camconfigif.h
����ļ�    : 
�ļ�ʵ�ֹ���: �������/����
����        : ���`�`
�汾        : V1.0  Copyright(C) 2011-2012 KDC, All rights reserved.
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��      �汾        �޸���      �޸�����
2014/11/26  1.0         ���`�`        ����
******************************************************************************/
#ifndef __CAMCONFIGIF_H__
#define __CAMCONFIGIF_H__

#include "kdvdispevent.h"
#include "moonstruct.h"
#include <vector>

class CCamConfigIF : public CKdvDispEvent
{
public:
	/** 
	* ����  	ѡ�������
	* @param [in] 	 TCameraMemInfo  
	* @return  
	* @remarks 
	*/		
	virtual u16 CamSelCmd( const u8& byCameraIndx ) = 0;

	/** 
	* ����  	ͬ�����������
	* @param [in] 	 TCameraMemInfo  
	* @return  
	* @remarks 
	*/		
	virtual u16 SetMoonCamCfgSyncCmd( const u8& byCameraIndx ) = 0;
	
	/** 
	* ����  	ѡ���������о
	* @param [in] 	 TCameraMemInfo  
	* @return  
	* @remarks 
	*/		
	virtual u16 CamStyleSelCmd( const EmTPMechanism& emTPMechanism ) = 0;

	/** 
	* ����  	ѡ��Gamma
	* @param [in] 	 TCameraMemInfo  
	* @return  
	* @remarks 
	*/	
	virtual u16 GammaStyleSelCmd( const EmH650Gamma& enH650Gamma ) = 0;

	/** 
	* ����  ��Ұ����
	* @param [in] 	 EmZoom  ��Ϊ:Զ����
	* @return  
	* @remarks 
	*/	
	virtual u16 SetCamZoomCmd( const EmTPZOOM& emZoom, u8 byIndex ) = 0;
    //moon904k30
    virtual u16 SetCamZoomValCmd( const TCamZoomVal& tCamZoomVal) = 0;

	virtual u16 SetCamZoomStopCmd(u8 byIndex) = 0;

	/** 
	* ����  ����zoomֵ
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	virtual u16 SetCamZoomValueCmd( const u32& dwZoom, u8 byIndex ) = 0;

	/** 
	* ����  	��ȡzoom
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	virtual u32 GetCamZoom() = 0;

	virtual u32 GetExtCamZoom() = 0;

	/** 
	* ����  ������Զ��۽�
	* @param [in] 	 
	* @return  
	* @remarks 
	*/		
	virtual u16 SetCamAutoFocusCmd(const EmTPMOOMMode& emFocusMode) = 0;

	/** 
	* ����  �ֶ��۽�����D
	* @param [in] 	 
	* @return  
	* @remarks 
	*/
    virtual u16 SetCamFocusNearCmd() = 0;

	/** 
	* ����  �ֶ��۽�����/��Զup
	* @param [in] 	 
	* @return  
	* @remarks 
	*/
    virtual u16 SetCamFocusStopCmd() = 0;

	/** 
	* ����  �ֶ��۽���ԶD
	* @param [in] 	 
	* @return  
	* @remarks 
	*/
    virtual u16 SetCamFocusFarCmd() = 0;

    /** 
	* ����: ��Ȧ��������
	* @param [in] 	TIrisAutoManuMode  
	* @return  
	* @remarks 
	*/
	virtual u16 SetCamApertreCmd( const TIrisAutoManuMode& tIrisAutoManuMode ) = 0;

	/** 
	* ����: �Ƿ����Զ��ع�
	* @param [in] 	EmTPMOOMMode  
	* @return  
	* @remarks 
	*/
	virtual u16 CamAutoExposureCmd( const EmTPMOOMMode& emExpAuto ) = 0;

	/** 
	* ����  	��ȡ�ع�ģʽ
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	virtual EmTPMOOMMode GetCamMoonMode() = 0;

	/** 
	* ����: ��Ȧ�л���Ϣ����
	* @param [in] 	EmTPMOOMMode  
	* @return  
	* @remarks 
	*/
	virtual u16 CamApertureCmd( const EmTPAperture &emTPAperture ) = 0;

	virtual EmTPAperture GetCamAperture() = 0;

	/** 
	* ����: �����л���Ϣ����
	* @param [in] 	EmTPMOOMMode  
	* @return  
	* @remarks 
	*/
	virtual u16 CamShutSpdCmd( const EmTPSOrThShutter& emShutSpd ) = 0;

	virtual u16 CamTwShutSpdCmd( const EmTPFOrTwShutter& emTwShutter ) = 0;

	virtual EmTPSOrThShutter GetCamShutSpd() = 0;

	virtual EmTPFOrTwShutter GetTwCamShutSpd() = 0;
	
	/** 
	* ����: �����л���Ϣ����
	* @param [in] 	EmTPMOOMMode  
	* @return  
	* @remarks 
	*/
	virtual u16 CamGainCmd( const EmTPExpGain& emGain ) = 0;

	virtual EmTPExpGain GetCamGain() = 0;

	/** 
	* ����: �Ƿ��Զ���ƽ��
	* @param [in] 	EmTPMOOMMode  
	* @return  
	* @remarks 
	*/
	virtual u16 CamAutoWBCmd( const EmTPMOOMMode& emWBAuto ) = 0;

	/** 
	* ����: ��ɫ�����������
	* @param [in] 	EmTPMOOMMode  
	* @return  
	* @remarks 
	*/
	virtual u16 CamRGainCmd( const u32& dwRGain ) = 0;

	/** 
	* ����: ��ɫ�����������
	* @param [in] 	EmTPMOOMMode  
	* @return  
	* @remarks 
	*/
	virtual u16 CamBGainCmd( const u32& dwBGain ) = 0;

	virtual u16 CamAdjustRangeCmd( const u32& dwAdjustRange ) = 0;

	virtual u16 CamHoriStretchCmd( const u32& dwHoriStretch ) = 0;

	/** 
	* ���� ��ȡ��ɫ����ֵ
	* @param [in] 	 
	* @return  
	* @remarks 
	*/
	virtual u32 GetCamRGain() = 0;

	/** 
	* ���� ��ȡ��ɫ����ֵ
	* @param [in] 	 
	* @return  
	* @remarks 
	*/
	virtual u32 GetCamBGain() = 0;

	virtual u32 GetCamAdjustRange() = 0;

	virtual u32 GetCamHoriStretch() = 0;

	/** 
	* ���� ͼƬ��������
	* @param [in] 	 
	* @return  
	* @remarks 
	*/
	virtual u16 CamImageParaCmd( EmTPImagePara emImagePara, const u32& dwImagePara ) = 0;

	/** 
	* ���� ��ȡ��ǰ���������
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	virtual TTPMoonCamInfo GetCamCfg() = 0;
	
	/** 
	* ���� ��ȡ��ѡ�е������
	* @param [in] 	 
	* @return  
	* @remarks 
	*/		
	virtual u8 GetCamSel()const = 0;

	/** 
	* ���� ��ȡ��ƽ��ģʽ
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	virtual EmTPMOOMMode GetCamWBMode() = 0;

	/** 
	* ���� �Ƿ������ⲹ��
	* @param [in] 	 
	* @return  
	* @remarks 
	*/
	virtual	u16 CamLightPensation( BOOL bIsOpen ) = 0;

	virtual	u16 CamKeystoneAdjust(const TTPDistortParam& tTPDistortParam,EmTPCorrect emMyOpetion ) = 0;

	virtual u16 SetColorRGBDirectCmd(u8 nPosition, EmTPColorConsistency emMyCorConsOption, const u32& dwRGBDirectValue) = 0;

	virtual	u16 CamOrderPosCheckCmd( BOOL bCheck ) = 0;

	/** 
	* ���� ��������
	* @param [in] 	 
	* @return  
	* @remarks 
	*/
	virtual	u16 CamNRCmd( BOOL bIsOpen, EmTPFpgaReduNoise emTPReduNoise ) = 0;

	/** 
	* ���� 2D��������
	* @param [in] 	 
	* @return  
	* @remarks 
	*/
	virtual	u16 Cam2DNRCmd( BOOL bIsOpen, EmTPReduNoise emTPReduNoise ) = 0;

	/** 
	* ���� 3D��������
	* @param [in] 	 
	* @return  
	* @remarks 
	*/
	virtual	u16 Cam3DNRCmd( BOOL bIsOpen, EmTPReduNoise emTPReduNoise ) = 0;

    virtual TTPCamPre* GetCamPreInfo() = 0; 

	/** ����   ����Ԥ��λ
	 *  @param[in] cfg ����Ԥ��λ
	 *  @return �ɹ�����0,ʧ�ܷ��ط�0������
	 *  @remarks 
	 */
	virtual u16 CamPreSetSaveCmd( const TTPCamPre& tTPCamPre ) = 0;

	virtual u16 CamPreSetModifyCmd( const TTPCamPre& tTPCamPre ) = 0;

	virtual u16 OrderPosDeleteReq( const TTPCamPre& tTPCamPre ) = 0;

	virtual u16 OrderPosInvokeCmd( const TTPCamPre& tTPCamPre ) = 0;

	virtual u16 CamParamUploadCmd() = 0;

	virtual u16 CamParamUploadNty( BOOL bSuccess ) = 0;

	virtual u16 UpgradeMoon( const s8* chVerFileInfo ) = 0;

	virtual u16 UpdateMoonMechanism( const s8* chVerFileInfo ) = 0;

	//����Moon
	virtual u16 RebootMoon() = 0;

	virtual u16 MoonCamResetCmd(u8 byIndex) = 0;
	/** ����   ���òο���
	 *  @param[in] bOpen �Ƿ��
	 *  @return �ɹ�����0,ʧ�ܷ��ط�0������
	 *  @remarks 
	 */
	virtual u16 SetReferenceLineCmd( BOOL bOpen ) = 0;
	/** ����   ����ˮƽ��ת
	 *  @param[in] bOpen �Ƿ��
	 *  @return �ɹ�����0,ʧ�ܷ��ط�0������
	 *  @remarks 
	 */
	virtual u16 SetHorizontalFlipCmd( BOOL bOpen ) =0;

	virtual u16 SetTrapezoidalCorCmd( BOOL bOpen ) =0;

	virtual u16 SetShowRectRegionCmd( BOOL bOpen ) = 0;

	virtual u16 SetRgbConsistSwitchCmd(BOOL bOpen) = 0;
	/** ����   ���ӡ��������β���
	 *  @param[in] emMyCorOption ���ĸ��������в���  emChangeOption ���ӻ����
	 *  @return �ɹ�����0,ʧ�ܷ��ط�0������
	 *  @remarks 
	 */
	virtual	u16 SetTraCorParamCmd( EmTPCorrect emMyCorOption,EmTPCorrectChange emChangeOption ) = 0;
	
	//������ɫһ����RGB
	virtual	u16 SetCorConsistRGBCmd( u8 nPosition, EmTPColorConsistency emMyCorConsOption,EmTPCorrectChange emChangeOption ) = 0;

	virtual u16 SetChangeDistortCmd( u8 byIndex, EmTPCorrectChange emTPCorrectChange, EmTPDistortPosition emTPDistortPosition ) = 0;

	virtual u16 SetDirectDistortCmd( const TTPDistortInfo&tTpDistortInfo ) = 0;

	virtual	u16 SetAutoSetColorConstancyCmd() = 0;

	virtual u16 SetChooseRectangleCmd(const TTPMoonRectRegion& tTPMoonRectRegion) = 0;

	virtual u16 SnapShotCmd( ) =0;

	//������ʱ����
    virtual u16 SetDelayCorrectCmd(u8 nPosition, u32 dwDelay) = 0;
};

#endif