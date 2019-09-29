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
	//�б�ť����¼�
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
		UIFACTORYMGR_PTR->LoadScheme( "SchmConfMenuListDefault", m_pWndTree );   //��½���ʼ��Ĭ��ҳ��
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
	REG_MSG_HANDLER( UI_CNS_SCHTEMP_NTY, CCentCfgFrameLogic::OnAirInfoNty, pThis, CCentCfgFrameLogic );		//�յ���Ϣͨ���ƹ���Ϣ������
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
	
	item.SetItemName("�����ƹ�" ); 
	item.SetItemType("ImageItemMenuLight");
	aryItem.push_back(item);
	
	item.SetItemName("��ʾ��" );  
	item.SetItemType("ImageItemMenuDisplay");
	aryItem.push_back(item);
	
	item.SetItemName("�յ��·�" );  
	item.SetItemType("ImageItemMenuXinFeng");
	aryItem.push_back(item);
	
	item.SetItemName("�����" );  
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
	
	String strCamera1Info = "�����һ��";
	strCamera1Info += CamStateToString(aemCam[0]);
	UIFACTORYMGR_PTR->SetCaption( "CentCfgCameraDlg/StcCamera1Info", strCamera1Info, NULL, TRUE );
	
	String strCamera2Info = "���������";
	strCamera2Info += CamStateToString(aemCam[1]);
	UIFACTORYMGR_PTR->SetCaption( "CentCfgCameraDlg/StcCamera2Info", strCamera2Info, NULL, TRUE );
	
	String strCamera3Info = "���������";
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
		strState = "��";
		break;
	case emCamPowerOff:
		strState = "����";
		break;
	default:
		strState = "��";
		break;
	}
	return strState;
}

LRESULT CCentCfgFrameLogic::OnDocCamInfoNty( WPARAM wParam, LPARAM lParam )
{
	String strState;
	TCentreDCamCfg tDCamCfg = *(TCentreDCamCfg*)wParam;
	
	String strDocCamera = "�ĵ��������";
	
	switch(tDCamCfg.emDCamPowerMode)
	{
	case emDCamPowerOn:
		strState = "��";
		break;
	case emDCamPowerOff:
		strState = "��";
		break;
	case emDCamPowerToggle:
		strState = "����";
		break;
	default:
		strState = "��";
	}
	strDocCamera += strState;
	UIFACTORYMGR_PTR->SetCaption( "CentCfgCameraDlg/StcDocCameraInfo", strDocCamera, NULL, TRUE );
	
	return S_OK;
}

LRESULT CCentCfgFrameLogic::OnAirInfoNty( WPARAM wParam, LPARAM lParam )
{
	u16 wSchTem = (u16)wParam;
    //��ǰ���ܻ�ÿյ�����,ֻ���¶�
	String strAirInfo = "�յ���";
	
	s8 chAirTemP[8] = {0};
	sprintf( chAirTemP, "%u", wSchTem );
	strAirInfo += chAirTemP;
	strAirInfo += "��";
	
	UIFACTORYMGR_PTR->SetCaption( "CentCfgXinFengDlg/StcAirInfo", strAirInfo, NULL, TRUE);
	return S_OK;
}

LRESULT CCentCfgFrameLogic::OnXinFengInfoNty( WPARAM wParam, LPARAM lParam )
{
	String strXinFengInfo = "�·磺";
	
	
	s8 chXinFeng[8] = {0};
//	sprintf( chXinFeng, "%u", tXinFengInfo.m_byLevel );
	strXinFengInfo += ",";
	strXinFengInfo += chXinFeng;
	strXinFengInfo += "��";
	
	UIFACTORYMGR_PTR->SetCaption( "CentCfgXinFengDlg/StcXinFengInfo", strXinFengInfo, NULL, TRUE);
	
	return S_OK;
}

LRESULT CCentCfgFrameLogic::OnLightInfoNty( WPARAM wParam, LPARAM lParam )
{
	TCentreSchCfg tSchCfg = *(TCentreSchCfg*)wParam;
	//��ǰ���ܻ�ÿյ�����,ֻ���¶�
	String strAirInfo = "�յ���";	
	s8 chAirTemP[8] = {0};
	sprintf( chAirTemP, "%u", tSchCfg.wSchTem );
	strAirInfo += chAirTemP;
	strAirInfo += "��";
	
	UIFACTORYMGR_PTR->SetCaption( "CentCfgXinFengDlg/StcAirInfo", strAirInfo, NULL, TRUE);
	
	//���õƹ�״̬��Ϣ
	String strState;
	switch(tSchCfg.emSchMidLight)
	{
	case emSchMidLightOn:
		strState += "��";
		break;
	case emSchMidLightOff:
		strState += "��";
		break;
	case emSchMidLightInvalid:
		strState += "��";
		break;
	default:
		break;
	}
	String strLight1, strLight2, strLight3, strLight4, strLight5, strLight6, strLight7, strLight8;
	strLight1 = "�ƹ�һ��" + strState;
	UIFACTORYMGR_PTR->SetCaption( "CentCfgLightDlg/StcLight1Info", strLight1, NULL, TRUE);
	strLight2 = "�ƹ����" + strState;
	UIFACTORYMGR_PTR->SetCaption( "CentCfgLightDlg/StcLight2Info", strLight2, NULL, TRUE);
	strLight3 = "�ƹ�����" + strState;
	UIFACTORYMGR_PTR->SetCaption( "CentCfgLightDlg/StcLight3Info", strLight3, NULL, TRUE);
	strLight4 = "�ƹ��ģ�" + strState;
	UIFACTORYMGR_PTR->SetCaption( "CentCfgLightDlg/StcLight4Info", strLight4, NULL, TRUE);
	strLight5 = "�ƹ��壺" + strState;
	UIFACTORYMGR_PTR->SetCaption( "CentCfgLightDlg/StcLight5Info", strLight5, NULL, TRUE);
	strLight6 = "�ƹ�����" + strState;
	UIFACTORYMGR_PTR->SetCaption( "CentCfgLightDlg/StcLight6Info", strLight6, NULL, TRUE);
	strLight7 = "�ƹ��ߣ�" + strState;
	UIFACTORYMGR_PTR->SetCaption( "CentCfgLightDlg/StcLight7Info", strLight7, NULL, TRUE);
	strLight8 = "�ƹ�ˣ�" + strState;
	UIFACTORYMGR_PTR->SetCaption( "CentCfgLightDlg/StcLight8Info", strLight8, NULL, TRUE);
	//Value_ItemLight LightState( &tSchCfg );
	//UIFACTORYMGR_PTR->SetPropertyValue( LightState, "CentCfgLightDlg/StcTPbg", NULL );	
	return S_OK;
}

LRESULT CCentCfgFrameLogic::OnCentSleepNty( WPARAM wParam, LPARAM lParam )
{
	//�Ͽ�cns
	COMIFMGRPTR->DisConnect();
	UIFACTORYMGR_PTR->HideAllWindow();
	LOGICMGR_PTR->DestroyLogic();
	//����cnstool����ʾ��¼���� 		
	UIDATAMGR_PTR->NotifyOuterWnd( WM_TPTOOL_LOGINRESULT, em_LOGIN_LOGOFF, 0 );
	return S_OK;
}
