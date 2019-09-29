// MainWndLogic.cpp: implementation of the CMainWndLogic class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h" 
#include "mainFrameLogic.h"
#include "confCtrlLogic.h"
#include "msgBoxLogic.h"
 
////���߼���Ԫ��Ӧ�����д�����
 
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
 
//String  g_strSimulateCnsDlgName;  //��ǰʹ�õ�ģ��᳡�Ľ����������ڽ����л���ʱ�������غ���ʾ

  
 CMainFrameLogic *CMainFrameLogic::m_pLogic = NULL;
  
static UINT g_nUpdateMainMenuElapse;
 

static UINT g_nTimerID;   //timer ��id������ˢ�¸澯��ť

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
	//�᳡����֪ͨ
    REG_MSG_HANDLER( UI_CNS_ROOMOFFLINE, CMainFrameLogic::OnCnsOfflineNotify, m_pLogic, CMainFrameLogic );  
     
    REG_MSG_HANDLER( UI_UMS_UPDATE_CONFINFO, CMainFrameLogic::OnRefreshConfLst , m_pLogic, CMainFrameLogic );
    REG_MSG_HANDLER( UI_UMS_REFRESH_CONFCNS_LIST, CMainFrameLogic::OnRefreshConfLst , m_pLogic, CMainFrameLogic );
  
    REG_MSG_HANDLER( UI_UMS_GRAB_LOGIN_NOTIFY, CMainFrameLogic::GrabLoginNotify , m_pLogic, CMainFrameLogic );


    //���ж�����ʾ �Ѵﵽ5���ӣ����᳡��δ����
    REG_MSG_HANDLER( UI_CMS_CALLING_TIME_OUT, CMainFrameLogic::CallingTimeOut , m_pLogic, CMainFrameLogic );
    //REG_MSG_HANDLER(  UI_UMS_CASCADE_CONF_NOTIFY, CMainFrameLogic::CascadeNotify , m_pLogic, CMainFrameLogic  );

    REG_MSG_HANDLER( UI_CMS_SHOW_ALARM_DLG, CMainFrameLogic::OnShowAlarmNotify, m_pLogic, CMainFrameLogic );

	REG_MSG_HANDLER( WM_CMS_UI_LOGIN_OK, CMainFrameLogic::OnRefreshConfLst, m_pLogic, CMainFrameLogic ); 

    REG_MSG_HANDLER( WM_CMS_UPDATE_CMAINMENU, CMainFrameLogic::OnRefreshConfLst, m_pLogic, CMainFrameLogic ); 
 
    //˫��״̬֪ͨ
    REG_MSG_HANDLER( UI_CNS_RECV_DUAL_NOTIFY, CMainFrameLogic::OnDualRecvStateNotify, m_pLogic, CMainFrameLogic ); 
    
	REG_MSG_HANDLER( UI_CNS_DUALOFFLINE_NOTIFY, CMainFrameLogic::OnDualOffLineNotify, m_pLogic, CMainFrameLogic ); 

    REG_MSG_HANDLER( UI_RECV_DUAL_INTERRUPT, CMainFrameLogic::OnDualRcvInterruptNotify, m_pLogic, CMainFrameLogic ); 

	REG_MSG_HANDLER( UI_CNS_LEAVECONF_NOTIFY, CMainFrameLogic::OnCnsLeaveConfNotify, m_pLogic, CMainFrameLogic ); 

    //ϵͳ����
    REG_MSG_HANDLER( UI_TPAD_CENTRESLEEP_NTY, CMainFrameLogic::OnCentreSleepNotify, m_pLogic, CMainFrameLogic ); 
    
    REG_MSG_HANDLER( UI_CNS_UMSREASON_IND, CMainFrameLogic::OnUmsReasonInd, m_pLogic, CMainFrameLogic );

    //TPad Home����Ӧ
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
	
    //�����������ж�Ӧbutn����Ӧ�¼�
    REG_GOBAL_MEMBER_FUNC( "CMainFrameLogic::BtnAddrbookManageClick", CMainFrameLogic::BtnAddrbookManageClick, m_pLogic, CMainFrameLogic ) ; 
    REG_GOBAL_MEMBER_FUNC( "CMainFrameLogic::BtnConftempManageClick", CMainFrameLogic::BtnConftempManageClick, m_pLogic, CMainFrameLogic ) ; 
    REG_GOBAL_MEMBER_FUNC( "CMainFrameLogic::BtnConfInfoClick", CMainFrameLogic::BtnConfInfoClick, m_pLogic, CMainFrameLogic ) ; 


    //ϵͳ����˵�	
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
        //PC���������϶�
        Value_TransparentDlgMoveStatus valStatus;
        valStatus.bMove = TRUE;
        UIManagePtr->SetPropertyValue( valStatus, g_stcStrMainFrameDlg );

        UIManagePtr->ShowWindow( g_stcStrLoginDlg, true );
    }
    else
    {
        //Window* pWnd = UIManagePtr->GetWindowPtr( g_stcStrMainFrameDlg );
        //pWnd->PostMessage( WM_SYSCOMMAND, SC_MINIMIZE, 0 );
        //��С������ʾ����һ�£�ֱ������
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
	//�ж����Ƿ�Ϊpc�汾
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
	PrtMsg("\n-------------�����������**********\n");    //-------JYY ��ӿ�����ӡ
    CMsgDispatch::SendMessage( WM_CMS_HIDE_VEDIO ,0 , 0 ); 
	return true; 
}


bool CMainFrameLogic::BtnAddrbookClick( const IArgs & arg )
{   
    bool bOn = false;
    UIManagePtr->GetSwitchState( m_strBtnAddrbook, bOn , m_pWndTree );
    if ( bOn == true )
    {
		//�ж����Ƿ�Ϊpc�汾
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
		//�ж����Ƿ�Ϊpc�汾
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
		//�ж����Ƿ�Ϊpc�汾
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
  * ����:  ���������Ϣbut
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
		//�ж����Ƿ�Ϊpc�汾
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
* ����:  ����û�����button
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
* ����:  ����Զ���button
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
		//�ж����Ƿ�Ϊpc�汾
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

//��ʾ����ͼ�����  wparam��1 ��ʾ��Ҫ�����ʾ
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
	case 1: //1��
		UIDATAMGR->SetCurSimulateDlgName( g_stcStrSimulateCns1Dlg ) ; 
		break;
	case 5:
        UIDATAMGR->SetCurSimulateDlgName( g_stcStrSimulateCns5Dlg ) ;
		break;
	default:   //3��
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

	switch( /*tCnsInfo.m_emLevel*/tCnsInfo.m_wScreenNum ) //2012-1-11 by yjj ����ʵ��������Ŀ����ʾ,����ؼ�������3������
	{
	case 1/*emTPSipCounty*/: //1��
		if ( UIDATAMGR->GetCurSimulateDlgName() != g_stcStrSimulateCns1Dlg )
		{
			UIManagePtr->ShowWindow( UIDATAMGR->GetCurSimulateDlgName(), false );
            UIDATAMGR->SetCurSimulateDlgName( g_stcStrSimulateCns1Dlg ); 
            UIManagePtr->ShowWindow( UIDATAMGR->GetCurSimulateDlgName(), bShow );
		}		
		break;
	default:   //3��
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
1.����cns���ڻ����У������ؽ���  ��ģ�������� �жϱ���cns�Ƿ��ڻ����У�������ڣ���������÷�����ϯѡ��  �� ͬʱ�����ػ᳡�� ���� �� ˫�� �Լ��Ҷϲ��������ã�
2.����cns�ڻ�������ֱ�ӽ���������
3.���м�������֪ͨ�����м����� �� �᳡����������ء��Ҷϡ��͡�˫�������ܣ���ϯ�᳡�����С��Ҷϡ��͡�˫�������ܣ����С��Ҷϡ�Ϊ�Ҷϻ��� 
*/
void CMainFrameLogic::UpdateMainMenuDlg()
{    
    if ( m_pWndTree == NULL )
    { 
        return;
    } 
 

    if ( !BusinessManagePtr->IsConnect( ))
    {  
        PrtMsg(0,emEventTypeCmsWindow,"[CMainFrameLogic::UpdateMainMenuDlg]δ���ӣ���ˢ��");
        return;
    }

     RefreshCallState();


    if ( UIDATAMGR->GetCurMainMenuType() == g_schmMainMenuSysManage || UIDATAMGR->GetCurMainMenuType() == g_schmMainMenuConfManage )
    {
        //������ڻ᳡������棬��m_emConfType��ΪemConfOtherUms����֤�е��᳡����ʱ����ˢ��һ��
        m_emConfType = emConfOtherUms;
        PrtMsg(0,emEventTypeCmsWindow,"[CMainFrameLogic::UpdateMainMenuDlg]��ǰ����%s,δ�ڻ᳡���棬��ˢ��", UIDATAMGR->GetCurMainMenuType().c_str() );
        return;
    } 

	BOOL32 bChange = FALSE;
  	TCMSConf tConfInfo;
    BOOL32 bOnline = BusinessManagePtr->IsInConf( &tConfInfo );  
    if ( bOnline )
	{    
		//��Ե����
		if ( tConfInfo.m_emConfType == emCallType_P2P )
		{
			if ( m_emConfType != emConfP2P )
			{
				m_emConfType = emConfP2P;
				UpdateConfMenu( emConfP2P ); 				
				PrtMsg(0,emEventTypeCmsWindow,"[CMainFrameLogic::UpdateMainMenuDlg]�л�����Ե�����н���");
				bChange = TRUE;
                UIManagePtr->LoadScheme( g_schmMainMenuCnsManageInconf,NULL, g_stcStrMainMenuDlg );	
                UIManagePtr->LoadScheme( g_schmSimScrPtpConf,NULL, UIDATAMGR->GetCurSimulateDlgName() );	
                                        
			}			
		}
// 		else if ( tConfInfo.m_emConfType == emConfOtherUms )
// 		{
// 			/*��������ڿ�ums����cns������:   2011-12-13 by yjj
// 			[ Bug00071569 ]:��sp1��[tp]�����У�һ���������ϵĻ��������һ���������ϵĻ᳡A�����ڻ᳡A�Ļ᳡����̨��ģ��᳡��δ��ʾ�κλ�����Ϣ��
// 			 �뽭��ȷ�Ͻ����������:��¼ ���Ǳ����ums���ߵ� �᳡A ��cmc ��ʾ��Ե�Ļ�ؽ��棨ȥ������˫��������*/
// 
// 			if ( m_emConfType != emConfOtherUms )
// 			{
// 				m_emConfType = emConfOtherUms;
// 				UpdateConfMenu( emConfOtherUms );				
// 				PrtMsg(0,emEventTypeCmsWindow,"[CMainFrameLogic::UpdateMainMenuDlg]���᳡δ�ڱ���Ļ����У��л�����UMS�����н���");
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
					PrtMsg(0,emEventTypeCmsWindow,"[CMainFrameLogic::UpdateMainMenuDlg]�л����������н���");
					bChange = TRUE;
                    UIManagePtr->LoadScheme( g_schmMainMenuCnsManageInconf,NULL, g_stcStrMainMenuDlg );	
                    UIManagePtr->LoadScheme( g_schmSimScrMiltConf,NULL, UIDATAMGR->GetCurSimulateDlgName() );	
				}
			}
			else  
			{                
				if ( m_emConfType != emConfCascade )
				{
					//�޻�ز���Ȩ��
					m_emConfType = emConfCascade;
					UpdateConfMenu( emConfCascade );					
					PrtMsg(0,emEventTypeCmsWindow,"[CMainFrameLogic::UpdateMainMenuDlg]��������/�ֻ᳡���л����������޲���Ȩ�޽���");
					bChange = TRUE;
                    UIManagePtr->LoadScheme( g_schmMainMenuCnsManageInconf,NULL, g_stcStrMainMenuDlg );	
                    UIManagePtr->LoadScheme( g_schmSimScrMiltConf,NULL, UIDATAMGR->GetCurSimulateDlgName() );	
				}
			} 
		} 
         		
        if ( bChange )
        {
           // UIManagePtr->LoadScheme( g_schmMainMenuCnsManageInconf,NULL, g_stcStrMainMenuDlg );	
            //�������͸ı䣬������ش���
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
			PrtMsg(0,emEventTypeCmsWindow,"[CMainFrameLogic::UpdateMainMenuDlg]�л����᳡�������");
		
            //�������в������� dyy
			HideAllDlg();
			//��ԭ�˵�λ��
			Value_HoriListOffset val;
			val.nOffset = 0;
			UIManagePtr->SetPropertyValue( val, m_strConfManageList, m_pWndTree );
		}		

    }
}



void CMainFrameLogic::RefreshCallState()
{ 
    //�����ǰ��û�����᳡����ֱ�ӷ���  2012-1-10 by yjj
    TTPCnsInfo tCnsInfo ;
    BusinessManagePtr->GetLocalCnsInfo( tCnsInfo );
    if ( strlen(tCnsInfo.m_achRoomName) == 0 )
    {    
        if ( UIDATAMGR->GetLocalCnsState() == emLocalCnsLocking )
        {    
            HIDE_MSG_BOX
        }

        PrtMsg(0,emEventTypeCmsWindow,"[CMainFrameLogic::RefreshCallState]���᳡������");
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
TP_StartConf_ConfTemplateUnExist,	//����ģ�岻����
TP_StartConf_ConfFull,				//UMS������
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
//���н��
enum EmCnsCallReason	
{
EmCnsCallReason_success,
EmCnsCallReason_hungup,			//�Զ˲����ܻ��������Ҷ�
EmCnsCallReason_Unreachable,	//�Զ˲����ߣ��޷�����
EmCnsCallReason_resourcefull,	//�Զ��޿�����Դ
EmCnsCallReason_dstnotfind,		//Ŀ�겻����
EmCnsCallReason_Busy,			//�Զ�æ
EmCnsCallReason_Local,			//����ԭ��
EmCnsCallReason_NoConf,			//���鲻����
EmCnsCallReason_Exist,			//�Զ����ڱ�������
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
			str.Format( "���� %s ʧ��", tEpAddr );
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
            CMsgDispatch::SendMessage( UI_UMS_HIDE_CALLING_DLG, 0, 0 ); // ���غ��ж������� 
             
        }
		else if ( emLocalCnsWillHungup == emState && em_CALL_IDLE == confState.emState )	//�������,�رյ�����  2013.10.31 jyy
		{////2012.11.14  by yjj Bug00113809
				HIDE_MSG_BOX	
		}
	 
	} 

	//��������ʱ mainmenu��״̬�ɷֻ᳡Ȩ�޵����᳡Ȩ��ת��Ĺ���  2013.1.16 by yjj
	if (   confState.emState == em_CALL_CONNECTED &&
		   UIDATAMGR->GetLocalCnsState() == emLocalCnsCalling )
	{//��ʾ �᳡��ʼ�� ����
		 
		 CMsgDispatch::SendMessage( UI_UMS_SHOW_CALLING_DLG, emTimerRefreshUI, 0 );       
		
// 		Window *pWnd = UIManagePtr->GetWindowPtr( g_stcStrMainFrameDlg );
// 		CMsgDispatch::SendMessage( UI_CNC_BEGINWAITING_REFRESH, (WPARAM)pWnd, emWaitConfInfo );
	} 



    UIDATAMGR->setLocalCnsState( ( EMLocalCnsState )( confState.emState ) ); //2012.11.14  byy Bug00113809
    
    //�յ�UI_UMS_UPDATE_CONFINFO����ˢ�� 2013-9-13 dyy
    //UpdateMainMenuDlg();  
    
    return NO_ERROR;
}

/*
////���н��
enum EmCnsCallReason	
{
	EmCnsCallReason_success,
	EmCnsCallReason_hungup,			//���عҶ�
	EmCnsCallReason_Unreachable,	//�Զ˲����ߣ��޷�����
	EmCnsCallReason_resourcefull,	//�Զ��޿�����Դ
	EmCnsCallReason_dstnotfind,		//Ŀ�겻����
	EmCnsCallReason_Busy,			//�Զ�æ
	EmCnsCallReason_Local,			//����ԭ��
	EmCnsCallReason_NoConf,			//���鲻����
	EmCnsCallReason_Exist,			//�Զ����ڱ�������
	EmCnsCallReason_Rejected,		//�Զ˾ܾ�
	EmCnsCallReason_peerhungup,		//�Զ˹Ҷ�
//	EmCnsCallReason_AlreadyDual,    //�Զ���˫��
	EmCnsCallReason_Abnormal,       //���ص��߹Ҷ�
	EmCnsCallReason_PeerAbnormal,   //�Զ˵��߹Ҷ�
	EmCnsCallReason_ConfOver,	//�������
	EmCnsCallReason_cncallexception,	//����ģ��(cncall)����
	EmCnsCallReason_ConfExist,		//�����Ѵ���
	EmCnsCallReason_unknown,  
	
	  
}; 
*/


/*
CNC�Ļ��������ʾ��Ϣ
1.��Ե����
a.���ҶϷ�,��ʾ�Զ˹Ҷ�
2.������
a.�ֻ᳡�뿪���飬�����᳡��ʾXX�᳡�뿪����
b.�ֻ᳡���߳����飬�����᳡��ʾXX�᳡�뿪���飬�ڷֻ᳡��ʾ�Զ˹Ҷ�
c.���᳡��ᣬ�ֻ᳡�Զ˹Ҷϣ����᳡��ʾ�������
 //2012.8.24 ���������޸� by yjj 
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
    case EmCnsCallReason_hungup://���عҶ�
        strErr = "";
        break;
    case EmCnsCallReason_Unreachable:
        strErr = "�Զ˲�����";
        break;
    case EmCnsCallReason_resourcefull:
        strErr = "�Ѵﵽ�᳡��������";
        break;
    case EmCnsCallReason_dstnotfind:
        strErr = "�Զ˲�����";
        break;
    case EmCnsCallReason_Busy:
        strErr = "�Զ�æ";
        break;
    case EmCnsCallReason_Local:
        strErr = "����ԭ��";
        break;
    case EmCnsCallReason_Rejected:		//�Զ˾ܾ�
        strErr = "�Զ˾ܾ�";
        break;
    case EmCnsCallReason_peerhungup:		//�Զ˹Ҷ�
        strErr = "����������Զ˹Ҷ�";
        break;
// 	case EmCnsCallReason_Abnormal:   ���С����ػ᳡���ߡ�����ʾ��������Ӧ��ʾ���� 2012-6-11  
// 		strErr = ": ���˲�����";
// 		break;
	case EmCnsCallReason_PeerAbnormal:
		strErr = "�Զ˲�����";
		break;
	case EmCnsCallReason_ConfOver:	//�������
		strErr = "�������"; 
		break;
	case EmCnsCallReason_cncallexception:
		strErr = "����ģ�����";
		break;
	case EmCnsCallReason_ConfExist:		//�����Ѵ���
		strErr = "�����Ѵ���";
		break; 
	case EmCnsCallReason_unknown:
		strErr = ""; //2012-8-7 SEʯ�ľ�ȷ��δ֪��������ʾ by yjj
		break;
    default:
        strErr = "";
        break; 
    }


	//���  Bug00113809   2012.11.20 by yjj
	EMLocalCnsState emLocalState  =  UIDATAMGR->GetLocalCnsState();
	if (  emLocalCnsCalling == emLocalState )
	{   
		CMsgDispatch::SendMessage( UI_UMS_HIDE_CALLING_DLG, 0, 0 ); // ���غ��ж������� 
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
				strErr = "�Զ˹Ҷ�";
			}
			ShowPopMsg( /*"���������" +*/strErr ); 
		}  
	
    } 
    else
    { 
		//���ڻ������յ�����Ϣ��˵���ǵ�Ե����ʧ��
		TTPCnsConfStatus tConfStatus = BusinessManagePtr->GetLocalCnsConfState();		
        if ( !strErr.IsEmpty() && tConfStatus.emState != em_CALL_CONNECTED )
		{
			ShowPopMsg( "����ʧ�ܣ�" + strErr );
		} 
    }
    
    UpdateMainMenuDlg();  


    //����˫��ͼ��button
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
		ShowPopMsg( "���ػ᳡����" );

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
    //msg.Format( "���Ѿ���ǿ�����ߣ����˻�������һ���ط���¼", inet_ntoa(tAddr) );
    msg = _T("���Ѿ���ǿ�����ߣ����˻�������һ���ط���¼");

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
                   // || (tMenuInfo.strName == MENU_CNSDUAL)  Ϊ�ں�h323�ն�  ȥ��������  2012.8.29 by yjj
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

	//��MainMenuLogicһ��ˢ�� Bug00158557 ��ӻ������Ͳ������д��� dyy 2014-1-24 
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
	//��������
	tMenuInfo.strName = MENU_ENDCONF;   
	tMenuInfo.nIndex = 0;
	tMenuInfo.strItemType = "ConfMenuButtonItem";
	tMenuInfo.strItemFunc = "CConfCnsLstLogic::BtnHangupConfClick";
	tMenuInfo.strImgFolder = strImgPath + "confmainmenu\\btnConfEnd";
	pMemu->push_back( tMenuInfo );

	//�᳡����
	tMenuInfo.strName = MENU_CNSCTRL;
	tMenuInfo.nIndex = 1;
	tMenuInfo.strItemType = "ConfMenuCheckItem";
	tMenuInfo.strItemFunc = "CMainMenuLogic::OnBtnCnsCtrlClick";
	tMenuInfo.strImgFolder = strImgPath + "confmainmenu\\btnConfCtrl";
	pMemu->push_back( tMenuInfo );

	//��������   
	tMenuInfo.strName = MENU_AUDMIX;
	tMenuInfo.nIndex = 2;
	tMenuInfo.strItemType = "ConfMenuCheckItem";
	tMenuInfo.strItemFunc = "CMainMenuLogic::OnBtnAudMixClick";
	tMenuInfo.strImgFolder = strImgPath + "confmainmenu\\btnConfAudMixOn";
	pMemu->push_back( tMenuInfo );

	//���л�
	tMenuInfo.strName = MENU_PIP;
	tMenuInfo.nIndex = 3;
	tMenuInfo.strItemType = "ConfMenuButtonItem";
	tMenuInfo.strItemFunc = "CMainMenuLogic::OnBtnPIPClick";
	tMenuInfo.strImgFolder = strImgPath + "confmainmenu\\btnConfPIPOn";
	pMemu->push_back( tMenuInfo );

	//����ǽ
// 	tMenuInfo.strName = MENU_TVW;
// 	tMenuInfo.nIndex = 3;
// 	tMenuInfo.strItemType = "ConfMenuCheckItem";
// 	tMenuInfo.strItemFunc = "CMainMenuLogic::OnBtnTvwClick";
// 	tMenuInfo.strImgFolder = strImgPath + "btnConfTvw";
// 	pMemu->push_back( tMenuInfo );

	//�᳡��ѯ
	tMenuInfo.strName = MENU_CNSPOLL;
	tMenuInfo.nIndex = 4;
	tMenuInfo.strItemType = "ConfMenuButtonItem";
	tMenuInfo.strItemFunc = "CMainMenuLogic::OnBtnCnsPoll";
	tMenuInfo.strImgFolder = strImgPath + "confmainmenu\\btnConfPollOn";
	pMemu->push_back( tMenuInfo );

	//��˷翪��
	tMenuInfo.strName = MENU_MUTE;
	tMenuInfo.nIndex = 5;
	tMenuInfo.strItemType = "ConfMenuButtonItem";
	tMenuInfo.strItemFunc = "CMainMenuLogic::OnBtnLocalCnsMute";
	tMenuInfo.strImgFolder = strImgPath + "confmainmenu\\btnConfMuteOn";
	pMemu->push_back( tMenuInfo );

	//����������
	tMenuInfo.strName = MENU_QUITE;
	tMenuInfo.nIndex = 6;
	tMenuInfo.strItemType = "ConfMenuButtonItem";
	tMenuInfo.strItemFunc = "CMainMenuLogic::OnBtnLocalCnsQuite";
	tMenuInfo.strImgFolder = strImgPath + "confmainmenu\\btnConfQuiteOn";
	pMemu->push_back( tMenuInfo );

	//������ʾ����
	tMenuInfo.strName = MENU_CNSDUAL;
	tMenuInfo.nIndex = 7;
	tMenuInfo.strItemType = "ConfMenuButtonItem";
	tMenuInfo.strItemFunc = "CMainMenuLogic::OnBtnLocalCnsDual";
	tMenuInfo.strImgFolder = strImgPath + "confmainmenu\\btnConfDualOn";
	pMemu->push_back( tMenuInfo );

	//������
	tMenuInfo.strName = MENU_SPEAKER;
	tMenuInfo.nIndex = 8;
	tMenuInfo.strItemType = "ConfMenuCheckItem";
	tMenuInfo.strItemFunc = "CMainMenuLogic::OnBtnCnsSpeaker";
	tMenuInfo.strImgFolder = strImgPath + "confmainmenu\\btnConfSpk";
	pMemu->push_back( tMenuInfo );

	//��˷�
	tMenuInfo.strName = MENU_MIC;
	tMenuInfo.nIndex = 9;
	tMenuInfo.strItemType = "ConfMenuCheckItem";
	tMenuInfo.strItemFunc = "CMainMenuLogic::OnBtnCnsMic";
	tMenuInfo.strImgFolder = strImgPath + "confmainmenu\\btnConfMic";
	pMemu->push_back( tMenuInfo );

	//��ʾԴ
	tMenuInfo.strName = MENU_DUALSRC;
	tMenuInfo.nIndex = 10;
	tMenuInfo.strItemType = "ConfMenuCheckItem";
	tMenuInfo.strItemFunc = "CMainMenuLogic::OnBtnDualSrc";
	tMenuInfo.strImgFolder = strImgPath + "confmainmenu\\btnDualSrc";
	pMemu->push_back( tMenuInfo );

	//��ַ��
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

		//�����ģ����н��շ���ȫ����ʾ
// 		BOOL32 bDual = BusinessManagePtr->IsLocalCnsDual();
// 	 	if ( !bDual )  //������ֻ�ǽ��շ�����ֱ��ȫ����ʾ˫��ͼ��

        //TPad��cnc�������ɼ�ʱ����ʾ dyy 2013��8��2��
        if ( !UIDATAMGR->IsPcVersion() )
        {
            if ( !UIManagePtr->IsVisible( g_stcStrMainFrameDlg ) ) 			
            {
                return S_OK;
            }
        }
        //��������ʱ����ʾȫ����ʾͼ��
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
		ShowPopMsg( "˫��Դ����" );	
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
            str = "ͨ���쳣�Ͽ�";
            break;
        case emTPDualOffLine:
            str = "˫��Դ����";
            break;
		case emTPForceStop:
			str = "˫��Դ������";
            break;
        default:
            str = "δ֪ԭ��";
        }

        ShowPopMsg( "����˫����ֹ: " + str );	
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
        str.Format( "�᳡ %s �뿪����", pCnsName );
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
        strMsg = _T("��������ʧ�ܣ�ý����Դ����");
        break;
    case TP_UMS_Discard_AddEp:
        strMsg = _T("��ӻ᳡ʧ�ܣ�ý����Դ����");
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
                    strMsg.Format( "�᳡%s�뿪���ۣ�ý����Դ����", tCnsInfo->m_achRoomName );
                }
            }
        }        
        break;
    case TP_UMS_Discard_Error:
        strMsg = _T("�������۹رգ�ý����Դ����");
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
    //��ӦHome��
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