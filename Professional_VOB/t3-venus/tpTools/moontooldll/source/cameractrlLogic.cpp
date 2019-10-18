// cameractrllogic.cpp: implementation of the CCameraCtrlLogic class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h" 
#include "cameractrlLogic.h"

#define MAX_PICSCEAPT_NUMBER 15
#define MIN_PICSCEAPT_NUMBER 1

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CCameraCtrlLogic::CCameraCtrlLogic()
: m_strComboboxCamera("ComboboxCamera")
, m_strComboboxCameraStyle("ComboboxCameraStyle")
, m_strComboboxOutputFormat("ComboboxOutputFormat")
, m_strBtnZoomPlus("BtnZoomPlus")
, m_strBtnZoomSub("BtnZoomSub")
, m_strEdtZoom("EdtZoom")
, m_strStcZoom("StcZoom")
, m_strBtnCheckManuelFocus("BtnCheckManuelFocus")
, m_strBtnCheckAutoFocus("BtnCheckAutoFocus")
, m_strBtnSwitchAutoExposure("BtnSwitchAutoExposure")
, m_strComboboxApertre("ComboboxApertre")  //MOON904K30
, m_strComboboxAperture("ComboboxAperture")
, m_strComboboxShut("ComboboxShut")
, m_strComboboxExposureGain("ComboboxExposureGain")
, m_strComboboxGamma("ComboboxGamma")
, m_strBtnSwitchAutoWB("BtnSwitchAutoWB")
, m_strSliderRGain("SliderRGain")
, m_strEdtRGain("EdtRGain")
, m_strSliderBGain("SliderBGain")
, m_strEdtBGain("EdtBGain")
, m_strStcLineImagePara("StcLineImagePara")
, m_strStcImageParam("StcImageParam")
, m_strSliderAdjustRange("SliderAdjustRange")
, m_strEdtAdjustRange("EdtAdjustRange")
, m_strSliderHoriStretch("SliderHoriStretch")
, m_strEdtHoriStretch("EdtHoriStretch")
, m_strSliderContrast("SliderContrast")
, m_strEdtContrast("EdtContrast")
, m_strSliderSaturat("SliderSaturat")
, m_strEdtSaturat("EdtSaturat")
, m_strSliderSharp("SliderSharp")
, m_strEdtSharp("EdtSharp")
, m_strSliderBright("SliderBright")
, m_strEdtBright("EdtBright")
, m_strBtnSwitchLightPensation("BtnSwitchLightPensation")
, m_strBtnSwitchPersetMove("BtnSwitchOrderPos")
, m_strBtnSwitchNR("BtnSwitchNR")
, m_strBtnSwitch2DNR("BtnSwitch2DNR")
, m_strBtnSwitch3DNR("BtnSwitch3DNR")
, m_strCombobox2DNR("Combobox2DNR")
, m_strCombobox3DNR("Combobox3DNR")
, m_strStcLine2DNR("StcLine2DNR")
, m_strStc2DNR("Stc2DNR")
, m_strStcLine3DNR("StcLine3DNR")
, m_strStc3DNR("Stc3DNR")
, m_strBtnSwitchKeystoneAdjust("BtnSwitchKA")
, m_strBtnCheckBackLight("BtnCheckBackLight")
, m_strStcLineBright("StcLineBright")
, m_strStcLineSaturat("StcLineSaturat")
, m_strStcLineContrast("StcLineContrast")
, m_strStcLineSharp("StcLineSharp")
, m_strStcBright("StcBright")
, m_strStcSaturat("StcSaturat")
, m_strStcContrast("StcContrast")
, m_strStcSharp("StcSharp")
, m_strStcGamma("StcGamma")
, m_strStcLineGamma("StcLineGamma")
, m_strStcVersion("StcVersion")
, m_strStcVersionNum("StcVersionNum")
, m_strBtnUpdateVersion("BtnUpdateVersion")
, m_bIsCameraPowerOn(false)
, m_bLoginByOther(false)
,m_bIsOrderPos(FALSE)
{
	m_dwSaturat = 0;
	m_dwBright = 0;
	m_dwSharp = 0;
    m_dwContrast = 0;
	m_bSourceCfg = 0;
	m_byCamIndex = 0;
}

CCameraCtrlLogic::~CCameraCtrlLogic()
{
	UnRegMsg();
	UnRegFunc();
}

void CCameraCtrlLogic::RegMsg()
{
	REG_MSG_HANDLER( UI_MOONTOOL_CAMINFO_NTY, CCameraCtrlLogic::OnCameraCfgNty, CAMERALOGICRPTR, CCameraCtrlLogic );
	REG_MSG_HANDLER( UI_TpMechanismSelect_NTY, CCameraCtrlLogic::OnTpMechanismSelectNty, CAMERALOGICRPTR, CCameraCtrlLogic );
	REG_MSG_HANDLER( UI_TpMechVer_NTY, CCameraCtrlLogic::OnTpMechVerNty, CAMERALOGICRPTR, CCameraCtrlLogic );
	REG_MSG_HANDLER( UI_MOONTOOL_CamSel_IND, CCameraCtrlLogic::OnCameraSelectInd, CAMERALOGICRPTR, CCameraCtrlLogic );
	REG_MSG_HANDLER( UI_MOONTOOL_CamParamSync_IND, CCameraCtrlLogic::OnCamParamSyncInd, CAMERALOGICRPTR, CCameraCtrlLogic );
	REG_MSG_HANDLER( UI_MOONTOOL_CamStyleSel_IND, CCameraCtrlLogic::OnCameraStyleSelectInd, CAMERALOGICRPTR, CCameraCtrlLogic );
	REG_MSG_HANDLER( UI_MOONTOOL_CAMERA_AUTO_EXPOSURE_IND, CCameraCtrlLogic::OnAutoExposureInd,  CAMERALOGICRPTR, CCameraCtrlLogic );
	REG_MSG_HANDLER( UI_MOONTOOL_CAMERA_APERTURE_IND, CCameraCtrlLogic::OnCameraApertureInd,  CAMERALOGICRPTR, CCameraCtrlLogic );
	REG_MSG_HANDLER( UI_MOONTOOL_CAMERA_SHUT_SPD_IND, CCameraCtrlLogic::OnCameraShutSpdInd,  CAMERALOGICRPTR, CCameraCtrlLogic );
	REG_MSG_HANDLER( UI_MOONTOOL_CAMERA_GAIN_IND, CCameraCtrlLogic::OnCameraGainInd,  CAMERALOGICRPTR, CCameraCtrlLogic );
	REG_MSG_HANDLER( UI_MOONTOOL_CAMERA_AUTO_WB_IND, CCameraCtrlLogic::OnCameraAutoWBInd,  CAMERALOGICRPTR, CCameraCtrlLogic );
	REG_MSG_HANDLER( UI_MOONTOOL_CAMERA_RGAIN_IND, CCameraCtrlLogic::OnCameraRGainInd,  CAMERALOGICRPTR, CCameraCtrlLogic );
	REG_MSG_HANDLER( UI_MOONTOOL_CAMERA_BGAIN_IND, CCameraCtrlLogic::OnCameraBGainInd,  CAMERALOGICRPTR, CCameraCtrlLogic );
	REG_MSG_HANDLER( UI_MOONTOOL_IMAGEPARA_IND, CCameraCtrlLogic::OnCameraImageParaInd,  CAMERALOGICRPTR, CCameraCtrlLogic );
	REG_MSG_HANDLER( UI_MOONTOOL_IMAGE_CONTRAST_IND, CCameraCtrlLogic::OnCameraContrastInd,  CAMERALOGICRPTR, CCameraCtrlLogic );
	REG_MSG_HANDLER( UI_MOONTOOL_IMAGE_Sharp_IND, CCameraCtrlLogic::OnCameraSharpInd,  CAMERALOGICRPTR, CCameraCtrlLogic );
	REG_MSG_HANDLER( UI_MOONTOOL_IMAGE_SATURAT_IND, CCameraCtrlLogic::OnCameraSaturatInd,  CAMERALOGICRPTR, CCameraCtrlLogic );
	REG_MSG_HANDLER( UI_MOONTOOL_IMAGE_BLIGHT_IND, CCameraCtrlLogic::OnCameraBrightInd,  CAMERALOGICRPTR, CCameraCtrlLogic );
	REG_MSG_HANDLER( UI_MOONTOOL_CAMERA_BACKLIGHT_IND, CCameraCtrlLogic::OnCamLightPensationInd,  CAMERALOGICRPTR, CCameraCtrlLogic );
	REG_MSG_HANDLER( UI_MOONTOOL_CAMERA_NR_IND, CCameraCtrlLogic::OnCameraNRInd,  CAMERALOGICRPTR, CCameraCtrlLogic );
	REG_MSG_HANDLER( UI_MOONTOOL_CAMERA_2DNR_IND, CCameraCtrlLogic::OnCamera2DNRInd,  CAMERALOGICRPTR, CCameraCtrlLogic );
	REG_MSG_HANDLER( UI_MOONTOOL_CAMERA_3DNR_IND, CCameraCtrlLogic::OnCamera3DNRInd,  CAMERALOGICRPTR, CCameraCtrlLogic );
	REG_MSG_HANDLER( UI_MOONTOOL_CAMERA_INITPRESET_IND, CCameraCtrlLogic::OnCamOrderPosSelInd,  CAMERALOGICRPTR, CCameraCtrlLogic );
	REG_MSG_HANDLER( UI_MOONTOOL_CAMOUTPUT_INFO_NTY, CCameraCtrlLogic::OnCamOutputInfoNty, CAMERALOGICRPTR, CCameraCtrlLogic );	
	REG_MSG_HANDLER( UI_MOONTOOL_CAMPARAMDEFAULT_IND, CCameraCtrlLogic::OnCamParameterDefaultInd, CAMERALOGICRPTR, CCameraCtrlLogic );
	REG_MSG_HANDLER( UI_MOONTOOL_CAMOUTPUT_INFO_IND, CCameraCtrlLogic::OnCamOutputInfoInd, CAMERALOGICRPTR, CCameraCtrlLogic );
	REG_MSG_HANDLER( UI_MOONTOOL_SET_CAMERA_ZOOM_IND, CCameraCtrlLogic::OnSetCameraZoomInd, CAMERALOGICRPTR, CCameraCtrlLogic );
//	REG_MSG_HANDLER( UI_MOONTOOL_CAMERA_DISTORTPARAM_IND, CCameraCtrlLogic::OnSetCamDistortParamInd, CAMERALOGICRPTR, CCameraCtrlLogic );
	REG_MSG_HANDLER( UI_MOONTOOL_CAMERA_AUTO_FOCUS_IND, CCameraCtrlLogic::OnSetCamAutoFocusInd, CAMERALOGICRPTR, CCameraCtrlLogic )
		
}

void CCameraCtrlLogic::UnRegMsg()
{
}

void CCameraCtrlLogic::RegCBFun()
{
	REG_GOBAL_MEMBER_FUNC( "CCameraCtrlLogic::InitWnd", CCameraCtrlLogic::InitWnd, CAMERALOGICRPTR, CCameraCtrlLogic );
	REG_GOBAL_MEMBER_FUNC( "CCameraCtrlLogic::OnComboboxCameraClick", CCameraCtrlLogic::OnComboboxCameraClick, CAMERALOGICRPTR, CCameraCtrlLogic );
	REG_GOBAL_MEMBER_FUNC( "CCameraCtrlLogic::OnComboboxCameraStyleClick", CCameraCtrlLogic::OnComboboxCameraStyleClick, CAMERALOGICRPTR, CCameraCtrlLogic );
	REG_GOBAL_MEMBER_FUNC( "CCameraCtrlLogic::OnBtnSyncClick", CCameraCtrlLogic::OnBtnSyncClick, CAMERALOGICRPTR, CCameraCtrlLogic );
    REG_GOBAL_MEMBER_FUNC( "CCameraCtrlLogic::OnComboboxOutputFormatClick", CCameraCtrlLogic::OnComboboxOutputFormatClick, CAMERALOGICRPTR, CCameraCtrlLogic );

	REG_GOBAL_MEMBER_FUNC( "CCameraCtrlLogic::OnBtnZoomPlusClick", CCameraCtrlLogic::OnBtnZoomPlusClick, CAMERALOGICRPTR, CCameraCtrlLogic );
	REG_GOBAL_MEMBER_FUNC( "CCameraCtrlLogic::OnBtnZoomSubClick", CCameraCtrlLogic::OnBtnZoomSubClick, CAMERALOGICRPTR, CCameraCtrlLogic );
	REG_GOBAL_MEMBER_FUNC( "CCameraCtrlLogic::OnLBtnDownZoomPlus", CCameraCtrlLogic::OnLBtnDownZoomPlus, CAMERALOGICRPTR, CCameraCtrlLogic );
	REG_GOBAL_MEMBER_FUNC( "CCameraCtrlLogic::OnLBtnDoubleDownZoomPlus", CCameraCtrlLogic::OnLBtnDoubleDownZoomPlus, CAMERALOGICRPTR, CCameraCtrlLogic );
	REG_GOBAL_MEMBER_FUNC( "CCameraCtrlLogic::OnLBtnUpZoomPlus", CCameraCtrlLogic::OnLBtnUpZoomPlus, CAMERALOGICRPTR, CCameraCtrlLogic );
	REG_GOBAL_MEMBER_FUNC( "CCameraCtrlLogic::OnLBtnDownZoomSub", CCameraCtrlLogic::OnLBtnDownZoomSub, CAMERALOGICRPTR, CCameraCtrlLogic );
	REG_GOBAL_MEMBER_FUNC( "CCameraCtrlLogic::OnLBtnDoubleDownZoomSub", CCameraCtrlLogic::OnLBtnDoubleDownZoomSub, CAMERALOGICRPTR, CCameraCtrlLogic );	
	REG_GOBAL_MEMBER_FUNC( "CCameraCtrlLogic::OnLBtnUpZoomSub", CCameraCtrlLogic::OnLBtnUpZoomSub, CAMERALOGICRPTR, CCameraCtrlLogic );
	REG_GOBAL_MEMBER_FUNC( "CCameraCtrlLogic::OnEdtZoomChange", CCameraCtrlLogic::OnEdtZoomChange, CAMERALOGICRPTR, CCameraCtrlLogic );
	REG_GOBAL_MEMBER_FUNC( "CCameraCtrlLogic::OnEdtZoomKillFocus", CCameraCtrlLogic::OnEdtZoomKillFocus, CAMERALOGICRPTR, CCameraCtrlLogic );
	REG_GOBAL_MEMBER_FUNC( "CCameraCtrlLogic::OnBtnManuelFocusClick", CCameraCtrlLogic::OnBtnManuelFocusClick, CAMERALOGICRPTR, CCameraCtrlLogic );
	REG_GOBAL_MEMBER_FUNC( "CCameraCtrlLogic::OnBtnAutoFocusClick", CCameraCtrlLogic::OnBtnAutoFocusClick, CAMERALOGICRPTR, CCameraCtrlLogic );
	REG_GOBAL_MEMBER_FUNC( "CCameraCtrlLogic::OnLBtnDownFocusNear", CCameraCtrlLogic::OnLBtnDownFocusNear, CAMERALOGICRPTR, CCameraCtrlLogic );
	REG_GOBAL_MEMBER_FUNC( "CCameraCtrlLogic::OnLBtnUpFocusNear", CCameraCtrlLogic::OnLBtnUpFocusNear, CAMERALOGICRPTR, CCameraCtrlLogic );
	REG_GOBAL_MEMBER_FUNC( "CCameraCtrlLogic::OnLBtnDownFocusFar", CCameraCtrlLogic::OnLBtnDownFocusFar, CAMERALOGICRPTR, CCameraCtrlLogic );
	REG_GOBAL_MEMBER_FUNC( "CCameraCtrlLogic::OnLBtnUpFocusFar", CCameraCtrlLogic::OnLBtnUpFocusFar, CAMERALOGICRPTR, CCameraCtrlLogic );
	REG_GOBAL_MEMBER_FUNC( "CCameraCtrlLogic::OnBtnSwitchAutoExposure", CCameraCtrlLogic::OnBtnSwitchAutoExposure, CAMERALOGICRPTR, CCameraCtrlLogic );
	REG_GOBAL_MEMBER_FUNC( "CCameraCtrlLogic::OnComboboxApertureClick", CCameraCtrlLogic::OnComboboxApertureClick, CAMERALOGICRPTR, CCameraCtrlLogic );
	REG_GOBAL_MEMBER_FUNC( "CCameraCtrlLogic::OnBtnSwitchAutoWB", CCameraCtrlLogic::OnBtnSwitchAutoWB, CAMERALOGICRPTR, CCameraCtrlLogic );
	REG_GOBAL_MEMBER_FUNC( "CCameraCtrlLogic::OnSliderRGainChanged", CCameraCtrlLogic::OnSliderRGainChanged, CAMERALOGICRPTR, CCameraCtrlLogic );
	REG_GOBAL_MEMBER_FUNC( "CCameraCtrlLogic::OnSliderBGainChanged", CCameraCtrlLogic::OnSliderBGainChanged, CAMERALOGICRPTR, CCameraCtrlLogic );
	REG_GOBAL_MEMBER_FUNC( "CCameraCtrlLogic::OnSliderContrastChanged", CCameraCtrlLogic::OnSliderContrastChanged, CAMERALOGICRPTR, CCameraCtrlLogic );
	REG_GOBAL_MEMBER_FUNC( "CCameraCtrlLogic::OnSliderSaturatChanged", CCameraCtrlLogic::OnSliderSaturatChanged, CAMERALOGICRPTR, CCameraCtrlLogic );
	REG_GOBAL_MEMBER_FUNC( "CCameraCtrlLogic::OnSliderSharpChanged", CCameraCtrlLogic::OnSliderSharpChanged, CAMERALOGICRPTR, CCameraCtrlLogic );
	REG_GOBAL_MEMBER_FUNC( "CCameraCtrlLogic::OnSliderBrightChanged", CCameraCtrlLogic::OnSliderBrightChanged, CAMERALOGICRPTR, CCameraCtrlLogic );
	REG_GOBAL_MEMBER_FUNC( "CCameraCtrlLogic::OnComboboxExposureGainClick", CCameraCtrlLogic::OnComboboxExposureGainClick, CAMERALOGICRPTR, CCameraCtrlLogic );
	REG_GOBAL_MEMBER_FUNC( "CCameraCtrlLogic::OnComboboxShutClick", CCameraCtrlLogic::OnComboboxShutClick, CAMERALOGICRPTR, CCameraCtrlLogic );
	REG_GOBAL_MEMBER_FUNC( "CCameraCtrlLogic::OnEdtRGainChange", CCameraCtrlLogic::OnEdtRGainChange, CAMERALOGICRPTR, CCameraCtrlLogic );
	REG_GOBAL_MEMBER_FUNC( "CCameraCtrlLogic::OnKillFocusEdtRGain", CCameraCtrlLogic::OnKillFocusEdtRGain, CAMERALOGICRPTR, CCameraCtrlLogic );
	REG_GOBAL_MEMBER_FUNC( "CCameraCtrlLogic::OnEdtBGainChange", CCameraCtrlLogic::OnEdtBGainChange, CAMERALOGICRPTR, CCameraCtrlLogic );
	REG_GOBAL_MEMBER_FUNC( "CCameraCtrlLogic::OnKillFocusEdtBGain", CCameraCtrlLogic::OnKillFocusEdtBGain, CAMERALOGICRPTR, CCameraCtrlLogic );
	REG_GOBAL_MEMBER_FUNC( "CCameraCtrlLogic::OnEdtContrastChange", CCameraCtrlLogic::OnEdtContrastChange, CAMERALOGICRPTR, CCameraCtrlLogic );
	REG_GOBAL_MEMBER_FUNC( "CCameraCtrlLogic::OnKillFocusEdtContrast", CCameraCtrlLogic::OnKillFocusEdtContrast, CAMERALOGICRPTR, CCameraCtrlLogic );
	REG_GOBAL_MEMBER_FUNC( "CCameraCtrlLogic::OnEdtSaturatChange", CCameraCtrlLogic::OnEdtSaturatChange, CAMERALOGICRPTR, CCameraCtrlLogic );
	REG_GOBAL_MEMBER_FUNC( "CCameraCtrlLogic::OnKillFocusEdtSaturat", CCameraCtrlLogic::OnKillFocusEdtSaturat, CAMERALOGICRPTR, CCameraCtrlLogic );
	REG_GOBAL_MEMBER_FUNC( "CCameraCtrlLogic::OnEdtSharpChange", CCameraCtrlLogic::OnEdtSharpChange, CAMERALOGICRPTR, CCameraCtrlLogic );
	REG_GOBAL_MEMBER_FUNC( "CCameraCtrlLogic::OnKillFocusEdtSharp", CCameraCtrlLogic::OnKillFocusEdtSharp, CAMERALOGICRPTR, CCameraCtrlLogic );
	REG_GOBAL_MEMBER_FUNC( "CCameraCtrlLogic::OnEdtBrightChange", CCameraCtrlLogic::OnEdtBrightChange, CAMERALOGICRPTR, CCameraCtrlLogic );
	REG_GOBAL_MEMBER_FUNC( "CCameraCtrlLogic::OnKillFocusEdtBright", CCameraCtrlLogic::OnKillFocusEdtBright, CAMERALOGICRPTR, CCameraCtrlLogic );
//	REG_GOBAL_MEMBER_FUNC( "CCameraCtrlLogic::OnBtnSwitchLightPensationClick", CCameraCtrlLogic::OnBtnSwitchLightPensationClick, CAMERALOGICRPTR, CCameraCtrlLogic );
	REG_GOBAL_MEMBER_FUNC( "CCameraCtrlLogic::OnBtnSwitchNRClick", CCameraCtrlLogic::OnBtnSwitchNRClick,  CAMERALOGICRPTR, CCameraCtrlLogic );
	REG_GOBAL_MEMBER_FUNC( "CCameraCtrlLogic::OnComboboxNRClick", CCameraCtrlLogic::OnComboboxNRClick,  CAMERALOGICRPTR, CCameraCtrlLogic );	
	REG_GOBAL_MEMBER_FUNC( "CCameraCtrlLogic::OnBtnSwitch2DNRClick", CCameraCtrlLogic::OnBtnSwitch2DNRClick,  CAMERALOGICRPTR, CCameraCtrlLogic );
	REG_GOBAL_MEMBER_FUNC( "CCameraCtrlLogic::OnCombobox2DNRClick", CCameraCtrlLogic::OnCombobox2DNRClick,  CAMERALOGICRPTR, CCameraCtrlLogic );
	REG_GOBAL_MEMBER_FUNC( "CCameraCtrlLogic::OnBtnSwitch3DNRClick", CCameraCtrlLogic::OnBtnSwitch3DNRClick,  CAMERALOGICRPTR, CCameraCtrlLogic );
	REG_GOBAL_MEMBER_FUNC( "CCameraCtrlLogic::OnCombobox3DNRClick", CCameraCtrlLogic::OnCombobox3DNRClick,  CAMERALOGICRPTR, CCameraCtrlLogic );
	REG_GOBAL_MEMBER_FUNC( "CCameraCtrlLogic::OnBtnSwitchOrderPosClick", CCameraCtrlLogic::OnBtnSwitchOrderPosClick, CAMERALOGICRPTR, CCameraCtrlLogic );
	REG_GOBAL_MEMBER_FUNC( "CCameraCtrlLogic::OnBtnUpdateVersion", CCameraCtrlLogic::OnBtnUpdateVersion, CAMERALOGICRPTR, CCameraCtrlLogic );
	REG_GOBAL_MEMBER_FUNC( "CCameraCtrlLogic::OnBtnOrderPosList", CCameraCtrlLogic::OnBtnOrderPosList, CAMERALOGICRPTR, CCameraCtrlLogic );
	REG_GOBAL_MEMBER_FUNC( "CCameraCtrlLogic::OnBtnSaveOrderPos", CCameraCtrlLogic::OnBtnSaveOrderPos, CAMERALOGICRPTR, CCameraCtrlLogic );
	REG_GOBAL_MEMBER_FUNC( "CCameraCtrlLogic::OnBtnSwitchKeyStoneAdjust", CCameraCtrlLogic::OnBtnSwitchKeyStoneAdjust, CAMERALOGICRPTR, CCameraCtrlLogic );
	REG_GOBAL_MEMBER_FUNC( "CCameraCtrlLogic::OnBtnCheckBackLightClick", CCameraCtrlLogic::OnBtnCheckBackLightClick, CAMERALOGICRPTR, CCameraCtrlLogic );
	REG_GOBAL_MEMBER_FUNC( "CCameraCtrlLogic::OnSliderAdjustRangeChanged", CCameraCtrlLogic::OnSliderAdjustRangeChanged, CAMERALOGICRPTR, CCameraCtrlLogic );
	REG_GOBAL_MEMBER_FUNC( "CCameraCtrlLogic::OnSliderHoriStretchChanged", CCameraCtrlLogic::OnSliderHoriStretchChanged, CAMERALOGICRPTR, CCameraCtrlLogic );
	REG_GOBAL_MEMBER_FUNC( "CCameraCtrlLogic::OnEdtAdjustRangeChange", CCameraCtrlLogic::OnEdtAdjustRangeChange, CAMERALOGICRPTR, CCameraCtrlLogic );
	REG_GOBAL_MEMBER_FUNC( "CCameraCtrlLogic::OnKillFocusEdtAdjustRange", CCameraCtrlLogic::OnKillFocusEdtAdjustRange, CAMERALOGICRPTR, CCameraCtrlLogic );
	REG_GOBAL_MEMBER_FUNC( "CCameraCtrlLogic::OnEdtHoriStretchChange", CCameraCtrlLogic::OnEdtHoriStretchChange, CAMERALOGICRPTR, CCameraCtrlLogic );
	REG_GOBAL_MEMBER_FUNC( "CCameraCtrlLogic::OnKillFocusEdtHoriStretch", CCameraCtrlLogic::OnKillFocusEdtHoriStretch, CAMERALOGICRPTR, CCameraCtrlLogic );
	REG_GOBAL_MEMBER_FUNC( "CCameraCtrlLogic::OnComboboxGammaClick", CCameraCtrlLogic::OnComboboxGammaClick, CAMERALOGICRPTR, CCameraCtrlLogic );
}

void CCameraCtrlLogic::UnRegFunc()
{
	UN_REG_GOBAL_FUNC( "CCameraCtrlLogic::InitWnd" );
}

bool CCameraCtrlLogic::InitWnd(  const IArgs & arg )
{
	CLogicBase::InitWnd( arg );

    //机芯
	std::vector<CString> vecCamera;																//设置摄像机下拉框数据
	vecCamera.push_back("机芯1");
	vecCamera.push_back("机芯2");
	vecCamera.push_back("机芯3");
	UIFACTORYMGR_PTR->SetComboListData( "ComboboxCamera", vecCamera, m_pWndTree );
	SetCamName( _T("机芯1") );

    //类型
	std::vector<CString> vecCameraStyle;
	vecCameraStyle.push_back("H650");
	vecCameraStyle.push_back("Sony");
    vecCameraStyle.push_back("SONY FCB-CS8230");
    UIFACTORYMGR_PTR->SetComboListData( "ComboboxCameraStyle", vecCameraStyle, m_pWndTree );
	SetCamStyleName( _T("H650") );

    //输出制式
    vecCamera.clear();
    vecCamera.push_back("4K@25fps");
    vecCamera.push_back("4K@30fps");
    vecCamera.push_back("1080P@25fps");
    vecCamera.push_back("1080P@30fps");
    vecCamera.push_back("1080P@50fps");
    vecCamera.push_back("1080P@60fps");
    vecCamera.push_back("720P@50fps");
    vecCamera.push_back("720P@60fps");
    UIFACTORYMGR_PTR->SetComboListData( m_strComboboxOutputFormat, vecCamera, m_pWndTree );
	UIFACTORYMGR_PTR->SetComboText( m_strComboboxOutputFormat, _T("4K@30fps"), m_pWndTree );

    //MOON904K30光圈
    vecCamera.clear();
    vecCamera.push_back("F2.8");
    vecCamera.push_back("F3.0");
    vecCamera.push_back("F3.5");
    vecCamera.push_back("F4.0");
    vecCamera.push_back("F4.5");
    UIFACTORYMGR_PTR->SetComboListData( m_strComboboxApertre, vecCamera, m_pWndTree );
	UIFACTORYMGR_PTR->SetComboText( m_strComboboxApertre, _T("F3.5"), m_pWndTree );

	//光圈数据初始化设置
	vecCamera.clear();
	vecCamera.push_back("Close");
	vecCamera.push_back("F9.6");
	vecCamera.push_back("F8");
	vecCamera.push_back("F6.8");
	vecCamera.push_back("F5.6");
	vecCamera.push_back("F4.8");
	vecCamera.push_back("F4");
	vecCamera.push_back("F3.4");
	vecCamera.push_back("F2.8");
	vecCamera.push_back("F2.4");
	vecCamera.push_back("F2");
	vecCamera.push_back("F1.8");
	UIFACTORYMGR_PTR->SetComboListData( m_strComboboxAperture, vecCamera, m_pWndTree );
	UIFACTORYMGR_PTR->SetComboText( m_strComboboxAperture, _T("F1.8"), m_pWndTree );

	//降噪等级
	vecCamera.clear();																
	vecCamera.push_back("低");
	vecCamera.push_back("中");
	vecCamera.push_back("高");
// 	vecCamera.push_back("level 4");
// 	vecCamera.push_back("level 5");
	UIFACTORYMGR_PTR->SetComboListData( "ComboboxNR", vecCamera, m_pWndTree );
	UIFACTORYMGR_PTR->SetComboText( "ComboboxNR", _T("中"), m_pWndTree );

	//2D降噪等级
	vecCamera.clear();																
	vecCamera.push_back("level 1");
	vecCamera.push_back("level 2");
	vecCamera.push_back("level 3");
	vecCamera.push_back("level 4");
	vecCamera.push_back("level 5");
	UIFACTORYMGR_PTR->SetComboListData( "Combobox2DNR", vecCamera, m_pWndTree );
	UIFACTORYMGR_PTR->SetComboText( "Combobox2DNR", _T("level 2"), m_pWndTree );

	//3D降噪等级
	vecCamera.clear();																
	vecCamera.push_back("level 1");
	vecCamera.push_back("level 2");
	vecCamera.push_back("level 3");
	vecCamera.push_back("level 4");
	vecCamera.push_back("level 5");
	UIFACTORYMGR_PTR->SetComboListData( "Combobox3DNR", vecCamera, m_pWndTree );
	UIFACTORYMGR_PTR->SetComboText( "Combobox3DNR", _T("level 2"), m_pWndTree );

	//设置快门下拉框数据
	SetShutComboxData();

	std::vector<CString> vecExposureGain;	                                                 //设置曝光增益下拉框数据
	for ( float fExposureGain = -10.5; fExposureGain < 12; fExposureGain += 1.5 )
	{
		CString strExposureGain;
		strExposureGain.Format( "%.1fdB", fExposureGain );
		if ( strExposureGain.Right(3) == "0dB" )
		{
 			int npos = strExposureGain.ReverseFind('.');
			if ( npos >= 0 )
 			{
 				strExposureGain = strExposureGain.Left(npos) + strExposureGain.Right(2);
 			}
 		}
 		vecExposureGain.push_back(strExposureGain);
	}
	UIFACTORYMGR_PTR->SetComboListData( m_strComboboxExposureGain, vecExposureGain, m_pWndTree ); 
	// 增益默认值
	UIFACTORYMGR_PTR->SetComboText( m_strComboboxExposureGain, "10.5dB", m_pWndTree );

	std::vector<CString> vecGammaPara;
	vecGammaPara.push_back("0");
	vecGammaPara.push_back("1");
	vecGammaPara.push_back("2");
	vecGammaPara.push_back("3");
	UIFACTORYMGR_PTR->SetComboListData( "ComboboxGamma", vecGammaPara, m_pWndTree );
	//伽码参数默认值
	UIFACTORYMGR_PTR->SetComboText( m_strComboboxGamma, _T("1"), m_pWndTree );

	CTransparentBtn* pBtnZoomPlus = (CTransparentBtn*)UIFACTORYMGR_PTR->GetWindowPtr( m_strBtnZoomPlus, m_pWndTree );
	if ( NULL != pBtnZoomPlus )
	{
		pBtnZoomPlus->SetUseElapse(600);
	}

	CTransparentBtn* pBtnZoomSub = (CTransparentBtn*)UIFACTORYMGR_PTR->GetWindowPtr( m_strBtnZoomSub, m_pWndTree );
	if ( NULL != pBtnZoomSub )
	{
		pBtnZoomSub->SetUseElapse(600);
	}

	SetFocus(NULL);

	return true;
}

void CCameraCtrlLogic::Clear()
{
	int i = 0;
	m_bIsCameraPowerOn = false;
	m_bLoginByOther = false;
	memset(&m_emTPMOOMMode,0,sizeof(EmTPMOOMMode));

	memset(&m_tTpMechver1, 0, sizeof(TTPMechVer));
	memset(&m_tTpMechver2, 0, sizeof(TTPMechVer));
	memset(&m_tTpMechver3, 0, sizeof(TTPMechVer));
}

bool CCameraCtrlLogic::OnComboboxCameraClick( const IArgs& args )
{
	if ( m_pWndTree == NULL )
	{
		return false;
	}

	//m_bNty = false;

	Value_TransparentComboBoxText valueTransparentComboBoxText;
	UIFACTORYMGR_PTR->GetPropertyValue( valueTransparentComboBoxText, m_strComboboxCamera, m_pWndTree );

	u8 byCameraIndx = 0;
	String strComboText = valueTransparentComboBoxText.strComboText;
	if ( strComboText == "机芯1" )
	{
		byCameraIndx = 0;
	}
	else if ( strComboText == "机芯2" )
	{
		byCameraIndx = 1;
	}
	else if ( strComboText == "机芯3" )
	{
		byCameraIndx = 2;
	}


	m_byCamIndex = byCameraIndx;
	u16 nRet = COMIFMGRPTR->CamSelCmd( byCameraIndx );
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "选择摄像机请求发送失败" );
	}

	return true;
}

bool CCameraCtrlLogic::OnComboboxCameraStyleClick(const IArgs& args)
{
	if ( m_pWndTree == NULL )
	{
		return false;
	}

	Value_TransparentComboBoxText valueTransparentComboBoxText;
	UIFACTORYMGR_PTR->GetPropertyValue( valueTransparentComboBoxText, m_strComboboxCameraStyle, m_pWndTree );

	EmTPMechanism emTPMechanism;
	String strComboText = valueTransparentComboBoxText.strComboText;

	bool bHide = false;
	Window *pWnd = UIFACTORYMGR_PTR->GetWindowPtr( m_strEdtZoom, m_pWndTree );
	if( strComboText == "Sony")
	{
		emTPMechanism = emSony;
		bHide = true;
		pWnd->ModifyStyle(ES_NUMBER, WS_CHILD|WS_CLIPSIBLINGS|ES_MULTILINE);
        UIFACTORYMGR_PTR->LoadScheme( _T("SchmCamNormal"), m_pWndTree );
	}
    else if ( strComboText == "SONY FCB-CS8230" )
    {
        emTPMechanism = emSonyFCBCS8230;
        bHide = false;
        pWnd->ModifyStyle(ES_NUMBER, WS_CHILD|WS_CLIPSIBLINGS|ES_MULTILINE);
        UIFACTORYMGR_PTR->LoadScheme( _T("SchmMoon904K30"), m_pWndTree );
    }
	else
	{
		emTPMechanism = emH650;
		bHide = false;
		pWnd->ModifyStyle(0, WS_CHILD|WS_CLIPSIBLINGS|ES_NUMBER );
        UIFACTORYMGR_PTR->LoadScheme( _T("SchmCamNormal"), m_pWndTree );
	}

	u16 nRet = COMIFMGRPTR->CamStyleSelCmd( emTPMechanism );
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "选择摄像机机芯类型请求发送失败" );
	}

    showCameraInfo(emTPMechanism, bHide);


// 	String str;
// 	UIFACTORYMGR_PTR->GetCaption( m_strEdtZoom, str, m_pWndTree );
// 	
// 	SetZoomCmd(str.c_str());

	return true;
}

bool CCameraCtrlLogic::OnBtnSyncClick(const IArgs& args)
{
	Value_TransparentComboBoxText valueTransparentComboBoxText;
	UIFACTORYMGR_PTR->GetPropertyValue( valueTransparentComboBoxText, m_strComboboxCamera, m_pWndTree );
	
	u8 byCameraIndx = 0;
	String strComboText = valueTransparentComboBoxText.strComboText;
	if ( strComboText == "机芯1" )
	{
		byCameraIndx = 0;
	}
	else if ( strComboText == "机芯2" )
	{
		byCameraIndx = 1;
	}
	else if ( strComboText == "机芯3" )
	{
		byCameraIndx = 2;
	}

    u16 nRet = COMIFMGRPTR->SetMoonCamCfgSyncCmd(byCameraIndx);
	if( nRet != NO_ERROR )
	{
		WARNMESSAGE( "同步摄像机机芯请求发送失败" );
	}
	
	return true;
}

bool CCameraCtrlLogic::OnComboboxOutputFormatClick(const IArgs& args)
{
    if ( m_pWndTree == NULL )
    {
        return false;
    }
    
    Value_TransparentComboBoxText valueTransparentComboBoxText;
    UIFACTORYMGR_PTR->GetPropertyValue( valueTransparentComboBoxText, m_strComboboxOutputFormat, m_pWndTree );
    
    u8 byOutputFormatIndx = 0;
    String strComboText = valueTransparentComboBoxText.strComboText;
    if ( strComboText == "4K@25fps" )
    {
        byOutputFormatIndx = 0;
    }
    else if ( strComboText == "4K@30fps" )
    {
        byOutputFormatIndx = 1;
    }
    else if ( strComboText == "1080P@25fps" )
    {
        byOutputFormatIndx = 2;
    }
    else if ( strComboText == "1080P@30fps" )
    {
        byOutputFormatIndx = 3;
    }
    else if ( strComboText == "1080P@50fps" )
    {
        byOutputFormatIndx = 4;
    }
    else if ( strComboText == "1080P@60fps" )
    {
        byOutputFormatIndx = 5;
    }
    else if ( strComboText == "720P@50fps" )
    {
        byOutputFormatIndx = 6;
    }
    else if ( strComboText == "720P@60fps" )
    {
        byOutputFormatIndx = 7;
    }
    
    
    //m_byCamIndex = byOutputFormatIndx;
    u16 nRet = COMIFMGRPTR->CamSelCmd( byOutputFormatIndx );//need add
    if ( nRet != NO_ERROR )
    {
        WARNMESSAGE( "选择输出制式请求发送失败" );
    }
    
	return true;
}

bool CCameraCtrlLogic::OnComboboxGammaClick(const IArgs& args)
{
	if ( m_pWndTree == NULL )
	{
		return false;
	}

	Value_TransparentComboBoxText valueTransparentComboBoxText;
	UIFACTORYMGR_PTR->GetPropertyValue( valueTransparentComboBoxText, m_strComboboxGamma, m_pWndTree );

	EmH650Gamma emH650Gamma;
	String strComboText = valueTransparentComboBoxText.strComboText;

	if( "0" == strComboText )
	{
		emH650Gamma = emGamma1;
	}
	else if( "1" == strComboText )
	{
		emH650Gamma = emGamma2;
	}
	else if( "2" == strComboText )
	{
		emH650Gamma = emGamma3;
	}
	else
	{
		emH650Gamma = emGamma4;
	}

	u16 nRet = COMIFMGRPTR->GammaStyleSelCmd( emH650Gamma );
	if(nRet != NO_ERROR)
	{
		WARNMESSAGE( "选择Gamma请求发送失败" );
	}
	
	return true;
}

bool CCameraCtrlLogic::OnBtnZoomPlusClick( const IArgs& args )
{
	EmZoom emZoom = emTele;
	
// 	u16 nRet = COMIFMGRPTR->SetCamZoomCmd( emZoom, m_byCamIndex );
// 	if ( nRet != NO_ERROR )
// 	{
// 		WARNMESSAGE( "Zoom请求发送失败" );
// 	}
	
	return true;
}

bool CCameraCtrlLogic::OnBtnZoomSubClick( const IArgs& args )
{
	EmZoom emZoom = emWide;
	
// 	u16 nRet = COMIFMGRPTR->SetCamZoomCmd( emZoom, m_byCamIndex );
// 	if ( nRet != NO_ERROR )
// 	{
// 		WARNMESSAGE( "Zoom请求发送失败" );
// 	}
	
	return true;
}

bool CCameraCtrlLogic::OnLBtnDownZoomPlus( const IArgs& args )
{
	EmTPZOOM emZoom = emEnlarge;
	
	u16 nRet = COMIFMGRPTR->SetCamZoomCmd( emZoom, m_byCamIndex );
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "Zoom请求发送失败" );
	}
	
	return true;
}

bool CCameraCtrlLogic::OnLBtnDoubleDownZoomPlus( const IArgs& args )
{
	EmTPZOOM emZoom = emEnlarge;
	
	u16 nRet = COMIFMGRPTR->SetCamZoomCmd( emZoom, m_byCamIndex );
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "Zoom请求发送失败" );
	}

	return true;	
}

bool CCameraCtrlLogic::OnLBtnUpZoomPlus( const IArgs& args )
{
	u16 nRet = COMIFMGRPTR->SetCamZoomStopCmd( m_byCamIndex );
	return true;
}

bool CCameraCtrlLogic::OnLBtnDownZoomSub( const IArgs& args )
{
	EmTPZOOM emZoom = emReduce;
	
	u16 nRet = COMIFMGRPTR->SetCamZoomCmd( emZoom, m_byCamIndex );
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "Zoom请求发送失败" );
	}
	
	return true;
}

bool CCameraCtrlLogic::OnLBtnDoubleDownZoomSub( const IArgs& args )
{
	EmTPZOOM emZoom = emReduce;
	
	u16 nRet = COMIFMGRPTR->SetCamZoomCmd( emZoom, m_byCamIndex );
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "Zoom请求发送失败" );
	}
	
	return true;	
}

bool CCameraCtrlLogic::OnLBtnUpZoomSub( const IArgs& args )
{
	u16 nRet = COMIFMGRPTR->SetCamZoomStopCmd( m_byCamIndex );
	return true;
}

bool CCameraCtrlLogic::OnBtnManuelFocusClick( const IArgs& args )
{
	if( m_emTPMOOMMode != emManual )
	{
		m_emTPMOOMMode = emManual;
		u16 nRet = COMIFMGRPTR->SetCamAutoFocusCmd(m_emTPMOOMMode);
		if ( nRet != NO_ERROR )
		{
			WARNMESSAGE( "手动焦距请求发送失败" );
		}
	}

	return true;
}

bool CCameraCtrlLogic::OnBtnAutoFocusClick( const IArgs& args )
{
	if ( m_emTPMOOMMode != emAuto )
	{
		m_emTPMOOMMode = emAuto;
		u16 nRet = COMIFMGRPTR->SetCamAutoFocusCmd(m_emTPMOOMMode);
		if ( nRet != NO_ERROR )
		{
			WARNMESSAGE( "自动焦距请求发送失败" );
		}	
	}

	return true;
}

bool CCameraCtrlLogic::OnLBtnDownFocusNear( const IArgs& args )
{	
	u16 nRet = COMIFMGRPTR->SetCamFocusNearCmd();
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "焦距拉近请求发送失败" );
	}

	return true;
}

bool CCameraCtrlLogic::OnLBtnUpFocusNear( const IArgs& args )
{	
	u16 nRet = COMIFMGRPTR->SetCamFocusStopCmd();
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "焦距拉近请求发送失败" );
	}

	return true;
}

bool CCameraCtrlLogic::OnLBtnDownFocusFar( const IArgs& args )
{	
	u16 nRet = COMIFMGRPTR->SetCamFocusFarCmd();
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "焦距推远请求发送失败" );
	}
	
	return true;
}

bool CCameraCtrlLogic::OnLBtnUpFocusFar( const IArgs& args )
{	
	u16 nRet = COMIFMGRPTR->SetCamFocusStopCmd();
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "焦距推远请求发送失败" );
	}
	
	return true;
}

bool CCameraCtrlLogic::OnBtnSwitchAutoExposure( const IArgs& args )
{
	if ( m_pWndTree == NULL )
	{
		return false;
	}
	
	Value_SwitchState valueSwitchState;
	UIFACTORYMGR_PTR->GetPropertyValue( valueSwitchState, m_strBtnSwitchAutoExposure, m_pWndTree );

	if ( valueSwitchState.bState )
	{
		u16 nRet = COMIFMGRPTR->CamAutoExposureCmd( emAuto );
		if ( nRet != NO_ERROR )
		{
			WARNMESSAGE( "自动曝光请求发送失败" );
		}
		//手动变为自动时，如果背光补偿勾选，还需再发遍消息
		s32 nCheckState = 0;
		UIFACTORYMGR_PTR->GetCheckState( m_strBtnCheckBackLight, nCheckState, m_pWndTree );	
		if ( nCheckState )
		{
			u16 nRet = COMIFMGRPTR->CamLightPensation( TRUE );	
			if ( nRet != NO_ERROR )
			{
				WARNMESSAGE( "背光补偿请求发送失败" );
			}
		}
	}
	else
	{
		u16 nRet = COMIFMGRPTR->CamAutoExposureCmd( emManual );
		if ( nRet != NO_ERROR )
		{
			WARNMESSAGE( "手动曝光请求发送失败" );
		}
		else
		{
			EmTPAperture emTPAperture;
			GetApertureValue( emTPAperture );
			u16 nRetAperture = COMIFMGRPTR->CamApertureCmd( emTPAperture );
			if ( nRetAperture != NO_ERROR )
			{
				WARNMESSAGE( "光圈请求发送失败" );
 			}

			if ( m_bSourceCfg )
			{
				EmTPSOrThShutter emShutSpd;
				GetShutSpdValue( emShutSpd );
				u16 nRetShutSpd = COMIFMGRPTR->CamShutSpdCmd( emShutSpd );
				if ( nRetShutSpd != NO_ERROR )
				{
					WARNMESSAGE( "快门请求发送失败" );
 				}
			}
			else
			{
				EmTPFOrTwShutter emTwShutter;
				GetTwShutterValue( emTwShutter );
				u16 nRetShutSpd = COMIFMGRPTR->CamTwShutSpdCmd( emTwShutter );
				if ( nRetShutSpd != NO_ERROR )
				{
					WARNMESSAGE( "快门请求发送失败" );
 				}
			}

			EmTPExpGain emGain;
			GetExpGainValue( emGain );
			
			u16 nRetGain = COMIFMGRPTR->CamGainCmd( emGain );
			if ( nRetGain != NO_ERROR )
			{
				WARNMESSAGE( "增益请求发送失败" );
			}
			
		}
	}

	return true;
}

// 白平衡
bool CCameraCtrlLogic::OnBtnSwitchAutoWB( const IArgs& args )
{
	if ( m_pWndTree == NULL )
	{
		return false;
	}
	
	Value_SwitchState valueSwitchState;
	UIFACTORYMGR_PTR->GetPropertyValue( valueSwitchState, m_strBtnSwitchAutoWB, m_pWndTree );
	
	if ( valueSwitchState.bState )
	{
		u16 nRet = COMIFMGRPTR->CamAutoWBCmd( emAuto );
		if ( nRet != NO_ERROR )
		{
			WARNMESSAGE( "自动白平衡请求发送失败" );
		}
	}
	else
	{
		u16 nRet = COMIFMGRPTR->CamAutoWBCmd( emManual );
		if ( nRet != NO_ERROR )
		{
			WARNMESSAGE( "手动白平衡请求发送失败" );
		}

		String strRGain;
		UIFACTORYMGR_PTR->GetCaption( m_strEdtRGain, strRGain, m_pWndTree );
		
		u32 dwRGain = atoi(strRGain.c_str());
		u32 nRetRGain = COMIFMGRPTR->CamRGainCmd( dwRGain );
		if ( nRetRGain != NO_ERROR )
		{
			WARNMESSAGE( "RGain调节请求发送失败" );
		}


		String strBGain;
		UIFACTORYMGR_PTR->GetCaption( m_strEdtBGain, strBGain, m_pWndTree );

		u32 dwBGain = atoi(strBGain.c_str());
		u32 nRetBGain = COMIFMGRPTR->CamBGainCmd( dwBGain );
		if ( nRetBGain != NO_ERROR )
		{
			WARNMESSAGE( "BGain调节请求发送失败" );
		}
	}

	return true;
}

bool CCameraCtrlLogic::OnSliderRGainChanged( const IArgs& args )
{
	if ( m_pWndTree == NULL )
	{
		return false;
	}


	Value_CSliderCtrlPos valueCSliderCtrlPos;
	UIFACTORYMGR_PTR->GetPropertyValue( valueCSliderCtrlPos, m_strSliderRGain, m_pWndTree );
	
	SetRGainValue( valueCSliderCtrlPos.nPos );
	
	u32 dwRGain = valueCSliderCtrlPos.nPos;
	u32 dwRGainInLib = 0;
	MOONLIBDATAMGRPTR->GetCamRGain( dwRGainInLib );
	if ( dwRGain == dwRGainInLib )
	{
		return true;
	}

	u16 nRet = COMIFMGRPTR->CamRGainCmd( dwRGain );
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "RGain调节请求发送失败" );
	}

	return true;
}

bool CCameraCtrlLogic::OnSliderBGainChanged( const IArgs& args )
{
	if ( m_pWndTree == NULL )
	{
		return false;
	}

	Value_CSliderCtrlPos valueCSliderCtrlPos;
	UIFACTORYMGR_PTR->GetPropertyValue( valueCSliderCtrlPos, m_strSliderBGain, m_pWndTree );
	
	SetBGainValue( valueCSliderCtrlPos.nPos );
	
	u32 dwBGain = valueCSliderCtrlPos.nPos;
	u32 dwBGainInLib = 0;
	MOONLIBDATAMGRPTR->GetCamBGain( dwBGainInLib );
	if ( dwBGain == dwBGainInLib )
	{
		return true;
	}

	u16 nRet = COMIFMGRPTR->CamBGainCmd( dwBGain );
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "BGain调节请求发送失败" );
	}

	return true;
}

bool CCameraCtrlLogic::OnSliderContrastChanged( const IArgs& args )
{
	if ( m_pWndTree == NULL )
	{
		return false;
	}

	Value_CSliderCtrlPos valueCSliderCtrlPos;
	UIFACTORYMGR_PTR->GetPropertyValue( valueCSliderCtrlPos, m_strSliderContrast, m_pWndTree );
	
	SetContrastValue( valueCSliderCtrlPos.nPos );

	u32 dwContrast = valueCSliderCtrlPos.nPos;
//说实话 不知道这步干嘛用 参照之前的 也是有弊端的
	if ( dwContrast == m_dwContrast )
	{
		return true;
	}

	u16 nRet = COMIFMGRPTR->CamImageParaCmd( emContrast, dwContrast );
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "对比度请求发送失败" );
	}

	return true;
}

bool CCameraCtrlLogic::OnSliderSaturatChanged( const IArgs& args )
{
	if ( m_pWndTree == NULL )
	{
		return false;
	}

	Value_CSliderCtrlPos valueCSliderCtrlPos;
	UIFACTORYMGR_PTR->GetPropertyValue( valueCSliderCtrlPos, m_strSliderSaturat, m_pWndTree );
	
	SetSaturatValue( valueCSliderCtrlPos.nPos );

	u32 dwSaturat = valueCSliderCtrlPos.nPos;

	if ( dwSaturat == m_dwSaturat )
	{
		return true;
	}

	u16 nRet = COMIFMGRPTR->CamImageParaCmd( emSaturat, dwSaturat );
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "饱和度请求发送失败" );
	}

	return true;
}

bool CCameraCtrlLogic::OnSliderSharpChanged( const IArgs& args )
{
	if ( m_pWndTree == NULL )
	{
		return false;
	}

	Value_CSliderCtrlPos valueCSliderCtrlPos;
	UIFACTORYMGR_PTR->GetPropertyValue( valueCSliderCtrlPos, m_strSliderSharp, m_pWndTree );
	
	SetSharpValue( valueCSliderCtrlPos.nPos );

	u32 dwSharp = valueCSliderCtrlPos.nPos;

	if ( dwSharp == m_dwSharp )
	{
		return true;
	}

	u16 nRet = COMIFMGRPTR->CamImageParaCmd( emSharp,dwSharp );
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "锐度请求发送失败" );
	}

	return true;
}

bool CCameraCtrlLogic::OnSliderBrightChanged( const IArgs& args )
{
	if ( m_pWndTree == NULL )
	{
		return false;
	}

	Value_CSliderCtrlPos valueCSliderCtrlPos;
	UIFACTORYMGR_PTR->GetPropertyValue( valueCSliderCtrlPos, m_strSliderBright, m_pWndTree );
	
	SetBrightValue( valueCSliderCtrlPos.nPos );

	u32 dwBright = valueCSliderCtrlPos.nPos;

	if ( dwBright == m_dwBright )
	{
		return true;
	}

	u16 nRet = COMIFMGRPTR->CamImageParaCmd( emBlight,dwBright );
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "亮度请求发送失败" );
	}

	return true;
}

HRESULT CCameraCtrlLogic::OnCameraCfgNty( WPARAM wparam, LPARAM lparam )
{
	if ( m_bIsCameraPowerOn && m_bLoginByOther )
	{
		m_bLoginByOther = false;
	    ResetNormal();
	}

	TTPMoonCamInfo tMoonCameraCfg;
	MOONLIBDATAMGRPTR->GetCamCfg( tMoonCameraCfg );
	//初次登陆赋值，一旦聚焦手动/自动被选中，点击选中的不发消息
	m_emTPMOOMMode = tMoonCameraCfg.emFocusMode;
	SetCameraCfg( tMoonCameraCfg );

	return S_OK;
}

HRESULT CCameraCtrlLogic::OnTpMechanismSelectNty(WPARAM wparam, LPARAM lparam)
{
	EmTPMechanism emTPMechanism = static_cast<EmTPMechanism>(lparam);

	bool bhide;
	Window *pWnd = UIFACTORYMGR_PTR->GetWindowPtr( m_strEdtZoom, m_pWndTree );
	if( emTPMechanism == emSony )
	{
		emTPMechanism = emSony;
		bhide = true;
		pWnd->ModifyStyle(ES_NUMBER, WS_CHILD|WS_CLIPSIBLINGS|ES_MULTILINE);
		SetCamStyleName(_T("Sony"));
	}
    else if( emTPMechanism == emSonyFCBCS8230 )
    {
        emTPMechanism = emSonyFCBCS8230;
        bhide = false;
        pWnd->ModifyStyle(ES_NUMBER, WS_CHILD|WS_CLIPSIBLINGS|ES_MULTILINE);
		SetCamStyleName(_T("SONY FCB-CS8230"));
    }
	else
	{
		emTPMechanism = emH650;
		bhide = false;
		pWnd->ModifyStyle(0, WS_CHILD|WS_CLIPSIBLINGS|ES_NUMBER );
		SetCamStyleName(_T("H650"));
	}

	showCameraInfo(emTPMechanism, bhide);
	return S_OK;
}

HRESULT CCameraCtrlLogic::OnTpMechVerNty(WPARAM wparam, LPARAM lparam)
{
	TTPMechVer tTPMechVer = *(TTPMechVer*)(wparam);

	if( 0 == tTPMechVer.byIndex )
	{
		m_tTpMechver1 = tTPMechVer;
	}
	else if( 1 == tTPMechVer.byIndex )
	{
		m_tTpMechver2 = tTPMechVer;
	}
	else
	{
		m_tTpMechver3 = tTPMechVer;
	}

	return S_OK;
}

HRESULT CCameraCtrlLogic::OnCameraStyleSelectInd(WPARAM wparam, LPARAM lparam)
{
	BOOL bRet = static_cast<BOOL>(lparam);
	//EmTPMechanism emTPMechanism = *(EmTPMechanism*)(wparam);

	if ( bRet == FALSE )
	{
		WARNMESSAGE( _T("选择摄像机类型设置失败") );
	}

	TTPMoonCamInfo tMoonCameraCfg;
	MOONLIBDATAMGRPTR->GetCamCfg( tMoonCameraCfg );
	
	m_emTPMOOMMode = tMoonCameraCfg.emFocusMode;
	SetCameraCfg( tMoonCameraCfg );

	return S_OK;
}

HRESULT CCameraCtrlLogic::OnCameraSelectInd( WPARAM wparam, LPARAM lparam )
{
	BOOL bRet = static_cast<BOOL>(lparam);
	if ( bRet == FALSE )
	{
		WARNMESSAGE( _T("选择摄像机设置失败") );
	}

	TTPMoonCamInfo tMoonCameraCfg;
	MOONLIBDATAMGRPTR->GetCamCfg( tMoonCameraCfg );
	//若不赋值 切换机芯时 成员变量无初值
	m_emTPMOOMMode = tMoonCameraCfg.emFocusMode;
	SetCameraCfg( tMoonCameraCfg );
	//切换机芯时，根据最后一次的操作结果设置值
//	SetZoomValue((float)tMoonCameraCfg.dwZoom/100);
	//m_bNty = true;
	
	return S_OK;
}

HRESULT CCameraCtrlLogic::OnCamParamSyncInd(WPARAM wparam, LPARAM lparam)
{
	BOOL bRet = static_cast<BOOL>(lparam);
	if ( bRet == FALSE )
	{
		WARNMESSAGE( _T("摄像机同步失败") );
	}

	return S_OK;
}

HRESULT CCameraCtrlLogic::OnCameraZoomInd( WPARAM wparam, LPARAM lparam )
{
	if ( m_pWndTree == NULL )
	{
		return S_FALSE;
	}

	EmZoom emZoom = static_cast<EmZoom>(wparam);
	BOOL bCamZoom = static_cast<BOOL>(lparam);

	if ( bCamZoom == FALSE )
	{
		WARNMESSAGE( "Zoom设置失败");
		return S_OK;
	}

	return S_OK;
}

HRESULT CCameraCtrlLogic::OnCameraAutoFocusInd( WPARAM wparam, LPARAM lparam )
{
	EmFocusMode emFocusMode = static_cast<EmFocusMode>(wparam);
	BOOL bRet = static_cast<BOOL>(lparam);

	if ( bRet == FALSE )
	{
		SetCursorPos( 710, 530 );//20130326-解决弹出框后还能点击问题

		WARNMESSAGE( "自动焦距设置失败" );
	}

	return S_OK;
}

HRESULT CCameraCtrlLogic::OnCameraFocusInd( WPARAM wparam, LPARAM lparam )
{
	EmFocus emFocus = static_cast<EmFocus>(wparam);
	BOOL bRet = static_cast<BOOL>(lparam);

	if ( bRet == FALSE )
	{
		WARNMESSAGE( "焦距设置失败" );
	}
	return S_OK;
}

HRESULT CCameraCtrlLogic::OnCameraPersetMoveInd( WPARAM wparam, LPARAM lparam )
{
	if ( m_pWndTree == NULL )
	{
		return S_FALSE;
	}
	
//	BOOL bUsed;
/*	MOONLIBDATAMGRPTR->GetCamPresetMove( bUsed );*/
	BOOL bRet = static_cast<BOOL>(lparam);
	
	if ( bRet == FALSE )
	{
		WARNMESSAGE( "保存至预置位1设置失败");
	}

//	SetPresetValue( bUsed );
	
	return S_OK;
}

HRESULT CCameraCtrlLogic::OnAutoExposureInd( WPARAM wparam, LPARAM lparam )
{
	if ( m_pWndTree == NULL )
	{
		return S_FALSE;
	}

	EmTPMOOMMode emExpMode;
	MOONLIBDATAMGRPTR->GetCamMoonMode( emExpMode );
	BOOL bRet = static_cast<BOOL>(lparam);

	if ( bRet == FALSE )
	{
		WARNMESSAGE( "自动曝光设置失败" );
	}

	SetAutoExp(emExpMode);


	return S_OK;
}

bool CCameraCtrlLogic::OnComboboxApertureClick( const IArgs& args )
{
	EmTPAperture emTPAperture;
	GetApertureValue( emTPAperture );
	u16 nRet = COMIFMGRPTR->CamApertureCmd( emTPAperture );
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "光圈请求发送失败" );
	}
	return true;	
}

bool CCameraCtrlLogic::OnComboboxShutClick( const IArgs& args )
{
	if ( m_bSourceCfg )
	{
		EmTPSOrThShutter emShutSpd;
		GetShutSpdValue( emShutSpd );
		u16 nRet = COMIFMGRPTR->CamShutSpdCmd( emShutSpd );
		if ( nRet != NO_ERROR )
		{
			WARNMESSAGE( "快门请求发送失败" );
		}
	}
	else
	{
		EmTPFOrTwShutter emTwShutter;
		GetTwShutterValue( emTwShutter );
		u16 nRet = COMIFMGRPTR->CamTwShutSpdCmd( emTwShutter );
		if ( nRet != NO_ERROR )
		{
			WARNMESSAGE( "快门请求发送失败" );
		}
	}	
	return true;
}

bool CCameraCtrlLogic::OnComboboxExposureGainClick( const IArgs& args )
{
	EmTPExpGain emGain;
	GetExpGainValue( emGain );
	
	u16 nRet = COMIFMGRPTR->CamGainCmd( emGain );
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "增益请求发送失败" );
	}
	return true;
}

HRESULT CCameraCtrlLogic::OnCameraApertureInd( WPARAM wparam, LPARAM lparam )
{
	if ( m_pWndTree == NULL )
	{
		return S_FALSE;
	}
	
	EmTPAperture emAper;
	MOONLIBDATAMGRPTR->GetCamAperture( emAper );
	BOOL bRet = static_cast<BOOL>(lparam);
	
	if ( bRet == FALSE )
	{
		WARNMESSAGE( "光圈设置失败" );
	}
	
	SetApertureValue(emAper);
	
	return S_OK;
}

HRESULT CCameraCtrlLogic::OnCameraShutSpdInd( WPARAM wparam, LPARAM lparam )
{
	if ( m_pWndTree == NULL )
	{
		return S_FALSE;
	}

	BOOL bRet = static_cast<BOOL>(lparam);
	
	if ( bRet == FALSE )
	{
		WARNMESSAGE( "快门设置失败" );
	}
	
	if ( m_bSourceCfg )
	{
		EmTPSOrThShutter emShutSpd;
		MOONLIBDATAMGRPTR->GetCamShutSpd( emShutSpd );	
		SetShutSpdValue(emShutSpd);
	}
	else
	{
		EmTPFOrTwShutter emTwShutter;
		MOONLIBDATAMGRPTR->GetTwCamShutSpd( emTwShutter );
		SetTwShutterValue(emTwShutter);
	}	
	return S_OK;
}

HRESULT CCameraCtrlLogic::OnCameraGainInd( WPARAM wparam, LPARAM lparam )
{
	if ( m_pWndTree == NULL )
	{
		return S_FALSE;
	}

	EmTPExpGain emGain;
	MOONLIBDATAMGRPTR->GetCamGain( emGain );
	BOOL bRet = static_cast<BOOL>(lparam);

	if ( bRet == FALSE )
	{
		WARNMESSAGE( "增益设置失败" );
	}

	SetExpGainValue( emGain );

	return S_OK;
}

HRESULT CCameraCtrlLogic::OnCameraAutoWBInd( WPARAM wparam, LPARAM lparam )
{
	if ( m_pWndTree == NULL )
	{
		return S_FALSE;
	}
	
	EmTPMOOMMode emWBMode;
	MOONLIBDATAMGRPTR->GetCamWBMode( emWBMode );
	BOOL bRet = static_cast<BOOL>(lparam);
	
	if ( bRet == FALSE )
	{
		WARNMESSAGE( "自动白平衡设置失败" );
	}
	
	SetAutoWB(emWBMode);
		
	return S_OK;
}

bool CCameraCtrlLogic::OnEdtRGainChange( const IArgs& args )
{
	if ( m_pWndTree == NULL )
	{
		return true;
	}
	
	/*Window* pWnd = UIFACTORYMGR_PTR->GetWindowPtr( m_strEdtRGain, m_pWndTree );
	if ( pWnd )
	{
		(( CEdit *) pWnd)->SetSel( -1 );
	}*/
	
	Args_WindowMsg* pMsg = dynamic_cast< Args_WindowMsg *>( const_cast<IArgs*>( &args ));
	
	UINT nChar = 0;
	if ( NULL !=  pMsg  )
	{
		nChar = pMsg->m_Msg.wParam;
	}
	
	if ( nChar == 0x0d )
	{
		SetFocus(NULL);
	}
	
	return true;
}

bool CCameraCtrlLogic::OnKillFocusEdtRGain( const IArgs& args )
{
	String str;
	UIFACTORYMGR_PTR->GetCaption( m_strEdtRGain, str, m_pWndTree );
	
	SetRGainCmd(str.c_str());
	
	return true;
}

void CCameraCtrlLogic::SetRGainCmd( CString str )
{
	int n = atoi( str );
	
	if ( n > 255 )
	{
		n = 255;
	}
	else if ( n < 0)
	{
		n = 0;
	}
	
	u16 nRet = COMIFMGRPTR->CamRGainCmd( n );
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "RGain调节请求发送失败" );
	}
}

bool CCameraCtrlLogic::OnEdtBGainChange( const IArgs& args )
{
	if ( m_pWndTree == NULL )
	{
		return true;
	}
	
	/*Window* pWnd = UIFACTORYMGR_PTR->GetWindowPtr( m_strEdtBGain, m_pWndTree );
	if ( pWnd )
	{
		(( CEdit *) pWnd)->SetSel( -1 );
	}*/
	
	Args_WindowMsg* pMsg = dynamic_cast< Args_WindowMsg *>( const_cast<IArgs*>( &args ));
	
	UINT nChar = 0;
	if ( NULL !=  pMsg  )
	{
		nChar = pMsg->m_Msg.wParam;
	}
	
	if ( nChar == 0x0d )
	{
		SetFocus(NULL);
	}
	
	return true;
}

bool CCameraCtrlLogic::OnKillFocusEdtBGain( const IArgs& args )
{
	String str;
	UIFACTORYMGR_PTR->GetCaption( m_strEdtBGain, str, m_pWndTree );
	
	SetBGainCmd(str.c_str());
	
	return true;
}

void CCameraCtrlLogic::SetBGainCmd( CString str )
{
	int n = atoi( str );
	
	if ( n > 255 )
	{
		n = 255;
	}
	else if ( n < 0)
	{
		n = 0;
	}
	
	u16 nRet = COMIFMGRPTR->CamBGainCmd( n );
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "BGain调节请求发送失败" );
	}
}

HRESULT CCameraCtrlLogic::OnCameraRGainInd( WPARAM wparam, LPARAM lparam )
{
	if ( m_pWndTree == NULL )
	{
		return S_FALSE;
	}

	u32 dwRGain = 0;
	MOONLIBDATAMGRPTR->GetCamRGain( dwRGain );
	BOOL bRet = static_cast<BOOL>(lparam);
	
	if ( bRet == FALSE )
	{
		WARNMESSAGE( "RGain设置失败" );
	}
	
	SetRGainValue(dwRGain);

	
	return S_OK;
}

HRESULT CCameraCtrlLogic::OnCameraBGainInd( WPARAM wparam, LPARAM lparam )
{
	if ( m_pWndTree == NULL )
	{
		return S_FALSE;
	}

	u32 dwBGain = 0;
	MOONLIBDATAMGRPTR->GetCamBGain( dwBGain );
	BOOL bRet = static_cast<BOOL>(lparam);
	
	if ( bRet == FALSE )
	{
		WARNMESSAGE( "BGain设置失败" );
	}
	
	SetBGainValue(dwBGain);

	
	return S_OK;
}

bool CCameraCtrlLogic::OnEdtContrastChange( const IArgs& args )
{
	if ( m_pWndTree == NULL )
	{
		return true;
	}
	
	/*Window* pWnd = UIFACTORYMGR_PTR->GetWindowPtr( m_strEdtContrast, m_pWndTree );
	if ( pWnd )
	{
		(( CEdit *) pWnd)->SetSel( -1 );
	}*/
	
	Args_WindowMsg* pMsg = dynamic_cast< Args_WindowMsg *>( const_cast<IArgs*>( &args ));
	
	UINT nChar = 0;
	if ( NULL !=  pMsg  )
	{
		nChar = pMsg->m_Msg.wParam;
	}
	
	if ( nChar == 0x0d )
	{
		SetFocus(NULL);
	}
	
	return true;
}

bool CCameraCtrlLogic::OnKillFocusEdtContrast( const IArgs& args )
{
	String str;
	UIFACTORYMGR_PTR->GetCaption( m_strEdtContrast, str, m_pWndTree );
	
	SetContrastCmd(str.c_str());
	
	return true;
}

void CCameraCtrlLogic::SetContrastCmd( CString str )
{
	int n = atoi( str );
	
	if ( n > 255 )
	{
		n = 255;
	}
	else if ( n < 0 )
	{
		n = 0;
	}
	
	u16 nRet = COMIFMGRPTR->CamImageParaCmd( emContrast, n );
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "对比度请求发送失败" );
	}
}

bool CCameraCtrlLogic::OnEdtSaturatChange( const IArgs& args )
{
	if ( m_pWndTree == NULL )
	{
		return true;
	}
	
	/*Window* pWnd = UIFACTORYMGR_PTR->GetWindowPtr( m_strEdtSaturat, m_pWndTree );
	if ( pWnd )
	{
		(( CEdit *) pWnd)->SetSel( -1 );
	}*/
	
	Args_WindowMsg* pMsg = dynamic_cast< Args_WindowMsg *>( const_cast<IArgs*>( &args ));
	
	UINT nChar = 0;
	if ( NULL !=  pMsg  )
	{
		nChar = pMsg->m_Msg.wParam;
	}
	
	if ( nChar == 0x0d )
	{
		SetFocus(NULL);
	}
	
	return true;
}

bool CCameraCtrlLogic::OnKillFocusEdtSaturat( const IArgs& args )
{
	String str;
	UIFACTORYMGR_PTR->GetCaption( m_strEdtSaturat, str, m_pWndTree );
	
	SetSaturatCmd(str.c_str());
	
	return true;
}

void CCameraCtrlLogic::SetSaturatCmd( CString str )
{
	int n = atoi( str );
	
	if ( n > 255 )
	{
		n = 255;
	}
	else if ( n < 0 )
	{
		n = 0;
	}
	
	u16 nRet = COMIFMGRPTR->CamImageParaCmd( emSaturat, n );
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "饱和度请求发送失败" );
	}
}

bool CCameraCtrlLogic::OnEdtSharpChange( const IArgs& args )
{
	if ( m_pWndTree == NULL )
	{
		return true;
	}
	
	/*Window* pWnd = UIFACTORYMGR_PTR->GetWindowPtr( m_strEdtSharp, m_pWndTree );
	if ( pWnd )
	{
		(( CEdit *) pWnd)->SetSel( -1 );
	}*/
	
	Args_WindowMsg* pMsg = dynamic_cast< Args_WindowMsg *>( const_cast<IArgs*>( &args ));
	
	UINT nChar = 0;
	if ( NULL !=  pMsg  )
	{
		nChar = pMsg->m_Msg.wParam;
	}
	
	if ( nChar == 0x0d )
	{
		SetFocus(NULL);
	}
	
	return true;
}

bool CCameraCtrlLogic::OnKillFocusEdtSharp( const IArgs& args )
{
	String str;
	UIFACTORYMGR_PTR->GetCaption( m_strEdtSharp, str, m_pWndTree );
	
	SetHueCmd(str.c_str());
	
	return true;
}

void CCameraCtrlLogic::SetHueCmd( CString str )
{
	int n = atoi( str );
	
	if ( n > 255 )
	{
		n = 255;
	}
	else if ( n < 0 )
	{
		n = 0;
	}
	
	u16 nRet = COMIFMGRPTR->CamImageParaCmd( emSharp, n );
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "锐度请求发送失败" );
	}
}

bool CCameraCtrlLogic::OnEdtBrightChange( const IArgs& args )
{
	if ( m_pWndTree == NULL )
	{
		return true;
	}
	
	/*Window* pWnd = UIFACTORYMGR_PTR->GetWindowPtr( m_strEdtBright, m_pWndTree );
	if ( pWnd )
	{
		(( CEdit *) pWnd)->SetSel( -1 );
	}*/
	
	Args_WindowMsg* pMsg = dynamic_cast< Args_WindowMsg *>( const_cast<IArgs*>( &args ));
	
	UINT nChar = 0;
	if ( NULL !=  pMsg  )
	{
		nChar = pMsg->m_Msg.wParam;
	}
	
	if ( nChar == 0x0d )
	{
		SetFocus(NULL);
	}
	
	return true;
}

bool CCameraCtrlLogic::OnKillFocusEdtBright( const IArgs& args )
{
	String str;
	UIFACTORYMGR_PTR->GetCaption( m_strEdtBright, str, m_pWndTree );
	
	SetBrightCmd(str.c_str());
	
	return true;
}

void CCameraCtrlLogic::SetBrightCmd( CString str )
{
	int n = atoi( str );
	
	if ( n > 255 )
	{
		n = 255;
	}
	else if ( n < 0 )
	{
		n = 0;
	}
	
	u16 nRet = COMIFMGRPTR->CamImageParaCmd( emBlight, n );
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "亮度请求发送失败" );
	}
}

bool CCameraCtrlLogic::OnEdtZoomChange( const IArgs& args )
{
	if ( m_pWndTree == NULL )
	{
		return false;
	}
  	Args_WindowMsg* pMsg = dynamic_cast< Args_WindowMsg *>( const_cast<IArgs*>( &args ));
   
	UINT nChar = 0;
	if ( NULL !=  pMsg  )
	{
		nChar = pMsg->m_Msg.wParam;
	}

	Value_WindowCaption valueWindowCaption;
	UIFACTORYMGR_PTR->GetPropertyValue( valueWindowCaption, m_strEdtZoom, m_pWndTree );
	
	CString str;
	str = OnlyFloat( valueWindowCaption.strCaption.c_str() );
	//UIFACTORYMGR_PTR->SetCaption( m_strEdtZoom, (String)str, m_pWndTree );
	
	/*Window* pWnd = UIFACTORYMGR_PTR->GetWindowPtr( m_strEdtZoom, m_pWndTree );
	//DWORD dwPos = (( CEdit *) pWnd)->GetSel() & 0xFFFF;	//获取鼠标当前位置
	if ( pWnd )
	{
		(( CEdit *) pWnd)->SetSel( -1 );		
	}*/

	if ( nChar == 0x0d )
	{
		SetZoomCmd(str);


		SetFocus(NULL);
	}

	return true;
}

bool CCameraCtrlLogic::OnEdtZoomKillFocus( const IArgs& args )
{
	String str;
	UIFACTORYMGR_PTR->GetCaption( m_strEdtZoom, str, m_pWndTree );
		
	SetZoomCmd(str.c_str());

	return true;
}

HRESULT CCameraCtrlLogic::OnCameraImageParaInd( WPARAM wparam, LPARAM lparam )
{
	if ( m_pWndTree == NULL )
	{
		return S_FALSE;
	}
	
    EmTPImagePara emTPImagePara = static_cast<EmTPImagePara>(wparam);
	BOOL bRet = static_cast<BOOL>(lparam);
	switch ( emTPImagePara )
	{
	case emBlight:
		{
			if ( bRet == FALSE )
			{
				WARNMESSAGE( _T("亮度设置失败") );
			}
			break;
		}
	case emContrast:
		{
			if ( bRet == FALSE )
			{
				WARNMESSAGE( _T("对比度设置失败") );
			}
			break;
		}
	case emSharp:
		{
			if ( bRet == FALSE )
			{
				WARNMESSAGE( _T("锐度设置失败") );
			}
			break;
		}
	case emSaturat:
		{
			if ( bRet == FALSE )
			{
				WARNMESSAGE( _T("饱和度设置失败") );
			}
			break;
		}
	default:
		break;
	}
	
	return S_OK;	
}

HRESULT CCameraCtrlLogic::OnCameraBrightInd( WPARAM wparam, LPARAM lparam )
{
	if ( m_pWndTree == NULL )
	{
		return S_FALSE;
	}

	m_dwBright = (u32)(lparam);

	SetBrightValue( m_dwBright );

	return S_OK;	
}

HRESULT CCameraCtrlLogic::OnCameraContrastInd( WPARAM wparam, LPARAM lparam )
{
	if ( m_pWndTree == NULL )
	{
		return S_FALSE;
	}

	m_dwContrast = (u32)(lparam);

	SetContrastValue(m_dwContrast);

	return S_OK;
}

HRESULT CCameraCtrlLogic::OnCameraSharpInd( WPARAM wparam, LPARAM lparam )
{
	if ( m_pWndTree == NULL )
	{
		return S_FALSE;
	}
	
	m_dwSharp = (u32)(lparam);
	
	SetSharpValue(m_dwSharp);
		
	return S_OK;
}

HRESULT CCameraCtrlLogic::OnCameraSaturatInd( WPARAM wparam, LPARAM lparam )
{
	if ( m_pWndTree == NULL )
	{
		return S_FALSE;
	}
	
	m_dwSaturat = (u32)(lparam);
	
	SetSaturatValue(m_dwSaturat);
		
	return S_OK;
}

HRESULT CCameraCtrlLogic::OnCameraPersetSaveInd( WPARAM wparam, LPARAM lparam )
{
	BOOL bRet = static_cast<BOOL>(lparam);
	if ( bRet == FALSE )
	{
		SetCursorPos( 710, 530 );//20130326-解决弹出框后还能点击问题
		WARNMESSAGE( _T("预置位保存设置失败") );
	}
	
	return S_OK;
}

void CCameraCtrlLogic::SetCameraCfg( TTPMoonCamInfo tMoonCameraCfg )
{
	CString strCaption;
	Value_SwitchState valueSwitchState;
	Value_TransparentComboBoxText valueTransparentComboBoxText;

	//摄像机名称
	u8 byCameraIndex = 0;
	MOONLIBDATAMGRPTR->GetCamSel( byCameraIndex );
	switch ( byCameraIndex )
	{
	case 0:
		{
			strCaption = _T("机芯1");
			SetMechVersion( m_tTpMechver1.achMechSWVer, m_tTpMechver1.achMechHWVer );
			m_byCamIndex = 0;
			break;
		}
	case 1:
		{
			strCaption = _T("机芯2");
			SetMechVersion( m_tTpMechver2.achMechSWVer, m_tTpMechver2.achMechHWVer );
			m_byCamIndex = 1;
			break;
		}
	case 2:
		{
			strCaption = _T("机芯3");
			SetMechVersion( m_tTpMechver3.achMechSWVer, m_tTpMechver3.achMechHWVer );
			m_byCamIndex = 2;
			break;
		}
	default:
		break;
	}
	
	SetCamName(strCaption);

	UIFACTORYMGR_PTR->GetPropertyValue( valueTransparentComboBoxText, m_strComboboxCameraStyle, m_pWndTree );
	String strComboText = valueTransparentComboBoxText.strComboText;
	
	if( strComboText == "Sony" )
	{
		SetZoomValue(((float)tMoonCameraCfg.dwZoom)/100);
	}
	else
	{
		//SetZoomValue(((float)tMoonCameraCfg.dwZoom)/1000);
		SetH650ZoomValue( tMoonCameraCfg.dwZoom, tMoonCameraCfg.dwZoomPos );
	}

	SetFocusState( tMoonCameraCfg.emFocusMode );
	
	//开机调用预置位1
	SetPresetValue( tMoonCameraCfg.bIsPreUsed );

	//曝光
	//是否开启自动曝光
	SetAutoExp( tMoonCameraCfg.emExpMode );
	//光圈
	SetApertureValue( tMoonCameraCfg.emAper );
	//快门
	if ( m_bSourceCfg )
	{
		SetShutSpdValue( tMoonCameraCfg.emSOrThShutSpd );	
	}
	else
	{
		SetTwShutterValue( tMoonCameraCfg.emFOrTwShutSpd );
	}

	//增益
	SetExpGainValue( tMoonCameraCfg.emGain );


	//白平衡
	SetAutoWB( tMoonCameraCfg.emWBMode );
	SetRGainValue( tMoonCameraCfg.dwRGain );
	SetBGainValue( tMoonCameraCfg.dwBGain );

	//图片调节
	SetContrastValue( tMoonCameraCfg.dwContrast );
	SetSaturatValue( tMoonCameraCfg.dwSaturat );
	SetSharpValue( tMoonCameraCfg.dwSharp );
	SetBrightValue( tMoonCameraCfg.dwBright );

	//降噪
 	SetNRValue( tMoonCameraCfg.emReduNoise );

	//2D降噪
	Set2DNRValue(tMoonCameraCfg.em2DNoiseLevle);

	//3D降噪
	Set3DNRValue(tMoonCameraCfg.em3DNoiseLevle);

	SetLightPensationValue( tMoonCameraCfg.bIsBLCSwitch );

	SetGammaValue( tMoonCameraCfg.emGamma );

	//梯形校正
/*	SetKeyStoneAdjust( tMoonCameraCfg.bIsCorrect );
	SetAdjustRangeValue( tMoonCameraCfg.dwCorrectLevel );
	SetHoriStretchValue( tMoonCameraCfg.dwStretchRegion );

*/
	return;
}

void CCameraCtrlLogic::GetApertureValue(EmTPAperture &emAper)
{
	if ( m_pWndTree == NULL )
	{
		return;
	}

	Value_TransparentComboBoxText valueTransparentComboBoxText;
	UIFACTORYMGR_PTR->GetPropertyValue( valueTransparentComboBoxText, m_strComboboxAperture, m_pWndTree );

	String strComboText = valueTransparentComboBoxText.strComboText;
	if ( strComboText == "Close" )
	{
		emAper = em_Aperture_OFF;
	}
	else if ( strComboText == "F9.6" )
	{
		emAper = em_Aperture_F9_6;
	}
	else if ( strComboText == "F8")
	{
		emAper = em_Aperture_F8;
	}
	else if ( strComboText == "F6.8")
	{
		emAper = em_Aperture_F6_8;
	}
	else if ( strComboText == "F5.6")
	{
		emAper = em_Aperture_F5_6;
	}
	else if ( strComboText == "F4.8")
	{
		emAper = em_Aperture_F4_8;
	}
	else if ( strComboText == "F4")
	{
		emAper = em_Aperture_F4;
	}
	else if ( strComboText == "F3.4")
	{
		emAper = em_Aperture_F3_4;
	}
	else if ( strComboText == "F2.8")
	{
		emAper = em_Aperture_F2_8;
	}
	else if ( strComboText == "F2.4")
	{
		emAper = em_Aperture_F2_4;
	}
	else if ( strComboText == "F2")
	{
		emAper = em_Aperture_F2;
	}
	else if ( strComboText == "F1.8")
	{
		emAper = em_Aperture_F1_8;
	}
	

}

void CCameraCtrlLogic::SetApertureValue( EmTPAperture emAper )
{
	Value_TransparentComboBoxText valueTransparentComboBoxText;	
	switch( emAper )
	{
		case em_Aperture_OFF:
			{
				valueTransparentComboBoxText.strComboText = "Close"; 
				break;
			}
		case em_Aperture_F9_6:
			{
				valueTransparentComboBoxText.strComboText = "F9.6"; 
				break;
			}
		case em_Aperture_F8:
			{
				valueTransparentComboBoxText.strComboText = "F8"; 
				break;
			}
		case em_Aperture_F6_8:
			{
				valueTransparentComboBoxText.strComboText = "F6.8"; 
				break;
			}
		case em_Aperture_F5_6:
			{
				valueTransparentComboBoxText.strComboText = "F5.6"; 
				break;
			}
		case em_Aperture_F4_8:
			{
				valueTransparentComboBoxText.strComboText = "F4.8"; 
				break;
			}
		case em_Aperture_F4:
			{
				valueTransparentComboBoxText.strComboText = "F4"; 
				break;
			}
		case em_Aperture_F3_4:
			{
				valueTransparentComboBoxText.strComboText = "F3.4"; 
				break;
			}
		case em_Aperture_F2_8:
			{
				valueTransparentComboBoxText.strComboText = "F2.8"; 
				break;
			}
		case em_Aperture_F2_4:
			{
				valueTransparentComboBoxText.strComboText = "F2.4"; 
				break;
			}
		case em_Aperture_F2:
			{
				valueTransparentComboBoxText.strComboText = "F2"; 
				break;
			}
		case em_Aperture_F1_8:
			{
				valueTransparentComboBoxText.strComboText = "F1.8"; 
				break;
			}
		default:
			break;

	}
	UIFACTORYMGR_PTR->SetPropertyValue( valueTransparentComboBoxText, m_strComboboxAperture, m_pWndTree );
}

void CCameraCtrlLogic::GetShutSpdValue( EmTPSOrThShutter &emShutSpd )
{
	if ( m_pWndTree == NULL )
	{
		return;
	}
	
	Value_TransparentComboBoxText valueTransparentComboBoxText;
	UIFACTORYMGR_PTR->GetPropertyValue( valueTransparentComboBoxText, m_strComboboxShut, m_pWndTree );
	
	String strComboText = valueTransparentComboBoxText.strComboText;
	if ( strComboText == "1/1" )
	{
		emShutSpd = em_Shutter_1Sp;
	}
	else if ( strComboText == "1/2" )
	{
		emShutSpd = em_Shutter_2Sp;
	}
	else if ( strComboText == "1/4" )
	{
		emShutSpd = em_Shutter_4Sp;
	}
	else if ( strComboText == "1/8" )
	{
		emShutSpd = em_Shutter_8Sp;
	}
	else if ( strComboText == "1/15" )
	{
		emShutSpd = em_Shutter_15Sp;
	}
	else if ( strComboText == "1/30" )
	{
		emShutSpd = em_Shutter_30Sp;
	}
	else if ( strComboText == "1/60" )
	{
		emShutSpd = em_Shutter_60Sp;
	}
	else if ( strComboText == "1/90" )
	{
		emShutSpd = em_Shutter_90Sp;
	}
	else if ( strComboText == "1/100" )
	{
		emShutSpd = em_Shutter_100Sp;
	}
	else if ( strComboText == "1/125" )
	{
		emShutSpd = em_Shutter_125Sp;
	}
	else if ( strComboText == "1/180" )
	{
		emShutSpd = em_Shutter_180Sp;
	}
	else if ( strComboText == "1/250" )
	{
		emShutSpd = em_Shutter_250Sp;
	}
	else if ( strComboText == "1/350" )
	{
		emShutSpd = em_Shutter_350Sp;
	}
	else if ( strComboText == "1/500" )
	{
		emShutSpd = em_Shutter_500Sp;
	}
	else if ( strComboText == "1/725" )
	{
		emShutSpd = em_Shutter_725Sp;
	}
	else if ( strComboText == "1/1000" )
	{
		emShutSpd = em_Shutter_1000Sp;
	}
	else if ( strComboText == "1/1500" )
	{
		emShutSpd = em_Shutter_1500Sp;
	}
	else if ( strComboText == "1/2000" )
	{
		emShutSpd = em_Shutter_2000Sp;
	}
	else if ( strComboText == "1/3000" )
	{
		emShutSpd = em_Shutter_3000Sp;
	}
	else if ( strComboText == "1/4000" )
	{
		emShutSpd = em_Shutter_4000Sp;
	}
	else if ( strComboText == "1/6000" )
	{
		emShutSpd = em_Shutter_6000Sp;
	}
	else if ( strComboText == "1/10000" )
	{
		emShutSpd = em_Shutter_10000Sp;
	}
}

void CCameraCtrlLogic::GetTwShutterValue( EmTPFOrTwShutter &emTwShutter)
{
	if ( m_pWndTree == NULL )
	{
		return;
	}
	
	Value_TransparentComboBoxText valueTransparentComboBoxText;
	UIFACTORYMGR_PTR->GetPropertyValue( valueTransparentComboBoxText, m_strComboboxShut, m_pWndTree );
	
	String strComboText = valueTransparentComboBoxText.strComboText;
	if ( strComboText == "1/1" )
	{
		emTwShutter = em_Shutter_1Spd;
	}
	else if ( strComboText == "1/2" )
	{
		emTwShutter = em_Shutter_2Spd;
	}
	else if ( strComboText == "1/3" )
	{
		emTwShutter = em_Shutter_3Spd;
	}
	else if ( strComboText == "1/6" )
	{
		emTwShutter = em_Shutter_6Spd;
	}
	else if ( strComboText == "1/12" )
	{
		emTwShutter = em_Shutter_12Spd;
	}
	else if ( strComboText == "1/25" )
	{
		emTwShutter = em_Shutter_25Spd;
	}
	else if ( strComboText == "1/50" )
	{
		emTwShutter = em_Shutter_50Spd;
	}
	else if ( strComboText == "1/75" )
	{
		emTwShutter = em_Shutter_75Spd;
	}
	else if ( strComboText == "1/100" )
	{
		emTwShutter = em_Shutter_100Spd;
	}
	else if ( strComboText == "1/120" )
	{
		emTwShutter = em_Shutter_120Spd;
	}
	else if ( strComboText == "1/150" )
	{
		emTwShutter = em_Shutter_150Spd;
	}
	else if ( strComboText == "1/215" )
	{
		emTwShutter = em_Shutter_215Spd;
	}
	else if ( strComboText == "1/300" )
	{
		emTwShutter = em_Shutter_300Spd;
	}
	else if ( strComboText == "1/425" )
	{
		emTwShutter = em_Shutter_425Spd;
	}
	else if ( strComboText == "1/600" )
	{
		emTwShutter = em_Shutter_600Spd;
	}
	else if ( strComboText == "1/1000" )
	{
		emTwShutter = em_Shutter_1000Spd;
	}
	else if ( strComboText == "1/1250" )
	{
		emTwShutter = em_Shutter_1250Spd;
	}
	else if ( strComboText == "1/1750" )
	{
		emTwShutter = em_Shutter_1750Spd;
	}
	else if ( strComboText == "1/2500" )
	{
		emTwShutter = em_Shutter_2500Spd;
	}
	else if ( strComboText == "1/3500" )
	{
		emTwShutter = em_Shutter_3500Spd;
	}
	else if ( strComboText == "1/6000" )
	{
		emTwShutter = em_Shutter_6000Spd;
	}
	else if ( strComboText == "1/10000" )
	{
		emTwShutter = em_Shutter_10000Spd;
	}
}

void CCameraCtrlLogic::SetShutSpdValue( EmTPSOrThShutter emShutSpd )
{
	Value_TransparentComboBoxText valueTransparentComboBoxText;

	switch ( emShutSpd )
	{
	case em_Shutter_1Sp:
		{
			valueTransparentComboBoxText.strComboText = "1/1"; 
			break;
		}
	case em_Shutter_2Sp:
		{
			valueTransparentComboBoxText.strComboText = "1/2"; 
			break;
		}
	case em_Shutter_4Sp:
		{
			valueTransparentComboBoxText.strComboText = "1/4"; 
			break;
		}
	case em_Shutter_8Sp:
		{
			valueTransparentComboBoxText.strComboText = "1/8"; 
			break;
		}
	case em_Shutter_15Sp:
		{
			valueTransparentComboBoxText.strComboText = "1/15"; 
			break;
		}
	case em_Shutter_30Sp:
		{
			valueTransparentComboBoxText.strComboText = "1/30"; 
			break;
		}
	case em_Shutter_60Sp:
		{
			valueTransparentComboBoxText.strComboText = "1/60"; 
			break;
		}
	case em_Shutter_90Sp:
		{
			valueTransparentComboBoxText.strComboText = "1/90"; 
			break;
		}
	case em_Shutter_100Sp:
		{
			valueTransparentComboBoxText.strComboText = "1/100"; 
			break;
		}
	case em_Shutter_125Sp:
		{
			valueTransparentComboBoxText.strComboText = "1/125"; 
			break;
		}
	case em_Shutter_180Sp:
		{
			valueTransparentComboBoxText.strComboText = "1/180"; 
			break;
		}
	case em_Shutter_250Sp:
		{
			valueTransparentComboBoxText.strComboText = "1/250"; 
			break;
		}
	case em_Shutter_350Sp:
		{
			valueTransparentComboBoxText.strComboText = "1/350"; 
			break;
		}
	case em_Shutter_500Sp:
		{
			valueTransparentComboBoxText.strComboText = "1/500"; 
			break;
		}
	case em_Shutter_725Sp:
		{
			valueTransparentComboBoxText.strComboText = "1/725"; 
			break;
		}
	case em_Shutter_1000Sp:
		{
			valueTransparentComboBoxText.strComboText = "1/1000"; 
			break;
		}
	case em_Shutter_1500Sp:
		{
			valueTransparentComboBoxText.strComboText = "1/1500"; 
			break;
		}
	case em_Shutter_2000Sp:
		{
			valueTransparentComboBoxText.strComboText = "1/2000"; 
			break;
		}
	case em_Shutter_3000Sp:
		{
			valueTransparentComboBoxText.strComboText = "1/3000"; 
			break;
		}
	case em_Shutter_4000Sp:
		{
			valueTransparentComboBoxText.strComboText = "1/4000"; 
			break;
		}
	case em_Shutter_6000Sp:
		{
			valueTransparentComboBoxText.strComboText = "1/6000"; 
			break;
		}
	case em_Shutter_10000Sp:
		{
			valueTransparentComboBoxText.strComboText = "1/10000"; 
			break;
		}
	default:
		break;
	}

	UIFACTORYMGR_PTR->SetPropertyValue( valueTransparentComboBoxText, m_strComboboxShut, m_pWndTree );
}

void CCameraCtrlLogic::SetTwShutterValue( EmTPFOrTwShutter emTwShutter )
{
	Value_TransparentComboBoxText valueTransparentComboBoxText;

	switch ( emTwShutter )
	{
	case em_Shutter_1Spd:
		{
			valueTransparentComboBoxText.strComboText = "1/1"; 
			break;
		}
	case em_Shutter_2Spd:
		{
			valueTransparentComboBoxText.strComboText = "1/2"; 
			break;
		}
	case em_Shutter_3Spd:
		{
			valueTransparentComboBoxText.strComboText = "1/3"; 
			break;
		}
	case em_Shutter_6Spd:
		{
			valueTransparentComboBoxText.strComboText = "1/6"; 
			break;
		}
	case em_Shutter_12Spd:
		{
			valueTransparentComboBoxText.strComboText = "1/12"; 
			break;
		}
	case em_Shutter_25Spd:
		{
			valueTransparentComboBoxText.strComboText = "1/25"; 
			break;
		}
	case em_Shutter_50Spd:
		{
			valueTransparentComboBoxText.strComboText = "1/50"; 
			break;
		}
	case em_Shutter_75Spd:
		{
			valueTransparentComboBoxText.strComboText = "1/75"; 
			break;
		}
	case em_Shutter_100Spd:
		{
			valueTransparentComboBoxText.strComboText = "1/100"; 
			break;
		}
	case em_Shutter_120Spd:
		{
			valueTransparentComboBoxText.strComboText = "1/120"; 
			break;
		}
	case em_Shutter_150Spd:
		{
			valueTransparentComboBoxText.strComboText = "1/150"; 
			break;
		}
	case em_Shutter_215Spd:
		{
			valueTransparentComboBoxText.strComboText = "1/215"; 
			break;
		}
	case em_Shutter_300Spd:
		{
			valueTransparentComboBoxText.strComboText = "1/300"; 
			break;
		}
	case em_Shutter_425Spd:
		{
			valueTransparentComboBoxText.strComboText = "1/425"; 
			break;
		}
	case em_Shutter_600Spd:
		{
			valueTransparentComboBoxText.strComboText = "1/600"; 
			break;
		}
	case em_Shutter_1000Spd:
		{
			valueTransparentComboBoxText.strComboText = "1/1000"; 
			break;
		}
	case em_Shutter_1250Spd:
		{
			valueTransparentComboBoxText.strComboText = "1/1250"; 
			break;
		}
	case em_Shutter_1750Spd:
		{
			valueTransparentComboBoxText.strComboText = "1/1750"; 
			break;
		}
	case em_Shutter_2500Spd:
		{
			valueTransparentComboBoxText.strComboText = "1/2500"; 
			break;
		}
	case em_Shutter_3500Spd:
		{
			valueTransparentComboBoxText.strComboText = "1/3500"; 
			break;
		}
	case em_Shutter_6000Spd:
		{
			valueTransparentComboBoxText.strComboText = "1/6000"; 
			break;
		}
	case em_Shutter_10000Spd:
		{
			valueTransparentComboBoxText.strComboText = "1/10000"; 
			break;
		}
	default:
		break;
	}

	UIFACTORYMGR_PTR->SetPropertyValue( valueTransparentComboBoxText, m_strComboboxShut, m_pWndTree );
}

void CCameraCtrlLogic::GetExpGainValue( EmTPExpGain &emGain )
{
	if ( m_pWndTree == NULL )
	{
		return;
	}

	Value_TransparentComboBoxText valueTransparentComboBoxText;
	UIFACTORYMGR_PTR->GetPropertyValue( valueTransparentComboBoxText, m_strComboboxExposureGain, m_pWndTree );
	
	
	String strComboText = valueTransparentComboBoxText.strComboText;
	if ( strComboText == "-10.5dB" )
	{
		emGain = em_Gain_Nega10_5dB ;
	}
	else if ( strComboText == "-9dB" )
	{
		emGain = em_Gain_Nega9dB;
	}
	else if ( strComboText == "-7.5dB" )
	{
		emGain = em_Gain_Nega7_5dB;
	}
	else if ( strComboText == "-6dB" )
	{
		emGain = em_Gain_Nega6dB;
	}
	else if ( strComboText == "-4.5dB" )
	{
		emGain = em_Gain_Nega4_5dB;
	}
	else if ( strComboText == "-3dB" )
	{
		emGain = em_Gain_Nega3dB;
	}
	else if ( strComboText == "-1.5dB" )
	{
		emGain = em_Gain_Nega1_5dB;
	}
	else if ( strComboText == "0dB" )
	{
		emGain = em_Gain_ZerodB;
	}
	else if ( strComboText == "1.5dB" )
	{
		emGain = em_Gain_Posi1_5dB;
	}
	else if ( strComboText == "3dB" )
	{
		emGain = em_Gain_Posi3dB;
	}
	else if ( strComboText == "4.5dB" )
	{
		emGain = em_Gain_Posi4_5dB;
	}
	else if ( strComboText == "6dB" )
	{
		emGain = em_Gain_Posi6dB;
	}
	else if ( strComboText == "7.5dB" )
	{
		emGain = em_Gain_Posi7_5dB;
	}
	else if ( strComboText == "9dB" )
	{
		emGain = em_Gain_Posi9dB;
	}
	else if ( strComboText == "10.5dB" )
	{
		emGain = em_Gain_Posi10_5dB;
	}

};

void CCameraCtrlLogic::SetExpGainValue( EmTPExpGain emExpGain )
{
	Value_TransparentComboBoxText valueTransparentComboBoxText;

	switch ( emExpGain )
	{
	case em_Gain_Nega10_5dB:
		{
			valueTransparentComboBoxText.strComboText = "-10.5dB";
			break;
		}
	case em_Gain_Nega9dB:
		{
			valueTransparentComboBoxText.strComboText = "-9dB";
			break;
		}
	case em_Gain_Nega7_5dB:
		{
			valueTransparentComboBoxText.strComboText = "-7.5dB";
			break;
		}
	case em_Gain_Nega6dB:
		{
			valueTransparentComboBoxText.strComboText = "-6dB";
			break;
		}
	case em_Gain_Nega4_5dB:
		{
			valueTransparentComboBoxText.strComboText = "-4.5dB";
			break;
		}
	case em_Gain_Nega3dB:
		{
			valueTransparentComboBoxText.strComboText = "-3dB";
			break;
		}
	case em_Gain_Nega1_5dB:
		{
			valueTransparentComboBoxText.strComboText = "-1.5dB";
			break;
		}
	case em_Gain_ZerodB:
		{
			valueTransparentComboBoxText.strComboText = "0dB";
			break;
		}
	case em_Gain_Posi1_5dB:
		{
			valueTransparentComboBoxText.strComboText = "1.5dB";
			break;
		}
	case em_Gain_Posi3dB:
		{
			valueTransparentComboBoxText.strComboText = "3dB";
			break;
		}
	case em_Gain_Posi4_5dB:
		{
			valueTransparentComboBoxText.strComboText = "4.5dB";
			break;
		}
	case em_Gain_Posi6dB:
		{
			valueTransparentComboBoxText.strComboText = "6dB";
			break;
		}
	case em_Gain_Posi7_5dB:
		{
			valueTransparentComboBoxText.strComboText = "7.5dB";
			break;
		}
	case em_Gain_Posi9dB:
		{
			valueTransparentComboBoxText.strComboText = "9dB";
			break;
		}
	case em_Gain_Posi10_5dB:
		{
			valueTransparentComboBoxText.strComboText = "10.5dB";
			break;
		}
	default:
		break;
	}

	UIFACTORYMGR_PTR->SetPropertyValue( valueTransparentComboBoxText, m_strComboboxExposureGain, m_pWndTree );
}

void CCameraCtrlLogic::GetNRValue( EmTPFpgaReduNoise &emTPReduNoise )
{
	String strLevel;
	UIFACTORYMGR_PTR->GetComboText( "ComboboxNR", strLevel, m_pWndTree );
	if ( strLevel == "低" )
	{
		emTPReduNoise = emFpgaLow;
	} 
	else if ( strLevel == "中" )
	{
		emTPReduNoise = emFpgaMid;
	}
	else if ( strLevel == "高" )
	{
		emTPReduNoise = emFpgaHight;
	}
// 	else if ( strLevel == "level 4" )
// 	{
// 		emTPReduNoise = emLevelFourth;
// 	}
// 	else if ( strLevel == "level 5" )
// 	{
// 		emTPReduNoise = emLeVelFifth;
// 	}	
}

void CCameraCtrlLogic::Get2DNRValue(EmTPReduNoise &emTPReduNoise)
{
	String strLevel;
	UIFACTORYMGR_PTR->GetComboText( "Combobox2DNR", strLevel, m_pWndTree );

	if ( strLevel == "level 1" )
	{
		emTPReduNoise = emLevelFist;
	} 
	else if ( strLevel == "level 2" )
	{
		emTPReduNoise = emLevelSecond;
	}
	else if ( strLevel == "level 3" )
	{
		emTPReduNoise = emLevelThird;
	}
	else if ( strLevel == "level 4" )
	{
		emTPReduNoise = emLevelFourth;
	}
	else if ( strLevel == "level 5" )
	{
		emTPReduNoise = emLeVelFifth;
 	}
}


void CCameraCtrlLogic::Get3DNRValue(EmTPReduNoise &emTPReduNoise)
{
	String strLevel;
	UIFACTORYMGR_PTR->GetComboText( "Combobox3DNR", strLevel, m_pWndTree );
	
	if ( strLevel == "level 1" )
	{
		emTPReduNoise = emLevelFist;
	} 
	else if ( strLevel == "level 2" )
	{
		emTPReduNoise = emLevelSecond;
	}
	else if ( strLevel == "level 3" )
	{
		emTPReduNoise = emLevelThird;
	}
	else if ( strLevel == "level 4" )
	{
		emTPReduNoise = emLevelFourth;
	}
	else if ( strLevel == "level 5" )
	{
		emTPReduNoise = emLeVelFifth;
 	}
}

void CCameraCtrlLogic::SetNRValue( EmTPFpgaReduNoise emTPReduNoise )
{
	String strLevel;
	Value_SwitchState valueSwitchState;
	if ( emFpgaLow == emTPReduNoise)
	{
		strLevel = "低" ;
	}
	else if ( emFpgaMid == emTPReduNoise )
	{
		strLevel = "中";
	}
	else if ( emFpgaHight == emTPReduNoise )
	{
		strLevel = "高";
	}
	else if ( emFpgaClose == emTPReduNoise)
	{
		valueSwitchState.bState = FALSE;
		strLevel = "中";
		UIFACTORYMGR_PTR->SetPropertyValue( valueSwitchState, m_strBtnSwitchNR, m_pWndTree );
		UIFACTORYMGR_PTR->SetComboText( "ComboboxNR", strLevel, m_pWndTree );
		UIFACTORYMGR_PTR->LoadScheme("SchAutoNR", m_pWndTree);
		return;
	}
	
	valueSwitchState.bState = TRUE;
	UIFACTORYMGR_PTR->SetPropertyValue( valueSwitchState, m_strBtnSwitchNR, m_pWndTree );
	UIFACTORYMGR_PTR->SetComboText( "ComboboxNR", strLevel, m_pWndTree );
	UIFACTORYMGR_PTR->LoadScheme("SchManuelNR", m_pWndTree);
}


void CCameraCtrlLogic::Set2DNRValue(EmTPReduNoise emTPReduNoise)
{
	String strLevel;
	Value_SwitchState valueSwitchState;
	if ( emLevelFist == emTPReduNoise)
	{
		strLevel = "level 1" ;
	}
	else if ( emLevelSecond == emTPReduNoise )
	{
		strLevel = "level 2";
	}
	else if ( emLevelThird == emTPReduNoise )
	{
		strLevel = "level 3";
	}
	else if ( emLevelFourth == emTPReduNoise )
	{
		strLevel = "level 4";
	}
	else if ( emLeVelFifth == emTPReduNoise )
	{
		strLevel = "level 5";
	}
	else if ( emClose == emTPReduNoise)
	{
		valueSwitchState.bState = FALSE;
		strLevel = "level 1";
		UIFACTORYMGR_PTR->SetPropertyValue( valueSwitchState, m_strBtnSwitch2DNR, m_pWndTree );
		UIFACTORYMGR_PTR->SetComboText( "Combobox2DNR", strLevel, m_pWndTree );
		UIFACTORYMGR_PTR->LoadScheme("SchAuto2DNR", m_pWndTree);
		return;
	}
	
	valueSwitchState.bState = TRUE;
	UIFACTORYMGR_PTR->SetPropertyValue( valueSwitchState, m_strBtnSwitch2DNR, m_pWndTree );
	UIFACTORYMGR_PTR->SetComboText( "Combobox2DNR", strLevel, m_pWndTree );
	UIFACTORYMGR_PTR->LoadScheme("SchManuel2DNR", m_pWndTree);
}

void CCameraCtrlLogic::Set3DNRValue(EmTPReduNoise emTPReduNoise)
{
	String strLevel;
	Value_SwitchState valueSwitchState;
	if ( emLevelFist == emTPReduNoise)
	{
		strLevel = "level 1" ;
	}
	else if ( emLevelSecond == emTPReduNoise )
	{
		strLevel = "level 2";
	}
	else if ( emLevelThird == emTPReduNoise )
	{
		strLevel = "level 3";
	}
	else if ( emLevelFourth == emTPReduNoise )
	{
		strLevel = "level 4";
	}
	else if ( emLeVelFifth == emTPReduNoise )
	{
		strLevel = "level 5";
	}
	else if ( emClose == emTPReduNoise)
	{
		valueSwitchState.bState = FALSE;
		strLevel = "level 1";
		UIFACTORYMGR_PTR->SetPropertyValue( valueSwitchState, m_strBtnSwitch3DNR, m_pWndTree );
		UIFACTORYMGR_PTR->SetComboText( "Combobox3DNR", strLevel, m_pWndTree );
		UIFACTORYMGR_PTR->LoadScheme("SchAuto3DNR", m_pWndTree);
		return;
	}
	
	valueSwitchState.bState = TRUE;
	UIFACTORYMGR_PTR->SetPropertyValue( valueSwitchState, m_strBtnSwitch3DNR, m_pWndTree );
	UIFACTORYMGR_PTR->SetComboText( "Combobox3DNR", strLevel, m_pWndTree );
	UIFACTORYMGR_PTR->LoadScheme("SchManuel3DNR", m_pWndTree);
}

void CCameraCtrlLogic::SetAutoWB( EmTPMOOMMode emWBMode )
{
	if ( emWBMode == emWBAuto )
	{
		UIFACTORYMGR_PTR->LoadScheme( "SchAutoWB", m_pWndTree );
	}
	else if ( emWBMode == emWBManual )
	{
		UIFACTORYMGR_PTR->LoadScheme( "SchManuelWB", m_pWndTree );
	}
	else
	{
		
	}
}

void CCameraCtrlLogic::SetAutoExp( EmTPMOOMMode emExpMode )
{
	if ( emExpMode == emExpAuto )
	{
		UIFACTORYMGR_PTR->LoadScheme( "SchAutoExposure", m_pWndTree );
	}
	else
	{
		UIFACTORYMGR_PTR->LoadScheme( "SchManuelExposure", m_pWndTree );
	}
}

void CCameraCtrlLogic::SetCamName( CString strCaption )
{
	UIFACTORYMGR_PTR->SetComboText( m_strComboboxCamera, (LPCTSTR)strCaption, m_pWndTree );
}

void CCameraCtrlLogic::SetGammaName(CString strCaption)
{
	UIFACTORYMGR_PTR->SetComboText( m_strComboboxGamma, (LPCTSTR)strCaption, m_pWndTree );
}

void CCameraCtrlLogic::SetCamStyleName(CString strCaption)
{
	UIFACTORYMGR_PTR->SetComboText( m_strComboboxCameraStyle, (LPCTSTR)strCaption, m_pWndTree );
}

void CCameraCtrlLogic::SetPresetValue( BOOL bUsed )
{
	Value_SwitchState valueSwitchState;
	valueSwitchState.bState = bUsed;
	m_bIsOrderPos = bUsed;
	UIFACTORYMGR_PTR->SetPropertyValue( valueSwitchState, m_strBtnSwitchPersetMove, m_pWndTree );
}

void CCameraCtrlLogic::SetAptValue( u8 byApt )
{
	Value_CSliderCtrlPos valueCSliderCtrlPos;
	valueCSliderCtrlPos.nPos = byApt;
	UIFACTORYMGR_PTR->SetPropertyValue( valueCSliderCtrlPos, m_strSliderAperture, m_pWndTree );
	
	CString strCaption;
	strCaption.Format( "%d", byApt );
	UIFACTORYMGR_PTR->SetCaption( m_strEdtAperture, (LPCTSTR)strCaption, m_pWndTree );

	Window* pWnd = UIFACTORYMGR_PTR->GetWindowPtr( m_strEdtAperture, m_pWndTree );
	if ( pWnd )
	{
		(( CEdit *) pWnd)->SetSel( -1 );
	}
}

void CCameraCtrlLogic::SetRGainValue( u32 dwRGain )
{
	Value_CSliderCtrlPos valueCSliderCtrlPos;
	valueCSliderCtrlPos.nPos = dwRGain;
	UIFACTORYMGR_PTR->SetPropertyValue( valueCSliderCtrlPos, m_strSliderRGain, m_pWndTree );
	
	CString strCaption;
	strCaption.Format( "%d", dwRGain );
	Value_WindowCaption valueWindowCaption;
	valueWindowCaption.strCaption = strCaption;
	UIFACTORYMGR_PTR->SetPropertyValue( valueWindowCaption, m_strEdtRGain, m_pWndTree );

	Window* pWnd = UIFACTORYMGR_PTR->GetWindowPtr( m_strEdtRGain, m_pWndTree );
	if ( pWnd )
	{
		(( CEdit *) pWnd)->SetSel( -1 );
	}
}

void CCameraCtrlLogic::SetBGainValue( u32 dwBGain )
{
	Value_CSliderCtrlPos valueCSliderCtrlPos;
	valueCSliderCtrlPos.nPos = dwBGain;
	UIFACTORYMGR_PTR->SetPropertyValue( valueCSliderCtrlPos, m_strSliderBGain, m_pWndTree );
	
	CString strCaption;
	strCaption.Format( "%d", dwBGain );
	Value_WindowCaption valueWindowCaption;
	valueWindowCaption.strCaption = strCaption;
	UIFACTORYMGR_PTR->SetPropertyValue( valueWindowCaption, m_strEdtBGain, m_pWndTree );

	Window* pWnd = UIFACTORYMGR_PTR->GetWindowPtr( m_strEdtBGain, m_pWndTree );
	if ( pWnd )
	{
		(( CEdit *) pWnd)->SetSel( -1 );
	}
}

void CCameraCtrlLogic::SetContrastValue( u32 dwContrast )
{
	Value_CSliderCtrlPos valueCSliderCtrlPos;
	valueCSliderCtrlPos.nPos = dwContrast;
	UIFACTORYMGR_PTR->SetPropertyValue( valueCSliderCtrlPos, m_strSliderContrast, m_pWndTree );
	
	CString strCaption;
	strCaption.Format( "%d", dwContrast );
	Value_WindowCaption valueWindowCaption;
	valueWindowCaption.strCaption = strCaption;
	UIFACTORYMGR_PTR->SetPropertyValue( valueWindowCaption, m_strEdtContrast, m_pWndTree );

	Window* pWnd = UIFACTORYMGR_PTR->GetWindowPtr( m_strEdtContrast, m_pWndTree );
	if ( pWnd )
	{
		(( CEdit *) pWnd)->SetSel( -1 );
	}
}

void CCameraCtrlLogic::SetSaturatValue( u32 dwSaturat )
{
	Value_CSliderCtrlPos valueCSliderCtrlPos;
	valueCSliderCtrlPos.nPos = dwSaturat;
	UIFACTORYMGR_PTR->SetPropertyValue( valueCSliderCtrlPos, m_strSliderSaturat, m_pWndTree );
	
	CString strCaption;
	strCaption.Format( "%d", dwSaturat );
	Value_WindowCaption valueWindowCaption;
	valueWindowCaption.strCaption = strCaption;
	UIFACTORYMGR_PTR->SetPropertyValue( valueWindowCaption, m_strEdtSaturat, m_pWndTree );

	Window* pWnd = UIFACTORYMGR_PTR->GetWindowPtr( m_strEdtSaturat, m_pWndTree );
	if ( pWnd )
	{
		(( CEdit *) pWnd)->SetSel( -1 );
	}
}

void CCameraCtrlLogic::SetSharpValue( u32 dwSharp )
{
	Value_CSliderCtrlPos valueCSliderCtrlPos;
	valueCSliderCtrlPos.nPos = dwSharp;
	UIFACTORYMGR_PTR->SetPropertyValue( valueCSliderCtrlPos, m_strSliderSharp, m_pWndTree );
	
	CString strCaption;
	strCaption.Format( "%d", dwSharp );
	Value_WindowCaption valueWindowCaption;
	valueWindowCaption.strCaption = strCaption;
	//UIFACTORYMGR_PTR->SetPropertyValue( valueWindowCaption, m_strEdtHue, m_pWndTree );
	UIFACTORYMGR_PTR->SetCaption( m_strEdtSharp, (String)strCaption, m_pWndTree );

	Window* pWnd = UIFACTORYMGR_PTR->GetWindowPtr( m_strEdtSharp, m_pWndTree );
	if ( pWnd )
	{
		(( CEdit *) pWnd)->SetSel( -1 );
	}
}

void CCameraCtrlLogic::SetBrightValue( u32 dwBright )
{
	Value_CSliderCtrlPos valueCSliderCtrlPos;
	valueCSliderCtrlPos.nPos = dwBright;
	UIFACTORYMGR_PTR->SetPropertyValue( valueCSliderCtrlPos, m_strSliderBright, m_pWndTree );
	
	CString strCaption;
	strCaption.Format( "%d", dwBright );
	Value_WindowCaption valueWindowCaption;
	valueWindowCaption.strCaption = strCaption;
	UIFACTORYMGR_PTR->SetPropertyValue( valueWindowCaption, m_strEdtBright, m_pWndTree );

	Window* pWnd = UIFACTORYMGR_PTR->GetWindowPtr( m_strEdtBright, m_pWndTree );
	if ( pWnd )
	{
		(( CEdit *) pWnd)->SetSel( -1 );
	}
}

float CCameraCtrlLogic::StringToFloatThree( CString str )
{
	float f = 0;
	f = atof((LPCTSTR)str);
	char strRet[10] = {0};
	sprintf(strRet,"%.2f",f);
	f = atof(strRet);
	return f;
}

CString CCameraCtrlLogic::OnlyFloat( CString str )
{
	// 只允许输数据
	int nStringLength = str.GetLength();
	int nDotCount = 0;
	// 点字符不能多于1个
	int nIndex = 0;
	for ( ; nIndex < nStringLength; nIndex++ )
	{
		if ( str[ nIndex ] == '.' )
		{
			nDotCount++;
			if ( nDotCount > 1 )
			{
				CString csTmp;
				csTmp = str.Left( nIndex );
				csTmp += str.Right( str.GetLength() - nIndex - 1 );
				//csRadius = csRadius.Left( nIndex + 1 ) + csRadius.Right( nStringLength - ( nIndex + 1 ) - 1 );
				//GetDlgItem( IDC_EDIT_AREA_S )->SetWindowText( csTmp );
				return csTmp;
			}
		}
	}
	
	// 不允许输入数字和点以外的字符
	nIndex = 0;
	for ( ; nIndex < nStringLength; nIndex++ )
	{
		if ( str[ nIndex ] != '.' && ( str[ nIndex ] > '9' || str[ nIndex ] < '0' ) )
		{
			str = str.Left( nIndex ) + str.Right( str.GetLength() - nIndex - 1 );
			//GetDlgItem( IDC_EDIT_AREA_S )->SetWindowText( csTmp );
			return str;
		}
	}

	return str;
}

HRESULT CCameraCtrlLogic::OnSetCameraZoomInd( WPARAM wparam, LPARAM lparam )
{
	if ( m_pWndTree == NULL )
	{
		return S_FALSE;
	}
	
	u32 dwZoom;
	u32 dwZoomPos;
	MOONLIBDATAMGRPTR->GetCamZoom( dwZoom );
	MOONLIBDATAMGRPTR->GetExtCamZoom( dwZoomPos );
	BOOL bRet = static_cast<BOOL>(lparam);
	if ( bRet == FALSE )
	{
		WARNMESSAGE( "zoom设置失败");
	}

	Value_TransparentComboBoxText valueTransparentComboBoxText;
	UIFACTORYMGR_PTR->GetPropertyValue( valueTransparentComboBoxText, m_strComboboxCameraStyle, m_pWndTree );
	String strComboText = valueTransparentComboBoxText.strComboText;

	if( strComboText == "Sony" )
	{
		SetZoomValue((float)dwZoom/100);
	}
	else
	{
		//SetZoomValue((float)dwZoom);
		SetH650ZoomValue( dwZoom, dwZoomPos );
	}
	
	Window* pWnd = UIFACTORYMGR_PTR->GetWindowPtr( m_strEdtZoom, m_pWndTree );
	if ( pWnd )
	{
		pWnd->ShowWindow(SW_HIDE);
		pWnd->ShowWindow(SW_SHOW);
	}
	
	return S_OK;
}

void CCameraCtrlLogic::SetZoomValue( float fZoom )
{
	CString strCaption;
	strCaption.Format( "%.2f", fZoom );
	UIFACTORYMGR_PTR->SetCaption( m_strEdtZoom, (String)strCaption, m_pWndTree );
}

void CCameraCtrlLogic::SetH650ZoomValue(u32 dwZoom, u32 dwZoomPos)
{
	CString strCaption;
	dwZoom = dwZoom - 199;
	strCaption.Format( "%d", dwZoom );
	UIFACTORYMGR_PTR->SetCaption( m_strEdtZoom, (String)strCaption, m_pWndTree );

	CString strCaption1;
	float fZoomPos = dwZoomPos*1.0/100;
	strCaption1.Format( "%.2f", fZoomPos );
	UIFACTORYMGR_PTR->SetCaption( m_strStcZoom, (String)strCaption1, m_pWndTree );
}

void CCameraCtrlLogic::SetZoomCmd( CString str )
{
	Value_TransparentComboBoxText valueTransparentComboBoxText;
	UIFACTORYMGR_PTR->GetPropertyValue( valueTransparentComboBoxText, m_strComboboxCameraStyle, m_pWndTree );
	
	u8 byCameraStyleIndx = 0;
	String strComboText = valueTransparentComboBoxText.strComboText;

	u32 dwZoom = 0;
	if( strComboText == "Sony")
	{
		float fZoom = StringToFloatThree( str );

		if ( fZoom > 10 )
		{
			fZoom = 10.00;
		}
		else if ( fZoom < 1)
		{
			fZoom = 1.00;
		}

		dwZoom = (fZoom+1.0e-6)*100;
	}
	else
	{
		dwZoom = atoi(LPCTSTR(str));

		if( dwZoom < 1 )
		{
			dwZoom = 1;
		}
		else if( dwZoom > 6775 )
		{
			dwZoom = 6775;
		}

		dwZoom += 199;
	}

	u16 nRet = COMIFMGRPTR->SetCamZoomValueCmd( dwZoom, m_byCamIndex );
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "zoom请求发送失败" );
	}
}

bool CCameraCtrlLogic::OnBtnSwitchLightPensationClick( const IArgs& args )
{
	if ( m_pWndTree == NULL )
	{
		return false;
	}

	Value_SwitchState valueSwitchState;
	UIFACTORYMGR_PTR->GetPropertyValue( valueSwitchState, m_strBtnSwitchLightPensation, m_pWndTree );

	if ( valueSwitchState.bState )
	{
		u16 nRet = COMIFMGRPTR->CamLightPensation( TRUE );	
		if ( nRet != NO_ERROR )
		{
			WARNMESSAGE( "背光补偿请求发送失败" );
		}
	}
	else
	{
		u16 nRet = COMIFMGRPTR->CamLightPensation( FALSE );
		if ( nRet != NO_ERROR )
		{
			WARNMESSAGE( "背光补偿请求发送失败" );
		}
	}

	return true;
}

bool CCameraCtrlLogic::OnBtnSwitchNRClick( const IArgs& args )
{
	Value_SwitchState valueSwitchState;
	UIFACTORYMGR_PTR->GetPropertyValue( valueSwitchState, m_strBtnSwitchNR, m_pWndTree );	
	if ( valueSwitchState.bState )
	{
		EmTPFpgaReduNoise emTPReduNoise;
		GetNRValue( emTPReduNoise );
		u16 nRet = COMIFMGRPTR->CamNRCmd( TRUE, emTPReduNoise );
		if ( nRet != NO_ERROR )
		{
			WARNMESSAGE( "降噪请求发送失败" );
		}
	}
	else
	{
		u16 nRet = COMIFMGRPTR->CamNRCmd( FALSE, emFpgaClose );
		if ( nRet != NO_ERROR )
		{
			WARNMESSAGE( "关闭降噪请求发送失败" );
		}
	}
	return true;	
}

bool CCameraCtrlLogic::OnBtnSwitch2DNRClick(const IArgs& args)
{
	Value_SwitchState valueSwitchState;
	UIFACTORYMGR_PTR->GetPropertyValue( valueSwitchState, m_strBtnSwitch2DNR, m_pWndTree );
	if ( valueSwitchState.bState )
	{
		EmTPReduNoise emTPReduNoise;
		Get2DNRValue( emTPReduNoise );
		u16 nRet = COMIFMGRPTR->Cam2DNRCmd( TRUE, emTPReduNoise );
	}
	else
	{
		u16 nRet = COMIFMGRPTR->Cam2DNRCmd( FALSE, emClose );
		if ( nRet != NO_ERROR )
		{
			WARNMESSAGE( "关闭2D降噪请求发送失败" );
		}
	}

	return true;
}

bool CCameraCtrlLogic::OnBtnSwitch3DNRClick(const IArgs& args)
{
	Value_SwitchState valueSwitchState;
	UIFACTORYMGR_PTR->GetPropertyValue( valueSwitchState, m_strBtnSwitch3DNR, m_pWndTree );
	if ( valueSwitchState.bState )
	{
		EmTPReduNoise emTPReduNoise;
		Get3DNRValue( emTPReduNoise );
		u16 nRet = COMIFMGRPTR->Cam3DNRCmd( TRUE, emTPReduNoise );
	}
	else
	{
		u16 nRet = COMIFMGRPTR->Cam3DNRCmd( FALSE, emClose );
		if ( nRet != NO_ERROR )
		{
			WARNMESSAGE( "关闭3D降噪请求发送失败" );
		}
	}
	return true;
}

HRESULT CCameraCtrlLogic::OnCamLightPensationInd( WPARAM wparam, LPARAM lparam )
{
	if ( m_pWndTree == NULL )
	{
		return S_FALSE;
	}
    BOOL bRet = (BOOL)(lparam);
	BOOL bIsOpen = (BOOL)(wparam);

	if ( bRet )
	{
// 		Value_SwitchState valueSwitchState;
// 		valueSwitchState.bState = bIsOpen;
// 		UIFACTORYMGR_PTR->SetPropertyValue( valueSwitchState, m_strBtnSwitchLightPensation, m_pWndTree );
		SetLightPensationValue( bIsOpen );
	}
	else
	{
		WARNMESSAGE( "背光补偿设置失败");
	}

	return NO_ERROR;
}

HRESULT CCameraCtrlLogic::OnCameraNRInd( WPARAM wparam, LPARAM lparam )
{
	if ( m_pWndTree == NULL )
	{
		return S_FALSE;
	}

	BOOL bOk = (BOOL)(lparam);
	EmTPReduNoise TPReduNoise = static_cast<EmTPReduNoise>(wparam);

	Value_SwitchState valueSwitchState;
	valueSwitchState.bState = bOk;
	UIFACTORYMGR_PTR->SetPropertyValue( valueSwitchState, m_strBtnSwitchNR, m_pWndTree );

	if ( bOk )
	{
		UIFACTORYMGR_PTR->LoadScheme("SchManuelNR", m_pWndTree);
	}
	else
	{
		UIFACTORYMGR_PTR->LoadScheme("SchAutoNR", m_pWndTree);		
	}

	return NO_ERROR;
}

HRESULT CCameraCtrlLogic::OnCamera2DNRInd( WPARAM wparam, LPARAM lparam )
{
	if ( m_pWndTree == NULL )
	{
		return S_FALSE;
	}
	
	BOOL bOk = (BOOL)(lparam);
	EmTPReduNoise TPReduNoise = static_cast<EmTPReduNoise>(wparam);
	
	Value_SwitchState valueSwitchState;
	valueSwitchState.bState = bOk;
	UIFACTORYMGR_PTR->SetPropertyValue( valueSwitchState, m_strBtnSwitch2DNR, m_pWndTree );
	
	if ( bOk )
	{
		UIFACTORYMGR_PTR->LoadScheme("SchManuel2DNR", m_pWndTree);
	}
	else
	{
		UIFACTORYMGR_PTR->LoadScheme("SchAuto2DNR", m_pWndTree);		
	}
	
	return NO_ERROR;
}

HRESULT CCameraCtrlLogic::OnCamera3DNRInd( WPARAM wparam, LPARAM lparam )
{
	if ( m_pWndTree == NULL )
	{
		return S_FALSE;
	}
	
	BOOL bOk = (BOOL)(lparam);
	EmTPReduNoise TPReduNoise = static_cast<EmTPReduNoise>(wparam);
	
	Value_SwitchState valueSwitchState;
	valueSwitchState.bState = bOk;
	UIFACTORYMGR_PTR->SetPropertyValue( valueSwitchState, m_strBtnSwitch3DNR, m_pWndTree );
	
	if ( bOk )
	{
		UIFACTORYMGR_PTR->LoadScheme("SchManuel3DNR", m_pWndTree);
	}
	else
	{
		UIFACTORYMGR_PTR->LoadScheme("SchAuto3DNR", m_pWndTree);		
	}
	
	return NO_ERROR;
}

HRESULT CCameraCtrlLogic::OnCamOrderPosSelInd( WPARAM wparam, LPARAM lparam )
{
	if ( m_pWndTree == NULL )
	{
		return S_FALSE;
	}
	Value_SwitchState valueSwitchState;
	BOOL bOk = (BOOL)(lparam);
	BOOL bCheck = (BOOL)(wparam);
	if ( bOk == TRUE )
	{
		m_bIsOrderPos = bCheck;

	}
	else
	{
		WARNMESSAGE( "配置开机调用预置位1失败" );
	}

	if ( m_bIsOrderPos )
	{
		valueSwitchState.bState = true;
		UIFACTORYMGR_PTR->SetPropertyValue( valueSwitchState, m_strBtnSwitchPersetMove, m_pWndTree );
	} 
	else
	{
		valueSwitchState.bState = false;
		UIFACTORYMGR_PTR->SetPropertyValue( valueSwitchState, m_strBtnSwitchPersetMove, m_pWndTree );
	}

	return NO_ERROR;
}

void CCameraCtrlLogic::ResetNormal()
{
	if ( NULL == m_pWndTree )
	{
		return;
	}
	
	if ( m_bIsCameraPowerOn )
	{
		m_bIsCameraPowerOn = false;
		UIFACTORYMGR_PTR->LoadScheme( "SchmNormal", m_pWndTree );
	}
}

bool CCameraCtrlLogic::OnBtnSaveOrderPos( const IArgs& args )
{
	CMsgDispatch::SendMessage( UI_MOONTOOL_LISTMENU_OPTION, NULL, (LPARAM)em_MENULIST_HIDE );
	UIFACTORYMGR_PTR->ShowWindow( g_strCamCtrlDlg, false );
	UIFACTORYMGR_PTR->ShowWindow( g_strOrderListDlg );
	CMsgDispatch::SendMessage( UI_MOONTOOL_ORDERPOS_MODIFY, NULL, (LPARAM)em_ORDERPOSOPT_SAVE );
	return true;
}

bool CCameraCtrlLogic::OnBtnSwitchOrderPosClick( const IArgs& args )
{
	Value_SwitchState valueSwitchState;
	UIFACTORYMGR_PTR->GetPropertyValue( valueSwitchState, m_strBtnSwitchPersetMove, m_pWndTree );
	if ( valueSwitchState.bState )
	{
		u16 nRet = COMIFMGRPTR->CamOrderPosCheckCmd(TRUE);
		if ( nRet != NO_ERROR )
		{
			WARNMESSAGE( "调用预置位1请求发送失败" );
		}
	}
	else
	{
		u16 nRet = COMIFMGRPTR->CamOrderPosCheckCmd(FALSE);
		if ( nRet != NO_ERROR )
		{
			WARNMESSAGE( "关闭调用预置位1请求发送失败" );
		}
	}
	return true;
}

bool CCameraCtrlLogic::OnBtnUpdateVersion(const IArgs& args)
{
	UIFACTORYMGR_PTR->LoadScheme( "SchmImpCommonClean", NULL, g_stcStrImpCommonDlg );
	UIFACTORYMGR_PTR->LoadScheme( "SchUpgradeMechanism", NULL, g_stcStrImpCommonDlg );
	s32 nDodalResult = UIFACTORYMGR_PTR->Domodal( g_stcStrImpCommonDlg );

	return true;
}

bool CCameraCtrlLogic::OnBtnOrderPosList( const IArgs& args )
{
	UIFACTORYMGR_PTR->ShowWindow( g_strOrderListDlg );
	UIFACTORYMGR_PTR->ShowWindow( g_strCamCtrlDlg, false );
	CMsgDispatch::SendMessage( UI_MOONTOOL_LISTMENU_OPTION, NULL, (LPARAM)em_MENULIST_HIDE );

	return true;	
}

bool CCameraCtrlLogic::OnComboboxNRClick( const IArgs& args )
{
	EmTPFpgaReduNoise emTPReduNoise;
	GetNRValue( emTPReduNoise );
	u16 nRet = COMIFMGRPTR->CamNRCmd( TRUE, emTPReduNoise );
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "降噪请求发送失败" );
	}
	return true;
}

bool CCameraCtrlLogic::OnCombobox2DNRClick(const IArgs& args)
{
	EmTPReduNoise emTPReduNoise;
	Get2DNRValue( emTPReduNoise );
	u16 nRet = COMIFMGRPTR->Cam2DNRCmd( TRUE, emTPReduNoise );
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "2D降噪请求发送失败" );
	}
	return true;
}

bool CCameraCtrlLogic::OnCombobox3DNRClick(const IArgs& args)
{
	EmTPReduNoise emTPReduNoise;
	Get3DNRValue( emTPReduNoise );
	u16 nRet = COMIFMGRPTR->Cam3DNRCmd( TRUE, emTPReduNoise );
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "3D降噪请求发送失败" );
	}
	return true;
}

bool CCameraCtrlLogic::OnBtnSwitchKeyStoneAdjust( const IArgs& args )
{
	if ( m_pWndTree == NULL )
	{
		return false;
	}

	TTPDistortParam tTPDistortParam;
	Value_SwitchState valueSwitchState;
	UIFACTORYMGR_PTR->GetPropertyValue( valueSwitchState, m_strBtnSwitchKeystoneAdjust, m_pWndTree );

//  Value_CSliderCtrlPos valueCSliderCtrlPos;
// 	UIFACTORYMGR_PTR->GetPropertyValue( valueCSliderCtrlPos, m_strSliderAdjustRange, m_pWndTree );
// 	SetAdjustRangeValue( valueCSliderCtrlPos.nPos );
// 	tTPDistortParam.dwCorrectLevel = valueCSliderCtrlPos.nPos;

	String strAdjustRange;
	UIFACTORYMGR_PTR->GetCaption( m_strEdtAdjustRange, strAdjustRange, m_pWndTree );	
	tTPDistortParam.dwCorrectLevel= atoi(strAdjustRange.c_str());

// 	UIFACTORYMGR_PTR->GetPropertyValue( valueCSliderCtrlPos, m_strSliderHoriStretch, m_pWndTree );
// 	SetHoriStretchValue( valueCSliderCtrlPos.nPos );
// 	tTPDistortParam.dwStretchRegion = valueCSliderCtrlPos.nPos;
	String strStretchRegion;
	UIFACTORYMGR_PTR->GetCaption( m_strEdtHoriStretch, strStretchRegion, m_pWndTree );
	tTPDistortParam.dwStretchRegion = atoi(strStretchRegion.c_str());
	
	if ( valueSwitchState.bState )
	{
		tTPDistortParam.dwEnable = 1;
		u16 nRet = NO_ERROR;
	//	u16 nRet = COMIFMGRPTR->CamKeystoneAdjust( tTPDistortParam );	
		if ( nRet != NO_ERROR )
		{
			WARNMESSAGE( "梯形校正请求发送失败" );
		}
	}
	else
	{
		tTPDistortParam.dwEnable = 0;
	//	u16 nRet = COMIFMGRPTR->CamKeystoneAdjust( tTPDistortParam );
		u16 nRet = NO_ERROR;
		if ( nRet != NO_ERROR )
		{
			WARNMESSAGE( "梯形校正请求发送失败" );
		}
	}
	
	return true;	
}


//初次登陆combox值设置
HRESULT CCameraCtrlLogic::OnCamOutputInfoNty( WPARAM wparam, LPARAM lparam )
{
	EmTPMOONOutMode emTPMoonOutMode =  static_cast<EmTPMOONOutMode>(lparam);	

	if ( emTPMoonOutMode == em_MoonOutMode_1080P_25fps || emTPMoonOutMode == em_MoonOutMode_1080P_50fps || emTPMoonOutMode == em_MoonOutMode_720P_50fps )
	{
		m_bSourceCfg = 0;	
	}
	else if ( emTPMoonOutMode == em_MoonOutMode_720P_60fps || emTPMoonOutMode == em_MoonOutMode_1080P_30fps || emTPMoonOutMode == em_MoonOutMode_1080P_60fps )
	{
		m_bSourceCfg = 1;
	}

	SetShutComboxData();
	return true;
}

//sys界面切换信号源输入时，cam界面shut combox下拉值修改
HRESULT CCameraCtrlLogic::OnCamOutputInfoInd( WPARAM wparam, LPARAM lparam )
{
	EmTPMOONOutMode emTPMoonOutMode =  static_cast<EmTPMOONOutMode>(lparam);	
	
	if ( emTPMoonOutMode == em_MoonOutMode_1080P_25fps || emTPMoonOutMode == em_MoonOutMode_1080P_50fps || emTPMoonOutMode == em_MoonOutMode_720P_50fps )
	{
		m_bSourceCfg = 0;		
	}
	else if ( emTPMoonOutMode == em_MoonOutMode_720P_60fps || emTPMoonOutMode == em_MoonOutMode_1080P_30fps || emTPMoonOutMode == em_MoonOutMode_1080P_60fps )
	{
		m_bSourceCfg = 1;
	}
	
	SetShutComboxData();
	return true;	
}

HRESULT CCameraCtrlLogic::OnCamParameterDefaultInd( WPARAM wparam, LPARAM lparam )
{
	BOOL bOk = static_cast<BOOL>(lparam);
	if ( bOk )
	{
		//是否要加保护
//		CMsgboxDlgLogic::GetSingletonPtr()->Clear();
		TTPMoonCamInfo tTPMoonCamInfo = *reinterpret_cast<TTPMoonCamInfo*>(wparam);
		SetCameraCfg( tTPMoonCamInfo );
		WARNMESSAGE( _T("恢复默认设置成功") );
	}
	else
	{
//		CMsgboxDlgLogic::GetSingletonPtr()->Clear();
		WARNMESSAGE( _T("恢复默认设置失败") );
	}
	return true;	
}

HRESULT CCameraCtrlLogic::OnSetCamDistortParamInd( WPARAM wparam, LPARAM lparam )
{
	BOOL bOk = static_cast<BOOL>(lparam);
	if ( bOk )
	{
		TTPDistortParam tTPDistortParam;
		BOOL bOpen;
		tTPDistortParam.dwEnable = (u32)(wparam);
		if ( tTPDistortParam.dwEnable == 1 )
		{
			bOpen = TRUE;
		}
		if ( tTPDistortParam.dwEnable == 0 )
		{
			bOpen = FALSE;
		}
		SetKeyStoneAdjust( bOpen );

	}

	u32 dwAdjustRangeInLib = 0;	
	MOONLIBDATAMGRPTR->GetCamAdjustRange( dwAdjustRangeInLib );
	SetAdjustRangeValue( dwAdjustRangeInLib );

	u32 dwHoriStretchInLib = 0;	
	MOONLIBDATAMGRPTR->GetCamHoriStretch( dwHoriStretchInLib );
	SetHoriStretchValue( dwHoriStretchInLib );

	return true;	
}

void CCameraCtrlLogic::SetShutComboxData()
{
	std::vector<CString> vecShut;
	if ( m_bSourceCfg )
	{
		//设置快门下拉框数据
		vecShut.push_back( "1/1" );
		vecShut.push_back( "1/2" );
		vecShut.push_back( "1/4" );
		vecShut.push_back( "1/8" );
		vecShut.push_back( "1/15" );
		vecShut.push_back( "1/30" );
		vecShut.push_back( "1/60" );
		vecShut.push_back( "1/90" );
		vecShut.push_back( "1/100" );
		vecShut.push_back( "1/125" );
		vecShut.push_back( "1/180" );
		vecShut.push_back( "1/250" );
		vecShut.push_back( "1/350" );
		vecShut.push_back( "1/500" );
		vecShut.push_back( "1/725" );
		vecShut.push_back( "1/1000" );
		vecShut.push_back( "1/1500" );
		vecShut.push_back( "1/2000" );
		vecShut.push_back( "1/3000" );
		vecShut.push_back( "1/4000" );
		vecShut.push_back( "1/6000" );
		vecShut.push_back( "1/10000" );
	}
	else
	{
		vecShut.push_back( "1/1" );
		vecShut.push_back( "1/2" );
		vecShut.push_back( "1/3" );
		vecShut.push_back( "1/6" );
		vecShut.push_back( "1/12" );
		vecShut.push_back( "1/25" );
		vecShut.push_back( "1/50" );
		vecShut.push_back( "1/75" );
		vecShut.push_back( "1/100" );
		vecShut.push_back( "1/120" );
		vecShut.push_back( "1/150" );
		vecShut.push_back( "1/215" );
		vecShut.push_back( "1/300" );
		vecShut.push_back( "1/425" );
		vecShut.push_back( "1/600" );
		vecShut.push_back( "1/1000" );
		vecShut.push_back( "1/1250" );
		vecShut.push_back( "1/1750" );
		vecShut.push_back( "1/2500" );
		vecShut.push_back( "1/3500" );
		vecShut.push_back( "1/6000" );
		vecShut.push_back( "1/10000" );
	}

	UIFACTORYMGR_PTR->SetComboListData( m_strComboboxShut, vecShut, m_pWndTree );
    //不能设默认值，应设之前值	
//	UIFACTORYMGR_PTR->SetComboText( m_strComboboxShut, "1/100", m_pWndTree );

	//防止系统设置界面切换输入源时，快门combox状态不对
	EmTPMOOMMode emExpMode;
	MOONLIBDATAMGRPTR->GetCamMoonMode( emExpMode );
	SetAutoExp(emExpMode);
	//切换回来时，还要原先对应的枚举值
	if ( m_bSourceCfg )
	{
		EmTPSOrThShutter emShutSpd;
		MOONLIBDATAMGRPTR->GetCamShutSpd( emShutSpd );	
		SetShutSpdValue(emShutSpd);
	}
	else
	{
		EmTPFOrTwShutter emTwShutter;
		MOONLIBDATAMGRPTR->GetTwCamShutSpd( emTwShutter );
		SetTwShutterValue(emTwShutter);
	}

}

void CCameraCtrlLogic::SetLightPensationValue( BOOL bUsed )
{
// 	Value_SwitchState valueSwitchState;
// 	valueSwitchState.bState = bUsed;
// 	UIFACTORYMGR_PTR->SetPropertyValue( valueSwitchState, m_strBtnSwitchLightPensation, m_pWndTree );
//  背光补偿由switchbtn替换为checkbtn
	if( bUsed )
	{
		UIFACTORYMGR_PTR->SetCheckState( m_strBtnCheckBackLight, 1, m_pWndTree );
	}
	else
	{
		UIFACTORYMGR_PTR->SetCheckState( m_strBtnCheckBackLight, 0, m_pWndTree );
	}

}

void CCameraCtrlLogic::SetKeyStoneAdjust( BOOL bUsed )
{
	Value_SwitchState valueSwitchState;
	valueSwitchState.bState = bUsed;
	UIFACTORYMGR_PTR->SetPropertyValue( valueSwitchState, m_strBtnSwitchKeystoneAdjust, m_pWndTree );
	if ( bUsed )
	{
		UIFACTORYMGR_PTR->LoadScheme("SchKeyStoneAdjustOn", m_pWndTree);
	}
	else
	{
		UIFACTORYMGR_PTR->LoadScheme("SchKeyStoneAdjustOff", m_pWndTree);
	}
}

void CCameraCtrlLogic::SetFocusState( EmTPMOOMMode emFocusMode )
{
	if ( emFocusMode == emAuto )
	{
		UIFACTORYMGR_PTR->SetCheckState( m_strBtnCheckAutoFocus, 1, m_pWndTree );
		UIFACTORYMGR_PTR->SetCheckState( m_strBtnCheckManuelFocus, 0, m_pWndTree );
		UIFACTORYMGR_PTR->LoadScheme( "SchAutoFocus", m_pWndTree );
	}
	else
	{
		UIFACTORYMGR_PTR->SetCheckState( m_strBtnCheckManuelFocus, 1, m_pWndTree );
		UIFACTORYMGR_PTR->SetCheckState( m_strBtnCheckAutoFocus, 0, m_pWndTree );
		UIFACTORYMGR_PTR->LoadScheme( "SchManuelFocus", m_pWndTree );
	}		
}

HRESULT CCameraCtrlLogic::OnSetCamAutoFocusInd( WPARAM wparam, LPARAM lparam )
{
	m_emTPMOOMMode = static_cast<EmTPMOOMMode>(wparam);
	BOOL bRet = static_cast<BOOL>(lparam);
	SetFocusState( m_emTPMOOMMode );
	
	if ( bRet == FALSE )
	{
		WARNMESSAGE( "聚焦设置失败" );
	}
	return S_OK;	
}

bool CCameraCtrlLogic::OnBtnCheckBackLightClick( const IArgs& args )
{
	if ( m_pWndTree == NULL )
	{
		return false;
	}
	s32 nCheckState = 0;
	UIFACTORYMGR_PTR->GetCheckState( m_strBtnCheckBackLight, nCheckState, m_pWndTree );
	if ( nCheckState )
	{
		u16 nRet = COMIFMGRPTR->CamLightPensation( TRUE );	
		if ( nRet != NO_ERROR )
		{
			WARNMESSAGE( "背光补偿请求发送失败" );
		}
	}
	else
	{
		u16 nRet = COMIFMGRPTR->CamLightPensation( FALSE );
		if ( nRet != NO_ERROR )
		{
			WARNMESSAGE( "背光补偿请求发送失败" );
		}
	}

	return true;
}

bool CCameraCtrlLogic::OnSliderAdjustRangeChanged( const IArgs& args )
{
	if ( m_pWndTree == NULL )
	{
		return false;
	}
	
	TTPDistortParam tTPDistortParam;
	Value_CSliderCtrlPos valueCSliderCtrlPos;
	UIFACTORYMGR_PTR->GetPropertyValue( valueCSliderCtrlPos, m_strSliderAdjustRange, m_pWndTree );
	SetAdjustRangeValue( valueCSliderCtrlPos.nPos );
	tTPDistortParam.dwCorrectLevel = valueCSliderCtrlPos.nPos;
	Value_CSliderCtrlPos valueCSliderCtrlPos1;
	UIFACTORYMGR_PTR->GetPropertyValue( valueCSliderCtrlPos1, m_strSliderHoriStretch, m_pWndTree );
	tTPDistortParam.dwStretchRegion = valueCSliderCtrlPos1.nPos;
	tTPDistortParam.dwEnable = 1;


	u32 dwAdjustRange = valueCSliderCtrlPos.nPos;
	u32 dwAdjustRangeInLib = 0;

	MOONLIBDATAMGRPTR->GetCamAdjustRange( dwAdjustRangeInLib );
	if ( dwAdjustRange == dwAdjustRangeInLib )
	{
		return true;
	}
	
// 	u16 nRet = COMIFMGRPTR->CamAdjustRangeCmd( dwAdjustRange );
// 	if ( nRet != NO_ERROR )
// 	{
// 		WARNMESSAGE( "校正幅度调节请求发送失败" );
// 	}
//	u16 nRet = COMIFMGRPTR->CamKeystoneAdjust( tTPDistortParam );	
	u16 nRet = NO_ERROR;
	return true;
}

void CCameraCtrlLogic::SetAdjustRangeValue( u32 dwAdjustRange )
{
	Value_CSliderCtrlPos valueCSliderCtrlPos;
	valueCSliderCtrlPos.nPos = dwAdjustRange;
	UIFACTORYMGR_PTR->SetPropertyValue( valueCSliderCtrlPos, m_strSliderAdjustRange, m_pWndTree );
	
	CString strCaption;
	strCaption.Format( "%d", dwAdjustRange );
	Value_WindowCaption valueWindowCaption;
	valueWindowCaption.strCaption = strCaption;
	UIFACTORYMGR_PTR->SetPropertyValue( valueWindowCaption, m_strEdtAdjustRange, m_pWndTree );
	
	Window* pWnd = UIFACTORYMGR_PTR->GetWindowPtr( m_strEdtAdjustRange, m_pWndTree );
	if ( pWnd )
	{
		(( CEdit *) pWnd)->SetSel( -1 );
	}	
}

void CCameraCtrlLogic::SetGammaValue(EmH650Gamma emGamma)
{
	CString strCaption;
	
	if( emGamma == emGamma1 )
	{
		SetGammaName(_T("0"));
	}
	else if( emGamma == emGamma2 )
	{
		SetGammaName(_T("1"));
	}
	else if( emGamma == emGamma3 )
	{
		SetGammaName(_T("2"));
	}
	else
	{
		SetGammaName(_T("3"));
	}
}

void CCameraCtrlLogic::SetMechVersion( s8 *achSwVersion, s8 *achHwVersion )
{
	String strVerNum = "HW: ";
	strVerNum += achHwVersion;
	strVerNum += "    ";
	strVerNum += "SW: ";
	strVerNum += achSwVersion;
	UIFACTORYMGR_PTR->SetCaption( m_strStcVersionNum, strVerNum, m_pWndTree );
}

bool CCameraCtrlLogic::OnSliderHoriStretchChanged( const IArgs& args )
{
	if ( m_pWndTree == NULL )
	{
		return false;
	}

	TTPDistortParam tTPDistortParam;

	Value_CSliderCtrlPos valueCSliderCtrlPos;
	UIFACTORYMGR_PTR->GetPropertyValue( valueCSliderCtrlPos, m_strSliderHoriStretch, m_pWndTree );
	SetHoriStretchValue( valueCSliderCtrlPos.nPos );
	tTPDistortParam.dwStretchRegion = valueCSliderCtrlPos.nPos;
	//不能复用同一变量，否则后续比较会有问题
	Value_CSliderCtrlPos valueCSliderCtrlPos1;
	UIFACTORYMGR_PTR->GetPropertyValue( valueCSliderCtrlPos1, m_strSliderAdjustRange, m_pWndTree );
	tTPDistortParam.dwCorrectLevel = valueCSliderCtrlPos1.nPos;

	tTPDistortParam.dwEnable = 1;

	u32 dwHoriStretch = valueCSliderCtrlPos.nPos;
	u32 dwHoriStretchInLib = 0;
	
	MOONLIBDATAMGRPTR->GetCamHoriStretch( dwHoriStretchInLib );
	if ( dwHoriStretch == dwHoriStretchInLib )
	{
		return true;
	}
	
// 	u16 nRet = COMIFMGRPTR->CamHoriStretchCmd( dwHoriStretch );
// 	if ( nRet != NO_ERROR )
// 	{
// 		WARNMESSAGE( "校正幅度调节请求发送失败" );
// 	}
	//u16 nRet = COMIFMGRPTR->CamKeystoneAdjust( tTPDistortParam );
	u16 nRet = NO_ERROR;
	return true;	
}

void CCameraCtrlLogic::SetHoriStretchValue( u32 dwHoriStretch )
{
	Value_CSliderCtrlPos valueCSliderCtrlPos;
	valueCSliderCtrlPos.nPos = dwHoriStretch;
	UIFACTORYMGR_PTR->SetPropertyValue( valueCSliderCtrlPos, m_strSliderHoriStretch, m_pWndTree );
	
	CString strCaption;
	strCaption.Format( "%d", dwHoriStretch );
	Value_WindowCaption valueWindowCaption;
	valueWindowCaption.strCaption = strCaption;
	UIFACTORYMGR_PTR->SetPropertyValue( valueWindowCaption, m_strEdtHoriStretch, m_pWndTree );
	
	Window* pWnd = UIFACTORYMGR_PTR->GetWindowPtr( m_strEdtHoriStretch, m_pWndTree );
	if ( pWnd )
	{
		(( CEdit *) pWnd)->SetSel( -1 );
	}	
}

bool CCameraCtrlLogic::OnEdtAdjustRangeChange( const IArgs& args )
{
	if ( m_pWndTree == NULL )
	{
		return true;
	}
	
	Window* pWnd = UIFACTORYMGR_PTR->GetWindowPtr( m_strEdtAdjustRange, m_pWndTree );
	if ( pWnd )
	{
		(( CEdit *) pWnd)->SetSel( -1 );
	}
	
	Args_WindowMsg* pMsg = dynamic_cast< Args_WindowMsg *>( const_cast<IArgs*>( &args ));
	
	UINT nChar = 0;
	if ( NULL !=  pMsg  )
	{
		nChar = pMsg->m_Msg.wParam;
	}
	
	if ( nChar == 0x0d )
	{
		SetFocus(NULL);
	}
	
	return true;
}

bool CCameraCtrlLogic::OnKillFocusEdtAdjustRange( const IArgs& args )
{
	String str;
	UIFACTORYMGR_PTR->GetCaption( m_strEdtAdjustRange, str, m_pWndTree );
	
	SetAdjustRangeCmd(str.c_str());
	return true;
}

void CCameraCtrlLogic::SetAdjustRangeCmd( CString str )
{
	int n = atoi( str );
	
	if ( n > 140 )
	{
		n = 140;
	}
	else if ( n < 0)
	{
		n = 0;
	}
	
	TTPDistortParam tTPDistortParam;
	tTPDistortParam.dwCorrectLevel = n;
	tTPDistortParam.dwEnable = 1;
	String strStretchRegion;
	UIFACTORYMGR_PTR->GetCaption( m_strEdtHoriStretch, strStretchRegion, m_pWndTree );
	tTPDistortParam.dwStretchRegion = atoi(strStretchRegion.c_str());
	u16 nRet = NO_ERROR;
//	u16 nRet = COMIFMGRPTR->CamKeystoneAdjust( tTPDistortParam );
}

bool CCameraCtrlLogic::OnEdtHoriStretchChange( const IArgs& args )
{
	if ( m_pWndTree == NULL )
	{
		return true;
	}
	
	Window* pWnd = UIFACTORYMGR_PTR->GetWindowPtr( m_strEdtHoriStretch, m_pWndTree );
	if ( pWnd )
	{
		(( CEdit *) pWnd)->SetSel( -1 );
	}
	
	Args_WindowMsg* pMsg = dynamic_cast< Args_WindowMsg *>( const_cast<IArgs*>( &args ));
	
	UINT nChar = 0;
	if ( NULL !=  pMsg  )
	{
		nChar = pMsg->m_Msg.wParam;
	}
	
	if ( nChar == 0x0d )
	{
		SetFocus(NULL);
	}
	
	return true;	
}

bool CCameraCtrlLogic::OnKillFocusEdtHoriStretch( const IArgs& args )
{
	String str;
	UIFACTORYMGR_PTR->GetCaption( m_strEdtHoriStretch, str, m_pWndTree );
	
	SetHoriStretchCmd(str.c_str());
	return true;	
}

void CCameraCtrlLogic::SetHoriStretchCmd( CString str )
{
	int n = atoi( str );
	
	if ( n > 192 )
	{
		n = 192;
	}
	else if ( n < 0)
	{
		n = 0;
	}
	
	TTPDistortParam tTPDistortParam;
	tTPDistortParam.dwStretchRegion = n;
	tTPDistortParam.dwEnable = 1;
	String strAdjustRange;
	UIFACTORYMGR_PTR->GetCaption( m_strEdtAdjustRange, strAdjustRange, m_pWndTree );	
	tTPDistortParam.dwCorrectLevel= atoi(strAdjustRange.c_str());
	
//	u16 nRet = COMIFMGRPTR->CamKeystoneAdjust( tTPDistortParam );	
}

void CCameraCtrlLogic::showCameraInfo(EmTPMechanism emCamType, bool bHide)
{
	UIFACTORYMGR_PTR->ShowWindow(m_strStcLineImagePara, !bHide, m_pWndTree);
	UIFACTORYMGR_PTR->ShowWindow(m_strStcImageParam, !bHide, m_pWndTree);

	UIFACTORYMGR_PTR->ShowWindow( m_strStcLineBright, !bHide, m_pWndTree );
	UIFACTORYMGR_PTR->ShowWindow( m_strStcBright, !bHide, m_pWndTree );
	UIFACTORYMGR_PTR->ShowWindow( m_strSliderBright, !bHide, m_pWndTree );
	UIFACTORYMGR_PTR->ShowWindow( m_strEdtBright, !bHide, m_pWndTree );

	UIFACTORYMGR_PTR->ShowWindow( m_strStcLineSaturat, !bHide, m_pWndTree );
	UIFACTORYMGR_PTR->ShowWindow( m_strStcSaturat, !bHide, m_pWndTree );
	UIFACTORYMGR_PTR->ShowWindow( m_strSliderSaturat, !bHide, m_pWndTree );
	UIFACTORYMGR_PTR->ShowWindow( m_strEdtSaturat, !bHide, m_pWndTree );

    if (emCamType == emSonyFCBCS8230)
    {
        UIFACTORYMGR_PTR->ShowWindow( m_strStcLineContrast, FALSE, m_pWndTree );
        UIFACTORYMGR_PTR->ShowWindow( m_strStcContrast, FALSE, m_pWndTree );
        UIFACTORYMGR_PTR->ShowWindow( m_strSliderContrast, FALSE, m_pWndTree );
	    UIFACTORYMGR_PTR->ShowWindow( m_strEdtContrast, FALSE, m_pWndTree );

        UIFACTORYMGR_PTR->ShowWindow( m_strStcLineSharp, FALSE, m_pWndTree );
        UIFACTORYMGR_PTR->ShowWindow( m_strStcSharp, FALSE, m_pWndTree );
        UIFACTORYMGR_PTR->ShowWindow( m_strSliderSharp, FALSE, m_pWndTree );
	    UIFACTORYMGR_PTR->ShowWindow( m_strEdtSharp, FALSE, m_pWndTree );

        UIFACTORYMGR_PTR->ShowWindow( m_strStcVersion, FALSE, m_pWndTree );
        UIFACTORYMGR_PTR->ShowWindow( m_strStcVersionNum, FALSE, m_pWndTree );
	    UIFACTORYMGR_PTR->ShowWindow( m_strBtnUpdateVersion, FALSE, m_pWndTree);

        UIFACTORYMGR_PTR->ShowWindow( m_strStcZoom, FALSE, m_pWndTree );
    }
    else
    {
        UIFACTORYMGR_PTR->ShowWindow( m_strStcLineContrast, !bHide, m_pWndTree );
        UIFACTORYMGR_PTR->ShowWindow( m_strStcContrast, !bHide, m_pWndTree );
        UIFACTORYMGR_PTR->ShowWindow( m_strSliderContrast, !bHide, m_pWndTree );
	    UIFACTORYMGR_PTR->ShowWindow( m_strEdtContrast, !bHide, m_pWndTree );

        UIFACTORYMGR_PTR->ShowWindow( m_strStcLineSharp, !bHide, m_pWndTree );
        UIFACTORYMGR_PTR->ShowWindow( m_strStcSharp, !bHide, m_pWndTree );
        UIFACTORYMGR_PTR->ShowWindow( m_strSliderSharp, !bHide, m_pWndTree );
	    UIFACTORYMGR_PTR->ShowWindow( m_strEdtSharp, !bHide, m_pWndTree );

        UIFACTORYMGR_PTR->ShowWindow( m_strStcVersion, !bHide, m_pWndTree );
        UIFACTORYMGR_PTR->ShowWindow( m_strStcVersionNum, !bHide, m_pWndTree );
	    UIFACTORYMGR_PTR->ShowWindow( m_strBtnUpdateVersion, !bHide, m_pWndTree);

        UIFACTORYMGR_PTR->ShowWindow( m_strStcZoom, !bHide, m_pWndTree );
    }

	UIFACTORYMGR_PTR->ShowWindow( m_strStcLineGamma, !bHide, m_pWndTree );
	UIFACTORYMGR_PTR->ShowWindow( m_strStcGamma, !bHide, m_pWndTree );
	UIFACTORYMGR_PTR->ShowWindow( m_strComboboxGamma, !bHide, m_pWndTree );

	UIFACTORYMGR_PTR->ShowWindow( m_strStcLine2DNR, !bHide, m_pWndTree);
	UIFACTORYMGR_PTR->ShowWindow( m_strStc2DNR, !bHide, m_pWndTree);
	UIFACTORYMGR_PTR->ShowWindow( m_strBtnSwitch2DNR, !bHide, m_pWndTree);
	UIFACTORYMGR_PTR->ShowWindow( m_strCombobox2DNR, !bHide, m_pWndTree);

	UIFACTORYMGR_PTR->ShowWindow( m_strStcLine3DNR, !bHide, m_pWndTree);
	UIFACTORYMGR_PTR->ShowWindow( m_strStc3DNR, !bHide, m_pWndTree);
	UIFACTORYMGR_PTR->ShowWindow( m_strBtnSwitch3DNR, !bHide, m_pWndTree);
	UIFACTORYMGR_PTR->ShowWindow( m_strCombobox3DNR, !bHide, m_pWndTree);
}

String CCameraCtrlLogic::GetCamMechnismStyle()
{
	Value_TransparentComboBoxText valueTransparentComboBoxText;
	UIFACTORYMGR_PTR->GetPropertyValue( valueTransparentComboBoxText, m_strComboboxCameraStyle, m_pWndTree );
	String strComboText = valueTransparentComboBoxText.strComboText;

	return strComboText;
}






































