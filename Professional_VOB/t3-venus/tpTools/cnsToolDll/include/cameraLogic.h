/*****************************************************************************
ģ����      : CCameraLogic
�ļ���      : cameraLogic.h
����ļ�    : 
�ļ�ʵ�ֹ���: �������ҳ��
����        : ʯ��
�汾        : V1.0  Copyright(C) 2013-2014 KDV, All rights reserved.
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��         �汾        �޸���      �޸�����
2013/2/29      1.0         ʯ��			����
******************************************************************************/
#if !defined(AFX_CAMERALOGIC_H__AE177678_C26D_4119_9634_55EB6A4DB4C3__INCLUDED_)
#define AFX_CAMERALOGIC_H__AE177678_C26D_4119_9634_55EB6A4DB4C3__INCLUDED_

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

protected:
	/**	 
	* ����:  ����ComboboxCameraĳ�����Ӧ����
	* @return   bool
	* @remarks	 
	*/
	bool OnComboboxCameraClick( const IArgs& args );
	
	/**	 
	* ����:  ����BtnImport����Ӧ����
	* @return   bool
	* @remarks	 
	*/
	bool OnBtnImportClick( const IArgs& args );

	/**	 
	* ����:  ����BtnExport����Ӧ����
	* @return   bool
	* @remarks	 
	*/
	bool OnBtnExportClick( const IArgs& args );

	/**	 
	* ����:  ����BtnResume����Ӧ����
	* @return   bool
	* @remarks	 
	*/
	bool OnBtnResumeClick( const IArgs& args );

	/**	 
	* ����:  ����BtnUpgradeCamera����Ӧ����
	* @return   bool
	* @remarks	 
	*/
	bool OnBtnUpgradeCameraClick( const IArgs& args );	

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
	bool OnBtnZoomPlusHold( const IArgs& args );

	/**	 
	* ����: BtnZoomPlusHoldEnd����Ӧ����
	* @return   bool
	* @remarks	 
	*/
	bool OnBtnZoomPlusHoldEnd( const IArgs& args );

	/**	 
	* ����: BtnZoomSubHold����Ӧ����
	* @return   bool
	* @remarks	 
	*/
	bool OnBtnZoomSubHold( const IArgs& args );

	/**	 
	* ����: BtnZoomSubHoldEnd����Ӧ����
	* @return   bool
	* @remarks	 
	*/
	bool OnBtnZoomSubHoldEnd( const IArgs& args );

	/**	 
	* ����:  ����BtnVisualFieldSwitch����Ӧ����
	* @return   bool
	* @remarks	 
	*/
	bool OnBtnSwitchVisualFieldClick( const IArgs& args );
	
	/**	 
	* ����:  ����BtnPresetSave����Ӧ����
	* @return   bool
	* @remarks	 
	*/
	bool OnBtnPresetSaveClick( const IArgs& args );

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
	* ����:  ����BtnSwitchPersetMove����Ӧ����
	* @return   bool
	* @remarks	 
	*/
	bool OnBtnSwitchPersetMove( const IArgs& args );
	

	/**	 
	* ����:  ����BtnSwitchAutoExposure����Ӧ����
	* @return   bool
	* @remarks	 
	*/
	bool OnBtnSwitchAutoExposure( const IArgs& args );

	/**	 
	* ����:  SliderApertureֵ�ı����Ӧ����
	* @return   bool
	* @remarks	 
	*/
	bool OnSliderApertureChanged( const IArgs& args );

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
	* ����:  BtnRadioLamp����Ӧ����
	* @return   bool
	* @remarks	 
	*/
	bool OnBtnRadioLamp( const IArgs& args );

	/**	 
	* ����:  BtnRadioSun����Ӧ����
	* @return   bool
	* @remarks	 
	*/
	bool OnBtnRadioSun( const IArgs& args );

	/**	 
	* ����:  BtnRadioManuel����Ӧ����
	* @return   bool
	* @remarks	 
	*/
	bool OnBtnRadioManuel( const IArgs& args );

	/**	 
	* ����:  ����BtnGammaOn����Ӧ����
	* @return   bool
	* @remarks	 
	*/
	bool OnBtnGammaOnClick( const IArgs& args );

	/**	 
	* ����:  ����BtnGammaOff����Ӧ����
	* @return   bool
	* @remarks	 
	*/
	bool OnBtnGammaOffClick( const IArgs& args );

	/**	 
	* ����:  ����BtnSmart1����Ӧ����
	* @return   bool
	* @remarks	 
	*/
	bool OnBtnSmart1Click( const IArgs& args );

	/**	 
	* ����:  ����BtnSmart2����Ӧ����
	* @return   bool
	* @remarks	 
	*/
	bool OnBtnSmart2Click( const IArgs& args );

	/**	 
	* ����:  SliderPicSceAptֵ�ı����Ӧ����
	* @return   bool
	* @remarks	 
	*/
	bool OnSliderPicSceAptChanged( const IArgs& args );

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
	* ����:  SliderHueֵ�ı����Ӧ����
	* @return   bool
	* @remarks	 
	*/
	bool OnSliderHueChanged( const IArgs& args );

	/**	 
	* ����:  SliderBrightֵ�ı����Ӧ����
	* @return   bool
	* @remarks	 
	*/
	bool OnSliderBrightChanged( const IArgs& args );

	/**	 
	* ����: ����BtnNROff����Ӧ����
	* @return   bool
	* @remarks	 
	*/
	bool OnBtnNROffClick( const IArgs& args );

	/**	 
	* ����: ����BtnNRLow����Ӧ����
	* @return   bool
	* @remarks	 
	*/
	bool OnBtnNRLowClick( const IArgs& args );

	/**	 
	* ����: ����BtnNRMid����Ӧ����
	* @return   bool
	* @remarks	 
	*/
	bool OnBtnNRMidClick( const IArgs& args );

	/**	 
	* ����: ����BtnNRHigh����Ӧ����
	* @return   bool
	* @remarks	 
	*/
	bool OnBtnNRHighClick( const IArgs& args );

	/**	 
	* ����: ����BtnSwitch3DNR����Ӧ����
	* @return   bool
	* @remarks	 
	*/
	bool OnBtnSwitch3DNRClick( const IArgs& args );

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
	* ����: ����ComboboxBackLightĳһ�����Ӧ����
	* @return   bool
	* @remarks	 
	*/
	bool OnComboboxBackLightClick( const IArgs& args );
	
	/**	 
	* ����: EdtAperture�ı����Ӧ����
	* @return   bool
	* @remarks	 
	*/
	bool OnEdtApertureChange( const IArgs& args );	

	/**	 
	* ����: EdtApertureʧȥ�������Ӧ����
	* @return   bool
	* @remarks	 
	*/
	bool OnKillFocusEdtAperture( const IArgs& args );	

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
	* ����: EdtPicSceApt�ı����Ӧ����
	* @return   bool
	* @remarks	 
	*/
	bool OnEdtPicSceAptChange( const IArgs& args );

	/**	 
	* ����: EdtPicSceAptʧȥ�������Ӧ����
	* @return   bool
	* @remarks	 
	*/
	bool OnKillFocusEdtPicSceApt( const IArgs& args );

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
	* ����: EdtHue�ı����Ӧ����
	* @return   bool
	* @remarks	 
	*/
	bool OnEdtHueChange( const IArgs& args );

	/**	 
	* ����: EdtHueʧȥ�������Ӧ����
	* @return   bool
	* @remarks	 
	*/
	bool OnKillFocusEdtHue( const IArgs& args );
	
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
	
	

protected:
	/**	 
	* ����:  ��Ӧ������������UI_CNSTOOL_CAMERA_CFG_NTY�ĺ���
	* @return   LRESULT
	* @remarks	 
	*/
	HRESULT OnCameraCfgNty( WPARAM wparam, LPARAM lparam );
	
	/**	 
	* ����:  ��Ӧ������������UI_CNSTOOL_CAMERA_SELECT_IND�ĺ���
	* @return   LRESULT
	* @remarks	 
	*/
	HRESULT OnCameraSelectInd( WPARAM wparam, LPARAM lparam );
	
	/**	 
	* ����:  ��Ӧ������������UI_CNSTOOL_CAMERA_ZOOM_IND�ĺ���
	* @return   LRESULT
	* @remarks	 
	*/
	HRESULT OnCameraZoomInd( WPARAM wparam, LPARAM lparam );

	/**	 
	* ����:  ��Ӧ������������UI_CNSTOOL_CAMERA_OSDSHOW_IND�ĺ���
	* @return   LRESULT
	* @remarks	 
	*/
	HRESULT OnCameraOSDShowInd( WPARAM wparam, LPARAM lparam );

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
	* ����:  ��Ӧ������������UI_CNSTOOL_CAMERA_AUTO_EXPOSURE_IND�ĺ���
	* @return   LRESULT
	* @remarks	 
	*/
	HRESULT OnCameraAutoExposureInd( WPARAM wparam, LPARAM lparam );
	
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
	HRESULT OnCameraBackLightInd( WPARAM wparam, LPARAM lparam );

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
	* ����:  ��Ӧ������������UI_CNSTOOL_CAMERA_PIC_SCENE_MODE_IND�ĺ���
	* @return   LRESULT
	* @remarks	 
	*/
	HRESULT OnCameraPicSceneModeInd( WPARAM wparam, LPARAM lparam );
	
	/**	 
	* ����:  ��Ӧ������������UI_CNSTOOL_CAMERA_GAMMA_IND�ĺ���
	* @return   LRESULT
	* @remarks	 
	*/
	HRESULT OnCameraGammaInd( WPARAM wparam, LPARAM lparam );
	
	/**	 
	* ����:  ��Ӧ������������UI_CNSTOOL_CAMERA_PIC_SCE_APT_IND�ĺ���
	* @return   LRESULT
	* @remarks	 
	*/
	HRESULT OnCameraPicSceAptInd( WPARAM wparam, LPARAM lparam );
	
	/**	 
	* ����:  ��Ӧ������������UI_CNSTOOL_CAMERA_CONTRAST_IND�ĺ���
	* @return   LRESULT
	* @remarks	 
	*/
	HRESULT OnCameraContrastInd( WPARAM wparam, LPARAM lparam );
	
	/**	 
	* ����:  ��Ӧ������������UI_CNSTOOL_CAMERA_SATURAT_IND�ĺ���
	* @return   LRESULT
	* @remarks	 
	*/
	HRESULT OnCameraSaturatInd( WPARAM wparam, LPARAM lparam );
	
	/**	 
	* ����:  ��Ӧ������������UI_CNSTOOL_CAMERA_HUE_IND�ĺ���
	* @return   LRESULT
	* @remarks	 
	*/
	HRESULT OnCameraHueInd( WPARAM wparam, LPARAM lparam );
	
	/**	 
	* ����:  ��Ӧ������������UI_CNSTOOL_CAMERA_BRIGHT_IND�ĺ���
	* @return   LRESULT
	* @remarks	 
	*/
	HRESULT OnCameraBrightInd( WPARAM wparam, LPARAM lparam );
	
	/**	 
	* ����:  ��Ӧ������������UI_CNSTOOL_CAMERA_NR_STM_CLEAN_IND�ĺ���
	* @return   LRESULT
	* @remarks	 
	*/
	HRESULT OnCameraNRStmCleanInd( WPARAM wparam, LPARAM lparam );
	
	/**	 
	* ����:  ��Ӧ������������UI_CNSTOOL_CAMERA_3DNR_IND�ĺ���
	* @return   LRESULT
	* @remarks	 
	*/
	HRESULT OnCamera3DNRInd( WPARAM wparam, LPARAM lparam );
	
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
	
	/**	 
	* ����:  ��Ӧ������������UI_CNSTOOL_CAMERA_POWER_ON_NTY�ĺ���    by xhx
	* @return   LRESULT
	* @remarks	 
	*/
	HRESULT OnCameraPowerOnNty( WPARAM wparam, LPARAM lparam );

private:
	void GetBackLightValue( EmBackLightType &emBackLightType, u8 &byMulti );
	void GetShutSpdValue( EmShutSpd &emShutSpd );
	void GetGainValue( EmGain &emGain );
	void SetExpGainValue( EmGain emGain );
	void SetShutSpdValue( EmShutSpd emShutSpd );
	void SetBackLightValue( EmBackLightType emBackLightType, u8 byMulti );
	void SetAutoWB( EmWBMode emWBMode );
	void SetAutoExp( EmExpMode emExpMode );
	void SetCameraCfg( TCnCameraCfg tCnCameraCfg );
	void SetAptValue( u8 byApt );
	void SetPresetValue( BOOL bUsed );
	void SetOSDShowValue( EmOSDShow emOSDShow );
	void SetCamName( CString strCaption );
	void SetRGainValue( u16 wRGain );
	void SetBGainValue( u16 wBGain );
	void SetPicSceModeValue( EmPicSceMode emPicSceMode );
	void SetGammaValue( EmGamma emGamma );
	void SetPicSceAptValue( u8 byPicSceApt );
	void SetContrastValue( u16 wContrast );
	void SetSaturatValue( u16 wSaturat );
	void SetHueValue( u16 wHue );
	void SetBrightValue( u16 wBright );
	void SetNRStmCleanValue( EmStmClean emStmClean );
	void Set3DNRValue( Em3DNR em3DNR );

	float StringToFloatTwo( CString str );
	CString OnlyFloat( CString str );

	void SetZoomValue( float fZoom );
	void SetZoomCmd( CString str );
	void SetApertureCmd( CString str );
	void SetRGainCmd( CString str );
	void SetBGainCmd( CString str );
	void SetPicSceAptCmd( CString str );
	void SetContrastCmd( CString str );
	void SetSaturatCmd( CString str );
	void SetHueCmd( CString str );
	void SetBrightCmd( CString str );

private:
	//���߼���Ԫ��Ӧ�����пؼ���
	const String m_strComboboxCamera;
	const String m_strBtnSwitchVisualField;
	const String m_strBtnSwitchPersetMove;
	const String m_strComboboxExposureGain;
	const String m_strComboboxShut;
	const String m_strComboboxBackLight;
	const String m_strSliderAperture;
	const String m_strEdtAperture;
	const String m_strSliderRGain;
	const String m_strEdtRGain;
	const String m_strSliderBGain;
	const String m_strEdtBGain;
	const String m_strSliderPicSceApt;
	const String m_strEdtPicSceApt;
	const String m_strSliderContrast;
	const String m_strEdtContrast;
	const String m_strSliderSaturat;
	const String m_strEdtSaturat;
	const String m_strSliderHue;
	const String m_strEdtHue;
	const String m_strSliderBright;
	const String m_strEdtBright;
	const String m_strEdtZoom;
	const String m_strBtnSwitch3DNR;
	const String m_strBtnSwitchAutoExposure;
	const String m_strBtnSwitchAutoWB;
	const String m_strBtnZoomPlus;
	const String m_strBtnZoomSub;
	bool         m_bIsCameraPowerOn;   //������Ƿ������ϵ�   by xhx
	bool         m_bLoginByOther;      //tptools�Ƿ�����    by xhx
};

#define CAMERALOGICRPTR    CCameraCtrlLogic::GetSingletonPtr()               //Cameralogicָ��

#endif // !defined(AFX_CAMERALOGIC_H__AE177678_C26D_4119_9634_55EB6A4DB4C3__INCLUDED_)
