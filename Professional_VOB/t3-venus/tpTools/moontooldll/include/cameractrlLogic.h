/*****************************************************************************
ģ����      : CCameraCtrlLogic
�ļ���      : cameractrlLogic.h
����ļ�    : 
�ļ�ʵ�ֹ���: ���������ҳ��
����        : ���`�`
�汾        : V1.0  Copyright(C) 2013-2014 KDV, All rights reserved.
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��         �汾        �޸���      �޸�����
2014/12/3      1.0         ���`�`			����
******************************************************************************/
#if !defined(AFX_CAMERACTRLLOGIC_H__AE177678_C26D_4119_9634_55EB6A4DB4C3__INCLUDED_)
#define AFX_CAMERACTRLLOGIC_H__AE177678_C26D_4119_9634_55EB6A4DB4C3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "logicBase.h"

class CCameraCtrlLogic : public CLogicBase, public ISingleTon<CCameraCtrlLogic>
{
public:
	CCameraCtrlLogic();
	virtual ~CCameraCtrlLogic();


public:  
	/**	 
	* ����:  ע���logic�����еĻص�����
	* @return  void
	* @remarks	�ڴ�ע��Ļص�������Ҫ�ǿؼ�����Ӧ�¼�����Ϊ��Ա�ص�����,Ҳ��ע�������Ļص�����
	                    ע��ʱ��Ӧע��ص�������Ӧ���ӵ��������򣺡�����::��������
	*/
	virtual void RegCBFun();

	/**	 
	* ����:  ע��Ҫ�������Ϣ
	* @return  void
	* @remarks	 ע������Ϣ���ܷ��͵����߼�ģ�飬���򣬽��ղ�������Ϣ
	*/
	virtual void RegMsg(); 

	/**	 
	* ����:  ע��ĳ�ص�����
	* @return  void
	* @remarks	 
	*/
	virtual void UnRegFunc( );

	/**	 
	* ����:  ע��ĳ�ص�����
	* @return  void
	* @remarks	 
	*/
	virtual void UnRegMsg();

	/**	 
	* ����:  ��ʼ����������,
	* @return  void
	* @remarks	���ڸù��ܱ��������ؼ����Բ���xml����ؼ��󶨣�
	                    ��Ҫ��RegCBFun������ע�ᵽ�ص���������ģ�� 
	*/
    virtual bool InitWnd( const IArgs & arg );

   /**	 
	* ����:  �������״̬������
	* @return   
	* @remarks	 
	*/
    virtual void Clear();

	/**	 
	* ����:  �ָ�����ؼ�״̬    by xhx
	* @return   
	* @remarks	 
	*/
    void ResetNormal();

	String GetCamMechnismStyle();

protected:
	/**	 
	* ����:  ����ComboboxCameraĳ�����Ӧ����
	* @return   bool
	* @remarks	 
	*/
	bool OnComboboxCameraClick( const IArgs& args );
	
	/**	 
	* ����:  ����ComboboxCameraStyleĳ�����Ӧ����
	* @return   bool
	* @remarks	 
	*/
	bool OnComboboxCameraStyleClick( const IArgs& args );


	/**	 
	* ����:  ����BtnSync����Ӧ����
	* @return   bool
	* @remarks	 
	*/
	bool OnBtnSyncClick( const IArgs& args );
	/**	 
	* ����:  ����BtnZoomPlus����Ӧ����
	* @return   bool
	* @remarks	 
	*/
	bool OnBtnZoomPlusClick( const IArgs& args );	

	/**	 
	* ����:  ����BtnZoomSub����Ӧ����
	* @return   bool
	* @remarks	 
	*/
	bool OnBtnZoomSubClick( const IArgs& args );

	/**	 
	* ����: BtnZoomPlusHold����Ӧ����
	* @return   bool
	* @remarks	 
	*/
	bool OnLBtnDownZoomPlus( const IArgs& args );

	bool OnLBtnDoubleDownZoomPlus( const IArgs& args );

	/**	 
	* ����: BtnZoomPlusHoldEnd����Ӧ����
	* @return   bool
	* @remarks	 
	*/
	bool OnLBtnUpZoomPlus( const IArgs& args );

	/**	 
	* ����: BtnZoomSubHold����Ӧ����
	* @return   bool
	* @remarks	 
	*/
	bool OnLBtnDownZoomSub( const IArgs& args );

	bool OnLBtnDoubleDownZoomSub( const IArgs& args );

	/**	 
	* ����: BtnZoomSubHoldEnd����Ӧ����
	* @return   bool
	* @remarks	 
	*/
	bool OnLBtnUpZoomSub( const IArgs& args );
	
	/**	 
	* ����:  ����BtnManuelFocus����Ӧ����
	* @return   bool
	* @remarks	 
	*/
	bool OnBtnManuelFocusClick( const IArgs& args );

	/**	 
	* ����:  ����BtnAutoFocus����Ӧ����
	* @return   bool
	* @remarks	 
	*/
	bool OnBtnAutoFocusClick( const IArgs& args );

	/**	 
	* ����:  BtnFocusNear��LBtnDown����Ӧ����
	* @return   bool
	* @remarks	 
	*/
	bool OnLBtnDownFocusNear( const IArgs& args );

	/**	 
	* ����:  BtnFocusNear��LBtnUp����Ӧ����
	* @return   bool
	* @remarks	 
	*/
	bool OnLBtnUpFocusNear( const IArgs& args );

	/**	 
	* ����:  BtnFocusFar��LBtnDown����Ӧ����
	* @return   bool
	* @remarks	 
	*/
	bool OnLBtnDownFocusFar( const IArgs& args );

	/**	 
	* ����:  BtnFocusFar��LBtnUp����Ӧ����
	* @return   bool
	* @remarks	 
	*/
	bool OnLBtnUpFocusFar( const IArgs& args );

	/**	 
	* ����:  ����BtnSwitchAutoExposure����Ӧ����
	* @return   bool
	* @remarks	 
	*/
	bool OnBtnSwitchAutoExposure( const IArgs& args );

	/**	 
	* ����:  ��Ȧ������
	* @return   bool
	* @remarks	 
	*/
	bool OnComboboxApertureClick( const IArgs& args );

	/**	 
	* ����:  ����BtnSwitchAutoWB����Ӧ����
	* @return   bool
	* @remarks	 
	*/
	bool OnBtnSwitchAutoWB( const IArgs& args );

	/**	 
	* ����:  SliderRGainֵ�ı����Ӧ����
	* @return   bool
	* @remarks	 
	*/
	bool OnSliderRGainChanged( const IArgs& args );

	/**	 
	* ����:  SliderBGainֵ�ı����Ӧ����
	* @return   bool
	* @remarks	 
	*/
	bool OnSliderBGainChanged( const IArgs& args );

	/**	 
	* ����:  SliderContrastֵ�ı����Ӧ����
	* @return   bool
	* @remarks	 
	*/
	bool OnSliderContrastChanged( const IArgs& args );

	/**	 
	* ����:  SliderContrastֵ�ı����Ӧ����
	* @return   bool
	* @remarks	 
	*/
	bool OnSliderSaturatChanged( const IArgs& args );

	/**	 
	* ����:  SliderSharpֵ�ı����Ӧ����
	* @return   bool
	* @remarks	 
	*/
	bool OnSliderSharpChanged( const IArgs& args );

	/**	 
	* ����:  SliderBrightֵ�ı����Ӧ����
	* @return   bool
	* @remarks	 
	*/
	bool OnSliderBrightChanged( const IArgs& args );

	/**	 
	* ����: ����ComboboxExposureGainĳһ�����Ӧ����
	* @return   bool
	* @remarks	 
	*/
	bool OnComboboxExposureGainClick( const IArgs& args );

	/**	 
	* ����: ����ComboboxShutĳһ�����Ӧ����
	* @return   bool
	* @remarks	 
	*/
	bool OnComboboxShutClick( const IArgs& args );

	/**	 
	* ����: EdtRGain�ı����Ӧ����
	* @return   bool
	* @remarks	 
	*/
	bool OnEdtRGainChange( const IArgs& args );

	/**	 
	* ����: EdtRGainʧȥ�������Ӧ����
	* @return   bool
	* @remarks	 
	*/
	bool OnKillFocusEdtRGain( const IArgs& args );

	/**	 
	* ����: EdtBGain�ı����Ӧ����
	* @return   bool
	* @remarks	 
	*/
	bool OnEdtBGainChange( const IArgs& args );

	/**	 
	* ����: EdtBGainʧȥ�������Ӧ����
	* @return   bool
	* @remarks	 
	*/
	bool OnKillFocusEdtBGain( const IArgs& args );

	/**	 
	* ����: EdtContrast�ı����Ӧ����
	* @return   bool
	* @remarks	 
	*/
	bool OnEdtContrastChange( const IArgs& args );

	/**	 
	* ����: EdtContrastʧȥ�������Ӧ����
	* @return   bool
	* @remarks	 
	*/
	bool OnKillFocusEdtContrast( const IArgs& args );

	/**	 
	* ����: EdtSaturat�ı����Ӧ����
	* @return   bool
	* @remarks	 
	*/
	bool OnEdtSaturatChange( const IArgs& args );

	/**	 
	* ����: EdtSaturatʧȥ�������Ӧ����
	* @return   bool
	* @remarks	 
	*/
	bool OnKillFocusEdtSaturat( const IArgs& args );

	/**	 
	* ����: EdtColor��ȸı����Ӧ����
	* @return   bool
	* @remarks	 
	*/
	bool OnEdtSharpChange( const IArgs& args );

	/**	 
	* ����: EdtColor���ʧȥ�������Ӧ����
	* @return   bool
	* @remarks	 
	*/
	bool OnKillFocusEdtSharp( const IArgs& args );
	
	/**	 
	* ����: EdtBright�ı����Ӧ����
	* @return   bool
	* @remarks	 
	*/
	bool OnEdtBrightChange( const IArgs& args );

	/**	 
	* ����: EdtBrightʧȥ�������Ӧ����
	* @return   bool
	* @remarks	 
	*/
	bool OnKillFocusEdtBright( const IArgs& args );

	/**	 
	* ����: EdtZoom�ı����Ӧ����
	* @return   bool
	* @remarks	 
	*/
	bool OnEdtZoomChange( const IArgs& args );

	/**	 
	* ����: EdtZoomʧȥ�������Ӧ����
	* @return   bool
	* @remarks	 
	*/
	bool OnEdtZoomKillFocus( const IArgs& args );
	
	/**	 
	* ����: ���ⲹ���Ƿ�����ť
	* @return   bool
	* @remarks	 
	*/
	bool OnBtnSwitchLightPensationClick( const IArgs& args );

	/**	 
	* ����: �����Ƿ���
	* @return   bool
	* @remarks	 
	*/
	bool OnBtnSwitchNRClick( const IArgs& args );

	bool OnComboboxNRClick( const IArgs& args );

	bool OnBtnSwitch2DNRClick( const IArgs& args );
	
	bool OnCombobox2DNRClick( const IArgs& args );

	bool OnBtnSwitch3DNRClick( const IArgs& args );
	
	bool OnCombobox3DNRClick( const IArgs& args );

	/**	 
	* ����: �Ƿ񿪻�����Ԥ��λ1
	* @return   bool
	* @remarks	 
	*/
	bool OnBtnSwitchOrderPosClick( const IArgs& args );

	/**	 
	* ����: ���������Ӧ����
	* @return   bool
	* @remarks	 
	*/
	bool OnBtnUpdateVersion( const IArgs& args );

	/**	 
	* ����: ���Ԥ��λ�б�ť��Ӧ����
	* @return   bool
	* @remarks	 
	*/
	bool OnBtnOrderPosList( const IArgs& args );

	/**	 
	* ����: ����Ԥ��λ��ť��Ӧ����
	* @return   bool
	* @remarks	 
	*/
	bool OnBtnSaveOrderPos( const IArgs& args );

	bool OnBtnSwitchKeyStoneAdjust( const IArgs& args );

	bool OnBtnCheckBackLightClick( const IArgs& args );

	bool OnSliderAdjustRangeChanged( const IArgs& args );

	bool OnSliderHoriStretchChanged( const IArgs& args );

	bool OnEdtAdjustRangeChange( const IArgs& args );

	bool OnKillFocusEdtAdjustRange( const IArgs& args );

	bool OnEdtHoriStretchChange( const IArgs& args );

	bool OnKillFocusEdtHoriStretch( const IArgs& args );

	bool OnComboboxGammaClick( const IArgs& args );

protected:
	/**	 
	* ����:  ��Ӧ������������UI_CNSTOOL_CAMERA_CFG_NTY�ĺ���
	* @return   LRESULT
	* @remarks	 
	*/
	HRESULT OnCameraCfgNty( WPARAM wparam, LPARAM lparam );

	/**	 
	* ����:  ��Ӧ������������UI_TpMechanismSelect_NTY�ĺ���
	* @return   LRESULT
	* @remarks	 
	*/
	HRESULT OnTpMechanismSelectNty( WPARAM wparam, LPARAM lparam );

	/**	 
	* ����:  ��Ӧ������������UI_TpMechVer_NTY�ĺ���
	* @return   LRESULT
	* @remarks	 
	*/
	HRESULT OnTpMechVerNty( WPARAM wparam, LPARAM lparam );

	/**	 
	* ����:  ��Ӧ������������UI_MOONTOOL_CamStyleSel_IND�ĺ���
	* @return   LRESULT
	* @remarks	 
	*/
	HRESULT OnCameraStyleSelectInd( WPARAM wparam, LPARAM lparam );
	
	/**	 
	* ����:  ��Ӧ������������UI_CNSTOOL_CAMERA_SELECT_IND�ĺ���
	* @return   LRESULT
	* @remarks	 
	*/
	HRESULT OnCameraSelectInd( WPARAM wparam, LPARAM lparam );

	/**	 
	* ����:  ��Ӧ������������UI_MOONTOOL_CamParamSync_IND�ĺ���
	* @return   LRESULT
	* @remarks	 
	*/
	HRESULT OnCamParamSyncInd( WPARAM wparam, LPARAM lparam );
	
	/**	 
	* ����:  ��Ӧ������������UI_CNSTOOL_CAMERA_ZOOM_IND�ĺ���
	* @return   LRESULT
	* @remarks	 
	*/
	HRESULT OnCameraZoomInd( WPARAM wparam, LPARAM lparam );

	/**	 
	* ����:  ��Ӧ������������UI_CNSTOOL_CAMERA_AUTO_FOCUS_IND�ĺ���
	* @return   LRESULT
	* @remarks	 
	*/
	HRESULT OnCameraAutoFocusInd( WPARAM wparam, LPARAM lparam );
	
	/**	 
	* ����:  ��Ӧ������������UI_CNSTOOL_CAMERA_FOCUS_IND�ĺ���
	* @return   LRESULT
	* @remarks	 
	*/
	HRESULT OnCameraFocusInd( WPARAM wparam, LPARAM lparam );

	/**	 
	* ����:  ��Ӧ������������UI_CNSTOOL_CAMERA_PERSET_MOVE_IND�ĺ���
	* @return   LRESULT
	* @remarks	 
	*/
	HRESULT OnCameraPersetMoveInd( WPARAM wparam, LPARAM lparam );

	/**	 
	* ����: ��Ӧ������������UI_MOONTOOL_CAMERA_AUTO_EXPOSURE_IND�ĺ���
	* @return   LRESULT
	* @remarks	 
	*/
	HRESULT OnAutoExposureInd( WPARAM wparam, LPARAM lparam );
	
	/**	 
	* ����:  ��Ӧ������������UI_CNSTOOL_CAMERA_GAIN_IND�ĺ���
	* @return   LRESULT
	* @remarks	 
	*/
	HRESULT OnCameraGainInd( WPARAM wparam, LPARAM lparam );
	
	/**	 
	* ����:  ��Ӧ������������UI_CNSTOOL_CAMERA_SHUT_SPD_IND�ĺ���
	* @return   LRESULT
	* @remarks	 
	*/
	HRESULT OnCameraShutSpdInd( WPARAM wparam, LPARAM lparam );
	
	/**	 
	* ����:  ��Ӧ������������UI_CNSTOOL_CAMERA_BACK_LIGHT_IND�ĺ���
	* @return   LRESULT
	* @remarks	 
	*/
	HRESULT OnCamLightPensationInd( WPARAM wparam, LPARAM lparam );

	/**	 
	* ����:  ��Ӧ������������UI_CNSTOOL_CAMERA_APERTURE_IND�ĺ���
	* @return   LRESULT
	* @remarks	 
	*/
	HRESULT OnCameraApertureInd( WPARAM wparam, LPARAM lparam );

	/**	 
	* ����:  ��Ӧ������������UI_CNSTOOL_CAMERA_AUTO_WB_IND�ĺ���
	* @return   LRESULT
	* @remarks	 
	*/
	HRESULT OnCameraAutoWBInd( WPARAM wparam, LPARAM lparam );
	
	/**	 
	* ����:  ��Ӧ������������UI_CNSTOOL_CAMERA_RGAIN_IND�ĺ���
	* @return   LRESULT
	* @remarks	 
	*/
	HRESULT OnCameraRGainInd( WPARAM wparam, LPARAM lparam );
	
	/**	 
	* ����:  ��Ӧ������������UI_CNSTOOL_CAMERA_BGAIN_IND�ĺ���
	* @return   LRESULT
	* @remarks	 
	*/
	HRESULT OnCameraBGainInd( WPARAM wparam, LPARAM lparam );
	
	/**	 
	* ����:  ��Ӧ������������UI_CNSTOOL_CAMERA_CONTRAST_IND�ĺ���
	* @return   LRESULT
	* @remarks	 
	*/
	HRESULT OnCameraBrightInd( WPARAM wparam, LPARAM lparam );

	/**	 
	* ����:  ��Ӧ������������UI_CNSTOOL_IMAGEPARA_IND�ĺ���
	* @return   LRESULT
	* @remarks	 
	*/
	HRESULT OnCameraImageParaInd( WPARAM wparam, LPARAM lparam );

	/**	 
	* ����:  ��Ӧ������������UI_CNSTOOL_CAMERA_CONTRAST_IND�ĺ���
	* @return   LRESULT
	* @remarks	 
	*/
	HRESULT OnCameraContrastInd( WPARAM wparam, LPARAM lparam );

	/**	 
	* ����:  ��ȵ��ڽ������
	* @return   LRESULT
	* @remarks	 
	*/	
	HRESULT OnCameraSharpInd( WPARAM wparam, LPARAM lparam );

	/**	 
	* ����:  ���Ͷȵ��ڽ������
	* @return   LRESULT
	* @remarks	 
	*/	
	HRESULT OnCameraSaturatInd( WPARAM wparam, LPARAM lparam );

	/**	 
	* ����:  ���ⲹ�����ý������
	* @return   LRESULT
	* @remarks	 
	*/	
	HRESULT OnCameraBackLightInd( WPARAM wparam, LPARAM lparam );
	
	/**	 
	* ����:  ��Ӧ������������UI_CNSTOOL_CAMERA_NR_IND�ĺ���
	* @return   LRESULT
	* @remarks	 
	*/
	HRESULT OnCameraNRInd( WPARAM wparam, LPARAM lparam );

	/**	 
	* ����:  ��Ӧ������������UI_CNSTOOL_CAMERA_2DNR_IND�ĺ���
	* @return   LRESULT
	* @remarks	 
	*/
	HRESULT OnCamera2DNRInd( WPARAM wparam, LPARAM lparam );

	/**	 
	* ����:  ��Ӧ������������UI_CNSTOOL_CAMERA_3DNR_IND�ĺ���
	* @return   LRESULT
	* @remarks	 
	*/
	HRESULT OnCamera3DNRInd( WPARAM wparam, LPARAM lparam );

	HRESULT OnCamOrderPosSelInd( WPARAM wparam, LPARAM lparam );

	HRESULT OnCamOutputInfoNty( WPARAM wparam, LPARAM lparam );

	HRESULT OnCamOutputInfoInd( WPARAM wparam, LPARAM lparam );

	HRESULT OnCamParameterDefaultInd( WPARAM wparam, LPARAM lparam );

	/**	 
	* ����:  ��Ӧ������������UI_CNSTOOL_CAMERA_RESET_IND�ĺ���
	* @return   LRESULT
	* @remarks	 
	*/
	HRESULT OnCameraResetInd( WPARAM wparam, LPARAM lparam );
	
	/**	 
	* ����:  ��Ӧ������������UI_CNSTOOL_CAMERA_PERSET_SAVE_IND�ĺ���
	* @return   LRESULT
	* @remarks	 
	*/
	HRESULT OnCameraPersetSaveInd( WPARAM wparam, LPARAM lparam );

	/**	 
	* ����:  ��Ӧ������������UI_CNSTOOL_SET_CAMERA_ZOOM_IND�ĺ���
	* @return   LRESULT
	* @remarks	 
	*/
	HRESULT OnSetCameraZoomInd( WPARAM wparam, LPARAM lparam );

	HRESULT OnSetCamDistortParamInd( WPARAM wparam, LPARAM lparam );

	HRESULT OnSetCamAutoFocusInd( WPARAM wparam, LPARAM lparam );

	

private:
	void GetShutSpdValue( EmTPSOrThShutter &emShutSpd );
	void GetTwShutterValue( EmTPFOrTwShutter &emTwShutter );
	void GetApertureValue(EmTPAperture &emAper);
	void SetApertureValue(EmTPAperture emAper);
	void GetExpGainValue( EmTPExpGain &emGain );
	void SetExpGainValue( EmTPExpGain emExpGain );
	void SetShutSpdValue(  EmTPSOrThShutter emShutSpd );
	void SetTwShutterValue( EmTPFOrTwShutter emTwShutter );
	void SetAutoWB( EmTPMOOMMode emWBMode );
	void SetAutoExp( EmTPMOOMMode emExpMode );
	void SetCameraCfg( TTPMoonCamInfo tMoonCameraCfg );
	void SetAptValue( u8 byApt );
	void SetPresetValue( BOOL bUsed );
	void SetCamName( CString strCaption );
	void SetCamStyleName( CString strCaption );
	void SetGammaName( CString strCaption );
	void SetRGainValue( u32 dwRGain );
	void SetBGainValue( u32 dwBGain );
	void SetAdjustRangeValue( u32 dwAdjustRange );
	void SetHoriStretchValue( u32 dwHoriStretch );
	void SetContrastValue( u32 dwContrast );
	void SetSaturatValue( u32 dwSaturat );
	void SetSharpValue( u32 dwSharp );
	void SetBrightValue( u32 dwBright );
	void GetNRValue(EmTPFpgaReduNoise &emTPReduNoise);
	void Get2DNRValue(EmTPReduNoise &emTPReduNoise);
	void Get3DNRValue(EmTPReduNoise &emTPReduNoise);
 	void SetNRValue( EmTPFpgaReduNoise emReduNoise );
	void Set2DNRValue( EmTPReduNoise emReduNoise );
	void Set3DNRValue( EmTPReduNoise emReduNoise );
	void SetFocusState( EmTPMOOMMode emFocusMode );
	void SetLightPensationValue( BOOL bUsed );
	void SetKeyStoneAdjust( BOOL bUsed );
	void SetGammaValue(EmH650Gamma emGamma);
	void SetMechVersion( s8 *achSwVersion, s8 *achHwVersion );
 
	float StringToFloatThree( CString str );
	CString OnlyFloat( CString str );

	void SetZoomValue( float fZoom );
	void SetH650ZoomValue(u32 dwZoom, u32 dwZoomPos);
	void SetZoomCmd( CString str );
	void SetApertureCmd( CString str );
	void SetRGainCmd( CString str );
	void SetBGainCmd( CString str );
	void SetAdjustRangeCmd( CString str );
	void SetHoriStretchCmd( CString str );
	void SetPicSceAptCmd( CString str );
	void SetContrastCmd( CString str );
	void SetSaturatCmd( CString str );
	void SetHueCmd( CString str );
	void SetBrightCmd( CString str );
	void SetShutComboxData();
	void showCameraInfo(bool bHide);

private:
	//���߼���Ԫ��Ӧ�����пؼ���
	const String m_strStcLineImagePara;
	const String m_strStcImageParam;
	const String m_strStcLineBright;
	const String m_strStcBright;
	const String m_strStcLineSaturat;
	const String m_strStcSaturat;
	const String m_strStcLineContrast;
	const String m_strStcContrast;
	const String m_strStcLineSharp;
	const String m_strStcSharp;
	const String m_strStcLineGamma;
	const String m_strStcGamma;
	const String m_strStcVersion;
	const String m_strStcVersionNum;
	const String m_strBtnUpdateVersion;
	const String m_strComboboxCamera;
	const String m_strComboboxCameraStyle;
	const String m_strComboboxExposureGain;
	const String m_strComboboxGamma;
	const String m_strComboboxShut;
	const String m_strComboboxAperture;
	const String m_strSliderAperture;
	const String m_strEdtAperture;
	const String m_strSliderRGain;
	const String m_strEdtRGain;
	const String m_strSliderBGain;
	const String m_strEdtBGain;
	const String m_strSliderAdjustRange;
	const String m_strSliderHoriStretch;
	const String m_strEdtHoriStretch;
	const String m_strEdtAdjustRange;
	const String m_strSliderPicSceApt;
	const String m_strEdtPicSceApt;
	const String m_strSliderContrast;
	const String m_strEdtContrast;
	const String m_strSliderSaturat;
	const String m_strEdtSaturat;
	const String m_strSliderSharp;
	const String m_strEdtSharp;
	const String m_strSliderBright;
	const String m_strEdtBright;
	const String m_strEdtZoom;
	const String m_strStcZoom;
	const String m_strStcLine2DNR;
	const String m_strStc2DNR;
	const String m_strStcLine3DNR;
	const String m_strStc3DNR;
	const String m_strCombobox2DNR;
	const String m_strCombobox3DNR;
	const String m_strBtnCheckManuelFocus;
	const String m_strBtnCheckAutoFocus;
	
	const String m_strBtnSwitchAutoExposure;
	const String m_strBtnSwitchAutoWB;
	const String m_strBtnZoomPlus;
	const String m_strBtnZoomSub;
	const String m_strBtnSwitchPersetMove;
	const String m_strBtnSwitchNR;
	const String m_strBtnSwitch2DNR;
	const String m_strBtnSwitch3DNR;
	const String m_strBtnSwitchLightPensation;
	const String m_strBtnSwitchKeystoneAdjust;
	const String m_strBtnCheckBackLight;
	bool         m_bIsCameraPowerOn;   //������Ƿ������ϵ�   by xhx
	bool         m_bLoginByOther;      //tptools�Ƿ�����    by xhx
	bool         m_bSourceCfg;         //�ź�Դ֡����ͬʱ���Ų�����ͬ
	u32          m_dwContrast;		   //�������ú��ֵͨ����Ϣ֪ͨ����󱣴�	
	u32          m_dwSharp;
	u32          m_dwBright;
	u32          m_dwSaturat;
	EmTPMOOMMode m_emTPMOOMMode;
	BOOL		 m_bIsOrderPos;

	TTPMechVer m_tTpMechver1;
	TTPMechVer m_tTpMechver2;
	TTPMechVer m_tTpMechver3;

	u8 m_byCamIndex;
};

#define CAMERALOGICRPTR    CCameraCtrlLogic::GetSingletonPtr()               //CameraCtrllogicָ��

#endif // !defined(AFX_CAMERALOGIC_H__AE177678_C26D_4119_9634_55EB6A4DB4C3__INCLUDED_)
