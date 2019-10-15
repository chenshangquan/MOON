#pragma once

#ifndef _EVRKCLIB_20180920_H_
#define _EVRKCLIB_20180920_H_



//rkcLib中消息定义
enum EmUiRkcMsg
{

#define UI_RKC_MSG_BEGIN  	2000 + 0x1 

	/************************************************************************/
	/** 连接 
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UIRkConnect	= UI_RKC_MSG_BEGIN,
#define	UI_RKC_CONNECTED  ev_UIRkConnect
	
	/************************************************************************/
	/** 已断开
	wParam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UIRkDisconnected,
#define UI_RKC_DISCONNECTED	 ev_UIRkDisconnected

    /************************************************************************/
	/** 重启
	wParam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UIRkReBoot,
#define UI_RKC_REBOOT	 ev_UIRkReBoot

    /************************************************************************/
	/** 恢复出厂设置
	wParam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UIRkRestore,
#define UI_RKC_RESTONE	 ev_UIRkRestore

    /************************************************************************/
	/** 刷新搜索列表
	wParam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UIRkDevReflesh,
#define UI_RKC_RKDEV_REFLESH    ev_UIRkDevReflesh

    /************************************************************************/
	/** 搜索包发送完毕
	wParam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UISearchFinish,
#define UI_RKC_SEARCH_FINISH    ev_UISearchFinish

     /************************************************************************/
	/** 刷新工作模式界面
	wParam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UIWorkModeReflesh,
#define UI_RKC_WORKMODE_REFLESH    ev_UIWorkModeReflesh

    /************************************************************************/
	/** 工作模式修改反馈
	wParam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UIWorkModeChange,
#define UI_RKC_WORKMODE_CHANGE    ev_UIWorkModeChange

    /************************************************************************/
	/** IP校验反馈
	wParam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UIIPChecking,
#define UI_RKC_IP_CHECK    ev_UIIPChecking

    /************************************************************************/
	/** 刷新网络配置界面
	wParam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UINetWorkReflesh,
#define UI_RKC_NETWORK_REFLESH    ev_UINetWorkReflesh

    /************************************************************************/
	/** 网络配置修改反馈
	wParam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UINetWorkChange,
#define UI_RKC_NETWORK_CHANGE    ev_UINetWorkChange

	/************************************************************************/
	/** 修改密码反馈
	wParam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UIRkModifyPassword,
#define UI_RKC_MODIFY_PASSWORD    ev_UIRkModifyPassword

    /************************************************************************/
	/** 功耗电源刷新
	wParam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UIPowerFlesh,
#define UI_RKC_POWER_FLESH    ev_UIPowerFlesh

    /************************************************************************/
	/** 升级更新回复
	wParam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UIRkUpdateFirstAck,
#define UI_RKC_UPDATE_FIRST_ACK    ev_UIRkUpdateFirstAck

    /************************************************************************/
	/** 升级更新回复notify
	wParam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UIRkUpdateFirstNty,
#define UI_RKC_UPDATE_FIRST_NTY    ev_UIRkUpdateFirstNty

    /************************************************************************/
	/** 升级更新回复notify
	wParam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UIRkUpdateSecondNty,
#define UI_RKC_UPDATE_SECOND_NTY    ev_UIRkUpdateSecondNty

    /************************************************************************/
	/** 调试模式刷新
	wParam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UIDebugModeFlesh,
#define UI_RKC_DEBUGMODE_FLESH    ev_UIDebugModeFlesh

    /************************************************************************/
	/** 调试模式修改反馈
	wParam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UIDebugModeChange,
#define UI_RKC_DEBUGMODE_CHANGE    ev_UIDebugModeChange

    /************************************************************************/
	/** 板卡信息通知
	wParam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UIBrdInfoNty,
#define UI_RKC_BRDINFO_NTY    ev_UIBrdInfoNty

    ev_UIRkcEnd,
#define	UI_RKC_MSG_END   ev_UIRkcEnd

};

//moontool中消息定义
enum EmUiMoontoolMsg
{
#define UI_MOONTOOL_MSG_BEGIN  UI_RKC_MSG_END + 0x1

	/************************************************************************/
	/** 连接  MOON90 
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UIMoonToolLoginRsp	= UI_MOONTOOL_MSG_BEGIN,
#define	UI_MOONTOOL_CONNECTED  ev_UIMoonToolLoginRsp

	/************************************************************************/
	/** 已断开MOON90
	wParam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UIMoonToolDisconnected,
#define UI_MOONTOOL_DISCONNECTED	 ev_UIMoonToolDisconnected

	/************************************************************************/
	/** MOON90摄像调节界面数据信息通知 
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UIMoonToolCamInfoNty,
#define	UI_MOONTOOL_CAMINFO_NTY  ev_UIMoonToolCamInfoNty

	/************************************************************************/
	/** MOON90梯形矫正Zoom值通知界面 
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UIMoonDistortZoomNty,
#define	UI_DISTORTZOOM_NTY  ev_UIMoonDistortZoomNty

	/************************************************************************/
	/** MOON90摄像机选择界面通知 
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UIMoonToolCamSelectInd,
#define	UI_MOONTOOL_CamSel_IND  ev_UIMoonToolCamSelectInd

	/************************************************************************/
	/** MOON90摄像机机芯同步通知 
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UIMoonToolCamParamSyncInd,
#define	UI_MOONTOOL_CamParamSync_IND  ev_UIMoonToolCamParamSyncInd

	/************************************************************************/
	/** MOON90摄像机机芯选择界面通知 
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UIMoonToolCamStyleSelectInd,
#define	UI_MOONTOOL_CamStyleSel_IND  ev_UIMoonToolCamStyleSelectInd

	/************************************************************************/
	/** 摄像调节界面zoom值增减设置回复 
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UIMoonToolCamZoomInd,
#define	UI_MOONTOOL_SET_CAMERA_ZOOM_IND  ev_UIMoonToolCamZoomInd

	/************************************************************************/
	/** 梯形矫正界面zoom值增减设置回复 
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UIMoonToolCamSetZoonStopInd,
#define	UI_MOONTOOL_CAMSETZOON_STOP_IND  ev_UIMoonToolCamSetZoonStopInd

	/************************************************************************/
	/** 摄像调节界面zoom值增减设置回复 
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UIMoonToolCamAutoFocusInd,
#define	UI_MOONTOOL_CAMERA_AUTO_FOCUS_IND  ev_UIMoonToolCamAutoFocusInd

	/************************************************************************/
	/** 是否开启自动曝光回复 
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UIMoonToolCamAutoExposureInd,
#define	UI_MOONTOOL_CAMERA_AUTO_EXPOSURE_IND  ev_UIMoonToolCamAutoExposureInd

	/************************************************************************/
	/** 是否开启自动白平衡回复 
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UIMoonToolCamAutoWBInd,
#define	UI_MOONTOOL_CAMERA_AUTO_WB_IND  ev_UIMoonToolCamAutoWBInd

	/************************************************************************/
	/** 白平衡R制式回复 
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UIMoonToolCamRGainInd,
#define	UI_MOONTOOL_CAMERA_RGAIN_IND  ev_UIMoonToolCamRGainInd

	/************************************************************************/
	/** 白平衡B制式回复 
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UIMoonToolCamBGainInd,
#define	UI_MOONTOOL_CAMERA_BGAIN_IND  ev_UIMoonToolCamBGainInd

	/************************************************************************/
	/** 背光补偿是否开启界面回复 
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UIMoonToolCamBackLightInd,
#define	UI_MOONTOOL_CAMERA_BACKLIGHT_IND  ev_UIMoonToolCamBackLightInd

	/************************************************************************/
	/** 降噪设置界面回复 
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UIMoonToolCamNRInd,
#define	UI_MOONTOOL_CAMERA_NR_IND  ev_UIMoonToolCamNRInd

	/************************************************************************/
	/** 2D降噪设置界面回复 
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UIMoonToolCam2DNRInd,
#define	UI_MOONTOOL_CAMERA_2DNR_IND  ev_UIMoonToolCam2DNRInd

	/************************************************************************/
	/** 3D降噪设置界面回复 
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UIMoonToolCam3DNRInd,
#define	UI_MOONTOOL_CAMERA_3DNR_IND  ev_UIMoonToolCam3DNRInd

	/************************************************************************/
	/** 降噪设置界面回复 
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UIMoonToolCamInitPresetInd,
#define	UI_MOONTOOL_CAMERA_INITPRESET_IND  ev_UIMoonToolCamInitPresetInd
		
	/************************************************************************/
	/** 亮度调节后通知界面 
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UIMoonToolImageBLightInd,
#define	UI_MOONTOOL_IMAGE_BLIGHT_IND  ev_UIMoonToolImageBLightInd

	/************************************************************************/
	/** 对比度调节后通知界面 
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UIMoonToolImageContrastInd,
#define	UI_MOONTOOL_IMAGE_CONTRAST_IND  ev_UIMoonToolImageContrastInd

	/************************************************************************/
	/** 色度调节后通知界面 
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UIMoonToolImageSharpInd,
#define	UI_MOONTOOL_IMAGE_Sharp_IND  ev_UIMoonToolImageSharpInd

	/************************************************************************/
	/** 饱和度调节后通知界面 
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UIMoonToolImageSaturatInd,
#define	UI_MOONTOOL_IMAGE_SATURAT_IND  ev_UIMoonToolImageSaturatInd
	
	/************************************************************************/
	/** 光圈调节后通知界面 
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UIMoonToolCamApertureInd,
#define	UI_MOONTOOL_CAMERA_APERTURE_IND  ev_UIMoonToolCamApertureInd

	/************************************************************************/
	/** 快门调节后通知界面 
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UIMoonToolCamShutSpdInd,
#define	UI_MOONTOOL_CAMERA_SHUT_SPD_IND  ev_UIMoonToolCamShutSpdInd

	/************************************************************************/
	/** 增益调节后通知界面 
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UIMoonToolCamGainInd,
#define	UI_MOONTOOL_CAMERA_GAIN_IND  ev_UIMoonToolCamGainInd

	/************************************************************************/
	/** 增益调节后通知界面 
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UIMoonToolImageParaInd,
#define	UI_MOONTOOL_IMAGEPARA_IND  ev_UIMoonToolImageParaInd

	/************************************************************************/
	/** 梯形校正操作结果通知界面 
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UIMoonToolCamDistortParamInd,
#define	UI_MOONTOOL_CAMERA_DISTORTPARAM_IND  ev_UIMoonToolCamDistortParamInd

	/************************************************************************/
	/** 设置颜色一致性自动计算通知界面 
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UIAutoSetColorConstancyInd,
#define	UI_AUTOSETCOLORCONSTANCY_IND  ev_UIAutoSetColorConstancyInd

	/************************************************************************/
	/** 中间路RGB系数改变时通知两边路RGB改变系数通知界面 
	wparam = 0
	lparam = 0*/
	/************************************************************************/
    ev_UIChangeSideRGBNty,
#define	UI_CHANGESIDERGB_NTY  ev_UIChangeSideRGBNty
	/************************************************************************/
	/** 设置颜色一致性RGB值通知界面 
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UISetColorRGBInd,
#define	UI_SETCOLORRGB_IND  ev_UISetColorRGBInd

	/************************************************************************/
	/** 直接设置颜色一致性RGB值通知界面 
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UIDirectSetColorRGBInd,
#define	UI_DIRECT_SETCOLORRGB_IND  ev_UIDirectSetColorRGBInd

	/************************************************************************/
	/** 矩形长宽设置请求通知界面 
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UIChooseRectangleInd,
#define	UI_CHOOSERECTANGLE_IND  ev_UIChooseRectangleInd

	/************************************************************************/
	/** 恢复默认设置请求通知界面 
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_TpSecDefaultNty,
#define	UI_MoonSecDefault_Nty  ev_TpSecDefaultNty

	/************************************************************************/
	/** 登录请求第二页数据通知界面 
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_TpSecBoundaryNty,
#define	UI_SecBoundary_Nty  ev_TpSecBoundaryNty

	/************************************************************************/
	/** 设置增减梯形矫正参数值通知界面 
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UIChangeDistorInd,
#define	UI_CHANGEDISTORT_IND  ev_UIChangeDistorInd

	/************************************************************************/
	/** 直接设置梯形矫正参数值通知界面 
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UIDirectSetDistorInd,
#define	UI_DIRECTSETDISTORT_IND  ev_UIDirectSetDistorInd

	/************************************************************************/
	/** 软件版本信息通知界面 
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_TpMoonToolVerInfo_Nty,
#define	UI_MOONTOOL_VERINFO_NTY  ev_TpMoonToolVerInfo_Nty

	/************************************************************************/
	/** 输出信号源通知界面 
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_TpMoonToolCamOutputInfo_Nty,
#define	UI_MOONTOOL_CAMOUTPUT_INFO_NTY  ev_TpMoonToolCamOutputInfo_Nty

	/************************************************************************/
	/** 图片翻转信息通知界面 
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_TpMoonToolCamImageAdjustInfo_Nty,
#define	UI_MOONTOOL_IMAGE_ADJUST_NTY  ev_TpMoonToolCamImageAdjustInfo_Nty

	/************************************************************************/
	/** 网络信息通知界面 
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_TpMoonToolEthnetInfo_Nty,
#define	UI_MOONTOOL_ETHNETINFO_NOTIFY  ev_TpMoonToolEthnetInfo_Nty

	/************************************************************************/
	/** 设置时输出信号源通知界面 
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_TpMoonToolCamOutputInfo_Ind,
#define	UI_MOONTOOL_CAMOUTPUT_INFO_IND  ev_TpMoonToolCamOutputInfo_Ind

	/************************************************************************/
	/** 图片翻转结果通知界面 
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_TpMoonToolCamImageAdjustInfo_Ind,
#define	UI_MOONTOOL_IMAGE_ADJUST_IND  ev_TpMoonToolCamImageAdjustInfo_Ind

	/************************************************************************/
	/** 预置位列表通知消息 
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_TpMoonToolCamPreSet_Nty,
#define	UI_MOONTOOL_CAMPRESET_NTY  ev_TpMoonToolCamPreSet_Nty

	/************************************************************************/
	/** 点击修改按钮后通知弹框窗口数据消息 
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_TpMoonToolOrderPos_Modify,
#define	UI_MOONTOOL_ORDERPOS_MODIFY  ev_TpMoonToolOrderPos_Modify

	/************************************************************************/
	/** 通知主界面显隐标题栏消息 
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_TpMoonToolListMenu_Option,
#define	UI_MOONTOOL_LISTMENU_OPTION  ev_TpMoonToolListMenu_Option

	/************************************************************************/
	/** 删除预置位后通知界面更新 
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_TpMoonToolPreDel_Ind,
#define	UI_MOONTOOL_PREDEL_IND  ev_TpMoonToolPreDel_Ind

	/************************************************************************/
	/** 修改预置位后通知界面更新 
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_TpMoonToolPreModify_Ind,
#define	UI_MOONTOOL_PREMODIFY_IND  ev_TpMoonToolPreModify_Ind

	/************************************************************************/
	/** 保存预置位后通知界面更新 
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_TpMoonToolPreSet_Ind,
#define	UI_MOONTOOL_PRESET_IND  ev_TpMoonToolPreSet_Ind

	/************************************************************************/
	/** 底层发送默认值通知界面更新 
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_TpMoonToolCamParamDefault_Ind,
#define	UI_MOONTOOL_CAMPARAMDEFAULT_IND  ev_TpMoonToolCamParamDefault_Ind

	/************************************************************************/
	/** 机芯升级回复通知界面
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_CamMechanismUpgrade_Ind,
#define	UI_CAMMECHANISM_UPGRADE_IND  ev_CamMechanismUpgrade_Ind

	/************************************************************************/
	/** 升级回复通知界面
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_TpMoonToolUpgrade_Ind,
#define	UI_MOONTOOL_UPGRADE_IND  ev_TpMoonToolUpgrade_Ind
	/************************************************************************/
	/** 波特率通知
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_TpMoonToolLVDSBaud_Ind,
#define	UI_MOONTOOL_LVDSBAUD_IND  ev_TpMoonToolLVDSBaud_Ind
	
	
	

	
	
	/************************************************************************/
	/** 参考线设置通知
	wparam 
	lparam */
	/************************************************************************/
	ev_TpReferenceLine_Ind,
#define	UI_MoonTool_ReferenceLine_IND  ev_TpReferenceLine_Ind
	/************************************************************************/
	/** 水平翻转设置通知
	wparam 
	lparam */
	/************************************************************************/
	ev_TpHorizontalFlip_Ind,
#define	UI_MoonTool_HorizontalFlip_IND  ev_TpHorizontalFlip_Ind
	/************************************************************************/
	/** 梯形矫正设置通知
	wparam  
	lparam */
	/************************************************************************/
	ev_TpTrapezoidalCor_Ind,
#define	UI_MoonTool_TrapezoidalCor_IND  ev_TpTrapezoidalCor_Ind
	/************************************************************************/
	/** 登录矩形显示设置通知
	wparam  
	lparam */
	/************************************************************************/
	ev_UIMoonShowRectRegion_Nty,
#define	UI_MoonTool_ShowRectRegion_NTY  ev_UIMoonShowRectRegion_Nty
	/************************************************************************/
	/** 矩形显示设置通知
	wparam  
	lparam */
	/************************************************************************/
	ev_UIMoonShowRectRegion_Ind,
#define	UI_MoonTool_ShowRectRegion_IND  ev_UIMoonShowRectRegion_Ind
	/************************************************************************/
	/** 颜色一致性开关设置通知
	wparam  
	lparam */
	/************************************************************************/
	ev_UIMoonTpColorSwich_Ind,
#define	UI_MoonTool_ColorSwitch_IND  ev_UIMoonTpColorSwich_Ind
	/************************************************************************/
	/** 梯形矫正参数值通知
	wparam  操作类型
	lparam = 0*/
	/************************************************************************/
	ev_TpTraCorValue_Ind,
#define	UI_MoonTool_TraCorValue_IND  ev_TpTraCorValue_Ind
	/************************************************************************/
	/** 快照操作通知
	wparam  操作类型
	lparam = 0*/
	/************************************************************************/
	ev_TpSnapShot_Ind,
#define	UI_MoonTool_SnapShot_IND  ev_TpSnapShot_Ind
	/************************************************************************/
	/** FTP下载快照进度通知
	wparam 
	lparam */
	/************************************************************************/
	ev_TpMoonToolFTPSnapDownLoad,
#define	WM_MoonTool_FTPSnapDownLoad  ev_TpMoonToolFTPSnapDownLoad
	/************************************************************************/
	/** 给预置位信息界面传递预置位列表
	wparam 
	lparam */
	/************************************************************************/
	ev_TpMoonToolPresetListParam_Ind,
#define	WM_MoonTool_PresetListParam_IND  ev_TpMoonToolPresetListParam_Ind	
	/************************************************************************/
	/** FTP下载预置位快照
	wparam 
	lparam */
	/************************************************************************/
	ev_TpMoonToolFTPPreSetSnapDownLoad,
#define	WM_MoonTool_FTP_PreSetSnapDownLoad  ev_TpMoonToolFTPPreSetSnapDownLoad

	/************************************************************************/
	/** MOON90 Gamma选择界面通知 
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UIMoonToolGammaSelectInd,
#define	UI_MOONTOOL_GammaStyleSel_IND  ev_UIMoonToolGammaSelectInd

	/************************************************************************/
	/** 防止在短时间内保存多个预制位 设置空间按钮
	wparam 
	lparam */
	/************************************************************************/
	ev_TpMoonToolStatusSet,
#define	WM_MoonTool_StatusSet  ev_TpMoonToolStatusSet

	/************************************************************************/
	/** 登陆时从服务器获取机芯类型
	wparam 
	lparam */
	/************************************************************************/
	ev_TpMechanismSelectNty,
#define	UI_TpMechanismSelect_NTY  ev_TpMechanismSelectNty

	/** 登陆时从服务器获取机芯版本号
	wparam 
	lparam */
	/************************************************************************/
	ev_TpMechVerNty,
#define	UI_TpMechVer_NTY  ev_TpMechVerNty

	/************************************************************************/
	/** 设置延时矫正通知界面 
	wparam TTPFpgaDelay具体信息
	lparam* BOOL/
	/************************************************************************/
	ev_UISetDelayCorrectInd,
#define	UI_SETDELAYCORRECT_IND  ev_UISetDelayCorrectInd
   
	/************************************************************************/
	/** 设置延时矫正通知界面 
	wparam TTPFpgaDelay
	lparam*/
	/************************************************************************/
	ev_UISetDelayCorrectNty,
#define	UI_SETDELAYCORRECT_NTY  ev_UISetDelayCorrectNty

};

#endif 
