// MainWndLogic.cpp: implementation of the CMainWndLogic class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h" 
#include "mainFrameLogic.h"
#include "confCtrlLogic.h"
#include "msgBoxLogic.h"
 
////该逻辑单元对应的所有窗口名
 
const String CMainFrameLogic::m_strBtnToolMenu =  "btnToolMenu" ;
const String CMainFrameLogic:: m_strBtnLockScreen =  "btnLockScreen" ;


const String CMainFrameLogic:: m_strBtnAddrbook = "btnAddrBook";
const String CMainFrameLogic:: m_strBtnAddrbookMng = "btnAddrBookMg";
const String CMainFrameLogic::m_strBtnConftempLst = "btnConfTemplateLst" ; 
const String CMainFrameLogic::m_strBtnCnsLst =  "btnCnsLst";
const String CMainFrameLogic::m_strBtnMixaud = "btnMixaud";
const String CMainFrameLogic::m_strBtnTvw = "btnTvw"; 
const String CMainFrameLogic::m_strBtnAlarm = "btnAlarm";
const String CMainFrameLogic::m_strDlgConfManageMenu = "ConfManageMenuDlg";
const String CMainFrameLogic::m_strBtnPrePage = "btnPrePage";
const String CMainFrameLogic::m_strBtnNextPage = "btnNextPage";
const String CMainFrameLogic::m_strConfManageList = "ConfManageList";
const String CMainFrameLogic::m_strBtnVideo = "btnVedio" ;

//String   CMainFrameLogic::m_strDlgSimulateCns = g_stcStrSimulateCns1Dlg;
 
//String  g_strSimulateCnsDlgName;  //当前使用的模拟会场的界面名，便于界面切换的时候做隐藏和显示

  
 CMainFrameLogic *CMainFrameLogic::m_pLogic = NULL;
  
static UINT g_nUpdateMainMenuElapse;
 

static UINT g_nTimerID;   //timer 的id，用于刷新告警按钮

VOID  CALLBACK  CBTimerPoc( HWND hwnd, UINT  uMsg, UINT_PTR idEvent, DWORD dwTime  );

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
 
 
CMainFrameLogic::CMainFrameLogic()  
{   
	UIDATAMGR->SetCurSimulateDlgName( g_stcStrSimulateCns3Dlg )   ;
	g_nUpdateMainMenuElapse = 500;
	m_bAlarmOn = FALSE;
	m_emConfType = emConfUnKnown;
    const_cast<String &> (m_strBtnVideo) = g_stcStrMainMenuDlg + "/" + m_strBtnVideo;
    const_cast<String &> (m_strBtnAddrbook) = g_stcStrMainMenuDlg + "/" + m_strBtnAddrbook;
    const_cast<String &> (m_strBtnAddrbookMng) = g_stcStrMainMenuDlg + "/" + m_strBtnAddrbookMng;
	const_cast<String &> (m_strBtnConftempLst ) =  g_stcStrMainMenuDlg + "/" + m_strBtnConftempLst;
	const_cast<String &> (m_strBtnCnsLst) = g_stcStrMainMenuDlg + "/" + m_strBtnCnsLst;
	const_cast<String &> ( m_strBtnTvw ) = g_stcStrMainMenuDlg + "/" + m_strBtnTvw ;
	const_cast<String &> (m_strBtnMixaud) = g_stcStrMainMenuDlg + "/" + m_strBtnMixaud; 
	const_cast<String &> (m_strBtnAlarm) = g_stcStrMainMenuDlg + "/" + m_strBtnAlarm; 
	const_cast<String &> (m_strDlgConfManageMenu) = g_stcStrMainMenuDlg + "/" + m_strDlgConfManageMenu; 
	const_cast<String &> (m_strBtnPrePage) = m_strDlgConfManageMenu + "/" + m_strBtnPrePage; 
	const_cast<String &> (m_strBtnNextPage) = m_strDlgConfManageMenu + "/" + m_strBtnNextPage; 
	const_cast<String &> (m_strConfManageList) = m_strDlgConfManageMenu + "/" + m_strConfManageList;

}

CMainFrameLogic::~CMainFrameLogic()
{
	if ( m_pLogic != NULL )
	{   
		 UnRegMsg();
	   	 UnRegFunc();
	     delete m_pLogic;
		 m_pLogic = NULL;
	}
}
 

CMainFrameLogic* CMainFrameLogic::GetLogicPtr()
{
	if ( m_pLogic == NULL )
	{
		m_pLogic = new CMainFrameLogic(); 
	} 
	return m_pLogic;
}


void CMainFrameLogic::RegMsg()
{    
	REG_MSG_HANDLER( UI_UMS_START_CONFTEMPLATE_RSP, CMainFrameLogic::OnStratConftempRsp, m_pLogic, CMainFrameLogic );
    
    REG_MSG_HANDLER( UI_UMS_HANGUP_CONF_RSP, CMainFrameLogic::OnHungupConf , m_pLogic, CMainFrameLogic );  

	REG_MSG_HANDLER( UI_UMS_INVITE_CNS_RSP, CMainFrameLogic::OnInvitCnsRsp , m_pLogic, CMainFrameLogic );
     
 	REG_MSG_HANDLER( UI_CNS_CONFSTATE_NOTIFY, CMainFrameLogic::OnConfStateNotify, m_pLogic, CMainFrameLogic );
    REG_MSG_HANDLER( UI_CNS_HUNGUP_P2P_NOTIFY, CMainFrameLogic::OnHungupP2pConfNotify, m_pLogic, CMainFrameLogic );
    
	REG_MSG_HANDLER( UI_CNS_CNSINFO_NOTIFY, CMainFrameLogic::OnCnsInfoNotify, m_pLogic, CMainFrameLogic );
	//会场掉线通知
    REG_MSG_HANDLER( UI_CNS_ROOMOFFLINE, CMainFrameLogic::OnCnsOfflineNotify, m_pLogic, CMainFrameLogic );  
     
    REG_MSG_HANDLER( UI_UMS_UPDATE_CONFINFO, CMainFrameLogic::OnRefreshConfLst , m_pLogic, CMainFrameLogic );
    REG_MSG_HANDLER( UI_UMS_REFRESH_CONFCNS_LIST, CMainFrameLogic::OnRefreshConfLst , m_pLogic, CMainFrameLogic );
  
    REG_MSG_HANDLER( UI_UMS_GRAB_LOGIN_NOTIFY, CMainFrameLogic::GrabLoginNotify , m_pLogic, CMainFrameLogic );


    //呼叫动画显示 已达到5秒钟，主会场还未上线
    REG_MSG_HANDLER( UI_CMS_CALLING_TIME_OUT, CMainFrameLogic::CallingTimeOut , m_pLogic, CMainFrameLogic );
    //REG_MSG_HANDLER(  UI_UMS_CASCADE_CONF_NOTIFY, CMainFrameLogic::CascadeNotify , m_pLogic, CMainFrameLogic  );

    REG_MSG_HANDLER( UI_CMS_SHOW_ALARM_DLG, CMainFrameLogic::OnShowAlarmNotify, m_pLogic, CMainFrameLogic );

	REG_MSG_HANDLER( WM_CMS_UI_LOGIN_OK, CMainFrameLogic::OnRefreshConfLst, m_pLogic, CMainFrameLogic ); 

    REG_MSG_HANDLER( WM_CMS_UPDATE_CMAINMENU, CMainFrameLogic::OnRefreshConfLst, m_pLogic, CMainFrameLogic ); 
 
    //双流状态通知
    REG_MSG_HANDLER( UI_CNS_RECV_DUAL_NOTIFY, CMainFrameLogic::OnDualRecvStateNotify, m_pLogic, CMainFrameLogic ); 
    
	REG_MSG_HANDLER( UI_CNS_DUALOFFLINE_NOTIFY, CMainFrameLogic::OnDualOffLineNotify, m_pLogic, CMainFrameLogic ); 

    REG_MSG_HANDLER( UI_RECV_DUAL_INTERRUPT, CMainFrameLogic::OnDualRcvInterruptNotify, m_pLogic, CMainFrameLogic ); 

	REG_MSG_HANDLER( UI_CNS_LEAVECONF_NOTIFY, CMainFrameLogic::OnCnsLeaveConfNotify, m_pLogic, CMainFrameLogic ); 

    //系统待机
    REG_MSG_HANDLER( UI_TPAD_CENTRESLEEP_NTY, CMainFrameLogic::OnCentreSleepNotify, m_pLogic, CMainFrameLogic ); 
    
    REG_MSG_HANDLER( UI_CNS_UMSREASON_IND, CMainFrameLogic::OnUmsReasonInd, m_pLogic, CMainFrameLogic );

    //TPad Home键响应
    REG_MSG_HANDLER( UI_TPAD_HOMEKEY_NOTIFY, CMainFrameLogic::OnTPadHomeKeyNotify, m_pLogic, CMainFrameLogic );
}

void CMainFrameLogic::UnRegMsg()
{
//   	UN_REG_MSG_HANDLER(  UI_UMS_START_CONFTEMPLATE_RSP );
//   	UN_REG_MSG_HANDLER ( UI_UMS_INVITE_CNS_RSP );
//   	UN_REG_MSG_HANDLER( UI_UMS_HANGUP_CONF_RSP );
}

bool CMainFrameLogic::RegCBFun()
{   	 
	REG_GOBAL_MEMBER_FUNC( "CMainFrameLogic::InitWnd", CMainFrameLogic::InitWnd, m_pLogic, CMainFrameLogic ) ;
	REG_GOBAL_MEMBER_FUNC( "CMainFrameLogic::BtnToolMenuClick", CMainFrameLogic::BtnToolMenuClick, m_pLogic, CMainFrameLogic ) ;
	REG_GOBAL_MEMBER_FUNC( "CMainFrameLogic::BtnLockScreenClick", CMainFrameLogic::BtnLockScreenClick, m_pLogic, CMainFrameLogic ) ;
	REG_GOBAL_MEMBER_FUNC( "CMainFrameLogic::BtnAddrbookClick", CMainFrameLogic::BtnAddrbookClick, m_pLogic, CMainFrameLogic ) ;
	REG_GOBAL_MEMBER_FUNC( "CMainFrameLogic::BtnConftempClick", CMainFrameLogic::BtnConftempClick, m_pLogic, CMainFrameLogic ) ;
	REG_GOBAL_MEMBER_FUNC( "CMainFrameLogic::BtnCnsListClick", CMainFrameLogic::BtnCnsListClick, m_pLogic, CMainFrameLogic ) ; 
	REG_GOBAL_MEMBER_FUNC( "CMainFrameLogic::BtnMixAudClick", CMainFrameLogic::BtnMixAudClick, m_pLogic, CMainFrameLogic ) ;
	REG_GOBAL_MEMBER_FUNC( "CMainFrameLogic::BtnTvwClick", CMainFrameLogic::BtnTvwClick, m_pLogic, CMainFrameLogic ) ; 
	REG_GOBAL_MEMBER_FUNC( "CMainFrameLogic::BtnSaveToFileClick", CMainFrameLogic::BtnSaveToFileClick, m_pLogic, CMainFrameLogic ) ; 
	
    //会议管理界面中对应butn的响应事件
    REG_GOBAL_MEMBER_FUNC( "CMainFrameLogic::BtnAddrbookManageClick", CMainFrameLogic::BtnAddrbookManageClick, m_pLogic, CMainFrameLogic ) ; 
    REG_GOBAL_MEMBER_FUNC( "CMainFrameLogic::BtnConftempManageClick", CMainFrameLogic::BtnConftempManageClick, m_pLogic, CMainFrameLogic ) ; 
    REG_GOBAL_MEMBER_FUNC( "CMainFrameLogic::BtnConfInfoClick", CMainFrameLogic::BtnConfInfoClick, m_pLogic, CMainFrameLogic ) ; 


    //系统管理菜单	
	REG_GOBAL_MEMBER_FUNC( "CMainFrameLogic::BtnSysCfgClick", CMainFrameLogic::BtnSysCfgClick, m_pLogic, CMainFrameLogic ) ; 
    REG_GOBAL_MEMBER_FUNC( "CMainFrameLogic::BtnUserManageClick", CMainFrameLogic::BtnUserManageClick, m_pLogic, CMainFrameLogic ) ; 
    REG_GOBAL_MEMBER_FUNC( "CMainFrameLogic::BtnUserDefineClick", CMainFrameLogic::BtnUserDefineClick, m_pLogic, CMainFrameLogic ) ; 
    
    REG_GOBAL_MEMBER_FUNC( "CMainFrameLogic::BtnAlarmClick", CMainFrameLogic::BtnAlarmClick, m_pLogic, CMainFrameLogic ) ;
    
    REG_GOBAL_MEMBER_FUNC( "CMainFrameLogic::BtnVideoClick", CMainFrameLogic::BtnVideoClick, m_pLogic, CMainFrameLogic ) ;
    
	return true;
}
 
bool CMainFrameLogic::UnRegFunc()
{
	UN_REG_GOBAL_FUNC( "CMainFrameLogic::InitWnd" );
	return true;
}
 

bool CMainFrameLogic::InitWnd(  const IArgs & arg )
{   
	CWndLogicBase::InitWnd( arg );


    CreateWnd();
    CreateSimulateCnsDlg(); 
	InitConfMenu();

    UIManagePtr->LoadScheme( g_schmMainMenuCnsManage, NULL, g_stcStrMainMenuDlg, FALSE ); //25012-3-5

    UpdateMainMenuDlg();


    if ( UIDATAMGR->IsPcVersion() )
    {
        //PC版界面可以拖动
        Value_TransparentDlgMoveStatus valStatus;
        valStatus.bMove = TRUE;
        UIManagePtr->SetPropertyValue( valStatus, g_stcStrMainFrameDlg );

        UIManagePtr->ShowWindow( g_stcStrLoginDlg, true );
    }
    else
    {
        //Window* pWnd = UIManagePtr->GetWindowPtr( g_stcStrMainFrameDlg );
        //pWnd->PostMessage( WM_SYSCOMMAND, SC_MINIMIZE, 0 );
        //最小化再显示会闪一下，直接隐藏
        UIManagePtr->ShowWindow( g_stcStrMainFrameDlg, false );

        ComInterface->ConnectTPad();
    }

	return true;
}


void CMainFrameLogic::CreateWnd()
{
	UIManagePtr->ShowWindow( g_stcStrLoginDlg, false );
	UIManagePtr->ShowWindow( g_stcStrConnectCnsDlg, false );
    //UIManagePtr->ShowWindow( g_stcStrIpCfgDlg,false );
	   
    UIManagePtr->ShowWindow( g_stcStrScrnDisplayMenu, false );
    UIManagePtr->ShowWindow( g_stcStrMsgBox, false ); 
    UIManagePtr->ShowWindow( g_stcStrCallDlg, false );
    UIManagePtr->ShowWindow( g_stcStrAlarmInfoDlg, false );
    // UIManagePtr->ShowWindow( "PollLstManageMenu", false );

    UIManagePtr->ShowWindow( g_stcStrCnsLstDlg, false );
    
    UIManagePtr->ShowWindow( g_stcStrAudMixDlg, false );
    //UIManagePtr->ShowWindow( g_stcStrTvwDlg, false );
    UIManagePtr->ShowWindow( g_strDualSrcDlg, false );

    UIManagePtr->ShowWindow( g_strAddrShowOptnDlg, false );
	UIManagePtr->ShowWindow( g_stcStrAddrbookDlg, false ); 
    UIManagePtr->ShowWindow( g_stcStrAddrEditDlg, false );   
    
    UIManagePtr->ShowWindow( g_stcStrConftempDlg, false );
    // UIManagePtr->ShowWindow( g_stcStrConftempEdtDlg, false );

    UIManagePtr->ShowWindow( g_stcStrMainMenuDlg, false );

    UIManagePtr->ShowWindow( g_stcStrUserdefinedDlg, false );
    //UIManagePtr->ShowWindow( g_stcStrConfInfoDlg, false );
	UIManagePtr->ShowWindow( g_stcStrConfCnsCtrlDlg, false );	
    UIManagePtr->ShowWindow( g_stcStrUserManageDlg, false ); 
    UIManagePtr->ShowWindow( "SysCfgDlg", false ); 
    
    UIManagePtr->ShowWindow( g_stcStrFuncLstManageMenu, false ); 
    UIManagePtr->ShowWindow( g_stcStrVolumCtrlDlg, false ); 

    UIManagePtr->ShowWindow( g_stcStrVideoDlg, false );
    UIManagePtr->ShowWindow( g_stcStrLockScreenDlg, false );
	UIManagePtr->ShowWindow( g_strWaitingRefreshDlg, false );
     
    UIManagePtr->ShowWindow( g_stcStrTitleBarDlg, false );
}


void CMainFrameLogic::Clear()
{   
    UIManagePtr->ShowWindow( g_stcStrMainMenuDlg, FALSE ); 
	UIManagePtr->ShowWindow( UIDATAMGR->GetCurSimulateDlgName(), FALSE );
 //	UIManagePtr->SetTransparentDlgImage( g_stcStrMainFrameDlg, g_strMainFrameSimulateBkg );  
    UIManagePtr->LoadScheme( g_schmMainMenuCnsManage ,NULL,g_stcStrMainMenuDlg , FALSE ); 
    UIDATAMGR->setLocalCnsState( emLocalCnsIdle ); 	
    UIDATAMGR->SetCurSimulateDlgName( g_stcStrSimulateCns3Dlg );
	UIManagePtr->ShowWindow( m_strBtnAlarm, false, m_pWndTree );
	m_bAlarmOn = FALSE;
	m_emConfType = emConfUnKnown;
	CDragWindow* pDrag = CDragWindow::GetDragWindow();
	if ( pDrag != NULL )
	{
		pDrag->ClearUserData();
		pDrag->ShowWindow( SW_HIDE );
	}
}

bool CMainFrameLogic::BtnToolMenuClick( const IArgs & arg )
{
	CMsgDispatch::SendMessage( UI_CMS_CLICK_TOOL_BTN ,0 , 0 ); 
    CMsgDispatch::SendMessage( WM_CMS_HIDE_VEDIO ,0 , 0 ); 
    
	return true; 
}


bool CMainFrameLogic::BtnLockScreenClick( const IArgs & arg )
{  
	//判断其是否为pc版本
//	if ( UIDATAMGR->IsPcVersion() )
	{
		POINT pt;
		Value_WindowSize val;
		UIManagePtr->GetPropertyValue( val, g_stcStrLockScreenDlg );
		
		Value_WindowSize valParent;
		UIManagePtr->GetPropertyValue( valParent, g_stcStrMainFrameDlg );
		
		pt.x = ( valParent.nWidth - val.nWidth )/2;
	
		pt.y = 189;
		UIFACTORYMGR_PTR->SetWndPos( pt, g_stcStrLockScreenDlg, NULL, g_stcStrMainFrameDlg );
	}

	UIManagePtr->ShowWindow( g_stcStrLockScreenDlg, true );
	PrtMsg("\n-------------点击锁屏窗口**********\n");    //-------JYY 添加拷机打印
    CMsgDispatch::SendMessage( WM_CMS_HIDE_VEDIO ,0 , 0 ); 
	return true; 
}


bool CMainFrameLogic::BtnAddrbookClick( const IArgs & arg )
{   
    bool bOn = false;
    UIManagePtr->GetSwitchState( m_strBtnAddrbook, bOn , m_pWndTree );
    if ( bOn == true )
    {
		//判断其是否为pc版本
//		if ( UIDATAMGR->IsPcVersion() )
		{
			POINT pt;
			//pt.x = 441;
            Value_WindowSize val;
            UIManagePtr->GetPropertyValue( val, g_stcStrAddrbookDlg );
            
            Value_WindowSize valParent;
            UIManagePtr->GetPropertyValue( valParent, g_stcStrMainFrameDlg );
            
		    pt.x = ( valParent.nWidth - val.nWidth ) / 2;
			pt.y = 53; 
			UIFACTORYMGR_PTR->SetWndPos( pt, g_stcStrAddrbookDlg, NULL, g_stcStrMainFrameDlg );
		}
        UIManagePtr->ShowWindow( g_stcStrAddrbookDlg, true );
        CMsgDispatch::SendMessage( WM_CMS_HIDE_VEDIO ,0 , 0 ); 
    }
    else
    {
        UIManagePtr->ShowWindow( g_stcStrAddrbookDlg, false );
    }
	  
	return true;
}

bool CMainFrameLogic::BtnAddrbookManageClick( const IArgs & arg )
{   
    bool bOn = false;
    UIManagePtr->GetSwitchState( m_strBtnAddrbookMng, bOn , m_pWndTree );
    if ( bOn == true )
    {
		//判断其是否为pc版本
//		if ( UIDATAMGR->IsPcVersion() )
		{
			POINT pt;			
 			pt.x = 93; 			
 			pt.y = 53;		
			UIFACTORYMGR_PTR->SetWndPos( pt, g_stcStrAddrEditDlg, NULL, g_stcStrMainFrameDlg );			
		}
        UIManagePtr->ShowWindow( g_stcStrAddrEditDlg, true );
        CMsgDispatch::SendMessage( WM_CMS_HIDE_VEDIO ,0 , 0 ); 
    }
    else
    {
        UIManagePtr->ShowWindow( g_stcStrAddrEditDlg, false );
    }
 
	return true;
}

bool CMainFrameLogic::BtnConftempClick( const IArgs & arg )
{   
    bool bOn = false;
    UIManagePtr->GetSwitchState( m_strBtnConftempLst, bOn , m_pWndTree );
    if ( bOn == true )
    {   
        UIManagePtr->LoadScheme( "", NULL , g_stcStrConftempDlg );
		//判断其是否为pc版本
//		if ( UIDATAMGR->IsPcVersion() )
		{
			POINT pt;
			pt.x = 441;
			pt.y = 53; 
			UIFACTORYMGR_PTR->SetWndPos( pt, g_stcStrConftempDlg, NULL, g_stcStrMainFrameDlg );
		}
        UIManagePtr->ShowWindow(  g_stcStrConftempDlg, true );
        CMsgDispatch::SendMessage( WM_CMS_HIDE_VEDIO ,0 , 0 ); 
    }
    else
    {
        UIManagePtr->ShowWindow(  g_stcStrConftempDlg, false );
    }
       
	return true;
}

bool CMainFrameLogic::BtnConftempManageClick( const IArgs & arg )
{
    bool bOn = false;
    UIManagePtr->GetSwitchState( m_strBtnConftempLst, bOn , m_pWndTree );
    if ( bOn == true )
    {    
        UIManagePtr->ShowWindow(  g_stcStrConftempEdtDlg, true );
        CMsgDispatch::SendMessage( WM_CMS_HIDE_VEDIO ,0 , 0 ); 
    }
    else
    {
        UIManagePtr->ShowWindow(  g_stcStrConftempEdtDlg, false );
    }
       
	return true; 
}

/**	 
  * 功能:  点击会议信息but
  * @return   bool
  * @remarks  
  */
bool CMainFrameLogic::BtnConfInfoClick( const IArgs & arg )
{   
    bool bOn = false;
    UIManagePtr->GetSwitchState( m_strBtnMixaud, bOn , m_pWndTree );
    if ( bOn == true )
    {    
        UIManagePtr->ShowWindow(  g_stcStrConfInfoDlg, true );
        CMsgDispatch::SendMessage( WM_CMS_HIDE_VEDIO ,0 , 0 ); 
    }
    else
    {
        UIManagePtr->ShowWindow(  g_stcStrConfInfoDlg, false );
    }
       
	return true; 
}


bool CMainFrameLogic::BtnSysCfgClick( const IArgs & arg )
{ 
    bool bOn = false;
    UIManagePtr->GetSwitchState( m_strBtnAddrbook, bOn , m_pWndTree );
    if ( bOn == true )
    {
		//判断其是否为pc版本
		UIManagePtr->LoadScheme( "SchmSysCfg", NULL, "SysCfgDlg", false );
//		if ( UIDATAMGR->IsPcVersion() )
		{
			POINT pt;
			pt.x = 441;
			pt.y = 53;
			UIFACTORYMGR_PTR->SetWndPos( pt, "SysCfgDlg", NULL, g_stcStrMainFrameDlg );
		}
        UIManagePtr->ShowWindow( "SysCfgDlg", true );
        CMsgDispatch::SendMessage( WM_CMS_HIDE_VEDIO ,0 , 0 ); 
    }
    else
    {
        UIManagePtr->ShowWindow( "SysCfgDlg", false );
    }
    return true;
}

/**	 
* 功能:  点击用户管理button
* @return   bool
* @remarks  
*/
bool CMainFrameLogic::BtnUserManageClick( const IArgs & arg )
{   
    
    bool bOn = false;
    UIManagePtr->GetSwitchState( m_strBtnConftempLst, bOn , m_pWndTree );
    if ( bOn == true )
    {   
        UIManagePtr->LoadScheme("", NULL, g_stcStrUserManageDlg);
//		if ( UIDATAMGR->IsPcVersion() )
		{
			POINT pt;
			pt.x = 441;
			pt.y = 53;
			UIFACTORYMGR_PTR->SetWndPos( pt, g_stcStrUserManageDlg, NULL, g_stcStrMainFrameDlg );
		}
        UIManagePtr->ShowWindow(  g_stcStrUserManageDlg, true );
        CMsgDispatch::SendMessage( WM_CMS_HIDE_VEDIO ,0 , 0 ); 
    }
    else
    {
        UIManagePtr->ShowWindow(  g_stcStrUserManageDlg, false );
    }
    return true;   
}


/**	 
* 功能:  点击自定义button
* @return   bool
* @remarks  
*/
bool CMainFrameLogic::BtnUserDefineClick( const IArgs & arg )
{
	
    bool bOn = false;
    UIManagePtr->GetSwitchState( m_strBtnMixaud, bOn , m_pWndTree );
    if ( bOn == true )
    {   
        UIManagePtr->LoadScheme( "SchmUserDefined", NULL, g_stcStrUserdefinedDlg, false );
		//判断其是否为pc版本
//		if ( UIDATAMGR->IsPcVersion() )
		{
			POINT pt;
			pt.x = 441;
			pt.y = 53;
			UIFACTORYMGR_PTR->SetWndPos( pt, g_stcStrUserdefinedDlg, NULL, g_stcStrMainFrameDlg );
		}
        UIManagePtr->ShowWindow( g_stcStrUserdefinedDlg, true ); 
        CMsgDispatch::SendMessage( WM_CMS_HIDE_VEDIO ,0 , 0 ); 
    }
    else
    {
        UIManagePtr->ShowWindow(  g_stcStrUserdefinedDlg, false );
    }
    return true;
}


bool CMainFrameLogic::BtnCnsListClick( const IArgs & arg )
{ 
    bool bOn = false;
    UIManagePtr->GetSwitchState( m_strBtnConftempLst, bOn , m_pWndTree );
    if ( bOn == true )
    {   
//		if ( UIDATAMGR->IsPcVersion() )
		{
			POINT pt;
			pt.x = 441;
			pt.y = 53;
			UIFACTORYMGR_PTR->SetWndPos( pt, g_stcStrCnsLstDlg, NULL, g_stcStrMainFrameDlg );			
		}
        UIManagePtr->ShowWindow( g_stcStrCnsLstDlg, true ); 
        CMsgDispatch::SendMessage( WM_CMS_HIDE_VEDIO ,0 , 0 ); 
    }
    else
    {
        UIManagePtr->ShowWindow(  g_stcStrCnsLstDlg, false );
    }
    return true;
}

bool CMainFrameLogic::BtnMixAudClick( const IArgs & arg )
{    
    bool bOn = false;
    UIManagePtr->GetSwitchState( m_strBtnMixaud, bOn , m_pWndTree );
    if ( bOn == true )
    {    
//		if ( UIDATAMGR->IsPcVersion() )
		{
			POINT pt;
			pt.x = 441;
			pt.y = 53;
			UIFACTORYMGR_PTR->SetWndPos( pt, g_stcStrAudMixDlg, NULL, g_stcStrMainFrameDlg );			
		}
        UIManagePtr->ShowWindow( g_stcStrAudMixDlg, true ); 
        CMsgDispatch::SendMessage( WM_CMS_HIDE_VEDIO ,0 , 0 ); 
    }
    else
    {
        UIManagePtr->ShowWindow(  g_stcStrAudMixDlg, false );
    }
    return true;
}


bool CMainFrameLogic::BtnTvwClick( const IArgs & arg )
{ 
 
    bool bOn = false;
    UIManagePtr->GetSwitchState( m_strBtnTvw, bOn , m_pWndTree );
    if ( bOn == true )
    {    
        UIManagePtr->ShowWindow( g_stcStrTvwDlg, true ); 
        CMsgDispatch::SendMessage( WM_CMS_HIDE_VEDIO ,0 , 0 ); 
    }
    else
    {
        UIManagePtr->ShowWindow(  g_stcStrTvwDlg, false );
    }
    return true;
}

bool CMainFrameLogic::BtnAlarmClick( const IArgs & arg )
{
    if ( g_nTimerID != 0 )
    {
	    KillTimer( NULL, g_nTimerID );
        g_nTimerID = 0;
	    UIManagePtr->LoadScheme( "SchmAlarmOff", m_pWndTree, m_strBtnAlarm );
        m_bAlarmOn = TRUE;
    }

    if ( m_bAlarmOn )
    {
        //	if ( UIDATAMGR->IsPcVersion() )
        {
            POINT pt;
            Value_WindowSize val;
            UIManagePtr->GetPropertyValue( val, g_stcStrAlarmInfoDlg );
            
            Value_WindowSize valParent;
            UIManagePtr->GetPropertyValue( valParent, g_stcStrMainFrameDlg );
            pt.x = valParent.nWidth - 19 - val.nWidth;
            pt.y = valParent.nHeight - 80 - val.nWidth;
            UIFACTORYMGR_PTR->SetWndPos( pt, g_stcStrAlarmInfoDlg, NULL, g_stcStrMainFrameDlg );
            
        }
	    UIManagePtr->ShowWindow( g_stcStrAlarmInfoDlg, true );
    }
    else
    {
        UIManagePtr->ShowWindow( g_stcStrAlarmInfoDlg, false );
    }

    m_bAlarmOn = !m_bAlarmOn;
	
	return true;
}


bool CMainFrameLogic::BtnSaveToFileClick( const IArgs & arg )
{
	bool bRe = UIManagePtr->SaveToFile( /*g_stcStrMainFrameDlg */g_stcStrMainMenuDlg );   
	return bRe;
}

//显示码流图像界面  wparam：1 表示是要最大化显示
bool CMainFrameLogic::BtnVideoClick( const IArgs & args )
{   
	ShowVideo( FALSE );
	
    return true;
}

//2012-7-23
void CMainFrameLogic::ShowVideo( BOOL32 bFullScreen )
{
	WPARAM wp = 0;
	if (  bFullScreen )
    {
		wp = 1;
    }
    CMsgDispatch::SendMessage( WM_CMS_SHOWVIDEO, wp , 0 );
}

void CMainFrameLogic::CreateSimulateCnsDlg()
{
	TTPCnsInfo  tCnsInfo;
	u16 wRe = BusinessManagePtr->GetLocalCnsInfo( tCnsInfo ); 
	if ( wRe != NO_ERROR )
	{
		HANDLE_ERROR( ERR_CMS_Get_LOCAL_CNS_INFO );
		return;
	}

	switch( /*tCnsInfo.m_emLevel*/tCnsInfo.m_wScreenNum )
	{
	case 1: //1屏
		UIDATAMGR->SetCurSimulateDlgName( g_stcStrSimulateCns1Dlg ) ; 
		break;
	case 5:
        UIDATAMGR->SetCurSimulateDlgName( g_stcStrSimulateCns5Dlg ) ;
		break;
	default:   //3屏
        UIDATAMGR->SetCurSimulateDlgName( g_stcStrSimulateCns3Dlg ) ;
		break;
	}

	UIManagePtr->ShowWindow( UIDATAMGR->GetCurSimulateDlgName(), false );
}

void CMainFrameLogic::UpdateSimulateCnsDlg()
{	
	TTPCnsInfo  tCnsInfo;
	u16 wRe = BusinessManagePtr->GetLocalCnsInfo( tCnsInfo ); 
	if ( wRe != NO_ERROR )
	{
		HANDLE_ERROR( ERR_CMS_Get_LOCAL_CNS_INFO );
		return;
	}
    
    bool bShow = UIManagePtr->IsVisible( UIDATAMGR->GetCurSimulateDlgName() );

	switch( /*tCnsInfo.m_emLevel*/tCnsInfo.m_wScreenNum ) //2012-1-11 by yjj 根据实际屏的数目来显示,解决县级可以配3屏问题
	{
	case 1/*emTPSipCounty*/: //1屏
		if ( UIDATAMGR->GetCurSimulateDlgName() != g_stcStrSimulateCns1Dlg )
		{
			UIManagePtr->ShowWindow( UIDATAMGR->GetCurSimulateDlgName(), false );
            UIDATAMGR->SetCurSimulateDlgName( g_stcStrSimulateCns1Dlg ); 
            UIManagePtr->ShowWindow( UIDATAMGR->GetCurSimulateDlgName(), bShow );
		}		
		break;
	default:   //3屏
        if ( tCnsInfo.m_emLevel == emTPSipProvince )
        {
			if ( UIDATAMGR->GetCurSimulateDlgName() != g_stcStrSimulateCns5Dlg )
			{
				UIManagePtr->ShowWindow( UIDATAMGR->GetCurSimulateDlgName(), false );
				UIDATAMGR->SetCurSimulateDlgName( g_stcStrSimulateCns5Dlg ); 
                UIManagePtr->ShowWindow( UIDATAMGR->GetCurSimulateDlgName(), bShow );
			}		
        }
        else
        {
			if ( UIDATAMGR->GetCurSimulateDlgName() != g_stcStrSimulateCns3Dlg )
			{
				UIManagePtr->ShowWindow( UIDATAMGR->GetCurSimulateDlgName(), false );
				UIDATAMGR->SetCurSimulateDlgName( g_stcStrSimulateCns3Dlg ); 
                UIManagePtr->ShowWindow( UIDATAMGR->GetCurSimulateDlgName(), bShow );
			}			 
		}
		break;
	}   

}


BOOL32 CMainFrameLogic::CheckLinkState()
{
	BOOL32 bConnect  = ComInterface->IsConnect();
	if ( !bConnect ) 
	{  
		return false;
	} 
	return true;
}
  

/*
1.本地cns不在会议中：进入会控界面  （模拟屏界面 判断本地cns是否在会议中，如果不在，则禁用设置发言坐席选项  ； 同时，本地会场的 音量 和 双流 以及挂断操作都禁用）
2.本地cns在会议中则直接进入会议界面
3.若有级联会议通知，则市级会议 的 会场管理界面隐藏“挂断”和“双流”功能，主席会场界面有“挂断”和“双流”功能，其中“挂断”为挂断会议 
*/
void CMainFrameLogic::UpdateMainMenuDlg()
{    
    if ( m_pWndTree == NULL )
    { 
        return;
    } 
 

    if ( !BusinessManagePtr->IsConnect( ))
    {  
        PrtMsg(0,emEventTypeCmsWindow,"[CMainFrameLogic::UpdateMainMenuDlg]未连接，不刷新");
        return;
    }

     RefreshCallState();


    if ( UIDATAMGR->GetCurMainMenuType() == g_schmMainMenuSysManage || UIDATAMGR->GetCurMainMenuType() == g_schmMainMenuConfManage )
    {
        //如果不在会场管理界面，把m_emConfType置为emConfOtherUms，保证切到会场管理时可以刷新一次
        m_emConfType = emConfOtherUms;
        PrtMsg(0,emEventTypeCmsWindow,"[CMainFrameLogic::UpdateMainMenuDlg]当前方案%s,未在会场界面，不刷新", UIDATAMGR->GetCurMainMenuType().c_str() );
        return;
    } 

	BOOL32 bChange = FALSE;
  	TCMSConf tConfInfo;
    BOOL32 bOnline = BusinessManagePtr->IsInConf( &tConfInfo );  
    if ( bOnline )
	{    
		//点对点会议
		if ( tConfInfo.m_emConfType == emCallType_P2P )
		{
			if ( m_emConfType != emConfP2P )
			{
				m_emConfType = emConfP2P;
				UpdateConfMenu( emConfP2P ); 				
				PrtMsg(0,emEventTypeCmsWindow,"[CMainFrameLogic::UpdateMainMenuDlg]切换到点对点会议中界面");
				bChange = TRUE;
                UIManagePtr->LoadScheme( g_schmMainMenuCnsManageInconf,NULL, g_stcStrMainMenuDlg );	
                UIManagePtr->LoadScheme( g_schmSimScrPtpConf,NULL, UIDATAMGR->GetCurSimulateDlgName() );	
                                        
			}			
		}
// 		else if ( tConfInfo.m_emConfType == emConfOtherUms )
// 		{
// 			/*解决：关于跨ums呼叫cns的问题:   2011-12-13 by yjj
// 			[ Bug00071569 ]:【sp1】[tp]会议中，一个服务器上的会议呼叫另一个服务器上的会场A，则在会场A的会场控制台的模拟会场中未显示任何会议信息）
// 			 与江轶确认解决方案如下:登录 被非本域的ums呼走的 会场A ，cmc 显示点对点的会控界面（去除开启双流操作）*/
// 
// 			if ( m_emConfType != emConfOtherUms )
// 			{
// 				m_emConfType = emConfOtherUms;
// 				UpdateConfMenu( emConfOtherUms );				
// 				PrtMsg(0,emEventTypeCmsWindow,"[CMainFrameLogic::UpdateMainMenuDlg]本会场未在本域的会议中，切换到跨UMS会议中界面");
// 				bChange = TRUE;
//                 UIManagePtr->LoadScheme( g_schmMainMenuCnsManageInconf,NULL, g_stcStrMainMenuDlg );	
//                 UIManagePtr->LoadScheme( g_schmSimScrMiltConf,NULL, UIDATAMGR->GetCurSimulateDlgName() );	
// 			}			
// 		}
		else
		{
			BOOL32 bIsChairMan = BusinessManagePtr->IsLocalCnsChairMan();
			if (  bIsChairMan )
			{
				if ( m_emConfType != emConfMulti )
				{
					m_emConfType = emConfMulti;
					UpdateConfMenu( emConfMulti ); 					
					PrtMsg(0,emEventTypeCmsWindow,"[CMainFrameLogic::UpdateMainMenuDlg]切换到多点会议中界面");
					bChange = TRUE;
                    UIManagePtr->LoadScheme( g_schmMainMenuCnsManageInconf,NULL, g_stcStrMainMenuDlg );	
                    UIManagePtr->LoadScheme( g_schmSimScrMiltConf,NULL, UIDATAMGR->GetCurSimulateDlgName() );	
				}
			}
			else  
			{                
				if ( m_emConfType != emConfCascade )
				{
					//无会控操作权限
					m_emConfType = emConfCascade;
					UpdateConfMenu( emConfCascade );					
					PrtMsg(0,emEventTypeCmsWindow,"[CMainFrameLogic::UpdateMainMenuDlg]级联会议/分会场，切换到会议中无操作权限界面");
					bChange = TRUE;
                    UIManagePtr->LoadScheme( g_schmMainMenuCnsManageInconf,NULL, g_stcStrMainMenuDlg );	
                    UIManagePtr->LoadScheme( g_schmSimScrMiltConf,NULL, UIDATAMGR->GetCurSimulateDlgName() );	
				}
			} 
		} 
         		
        if ( bChange )
        {
           // UIManagePtr->LoadScheme( g_schmMainMenuCnsManageInconf,NULL, g_stcStrMainMenuDlg );	
            //界面类型改变，隐藏相关窗口
            UIManagePtr->ShowWindow( g_stcStrAddrbookDlg, false );
            UIManagePtr->ShowWindow( g_stcStrCallDlg, false );
            UIManagePtr->ShowWindow( g_stcStrConftempDlg, false );
        }			
    } 
    else
    {  
      
		if ( m_emConfType != emConfUnKnown )
		{
			m_emConfType = emConfUnKnown;
			UIManagePtr->LoadScheme( g_schmMainMenuCnsManage, NULL, g_stcStrMainMenuDlg ); 
			PrtMsg(0,emEventTypeCmsWindow,"[CMainFrameLogic::UpdateMainMenuDlg]切换到会场管理界面");
		
            //隐藏所有操作界面 dyy
			HideAllDlg();
			//还原菜单位置
			Value_HoriListOffset val;
			val.nOffset = 0;
			UIManagePtr->SetPropertyValue( val, m_strConfManageList, m_pWndTree );
		}		

    }
}



void CMainFrameLogic::RefreshCallState()
{ 
    //如果当前还没有主会场，则直接返回  2012-1-10 by yjj
    TTPCnsInfo tCnsInfo ;
    BusinessManagePtr->GetLocalCnsInfo( tCnsInfo );
    if ( strlen(tCnsInfo.m_achRoomName) == 0 )
    {    
        if ( UIDATAMGR->GetLocalCnsState() == emLocalCnsLocking )
        {    
            HIDE_MSG_BOX
        }

        PrtMsg(0,emEventTypeCmsWindow,"[CMainFrameLogic::RefreshCallState]本会场不在线");
        return  ;
    }
  
     
    BOOL32 bOnline = BusinessManagePtr->IsInConf( );  
    if (  bOnline )
    {   
        if ( UIDATAMGR->GetLocalCnsState() == emLocalCnsLocking )
        {    
            HIDE_MSG_BOX
        }
        else if ( UIDATAMGR->GetLocalCnsState() == emLocalCnsCalling )
        { 
            CMsgDispatch::SendMessage( UI_UMS_HIDE_CALLING_DLG, 0, 0 );
        } 
    }

     
 
}

/*EmTpStartConfRet
TP_StartConf_UnKonw,
TP_StartConf_Success,
TP_StartConf_ConfTemplateUnExist,	//会议模板不存在
TP_StartConf_ConfFull,				//UMS会议满
TP_StartConf_ConfExist,
};*/
 //PostEvent(UI_UMS_START_CONFTEMPLATE_RSP,tRe.m_wConfTemplateID,tRe.m_emReason);
HRESULT CMainFrameLogic::OnStratConftempRsp( WPARAM wparam, LPARAM lparam)
{   
   if ( m_pWndTree == NULL)
   {
       return NO_ERROR;
   }
   
   TStartConfResult tStartRe = *( TStartConfResult * )wparam;
   TTPConfTemplate tTemp = BusinessManagePtr->GetCurConfTemplate();
   if ( tStartRe.m_wConfTemplateID != tTemp.m_wID )
   {
       return S_FALSE;
   }

   if(lparam != NO_ERROR )
   {   
       if ( UIDATAMGR->GetLocalCnsState() == emLocalCnsCalling )
       {
           CMsgDispatch::SendMessage( UI_UMS_HIDE_CALLING_DLG , 0 , 0 );
       }

       UIDATAMGR->setLocalCnsState( emLocalCnsIdle );
 

       HANDLE_ERROR( lparam );
   }
 
	UpdateMainMenuDlg(); 

	return NO_ERROR;
}


/*
//呼叫结果
enum EmCnsCallReason	
{
EmCnsCallReason_success,
EmCnsCallReason_hungup,			//对端不接受或者主动挂断
EmCnsCallReason_Unreachable,	//对端不在线，无法呼叫
EmCnsCallReason_resourcefull,	//对端无可用资源
EmCnsCallReason_dstnotfind,		//目标不存在
EmCnsCallReason_Busy,			//对端忙
EmCnsCallReason_Local,			//本地原因
EmCnsCallReason_NoConf,			//会议不存在
EmCnsCallReason_Exist,			//对端已在本会议中
};
  PostEvent(UI_UMS_INVITE_CNS_RSP,(WPARAM)( tInviteInfo.m_wConfID),emRe);
*/
HRESULT CMainFrameLogic::OnInvitCnsRsp( WPARAM wparam, LPARAM lparam)
{   
	TCMSConf tConf;
	BOOL32 bInConf = ComInterface->IsInConf( &tConf );
	if ( !bInConf )
	{
		return NO_ERROR;
	}

   

	if( lparam != NO_ERROR  )
	{   
		CString tEpAddr = *(CString*)wparam;  
		CString str;    
		if ( !tEpAddr.IsEmpty() )
		{
			str.Format( "呼叫 %s 失败", tEpAddr );
		}

		HANDLE_ERROR( lparam, str );
	}
 
	return NO_ERROR;
}


 
HRESULT CMainFrameLogic::OnConfStateNotify( WPARAM wparam, LPARAM lparam)
{

    TTPCnsConfStatus confState = *(TTPCnsConfStatus *)lparam;
 
	if ( em_CALL_CALLING != confState.emState  )
    {   
        EMLocalCnsState emState = UIDATAMGR->GetLocalCnsState();
         
        if (  emLocalCnsCalling == emState )
        {   
            CMsgDispatch::SendMessage( UI_UMS_HIDE_CALLING_DLG, 0, 0 ); // 隐藏呼叫动画界面 
             
        }
		else if ( emLocalCnsWillHungup == emState && em_CALL_IDLE == confState.emState )	//会议结束,关闭弹出框  2013.10.31 jyy
		{////2012.11.14  by yjj Bug00113809
				HIDE_MSG_BOX	
		}
	 
	} 

	//解决刚入会时 mainmenu的状态由分会场权限到主会场权限转变的过程  2013.1.16 by yjj
	if (   confState.emState == em_CALL_CONNECTED &&
		   UIDATAMGR->GetLocalCnsState() == emLocalCnsCalling )
	{//显示 会场初始化 动画
		 
		 CMsgDispatch::SendMessage( UI_UMS_SHOW_CALLING_DLG, emTimerRefreshUI, 0 );       
		
// 		Window *pWnd = UIManagePtr->GetWindowPtr( g_stcStrMainFrameDlg );
// 		CMsgDispatch::SendMessage( UI_CNC_BEGINWAITING_REFRESH, (WPARAM)pWnd, emWaitConfInfo );
	} 



    UIDATAMGR->setLocalCnsState( ( EMLocalCnsState )( confState.emState ) ); //2012.11.14  byy Bug00113809
    
    //收到UI_UMS_UPDATE_CONFINFO后再刷新 2013-9-13 dyy
    //UpdateMainMenuDlg();  
    
    return NO_ERROR;
}

/*
////呼叫结果
enum EmCnsCallReason	
{
	EmCnsCallReason_success,
	EmCnsCallReason_hungup,			//本地挂断
	EmCnsCallReason_Unreachable,	//对端不在线，无法呼叫
	EmCnsCallReason_resourcefull,	//对端无可用资源
	EmCnsCallReason_dstnotfind,		//目标不存在
	EmCnsCallReason_Busy,			//对端忙
	EmCnsCallReason_Local,			//本地原因
	EmCnsCallReason_NoConf,			//会议不存在
	EmCnsCallReason_Exist,			//对端已在本会议中
	EmCnsCallReason_Rejected,		//对端拒绝
	EmCnsCallReason_peerhungup,		//对端挂断
//	EmCnsCallReason_AlreadyDual,    //对端在双流
	EmCnsCallReason_Abnormal,       //本地掉线挂断
	EmCnsCallReason_PeerAbnormal,   //对端掉线挂断
	EmCnsCallReason_ConfOver,	//会议结束
	EmCnsCallReason_cncallexception,	//接入模块(cncall)掉线
	EmCnsCallReason_ConfExist,		//会议已存在
	EmCnsCallReason_unknown,  
	
	  
}; 
*/


/*
CNC的会议结束提示消息
1.点对点会议
a.被挂断方,提示对端挂断
2.多点会议
a.分会场离开会议，在主会场提示XX会场离开会议
b.分会场被踢出会议，在主会场提示XX会场离开会议，在分会场提示对端挂断
c.主会场结会，分会场对端挂断，主会场提示会议结束
 //2012.8.24 根据需求修改 by yjj 
*/
HRESULT CMainFrameLogic::OnHungupP2pConfNotify( WPARAM wparam, LPARAM lparam )
{   
	 
    EmCnsCallReason emRe = (EmCnsCallReason)wparam;
    CString strErr = "";
    switch ( emRe )
    { 
    case EmCnsCallReason_success:
        strErr = "";
        break;
    case EmCnsCallReason_hungup://本地挂断
        strErr = "";
        break;
    case EmCnsCallReason_Unreachable:
        strErr = "对端不在线";
        break;
    case EmCnsCallReason_resourcefull:
        strErr = "已达到会场最大接入数";
        break;
    case EmCnsCallReason_dstnotfind:
        strErr = "对端不存在";
        break;
    case EmCnsCallReason_Busy:
        strErr = "对端忙";
        break;
    case EmCnsCallReason_Local:
        strErr = "本地原因";
        break;
    case EmCnsCallReason_Rejected:		//对端拒绝
        strErr = "对端拒绝";
        break;
    case EmCnsCallReason_peerhungup:		//对端挂断
        strErr = "会议结束：对端挂断";
        break;
// 	case EmCnsCallReason_Abnormal:   会有“本地会场掉线”的提示，本条不应提示出来 2012-6-11  
// 		strErr = ": 本端不在线";
// 		break;
	case EmCnsCallReason_PeerAbnormal:
		strErr = "对端不在线";
		break;
	case EmCnsCallReason_ConfOver:	//会议结束
		strErr = "会议结束"; 
		break;
	case EmCnsCallReason_cncallexception:
		strErr = "接入模块掉线";
		break;
	case EmCnsCallReason_ConfExist:		//会议已存在
		strErr = "会议已存在";
		break; 
	case EmCnsCallReason_unknown:
		strErr = ""; //2012-8-7 SE石文娟确认未知错误不做提示 by yjj
		break;
    default:
        strErr = "";
        break; 
    }


	//解决  Bug00113809   2012.11.20 by yjj
	EMLocalCnsState emLocalState  =  UIDATAMGR->GetLocalCnsState();
	if (  emLocalCnsCalling == emLocalState )
	{   
		CMsgDispatch::SendMessage( UI_UMS_HIDE_CALLING_DLG, 0, 0 ); // 隐藏呼叫动画界面 
	}
	else if( emLocalCnsWillHungup == emLocalState )
	{
		HIDE_MSG_BOX
	}

	UIDATAMGR->setLocalCnsState(emLocalCnsIdle);

    TCMSConf tConfInfo;
    BOOL32 bInConf = BusinessManagePtr->IsInConf( &tConfInfo );
    if ( bInConf )
    {   		
		if ( !strErr.IsEmpty() )
		{   
			if ( tConfInfo.m_emConfType == emCallType_Conf && emRe == EmCnsCallReason_peerhungup )
			{
				strErr = "对端挂断";
			}
			ShowPopMsg( /*"会议结束：" +*/strErr ); 
		}  
	
    } 
    else
    { 
		//不在会议中收到此消息，说明是点对点呼叫失败
		TTPCnsConfStatus tConfStatus = BusinessManagePtr->GetLocalCnsConfState();		
        if ( !strErr.IsEmpty() && tConfStatus.emState != em_CALL_CONNECTED )
		{
			ShowPopMsg( "呼叫失败：" + strErr );
		} 
    }
    
    UpdateMainMenuDlg();  


    //隐藏双流图像button
    UIManagePtr->ShowWindow( m_strBtnVideo, false, m_pWndTree ); 

    return S_OK;
}


HRESULT CMainFrameLogic::OnCnsInfoNotify( WPARAM wparam, LPARAM lparam )
{
    EmTPCNSInfoRst emRst = (EmTPCNSInfoRst)lparam;
    if ( m_pWndTree != NULL && emRst == emTPCNSInfoSuccess )
    { 
		UpdateSimulateCnsDlg();
    }
	
	return NO_ERROR;
}

HRESULT	CMainFrameLogic::OnCnsOfflineNotify( WPARAM wparam, LPARAM lparam )
{
	if ( m_pWndTree != NULL && (BOOL)lparam == TRUE )
    {
		ShowPopMsg( "本地会场掉线" );

		//BusinessManagePtr->DisConnect();		
	}
	return NO_ERROR;
}


HRESULT	CMainFrameLogic::OnRefreshConfLst( WPARAM wparam, LPARAM lparam )
{  
	if ( m_pWndTree != NULL )
	{     
		UpdateMainMenuDlg();  
	}
    return NO_ERROR;
}

HRESULT	CMainFrameLogic::OnRefreshConfCnsLst( WPARAM wparam, LPARAM lparam )
{
    if ( m_pWndTree != NULL )
    {   
        
         bool bLocalConf = BusinessManagePtr->IsInConf();
         if ( bLocalConf )
         {
              UpdateMainMenuDlg(); 
         }         
    }
    return NO_ERROR;
}


HRESULT CMainFrameLogic::OnHungupConf( WPARAM wparam, LPARAM lparam )
{
    if ( m_pWndTree != NULL )
    {    
        UpdateMainMenuDlg();
    }
    return NO_ERROR;
}

 
HRESULT CMainFrameLogic::GrabLoginNotify( WPARAM wparam, LPARAM lparam )
{
    if ( !UIDATAMGR->IsPcVersion() )
    {
        return NO_ERROR;
    }

    u32 dwIP = (u32)wparam;
    in_addr tAddr;
    tAddr.S_un.S_addr = dwIP; 
    CString msg;
    //msg.Format( "您已经被强制下线，该账户已在另一个地方登录", inet_ntoa(tAddr) );
    msg = _T("您已经被强制下线，该账户已在另一个地方登录");

    Args_MsgBox msgArg;
	msgArg.pOwnerWnd = UIManagePtr->GetWindowPtr( g_stcStrMainFrameDlg );

    HWND hWnd = msgArg.pOwnerWnd->GetSafeHwnd();
    if ( ::IsIconic(hWnd) ) 			
    {
        ::ShowWindow( hWnd, SW_RESTORE );
    }
	
    CMsgBoxLogic::GetLogicPtr()->SetDisCntMsgBoxFlag(TRUE);
	MSG_BOX( (LPCSTR)msg, FALSE, &msgArg);
	IArgs arg("");
	OnGrabLogin( arg ); 

    return NO_ERROR;
}

bool CMainFrameLogic::OnGrabLogin( const IArgs & arg )
{
	UIManagePtr->ShowWindow( g_stcStrTitleBarDlg, false );
	UIManagePtr->HideAllWindow();   
    
  	UIManagePtr->ShowWindow( g_stcStrLoginDlg );
	return true;
}

HRESULT CMainFrameLogic::OnShowAlarmNotify( WPARAM wparam, LPARAM lparam )
{
	UIManagePtr->ShowWindow( m_strBtnAlarm, true, m_pWndTree );
	g_nTimerID = SetTimer( NULL, NULL, g_nUpdateMainMenuElapse, CBTimerPoc );
	return NO_ERROR;
}

void CMainFrameLogic::UpdateAlarmImg()
{
	if ( m_bAlarmOn )
	{
		UIManagePtr->LoadScheme( "SchmAlarmOn", m_pWndTree, m_strBtnAlarm );
	}
	else
	{
		UIManagePtr->LoadScheme( "SchmAlarmOff", m_pWndTree, m_strBtnAlarm );
	}
	m_bAlarmOn = !m_bAlarmOn;
}


HRESULT CMainFrameLogic::CallingTimeOut( WPARAM wparam, LPARAM lparam )
{   
    UpdateMainMenuDlg();
    return NO_ERROR;
}

VOID  CALLBACK  CBTimerPoc( HWND hwnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime )
{
	if ( idEvent == g_nTimerID )
	{
		CMainFrameLogic::GetLogicPtr()->UpdateAlarmImg();
	}
}


void CMainFrameLogic::UpdateConfMenu( EM_ConfType emConfType )
{
	TCMSConf tConfInfo;
	BOOL32 bRe =  BusinessManagePtr->IsInConf( &tConfInfo );
	if ( !bRe )
    {        
        return;	
	}

    CString strImgPath;
    String Path = UIManagePtr->GetImagePath();
    strImgPath.Format( "%s", Path.c_str() );
    
    vector<TConfMenuInfo>* pMemu = UIManagePtr->GetConfMenu(); 

    switch( emConfType)
    { 
    case emConfCascade:
        {
            for ( int i = 0; i < pMemu->size(); i++ )
            {
                TConfMenuInfo tMenuInfo = pMemu->at(i);
                
                if ( tMenuInfo.strName == MENU_ENDCONF )
                { 	
                    tMenuInfo.strItemFunc = "CConfCnsLstLogic::BtnHangupLocalCnsClick";
                    tMenuInfo.strImgFolder = strImgPath + "confmainmenu\\btnConfLeave";                   
                }              
                
                if ( (tMenuInfo.strName == MENU_AUDMIX) || (tMenuInfo.strName == MENU_TVW) 
                   // || (tMenuInfo.strName == MENU_CNSDUAL)  为融合h323终端  去除该限制  2012.8.29 by yjj
				   || (tMenuInfo.strName == MENU_CNSPOLL) || (tMenuInfo.strName == MENU_ADDRBOOK)  )
                { 
                    tMenuInfo.bShow = FALSE; 
                }
				else
				{
					tMenuInfo.bShow = TRUE; 
				}
                
                pMemu->at(i) = tMenuInfo;            
            }
        }
        break;
    case emConfP2P:
        {
             for ( int i = 0; i < pMemu->size(); i++ )
            {
                TConfMenuInfo tMenuInfo = pMemu->at(i);
                
                if ( tMenuInfo.strName == MENU_ENDCONF )
                {  
                    tMenuInfo.strItemFunc = "CConfCnsLstLogic::BtnHangupConfClick";
                    tMenuInfo.strImgFolder = strImgPath + "confmainmenu\\btnConfEnd";                  
                }
                
                
                if ( (tMenuInfo.strName == MENU_AUDMIX) || (tMenuInfo.strName == MENU_TVW) || (tMenuInfo.strName == MENU_CNSCTRL) 
					|| (tMenuInfo.strName == MENU_CNSPOLL) /*|| (tMenuInfo.strName == MENU_ADDRBOOK)*/ )
                {                   
                    tMenuInfo.bShow = FALSE;                    
                }	
				else
				{
					tMenuInfo.bShow = TRUE; 
				}
                
                pMemu->at(i) = tMenuInfo;               
             }
        }
        break;
    case emConfOtherUms:
        {
            for ( int i = 0; i < pMemu->size(); i++ )
            {
            TConfMenuInfo tMenuInfo = pMemu->at(i);

            if ( tMenuInfo.strName == MENU_ENDCONF )
            { 	
                tMenuInfo.strItemFunc = "CConfCnsLstLogic::BtnHangupLocalCnsClick";
                tMenuInfo.strImgFolder = strImgPath + "confmainmenu\\btnConfLeave";                   
            } 


            if ( (tMenuInfo.strName == MENU_AUDMIX) || (tMenuInfo.strName == MENU_TVW) || (tMenuInfo.strName == MENU_CNSCTRL) 
                || (tMenuInfo.strName == MENU_CNSPOLL) || (tMenuInfo.strName == MENU_ADDRBOOK) || (tMenuInfo.strName == MENU_CNSDUAL) )
            {                   
                tMenuInfo.bShow = FALSE;                    
            }	
            else
            {
                tMenuInfo.bShow = TRUE; 
            }

            pMemu->at(i) = tMenuInfo;               
            }
        }
        break;
    default:
        {
            for ( int i = 0; i < pMemu->size(); i++ )
            {
                TConfMenuInfo tMenuInfo = pMemu->at(i);
                
                if ( tMenuInfo.strName == MENU_ENDCONF )
                {                     
                    tMenuInfo.strItemFunc = "CConfCnsLstLogic::BtnHangupConfClick";
                    tMenuInfo.strImgFolder = strImgPath + "confmainmenu\\btnConfEnd";                 
                }
                                                              
                tMenuInfo.bShow = TRUE;                 	
                
                pMemu->at(i) = tMenuInfo;               
            }
        }
    }

	//Value_HoriListConfMenu valueMenu( pMemu );
	//UIManagePtr->SetPropertyValue( valueMenu, m_strConfManageList, m_pWndTree );

	//在MainMenuLogic一起刷新 Bug00158557 添加会议类型参数进行传递 dyy 2014-1-24 
	CMsgDispatch::SendMessage( WM_CMS_UPDATE_CONFMENU, 0, (LPARAM)emConfType );
}


void CMainFrameLogic::InitConfMenu()
{
    vector<TConfMenuInfo>*pMemu = UIManagePtr->GetConfMenu();
    pMemu->clear();
 
	CString strImgPath;
	String Path = UIManagePtr->GetImagePath();
	strImgPath.Format( "%s", Path.c_str() );

	TConfMenuInfo tMenuInfo;
	//结束会议
	tMenuInfo.strName = MENU_ENDCONF;   
	tMenuInfo.nIndex = 0;
	tMenuInfo.strItemType = "ConfMenuButtonItem";
	tMenuInfo.strItemFunc = "CConfCnsLstLogic::BtnHangupConfClick";
	tMenuInfo.strImgFolder = strImgPath + "confmainmenu\\btnConfEnd";
	pMemu->push_back( tMenuInfo );

	//会场控制
	tMenuInfo.strName = MENU_CNSCTRL;
	tMenuInfo.nIndex = 1;
	tMenuInfo.strItemType = "ConfMenuCheckItem";
	tMenuInfo.strItemFunc = "CMainMenuLogic::OnBtnCnsCtrlClick";
	tMenuInfo.strImgFolder = strImgPath + "confmainmenu\\btnConfCtrl";
	pMemu->push_back( tMenuInfo );

	//会议讨论   
	tMenuInfo.strName = MENU_AUDMIX;
	tMenuInfo.nIndex = 2;
	tMenuInfo.strItemType = "ConfMenuCheckItem";
	tMenuInfo.strItemFunc = "CMainMenuLogic::OnBtnAudMixClick";
	tMenuInfo.strImgFolder = strImgPath + "confmainmenu\\btnConfAudMixOn";
	pMemu->push_back( tMenuInfo );

	//画中画
	tMenuInfo.strName = MENU_PIP;
	tMenuInfo.nIndex = 3;
	tMenuInfo.strItemType = "ConfMenuButtonItem";
	tMenuInfo.strItemFunc = "CMainMenuLogic::OnBtnPIPClick";
	tMenuInfo.strImgFolder = strImgPath + "confmainmenu\\btnConfPIPOn";
	pMemu->push_back( tMenuInfo );

	//电视墙
// 	tMenuInfo.strName = MENU_TVW;
// 	tMenuInfo.nIndex = 3;
// 	tMenuInfo.strItemType = "ConfMenuCheckItem";
// 	tMenuInfo.strItemFunc = "CMainMenuLogic::OnBtnTvwClick";
// 	tMenuInfo.strImgFolder = strImgPath + "btnConfTvw";
// 	pMemu->push_back( tMenuInfo );

	//会场轮询
	tMenuInfo.strName = MENU_CNSPOLL;
	tMenuInfo.nIndex = 4;
	tMenuInfo.strItemType = "ConfMenuButtonItem";
	tMenuInfo.strItemFunc = "CMainMenuLogic::OnBtnCnsPoll";
	tMenuInfo.strImgFolder = strImgPath + "confmainmenu\\btnConfPollOn";
	pMemu->push_back( tMenuInfo );

	//麦克风开关
	tMenuInfo.strName = MENU_MUTE;
	tMenuInfo.nIndex = 5;
	tMenuInfo.strItemType = "ConfMenuButtonItem";
	tMenuInfo.strItemFunc = "CMainMenuLogic::OnBtnLocalCnsMute";
	tMenuInfo.strImgFolder = strImgPath + "confmainmenu\\btnConfMuteOn";
	pMemu->push_back( tMenuInfo );

	//扬声器开关
	tMenuInfo.strName = MENU_QUITE;
	tMenuInfo.nIndex = 6;
	tMenuInfo.strItemType = "ConfMenuButtonItem";
	tMenuInfo.strItemFunc = "CMainMenuLogic::OnBtnLocalCnsQuite";
	tMenuInfo.strImgFolder = strImgPath + "confmainmenu\\btnConfQuiteOn";
	pMemu->push_back( tMenuInfo );

	//本方演示开关
	tMenuInfo.strName = MENU_CNSDUAL;
	tMenuInfo.nIndex = 7;
	tMenuInfo.strItemType = "ConfMenuButtonItem";
	tMenuInfo.strItemFunc = "CMainMenuLogic::OnBtnLocalCnsDual";
	tMenuInfo.strImgFolder = strImgPath + "confmainmenu\\btnConfDualOn";
	pMemu->push_back( tMenuInfo );

	//扬声器
	tMenuInfo.strName = MENU_SPEAKER;
	tMenuInfo.nIndex = 8;
	tMenuInfo.strItemType = "ConfMenuCheckItem";
	tMenuInfo.strItemFunc = "CMainMenuLogic::OnBtnCnsSpeaker";
	tMenuInfo.strImgFolder = strImgPath + "confmainmenu\\btnConfSpk";
	pMemu->push_back( tMenuInfo );

	//麦克风
	tMenuInfo.strName = MENU_MIC;
	tMenuInfo.nIndex = 9;
	tMenuInfo.strItemType = "ConfMenuCheckItem";
	tMenuInfo.strItemFunc = "CMainMenuLogic::OnBtnCnsMic";
	tMenuInfo.strImgFolder = strImgPath + "confmainmenu\\btnConfMic";
	pMemu->push_back( tMenuInfo );

	//演示源
	tMenuInfo.strName = MENU_DUALSRC;
	tMenuInfo.nIndex = 10;
	tMenuInfo.strItemType = "ConfMenuCheckItem";
	tMenuInfo.strItemFunc = "CMainMenuLogic::OnBtnDualSrc";
	tMenuInfo.strImgFolder = strImgPath + "confmainmenu\\btnDualSrc";
	pMemu->push_back( tMenuInfo );

	//地址簿
	tMenuInfo.strName = MENU_ADDRBOOK;
	tMenuInfo.nIndex = 11;
	tMenuInfo.strItemType = "ConfMenuCheckItem";
	tMenuInfo.strItemFunc = "CMainMenuLogic::OnBtnAddrbookClick";
	tMenuInfo.strImgFolder = strImgPath + "confmainmenu\\btnConfAddr";
	pMemu->push_back( tMenuInfo );


    UIManagePtr->UpdateConfMenuAccordFile();

}


HRESULT CMainFrameLogic::OnDualRecvStateNotify( WPARAM wparam, LPARAM lparam )
{

    BOOL32 bDual = (BOOL32)wparam;
    if ( bDual )
    {
        UIManagePtr->ShowWindow( m_strBtnVideo, true, m_pWndTree ); 

		//规格更改，所有接收方都全屏显示
// 		BOOL32 bDual = BusinessManagePtr->IsLocalCnsDual();
// 	 	if ( !bDual )  //若本方只是接收方，则直接全屏显示双流图像

        //TPad版cnc主窗不可见时不显示 dyy 2013年8月2日
        if ( !UIDATAMGR->IsPcVersion() )
        {
            if ( !UIManagePtr->IsVisible( g_stcStrMainFrameDlg ) ) 			
            {
                return S_OK;
            }
        }
        //界面锁屏时不显示全屏演示图像
        if ( !UIDATAMGR->IsUILockScreen() )
		{   	 
			Value_SwitchState vState;
			vState.bState = true;
			UIManagePtr->SetPropertyValue( vState, m_strBtnVideo);
			ShowVideo( TRUE );
		}		
    
    }
    else
    {
        UIManagePtr->ShowWindow( m_strBtnVideo, false, m_pWndTree ); 
		CMsgDispatch::SendMessage( WM_CMS_HIDE_VEDIO, 0 , 0 );
    }
    return S_OK;
}

HRESULT CMainFrameLogic::OnDualOffLineNotify( WPARAM wparam, LPARAM lparam )
{
	if ( m_pWndTree != NULL )
    {
		ShowPopMsg( "双流源掉线" );	
	}
	return NO_ERROR;
}


/*
enum EmTPChannelReason
{
emTPChannelReasonBegin,
emTPChannelDisconnectNormal,
emTPDualOffLine, 
};
*/
HRESULT CMainFrameLogic::OnDualRcvInterruptNotify( WPARAM wparam, LPARAM lparam )
{   
    if ( m_pWndTree != NULL )
    {  
        EmTPChannelReason reason = (EmTPChannelReason)wparam;
        CString str = "";
        switch( reason )
        {
        case emTPChannelReasonBegin:
			str = "";
			break;
        case emTPChannelDisconnectNormal:
            str = "通道异常断开";
            break;
        case emTPDualOffLine:
            str = "双流源掉线";
            break;
		case emTPForceStop:
			str = "双流源被抢断";
            break;
        default:
            str = "未知原因";
        }

        ShowPopMsg( "接收双流终止: " + str );	
    }
    return NO_ERROR;
}


HRESULT CMainFrameLogic::OnCnsLeaveConfNotify( WPARAM wparam, LPARAM lparam )
{
	if ( m_pWndTree == NULL )
	{
		return S_FALSE;
	}

    BOOL32 bChair = BusinessManagePtr->IsLocalCnsChairMan();
    char *pCnsName = (char*)lparam;
    if ( bChair && NULL != pCnsName  )
    { 
        CString str;
        str.Format( "会场 %s 离开会议", pCnsName );
        ShowPopMsg( str );	
    }
    return S_OK;
}

HRESULT CMainFrameLogic::OnCentreSleepNotify( WPARAM wparam, LPARAM lparam )
{
    if ( UIDATAMGR->IsPcVersion() )
    {
        BusinessManagePtr->DisConnect();
    }
    return NO_ERROR;
}

HRESULT CMainFrameLogic::OnUmsReasonInd( WPARAM wparam, LPARAM lparam )
{
    if ( m_pWndTree == NULL )
    {
        return S_FALSE;
	}

    TTPUmsReasonInd tReason;
    memcpy( &tReason, (TTPUmsReasonInd*)wparam, sizeof( TTPUmsReasonInd ) );

    CString strMsg;

    switch( tReason.m_dwReason )
    {
    case TP_UMS_Discard_Start:
        strMsg = _T("开启讨论失败：媒体资源不足");
        break;
    case TP_UMS_Discard_AddEp:
        strMsg = _T("添加会场失败：媒体资源不足");
        break;
    case TP_UMS_Discard_EpOnLine:
        {
            u32 dwEpId = tReason.m_dwReserve1;
            TCMSConf tConf;
            BOOL bInConf = ComInterface->IsInConf( &tConf );
            if ( bInConf )
            {
                TCnsInfo *tCnsInfo = tConf.GetCnsInfoByID( dwEpId );
                if ( tCnsInfo != NULL )
                {
                    strMsg.Format( "会场%s离开讨论：媒体资源不足", tCnsInfo->m_achRoomName );
                }
            }
        }        
        break;
    case TP_UMS_Discard_Error:
        strMsg = _T("会议讨论关闭：媒体资源不足");
        break;
    default:
        break;
    }

    if ( !strMsg.IsEmpty() )
    {
        ShowPopMsg( strMsg );
    }

    return S_OK;
}

HRESULT CMainFrameLogic::OnTPadHomeKeyNotify( WPARAM wparam, LPARAM lparam )
{
    //响应Home键
    CMsgDispatch::SendMessage( WM_CMS_HIDE_VEDIO ,0 , 0 );

    if ( UIManagePtr->IsVisible( g_stcStrLockScreenDlg ) )
    {
        UIManagePtr->ShowWindow( g_stcStrLockScreenDlg, false );
    }

    UIManagePtr->ShowWindow( g_stcStrToolMenuDlg, false );
    UIManagePtr->ShowWindow( g_stcStrMainFrameDlg, false ); 

    return NO_ERROR;
}


void CMainFrameLogic::HideAllDlg()
{    
    if ( UIManagePtr->IsVisible( g_stcStrVolumCtrlDlg ) )
    {
        UIManagePtr->ShowWindow( g_stcStrVolumCtrlDlg, false );
    }
    if ( UIManagePtr->IsVisible( g_stcStrConftempEdtDlg ) )
    {
        UIManagePtr->ShowWindow( g_stcStrConftempEdtDlg, false );
    }
    if ( UIManagePtr->IsVisible( g_stcStrAddrbookDlg ) )
    {
        UIManagePtr->ShowWindow( g_stcStrAddrbookDlg, false );
    }
    if ( UIManagePtr->IsVisible( g_stcStrAddrEditDlg ) )
    {
        UIManagePtr->ShowWindow( g_stcStrAddrEditDlg, false );
    }
    if ( UIManagePtr->IsVisible( g_stcStrConftempDlg ) )
    {
        UIManagePtr->ShowWindow( g_stcStrConftempDlg, false );
    }
    if ( UIManagePtr->IsVisible( g_stcStrCnsLstDlg ) )
    {
        UIManagePtr->ShowWindow( g_stcStrCnsLstDlg, false );
    }
    if ( UIManagePtr->IsVisible( g_stcStrConfCnsCtrlDlg ) )
    {
        UIManagePtr->ShowWindow( g_stcStrConfCnsCtrlDlg, false );
    }
    if ( UIManagePtr->IsVisible( g_stcStrAudMixDlg ) )
    {
        UIManagePtr->ShowWindow( g_stcStrAudMixDlg, false );
    }
    if ( UIManagePtr->IsVisible( g_stcStrUserManageDlg ) )
    {
        UIManagePtr->ShowWindow( g_stcStrUserManageDlg, false );
    }
    if ( UIManagePtr->IsVisible( g_stcStrUserdefinedDlg ) )
    {
        UIManagePtr->ShowWindow( g_stcStrUserdefinedDlg, false );
    }
    if ( UIManagePtr->IsVisible( g_stcStrHungupConfPopDlg ) )
    {
        UIManagePtr->ShowWindow( g_stcStrHungupConfPopDlg, false );
    }
    if ( UIManagePtr->IsVisible( g_stcStrIpCfgDlg ) )
    {
        UIManagePtr->ShowWindow( g_stcStrIpCfgDlg, false );
    }
    if ( UIManagePtr->IsVisible( g_stcStrVideoDlg ) )
    {
        UIManagePtr->ShowWindow( g_stcStrVideoDlg, false );
    }
    if ( UIManagePtr->IsVisible( g_stcStrAlarmInfoDlg ) )
    {
        UIManagePtr->ShowWindow( g_stcStrAlarmInfoDlg, false );
    }
    if ( UIManagePtr->IsVisible( g_strDualSrcDlg ) )
    {
        UIManagePtr->ShowWindow( g_strDualSrcDlg, false );
    }
    if ( UIManagePtr->IsVisible( g_strSysStandBy ) )
    {
        UIManagePtr->ShowWindow( g_strSysStandBy, false );
    }
    if ( UIManagePtr->IsVisible( g_strNetManageCfg ) )
    {
        UIManagePtr->ShowWindow( g_strNetManageCfg, false );
    }
    if ( UIManagePtr->IsVisible( g_stcStrFuncLstManageMenu ) )
    {
        UIManagePtr->ShowWindow( g_stcStrFuncLstManageMenu, false );
    }
    
}