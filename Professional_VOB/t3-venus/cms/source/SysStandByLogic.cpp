// SysStandByLogic.cpp: implementation of the CSysStandByLogic class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SysStandByLogic.h"
#include "msgBoxLogic.h"

CSysStandByLogic* CSysStandByLogic::m_pLogic = NULL;

String CSysStandByLogic::m_strBtnSysStandBySwitch = "SysStandByDlg/BtnSysStandBySwitch";
String CSysStandByLogic::m_strEdtStandByTime = "SysStandByDlg/EdtStandByTime";
String CSysStandByLogic::m_strBtnTimeDel = "SysStandByDlg/btnTimeDel";
String CSysStandByLogic::m_strBtnTimeAdd = "SysStandByDlg/btnTimeAdd";

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSysStandByLogic::CSysStandByLogic()
{

}

CSysStandByLogic::~CSysStandByLogic()
{
	if ( m_pLogic != NULL )
	{   
		UnRegMsg();
		UnRegFunc();
		delete m_pLogic;
		m_pLogic = NULL;
	}
}

bool CSysStandByLogic::RegCBFun()
{
	REG_GOBAL_MEMBER_FUNC( "CSysStandByLogic::InitWnd", CSysStandByLogic::InitWnd, m_pLogic, CSysStandByLogic );
	REG_GOBAL_MEMBER_FUNC( "CSysStandByLogic::OnSave", CSysStandByLogic::OnSave, m_pLogic, CSysStandByLogic );
	REG_GOBAL_MEMBER_FUNC( "CSysStandByLogic::OnCancel", CSysStandByLogic::OnCancel, m_pLogic, CSysStandByLogic );
	REG_GOBAL_MEMBER_FUNC( "CSysStandByLogic::OnEdit", CSysStandByLogic::OnEdit, m_pLogic, CSysStandByLogic );
	REG_GOBAL_MEMBER_FUNC( "CSysStandByLogic::OnSysCfg", CSysStandByLogic::OnSysCfg, m_pLogic, CSysStandByLogic );
	REG_GOBAL_MEMBER_FUNC( "CSysStandByLogic::OnAdd", CSysStandByLogic::OnAdd, m_pLogic, CSysStandByLogic );
	REG_GOBAL_MEMBER_FUNC( "CSysStandByLogic::OnPlus", CSysStandByLogic::OnPlus, m_pLogic, CSysStandByLogic ); 
	REG_GOBAL_MEMBER_FUNC( "CSysStandByLogic::OnAddHold", CSysStandByLogic::OnAdd , m_pLogic, CSysStandByLogic  );
	REG_GOBAL_MEMBER_FUNC( "CSysStandByLogic::OnPlusHold", CSysStandByLogic::OnPlus, m_pLogic, CSysStandByLogic );
	REG_GOBAL_MEMBER_FUNC( "CSysStandByLogic::OnAddHoldEnd", CSysStandByLogic::OnBtnHoldEnd , m_pLogic, CSysStandByLogic  );
	REG_GOBAL_MEMBER_FUNC( "CSysStandByLogic::OnPlusHoldEnd", CSysStandByLogic::OnBtnHoldEnd, m_pLogic, CSysStandByLogic );
	REG_GOBAL_MEMBER_FUNC( "CSysStandByLogic::OnStandByTimeNoFocus", CSysStandByLogic::OnStandByTimeNoFocus, m_pLogic, CSysStandByLogic );
	REG_GOBAL_MEMBER_FUNC( "CSysStandByLogic::BtnSwitchStandByClick", CSysStandByLogic::BtnSwitchStandByClick, m_pLogic, CSysStandByLogic );
	return true;
}

bool CSysStandByLogic::UnRegFunc()
{
	
	return true;
}

void CSysStandByLogic::RegMsg()
{
	REG_MSG_HANDLER( UI_CNS_SLEEPINFO_NOTIFY, CSysStandByLogic::OnSleepInfoNotify, m_pLogic, CSysStandByLogic );	
}

CSysStandByLogic* CSysStandByLogic::GetLogicPtr()
{
	if ( m_pLogic == NULL )
	{  
		m_pLogic = new CSysStandByLogic();  
	}
	
	return m_pLogic;
}

bool CSysStandByLogic::InitWnd( const IArgs & args )
{
	CWndLogicBase::InitWnd( args );

	if ( m_pWndTree == NULL )
    {
        return false;
    }	
	
	ComInterface->GetSysSleepInfo( m_tCenDevSleepInfo );
	UpdateDlg();
// 	Value_TransparentBtnUseTimer valUseTimer;
//     valUseTimer.bUseTimer = TRUE;
//     UIManagePtr->SetPropertyValue( valUseTimer, "SysStandByDlg/btnTimeAdd", m_pWndTree );
//     UIManagePtr->SetPropertyValue( valUseTimer, "SysStandByDlg/btnTimeDel", m_pWndTree );
	
	return true;
}

bool CSysStandByLogic::OnSave( const IArgs& args )
{
	Args_MsgBox msgArg;
	bool bOpen = false;
    UIManagePtr->GetSwitchState( m_strBtnSysStandBySwitch, bOpen, m_pWndTree );
	String strWaitTime;
    UIManagePtr->GetCaption( m_strEdtStandByTime, strWaitTime, m_pWndTree );
	int nSec  = atoi( strWaitTime.c_str() );
	if ( nSec > 3600 || nSec < 1 )
	{
		msgArg.pOwnerWnd = m_pWndTree->GetItemData()->pWnd;//UIManagePtr->GetWindowPtr( m_strEdtStandByTime, m_pWndTree );
        MSG_BOX("时间为 1 ~ 3600 间的整数", FALSE, &msgArg );
		msgArg.pOwnerWnd->SetFocus();	
		return false;
	}
	else
	{
		if ( nSec != m_tCenDevSleepInfo.wSleepWaitTime || (BOOL)bOpen != m_tCenDevSleepInfo.bSleepUsed )
		{
			TCenDevSleepInfo tCenDevSleepInfo;
			tCenDevSleepInfo.bSleepUsed = bOpen;
			tCenDevSleepInfo.wSleepWaitTime = atoi( strWaitTime.c_str());
			//strncmp( arr, strWaitTime.c_str(), sizeof(tTPSleepInfo.m_dwSleepTimes));		
			ComInterface->SetSysSleepInfo( tCenDevSleepInfo );
		}
		UIManagePtr->LoadScheme( "SchmNormal", m_pWndTree );
	}

	return true;
}

bool CSysStandByLogic::OnCancel( const IArgs& args )
{
	char arr[12];
	itoa( m_tCenDevSleepInfo.wSleepWaitTime, arr, 10 );
	UIManagePtr->SetSwitchState( m_strBtnSysStandBySwitch, m_tCenDevSleepInfo.bSleepUsed, m_pWndTree );
    UIManagePtr->SetCaption( m_strEdtStandByTime, arr, m_pWndTree );
	UIManagePtr->LoadScheme( "SchmNormal", m_pWndTree );
	return true;
}

bool CSysStandByLogic::OnEdit( const IArgs& args )
{
	UIManagePtr->LoadScheme( "SchmEdit", m_pWndTree );
	bool bUse = false;
    UIFACTORYMGR_PTR->GetSwitchState( "BtnSysStandBySwitch", bUse, m_pWndTree );
	if ( bUse )
    {
        UIFACTORYMGR_PTR->LoadScheme( "SchmEdit", m_pWndTree, "EdtStandByTime"); 
		UIFACTORYMGR_PTR->LoadScheme( "SchmEdit", m_pWndTree, "btnTimeDel");
		UIFACTORYMGR_PTR->LoadScheme( "SchmEdit", m_pWndTree, "btnTimeAdd");
    }
    else
    {   
        UIFACTORYMGR_PTR->LoadScheme( "SchmNormal", m_pWndTree,"EdtStandByTime");
		UIFACTORYMGR_PTR->LoadScheme( "SchmNormal", m_pWndTree, "btnTimeDel");
		UIFACTORYMGR_PTR->LoadScheme( "SchmNormal", m_pWndTree, "btnTimeAdd");
    }
	return true;
}


bool CSysStandByLogic::OnSysCfg( const IArgs& args )
{
    if ( ! UIManagePtr->IsVisible( "SysStandByDlg/BtnEdit" ) )
    {
        String strWaitTime;
        UIManagePtr->GetCaption( m_strEdtStandByTime, strWaitTime, m_pWndTree );
    	int nSec  = atoi( strWaitTime.c_str() );
        char arr[12];
        itoa( m_tCenDevSleepInfo.wSleepWaitTime, arr, 10 );

        bool bOpen = false;
        UIManagePtr->GetSwitchState( m_strBtnSysStandBySwitch, bOpen, m_pWndTree );

		if ( strcmp( strWaitTime.c_str(), arr ) != 0 || (BOOL)bOpen != m_tCenDevSleepInfo.bSleepUsed )
        {
            CString strMsg = "是否对编辑进行保存?";
            Args_MsgBox argMsg;
            argMsg.pOwnerWnd = UIManagePtr->GetWindowPtr( "SysStandByDlg" );
            int nResult = MSG_BOX( strMsg, TRUE, &argMsg);
            if ( IDOK == nResult )
            {
                if ( !OnSave(args) )
                {
                    return false;
                }
            }
            else
            {
                OnCancel(args);
            }
        }
        else
        {
            OnCancel(args);
        }
    }

	UIManagePtr->LoadScheme( "SchmSysCfg", NULL, "SysCfgDlg" );
	return true;
}

bool CSysStandByLogic::OnAdd( const IArgs& args )
{
	String  strSecond ;
	Args_MsgBox msgArg;
    UIManagePtr->GetCaption( m_strEdtStandByTime, strSecond, m_pWndTree );
    
    int nSec  = atoi( strSecond.c_str() );
	if ( nSec > 3599 )
	{
		msgArg.pOwnerWnd = m_pWndTree->GetItemData()->pWnd;//UIManagePtr->GetWindowPtr( m_strEdtStandByTime, m_pWndTree );
		MSG_BOX("时间为 1 ~ 3600 间的整数", FALSE, &msgArg );
		//msgArg.pOwnerWnd->SetFocus();
		if ( msgArg.pOwnerWnd )			
		{
			msgArg.pOwnerWnd->SetFocus();
		}
		return false;
	}
	else
	{
		nSec++;
	}
	s8 pSec[5] = {0} ;
	sprintf( pSec, "%d", nSec );
	UIManagePtr->SetCaption( m_strEdtStandByTime, pSec, m_pWndTree );
	return true;
}

bool CSysStandByLogic::OnPlus( const IArgs& args )
{
	String  strSecond ;
	Args_MsgBox msgArg;	
    UIManagePtr->GetCaption( m_strEdtStandByTime, strSecond, m_pWndTree );
    
    int nSec = atoi( strSecond.c_str() );
	if ( nSec < 2 )
	{
		msgArg.pOwnerWnd = m_pWndTree->GetItemData()->pWnd;//UIManagePtr->GetWindowPtr( m_strEdtStandByTime, m_pWndTree );
		MSG_BOX("时间为 1 ~ 3600 间的整数", FALSE, &msgArg );
		//msgArg.pOwnerWnd->SetFocus();
		if ( msgArg.pOwnerWnd )			
		{
			msgArg.pOwnerWnd->SetFocus();
		}
		return false;		
	}
	else
	{
		nSec--;
	}
	s8 pSec[5] = {0};
	sprintf( pSec, "%d", nSec );
	UIManagePtr->SetCaption( m_strEdtStandByTime, pSec, m_pWndTree );
	return true;
}

bool CSysStandByLogic::OnBtnHoldEnd( const IArgs& args )
{
	Window* pWnd;
    pWnd = UIManagePtr->GetWindowPtr( m_strEdtStandByTime, m_pWndTree );
	if ( pWnd )
	{
		pWnd->SetFocus();
		CEdit* pEd = ( CEdit* )pWnd;
		pEd->SetSel( 0, -1 );
	}
	return 0;
}

LRESULT CSysStandByLogic::OnSleepInfoNotify( WPARAM wParam, LPARAM lParam )
{
	if ( m_pWndTree == NULL )
    {
        return NO_ERROR;
    }

	ComInterface->GetSysSleepInfo( m_tCenDevSleepInfo );
	UpdateDlg();
	
	return NO_ERROR;
}

bool CSysStandByLogic::UpdateDlg()
{
	if ( m_pWndTree == NULL )
    {
        return false;
    }	
	
	char arr[12];
	itoa( m_tCenDevSleepInfo.wSleepWaitTime, arr, 10 );
	UIManagePtr->SetSwitchState( m_strBtnSysStandBySwitch, m_tCenDevSleepInfo.bSleepUsed, m_pWndTree );

    UIManagePtr->SetCaption( m_strEdtStandByTime, arr, m_pWndTree );
	
	return true;
}

void CSysStandByLogic::Clear()
{
	if ( m_pWndTree != NULL )
	{		
		UIManagePtr->LoadScheme( "SchmNormal", m_pWndTree );
	}
}

bool CSysStandByLogic::BtnSwitchStandByClick( const IArgs & arg )
{
	bool bUse = false;
    UIFACTORYMGR_PTR->GetSwitchState( "BtnSysStandBySwitch", bUse, m_pWndTree );
	if ( bUse )
    {
        UIFACTORYMGR_PTR->LoadScheme( "SchmEdit", m_pWndTree, "EdtStandByTime"); 
		UIFACTORYMGR_PTR->LoadScheme( "SchmEdit", m_pWndTree, "btnTimeDel");
		UIFACTORYMGR_PTR->LoadScheme( "SchmEdit", m_pWndTree, "btnTimeAdd");
    }
    else
    {   
        UIFACTORYMGR_PTR->LoadScheme( "SchmNormal", m_pWndTree,"EdtStandByTime");
		UIFACTORYMGR_PTR->LoadScheme( "SchmNormal", m_pWndTree, "btnTimeDel");
		UIFACTORYMGR_PTR->LoadScheme( "SchmNormal", m_pWndTree, "btnTimeAdd");
    }
	
	return true;
}

bool CSysStandByLogic::OnStandByTimeNoFocus( const IArgs & arg )
{
	//防止错误数据时，原本关闭点击开启焦点置于edit框内，再点击取消，会有空句柄产生问题
	if ( const Args_WindowMsg* pWinMsg = dynamic_cast<const Args_WindowMsg*>(&arg) )
	{
		WindowMsg msg = pWinMsg->m_Msg; 
		Window* pWnd = (CWnd*)msg.lParam;
		if ( pWnd == NULL )
		{
			return true;
		}
	}

	String strWaitTime;
    UIManagePtr->GetCaption( m_strEdtStandByTime, strWaitTime, m_pWndTree );
	int nSec  = atoi( strWaitTime.c_str() );
	if ( nSec <1 )
	{
		nSec = 1;
	}
	if ( nSec > 3600)
	{
		nSec = 3600;
	}
	char arr[12];
	itoa( nSec, arr, 10 );
	UIManagePtr->SetCaption( m_strEdtStandByTime, arr, m_pWndTree );
	return true;
}
