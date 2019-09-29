// CentCfgFrameLogic.cpp: implementation of the CCentCfgFrameLogic class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CentCfgFrameLogic.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCentCfgFrameLogic::CCentCfgFrameLogic()
{
	m_strLstFunMenu = "centCfgMenuDlg/LstcentCfgFuncMenu";
}

CCentCfgFrameLogic::~CCentCfgFrameLogic()
{

}

void CCentCfgFrameLogic::RegCBFun()
{
	CCentCfgFrameLogic *pThis =  GetSingletonPtr();
	
    REG_GOBAL_MEMBER_FUNC( "CCentCfgFrameLogic::InitWnd", CCentCfgFrameLogic::InitWnd, pThis, CCentCfgFrameLogic ) ;
	//列表按钮点击事件
	REG_LIST_CALLFUNC( "CCentCfgFrameLogic::OnClickXinFengCfg", CCentCfgFrameLogic::OnClickXinFengCfg, pThis, CCentCfgFrameLogic ) ;
	REG_LIST_CALLFUNC( "CCentCfgFrameLogic::OnClickCameraCfg", CCentCfgFrameLogic::OnClickCameraCfg, pThis, CCentCfgFrameLogic ) ;
	REG_LIST_CALLFUNC( "CCentCfgFrameLogic::OnClickLightCfg", CCentCfgFrameLogic::OnClickLightCfg, pThis, CCentCfgFrameLogic ) ;
	REG_LIST_CALLFUNC( "CCentCfgFrameLogic::OnClickDisplayCfg", CCentCfgFrameLogic::OnClickDisplayCfg, pThis, CCentCfgFrameLogic ) ;
}

void CCentCfgFrameLogic::UnRegFunc()
{
	UN_REG_GOBAL_FUNC( "CCentCfgFrameLogic::InitWnd" );
}

bool CCentCfgFrameLogic::InitWnd( const IArgs & arg )
{
	CLogicBase::InitWnd( arg );
	InitCfgFuncMenu();
	UIFACTORYMGR_PTR->ShowWindow( g_strCentLightDlg );
	UIFACTORYMGR_PTR->ShowWindow( g_strCentCameraDlg, false );
	UIFACTORYMGR_PTR->ShowWindow( g_strCentXinFengDlg, false );
	UIFACTORYMGR_PTR->ShowWindow( g_strCentDisplayDlg, false );

	m_strCurWnd = g_strCentLightDlg;
	m_strCfgCurWnd = g_strCentLightDlg;
	return true;
}

void CCentCfgFrameLogic::Clear()
{
	m_strCfgCurWnd = g_strCentLightDlg;
	if ( m_pWndTree != NULL )
	{		
		UIFACTORYMGR_PTR->LoadScheme( "SchmConfMenuListDefault", m_pWndTree );   //登陆后初始化默认页面
	}
}

void CCentCfgFrameLogic::HideAllWnd()
{
	UIFACTORYMGR_PTR->ShowWindow(g_strCentXinFengDlg, false);
	UIFACTORYMGR_PTR->ShowWindow(g_strCentCameraDlg, false);
	UIFACTORYMGR_PTR->ShowWindow(g_strCentLightDlg, false);
	UIFACTORYMGR_PTR->ShowWindow(g_strCentDisplayDlg, false);
}

void CCentCfgFrameLogic::RegMsg()
{
	CCentCfgFrameLogic *pThis =  GetSingletonPtr();
	REG_MSG_HANDLER( UI_CNSTOOL_MSG_CamPowerState_NTY, CCentCfgFrameLogic::OnCameraInfoNty, pThis, CCentCfgFrameLogic );
	REG_MSG_HANDLER( UI_CNS_DCAMSTATE_NTY, CCentCfgFrameLogic::OnDocCamInfoNty, pThis, CCentCfgFrameLogic );
	REG_MSG_HANDLER( UI_CNS_SCHTEMP_NTY, CCentCfgFrameLogic::OnAirInfoNty, pThis, CCentCfgFrameLogic );		//空调消息通过灯光消息传过来
	REG_MSG_HANDLER( UI_CNSTOOL_MSG_XinFengInfo_NTY, CCentCfgFrameLogic::OnXinFengInfoNty, pThis, CCentCfgFrameLogic );
	REG_MSG_HANDLER( UI_CNS_SCHSTATE_NTY, CCentCfgFrameLogic::OnLightInfoNty, pThis, CCentCfgFrameLogic );
	REG_MSG_HANDLER( UI_TPAD_CENTRESLEEP_NTY, CCentCfgFrameLogic::OnCentSleepNty, pThis, CCentCfgFrameLogic );
}

void CCentCfgFrameLogic::UnRegMsg()
{
	
}

void CCentCfgFrameLogic::InitCfgFuncMenu()
{
	ARRAY<TMenuItem> aryItem;
	TMenuItem item; 
	
	item.SetItemName("环境灯光" ); 
	item.SetItemType("ImageItemMenuLight");
	aryItem.push_back(item);
	
	item.SetItemName("显示器" );  
	item.SetItemType("ImageItemMenuDisplay");
	aryItem.push_back(item);
	
	item.SetItemName("空调新风" );  
	item.SetItemType("ImageItemMenuXinFeng");
	aryItem.push_back(item);
	
	item.SetItemName("摄像机" );  
	item.SetItemType("ImageItemMenuCamera");
	aryItem.push_back(item);

	Value_ItemMenu valueMenu( &aryItem ); 
	valueMenu.m_strAlgroithm = IAlgorithm::strVert;
	UIFACTORYMGR_PTR->SetPropertyValue( valueMenu, m_strLstFunMenu, m_pWndTree ); 
}

bool CCentCfgFrameLogic::OnClickXinFengCfg( const IArgs& args )
{
	SwitchCfgTabWnd(g_strCentXinFengDlg);
	return true;
}

bool CCentCfgFrameLogic::OnClickCameraCfg( const IArgs& args )
{
	SwitchCfgTabWnd(g_strCentCameraDlg);
	return true;
}

bool CCentCfgFrameLogic::OnClickLightCfg( const IArgs& args )
{
	SwitchCfgTabWnd(g_strCentLightDlg);
	return true;
}

bool CCentCfgFrameLogic::OnClickDisplayCfg( const IArgs& args )
{
	SwitchCfgTabWnd(g_strCentDisplayDlg);
	return true;
}

void CCentCfgFrameLogic::SwitchCfgTabWnd( string strWnd )
{
	if ( m_strCurWnd == g_strCentDisplayDlg && strWnd != g_strCentDisplayDlg )
	{
		bool bChange = CCentCfgDisplayDlg::GetSingletonPtr()->IsCentCfgDisplayChange();
		if ( false == bChange )
		{
			UIDATAMGR_PTR->SetLstSelItem( m_strLstFunMenu, m_pWndTree, 2 );
			return;
		}
	}
	
	HideAllWnd();
	UIFACTORYMGR_PTR->ShowWindow(strWnd);
	m_strCurWnd = strWnd;
	m_strCfgCurWnd = strWnd;
}

LRESULT CCentCfgFrameLogic::OnCameraInfoNty( WPARAM wParam, LPARAM lParam )
{
	EmCamPowerMode aemCam[MAX_CNCAMERA_NUM];
	for (int i=0;i<3;i++)
	{
		aemCam[i] =  *((EmCamPowerMode*)wParam + i);
	}
	
	String strCamera1Info = "摄像机一：";
	strCamera1Info += CamStateToString(aemCam[0]);
	UIFACTORYMGR_PTR->SetCaption( "CentCfgCameraDlg/StcCamera1Info", strCamera1Info, NULL, TRUE );
	
	String strCamera2Info = "摄像机二：";
	strCamera2Info += CamStateToString(aemCam[1]);
	UIFACTORYMGR_PTR->SetCaption( "CentCfgCameraDlg/StcCamera2Info", strCamera2Info, NULL, TRUE );
	
	String strCamera3Info = "摄像机三：";
	strCamera3Info += CamStateToString(aemCam[2]);
	UIFACTORYMGR_PTR->SetCaption( "CentCfgCameraDlg/StcCamera3Info", strCamera3Info, NULL, TRUE);

	return S_OK;
}

String CCentCfgFrameLogic::CamStateToString( EmCamPowerMode& emSwitchState )
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
	default:
		strState = "关";
		break;
	}
	return strState;
}

LRESULT CCentCfgFrameLogic::OnDocCamInfoNty( WPARAM wParam, LPARAM lParam )
{
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
	UIFACTORYMGR_PTR->SetCaption( "CentCfgCameraDlg/StcDocCameraInfo", strDocCamera, NULL, TRUE );
	
	return S_OK;
}

LRESULT CCentCfgFrameLogic::OnAirInfoNty( WPARAM wParam, LPARAM lParam )
{
	u16 wSchTem = (u16)wParam;
    //当前不能获得空调开关,只有温度
	String strAirInfo = "空调：";
	
	s8 chAirTemP[8] = {0};
	sprintf( chAirTemP, "%u", wSchTem );
	strAirInfo += chAirTemP;
	strAirInfo += "℃";
	
	UIFACTORYMGR_PTR->SetCaption( "CentCfgXinFengDlg/StcAirInfo", strAirInfo, NULL, TRUE);
	return S_OK;
}

LRESULT CCentCfgFrameLogic::OnXinFengInfoNty( WPARAM wParam, LPARAM lParam )
{
	String strXinFengInfo = "新风：";
	
	
	s8 chXinFeng[8] = {0};
//	sprintf( chXinFeng, "%u", tXinFengInfo.m_byLevel );
	strXinFengInfo += ",";
	strXinFengInfo += chXinFeng;
	strXinFengInfo += "级";
	
	UIFACTORYMGR_PTR->SetCaption( "CentCfgXinFengDlg/StcXinFengInfo", strXinFengInfo, NULL, TRUE);
	
	return S_OK;
}

LRESULT CCentCfgFrameLogic::OnLightInfoNty( WPARAM wParam, LPARAM lParam )
{
	TCentreSchCfg tSchCfg = *(TCentreSchCfg*)wParam;
	//当前不能获得空调开关,只有温度
	String strAirInfo = "空调：";	
	s8 chAirTemP[8] = {0};
	sprintf( chAirTemP, "%u", tSchCfg.wSchTem );
	strAirInfo += chAirTemP;
	strAirInfo += "℃";
	
	UIFACTORYMGR_PTR->SetCaption( "CentCfgXinFengDlg/StcAirInfo", strAirInfo, NULL, TRUE);
	
	//设置灯光状态信息
	String strState;
	switch(tSchCfg.emSchMidLight)
	{
	case emSchMidLightOn:
		strState += "开";
		break;
	case emSchMidLightOff:
		strState += "关";
		break;
	case emSchMidLightInvalid:
		strState += "关";
		break;
	default:
		break;
	}
	String strLight1, strLight2, strLight3, strLight4, strLight5, strLight6, strLight7, strLight8;
	strLight1 = "灯光一：" + strState;
	UIFACTORYMGR_PTR->SetCaption( "CentCfgLightDlg/StcLight1Info", strLight1, NULL, TRUE);
	strLight2 = "灯光二：" + strState;
	UIFACTORYMGR_PTR->SetCaption( "CentCfgLightDlg/StcLight2Info", strLight2, NULL, TRUE);
	strLight3 = "灯光三：" + strState;
	UIFACTORYMGR_PTR->SetCaption( "CentCfgLightDlg/StcLight3Info", strLight3, NULL, TRUE);
	strLight4 = "灯光四：" + strState;
	UIFACTORYMGR_PTR->SetCaption( "CentCfgLightDlg/StcLight4Info", strLight4, NULL, TRUE);
	strLight5 = "灯光五：" + strState;
	UIFACTORYMGR_PTR->SetCaption( "CentCfgLightDlg/StcLight5Info", strLight5, NULL, TRUE);
	strLight6 = "灯光六：" + strState;
	UIFACTORYMGR_PTR->SetCaption( "CentCfgLightDlg/StcLight6Info", strLight6, NULL, TRUE);
	strLight7 = "灯光七：" + strState;
	UIFACTORYMGR_PTR->SetCaption( "CentCfgLightDlg/StcLight7Info", strLight7, NULL, TRUE);
	strLight8 = "灯光八：" + strState;
	UIFACTORYMGR_PTR->SetCaption( "CentCfgLightDlg/StcLight8Info", strLight8, NULL, TRUE);
	//Value_ItemLight LightState( &tSchCfg );
	//UIFACTORYMGR_PTR->SetPropertyValue( LightState, "CentCfgLightDlg/StcTPbg", NULL );	
	return S_OK;
}

LRESULT CCentCfgFrameLogic::OnCentSleepNty( WPARAM wParam, LPARAM lParam )
{
	//断开cns
	COMIFMGRPTR->DisConnect();
	UIFACTORYMGR_PTR->HideAllWindow();
	LOGICMGR_PTR->DestroyLogic();
	//隐藏cnstool，显示登录界面 		
	UIDATAMGR_PTR->NotifyOuterWnd( WM_TPTOOL_LOGINRESULT, em_LOGIN_LOGOFF, 0 );
	return S_OK;
}
