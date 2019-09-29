// centCtrlLogic.cpp: implementation of the CCentCtrlLogic class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "centCtrlLogic.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCentCtrlLogic::CCentCtrlLogic()
:m_strAirInfo("StcAirInfo")
,m_strXinFengInfo("StcXinFengInfo")
,m_strDisPlay1Info("StcDisPlay1Info")
,m_strDisPlay2Info("StcDisPlay2Info")
,m_strDisPlay3Info("StcDisPlay3Info")
,m_strCamera1Info("StcCamera1Info")
,m_strCamera2Info("StcCamera2Info")
,m_strCamera3Info("StcCamera3Info")
,m_strDocCameraInfo("StcDocCameraInfo")
{

}

CCentCtrlLogic::~CCentCtrlLogic()
{

}

bool CCentCtrlLogic::InitWnd( const IArgs & arg )
{
	CLogicBase::InitWnd( arg );
	return true;
}

void CCentCtrlLogic::RegMsg()
{
	CCentCtrlLogic* m_pThis = GetSingletonPtr();
	REG_MSG_HANDLER( UI_CNS_SCHTEMP_NTY, CCentCtrlLogic::OnAirInfoNty, m_pThis, CCentCtrlLogic );
	REG_MSG_HANDLER( UI_CNSTOOL_MSG_XinFengInfo_NTY, CCentCtrlLogic::OnXinFengInfoNty, m_pThis, CCentCtrlLogic );
	REG_MSG_HANDLER( UI_CNS_TVSTATE_NTY, CCentCtrlLogic::OnDisplayInfoNty, m_pThis, CCentCtrlLogic );
	REG_MSG_HANDLER( UI_CNSTOOL_MSG_CamPowerState_NTY, CCentCtrlLogic::OnCameraInfoNty, m_pThis, CCentCtrlLogic );
	REG_MSG_HANDLER( UI_CNS_DCAMSTATE_NTY, CCentCtrlLogic::OnDocCamInfoNty, m_pThis, CCentCtrlLogic );
	REG_MSG_HANDLER( UI_CNS_SCHSTATE_NTY, CCentCtrlLogic::OnLightInfoNty, m_pThis, CCentCtrlLogic );
	REG_MSG_HANDLER( UI_TPAD_CENTRESLEEP_NTY, CCentCtrlLogic::OnCentSleepNty, m_pThis, CCentCtrlLogic );

}

void CCentCtrlLogic::UnRegMsg()
{
	
}

void CCentCtrlLogic::RegCBFun()
{
	CCentCtrlLogic* m_pThis = GetSingletonPtr();
	REG_GOBAL_MEMBER_FUNC( "CCentCtrlLogic::InitWnd", CCentCtrlLogic::InitWnd, m_pThis, CCentCtrlLogic ) ;
}

void CCentCtrlLogic::UnRegFunc()
{
	
}

void CCentCtrlLogic::Clear()
{
	
}

LRESULT CCentCtrlLogic::OnAirInfoNty( WPARAM wParam, LPARAM lParam )
{
	if ( m_pWndTree == NULL )
	{
		return S_FALSE;
	}
	
	u16 wSchTem = (u16)wParam;
    //当前不能获得空调开关,只有温度
	String strAirInfo = "空调：";

	s8 chAirTemP[8] = {0};
	sprintf( chAirTemP, "%u", wSchTem );
	strAirInfo += chAirTemP;
	strAirInfo += "℃";

	UIFACTORYMGR_PTR->SetCaption(m_strAirInfo, strAirInfo, m_pWndTree, TRUE);
	return S_OK;
}

LRESULT CCentCtrlLogic::OnXinFengInfoNty( WPARAM wParam, LPARAM lParam )	//新风没有相应的接口
{
	if ( m_pWndTree == NULL )
	{
		return S_FALSE;
	}

	String strXinFengInfo = "新风：";
	
	
	s8 chXinFeng[8] = {0};
//	sprintf( chXinFeng, "%u", tXinFengInfo.m_byLevel );
	strXinFengInfo += ",";
	strXinFengInfo += chXinFeng;
	strXinFengInfo += "级";

	UIFACTORYMGR_PTR->SetCaption(m_strXinFengInfo, strXinFengInfo, m_pWndTree, TRUE);

	return S_OK;
}

LRESULT CCentCtrlLogic::OnDisplayInfoNty( WPARAM wParam, LPARAM lParam )
{
	if ( m_pWndTree == NULL )
	{
		return S_FALSE;
	}
	TCentreTVCfg atCentreTVCfg[MAX_CENTRETV_NUM];
	memcpy( atCentreTVCfg, LIBDATAMGRPTR->GetCentreTVCfg(), sizeof(atCentreTVCfg)) ;

	String strDisplay1Info = "显示器一：";
	strDisplay1Info += StateToString(atCentreTVCfg[0].emTvPowerMode);
	UIFACTORYMGR_PTR->SetCaption(m_strDisPlay1Info, strDisplay1Info, m_pWndTree, TRUE);
	
	String strDisplay2Info = "显示器二：";
	strDisplay2Info += StateToString(atCentreTVCfg[1].emTvPowerMode);
	UIFACTORYMGR_PTR->SetCaption(m_strDisPlay2Info, strDisplay2Info, m_pWndTree, TRUE);
	
	String strDisplay3Info = "显示器三：";
	strDisplay3Info += StateToString(atCentreTVCfg[2].emTvPowerMode);
	UIFACTORYMGR_PTR->SetCaption(m_strDisPlay3Info, strDisplay3Info, m_pWndTree, TRUE);

	return S_OK;
}

LRESULT CCentCtrlLogic::OnCameraInfoNty( WPARAM wParam, LPARAM lParam )
{
	if ( m_pWndTree == NULL )
	{
		return S_FALSE;
	}

	EmCamPowerMode aemCam[MAX_CNCAMERA_NUM];
	for (int i=0;i<3;i++)
	{
		aemCam[i] =  *((EmCamPowerMode*)wParam + i);
	}

	String strCamera1Info = "摄像机一：";
	strCamera1Info += CamStateToString(aemCam[0]);
	UIFACTORYMGR_PTR->SetCaption(m_strCamera1Info, strCamera1Info, m_pWndTree, TRUE);
	
	String strCamera2Info = "摄像机二：";
	strCamera2Info += CamStateToString(aemCam[1]);
	UIFACTORYMGR_PTR->SetCaption(m_strCamera2Info, strCamera2Info, m_pWndTree, TRUE);
	
	String strCamera3Info = "摄像机三：";
	strCamera3Info += CamStateToString(aemCam[2]);
	UIFACTORYMGR_PTR->SetCaption(m_strCamera3Info, strCamera3Info, m_pWndTree, TRUE);

// 	TCnCameraCfg tInfo[MAX_CNCAMERA_NUM];
// 	vector<TCnCameraCfg> vecTCnCameraCfg;
// 	LIBDATAMGRPTR->GetCamInfo(vecTCnCameraCfg);
// 	
// 	for ( int i = 0; i < vecTCnCameraCfg.size(); i++ )
// 	{
// 		tInfo[i] = vecTCnCameraCfg.at(i);
// 	}
// 	
// 	String strCamera1Info = "摄像机一：";
// 	if ( tInfo[0].bUsed )
// 	{
// 		strCamera1Info += "开";
// 	}
// 	else
// 	{
// 		strCamera1Info += "关";
// 	}
// 	UIFACTORYMGR_PTR->SetCaption(m_strCamera1Info, strCamera1Info, m_pWndTree, TRUE);
// 	
// 	String strCamera2Info = "摄像机二：";
// 	if ( tInfo[1].bUsed )
// 	{
// 		strCamera2Info += "开";
// 	}
// 	else
// 	{
// 		strCamera2Info += "关";
// 	}
// 	UIFACTORYMGR_PTR->SetCaption(m_strCamera2Info, strCamera2Info, m_pWndTree, TRUE);
// 	
// 	String strCamera3Info = "摄像机三：";
// 	if ( tInfo[2].bUsed )
// 	{
// 		strCamera3Info += "开";
// 	}
// 	else
// 	{
// 		strCamera3Info += "关";
// 	}
// 	UIFACTORYMGR_PTR->SetCaption(m_strCamera3Info, strCamera3Info, m_pWndTree, TRUE);
	
	return S_OK;
}

LRESULT CCentCtrlLogic::OnDocCamInfoNty( WPARAM wParam, LPARAM lParam )
{
	if ( m_pWndTree == NULL )
	{
		return S_FALSE;
	}
	String strState;
	TCentreDCamCfg tDCamCfg = *(TCentreDCamCfg*)wParam;

	String strDocCamera = "文档摄像机：";
	
	switch(tDCamCfg.emDCamPowerMode)
	{
	case emDCamPowerOn:
		strState = "开";
		break;
	case emDCamPowerOff:
		strState = "关";
		break;
	case emDCamPowerToggle:
		strState = "待机";
		break;
	default:
		strState = "关";
	}
	strDocCamera += strState;
	UIFACTORYMGR_PTR->SetCaption(m_strDocCameraInfo, strDocCamera, m_pWndTree, TRUE);
	
	return S_OK;
}

LRESULT CCentCtrlLogic::OnLightInfoNty( WPARAM wParam, LPARAM lParam )
{
	if ( m_pWndTree == NULL )
	{
		return S_FALSE;
	}

	TCentreSchCfg tSchCfg = *(TCentreSchCfg*)wParam;
	//当前不能获得空调开关,只有温度
	String strAirInfo = "空调：";	
	s8 chAirTemP[8] = {0};
	sprintf( chAirTemP, "%u", tSchCfg.wSchTem );
	strAirInfo += chAirTemP;
	strAirInfo += "℃";
	
	UIFACTORYMGR_PTR->SetCaption(m_strAirInfo, strAirInfo, m_pWndTree, TRUE);

	//设置灯光状态信息
	Value_ItemLight LightState( &tSchCfg );
	UIFACTORYMGR_PTR->SetPropertyValue( LightState, "StcTPbg", m_pWndTree);	
	return S_OK;
}

String CCentCtrlLogic::StateToString( EmTvPowerMode& emSwitchState )
{
	String strState;
	switch(emSwitchState)
	{
	case emTVPowerON:
		strState = "开";
		break;
	case emTVPowerOFF:
		strState = "待机";
		break;
	case emTVPowerDown:
		strState = "关";
		break;
	default:
		strState = "关";
		break;
	}
	return strState;
}

String CCentCtrlLogic::CamStateToString( EmCamPowerMode& emSwitchState )
{
	String strState;
	switch(emSwitchState)
	{
	case emCamPowerOn:
		strState = "开";
		break;
	case emCamPowerOff:
		strState = "待机";
		break;
// 	case emTVPowerDown:
// 		strState = "关";
// 		break;
	default:
		strState = "关";
		break;
	}
	return strState;
}

LRESULT CCentCtrlLogic::OnCentSleepNty( WPARAM wParam, LPARAM lParam )
{
	//断开cns
	COMIFMGRPTR->DisConnect();
	UIFACTORYMGR_PTR->HideAllWindow();
	LOGICMGR_PTR->DestroyLogic();
	//隐藏cnstool，显示登录界面 		
	UIDATAMGR_PTR->NotifyOuterWnd( WM_TPTOOL_LOGINRESULT, em_LOGIN_LOGOFF, 0 );
	return S_OK;
}
