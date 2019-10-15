#pragma once

#ifndef _EVRKCLIB_20180920_H_
#define _EVRKCLIB_20180920_H_



//rkcLib����Ϣ����
enum EmUiRkcMsg
{

#define UI_RKC_MSG_BEGIN  	2000 + 0x1 

	/************************************************************************/
	/** ���� 
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UIRkConnect	= UI_RKC_MSG_BEGIN,
#define	UI_RKC_CONNECTED  ev_UIRkConnect
	
	/************************************************************************/
	/** �ѶϿ�
	wParam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UIRkDisconnected,
#define UI_RKC_DISCONNECTED	 ev_UIRkDisconnected

    /************************************************************************/
	/** ����
	wParam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UIRkReBoot,
#define UI_RKC_REBOOT	 ev_UIRkReBoot

    /************************************************************************/
	/** �ָ���������
	wParam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UIRkRestore,
#define UI_RKC_RESTONE	 ev_UIRkRestore

    /************************************************************************/
	/** ˢ�������б�
	wParam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UIRkDevReflesh,
#define UI_RKC_RKDEV_REFLESH    ev_UIRkDevReflesh

    /************************************************************************/
	/** �������������
	wParam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UISearchFinish,
#define UI_RKC_SEARCH_FINISH    ev_UISearchFinish

     /************************************************************************/
	/** ˢ�¹���ģʽ����
	wParam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UIWorkModeReflesh,
#define UI_RKC_WORKMODE_REFLESH    ev_UIWorkModeReflesh

    /************************************************************************/
	/** ����ģʽ�޸ķ���
	wParam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UIWorkModeChange,
#define UI_RKC_WORKMODE_CHANGE    ev_UIWorkModeChange

    /************************************************************************/
	/** IPУ�鷴��
	wParam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UIIPChecking,
#define UI_RKC_IP_CHECK    ev_UIIPChecking

    /************************************************************************/
	/** ˢ���������ý���
	wParam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UINetWorkReflesh,
#define UI_RKC_NETWORK_REFLESH    ev_UINetWorkReflesh

    /************************************************************************/
	/** ���������޸ķ���
	wParam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UINetWorkChange,
#define UI_RKC_NETWORK_CHANGE    ev_UINetWorkChange

	/************************************************************************/
	/** �޸����뷴��
	wParam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UIRkModifyPassword,
#define UI_RKC_MODIFY_PASSWORD    ev_UIRkModifyPassword

    /************************************************************************/
	/** ���ĵ�Դˢ��
	wParam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UIPowerFlesh,
#define UI_RKC_POWER_FLESH    ev_UIPowerFlesh

    /************************************************************************/
	/** �������»ظ�
	wParam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UIRkUpdateFirstAck,
#define UI_RKC_UPDATE_FIRST_ACK    ev_UIRkUpdateFirstAck

    /************************************************************************/
	/** �������»ظ�notify
	wParam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UIRkUpdateFirstNty,
#define UI_RKC_UPDATE_FIRST_NTY    ev_UIRkUpdateFirstNty

    /************************************************************************/
	/** �������»ظ�notify
	wParam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UIRkUpdateSecondNty,
#define UI_RKC_UPDATE_SECOND_NTY    ev_UIRkUpdateSecondNty

    /************************************************************************/
	/** ����ģʽˢ��
	wParam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UIDebugModeFlesh,
#define UI_RKC_DEBUGMODE_FLESH    ev_UIDebugModeFlesh

    /************************************************************************/
	/** ����ģʽ�޸ķ���
	wParam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UIDebugModeChange,
#define UI_RKC_DEBUGMODE_CHANGE    ev_UIDebugModeChange

    /************************************************************************/
	/** �忨��Ϣ֪ͨ
	wParam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UIBrdInfoNty,
#define UI_RKC_BRDINFO_NTY    ev_UIBrdInfoNty

    ev_UIRkcEnd,
#define	UI_RKC_MSG_END   ev_UIRkcEnd

};

//moontool����Ϣ����
enum EmUiMoontoolMsg
{
#define UI_MOONTOOL_MSG_BEGIN  UI_RKC_MSG_END + 0x1

	/************************************************************************/
	/** ����  MOON90 
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UIMoonToolLoginRsp	= UI_MOONTOOL_MSG_BEGIN,
#define	UI_MOONTOOL_CONNECTED  ev_UIMoonToolLoginRsp

	/************************************************************************/
	/** �ѶϿ�MOON90
	wParam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UIMoonToolDisconnected,
#define UI_MOONTOOL_DISCONNECTED	 ev_UIMoonToolDisconnected

	/************************************************************************/
	/** MOON90������ڽ���������Ϣ֪ͨ 
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UIMoonToolCamInfoNty,
#define	UI_MOONTOOL_CAMINFO_NTY  ev_UIMoonToolCamInfoNty

	/************************************************************************/
	/** MOON90���ν���Zoomֵ֪ͨ���� 
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UIMoonDistortZoomNty,
#define	UI_DISTORTZOOM_NTY  ev_UIMoonDistortZoomNty

	/************************************************************************/
	/** MOON90�����ѡ�����֪ͨ 
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UIMoonToolCamSelectInd,
#define	UI_MOONTOOL_CamSel_IND  ev_UIMoonToolCamSelectInd

	/************************************************************************/
	/** MOON90�������оͬ��֪ͨ 
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UIMoonToolCamParamSyncInd,
#define	UI_MOONTOOL_CamParamSync_IND  ev_UIMoonToolCamParamSyncInd

	/************************************************************************/
	/** MOON90�������оѡ�����֪ͨ 
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UIMoonToolCamStyleSelectInd,
#define	UI_MOONTOOL_CamStyleSel_IND  ev_UIMoonToolCamStyleSelectInd

	/************************************************************************/
	/** ������ڽ���zoomֵ�������ûظ� 
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UIMoonToolCamZoomInd,
#define	UI_MOONTOOL_SET_CAMERA_ZOOM_IND  ev_UIMoonToolCamZoomInd

	/************************************************************************/
	/** ���ν�������zoomֵ�������ûظ� 
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UIMoonToolCamSetZoonStopInd,
#define	UI_MOONTOOL_CAMSETZOON_STOP_IND  ev_UIMoonToolCamSetZoonStopInd

	/************************************************************************/
	/** ������ڽ���zoomֵ�������ûظ� 
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UIMoonToolCamAutoFocusInd,
#define	UI_MOONTOOL_CAMERA_AUTO_FOCUS_IND  ev_UIMoonToolCamAutoFocusInd

	/************************************************************************/
	/** �Ƿ����Զ��ع�ظ� 
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UIMoonToolCamAutoExposureInd,
#define	UI_MOONTOOL_CAMERA_AUTO_EXPOSURE_IND  ev_UIMoonToolCamAutoExposureInd

	/************************************************************************/
	/** �Ƿ����Զ���ƽ��ظ� 
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UIMoonToolCamAutoWBInd,
#define	UI_MOONTOOL_CAMERA_AUTO_WB_IND  ev_UIMoonToolCamAutoWBInd

	/************************************************************************/
	/** ��ƽ��R��ʽ�ظ� 
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UIMoonToolCamRGainInd,
#define	UI_MOONTOOL_CAMERA_RGAIN_IND  ev_UIMoonToolCamRGainInd

	/************************************************************************/
	/** ��ƽ��B��ʽ�ظ� 
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UIMoonToolCamBGainInd,
#define	UI_MOONTOOL_CAMERA_BGAIN_IND  ev_UIMoonToolCamBGainInd

	/************************************************************************/
	/** ���ⲹ���Ƿ�������ظ� 
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UIMoonToolCamBackLightInd,
#define	UI_MOONTOOL_CAMERA_BACKLIGHT_IND  ev_UIMoonToolCamBackLightInd

	/************************************************************************/
	/** �������ý���ظ� 
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UIMoonToolCamNRInd,
#define	UI_MOONTOOL_CAMERA_NR_IND  ev_UIMoonToolCamNRInd

	/************************************************************************/
	/** 2D�������ý���ظ� 
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UIMoonToolCam2DNRInd,
#define	UI_MOONTOOL_CAMERA_2DNR_IND  ev_UIMoonToolCam2DNRInd

	/************************************************************************/
	/** 3D�������ý���ظ� 
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UIMoonToolCam3DNRInd,
#define	UI_MOONTOOL_CAMERA_3DNR_IND  ev_UIMoonToolCam3DNRInd

	/************************************************************************/
	/** �������ý���ظ� 
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UIMoonToolCamInitPresetInd,
#define	UI_MOONTOOL_CAMERA_INITPRESET_IND  ev_UIMoonToolCamInitPresetInd
		
	/************************************************************************/
	/** ���ȵ��ں�֪ͨ���� 
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UIMoonToolImageBLightInd,
#define	UI_MOONTOOL_IMAGE_BLIGHT_IND  ev_UIMoonToolImageBLightInd

	/************************************************************************/
	/** �Աȶȵ��ں�֪ͨ���� 
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UIMoonToolImageContrastInd,
#define	UI_MOONTOOL_IMAGE_CONTRAST_IND  ev_UIMoonToolImageContrastInd

	/************************************************************************/
	/** ɫ�ȵ��ں�֪ͨ���� 
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UIMoonToolImageSharpInd,
#define	UI_MOONTOOL_IMAGE_Sharp_IND  ev_UIMoonToolImageSharpInd

	/************************************************************************/
	/** ���Ͷȵ��ں�֪ͨ���� 
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UIMoonToolImageSaturatInd,
#define	UI_MOONTOOL_IMAGE_SATURAT_IND  ev_UIMoonToolImageSaturatInd
	
	/************************************************************************/
	/** ��Ȧ���ں�֪ͨ���� 
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UIMoonToolCamApertureInd,
#define	UI_MOONTOOL_CAMERA_APERTURE_IND  ev_UIMoonToolCamApertureInd

	/************************************************************************/
	/** ���ŵ��ں�֪ͨ���� 
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UIMoonToolCamShutSpdInd,
#define	UI_MOONTOOL_CAMERA_SHUT_SPD_IND  ev_UIMoonToolCamShutSpdInd

	/************************************************************************/
	/** ������ں�֪ͨ���� 
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UIMoonToolCamGainInd,
#define	UI_MOONTOOL_CAMERA_GAIN_IND  ev_UIMoonToolCamGainInd

	/************************************************************************/
	/** ������ں�֪ͨ���� 
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UIMoonToolImageParaInd,
#define	UI_MOONTOOL_IMAGEPARA_IND  ev_UIMoonToolImageParaInd

	/************************************************************************/
	/** ����У���������֪ͨ���� 
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UIMoonToolCamDistortParamInd,
#define	UI_MOONTOOL_CAMERA_DISTORTPARAM_IND  ev_UIMoonToolCamDistortParamInd

	/************************************************************************/
	/** ������ɫһ�����Զ�����֪ͨ���� 
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UIAutoSetColorConstancyInd,
#define	UI_AUTOSETCOLORCONSTANCY_IND  ev_UIAutoSetColorConstancyInd

	/************************************************************************/
	/** �м�·RGBϵ���ı�ʱ֪ͨ����·RGB�ı�ϵ��֪ͨ���� 
	wparam = 0
	lparam = 0*/
	/************************************************************************/
    ev_UIChangeSideRGBNty,
#define	UI_CHANGESIDERGB_NTY  ev_UIChangeSideRGBNty
	/************************************************************************/
	/** ������ɫһ����RGBֵ֪ͨ���� 
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UISetColorRGBInd,
#define	UI_SETCOLORRGB_IND  ev_UISetColorRGBInd

	/************************************************************************/
	/** ֱ��������ɫһ����RGBֵ֪ͨ���� 
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UIDirectSetColorRGBInd,
#define	UI_DIRECT_SETCOLORRGB_IND  ev_UIDirectSetColorRGBInd

	/************************************************************************/
	/** ���γ�����������֪ͨ���� 
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UIChooseRectangleInd,
#define	UI_CHOOSERECTANGLE_IND  ev_UIChooseRectangleInd

	/************************************************************************/
	/** �ָ�Ĭ����������֪ͨ���� 
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_TpSecDefaultNty,
#define	UI_MoonSecDefault_Nty  ev_TpSecDefaultNty

	/************************************************************************/
	/** ��¼����ڶ�ҳ����֪ͨ���� 
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_TpSecBoundaryNty,
#define	UI_SecBoundary_Nty  ev_TpSecBoundaryNty

	/************************************************************************/
	/** �����������ν�������ֵ֪ͨ���� 
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UIChangeDistorInd,
#define	UI_CHANGEDISTORT_IND  ev_UIChangeDistorInd

	/************************************************************************/
	/** ֱ���������ν�������ֵ֪ͨ���� 
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UIDirectSetDistorInd,
#define	UI_DIRECTSETDISTORT_IND  ev_UIDirectSetDistorInd

	/************************************************************************/
	/** ����汾��Ϣ֪ͨ���� 
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_TpMoonToolVerInfo_Nty,
#define	UI_MOONTOOL_VERINFO_NTY  ev_TpMoonToolVerInfo_Nty

	/************************************************************************/
	/** ����ź�Դ֪ͨ���� 
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_TpMoonToolCamOutputInfo_Nty,
#define	UI_MOONTOOL_CAMOUTPUT_INFO_NTY  ev_TpMoonToolCamOutputInfo_Nty

	/************************************************************************/
	/** ͼƬ��ת��Ϣ֪ͨ���� 
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_TpMoonToolCamImageAdjustInfo_Nty,
#define	UI_MOONTOOL_IMAGE_ADJUST_NTY  ev_TpMoonToolCamImageAdjustInfo_Nty

	/************************************************************************/
	/** ������Ϣ֪ͨ���� 
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_TpMoonToolEthnetInfo_Nty,
#define	UI_MOONTOOL_ETHNETINFO_NOTIFY  ev_TpMoonToolEthnetInfo_Nty

	/************************************************************************/
	/** ����ʱ����ź�Դ֪ͨ���� 
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_TpMoonToolCamOutputInfo_Ind,
#define	UI_MOONTOOL_CAMOUTPUT_INFO_IND  ev_TpMoonToolCamOutputInfo_Ind

	/************************************************************************/
	/** ͼƬ��ת���֪ͨ���� 
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_TpMoonToolCamImageAdjustInfo_Ind,
#define	UI_MOONTOOL_IMAGE_ADJUST_IND  ev_TpMoonToolCamImageAdjustInfo_Ind

	/************************************************************************/
	/** Ԥ��λ�б�֪ͨ��Ϣ 
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_TpMoonToolCamPreSet_Nty,
#define	UI_MOONTOOL_CAMPRESET_NTY  ev_TpMoonToolCamPreSet_Nty

	/************************************************************************/
	/** ����޸İ�ť��֪ͨ���򴰿�������Ϣ 
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_TpMoonToolOrderPos_Modify,
#define	UI_MOONTOOL_ORDERPOS_MODIFY  ev_TpMoonToolOrderPos_Modify

	/************************************************************************/
	/** ֪ͨ������������������Ϣ 
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_TpMoonToolListMenu_Option,
#define	UI_MOONTOOL_LISTMENU_OPTION  ev_TpMoonToolListMenu_Option

	/************************************************************************/
	/** ɾ��Ԥ��λ��֪ͨ������� 
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_TpMoonToolPreDel_Ind,
#define	UI_MOONTOOL_PREDEL_IND  ev_TpMoonToolPreDel_Ind

	/************************************************************************/
	/** �޸�Ԥ��λ��֪ͨ������� 
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_TpMoonToolPreModify_Ind,
#define	UI_MOONTOOL_PREMODIFY_IND  ev_TpMoonToolPreModify_Ind

	/************************************************************************/
	/** ����Ԥ��λ��֪ͨ������� 
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_TpMoonToolPreSet_Ind,
#define	UI_MOONTOOL_PRESET_IND  ev_TpMoonToolPreSet_Ind

	/************************************************************************/
	/** �ײ㷢��Ĭ��ֵ֪ͨ������� 
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_TpMoonToolCamParamDefault_Ind,
#define	UI_MOONTOOL_CAMPARAMDEFAULT_IND  ev_TpMoonToolCamParamDefault_Ind

	/************************************************************************/
	/** ��о�����ظ�֪ͨ����
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_CamMechanismUpgrade_Ind,
#define	UI_CAMMECHANISM_UPGRADE_IND  ev_CamMechanismUpgrade_Ind

	/************************************************************************/
	/** �����ظ�֪ͨ����
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_TpMoonToolUpgrade_Ind,
#define	UI_MOONTOOL_UPGRADE_IND  ev_TpMoonToolUpgrade_Ind
	/************************************************************************/
	/** ������֪ͨ
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_TpMoonToolLVDSBaud_Ind,
#define	UI_MOONTOOL_LVDSBAUD_IND  ev_TpMoonToolLVDSBaud_Ind
	
	
	

	
	
	/************************************************************************/
	/** �ο�������֪ͨ
	wparam 
	lparam */
	/************************************************************************/
	ev_TpReferenceLine_Ind,
#define	UI_MoonTool_ReferenceLine_IND  ev_TpReferenceLine_Ind
	/************************************************************************/
	/** ˮƽ��ת����֪ͨ
	wparam 
	lparam */
	/************************************************************************/
	ev_TpHorizontalFlip_Ind,
#define	UI_MoonTool_HorizontalFlip_IND  ev_TpHorizontalFlip_Ind
	/************************************************************************/
	/** ���ν�������֪ͨ
	wparam  
	lparam */
	/************************************************************************/
	ev_TpTrapezoidalCor_Ind,
#define	UI_MoonTool_TrapezoidalCor_IND  ev_TpTrapezoidalCor_Ind
	/************************************************************************/
	/** ��¼������ʾ����֪ͨ
	wparam  
	lparam */
	/************************************************************************/
	ev_UIMoonShowRectRegion_Nty,
#define	UI_MoonTool_ShowRectRegion_NTY  ev_UIMoonShowRectRegion_Nty
	/************************************************************************/
	/** ������ʾ����֪ͨ
	wparam  
	lparam */
	/************************************************************************/
	ev_UIMoonShowRectRegion_Ind,
#define	UI_MoonTool_ShowRectRegion_IND  ev_UIMoonShowRectRegion_Ind
	/************************************************************************/
	/** ��ɫһ���Կ�������֪ͨ
	wparam  
	lparam */
	/************************************************************************/
	ev_UIMoonTpColorSwich_Ind,
#define	UI_MoonTool_ColorSwitch_IND  ev_UIMoonTpColorSwich_Ind
	/************************************************************************/
	/** ���ν�������ֵ֪ͨ
	wparam  ��������
	lparam = 0*/
	/************************************************************************/
	ev_TpTraCorValue_Ind,
#define	UI_MoonTool_TraCorValue_IND  ev_TpTraCorValue_Ind
	/************************************************************************/
	/** ���ղ���֪ͨ
	wparam  ��������
	lparam = 0*/
	/************************************************************************/
	ev_TpSnapShot_Ind,
#define	UI_MoonTool_SnapShot_IND  ev_TpSnapShot_Ind
	/************************************************************************/
	/** FTP���ؿ��ս���֪ͨ
	wparam 
	lparam */
	/************************************************************************/
	ev_TpMoonToolFTPSnapDownLoad,
#define	WM_MoonTool_FTPSnapDownLoad  ev_TpMoonToolFTPSnapDownLoad
	/************************************************************************/
	/** ��Ԥ��λ��Ϣ���洫��Ԥ��λ�б�
	wparam 
	lparam */
	/************************************************************************/
	ev_TpMoonToolPresetListParam_Ind,
#define	WM_MoonTool_PresetListParam_IND  ev_TpMoonToolPresetListParam_Ind	
	/************************************************************************/
	/** FTP����Ԥ��λ����
	wparam 
	lparam */
	/************************************************************************/
	ev_TpMoonToolFTPPreSetSnapDownLoad,
#define	WM_MoonTool_FTP_PreSetSnapDownLoad  ev_TpMoonToolFTPPreSetSnapDownLoad

	/************************************************************************/
	/** MOON90 Gammaѡ�����֪ͨ 
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UIMoonToolGammaSelectInd,
#define	UI_MOONTOOL_GammaStyleSel_IND  ev_UIMoonToolGammaSelectInd

	/************************************************************************/
	/** ��ֹ�ڶ�ʱ���ڱ�����Ԥ��λ ���ÿռ䰴ť
	wparam 
	lparam */
	/************************************************************************/
	ev_TpMoonToolStatusSet,
#define	WM_MoonTool_StatusSet  ev_TpMoonToolStatusSet

	/************************************************************************/
	/** ��½ʱ�ӷ�������ȡ��о����
	wparam 
	lparam */
	/************************************************************************/
	ev_TpMechanismSelectNty,
#define	UI_TpMechanismSelect_NTY  ev_TpMechanismSelectNty

	/** ��½ʱ�ӷ�������ȡ��о�汾��
	wparam 
	lparam */
	/************************************************************************/
	ev_TpMechVerNty,
#define	UI_TpMechVer_NTY  ev_TpMechVerNty

	/************************************************************************/
	/** ������ʱ����֪ͨ���� 
	wparam TTPFpgaDelay������Ϣ
	lparam* BOOL/
	/************************************************************************/
	ev_UISetDelayCorrectInd,
#define	UI_SETDELAYCORRECT_IND  ev_UISetDelayCorrectInd
   
	/************************************************************************/
	/** ������ʱ����֪ͨ���� 
	wparam TTPFpgaDelay
	lparam*/
	/************************************************************************/
	ev_UISetDelayCorrectNty,
#define	UI_SETDELAYCORRECT_NTY  ev_UISetDelayCorrectNty

};

#endif 
