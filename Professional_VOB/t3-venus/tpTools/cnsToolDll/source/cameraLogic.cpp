// cameralogic.cpp: implementation of the CCameraLogic class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h" 
#include "cameraLogic.h"

#define MAX_PICSCEAPT_NUMBER 15
#define MIN_PICSCEAPT_NUMBER 1

u16 g_wCameraTimerID = 0;
VOID CALLBACK CBCameraTimerFun( HWND hwnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime );   //by xhx
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CCameraCtrlLogic::CCameraCtrlLogic()
: m_strComboboxCamera("ComboboxCamera")
, m_strBtnSwitchVisualField("PresetDlg/BtnSwitchVisualField")
, m_strBtnSwitchPersetMove("PresetDlg/BtnSwitchPersetMove")
, m_strComboboxExposureGain("ComboboxExposureGain")
, m_strComboboxShut("ComboboxShut")
, m_strComboboxBackLight("ComboboxBackLight")
, m_strSliderAperture("SliderAperture")
, m_strEdtAperture("EdtAperture")
, m_strSliderRGain("SliderRGain")
, m_strEdtRGain("EdtRGain")
, m_strSliderBGain("SliderBGain")
, m_strEdtBGain("EdtBGain")
, m_strSliderPicSceApt("ManuelModeDlg/SliderPicSceApt")
, m_strEdtPicSceApt("ManuelModeDlg/EdtPicSceApt")
, m_strSliderContrast("SliderContrast")
, m_strEdtContrast("EdtContrast")
, m_strSliderSaturat("SliderSaturat")
, m_strEdtSaturat("EdtSaturat")
, m_strSliderHue("SliderHue")
, m_strEdtHue("EdtHue")
, m_strSliderBright("SliderBright")
, m_strEdtBright("EdtBright")
, m_strEdtZoom("PresetDlg/EdtZoom")
, m_strBtnSwitch3DNR("BtnSwitch3DNR")
, m_strBtnSwitchAutoExposure("BtnSwitchAutoExposure")
, m_strBtnSwitchAutoWB("BtnSwitchAutoWB")
, m_strBtnZoomPlus("PresetDlg/BtnZoomPlus")
, m_strBtnZoomSub("PresetDlg/BtnZoomSub")
, m_bIsCameraPowerOn(false)
, m_bLoginByOther(false)
{
}

CCameraCtrlLogic::~CCameraCtrlLogic()
{
	UnRegMsg();
	UnRegFunc();
}

void CCameraCtrlLogic::RegMsg()
{
	REG_MSG_HANDLER( UI_CNSTOOL_CAMERA_CFG_NTY, CCameraCtrlLogic::OnCameraCfgNty, CAMERALOGICRPTR, CCameraCtrlLogic );
	REG_MSG_HANDLER( UI_CNSTOOL_CAMERA_SELECT_IND, CCameraCtrlLogic::OnCameraSelectInd, CAMERALOGICRPTR, CCameraCtrlLogic );
	REG_MSG_HANDLER( UI_CNSTOOL_CAMERA_ZOOM_IND, CCameraCtrlLogic::OnCameraZoomInd, CAMERALOGICRPTR, CCameraCtrlLogic );
	REG_MSG_HANDLER( UI_CNSTOOL_CAMERA_OSDSHOW_IND, CCameraCtrlLogic::OnCameraOSDShowInd, CAMERALOGICRPTR, CCameraCtrlLogic );
	REG_MSG_HANDLER( UI_CNSTOOL_CAMERA_AUTO_FOCUS_IND, CCameraCtrlLogic::OnCameraAutoFocusInd, CAMERALOGICRPTR, CCameraCtrlLogic );
	REG_MSG_HANDLER( UI_CNSTOOL_CAMERA_FOCUS_IND, CCameraCtrlLogic::OnCameraFocusInd, CAMERALOGICRPTR, CCameraCtrlLogic );
	REG_MSG_HANDLER( UI_CNSTOOL_CAMERA_PERSET_MOVE_IND, CCameraCtrlLogic::OnCameraPersetMoveInd, CAMERALOGICRPTR, CCameraCtrlLogic );
	REG_MSG_HANDLER( UI_CNSTOOL_CAMERA_AUTO_EXPOSURE_IND, CCameraCtrlLogic::OnCameraAutoExposureInd, CAMERALOGICRPTR, CCameraCtrlLogic );
	REG_MSG_HANDLER( UI_CNSTOOL_CAMERA_GAIN_IND, CCameraCtrlLogic::OnCameraGainInd, CAMERALOGICRPTR, CCameraCtrlLogic );
	REG_MSG_HANDLER( UI_CNSTOOL_CAMERA_SHUT_SPD_IND, CCameraCtrlLogic::OnCameraShutSpdInd, CAMERALOGICRPTR, CCameraCtrlLogic );
	REG_MSG_HANDLER( UI_CNSTOOL_CAMERA_BACK_LIGHT_IND, CCameraCtrlLogic::OnCameraBackLightInd, CAMERALOGICRPTR, CCameraCtrlLogic );
	REG_MSG_HANDLER( UI_CNSTOOL_CAMERA_APERTURE_IND, CCameraCtrlLogic::OnCameraApertureInd, CAMERALOGICRPTR, CCameraCtrlLogic );
	REG_MSG_HANDLER( UI_CNSTOOL_CAMERA_AUTO_WB_IND, CCameraCtrlLogic::OnCameraAutoWBInd, CAMERALOGICRPTR, CCameraCtrlLogic );
	REG_MSG_HANDLER( UI_CNSTOOL_CAMERA_RGAIN_IND, CCameraCtrlLogic::OnCameraRGainInd, CAMERALOGICRPTR, CCameraCtrlLogic );
	REG_MSG_HANDLER( UI_CNSTOOL_CAMERA_BGAIN_IND, CCameraCtrlLogic::OnCameraBGainInd, CAMERALOGICRPTR, CCameraCtrlLogic );
	REG_MSG_HANDLER( UI_CNSTOOL_CAMERA_PIC_SCENE_MODE_IND, CCameraCtrlLogic::OnCameraPicSceneModeInd, CAMERALOGICRPTR, CCameraCtrlLogic );
	REG_MSG_HANDLER( UI_CNSTOOL_CAMERA_GAMMA_IND, CCameraCtrlLogic::OnCameraGammaInd, CAMERALOGICRPTR, CCameraCtrlLogic );
	REG_MSG_HANDLER( UI_CNSTOOL_CAMERA_PIC_SCE_APT_IND, CCameraCtrlLogic::OnCameraPicSceAptInd, CAMERALOGICRPTR, CCameraCtrlLogic );
	REG_MSG_HANDLER( UI_CNSTOOL_CAMERA_CONTRAST_IND, CCameraCtrlLogic::OnCameraContrastInd, CAMERALOGICRPTR, CCameraCtrlLogic );
	REG_MSG_HANDLER( UI_CNSTOOL_CAMERA_SATURAT_IND, CCameraCtrlLogic::OnCameraSaturatInd, CAMERALOGICRPTR, CCameraCtrlLogic );
	REG_MSG_HANDLER( UI_CNSTOOL_CAMERA_HUE_IND, CCameraCtrlLogic::OnCameraHueInd, CAMERALOGICRPTR, CCameraCtrlLogic );
	REG_MSG_HANDLER( UI_CNSTOOL_CAMERA_BRIGHT_IND, CCameraCtrlLogic::OnCameraBrightInd, CAMERALOGICRPTR, CCameraCtrlLogic );
	REG_MSG_HANDLER( UI_CNSTOOL_CAMERA_NR_STM_CLEAN_IND, CCameraCtrlLogic::OnCameraNRStmCleanInd, CAMERALOGICRPTR, CCameraCtrlLogic );
	REG_MSG_HANDLER( UI_CNSTOOL_CAMERA_3DNR_IND, CCameraCtrlLogic::OnCamera3DNRInd, CAMERALOGICRPTR, CCameraCtrlLogic );
	REG_MSG_HANDLER( UI_CNSTOOL_CAMERA_RESET_IND, CCameraCtrlLogic::OnCameraResetInd, CAMERALOGICRPTR, CCameraCtrlLogic );
	REG_MSG_HANDLER( UI_CNSTOOL_CAMERA_PERSET_SAVE_IND, CCameraCtrlLogic::OnCameraPersetSaveInd, CAMERALOGICRPTR, CCameraCtrlLogic );
	REG_MSG_HANDLER( UI_CNSTOOL_SET_CAMERA_ZOOM_IND, CCameraCtrlLogic::OnSetCameraZoomInd, CAMERALOGICRPTR, CCameraCtrlLogic );
	REG_MSG_HANDLER( UI_CNSTOOL_CAMERA_POWER_ON_NTY, CCameraCtrlLogic::OnCameraPowerOnNty, CAMERALOGICRPTR, CCameraCtrlLogic );
}

void CCameraCtrlLogic::UnRegMsg()
{
}

void CCameraCtrlLogic::RegCBFun()
{
	REG_GOBAL_MEMBER_FUNC( "CCameraLogic::InitWnd", CCameraCtrlLogic::InitWnd, CAMERALOGICRPTR, CCameraCtrlLogic );
	REG_GOBAL_MEMBER_FUNC( "CCameraLogic::OnComboboxCameraClick", CCameraCtrlLogic::OnComboboxCameraClick, CAMERALOGICRPTR, CCameraCtrlLogic );
	REG_GOBAL_MEMBER_FUNC( "CCameraLogic::OnBtnImportClick", CCameraCtrlLogic::OnBtnImportClick, CAMERALOGICRPTR, CCameraCtrlLogic );
	REG_GOBAL_MEMBER_FUNC( "CCameraLogic::OnBtnExportClick", CCameraCtrlLogic::OnBtnExportClick, CAMERALOGICRPTR, CCameraCtrlLogic );
	REG_GOBAL_MEMBER_FUNC( "CCameraLogic::OnBtnResumeClick", CCameraCtrlLogic::OnBtnResumeClick, CAMERALOGICRPTR, CCameraCtrlLogic );
	REG_GOBAL_MEMBER_FUNC( "CCameraLogic::OnBtnUpgradeCameraClick", CCameraCtrlLogic::OnBtnUpgradeCameraClick, CAMERALOGICRPTR, CCameraCtrlLogic );
	REG_GOBAL_MEMBER_FUNC( "CCameraLogic::OnBtnZoomPlusClick", CCameraCtrlLogic::OnBtnZoomPlusClick, CAMERALOGICRPTR, CCameraCtrlLogic );
	REG_GOBAL_MEMBER_FUNC( "CCameraLogic::OnBtnZoomSubClick", CCameraCtrlLogic::OnBtnZoomSubClick, CAMERALOGICRPTR, CCameraCtrlLogic );
	REG_GOBAL_MEMBER_FUNC( "CCameraLogic::OnBtnZoomPlusHold", CCameraCtrlLogic::OnBtnZoomPlusHold, CAMERALOGICRPTR, CCameraCtrlLogic );
	REG_GOBAL_MEMBER_FUNC( "CCameraLogic::OnBtnZoomPlusHoldEnd", CCameraCtrlLogic::OnBtnZoomPlusHoldEnd, CAMERALOGICRPTR, CCameraCtrlLogic );
	REG_GOBAL_MEMBER_FUNC( "CCameraLogic::OnBtnZoomSubHold", CCameraCtrlLogic::OnBtnZoomSubHold, CAMERALOGICRPTR, CCameraCtrlLogic );
	REG_GOBAL_MEMBER_FUNC( "CCameraLogic::OnBtnZoomSubHoldEnd", CCameraCtrlLogic::OnBtnZoomSubHoldEnd, CAMERALOGICRPTR, CCameraCtrlLogic );
	REG_GOBAL_MEMBER_FUNC( "CCameraLogic::OnBtnSwitchVisualFieldClick", CCameraCtrlLogic::OnBtnSwitchVisualFieldClick, CAMERALOGICRPTR, CCameraCtrlLogic );
	REG_GOBAL_MEMBER_FUNC( "CCameraLogic::OnBtnPresetSaveClick", CCameraCtrlLogic::OnBtnPresetSaveClick, CAMERALOGICRPTR, CCameraCtrlLogic );
	REG_GOBAL_MEMBER_FUNC( "CCameraLogic::OnBtnManuelFocusClick", CCameraCtrlLogic::OnBtnManuelFocusClick, CAMERALOGICRPTR, CCameraCtrlLogic );
	REG_GOBAL_MEMBER_FUNC( "CCameraLogic::OnBtnAutoFocusClick", CCameraCtrlLogic::OnBtnAutoFocusClick, CAMERALOGICRPTR, CCameraCtrlLogic );
	REG_GOBAL_MEMBER_FUNC( "CCameraLogic::OnLBtnDownFocusNear", CCameraCtrlLogic::OnLBtnDownFocusNear, CAMERALOGICRPTR, CCameraCtrlLogic );
	REG_GOBAL_MEMBER_FUNC( "CCameraLogic::OnLBtnUpFocusNear", CCameraCtrlLogic::OnLBtnUpFocusNear, CAMERALOGICRPTR, CCameraCtrlLogic );
	REG_GOBAL_MEMBER_FUNC( "CCameraLogic::OnLBtnDownFocusFar", CCameraCtrlLogic::OnLBtnDownFocusFar, CAMERALOGICRPTR, CCameraCtrlLogic );
	REG_GOBAL_MEMBER_FUNC( "CCameraLogic::OnLBtnUpFocusFar", CCameraCtrlLogic::OnLBtnUpFocusFar, CAMERALOGICRPTR, CCameraCtrlLogic );
	REG_GOBAL_MEMBER_FUNC( "CCameraLogic::OnBtnSwitchPersetMove", CCameraCtrlLogic::OnBtnSwitchPersetMove, CAMERALOGICRPTR, CCameraCtrlLogic );
	REG_GOBAL_MEMBER_FUNC( "CCameraLogic::OnBtnSwitchAutoExposure", CCameraCtrlLogic::OnBtnSwitchAutoExposure, CAMERALOGICRPTR, CCameraCtrlLogic );
	REG_GOBAL_MEMBER_FUNC( "CCameraLogic::OnSliderApertureChanged", CCameraCtrlLogic::OnSliderApertureChanged, CAMERALOGICRPTR, CCameraCtrlLogic );
	REG_GOBAL_MEMBER_FUNC( "CCameraLogic::OnBtnSwitchAutoWB", CCameraCtrlLogic::OnBtnSwitchAutoWB, CAMERALOGICRPTR, CCameraCtrlLogic );
	REG_GOBAL_MEMBER_FUNC( "CCameraLogic::OnSliderRGainChanged", CCameraCtrlLogic::OnSliderRGainChanged, CAMERALOGICRPTR, CCameraCtrlLogic );
	REG_GOBAL_MEMBER_FUNC( "CCameraLogic::OnSliderBGainChanged", CCameraCtrlLogic::OnSliderBGainChanged, CAMERALOGICRPTR, CCameraCtrlLogic );
	REG_GOBAL_MEMBER_FUNC( "CCameraLogic::OnBtnRadioLamp", CCameraCtrlLogic::OnBtnRadioLamp, CAMERALOGICRPTR, CCameraCtrlLogic );
	REG_GOBAL_MEMBER_FUNC( "CCameraLogic::OnBtnRadioSun", CCameraCtrlLogic::OnBtnRadioSun, CAMERALOGICRPTR, CCameraCtrlLogic );
	REG_GOBAL_MEMBER_FUNC( "CCameraLogic::OnBtnRadioManuel", CCameraCtrlLogic::OnBtnRadioManuel, CAMERALOGICRPTR, CCameraCtrlLogic );
	REG_GOBAL_MEMBER_FUNC( "CCameraLogic::OnBtnGammaOnClick", CCameraCtrlLogic::OnBtnGammaOnClick, CAMERALOGICRPTR, CCameraCtrlLogic );
	REG_GOBAL_MEMBER_FUNC( "CCameraLogic::OnBtnGammaOffClick", CCameraCtrlLogic::OnBtnGammaOffClick, CAMERALOGICRPTR, CCameraCtrlLogic );
	REG_GOBAL_MEMBER_FUNC( "CCameraLogic::OnBtnSmart1Click", CCameraCtrlLogic::OnBtnSmart1Click, CAMERALOGICRPTR, CCameraCtrlLogic );
	REG_GOBAL_MEMBER_FUNC( "CCameraLogic::OnBtnSmart2Click", CCameraCtrlLogic::OnBtnSmart2Click, CAMERALOGICRPTR, CCameraCtrlLogic );
	REG_GOBAL_MEMBER_FUNC( "CCameraLogic::OnSliderPicSceAptChanged", CCameraCtrlLogic::OnSliderPicSceAptChanged, CAMERALOGICRPTR, CCameraCtrlLogic );
	REG_GOBAL_MEMBER_FUNC( "CCameraLogic::OnSliderContrastChanged", CCameraCtrlLogic::OnSliderContrastChanged, CAMERALOGICRPTR, CCameraCtrlLogic );
	REG_GOBAL_MEMBER_FUNC( "CCameraLogic::OnSliderSaturatChanged", CCameraCtrlLogic::OnSliderSaturatChanged, CAMERALOGICRPTR, CCameraCtrlLogic );
	REG_GOBAL_MEMBER_FUNC( "CCameraLogic::OnSliderHueChanged", CCameraCtrlLogic::OnSliderHueChanged, CAMERALOGICRPTR, CCameraCtrlLogic );
	REG_GOBAL_MEMBER_FUNC( "CCameraLogic::OnSliderBrightChanged", CCameraCtrlLogic::OnSliderBrightChanged, CAMERALOGICRPTR, CCameraCtrlLogic );
	REG_GOBAL_MEMBER_FUNC( "CCameraLogic::OnBtnNROffClick", CCameraCtrlLogic::OnBtnNROffClick, CAMERALOGICRPTR, CCameraCtrlLogic );
	REG_GOBAL_MEMBER_FUNC( "CCameraLogic::OnBtnNRLowClick", CCameraCtrlLogic::OnBtnNRLowClick, CAMERALOGICRPTR, CCameraCtrlLogic );
	REG_GOBAL_MEMBER_FUNC( "CCameraLogic::OnBtnNRMidClick", CCameraCtrlLogic::OnBtnNRMidClick, CAMERALOGICRPTR, CCameraCtrlLogic );
	REG_GOBAL_MEMBER_FUNC( "CCameraLogic::OnBtnNRHighClick", CCameraCtrlLogic::OnBtnNRHighClick, CAMERALOGICRPTR, CCameraCtrlLogic );
	REG_GOBAL_MEMBER_FUNC( "CCameraLogic::OnBtnSwitch3DNRClick", CCameraCtrlLogic::OnBtnSwitch3DNRClick, CAMERALOGICRPTR, CCameraCtrlLogic );
	REG_GOBAL_MEMBER_FUNC( "CCameraLogic::OnComboboxExposureGainClick", CCameraCtrlLogic::OnComboboxExposureGainClick, CAMERALOGICRPTR, CCameraCtrlLogic );
	REG_GOBAL_MEMBER_FUNC( "CCameraLogic::OnComboboxShutClick", CCameraCtrlLogic::OnComboboxShutClick, CAMERALOGICRPTR, CCameraCtrlLogic );
	REG_GOBAL_MEMBER_FUNC( "CCameraLogic::OnComboboxBackLightClick", CCameraCtrlLogic::OnComboboxBackLightClick, CAMERALOGICRPTR, CCameraCtrlLogic );
	REG_GOBAL_MEMBER_FUNC( "CCameraLogic::OnEdtApertureChange", CCameraCtrlLogic::OnEdtApertureChange, CAMERALOGICRPTR, CCameraCtrlLogic );
	REG_GOBAL_MEMBER_FUNC( "CCameraLogic::OnKillFocusEdtAperture", CCameraCtrlLogic::OnKillFocusEdtAperture, CAMERALOGICRPTR, CCameraCtrlLogic );
	REG_GOBAL_MEMBER_FUNC( "CCameraLogic::OnEdtRGainChange", CCameraCtrlLogic::OnEdtRGainChange, CAMERALOGICRPTR, CCameraCtrlLogic );
	REG_GOBAL_MEMBER_FUNC( "CCameraLogic::OnKillFocusEdtRGain", CCameraCtrlLogic::OnKillFocusEdtRGain, CAMERALOGICRPTR, CCameraCtrlLogic );
	REG_GOBAL_MEMBER_FUNC( "CCameraLogic::OnEdtBGainChange", CCameraCtrlLogic::OnEdtBGainChange, CAMERALOGICRPTR, CCameraCtrlLogic );
	REG_GOBAL_MEMBER_FUNC( "CCameraLogic::OnKillFocusEdtBGain", CCameraCtrlLogic::OnKillFocusEdtBGain, CAMERALOGICRPTR, CCameraCtrlLogic );
	REG_GOBAL_MEMBER_FUNC( "CCameraLogic::OnEdtPicSceAptChange", CCameraCtrlLogic::OnEdtPicSceAptChange, CAMERALOGICRPTR, CCameraCtrlLogic );
	REG_GOBAL_MEMBER_FUNC( "CCameraLogic::OnKillFocusEdtPicSceApt", CCameraCtrlLogic::OnKillFocusEdtPicSceApt, CAMERALOGICRPTR, CCameraCtrlLogic );
	REG_GOBAL_MEMBER_FUNC( "CCameraLogic::OnEdtContrastChange", CCameraCtrlLogic::OnEdtContrastChange, CAMERALOGICRPTR, CCameraCtrlLogic );
	REG_GOBAL_MEMBER_FUNC( "CCameraLogic::OnKillFocusEdtContrast", CCameraCtrlLogic::OnKillFocusEdtContrast, CAMERALOGICRPTR, CCameraCtrlLogic );
	REG_GOBAL_MEMBER_FUNC( "CCameraLogic::OnEdtSaturatChange", CCameraCtrlLogic::OnEdtSaturatChange, CAMERALOGICRPTR, CCameraCtrlLogic );
	REG_GOBAL_MEMBER_FUNC( "CCameraLogic::OnKillFocusEdtSaturat", CCameraCtrlLogic::OnKillFocusEdtSaturat, CAMERALOGICRPTR, CCameraCtrlLogic );
	REG_GOBAL_MEMBER_FUNC( "CCameraLogic::OnEdtHueChange", CCameraCtrlLogic::OnEdtHueChange, CAMERALOGICRPTR, CCameraCtrlLogic );
	REG_GOBAL_MEMBER_FUNC( "CCameraLogic::OnKillFocusEdtHue", CCameraCtrlLogic::OnKillFocusEdtHue, CAMERALOGICRPTR, CCameraCtrlLogic );
	REG_GOBAL_MEMBER_FUNC( "CCameraLogic::OnEdtBrightChange", CCameraCtrlLogic::OnEdtBrightChange, CAMERALOGICRPTR, CCameraCtrlLogic );
	REG_GOBAL_MEMBER_FUNC( "CCameraLogic::OnKillFocusEdtBright", CCameraCtrlLogic::OnKillFocusEdtBright, CAMERALOGICRPTR, CCameraCtrlLogic );
	REG_GOBAL_MEMBER_FUNC( "CCameraLogic::OnEdtZoomChange", CCameraCtrlLogic::OnEdtZoomChange, CAMERALOGICRPTR, CCameraCtrlLogic );
	REG_GOBAL_MEMBER_FUNC( "CCameraLogic::OnEdtZoomKillFocus", CCameraCtrlLogic::OnEdtZoomKillFocus, CAMERALOGICRPTR, CCameraCtrlLogic );
}

void CCameraCtrlLogic::UnRegFunc()
{
	UN_REG_GOBAL_FUNC( "CCameraLogic::InitWnd" );
}

bool CCameraCtrlLogic::InitWnd(  const IArgs & arg )
{
	CLogicBase::InitWnd( arg );

	std::vector<CString> vecCamera;																//�������������������
	vecCamera.push_back("�����1");
	vecCamera.push_back("�����2");
	vecCamera.push_back("�����3");
	UIFACTORYMGR_PTR->SetComboListData( m_strComboboxCamera, vecCamera, m_pWndTree );
	SetCamName( _T("�����1") );

	std::vector<CString> vecExposureGain;														//�����ع���������������
	for ( int nExposureGain = 0; nExposureGain < 43; nExposureGain += 3 )
	{
		CString strExposureGain;
		strExposureGain.Format( "%ddB", nExposureGain );
		vecExposureGain.push_back(strExposureGain);
	}
	UIFACTORYMGR_PTR->SetComboListData( m_strComboboxExposureGain, vecExposureGain, m_pWndTree );  
	UIFACTORYMGR_PTR->SetComboText( m_strComboboxExposureGain, "6dB", m_pWndTree );

	std::vector<CString> vecShut;																//���ÿ�������������
	vecShut.push_back( "1/60" );
	vecShut.push_back( "1/100" );
	vecShut.push_back( "1/250" );
	vecShut.push_back( "1/500" );
	vecShut.push_back( "1/1000" );
	vecShut.push_back( "1/2000" );
	vecShut.push_back( "1/4000" );
	vecShut.push_back( "1/10000" );
	UIFACTORYMGR_PTR->SetComboListData( m_strComboboxShut, vecShut, m_pWndTree );  
	UIFACTORYMGR_PTR->SetComboText( m_strComboboxShut, "1/60", m_pWndTree );

	std::vector<CString> vecBackLight;															//���ñ�������������
	vecBackLight.push_back( "�ر�" );
	for ( int nBackLight = 0; nBackLight < 16; nBackLight++ )
	{
		CString strBackLight;
		strBackLight.Format( "multi%d", nBackLight );
		vecBackLight.push_back(strBackLight);
	}
	vecBackLight.push_back( "center" );
	vecBackLight.push_back( "face detect" );
	UIFACTORYMGR_PTR->SetComboListData( m_strComboboxBackLight, vecBackLight, m_pWndTree );  
	UIFACTORYMGR_PTR->SetComboText( m_strComboboxBackLight, "multi7", m_pWndTree );

	//Bug00173254  -- by xhx 20140123
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
	KillTimer(NULL, g_wCameraTimerID);
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
	if ( strComboText == "�����1" )
	{
		byCameraIndx = 0;
	}
	else if ( strComboText == "�����2" )
	{
		byCameraIndx = 1;
	}
	else if ( strComboText == "�����3" )
	{
		byCameraIndx = 2;
	}

	u16 nRet = COMIFMGRPTR->CamSelCmd( byCameraIndx );
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "ѡ�������������ʧ��" );
	}

	return true;
}

bool CCameraCtrlLogic::OnBtnImportClick( const IArgs& args )
{
	UIFACTORYMGR_PTR->LoadScheme( "SchmImpCommonClean", NULL, g_stcStrImpCommonDlg );
	UIFACTORYMGR_PTR->LoadScheme( "SchImportCamCfg", NULL, g_stcStrImpCommonDlg );
	s32 nDodalResult = UIFACTORYMGR_PTR->Domodal( g_stcStrImpCommonDlg );

	return true;
}

bool CCameraCtrlLogic::OnBtnExportClick( const IArgs& args )
{
	UIFACTORYMGR_PTR->LoadScheme( "SchmExpCommonClean", NULL, g_stcStrExpCommonDlg );
	UIFACTORYMGR_PTR->LoadScheme( "SchExportCameraCfg", NULL, g_stcStrExpCommonDlg );
	s32 nDodalResult = UIFACTORYMGR_PTR->Domodal( g_stcStrExpCommonDlg );	

	return true;
}

bool CCameraCtrlLogic::OnBtnResumeClick( const IArgs& args )
{
	if ( m_pWndTree == NULL )
	{
		return false;
	}

	u16 nRet = COMIFMGRPTR->CamResetCmd();
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "�ָ�Ĭ��������ʧ��" );
		return true;
	}

	MSG_BOX_ONLY_READ( _T("���ڻָ�Ĭ��ֵ�����Եȣ������������ʱ�޷�����") );

	return true;
}

bool CCameraCtrlLogic::OnBtnUpgradeCameraClick( const IArgs& args )
{
	return true;
}

bool CCameraCtrlLogic::OnBtnZoomPlusClick( const IArgs& args )
{
	EmZoom emZoom = emTele;
	
	u16 nRet = COMIFMGRPTR->SetCamZoomCmd( emZoom );
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "Zoom������ʧ��" );
	}
	
	return true;
}

bool CCameraCtrlLogic::OnBtnZoomSubClick( const IArgs& args )
{
	EmZoom emZoom = emWide;
	
	u16 nRet = COMIFMGRPTR->SetCamZoomCmd( emZoom );
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "Zoom������ʧ��" );
	}
	
	return true;
}

bool CCameraCtrlLogic::OnBtnZoomPlusHold( const IArgs& args )
{
	EmZoom emZoom = emTele;
	
	u16 nRet = COMIFMGRPTR->SetCamZoomCmd( emZoom );
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "Zoom������ʧ��" );
	}
	
	return true;
}

bool CCameraCtrlLogic::OnBtnZoomPlusHoldEnd( const IArgs& args )
{
	return true;
}

bool CCameraCtrlLogic::OnBtnZoomSubHold( const IArgs& args )
{
	EmZoom emZoom = emWide;
	
	u16 nRet = COMIFMGRPTR->SetCamZoomCmd( emZoom );
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "Zoom������ʧ��" );
	}
	
	return true;
}

bool CCameraCtrlLogic::OnBtnZoomSubHoldEnd( const IArgs& args )
{
	return true;
}


bool CCameraCtrlLogic::OnBtnSwitchVisualFieldClick( const IArgs& args )
{
	if ( m_pWndTree == NULL )
	{
		return false;
	}

	Value_SwitchState valueSwitchState;
	UIFACTORYMGR_PTR->GetPropertyValue( valueSwitchState, m_strBtnSwitchVisualField, m_pWndTree );

	EmOSDShow emOSDShow;
	if ( valueSwitchState.bState )
	{
		emOSDShow = emOSDOn;
	}
	else
	{
		emOSDShow = emOSDOff;
	}
	
	u16 nRet = COMIFMGRPTR->SetCamOSDCmd( emOSDShow );
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "��OSD����ʾ��Ұ����������ʧ��" );
	}

	return true;
}

bool CCameraCtrlLogic::OnBtnPresetSaveClick( const IArgs& args )
{
	u16 nRet = COMIFMGRPTR->CamPresetSaveCmd();
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "������Ԥ��λ1������ʧ��" );
	}
	return true;
}

bool CCameraCtrlLogic::OnBtnManuelFocusClick( const IArgs& args )
{
	EmFocusMode emFocusMode = emFocusManuel;
	u16 nRet = COMIFMGRPTR->SetCamAutoFocusCmd(emFocusMode);
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "�ֶ�����������ʧ��" );
	}
	return true;
}

bool CCameraCtrlLogic::OnBtnAutoFocusClick( const IArgs& args )
{
	EmFocusMode emFocusMode = emFocusAuto;
	u16 nRet = COMIFMGRPTR->SetCamAutoFocusCmd(emFocusMode);
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "�Զ�����������ʧ��" );
	}
	return true;
}

bool CCameraCtrlLogic::OnLBtnDownFocusNear( const IArgs& args )
{
	EmFocus emFocus = emNear;
	EmCnAction emCnAction = emCnStart;
	
	u16 nRet = COMIFMGRPTR->SetCamFocusCmd( emFocus, emCnAction );
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "��������������ʧ��" );
	}

	return true;
}

bool CCameraCtrlLogic::OnLBtnUpFocusNear( const IArgs& args )
{
	EmFocus emFocus = emNear;
	EmCnAction emCnAction = emCnStop;
	
	u16 nRet = COMIFMGRPTR->SetCamFocusCmd( emFocus, emCnAction );
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "��������������ʧ��" );
	}

	return true;
}

bool CCameraCtrlLogic::OnLBtnDownFocusFar( const IArgs& args )
{
	EmFocus emFocus = emFar;
	EmCnAction emCnAction = emCnStart;
	
	u16 nRet = COMIFMGRPTR->SetCamFocusCmd( emFocus, emCnAction );
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "������Զ������ʧ��" );
	}
	
	return true;
}

bool CCameraCtrlLogic::OnLBtnUpFocusFar( const IArgs& args )
{
	EmFocus emFocus = emFar;
	EmCnAction emCnAction = emCnStop;
	
	u16 nRet = COMIFMGRPTR->SetCamFocusCmd( emFocus, emCnAction );
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "������Զ������ʧ��" );
	}
	
	return true;
}

bool CCameraCtrlLogic::OnBtnSwitchPersetMove( const IArgs& args )
{
	if ( m_pWndTree == NULL )
	{
		return false;
	}
	
	Value_SwitchState valueSwitchState;
	UIFACTORYMGR_PTR->GetPropertyValue( valueSwitchState, m_strBtnSwitchPersetMove, m_pWndTree );

	u16 nRet = COMIFMGRPTR->SetCamPresetMoveCmd( valueSwitchState.bState );
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "��������Ԥ��λ1������ʧ��" );
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
		u16 nRet = COMIFMGRPTR->CamAutoExposureCmd( emExpAuto );
		if ( nRet != NO_ERROR )
		{
			WARNMESSAGE( "�Զ��ع�������ʧ��" );
		}
	}
	else
	{
		u16 nRet = COMIFMGRPTR->CamAutoExposureCmd( emExpManuel );
		if ( nRet != NO_ERROR )
		{
			WARNMESSAGE( "�ֶ��ع�������ʧ��" );
		}
		else
		{
			EmGain emGain;
			GetGainValue( emGain );
			
			u16 nRetGain = COMIFMGRPTR->CamGainCmd( emGain );
			if ( nRetGain != NO_ERROR )
			{
				WARNMESSAGE( "����������ʧ��" );
			}

			EmShutSpd emShutSpd;
			GetShutSpdValue( emShutSpd );
			u16 nRetShutSpd = COMIFMGRPTR->CamShutSpdCmd( emShutSpd );
			if ( nRetShutSpd != NO_ERROR )
			{
				WARNMESSAGE( "����������ʧ��" );
			}

			EmBackLightType emBackLightType;
			u8 byMulti = (u8)(TP_INVALID_INDEX);
			
			GetBackLightValue(emBackLightType, byMulti);
			
			
			u16 nRetBackLight = COMIFMGRPTR->CamBackLightCmd( emBackLightType, byMulti );
			if ( nRetBackLight != NO_ERROR )
			{
				WARNMESSAGE( "����������ʧ��" );
			}

			String strAperture;
			UIFACTORYMGR_PTR->GetCaption( m_strEdtAperture, strAperture, m_pWndTree );
			
			u8 byAperture = atoi(strAperture.c_str());
			u16 nRetAperture = COMIFMGRPTR->CamAperture( byAperture );
			if ( nRetAperture != NO_ERROR )
			{
				WARNMESSAGE( "��Ȧ����������ʧ��" );
			}
		}
	}

	return true;
}

bool CCameraCtrlLogic::OnSliderApertureChanged( const IArgs& args )
{
	if ( m_pWndTree == NULL )
	{
		return false;
	}

	Value_CSliderCtrlPos valueCSliderCtrlPos;
	UIFACTORYMGR_PTR->GetPropertyValue( valueCSliderCtrlPos, m_strSliderAperture, m_pWndTree );

	CString strCaption;
	strCaption.Format( "%d", valueCSliderCtrlPos.nPos );
	Value_WindowCaption valueWindowCaption;
	valueWindowCaption.strCaption = strCaption;
	UIFACTORYMGR_PTR->SetPropertyValue( valueWindowCaption, m_strEdtAperture, m_pWndTree );


	u8 byAperture = valueCSliderCtrlPos.nPos;
	u8 byApertureInLib = 0;
	LIBDATAMGRPTR->GetCamAperture( byApertureInLib );
	if ( byAperture == byApertureInLib )
	{
		return true;
	}

	u16 nRet = COMIFMGRPTR->CamAperture( byAperture );
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "��Ȧ����������ʧ��" );
	}

	return true;
}

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
		u16 nRet = COMIFMGRPTR->CamAutoWBCmd( emWBAuto );
		if ( nRet != NO_ERROR )
		{
			WARNMESSAGE( "�Զ���ƽ��������ʧ��" );
		}
	}
	else
	{
		u16 nRet = COMIFMGRPTR->CamAutoWBCmd( emWBManual );
		if ( nRet != NO_ERROR )
		{
			WARNMESSAGE( "�Զ���ƽ��������ʧ��" );
		}

		String strRGain;
		UIFACTORYMGR_PTR->GetCaption( m_strEdtRGain, strRGain, m_pWndTree );
		
		u16 wRGain = atoi(strRGain.c_str());
		u16 nRetRGain = COMIFMGRPTR->CamRGainCmd( wRGain );
		if ( nRetRGain != NO_ERROR )
		{
			WARNMESSAGE( "RGain����������ʧ��" );
		}


		String strBGain;
		UIFACTORYMGR_PTR->GetCaption( m_strEdtBGain, strBGain, m_pWndTree );

		u16 wBGain = atoi(strBGain.c_str());
		u16 nRetBGain = COMIFMGRPTR->CamBGainCmd( wBGain );
		if ( nRetBGain != NO_ERROR )
		{
			WARNMESSAGE( "BGain����������ʧ��" );
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
	
	u16 wRGain = valueCSliderCtrlPos.nPos;
	u16 wRGainInLib = 0;
	LIBDATAMGRPTR->GetCamRGain( wRGainInLib );
	if ( wRGain == wRGainInLib )
	{
		return true;
	}

	u16 nRet = COMIFMGRPTR->CamRGainCmd( wRGain );
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "RGain����������ʧ��" );
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
	
	u16 wBGain = valueCSliderCtrlPos.nPos;
	u16 wBGainInLib = 0;
	LIBDATAMGRPTR->GetCamBGain( wBGainInLib );
	if ( wBGain == wBGainInLib )
	{
		return true;
	}

	u16 nRet = COMIFMGRPTR->CamBGainCmd( wBGain );
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "BGain����������ʧ��" );
	}

	return true;
}

bool CCameraCtrlLogic::OnBtnRadioLamp( const IArgs& args )
{
	if ( m_pWndTree == NULL)
	{
		return false;
	}

	EmPicSceMode emPicSceMode = emLamp;
	u16 nRet = COMIFMGRPTR->CamPicSceneModeCmd( emPicSceMode );
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "�չ��ģʽ������ʧ��" );//ʧ��ʱ�ָ�ԭ����ButtonCheck״̬
	}

	UIFACTORYMGR_PTR->LoadScheme( _T("SchPicSceneModeLamp"), m_pWndTree );

	return true;
}

bool CCameraCtrlLogic::OnBtnRadioSun( const IArgs& args )
{
	if ( m_pWndTree == NULL )
	{
		return false;
	}

	EmPicSceMode emPicSceMode = emSun;
	u16 nRet = COMIFMGRPTR->CamPicSceneModeCmd( emPicSceMode );
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "̫����ģʽ������ʧ��" );
	}

	UIFACTORYMGR_PTR->LoadScheme( _T("SchPicSceneModeSun"), m_pWndTree );

	return true;
}

bool CCameraCtrlLogic::OnBtnRadioManuel( const IArgs& args )
{
	if ( m_pWndTree == NULL )
	{
		return false;
	}

	EmPicSceMode emPicSceMode = emManuel;
	u16 nRet = COMIFMGRPTR->CamPicSceneModeCmd( emPicSceMode );
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "�ֶ�ģʽ������ʧ��" );
	}

	UIFACTORYMGR_PTR->LoadScheme( _T("SchPicSceneModeManuel"), m_pWndTree );

	return true;
}

bool CCameraCtrlLogic::OnBtnGammaOnClick( const IArgs& args )
{
	EmGamma emGamma = emGammaOn;
	u16 nRet = COMIFMGRPTR->CamGammaCmd( emGamma );
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "Gamma On������ʧ��" );
	}

	return true;
}

bool CCameraCtrlLogic::OnBtnGammaOffClick( const IArgs& args )
{
	EmGamma emGamma = emGammaOff;
	u16 nRet = COMIFMGRPTR->CamGammaCmd( emGamma );
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "Gamma Off������ʧ��" );
	}

	return true;
}

bool CCameraCtrlLogic::OnBtnSmart1Click( const IArgs& args )
{
	EmGamma emGamma = emSmart1;
	u16 nRet = COMIFMGRPTR->CamGammaCmd( emGamma );
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "Gamma Smart1������ʧ��" );
	}

	return true;
}

bool CCameraCtrlLogic::OnBtnSmart2Click( const IArgs& args )
{
	EmGamma emGamma = emSmart2;
	u16 nRet = COMIFMGRPTR->CamGammaCmd( emGamma );
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "Gamma Smart2������ʧ��" );
	}

	return true;
}

bool CCameraCtrlLogic::OnSliderPicSceAptChanged( const IArgs& args )
{
	if ( m_pWndTree == NULL )
	{
		return false;
	}

	Value_CSliderCtrlPos valueCSliderCtrlPos;
	UIFACTORYMGR_PTR->GetPropertyValue( valueCSliderCtrlPos, m_strSliderPicSceApt, m_pWndTree );
	
	SetPicSceAptValue( valueCSliderCtrlPos.nPos );

	u8 byPicSceApt = valueCSliderCtrlPos.nPos;
	u8 byPicSceAptInLib = 0;
	LIBDATAMGRPTR->GetCamPicSceApt( byPicSceAptInLib );
	if ( byPicSceApt == byPicSceAptInLib )
	{
		return true;
	}

	u16 nRet = COMIFMGRPTR->CamPicSceAptCmd( byPicSceApt );
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "ģʽ��Ȧ����������ʧ��" );
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

	u16 wContrast = valueCSliderCtrlPos.nPos;
	u16 wContrastInLib = 0;
	LIBDATAMGRPTR->GetCamContrast( wContrastInLib );
	if ( wContrast == wContrastInLib )
	{
		return true;
	}

	u16 nRet = COMIFMGRPTR->CamContrastCmd( wContrast );
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "�Աȶ�������ʧ��" );
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

	u16 wSaturat = valueCSliderCtrlPos.nPos;
	u16 wSaturatInLib = 0;
	LIBDATAMGRPTR->GetCamSaturat( wSaturatInLib );
	if ( wSaturat == wSaturatInLib )
	{
		return true;
	}

	u16 nRet = COMIFMGRPTR->CamSaturatCmd( wSaturat );
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "���Ͷ�������ʧ��" );
	}

	return true;
}

bool CCameraCtrlLogic::OnSliderHueChanged( const IArgs& args )
{
	if ( m_pWndTree == NULL )
	{
		return false;
	}

	Value_CSliderCtrlPos valueCSliderCtrlPos;
	UIFACTORYMGR_PTR->GetPropertyValue( valueCSliderCtrlPos, m_strSliderHue, m_pWndTree );
	
	SetHueValue( valueCSliderCtrlPos.nPos );

	u16 wHue = valueCSliderCtrlPos.nPos;
	u16 wHueInLib = 0;
	LIBDATAMGRPTR->GetCamHue( wHueInLib );
	if ( wHue == wHueInLib )
	{
		return true;
	}

	u16 nRet = COMIFMGRPTR->CamHueCmd( wHue );
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "ɫ��������ʧ��" );
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

	u16 wBright = valueCSliderCtrlPos.nPos;
	u16 wBrightInLib = 0;
	LIBDATAMGRPTR->GetCamBright( wBrightInLib );
	if ( wBright == wBrightInLib )
	{
		return true;
	}

	u16 nRet = COMIFMGRPTR->CamBrightCmd( wBright );
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "����������ʧ��" );
	}

	return true;
}

bool CCameraCtrlLogic::OnBtnNROffClick( const IArgs& args )
{
	EmStmClean emStmClean = emNRoff;
	u16 nRet = COMIFMGRPTR->CamNRStmCleanCmd( emStmClean );
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "������� off������ʧ��" );
	}

	return true;
}

bool CCameraCtrlLogic::OnBtnNRLowClick( const IArgs& args )
{
	EmStmClean emStmClean = emNRlow;
	u16 nRet = COMIFMGRPTR->CamNRStmCleanCmd( emStmClean );
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "������� low������ʧ��" );
	}

	return true;
}

bool CCameraCtrlLogic::OnBtnNRMidClick( const IArgs& args )
{
	EmStmClean emStmClean = emNRmid;
	u16 nRet = COMIFMGRPTR->CamNRStmCleanCmd( emStmClean );
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "������� mid������ʧ��" );
	}

	return true;
}

bool CCameraCtrlLogic::OnBtnNRHighClick( const IArgs& args )
{
	EmStmClean emStmClean = emNRhigh;
	u16 nRet = COMIFMGRPTR->CamNRStmCleanCmd( emStmClean );
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "������� high������ʧ��" );
	}

	return true;
}

bool CCameraCtrlLogic::OnBtnSwitch3DNRClick( const IArgs& args )
{
	if ( m_pWndTree == NULL )
	{
		return false;
	}
	
	Value_SwitchState valueSwitchState;
	UIFACTORYMGR_PTR->GetPropertyValue( valueSwitchState, m_strBtnSwitch3DNR, m_pWndTree );
	
	Em3DNR em3DNR;
	if ( valueSwitchState.bState )
	{
		em3DNR = em3DNROn;
	}
	else
	{
		em3DNR = em3DNROff;
	}
	
	u16 nRet = COMIFMGRPTR->Cam3DNRCmd( em3DNR );
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "3D DNR������ʧ��" );
	}
	
	return true;
}

HRESULT CCameraCtrlLogic::OnCameraCfgNty( WPARAM wparam, LPARAM lparam )
{
	if ( m_bIsCameraPowerOn && m_bLoginByOther )
	{
		m_bLoginByOther = false;
		KillTimer(NULL, g_wCameraTimerID);
	    ResetNormal();
	}

	TCnCameraCfg tCnCameraCfg;
	LIBDATAMGRPTR->GetCamCfg( tCnCameraCfg );
	SetCameraCfg( tCnCameraCfg );

	return S_OK;
}

HRESULT CCameraCtrlLogic::OnCameraSelectInd( WPARAM wparam, LPARAM lparam )
{
	BOOL bRet = static_cast<BOOL>(lparam);
	if ( bRet == FALSE )
	{
		WARNMESSAGE( _T("ѡ�����������ʧ��") );
	}

	TCnCameraCfg tCnCameraCfg;
	LIBDATAMGRPTR->GetCamCfg( tCnCameraCfg );
	SetCameraCfg( tCnCameraCfg );

	//m_bNty = true;
	
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
		WARNMESSAGE( "Zoom����ʧ��");
		return S_OK;
	}

	return S_OK;
}

HRESULT CCameraCtrlLogic::OnCameraOSDShowInd( WPARAM wparam, LPARAM lparam )
{
	if ( m_pWndTree == NULL )
	{
		return S_FALSE;
	}

	EmOSDShow emOSDShow;
	LIBDATAMGRPTR->GetCamOSD( emOSDShow );
	BOOL bRet = static_cast<BOOL>(lparam);

	Value_SwitchState valueSwitchState;
	if ( bRet == FALSE )
	{
		WARNMESSAGE( "OSDShow����ʧ��");
	}

	SetOSDShowValue( emOSDShow );

	return S_OK;
}

HRESULT CCameraCtrlLogic::OnCameraAutoFocusInd( WPARAM wparam, LPARAM lparam )
{
	EmFocusMode emFocusMode = static_cast<EmFocusMode>(wparam);
	BOOL bRet = static_cast<BOOL>(lparam);

	if ( bRet == FALSE )
	{
		SetCursorPos( 710, 530 );//20130326-�����������ܵ������

		WARNMESSAGE( "�Զ���������ʧ��" );
	}

	return S_OK;
}

HRESULT CCameraCtrlLogic::OnCameraFocusInd( WPARAM wparam, LPARAM lparam )
{
	EmFocus emFocus = static_cast<EmFocus>(wparam);
	BOOL bRet = static_cast<BOOL>(lparam);

	if ( bRet == FALSE )
	{
		WARNMESSAGE( "��������ʧ��" );
	}
	return S_OK;
}

HRESULT CCameraCtrlLogic::OnCameraPersetMoveInd( WPARAM wparam, LPARAM lparam )
{
	if ( m_pWndTree == NULL )
	{
		return S_FALSE;
	}
	
	BOOL bUsed;
	LIBDATAMGRPTR->GetCamPresetMove( bUsed );
	BOOL bRet = static_cast<BOOL>(lparam);
	
	if ( bRet == FALSE )
	{
		WARNMESSAGE( "������Ԥ��λ1����ʧ��");
	}

	SetPresetValue( bUsed );
	
	return S_OK;
}

HRESULT CCameraCtrlLogic::OnCameraAutoExposureInd( WPARAM wparam, LPARAM lparam )
{
	if ( m_pWndTree == NULL )
	{
		return S_FALSE;
	}

	EmExpMode emExpMode;
	LIBDATAMGRPTR->GetCamExpMode( emExpMode );
	BOOL bRet = static_cast<BOOL>(lparam);

	if ( bRet == FALSE )
	{
		WARNMESSAGE( "�Զ��ع�����ʧ��" );
	}

	SetAutoExp(emExpMode);


	return S_OK;
}

bool CCameraCtrlLogic::OnComboboxExposureGainClick( const IArgs& args )
{
	EmGain emGain;
	GetGainValue( emGain );
	
	u16 nRet = COMIFMGRPTR->CamGainCmd( emGain );
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "����������ʧ��" );
	}
	return true;
}

bool CCameraCtrlLogic::OnComboboxShutClick( const IArgs& args )
{
	EmShutSpd emShutSpd;
	GetShutSpdValue( emShutSpd );
	u16 nRet = COMIFMGRPTR->CamShutSpdCmd( emShutSpd );
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "����������ʧ��" );
	}
	return true;
}

HRESULT CCameraCtrlLogic::OnCameraGainInd( WPARAM wparam, LPARAM lparam )
{
	if ( m_pWndTree == NULL )
	{
		return S_FALSE;
	}

	EmGain emGain;
	LIBDATAMGRPTR->GetCamGain( emGain );
	BOOL bRet = static_cast<BOOL>(lparam);

	if ( bRet == FALSE )
	{
		WARNMESSAGE( "��������ʧ��" );
	}

	SetExpGainValue( emGain );

	return S_OK;
}

HRESULT CCameraCtrlLogic::OnCameraShutSpdInd( WPARAM wparam, LPARAM lparam )
{
	if ( m_pWndTree == NULL )
	{
		return S_FALSE;
	}

	EmShutSpd emShutSpd;
	LIBDATAMGRPTR->GetCamShutSpd( emShutSpd );
	BOOL bRet = static_cast<BOOL>(lparam);

	if ( bRet == FALSE )
	{
		WARNMESSAGE( "��������ʧ��" );
	}

	SetShutSpdValue(emShutSpd);

	return S_OK;
}

bool CCameraCtrlLogic::OnComboboxBackLightClick( const IArgs& args )
{		
	EmBackLightType emBackLightType;
	u8 byMulti = (u8)(TP_INVALID_INDEX);

	GetBackLightValue(emBackLightType, byMulti);


	u16 nRet = COMIFMGRPTR->CamBackLightCmd( emBackLightType, byMulti );
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "����������ʧ��" );
	}
	return true;
}

HRESULT CCameraCtrlLogic::OnCameraBackLightInd( WPARAM wparam, LPARAM lparam )
{
	if ( m_pWndTree == NULL )
	{
		return S_FALSE;
	}

	BOOL bRet = static_cast<BOOL>(lparam);
	if ( bRet == FALSE )
	{
		WARNMESSAGE( "��������ʧ��" );
	}

	EmBackLightType emBackLightType;
	LIBDATAMGRPTR->GetCamBackLightType( emBackLightType );
	u8 byMulti = 16;
	if ( emBackLightType == emBLmulti )
	{
		LIBDATAMGRPTR->GetCamBackLightIndex( byMulti );
	}

	SetBackLightValue(emBackLightType, byMulti);


	return S_OK;
}

HRESULT CCameraCtrlLogic::OnCameraApertureInd( WPARAM wparam, LPARAM lparam )
{
	if ( m_pWndTree == NULL )
	{
		return S_FALSE;
	}

	u8 byAperture;
	LIBDATAMGRPTR->GetCamAperture( byAperture );
	BOOL bRet = static_cast<BOOL>(lparam);

	if ( bRet == FALSE )
	{
		WARNMESSAGE( "��Ȧ����ʧ��" );
	}

	SetAptValue( byAperture );

	return S_OK;
}

bool CCameraCtrlLogic::OnEdtApertureChange( const IArgs& args )
{
	if ( m_pWndTree == NULL )
	{
		return true;
	}

	Window* pWnd = UIFACTORYMGR_PTR->GetWindowPtr( m_strEdtAperture, m_pWndTree );
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

bool CCameraCtrlLogic::OnKillFocusEdtAperture( const IArgs& args )
{
	String str;
	UIFACTORYMGR_PTR->GetCaption( m_strEdtAperture, str, m_pWndTree );
	
	SetApertureCmd(str.c_str());

	return true;
}

HRESULT CCameraCtrlLogic::OnCameraAutoWBInd( WPARAM wparam, LPARAM lparam )
{
	if ( m_pWndTree == NULL )
	{
		return S_FALSE;
	}
	
	EmWBMode emWBMode;
	LIBDATAMGRPTR->GetCamWBMode( emWBMode );
	BOOL bRet = static_cast<BOOL>(lparam);
	
	if ( bRet == FALSE )
	{
		WARNMESSAGE( "�Զ��ع�����ʧ��" );
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
	
	Window* pWnd = UIFACTORYMGR_PTR->GetWindowPtr( m_strEdtRGain, m_pWndTree );
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
		WARNMESSAGE( "RGain����������ʧ��" );
	}
}

bool CCameraCtrlLogic::OnEdtBGainChange( const IArgs& args )
{
	if ( m_pWndTree == NULL )
	{
		return true;
	}
	
	Window* pWnd = UIFACTORYMGR_PTR->GetWindowPtr( m_strEdtBGain, m_pWndTree );
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
		WARNMESSAGE( "BGain����������ʧ��" );
	}
}

HRESULT CCameraCtrlLogic::OnCameraRGainInd( WPARAM wparam, LPARAM lparam )
{
	if ( m_pWndTree == NULL )
	{
		return S_FALSE;
	}

	u16 wRGain = 0;
	LIBDATAMGRPTR->GetCamRGain( wRGain );
	BOOL bRet = static_cast<BOOL>(lparam);
	
	if ( bRet == FALSE )
	{
		WARNMESSAGE( "RGain����ʧ��" );
	}
	
	SetRGainValue(wRGain);

	
	return S_OK;
}

HRESULT CCameraCtrlLogic::OnCameraBGainInd( WPARAM wparam, LPARAM lparam )
{
	if ( m_pWndTree == NULL )
	{
		return S_FALSE;
	}

	u16 wBGain = 0;
	LIBDATAMGRPTR->GetCamBGain( wBGain );
	BOOL bRet = static_cast<BOOL>(lparam);
	
	if ( bRet == FALSE )
	{
		WARNMESSAGE( "BGain����ʧ��" );
	}
	
	SetBGainValue(wBGain);

	
	return S_OK;
}

HRESULT CCameraCtrlLogic::OnCameraPicSceneModeInd( WPARAM wparam, LPARAM lparam )
{
	if ( m_pWndTree == NULL )
	{
		return S_FALSE;
	}

	EmPicSceMode emPicSceMode;
	LIBDATAMGRPTR->GetCamPicSceneMode(emPicSceMode);
	BOOL bRet = static_cast<BOOL>(lparam);
	if ( bRet == FALSE )
	{
		WARNMESSAGE( "ģʽ����ʧ��" );
	}

	SetPicSceModeValue(emPicSceMode);


	return S_OK;
}

HRESULT CCameraCtrlLogic::OnCameraGammaInd( WPARAM wparam, LPARAM lparam )
{
	EmGamma emGamma;
	LIBDATAMGRPTR->GetCamGamma( emGamma );
	BOOL bRet = static_cast<BOOL>(lparam);
	if ( bRet == FALSE )
	{
		WARNMESSAGE( "Gamma����ʧ��" );
	}

	SetGammaValue(emGamma);


	return S_OK;
}

bool CCameraCtrlLogic::OnEdtPicSceAptChange( const IArgs& args )
{
	if ( m_pWndTree == NULL )
	{
		return true;
	}
	
	Window* pWnd = UIFACTORYMGR_PTR->GetWindowPtr( m_strEdtPicSceApt, m_pWndTree );
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

bool CCameraCtrlLogic::OnKillFocusEdtPicSceApt( const IArgs& args )
{
	String str;
	UIFACTORYMGR_PTR->GetCaption( m_strEdtPicSceApt, str, m_pWndTree );
	
	SetPicSceAptCmd(str.c_str());
	
	return true;
}

void CCameraCtrlLogic::SetPicSceAptCmd( CString str )
{
	int n = atoi( str );
	
	if ( n > MAX_PICSCEAPT_NUMBER )
	{
		n = MAX_PICSCEAPT_NUMBER;
	}
	else if ( n < MIN_PICSCEAPT_NUMBER )
	{
		n = MIN_PICSCEAPT_NUMBER;
	}
	
	u16 nRet = COMIFMGRPTR->CamPicSceAptCmd( n );
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "ģʽ��Ȧ����������ʧ��" );
	}
}

bool CCameraCtrlLogic::OnEdtContrastChange( const IArgs& args )
{
	if ( m_pWndTree == NULL )
	{
		return true;
	}
	
	Window* pWnd = UIFACTORYMGR_PTR->GetWindowPtr( m_strEdtContrast, m_pWndTree );
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
	
	if ( n > 200 )
	{
		n = 200;
	}
	else if ( n < 0 )
	{
		n = 0;
	}
	
	u16 nRet = COMIFMGRPTR->CamContrastCmd( n );
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "�Աȶ�������ʧ��" );
	}
}

bool CCameraCtrlLogic::OnEdtSaturatChange( const IArgs& args )
{
	if ( m_pWndTree == NULL )
	{
		return true;
	}
	
	Window* pWnd = UIFACTORYMGR_PTR->GetWindowPtr( m_strEdtSaturat, m_pWndTree );
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
	
	if ( n > 200 )
	{
		n = 200;
	}
	else if ( n < 0 )
	{
		n = 0;
	}
	
	u16 nRet = COMIFMGRPTR->CamSaturatCmd( n );
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "���Ͷ�������ʧ��" );
	}
}

bool CCameraCtrlLogic::OnEdtHueChange( const IArgs& args )
{
	if ( m_pWndTree == NULL )
	{
		return true;
	}
	
	Window* pWnd = UIFACTORYMGR_PTR->GetWindowPtr( m_strEdtHue, m_pWndTree );
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

bool CCameraCtrlLogic::OnKillFocusEdtHue( const IArgs& args )
{
	String str;
	UIFACTORYMGR_PTR->GetCaption( m_strEdtHue, str, m_pWndTree );
	
	SetHueCmd(str.c_str());
	
	return true;
}

void CCameraCtrlLogic::SetHueCmd( CString str )
{
	int n = atoi( str );
	
	if ( n > 200 )
	{
		n = 200;
	}
	else if ( n < 0 )
	{
		n = 0;
	}
	
	u16 nRet = COMIFMGRPTR->CamHueCmd( n );
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "ɫ��������ʧ��" );
	}
}

bool CCameraCtrlLogic::OnEdtBrightChange( const IArgs& args )
{
	if ( m_pWndTree == NULL )
	{
		return true;
	}
	
	Window* pWnd = UIFACTORYMGR_PTR->GetWindowPtr( m_strEdtBright, m_pWndTree );
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
	
	if ( n > 200 )
	{
		n = 200;
	}
	else if ( n < 0 )
	{
		n = 0;
	}
	
	u16 nRet = COMIFMGRPTR->CamBrightCmd( n );
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "����������ʧ��" );
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

	UIFACTORYMGR_PTR->SetCaption( m_strEdtZoom, (String)str, m_pWndTree );


	Window* pWnd = UIFACTORYMGR_PTR->GetWindowPtr( m_strEdtZoom, m_pWndTree );
	if ( pWnd )
	{
		(( CEdit *) pWnd)->SetSel( -1 );
	}

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


HRESULT CCameraCtrlLogic::OnCameraPicSceAptInd( WPARAM wparam, LPARAM lparam )
{
	if ( m_pWndTree == NULL )
	{
		return S_FALSE;
	}

	u8 byPicSceApt = 0;
	LIBDATAMGRPTR->GetCamPicSceApt( byPicSceApt );
	BOOL bRet = static_cast<BOOL>(lparam);
	if ( bRet == FALSE )
	{
		WARNMESSAGE( _T("ģʽ��Ȧ����ʧ��") );
	}

	SetPicSceAptValue(byPicSceApt);


	return S_OK;
}

HRESULT CCameraCtrlLogic::OnCameraContrastInd( WPARAM wparam, LPARAM lparam )
{
	if ( m_pWndTree == NULL )
	{
		return S_FALSE;
	}

	u16 wContrast = 0;
	LIBDATAMGRPTR->GetCamContrast( wContrast );
	BOOL bRet = static_cast<BOOL>(lparam);
	if ( bRet == FALSE )
	{
		WARNMESSAGE( _T("�Աȶ�����ʧ��") );
	}

	SetContrastValue(wContrast);


	return S_OK;
}

HRESULT CCameraCtrlLogic::OnCameraSaturatInd( WPARAM wparam, LPARAM lparam )
{
	if ( m_pWndTree == NULL )
	{
		return S_FALSE;
	}
	
	u16 wSaturat = 0;
	LIBDATAMGRPTR->GetCamSaturat( wSaturat );
	BOOL bRet = static_cast<BOOL>(lparam);
	if ( bRet == FALSE )
	{
		WARNMESSAGE( _T("���Ͷ�����ʧ��") );
	}
	
	SetSaturatValue(wSaturat);

	
	return S_OK;
}

HRESULT CCameraCtrlLogic::OnCameraHueInd( WPARAM wparam, LPARAM lparam )
{
	if ( m_pWndTree == NULL )
	{
		return S_FALSE;
	}
	
	u16 wHue = 0;
	LIBDATAMGRPTR->GetCamHue( wHue );
	BOOL bRet = static_cast<BOOL>(lparam);
	if ( bRet == FALSE )
	{
		WARNMESSAGE( _T("ɫ������ʧ��") );
	}
	
	SetHueValue(wHue);

	
	return S_OK;
}

HRESULT CCameraCtrlLogic::OnCameraBrightInd( WPARAM wparam, LPARAM lparam )
{
	if ( m_pWndTree == NULL )
	{
		return S_FALSE;
	}
	
	u16 wBright = 0;
	LIBDATAMGRPTR->GetCamBright( wBright );
	BOOL bRet = static_cast<BOOL>(lparam);
	if ( bRet == FALSE )
	{
		WARNMESSAGE( _T("��������ʧ��") );
	}
	
	SetBrightValue(wBright);

	
	return S_OK;
}

HRESULT CCameraCtrlLogic::OnCameraNRStmCleanInd( WPARAM wparam, LPARAM lparam )
{
	EmStmClean emStmClean;
	LIBDATAMGRPTR->GetCamNRStmClean( emStmClean );
	BOOL bRet = static_cast<BOOL>(lparam);
	if ( bRet == FALSE )
	{
		WARNMESSAGE( _T("�����������ʧ��") );
	}

	SetNRStmCleanValue(emStmClean);


	return S_OK;
}

HRESULT CCameraCtrlLogic::OnCamera3DNRInd( WPARAM wparam, LPARAM lparam )
{
	if ( m_pWndTree == NULL )
	{
		return S_FALSE;
	}
	
	Em3DNR em3DNR;
	LIBDATAMGRPTR->GetCam3DNR( em3DNR );
	BOOL bRet = static_cast<BOOL>(lparam);
	if ( bRet == FALSE )
	{
		WARNMESSAGE( "3D DNR����ʧ��");
	}

	Set3DNRValue(em3DNR);

	
	return S_OK;
}

HRESULT CCameraCtrlLogic::OnCameraResetInd( WPARAM wparam, LPARAM lparam )
{
	BOOL bRet = static_cast<BOOL>(lparam);
	if ( bRet == FALSE )
	{
		CMsgboxDlgLogic::GetSingletonPtr()->Clear();
		WARNMESSAGE( _T("�ָ�Ĭ������ʧ��") );
	}
	else
	{
		CMsgboxDlgLogic::GetSingletonPtr()->Clear();
		WARNMESSAGE( _T("�ָ�Ĭ�����óɹ�") );

		TCnCameraCfg tCnCameraCfg;
		LIBDATAMGRPTR->GetCamCfg( tCnCameraCfg );
		SetCameraCfg( tCnCameraCfg );
	}

	return S_OK;
}

HRESULT CCameraCtrlLogic::OnCameraPersetSaveInd( WPARAM wparam, LPARAM lparam )
{
	BOOL bRet = static_cast<BOOL>(lparam);
	if ( bRet == FALSE )
	{
		SetCursorPos( 710, 530 );//20130326-�����������ܵ������
		WARNMESSAGE( _T("Ԥ��λ��������ʧ��") );
	}
	
	return S_OK;
}

void CCameraCtrlLogic::SetCameraCfg( TCnCameraCfg tCnCameraCfg )
{
	CString strCaption;
	Value_SwitchState valueSwitchState;
	Value_TransparentComboBoxText valueTransparentComboBoxText;

	//���������
	u8 byCameraIndex = 0;
	LIBDATAMGRPTR->GetCamSel( byCameraIndex );
	switch ( byCameraIndex )
	{
	case 0:
		{
			strCaption = _T("�����1");
			break;
		}
	case 1:
		{
			strCaption = _T("�����2");
			break;
		}
	case 2:
		{
			strCaption = _T("�����3");
			break;
		}
	default:
		break;
	}
	
	SetCamName(strCaption);

	SetZoomValue( ((float)tCnCameraCfg.wZoom)/100 );
	
	//����Ұ����ʾ����
	SetOSDShowValue( tCnCameraCfg.emOSDShow );


	//��������Ԥ��λ1
	SetPresetValue( tCnCameraCfg.bUsed );

	//�ع�
	SetAutoExp( tCnCameraCfg.emExpMode );
	SetExpGainValue( tCnCameraCfg.emGain );
	SetShutSpdValue( tCnCameraCfg.emShutSpd );
	SetBackLightValue( tCnCameraCfg.emBackLightType, tCnCameraCfg.byMulti );
	SetAptValue( tCnCameraCfg.byApt );

	//��ƽ��
	SetAutoWB( tCnCameraCfg.emWBMode );
	SetRGainValue( tCnCameraCfg.wRGain );
	SetBGainValue( tCnCameraCfg.wBGain );

	//ģʽ
	SetPicSceModeValue( tCnCameraCfg.emPicMode );
	SetGammaValue( tCnCameraCfg.emGamma );
	SetPicSceAptValue( tCnCameraCfg.byPicApt );

	//ͼƬ����
	SetContrastValue( tCnCameraCfg.wContrast );
	SetSaturatValue( tCnCameraCfg.wSaturat );
	SetHueValue( tCnCameraCfg.wHue );
	SetBrightValue( tCnCameraCfg.wBright );

	//����
	SetNRStmCleanValue( tCnCameraCfg.emStmClean );
	Set3DNRValue( tCnCameraCfg.em3DNR );

	return;
}

void CCameraCtrlLogic::GetBackLightValue( EmBackLightType &emBackLightType, u8 &byMulti )
{
	if ( m_pWndTree == NULL )
	{
		return;
	}

	Value_TransparentComboBoxText valueTransparentComboBoxText;
	UIFACTORYMGR_PTR->GetPropertyValue( valueTransparentComboBoxText, m_strComboboxBackLight, m_pWndTree );
	
	String strComboText = valueTransparentComboBoxText.strComboText;
	if ( strComboText == "�ر�" )
	{
		byMulti = 16;
		emBackLightType = emBLOff;
	}
	else if ( strComboText == "multi0" )
	{
		byMulti = 0;
		emBackLightType = emBLmulti;
	}
	else if ( strComboText == "multi1" )
	{
		byMulti = 1;
		emBackLightType = emBLmulti;
	}
	else if ( strComboText == "multi2" )
	{
		byMulti = 2;
		emBackLightType = emBLmulti;
	}
	else if ( strComboText == "multi3" )
	{
		byMulti = 3;
		emBackLightType = emBLmulti;
	}
	else if ( strComboText == "multi4" )
	{
		byMulti = 4;
		emBackLightType = emBLmulti;
	}
	else if ( strComboText == "multi5" )
	{
		byMulti = 5;
		emBackLightType = emBLmulti;
	}
	else if ( strComboText == "multi6" )
	{
		byMulti = 6;
		emBackLightType = emBLmulti;
	}
	else if ( strComboText == "multi7" )
	{
		byMulti = 7;
		emBackLightType = emBLmulti;
	}
	else if ( strComboText == "multi8" )
	{
		byMulti = 8;
		emBackLightType = emBLmulti;
	}
	else if ( strComboText == "multi9" )
	{
		byMulti = 9;
		emBackLightType = emBLmulti;
	}
	else if ( strComboText == "multi10" )
	{
		byMulti = 10;
		emBackLightType = emBLmulti;
	}
	else if ( strComboText == "multi11" )
	{
		byMulti = 11;
		emBackLightType = emBLmulti;
	}
	else if ( strComboText == "multi12" )
	{
		byMulti = 12;
		emBackLightType = emBLmulti;
	}
	else if ( strComboText == "multi13" )
	{
		byMulti = 13;
		emBackLightType = emBLmulti;
	}
	else if ( strComboText == "multi14" )
	{
		byMulti = 14;
		emBackLightType = emBLmulti;
	}
	else if ( strComboText == "multi15" )
	{
		byMulti = 15;
		emBackLightType = emBLmulti;
	}
	else if ( strComboText == "center" )
	{
		byMulti = 16;
		emBackLightType = emBLcenter;
	}
	else if ( strComboText == "face detect" )
	{
		byMulti = 16;
		emBackLightType = emBLfacedetect;
	}
}

void CCameraCtrlLogic::GetShutSpdValue( EmShutSpd &emShutSpd )
{
	if ( m_pWndTree == NULL )
	{
		return;
	}
	
	Value_TransparentComboBoxText valueTransparentComboBoxText;
	UIFACTORYMGR_PTR->GetPropertyValue( valueTransparentComboBoxText, m_strComboboxShut, m_pWndTree );
	
	String strComboText = valueTransparentComboBoxText.strComboText;
	if ( strComboText == "1/60" )
	{
		emShutSpd = emShutSpd0;
	}
	else if ( strComboText == "1/100" )
	{
		emShutSpd = emShutSpd1;
	}
	else if ( strComboText == "1/250" )
	{
		emShutSpd = emShutSpd2;
	}
	else if ( strComboText == "1/500" )
	{
		emShutSpd = emShutSpd3;
	}
	else if ( strComboText == "1/1000" )
	{
		emShutSpd = emShutSpd4;
	}
	else if ( strComboText == "1/2000" )
	{
		emShutSpd = emShutSpd5;
	}
	else if ( strComboText == "1/4000" )
	{
		emShutSpd = emShutSpd6;
	}
	else if ( strComboText == "1/10000" )
	{
		emShutSpd = emShutSpd7;
	}
}

void CCameraCtrlLogic::SetShutSpdValue( EmShutSpd emShutSpd )
{
	Value_TransparentComboBoxText valueTransparentComboBoxText;

	switch ( emShutSpd )
	{
	case emShutSpd0:
		{
			valueTransparentComboBoxText.strComboText = "1/60"; 
			break;
		}
	case emShutSpd1:
		{
			valueTransparentComboBoxText.strComboText = "1/100"; 
			break;
		}
	case emShutSpd2:
		{
			valueTransparentComboBoxText.strComboText = "1/250"; 
			break;
		}
	case emShutSpd3:
		{
			valueTransparentComboBoxText.strComboText = "1/500"; 
			break;
		}
	case emShutSpd4:
		{
			valueTransparentComboBoxText.strComboText = "1/1000"; 
			break;
		}
	case emShutSpd5:
		{
			valueTransparentComboBoxText.strComboText = "1/2000"; 
			break;
		}
	case emShutSpd6:
		{
			valueTransparentComboBoxText.strComboText = "1/4000"; 
			break;
		}
	case emShutSpd7:
		{
			valueTransparentComboBoxText.strComboText = "1/10000"; 
			break;
		}
	default:
		break;
	}

	UIFACTORYMGR_PTR->SetPropertyValue( valueTransparentComboBoxText, m_strComboboxShut, m_pWndTree );
}

void CCameraCtrlLogic::GetGainValue( EmGain &emGain )
{
	if ( m_pWndTree == NULL )
	{
		return;
	}

	Value_TransparentComboBoxText valueTransparentComboBoxText;
	UIFACTORYMGR_PTR->GetPropertyValue( valueTransparentComboBoxText, m_strComboboxExposureGain, m_pWndTree );
	
	
	String strComboText = valueTransparentComboBoxText.strComboText;
	if ( strComboText == "0dB" )
	{
		emGain = em0dB;
	}
	else if ( strComboText == "3dB" )
	{
		emGain = em3dB;
	}
	else if ( strComboText == "6dB" )
	{
		emGain = em6dB;
	}
	else if ( strComboText == "9dB" )
	{
		emGain = em9dB;
	}
	else if ( strComboText == "12dB" )
	{
		emGain = em12dB;
	}
	else if ( strComboText == "15dB" )
	{
		emGain = em15dB;
	}
	else if ( strComboText == "18dB" )
	{
		emGain = em18dB;
	}
	else if ( strComboText == "21dB" )
	{
		emGain = em21dB;
	}
	else if ( strComboText == "24dB" )
	{
		emGain = em24dB;
	}
	else if ( strComboText == "27dB" )
	{
		emGain = em27dB;
	}
	else if ( strComboText == "30dB" )
	{
		emGain = em30dB;
	}
	else if ( strComboText == "33dB" )
	{
		emGain = em33dB;
	}
	else if ( strComboText == "36dB" )
	{
		emGain = em36dB;
	}
	else if ( strComboText == "39dB" )
	{
		emGain = em39dB;
	}
	else if ( strComboText == "42dB" )
	{
		emGain = em42dB;
	}

};

void CCameraCtrlLogic::SetExpGainValue( EmGain emGain )
{
	Value_TransparentComboBoxText valueTransparentComboBoxText;

	switch ( emGain )
	{
	case em0dB:
		{
			valueTransparentComboBoxText.strComboText = "0dB";
			break;
		}
	case em3dB:
		{
			valueTransparentComboBoxText.strComboText = "3dB";
			break;
		}
	case em6dB:
		{
			valueTransparentComboBoxText.strComboText = "6dB";
			break;
		}
	case em9dB:
		{
			valueTransparentComboBoxText.strComboText = "9dB";
			break;
		}
	case em12dB:
		{
			valueTransparentComboBoxText.strComboText = "12dB";
			break;
		}
	case em15dB:
		{
			valueTransparentComboBoxText.strComboText = "15dB";
			break;
		}
	case em18dB:
		{
			valueTransparentComboBoxText.strComboText = "18dB";
			break;
		}
	case em21dB:
		{
			valueTransparentComboBoxText.strComboText = "21dB";
			break;
		}
	case em24dB:
		{
			valueTransparentComboBoxText.strComboText = "24dB";
			break;
		}
	case em27dB:
		{
			valueTransparentComboBoxText.strComboText = "27dB";
			break;
		}
	case em30dB:
		{
			valueTransparentComboBoxText.strComboText = "30dB";
			break;
		}
	case em33dB:
		{
			valueTransparentComboBoxText.strComboText = "33dB";
			break;
		}
	case em36dB:
		{
			valueTransparentComboBoxText.strComboText = "36dB";
			break;
		}
	case em39dB:
		{
			valueTransparentComboBoxText.strComboText = "39dB";
			break;
		}
	case em42dB:
		{
			valueTransparentComboBoxText.strComboText = "42dB";
			break;
		}
	default:
		break;
	}

	UIFACTORYMGR_PTR->SetPropertyValue( valueTransparentComboBoxText, m_strComboboxExposureGain, m_pWndTree );
}

void CCameraCtrlLogic::SetBackLightValue( EmBackLightType emBackLightType, u8 byMulti )
{
	Value_TransparentComboBoxText valueTransparentComboBoxText;
	switch ( emBackLightType )
	{
	case emBLOff:
		{
			valueTransparentComboBoxText.strComboText = "�ر�";
			break;
		}
	case emBLmulti:
		{
			switch ( byMulti )
			{
			case 0:
				{
					valueTransparentComboBoxText.strComboText = "multi0";
					break;
				}
			case 1:
				{
					valueTransparentComboBoxText.strComboText = "multi1";
					break;
				}
			case 2:
				{
					valueTransparentComboBoxText.strComboText = "multi2";
					break;
				}
			case 3:
				{
					valueTransparentComboBoxText.strComboText = "multi3";
					break;
				}
			case 4:
				{
					valueTransparentComboBoxText.strComboText = "multi4";
					break;
				}
			case 5:
				{
					valueTransparentComboBoxText.strComboText = "multi5";
					break;
				}
			case 6:
				{
					valueTransparentComboBoxText.strComboText = "multi6";
					break;
				}
			case 7:
				{
					valueTransparentComboBoxText.strComboText = "multi7";
					break;
				}
			case 8:
				{
					valueTransparentComboBoxText.strComboText = "multi8";
					break;
				}
			case 9:
				{
					valueTransparentComboBoxText.strComboText = "multi9";
					break;
				}
			case 10:
				{
					valueTransparentComboBoxText.strComboText = "multi10";
					break;
				}
			case 11:
				{
					valueTransparentComboBoxText.strComboText = "multi11";
					break;
				}
			case 12:
				{
					valueTransparentComboBoxText.strComboText = "multi12";
					break;
				}
			case 13:
				{
					valueTransparentComboBoxText.strComboText = "multi13";
					break;
				}
			case 14:
				{
					valueTransparentComboBoxText.strComboText = "multi14";
					break;
				}
			case 15:
				{
					valueTransparentComboBoxText.strComboText = "multi15";
					break;
				}
			default:
				break;
			}
			
			break;
		}
	case emBLcenter:
		{
			valueTransparentComboBoxText.strComboText = "center";
			break;
		}
	case emBLfacedetect:
		{
			valueTransparentComboBoxText.strComboText = "face detect";
			break;
		}
	default:
		break;
	}
	UIFACTORYMGR_PTR->SetPropertyValue( valueTransparentComboBoxText, m_strComboboxBackLight, m_pWndTree );
}

void CCameraCtrlLogic::SetAutoWB( EmWBMode emWBMode )
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

void CCameraCtrlLogic::SetAutoExp( EmExpMode emExpMode )
{
	if ( emExpMode == emExpAuto )
	{
		UIFACTORYMGR_PTR->LoadScheme( "SchAutoExp", m_pWndTree );
	}
	else
	{
		UIFACTORYMGR_PTR->LoadScheme( "SchManuelExp", m_pWndTree );
	}
}

void CCameraCtrlLogic::SetCamName( CString strCaption )
{
	UIFACTORYMGR_PTR->SetComboText( m_strComboboxCamera, (LPCTSTR)strCaption, m_pWndTree );
}

void CCameraCtrlLogic::SetOSDShowValue( EmOSDShow emOSDShow )
{
	Value_SwitchState valueSwitchState;
	if ( emOSDShow == emOSDOn )
	{
		valueSwitchState.bState = true;
	}
	else
	{
		valueSwitchState.bState = false;
	}
	
	UIFACTORYMGR_PTR->SetPropertyValue( valueSwitchState, m_strBtnSwitchVisualField, m_pWndTree );
}

void CCameraCtrlLogic::SetPresetValue( BOOL bUsed )
{
	Value_SwitchState valueSwitchState;
	valueSwitchState.bState = bUsed;
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

void CCameraCtrlLogic::SetRGainValue( u16 wRGain )
{
	Value_CSliderCtrlPos valueCSliderCtrlPos;
	valueCSliderCtrlPos.nPos = wRGain;
	UIFACTORYMGR_PTR->SetPropertyValue( valueCSliderCtrlPos, m_strSliderRGain, m_pWndTree );
	
	CString strCaption;
	strCaption.Format( "%d", wRGain );
	Value_WindowCaption valueWindowCaption;
	valueWindowCaption.strCaption = strCaption;
	UIFACTORYMGR_PTR->SetPropertyValue( valueWindowCaption, m_strEdtRGain, m_pWndTree );

	Window* pWnd = UIFACTORYMGR_PTR->GetWindowPtr( m_strEdtRGain, m_pWndTree );
	if ( pWnd )
	{
		(( CEdit *) pWnd)->SetSel( -1 );
	}
}

void CCameraCtrlLogic::SetBGainValue( u16 wBGain )
{
	Value_CSliderCtrlPos valueCSliderCtrlPos;
	valueCSliderCtrlPos.nPos = wBGain;
	UIFACTORYMGR_PTR->SetPropertyValue( valueCSliderCtrlPos, m_strSliderBGain, m_pWndTree );
	
	CString strCaption;
	strCaption.Format( "%d", wBGain );
	Value_WindowCaption valueWindowCaption;
	valueWindowCaption.strCaption = strCaption;
	UIFACTORYMGR_PTR->SetPropertyValue( valueWindowCaption, m_strEdtBGain, m_pWndTree );

	Window* pWnd = UIFACTORYMGR_PTR->GetWindowPtr( m_strEdtBGain, m_pWndTree );
	if ( pWnd )
	{
		(( CEdit *) pWnd)->SetSel( -1 );
	}
}

void CCameraCtrlLogic::SetPicSceModeValue( EmPicSceMode emPicSceMode )
{
	switch ( emPicSceMode )
	{
	case emLamp:
		{
			UIFACTORYMGR_PTR->LoadScheme( _T("SchPicSceneModeLamp"), m_pWndTree );
			break;
		}
	case emSun:
		{
			UIFACTORYMGR_PTR->LoadScheme( _T("SchPicSceneModeSun"), m_pWndTree );
			break;
		}
	case emManuel:
		{
			UIFACTORYMGR_PTR->LoadScheme( _T("SchPicSceneModeManuel"), m_pWndTree );
			break;
		}
	default:
		break;
	}
}

void CCameraCtrlLogic::SetGammaValue( EmGamma emGamma )
{
	switch ( emGamma )
	{
	case emGammaOn:
		{
			UIFACTORYMGR_PTR->LoadScheme( _T("SchGammaOn"), m_pWndTree );
			break;
		}
	case emGammaOff:
		{
			UIFACTORYMGR_PTR->LoadScheme( _T("SchGammaOff"), m_pWndTree );
			break;
		}
	case emSmart1:
		{
			UIFACTORYMGR_PTR->LoadScheme( _T("SchGammaSmart1"), m_pWndTree );
			break;
		}
	case emSmart2:
		{
			UIFACTORYMGR_PTR->LoadScheme( _T("SchGammaSmart2"), m_pWndTree );
			break;
		}
	default:
		break;
	}
}

void CCameraCtrlLogic::SetPicSceAptValue( u8 byPicSceApt )
{
	Value_CSliderCtrlPos valueCSliderCtrlPos;
	valueCSliderCtrlPos.nPos = byPicSceApt;
	UIFACTORYMGR_PTR->SetPropertyValue( valueCSliderCtrlPos, m_strSliderPicSceApt, m_pWndTree );
	
	CString strCaption;
	strCaption.Format( "%d", byPicSceApt );
	Value_WindowCaption valueWindowCaption;
	valueWindowCaption.strCaption = strCaption;
	UIFACTORYMGR_PTR->SetPropertyValue( valueWindowCaption, m_strEdtPicSceApt, m_pWndTree );

	Window* pWnd = UIFACTORYMGR_PTR->GetWindowPtr( m_strEdtPicSceApt, m_pWndTree );
	if ( pWnd )
	{
		(( CEdit *) pWnd)->SetSel( -1 );
	}
}

void CCameraCtrlLogic::SetContrastValue( u16 wContrast )
{
	Value_CSliderCtrlPos valueCSliderCtrlPos;
	valueCSliderCtrlPos.nPos = wContrast;
	UIFACTORYMGR_PTR->SetPropertyValue( valueCSliderCtrlPos, m_strSliderContrast, m_pWndTree );
	
	CString strCaption;
	strCaption.Format( "%d", wContrast );
	Value_WindowCaption valueWindowCaption;
	valueWindowCaption.strCaption = strCaption;
	UIFACTORYMGR_PTR->SetPropertyValue( valueWindowCaption, m_strEdtContrast, m_pWndTree );

	Window* pWnd = UIFACTORYMGR_PTR->GetWindowPtr( m_strEdtContrast, m_pWndTree );
	if ( pWnd )
	{
		(( CEdit *) pWnd)->SetSel( -1 );
	}
}

void CCameraCtrlLogic::SetSaturatValue( u16 wSaturat )
{
	Value_CSliderCtrlPos valueCSliderCtrlPos;
	valueCSliderCtrlPos.nPos = wSaturat;
	UIFACTORYMGR_PTR->SetPropertyValue( valueCSliderCtrlPos, m_strSliderSaturat, m_pWndTree );
	
	CString strCaption;
	strCaption.Format( "%d", wSaturat );
	Value_WindowCaption valueWindowCaption;
	valueWindowCaption.strCaption = strCaption;
	UIFACTORYMGR_PTR->SetPropertyValue( valueWindowCaption, m_strEdtSaturat, m_pWndTree );

	Window* pWnd = UIFACTORYMGR_PTR->GetWindowPtr( m_strEdtSaturat, m_pWndTree );
	if ( pWnd )
	{
		(( CEdit *) pWnd)->SetSel( -1 );
	}
}

void CCameraCtrlLogic::SetHueValue( u16 wHue )
{
	Value_CSliderCtrlPos valueCSliderCtrlPos;
	valueCSliderCtrlPos.nPos = wHue;
	UIFACTORYMGR_PTR->SetPropertyValue( valueCSliderCtrlPos, m_strSliderHue, m_pWndTree );
	
	CString strCaption;
	strCaption.Format( "%d", wHue );
	Value_WindowCaption valueWindowCaption;
	valueWindowCaption.strCaption = strCaption;
	//UIFACTORYMGR_PTR->SetPropertyValue( valueWindowCaption, m_strEdtHue, m_pWndTree );
	UIFACTORYMGR_PTR->SetCaption( m_strEdtHue, (String)strCaption, m_pWndTree );

	Window* pWnd = UIFACTORYMGR_PTR->GetWindowPtr( m_strEdtHue, m_pWndTree );
	if ( pWnd )
	{
		(( CEdit *) pWnd)->SetSel( -1 );
	}
}

void CCameraCtrlLogic::SetBrightValue( u16 wBright )
{
	Value_CSliderCtrlPos valueCSliderCtrlPos;
	valueCSliderCtrlPos.nPos = wBright;
	UIFACTORYMGR_PTR->SetPropertyValue( valueCSliderCtrlPos, m_strSliderBright, m_pWndTree );
	
	CString strCaption;
	strCaption.Format( "%d", wBright );
	Value_WindowCaption valueWindowCaption;
	valueWindowCaption.strCaption = strCaption;
	UIFACTORYMGR_PTR->SetPropertyValue( valueWindowCaption, m_strEdtBright, m_pWndTree );

	Window* pWnd = UIFACTORYMGR_PTR->GetWindowPtr( m_strEdtBright, m_pWndTree );
	if ( pWnd )
	{
		(( CEdit *) pWnd)->SetSel( -1 );
	}
}

void CCameraCtrlLogic::SetNRStmCleanValue( EmStmClean emStmClean )
{
	switch ( emStmClean )
	{
	case emNRoff:
		{
			UIFACTORYMGR_PTR->LoadScheme( _T("SchNROff"), m_pWndTree );
			break;
		}
	case emNRlow:
		{
			UIFACTORYMGR_PTR->LoadScheme( _T("SchNROffLow"), m_pWndTree );
			break;
		}
	case emNRmid:
		{
			UIFACTORYMGR_PTR->LoadScheme( _T("SchNROffMid"), m_pWndTree );
			break;
		}
	case emNRhigh:
		{
			UIFACTORYMGR_PTR->LoadScheme( _T("SchNROffHigh"), m_pWndTree );
			break;
		}
	default:
		break;
	}
}

void CCameraCtrlLogic::Set3DNRValue( Em3DNR em3DNR )
{
	Value_SwitchState valueSwitchState;
	if ( em3DNR == em3DNROn )
	{
		valueSwitchState.bState = true;
	}
	else
	{
		valueSwitchState.bState = false;
	}
	
	UIFACTORYMGR_PTR->SetPropertyValue( valueSwitchState, m_strBtnSwitch3DNR, m_pWndTree );
}

float CCameraCtrlLogic::StringToFloatTwo( CString str )
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
	// ֻ����������
	int nStringLength = str.GetLength();
	int nDotCount = 0;
	// ���ַ����ܶ���1��
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
	
	// �������������ֺ͵�������ַ�
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
	
	u16 wZoom = 0;
	LIBDATAMGRPTR->GetCamZoom( wZoom );
	BOOL bRet = static_cast<BOOL>(lparam);
	if ( bRet == FALSE )
	{
		WARNMESSAGE( "zoom����ʧ��");
	}
	
	SetZoomValue((float)wZoom/100);

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

void CCameraCtrlLogic::SetZoomCmd( CString str )
{
	float fZoom = StringToFloatTwo( str );
	
	if ( fZoom > 10 )
	{
		fZoom = 10.00;
	}
	else if ( fZoom < 1)
	{
		fZoom = 1.00;
	}
	
	u16 wZoom = (fZoom+1.0e-6)*100;
	u16 nRet = COMIFMGRPTR->SetCamZoomCmd( wZoom );
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "zoom������ʧ��" );
	}
}

void CCameraCtrlLogic::SetApertureCmd( CString str )
{
	int nAperture = atoi( str );
	
	if ( nAperture > 100 )
	{
		nAperture = 100;
	}
	else if ( nAperture < 0)
	{
		nAperture = 0;
	}
	
	u16 nRet = COMIFMGRPTR->CamAperture( nAperture );
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "��Ȧ����������ʧ��" );
	}
}

HRESULT CCameraCtrlLogic::OnCameraPowerOnNty( WPARAM wparam, LPARAM lparam )
{
	if ( NULL == m_pWndTree )
	{
		return S_FALSE;
	}

	m_bLoginByOther = static_cast<BOOL>(lparam);
	m_bIsCameraPowerOn = true;

	WARNMESSAGE( "��������ϵ磬Ӳ����Ҫ�����Ӳ��ܲ��� " );

	KillTimer(NULL, g_wCameraTimerID);
	g_wCameraTimerID = SetTimer( NULL, 1, 120000, CBCameraTimerFun );

	UIFACTORYMGR_PTR->LoadScheme( "SchmEnable", m_pWndTree );
	
	return S_OK;
}

VOID CALLBACK CBCameraTimerFun( HWND hwnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime )
{  
	KillTimer(NULL, g_wCameraTimerID);
	CAMERALOGICRPTR->ResetNormal();
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
