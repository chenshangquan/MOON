// cncconfig.h: interface for the CCncConfig class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CNCCONFIG_H__40492EAF_0B43_4101_A0B9_FDD4C21B1D4A__INCLUDED_)
#define AFX_CNCCONFIG_H__40492EAF_0B43_4101_A0B9_FDD4C21B1D4A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "rkcSession.h"

class CCamConfig : public CCamConfigIF 
{
	friend class CRkcSession;
public:

	CCamConfig(CRkcSession &cSession);
	virtual ~CCamConfig();

	/** 
	* ����  ��Ұ����
	* @param [in] 	 EmZoom ��Ϊ:Զ/��
	* @return  
	* @remarks 
	*/	
	virtual u16 SetCamZoomCmd( const EmTPZOOM& emZoom, u8 byIndex);	
    virtual u16 SetCamZoomValCmd( const TCamZoomVal& tCamZoomVal);

	virtual u16 SetCamZoomStopCmd(u8 byIndex);

	virtual u16 SetCamZoomValueCmd( const u32& dwZoom, u8 byIndex );

	/** 
	* ����  	��ȡzoom
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	virtual u32 GetCamZoom();

	virtual u32 GetExtCamZoom();

	/** 
	* ����  	������Զ��۽�
	* @param [in] 	 
	* @return  
	* @remarks 
	*/		
	virtual u16 SetCamAutoFocusCmd(const EmTPMOOMMode& emFocusMode);

	/** 
	* ����  	ѡ�������
	* @param [in] 	 TCameraMemInfo  
	* @return  
	* @remarks 
	*/		
	virtual u16 CamSelCmd( const u8& byCameraIndx );

	/** 
	* ����  	ͬ�����������
	* @param [in] 	 TCameraMemInfo  
	* @return  
	* @remarks 
	*/		
	virtual u16 SetMoonCamCfgSyncCmd( const u8& byCameraIndx );

	/** 
	* ����  	ѡ���������о
	* @param [in] 	 TCameraMemInfo  
	* @return  
	* @remarks 
	*/		
	virtual u16 CamStyleSelCmd( const EmTPMechanism& emTPMechanism );

	/** 
	* ����  	ѡ��Gamma
	* @param [in] 	 TCameraMemInfo  
	* @return  
	* @remarks 
	*/		
	virtual u16 GammaStyleSelCmd( const EmH650Gamma& enH650Gamma );
	/** 
	* ����  	��ȡ��ǰ���������
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	virtual TTPMoonCamInfo GetCamCfg();

	/** 
	* ����  	��ȡ��ѡ�е������
	* @param [in] 	 
	* @return  
	* @remarks 
	*/		
	virtual u8 GetCamSel()const;

	/** 
	* ����  	���Dʱ���ײ㷢������Ϣ
	* @param [in] 	 
	* @return  
	* @remarks 
	*/
	virtual u16 SetCamFocusNearCmd();

	/** 
	* ���� ���Upʱ���ײ㷢ֹͣ����/��Զ��Ϣ
	* @param [in] 	 
	* @return  
	* @remarks 
	*/
	virtual u16 SetCamFocusStopCmd();

	/** 
	* ����  	���Dʱ���ײ㷢��Զ��Ϣ
	* @param [in] 	 
	* @return  
	* @remarks 
	*/
	virtual u16 SetCamFocusFarCmd();

    /** 
	* ����  	��Ȧ������Ϣ
	* @param [in] 	 
	* @return  
	* @remarks 
	*/
	virtual u16 SetCamApertreCmd( const TIrisAutoManuMode& tIrisAutoManuMode );

	/** 
	* ����  	�Ƿ����Զ��ع�
	* @param [in] 	 
	* @return  
	* @remarks 
	*/
	virtual u16 CamAutoExposureCmd( const EmTPMOOMMode& emExpAuto );

	/** 
	* ����  �����л�
	* @param [in] 	 
	* @return  
	* @remarks 
	*/
	virtual u16 CamShutSpdCmd( const EmTPSOrThShutter& emShutSpd );

	virtual u16 CamTwShutSpdCmd( const EmTPFOrTwShutter& emTwShutter );

	/** 
	* ����  �����ȡ���Ų����ӿ�
	* @param [in] 	 
	* @return  
	* @remarks 
	*/
	virtual EmTPSOrThShutter GetCamShutSpd();

	virtual EmTPFOrTwShutter GetTwCamShutSpd();

	/** 
	* ����  ��Ȧ�л�
	* @param [in] 	 
	* @return  
	* @remarks 
	*/
	virtual u16 CamApertureCmd( const EmTPAperture& emAperture );

	/** 
	* ����  �����л�
	* @param [in] 	 
	* @return  
	* @remarks 
	*/
	virtual u16 CamGainCmd( const EmTPExpGain& emExpGain );

	virtual EmTPExpGain GetCamGain();

	virtual EmTPAperture GetCamAperture();

	virtual EmTPMOOMMode GetCamMoonMode();

	virtual EmTPMOOMMode GetCamWBMode();

	/** 
	* ����  ��ƽ�����(��Ϊ�Զ����ֶ�)
	* @param [in] 		   
	* @return  
	* @remarks 
	*/		
	virtual	u16 CamAutoWBCmd( const EmTPMOOMMode& emWBMode );	
	/** 
	* ����  R+����
	* @param [in] 	u16  R Gain ��Χ 0--100	   
	* @return  
	* @remarks 
	*/		
	virtual	u16 CamRGainCmd( const u32& dwRGain );
	/** 
	* ����  	��ȡ�������ƽ�����ģʽR+����ֵ
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	virtual u32 GetCamRGain();
	/** 
	* ����  B+����
	* @param [in] 	u16  B Gain ��Χ 0--100	   
	* @return  
	* @remarks 
	*/		
	virtual	u16 CamBGainCmd( const u32& dwBGain );
	/** 
	* ����  	��ȡ�������ƽ�����ģʽB+����ֵ
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	virtual u32 GetCamBGain();

	virtual	u16 CamAdjustRangeCmd( const u32& dwAdjustRange );

	virtual	u16 CamHoriStretchCmd( const u32& dwHoriStretch );

	virtual u32 GetCamAdjustRange();

	virtual u32 GetCamHoriStretch();
	/** 
	* ����  	����ͼƬ����ֵ
	* @param [in] 	 
	* @return  
	* @remarks 
	*/
	virtual u16 CamImageParaCmd( EmTPImagePara emImagePara, const u32& dwImagePara );
	/** 
	* ����  	��ȡͼƬ����ֵ
	* @param [in] 	 
	* @return  
	* @remarks 
	*/
//	virtual u16 GetCamImagePara();
	/** 
	* ����  	�Ƿ������ⲹ��
	* @param [in] 	 
	* @return  
	* @remarks 
	*/
	virtual u16 CamLightPensation( BOOL bIsOpen);

	virtual u16 CamKeystoneAdjust(const TTPDistortParam& tTPDistortParam,EmTPCorrect emMyOpetion );

	virtual u16 SetColorRGBDirectCmd(u8 nPosition, EmTPColorConsistency emMyCorConsOption, const u32& dwRGBDirectValue);

	/** 
	* ����  	�����������
	* @param [in] 	 
	* @return  
	* @remarks 
	*/
	virtual u16 CamNRCmd( BOOL bIsOpen, EmTPFpgaReduNoise emTPReduNoise );

	/** 
	* ����  	2D�����������
	* @param [in] 	 
	* @return  
	* @remarks 
	*/
	virtual u16 Cam2DNRCmd( BOOL bIsOpen, EmTPReduNoise emTPReduNoise );

	/** 
	* ����  	3D�����������
	* @param [in] 	 
	* @return  
	* @remarks 
	*/
	virtual u16 Cam3DNRCmd( BOOL bIsOpen, EmTPReduNoise emTPReduNoise );

    virtual u16 CamOrderPosCheckCmd( BOOL bCheck );

	/** 
	* ����  ��ȡ���ӻ�����
	* @return TCentreTVCfg*  ���ӻ���������ָ��
	*/
    virtual TTPCamPre* GetCamPreInfo();

	virtual u16 CamPreSetSaveCmd( const TTPCamPre& tTPCamPre );

	virtual u16 CamPreSetModifyCmd( const TTPCamPre& tTPCamPre );

	virtual u16 OrderPosDeleteReq( const TTPCamPre& tTPCamPre );

	virtual u16 OrderPosInvokeCmd( const TTPCamPre& tTPCamPre );

	virtual u16 CamParamUploadCmd();

	virtual u16 CamParamUploadNty( BOOL bSuccess );

	virtual u16 UpgradeMoon( const s8* chVerFileInfo );

	virtual u16 UpdateMoonMechanism( const s8* chVerFileInfo );

	//����moon
	virtual u16 RebootMoon();

	virtual u16 MoonCamResetCmd(u8 byIndex);
	//���òο���
	virtual	u16 SetReferenceLineCmd( BOOL bOpen );
	//����ˮƽ��ת
	virtual u16 SetHorizontalFlipCmd( BOOL bOpen );

	virtual u16 SetTrapezoidalCorCmd( BOOL bOpen );

	virtual u16 SetShowRectRegionCmd( BOOL bOpen );

	virtual u16 SetRgbConsistSwitchCmd(BOOL bOpen);
	//���ӻ�������ν����Ĳ���
	virtual	u16 SetTraCorParamCmd( EmTPCorrect emMyCorOption,EmTPCorrectChange emChangeOption );
	//������ɫһ����RGB
	virtual	u16 SetCorConsistRGBCmd( u8 nPosition, EmTPColorConsistency emMyCorConsOption,EmTPCorrectChange emChangeOption );

	virtual u16 SetChangeDistortCmd( u8 byIndex, EmTPCorrectChange emTPCorrectChange, EmTPDistortPosition emTPDistortPosition );

	virtual u16 SetDirectDistortCmd( const TTPDistortInfo&tTpDistortInfo );

	virtual	u16 SetAutoSetColorConstancyCmd();

	virtual u16 SetChooseRectangleCmd(const TTPMoonRectRegion& tTPMoonRectRegion);

	virtual u16 SnapShotCmd( );

	//������ʱ����
    virtual u16 SetDelayCorrectCmd(u8 nPosition, u32 dwDelay);

protected:
    virtual void OnTimeOut(u16 wEvent); 
    virtual void DispEvent(const CMessage &cMsg);
	void BuildEventsMap();

	//��Ϣ����
	void OnLinkBreak(const CMessage& cMsg);

	void OnMoonCamCfgNty(const CMessage& cMsg);

	void OnCamZoomInd(const CMessage& cMsg);

	void OnCamZoomStopInd(const CMessage& cMsg);

	void OnCamZoomValueInd(const CMessage& cMsg);

	void OnCamSelInd(const CMessage& cMsg);

	void OnCamParaSynchronizeInd(const CMessage& cMsg);

	void OnCamStyleSelInd(const CMessage& cMsg); //��о

	void OnGammaSelInd(const CMessage& cMsg);  //Gamma

	void OnMechanismSelectNty( const CMessage& cMsg);

	void OnTpMechverNty( const CMessage& cMsg);//�汾��

	void OnCamSelNty(const CMessage& cMsg);

	void OnCamAutoFocusInd(const CMessage& cMsg);

	void OnCamFocusNearInd(const CMessage& cMsg);

	void OnCamFocusStopInd(const CMessage& cMsg);

	void OnCamFocusFarInd(const CMessage& cMsg);

	void OnAutoExposureInd(const CMessage& cMsg);
	
	void OnCamShutSpdCInd(const CMessage& cMsg);

	void OnCamTwShutSpdCInd(const CMessage& cMsg);

	void OnCamApertureInd(const CMessage& cMsg);

	void OnCamGainInd(const CMessage& cMsg);

	void OnCamAutoWBInd(const CMessage& cMsg);

	void OnCamRGainInd(const CMessage& cMsg);

	void OnCamBGainInd(const CMessage& cMsg);

	void OnCamImageParaInd(const CMessage& cMsg);

	void OnCamLightPensationInd(const CMessage& cMsg);

	void OnCamNRInd(const CMessage& cMsg);

	void OnCam2DNRInd(const CMessage& cMsg);

	void OnCam3DNRInd(const CMessage& cMsg);

	void OnCamOrderPosSelInd(const CMessage& cMsg);

	void OnCamPreSetNty(const CMessage& cMsg);

	void OnCamPreSetInd(const CMessage& cMsg);

	void OnCamPreResetInd(const CMessage& cMsg);

	void OnCamPreRecallInd(const CMessage& cMsg);

	void OnCamPreSetModifyInd(const CMessage& cMsg);

	void OnCamParamDefaultInd(const CMessage& cMsg);

	void OnSetColorRGBInd(const CMessage& cMsg);

	void OnChooseRectangleInd(const CMessage& cMsg);

	void OnSetAutoColorConstancyInd(const CMessage& cMsg);

	void OnChangeSideRGBNty(const CMessage& cMsg);

	void OnSetColorRGBDirectInd(const CMessage& cMsg);

	void OnCamDistortAdjustInd(const CMessage& cMsg);

	void OnMoonUpgradeInd(const CMessage& cMsg);

	void OnUpdateMechanismInd(const CMessage& cMsg);
	//���òο���֪ͨ
	void OnReferenceLineInd( const CMessage& cMsg );

	void OnReferenceLineNty( const CMessage& cMsg );
	//����ˮƽ��ת֪ͨ
	void OnHorizontalFlipInd( const CMessage& cMsg );

	void OnHorizontalFlipNty( const CMessage& cMsg );

	void OnTrapezoidalCorInd( const CMessage& cMsg );

	void OnShowRectRegionInd( const CMessage& cMsg );

	void OnColorSwitchInd( const CMessage& cMsg );

	void OnTraCorParamInd( const CMessage& cMsg );

	void SnapShotInd( const CMessage& cMsg );

	void OnChangeDistortInd( const CMessage& cMsg );

	void OnDirectSetDistortInd( const CMessage& cMsg );

	void OnSecDefaultNty( const CMessage& cMsg );

	void OnSecBoundaryNty( const CMessage& cMsg );

	//��ʱ����
	void OnDelayCorrectInd( const CMessage& cMsg );
	void OnDelayCorrectNty( const CMessage& cMsg );

    //moon904k30
    void OnSetCamZoomValRsp( const CMessage& cMsg );
    void OnSetCamApertreRsp( const CMessage& cMsg );

public:
	void SetCameraCfgPtr();
	void SetCameraParamSync();

private:
	CRkcSession        *m_pSession;
	TTPMoonCamInfo  m_tCnCameraCfg1;
	TTPMoonCamInfo  m_tCnCameraCfg2;
	TTPMoonCamInfo  m_tCnCameraCfg3;
				
	u8	m_byCameraSel;
	u8  m_byCameraSyncSel;
	EmH650Gamma    m_emH650Gamma;
	TTPMoonCamInfo *m_pTPMoonCamCfg;

	TTPCamPre       m_atTPCamPre[MAX_CAMERA_Pre_NUM];   //��ʾ����Ϣ 
    EmTPMechanism  m_emTPMechanism;  //��о����
};

#endif // !defined(AFX_CNCCONFIG_H__40492EAF_0B43_4101_A0B9_FDD4C21B1D4A__INCLUDED_)
