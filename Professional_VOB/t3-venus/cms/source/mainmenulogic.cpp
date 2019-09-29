// mainmenulogic.cpp: implementation of the CMainMenuLogic class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "cms.h"
#include "mainmenulogic.h"
#include "volumCtrlLogic.h"

CMainMenuLogic *CMainMenuLogic::m_pLogic = NULL;

const String CMainMenuLogic::m_strDlgConfManageMenu = "ConfManageMenuDlg";
const String CMainMenuLogic::m_strBtnPrePage = "ConfManageMenuDlg/btnPrePage";
const String CMainMenuLogic::m_strBtnNextPage = "ConfManageMenuDlg/btnNextPage";
const String CMainMenuLogic::m_strConfManageList = "ConfManageMenuDlg/ConfManageList";


u16  g_wMainMenuID = 0;          //timer 的handle

VOID  CALLBACK  CBPrtTimerFun( HWND hwnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime )
{     
    if ( idEvent == g_wMainMenuID)
    {
        CMainMenuLogic::GetLogicPtr()->TimeProtect();
    }

}

typedef VOID (*WINSDK_RegTouchWindow)(HWND hWnd);
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CMainMenuLogic::CMainMenuLogic()
{
    m_bOptProtect = FALSE;
}

CMainMenuLogic::~CMainMenuLogic()
{
	if ( m_pLogic != NULL )
	{   
		UnRegMsg();
		UnRegFunc();
		delete m_pLogic;
		m_pLogic = NULL; 
	}
}


CMainMenuLogic* CMainMenuLogic::GetLogicPtr()
{
	if ( m_pLogic == NULL )
	{  
		m_pLogic = new CMainMenuLogic();   
	}
	
	return m_pLogic;
}

void CMainMenuLogic::RegMsg()
{ 
    REG_MSG_HANDLER( UI_CNS_CONFSTATE_NOTIFY, CMainMenuLogic::OnConfStateNotify, m_pLogic, CMainMenuLogic );

	REG_MSG_HANDLER( UI_CNS_START_POLL_RSP, CMainMenuLogic::OnCnsPollRsp, m_pLogic, CMainMenuLogic );
	REG_MSG_HANDLER( UI_CNS_POLL_STATE_NOTIFY, CMainMenuLogic::OnCnsPollStateNty, m_pLogic, CMainMenuLogic );
	
	REG_MSG_HANDLER( UI_CNS_START_DUAL_RSP, CMainMenuLogic::OnCnsDualRsp, m_pLogic, CMainMenuLogic );
	REG_MSG_HANDLER( UI_UMS_SET_DUAL_CNS_RSP, CMainMenuLogic::OnCnsDualRsp, m_pLogic, CMainMenuLogic );
	
	REG_MSG_HANDLER( UI_CNS_DUAL_STATE_NOTIFY, CMainMenuLogic::OnCnsDualNotify, m_pLogic, CMainMenuLogic );
	REG_MSG_HANDLER( UI_UMS_DUAL_CNS_NOTIFY, CMainMenuLogic::OnCnsDualNotify, m_pLogic, CMainMenuLogic  );

	REG_MSG_HANDLER( UI_CNS_QUITE_MUTE, CMainMenuLogic::OnCnsQuiteMuteRsp, m_pLogic, CMainMenuLogic );

	REG_MSG_HANDLER( UI_CNS_VIEWLOCALPIP_IND, CMainMenuLogic::OnViewLocalPIPRsp, m_pLogic, CMainMenuLogic );
	REG_MSG_HANDLER( UI_CNS_VIEWLOCALPIP_NTY, CMainMenuLogic::OnViewLocalPIPStateNty, m_pLogic, CMainMenuLogic );

	//更新会议讨论按钮状态
	REG_MSG_HANDLER( UI_UMS_REFRESH_CONFAUDMIX_LIST, CMainMenuLogic::RefreshAudMixState, m_pLogic, CMainMenuLogic );

    REG_MSG_HANDLER( WM_CMS_UPDATE_CONFMENU, CMainMenuLogic::OnUpdateConfMenu, m_pLogic, CMainMenuLogic );
}

void CMainMenuLogic::UnRegMsg()
{
}

bool CMainMenuLogic::RegCBFun()
{   	 
	REG_GOBAL_MEMBER_FUNC( "CMainMenuLogic::InitWnd", CMainMenuLogic::InitWnd, m_pLogic, CMainMenuLogic );
	REG_GOBAL_MEMBER_FUNC( "CMainMenuLogic::OnBtnCnsCtrlClick", CMainMenuLogic::OnBtnCnsCtrlClick, m_pLogic, CMainMenuLogic );
	REG_GOBAL_MEMBER_FUNC( "CMainMenuLogic::OnBtnAudMixClick", CMainMenuLogic::OnBtnAudMixClick, m_pLogic, CMainMenuLogic );
	REG_GOBAL_MEMBER_FUNC( "CMainMenuLogic::OnBtnPIPClick", CMainMenuLogic::OnBtnPIPClick, m_pLogic, CMainMenuLogic );
	REG_GOBAL_MEMBER_FUNC( "CMainMenuLogic::OnBtnTvwClick", CMainMenuLogic::OnBtnTvwClick, m_pLogic, CMainMenuLogic );
	REG_GOBAL_MEMBER_FUNC( "CMainMenuLogic::OnBtnAddrbookClick", CMainMenuLogic::OnBtnAddrbookClick, m_pLogic, CMainMenuLogic );
	REG_GOBAL_MEMBER_FUNC( "CMainMenuLogic::OnBtnCnsPoll", CMainMenuLogic::OnBtnCnsPoll, m_pLogic, CMainMenuLogic );
	REG_GOBAL_MEMBER_FUNC( "CMainMenuLogic::OnBtnCnsMic", CMainMenuLogic::OnBtnCnsMic, m_pLogic, CMainMenuLogic );
	REG_GOBAL_MEMBER_FUNC( "CMainMenuLogic::OnBtnCnsSpeaker", CMainMenuLogic::OnBtnCnsSpeaker, m_pLogic, CMainMenuLogic );
	REG_GOBAL_MEMBER_FUNC( "CMainMenuLogic::OnBtnLocalCnsMute", CMainMenuLogic::OnBtnLocalCnsMute, m_pLogic, CMainMenuLogic );
	REG_GOBAL_MEMBER_FUNC( "CMainMenuLogic::OnBtnLocalCnsQuite", CMainMenuLogic::OnBtnLocalCnsQuite, m_pLogic, CMainMenuLogic );
	REG_GOBAL_MEMBER_FUNC( "CMainMenuLogic::OnBtnLocalCnsDual", CMainMenuLogic::OnBtnLocalCnsDual, m_pLogic, CMainMenuLogic );
	REG_GOBAL_MEMBER_FUNC( "CMainMenuLogic::OnBtnDualSrc", CMainMenuLogic::OnBtnDualSrc, m_pLogic, CMainMenuLogic );

	REG_GOBAL_MEMBER_FUNC( "CMainMenuLogic::OnBtnPrePage", CMainMenuLogic::OnBtnPrePage, m_pLogic, CMainMenuLogic );
	REG_GOBAL_MEMBER_FUNC( "CMainMenuLogic::OnBtnNextPage", CMainMenuLogic::OnBtnNextPage, m_pLogic, CMainMenuLogic );
	REG_GOBAL_MEMBER_FUNC( "CMainMenuLogic::OnListOffsetNotify", CMainMenuLogic::OnListOffsetNotify, m_pLogic, CMainMenuLogic );	
	return true;
}

bool CMainMenuLogic::UnRegFunc()
{
	return true;
}


bool CMainMenuLogic::InitWnd( const IArgs& args )
{   
	CWndLogicBase::InitWnd( args );

    OSVERSIONINFOEX osvi;
    //利用OSVERSIONINFOEX结构调用GetVersionEx()函数
    //如果调用失败，可尝试使用OSVERSIONINFO结构
    ZeroMemory( &osvi, sizeof(OSVERSIONINFOEX) );
    osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
    if( !GetVersionEx((OSVERSIONINFO*)&osvi) )
    {
        osvi.dwOSVersionInfoSize=sizeof(OSVERSIONINFO);
        if(!GetVersionEx((OSVERSIONINFO*)&osvi))
            return false;
    }
    //xp以上版本才有触摸事件
    if ( osvi.dwMajorVersion > 5 )
    {  
        //注册响应WM_TOUCH的窗口
        Window* pWnd = UIManagePtr->GetWindowPtr( m_strConfManageList, m_pWndTree ); 
        if ( pWnd->GetSafeHwnd() != NULL )
        {
            //WINSDK_RegTouchWindow( pWnd->GetSafeHwnd() );

            WINSDK_RegTouchWindow _WINSDK_RegTouchWindow;
        
            HINSTANCE hInstLibrary = LoadLibrary("windowsexsdk.dll");
            if (hInstLibrary != NULL)
            {
                _WINSDK_RegTouchWindow = (WINSDK_RegTouchWindow)GetProcAddress( hInstLibrary, "WINSDK_RegTouchWindow" );
                if ( _WINSDK_RegTouchWindow != NULL )
                {
                    _WINSDK_RegTouchWindow( pWnd->GetSafeHwnd() );
                }

                FreeLibrary( hInstLibrary );
            }
        } 
    }
    
    return true;
}

void CMainMenuLogic::Clear()
{
	if ( m_pWndTree != NULL )
	{
		Value_HoriListOffset val;
		val.nOffset = 0;
		UIManagePtr->SetPropertyValue( val, m_strConfManageList, m_pWndTree );

		Value_HoriListSelItem valSel;
		valSel.dwDataKey = -1;
		UIManagePtr->SetPropertyValue( valSel, m_strConfManageList, m_pWndTree );

        m_bOptProtect = FALSE;
        KillTimer( NULL, g_wMainMenuID );
        g_wMainMenuID = 0;
	}	
}


bool CMainMenuLogic::OnBtnCnsCtrlClick( const IArgs& args )
{
	if ( const Args_ClickItemInfo *pClickInfo = dynamic_cast<const Args_ClickItemInfo*>(&args) )
    {
		IBaseItem* pBaseItem = pClickInfo->m_pClickList->GetItemData();
		if ( CCheckItem* pCheckItem = dynamic_cast<CCheckItem*>(pBaseItem) )
		{
			BOOL bSel = pCheckItem->IsItemSel();
			if ( bSel )
			{    

//                if ( UIDATAMGR->IsPcVersion() )
                {
                    POINT pt;
                    Value_WindowSize val;
                    UIManagePtr->GetPropertyValue( val, g_stcStrCnsLstDlg );
                    
                    Value_WindowSize valParent;
                    UIManagePtr->GetPropertyValue( valParent, g_stcStrMainFrameDlg );
                    pt.x = ( valParent.nWidth - val.nWidth ) / 2;
                    pt.y = 53;
                    UIFACTORYMGR_PTR->SetWndPos( pt, g_stcStrCnsLstDlg, NULL, g_stcStrMainFrameDlg );
                    
                }

                CMsgDispatch::SendMessage( WM_CMS_HIDE_VEDIO ,0 , 0 );
				BOOL32 bRe =  BusinessManagePtr->IsInConf();
				if ( bRe == TRUE )
				{
					UIManagePtr->ShowWindow( g_stcStrCnsLstDlg, true ); 
				}
			}
			else
			{
				UIManagePtr->ShowWindow( g_stcStrCnsLstDlg, false );
			}
		}
	}
	return true;
}

bool CMainMenuLogic::OnBtnAudMixClick( const IArgs& args )
{
	if ( const Args_ClickItemInfo *pClickInfo = dynamic_cast<const Args_ClickItemInfo*>(&args) )
    {
		IBaseItem* pBaseItem = pClickInfo->m_pClickList->GetItemData();
		if ( CCheckItem* pCheckItem = dynamic_cast<CCheckItem*>(pBaseItem) )
		{
			BOOL bSel = pCheckItem->IsItemSel();
			if ( bSel )
			{    
//                if ( UIDATAMGR->IsPcVersion() )
                {
                    POINT pt;
                    Value_WindowSize val;
                    UIManagePtr->GetPropertyValue( val, g_stcStrAudMixDlg );
                    
                    Value_WindowSize valParent;
                    UIManagePtr->GetPropertyValue( valParent, g_stcStrMainFrameDlg );
                    pt.x = ( valParent.nWidth - val.nWidth ) / 2;
                    pt.y = 53;
                    UIFACTORYMGR_PTR->SetWndPos( pt, g_stcStrAudMixDlg, NULL, g_stcStrMainFrameDlg );
                    
                }
                CMsgDispatch::SendMessage( WM_CMS_HIDE_VEDIO ,0 , 0 );
				UIManagePtr->ShowWindow( g_stcStrAudMixDlg, true ); 
			}
			else
			{
				UIManagePtr->ShowWindow( g_stcStrAudMixDlg, false );
			}
		}
	}
	return true;
}


bool CMainMenuLogic::OnBtnTvwClick( const IArgs& args )
{
	if ( const Args_ClickItemInfo *pClickInfo = dynamic_cast<const Args_ClickItemInfo*>(&args) )
    {
		IBaseItem* pBaseItem = pClickInfo->m_pClickList->GetItemData();
		if ( CCheckItem* pCheckItem = dynamic_cast<CCheckItem*>(pBaseItem) )
		{
			BOOL bSel = pCheckItem->IsItemSel();
			if ( bSel )
			{    
//                if ( UIDATAMGR->IsPcVersion() )
                {
                    POINT pt;
                    Value_WindowSize val;
                    UIManagePtr->GetPropertyValue( val, g_stcStrTvwDlg );
                    
                    Value_WindowSize valParent;
                    UIManagePtr->GetPropertyValue( valParent, g_stcStrMainFrameDlg );
                    pt.x = ( valParent.nWidth - val.nWidth ) / 2;
                    pt.y = 53;
                    UIFACTORYMGR_PTR->SetWndPos( pt, g_stcStrTvwDlg, NULL, g_stcStrMainFrameDlg );
                    
                }
                CMsgDispatch::SendMessage( WM_CMS_HIDE_VEDIO ,0 , 0 );
				UIManagePtr->ShowWindow( g_stcStrTvwDlg, true ); 
			}
			else
			{
				UIManagePtr->ShowWindow( g_stcStrTvwDlg, false );
			}
		}
	}
	return true;
}

bool CMainMenuLogic::OnBtnAddrbookClick( const IArgs& args )
{
	if ( const Args_ClickItemInfo *pClickInfo = dynamic_cast<const Args_ClickItemInfo*>(&args) )
    {
		IBaseItem* pBaseItem = pClickInfo->m_pClickList->GetItemData();
		if ( CCheckItem* pCheckItem = dynamic_cast<CCheckItem*>(pBaseItem) )
		{
			BOOL bSel = pCheckItem->IsItemSel();
			if ( bSel )
			{    
//                if ( UIDATAMGR->IsPcVersion() )
                {
                    POINT pt;
                    Value_WindowSize val;
                    UIManagePtr->GetPropertyValue( val, g_stcStrAddrbookDlg );
                    
                    Value_WindowSize valParent;
                    UIManagePtr->GetPropertyValue( valParent, g_stcStrMainFrameDlg );
                    pt.x = ( valParent.nWidth - val.nWidth ) / 2;
                    pt.y = 53;
                    UIFACTORYMGR_PTR->SetWndPos( pt, g_stcStrAddrbookDlg, NULL, g_stcStrMainFrameDlg );
                    
                }
                CMsgDispatch::SendMessage( WM_CMS_HIDE_VEDIO ,0 , 0 );
				UIManagePtr->ShowWindow( g_stcStrAddrbookDlg, true ); 
			}
			else
			{
				UIManagePtr->ShowWindow( g_stcStrAddrbookDlg, false );
			}
		}
	}
	return true;
}

bool CMainMenuLogic::OnBtnCnsMic( const IArgs& args )
{
	if ( const Args_ClickItemInfo *pClickInfo = dynamic_cast<const Args_ClickItemInfo*>(&args) )
    {
		IBaseItem* pBaseItem = pClickInfo->m_pClickList->GetItemData();
		if ( CCheckItem* pCheckItem = dynamic_cast<CCheckItem*>(pBaseItem) )
		{
			BOOL bSel = pCheckItem->IsItemSel();
			if ( bSel )
			{    
				Window *pOwner = NULL;
				if ( m_pWndTree != NULL )
				{
					pOwner = m_pWndTree->GetItemData()->pWnd;
				}
//                if ( UIDATAMGR->IsPcVersion() )
                {
                    POINT pt;
                    Value_WindowSize val;
                    UIManagePtr->GetPropertyValue( val, g_stcStrVolumCtrlDlg );
                    
                    Value_WindowSize valParent;
                    UIManagePtr->GetPropertyValue( valParent, g_stcStrMainFrameDlg );
                    pt.x = ( valParent.nWidth - val.nWidth ) / 2;
                    pt.y = ( valParent.nHeight - val.nHeight - 53) / 2;
                    UIFACTORYMGR_PTR->SetWndPos( pt, g_stcStrVolumCtrlDlg, NULL, g_stcStrMainFrameDlg );
                    
                }
                CMsgDispatch::SendMessage( WM_CMS_HIDE_VEDIO ,0 , 0 );
				CVolumCtrlLogic::GetLogicPtr()->ShowVolum( emVolumMic, pOwner ); 
                
			}
			else
			{
				UIManagePtr->ShowWindow( g_stcStrVolumCtrlDlg, false );
			}
		}
	}
	return true;
}

bool CMainMenuLogic::OnBtnCnsSpeaker( const IArgs& args )
{
	if ( const Args_ClickItemInfo *pClickInfo = dynamic_cast<const Args_ClickItemInfo*>(&args) )
    {
		IBaseItem* pBaseItem = pClickInfo->m_pClickList->GetItemData();
		if ( CCheckItem* pCheckItem = dynamic_cast<CCheckItem*>(pBaseItem) )
		{
			BOOL bSel = pCheckItem->IsItemSel();
			if ( bSel )
			{    
				Window *pOwner = NULL;
				if ( m_pWndTree != NULL )
				{
					pOwner = m_pWndTree->GetItemData()->pWnd;
				}
//                if ( UIDATAMGR->IsPcVersion() )
                {
                    POINT pt;
                    Value_WindowSize val;
                    UIManagePtr->GetPropertyValue( val, g_stcStrVolumCtrlDlg );
                    
                    Value_WindowSize valParent;
                    UIManagePtr->GetPropertyValue( valParent, g_stcStrMainFrameDlg );
                    pt.x = ( valParent.nWidth - val.nWidth ) / 2;
                    pt.y = ( valParent.nHeight - val.nHeight - 53) / 2;
                    UIFACTORYMGR_PTR->SetWndPos( pt, g_stcStrVolumCtrlDlg, NULL, g_stcStrMainFrameDlg );
                    
                }
                CMsgDispatch::SendMessage( WM_CMS_HIDE_VEDIO ,0 , 0 );
				CVolumCtrlLogic::GetLogicPtr()->ShowVolum( emVolumSpeaker, pOwner ); 

			}
			else
			{
				UIManagePtr->ShowWindow( g_stcStrVolumCtrlDlg, false );
			}
		}
	}
	return true;
}


bool CMainMenuLogic::OnBtnCnsPoll( const IArgs& args )
{
	//解决Bug00090730：开启会议，点击会场控制，点击一个分会场条目弹出功能条后，点击下方“》”控键，会场控制界面没有隐藏
	UIManagePtr->SetFocus( m_strConfManageList, m_pWndTree );

	BOOL bPoll = BusinessManagePtr->IsLocalCnsPoll(); 	
 
	if ( bPoll )
	{
		BusinessManagePtr->StartPoll( FALSE );
	}
	else
	{
		BusinessManagePtr->StartPoll( TRUE );
	}
	return true;
}

bool CMainMenuLogic::OnBtnLocalCnsMute( const IArgs& args )
{
	//解决Bug00090730：开启会议，点击会场控制，点击一个分会场条目弹出功能条后，点击下方“》”控键，会场控制界面没有隐藏
	UIManagePtr->SetFocus( m_strConfManageList, m_pWndTree );

	BOOL bMute = BusinessManagePtr->IsLocalCnsMute();
	if ( bMute )
	{
		BusinessManagePtr->SetLocalCnsMute( FALSE );
	}
	else
	{
		BusinessManagePtr->SetLocalCnsMute( TRUE );
	}
	return true;
}

bool CMainMenuLogic::OnBtnLocalCnsQuite( const IArgs& args )
{
	//解决Bug00090730：开启会议，点击会场控制，点击一个分会场条目弹出功能条后，点击下方“》”控键，会场控制界面没有隐藏
	UIManagePtr->SetFocus( m_strConfManageList, m_pWndTree );

	BOOL bQuite = BusinessManagePtr->IsLocalCnsQuite();
	if ( bQuite )
	{
		BusinessManagePtr->SetLocalCnsQuite( FALSE );
	}
	else
	{
		BusinessManagePtr->SetLocalCnsQuite( TRUE );
    }
	return true;
}

bool CMainMenuLogic::OnBtnLocalCnsDual( const IArgs& args )
{
    if ( m_bOptProtect )
    {
        return true;
    }  

	//解决Bug00090730：开启会议，点击会场控制，点击一个分会场条目弹出功能条后，点击下方“》”控键，会场控制界面没有隐藏
	UIManagePtr->SetFocus( m_strConfManageList, m_pWndTree );

	BOOL bDual = BusinessManagePtr->IsLocalCnsDual();
	if ( bDual )
	{
		BusinessManagePtr->StartDual( FALSE );
	}
	else
	{
		BusinessManagePtr->StartDual( TRUE );
    }

    //添加保护，一秒之内不能再操作双流
    m_bOptProtect = TRUE;
    g_wMainMenuID = SetTimer( NULL, 0, 1000, CBPrtTimerFun );

	return true;
}

void CMainMenuLogic::TimeProtect()
{
    m_bOptProtect = FALSE;
    KillTimer( NULL, g_wMainMenuID );
}


bool CMainMenuLogic::OnBtnDualSrc( const IArgs& args )
{
	if ( const Args_ClickItemInfo *pClickInfo = dynamic_cast<const Args_ClickItemInfo*>(&args) )
    {
		IBaseItem* pBaseItem = pClickInfo->m_pClickList->GetItemData();
		if ( CCheckItem* pCheckItem = dynamic_cast<CCheckItem*>(pBaseItem) )
		{
			BOOL bSel = pCheckItem->IsItemSel();
			if ( bSel )
			{    
//                if ( UIDATAMGR->IsPcVersion() )
                {
                    POINT pt;
                    Value_WindowSize val;
                    UIManagePtr->GetPropertyValue( val, g_strDualSrcDlg );
                    
                    Value_WindowSize valParent;
                    UIManagePtr->GetPropertyValue( valParent, g_stcStrMainFrameDlg );
                    pt.x = ( valParent.nWidth - val.nWidth ) / 2;
                    pt.y = 53;
                    UIFACTORYMGR_PTR->SetWndPos( pt, g_strDualSrcDlg, NULL, g_stcStrMainFrameDlg );
                    
                }
				CMsgDispatch::SendMessage( WM_CMS_HIDE_VEDIO ,0 , 0 );
				UIManagePtr->ShowWindow( g_strDualSrcDlg, true );              
			}
			else
			{
				UIManagePtr->ShowWindow( g_strDualSrcDlg, false );
			}
		}
	}
	return true;
}


bool CMainMenuLogic::OnBtnPrePage( const IArgs& args )
{
	if ( m_pWndTree == NULL )
	{
		return false;
	} 

	//解决Bug00090730：开启会议，点击会场控制，点击一个分会场条目弹出功能条后，点击下方“》”控键，会场控制界面没有隐藏
	UIManagePtr->SetFocus( m_strConfManageList, m_pWndTree );

	Value_HoriListOffsetIndex valIndex;
	UIManagePtr->GetPropertyValue( valIndex, m_strConfManageList, m_pWndTree );

	valIndex.nIndex--;
	UIManagePtr->SetPropertyValue( valIndex, m_strConfManageList, m_pWndTree );

	return true;
}

bool CMainMenuLogic::OnBtnNextPage( const IArgs& args )
{
	if ( m_pWndTree == NULL )
	{
		return false;
	}

	//解决Bug00090730：开启会议，点击会场控制，点击一个分会场条目弹出功能条后，点击下方“》”控键，会场控制界面没有隐藏
	UIManagePtr->SetFocus( m_strConfManageList, m_pWndTree );

	
	Value_HoriListOffsetIndex valIndex;
	UIManagePtr->GetPropertyValue( valIndex, m_strConfManageList, m_pWndTree );
	
	valIndex.nIndex++;
	UIManagePtr->SetPropertyValue( valIndex, m_strConfManageList, m_pWndTree );
	return true;
}


bool CMainMenuLogic::OnListOffsetNotify( const IArgs & args )
{
	if ( const Args_WindowMsg* pWinMsg = dynamic_cast<const Args_WindowMsg*>(&args) )
	{
		WindowMsg msg = pWinMsg->m_Msg;
		
		int nIndex = msg.wParam;
		
		UpdatePageBtn();
	}
	
	return true;
}

void CMainMenuLogic::UpdatePageBtn()
{
	if ( m_pWndTree == NULL )
	{
		return;
	}
	
	Value_HoriListOffsetIndex valIndex;
	UIManagePtr->GetPropertyValue( valIndex, m_strConfManageList, m_pWndTree );

	int nIndex = valIndex.nIndex;
	if ( nIndex == 0 )
	{
		UIManagePtr->EnableWindow( m_strBtnPrePage, false, m_pWndTree );
	}
	else
	{
		UIManagePtr->EnableWindow( m_strBtnPrePage, true, m_pWndTree );
	}
	
	Value_HoriListItemCount valCount;
	UIManagePtr->GetPropertyValue( valCount, m_strConfManageList, m_pWndTree );
	
	if ( nIndex >= valCount.nCount - 1 )
	{
		UIManagePtr->EnableWindow( m_strBtnNextPage, false, m_pWndTree );
	}
	else
	{
		UIManagePtr->EnableWindow( m_strBtnNextPage, true, m_pWndTree );
	}
}


void CMainMenuLogic::UpdateConfMenu()
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
	
	for ( int i = 0; i < pMemu->size(); i++ )
	{
		TConfMenuInfo tMenuInfo = pMemu->at(i);
		
		
		if ( tMenuInfo.strName == MENU_CNSPOLL )
		{
			BOOL32 bPoll = BusinessManagePtr->IsLocalCnsPoll();
			if ( bPoll )
			{
				tMenuInfo.strImgFolder = strImgPath + "confmainmenu\\btnConfPollOff";
			}
			else
			{	
				tMenuInfo.strImgFolder = strImgPath + "confmainmenu\\btnConfPollOn";
			}
		}
		
		
		if ( tMenuInfo.strName == MENU_CNSDUAL )
		{
			BOOL32 bDual = BusinessManagePtr->IsLocalCnsDual();
			if ( bDual )
			{
				tMenuInfo.strImgFolder = strImgPath + "confmainmenu\\btnConfDualOff";
			}
			else
			{
				tMenuInfo.strImgFolder = strImgPath + "confmainmenu\\btnConfDualOn";
			}
		}
		
		if ( tMenuInfo.strName == MENU_MUTE )
		{
			BOOL32 bMute = BusinessManagePtr->IsLocalCnsMute();
			if ( bMute )
			{				
				tMenuInfo.strImgFolder = strImgPath + "confmainmenu\\btnConfMuteOff";
			}
			else
			{
				tMenuInfo.strImgFolder = strImgPath + "confmainmenu\\btnConfMuteOn";
			}
		}
		
		if ( tMenuInfo.strName == MENU_QUITE )
		{
			BOOL32 bQuit = BusinessManagePtr->IsLocalCnsQuite();
			if ( bQuit )
			{
				tMenuInfo.strImgFolder = strImgPath + "confmainmenu\\btnConfQuiteOff";
			}
			else
			{
				tMenuInfo.strImgFolder = strImgPath + "confmainmenu\\btnConfQuiteOn";
			}
		}
		
		if ( tMenuInfo.strName == MENU_AUDMIX )
		{
			//判断是否开启会议讨论
			TCMSConf tConfInfo = BusinessManagePtr->GetConfInfo();
			if ( tConfInfo.m_bStartAudmix )
			{
				tMenuInfo.strImgFolder = strImgPath + "confmainmenu\\btnConfAudMixOn";
			}
			else
			{	
				tMenuInfo.strImgFolder = strImgPath + "confmainmenu\\btnConfAudMixOff";
			}
		}
		
		if ( tMenuInfo.strName == MENU_PIP )
		{
			String strDlg = UIDATAMGR->GetCurSimulateDlgName();
			if ( strDlg == "SimulateCns1Dlg" )
			{
				strDlg += "/btnSwithcScreen1";
			} 
			else
			{
				strDlg += "/btnSwithcScreen2";
			}
			BOOL32 bPIP = BusinessManagePtr->IsViewLocalPIP();		//判断是否开启画中画
			if ( bPIP )
			{
				tMenuInfo.strImgFolder = strImgPath + "confmainmenu\\btnConfPIPOff";
				//UIManagePtr->LoadScheme( "SchmInConf", NULL, UIDATAMGR->GetCurSimulateDlgName() );
				UIManagePtr->LoadScheme( "SchmLocalPIP", NULL , strDlg );
			}
			else
			{	
				tMenuInfo.strImgFolder = strImgPath + "confmainmenu\\btnConfPIPOn";
				UIManagePtr->LoadScheme( "SchmNoLocalPIP", NULL , strDlg );
				//Value_TransparentSwitchBtnImage ValImage;
				//ValImage.strImage = "screen/switchBtnScreen3";
				//UIManagePtr->SetPropertyValue( ValImage, strDlg );
				//UIManagePtr->LoadScheme( "SchmNoLocalPIP", NULL , "SimulateCns3Dlg/btnSwithcScreen2" );
				//"SimulateCns3Dlg/btnSwithcScreen2" 
			}
		}
		
		pMemu->at(i) = tMenuInfo;
		
	}
	
	Value_HoriListConfMenu valueMenu( pMemu );
	UIManagePtr->SetPropertyValue( valueMenu, m_strConfManageList, m_pWndTree );

	UpdatePageBtn();
}


HRESULT CMainMenuLogic::OnCnsPollStateNty( WPARAM wparam, LPARAM lparam)
{
	if ( m_pWndTree == NULL )
	{
		return NO_ERROR;
	}
	UpdateConfMenu();
	return NO_ERROR;
}

HRESULT CMainMenuLogic::OnCnsPollRsp( WPARAM wparam, LPARAM lparam )
{
	if ( m_pWndTree == NULL )
	{
		return NO_ERROR;
	}

    BOOL32 bStart = (BOOL32) wparam; 
    EmTPPollResult emRe = (EmTPPollResult)lparam;

    CString strErr = "";
    if ( emRe != emPollSucceed )
    {  
        CString strTemp;
        switch ( emRe )
        {
        case  emPollFailUnKown:
            strTemp = "未知原因";
            break;
		case emPollInvalidEp:
			strTemp = "无有效轮询会场";
			break;
        default:
            strTemp = "未知原因";
            break; 
        }

        if ( bStart )
        {
            strErr = "开启轮询失败：" + strTemp;
        }
        else
        {
            strErr = "关闭轮询失败：" + strTemp;
        }

        ShowPopMsg( strErr );
    }

    return S_OK;
}

HRESULT CMainMenuLogic::OnCnsDualRsp( WPARAM wparam, LPARAM lparam )
{
	if ( m_pWndTree == NULL )
	{
		return NO_ERROR;
	}
	 
	TCMSConf tConfInfo;
	BOOL bInConf = BusinessManagePtr->IsInConf( &tConfInfo );
	if ( !bInConf /*|| tConfInfo.m_emConfType != emCallType_P2P*/ )
	{
		return NO_ERROR;
	}

	BOOL bStart = (BOOL)wparam; 
    EmTPDualReason emRe = (EmTPDualReason)lparam;
	if ( bStart )
	{
		CString strErr = "";
		if ( emRe != emTpDualAccept )
		{  
			CString strTemp = "";
			switch ( emRe )
			{
			case emTpDualBusy:
				strTemp = "双流源忙";
				break;
			case emTpDualPreemptive:
				strTemp = "未知原因";
				break;
			case emTpDualPeerReject:
				strTemp = "对端拒绝";
				break;
			case emTpDualPeerStop:
				strTemp = "对端停止演示";
				break;
			case emTpDualNoVideo:
				strTemp = "无视频源";
				break;
			case emTpDualLocalStop:
				strTemp = "本地停止演示";
				break;
			case emTpDualSndFail:
				strTemp = "发送双流失败";
				break;
            case emTpDualInit:
                strTemp = "双流初始化中，请稍后再试";
				break;
			default:
				strTemp = "未知原因";
				break; 
			}
						
			strErr = "开启演示失败：" + strTemp;
			
			ShowPopMsg( strErr );
		}
	}

	//UpdateConfMenu();
	return NO_ERROR;
}

HRESULT CMainMenuLogic::OnCnsDualNotify( WPARAM wparam, LPARAM lparam)
{
	if ( m_pWndTree == NULL )
	{
		return NO_ERROR;
	}
	UpdateConfMenu();
	return NO_ERROR;	
}

HRESULT CMainMenuLogic::OnCnsQuiteMuteRsp( WPARAM wparam, LPARAM lparam)
{
	if ( m_pWndTree == NULL )
	{
		return NO_ERROR;
	}
	UpdateConfMenu();
	return NO_ERROR;	
}


HRESULT CMainMenuLogic::OnUpdateConfMenu( WPARAM wparam, LPARAM lparam)
{
    if ( m_pWndTree == NULL )
    {
        return NO_ERROR;
    }
    UpdateConfMenu();

    EM_ConfType emConfType = (EM_ConfType)lparam;
    if ( emConfType == emConfMulti )
    {
        //添加保护，2秒之内不能再操作双流 Bug00158557
        m_bOptProtect = TRUE;
        g_wMainMenuID = SetTimer( NULL, 0, 2000, CBPrtTimerFun );
    }

    return NO_ERROR;	
}

HRESULT CMainMenuLogic::OnConfStateNotify( WPARAM wparam, LPARAM lparam)
{
    if ( m_pWndTree == NULL )
    {
        return NO_ERROR;
    }
    UpdateConfMenu();
    return NO_ERROR;
}

bool CMainMenuLogic::OnBtnPIPClick( const IArgs& args )
{
	//解决Bug00090730：开启会议，点击会场控制，点击一个分会场条目弹出功能条后，点击下方“》”控键，会场控制界面没有隐藏
	UIManagePtr->SetFocus( m_strConfManageList, m_pWndTree );

	BOOL bPIP = BusinessManagePtr->IsViewLocalPIP();
	
	if ( bPIP )
	{
		BusinessManagePtr->ViewLocalPIPCmd( 1, FALSE );
	}
	else
	{
		BusinessManagePtr->ViewLocalPIPCmd( 1, TRUE );
    }
	return true;
}

HRESULT CMainMenuLogic::OnViewLocalPIPRsp( WPARAM wparam, LPARAM lparam )
{
	if ( m_pWndTree == NULL )
	{
		return NO_ERROR;
	}

	u8 byScrnID = (u8)wparam; 
    EmTPViewLocalResult emRe = (EmTPViewLocalResult)lparam;
	
    CString strErr = "";
    if ( emRe != emViewLocalSucceed )
    {  
        CString strTemp;
        switch ( emRe )
        {
        case  emViewLocalFailIllegalPos:
            strTemp = "屏号不是1";
            break;
		case  emViewLocalFailOffline:
            strTemp = "会场掉线";
            break;
        default:
            strTemp = "未知原因";
            break; 
        }
		
		BOOL bPIP = BusinessManagePtr->IsViewLocalPIP();
        if ( bPIP )
        {
            strErr = "关闭画中画失败：" + strTemp;
        }
        else
        {
            strErr = "开启画中画失败：" + strTemp;
        }
		
        ShowPopMsg( strErr );
    }
	return S_OK;
}

HRESULT CMainMenuLogic::OnViewLocalPIPStateNty( WPARAM wparam, LPARAM lparam )
{
	if ( m_pWndTree == NULL )
	{
		return S_FALSE;
	}
	UpdateConfMenu();
	return S_OK;
}

HRESULT CMainMenuLogic::RefreshAudMixState( WPARAM wparam, LPARAM lparam )
{
	if ( m_pWndTree == NULL )
	{
		return S_FALSE;
	}
	UpdateConfMenu();
	return S_OK;
}
