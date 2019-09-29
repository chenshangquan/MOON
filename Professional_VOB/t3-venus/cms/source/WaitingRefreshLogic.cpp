// WaitingRefreshLogic.cpp: implementation of the CWaitingRefreshLogic class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "WaitingRefreshLogic.h"

CWaitingRefreshLogic * CWaitingRefreshLogic::m_pLogic = NULL;

static UINT g_nTmHandleWaiting;

const String CWaitingRefreshLogic::m_stcUpdateImg = "stcAutoImg";
const String CWaitingRefreshLogic::m_shmImg1 = "SchmPic1";
const String CWaitingRefreshLogic::m_shmImg2 = "SchmPic2";
const String CWaitingRefreshLogic::m_shmImg3 = "SchmPic3";
const String CWaitingRefreshLogic::m_shmImg4 = "SchmPic4";

VOID  CALLBACK  CWaitingTimerFun( HWND hwnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime )
{   
    if ( idEvent == g_nTmHandleWaiting )
    {
		CWaitingRefreshLogic::GetLogicPtr()->UpdateWaitingImg();//更换呼叫图片
    } 
}
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CWaitingRefreshLogic::CWaitingRefreshLogic()
{
	g_nTmHandleWaiting = 0;
	m_emImgSchm = emImgSchm1;
	m_nUpdateTime = 0;
	m_emGetType = emGetRegInfoType_ALL;
}

CWaitingRefreshLogic::~CWaitingRefreshLogic()
{
	if ( m_pLogic != NULL )
	{   
		UnRegMsg();
		UnRegFunc();
		delete m_pLogic;
		m_pLogic = NULL;
	}
}


bool CWaitingRefreshLogic::RegCBFun()
{	
	REG_GOBAL_MEMBER_FUNC( "CWaitingRefreshLogic::InitWnd", CWaitingRefreshLogic::InitWnd, m_pLogic, CWaitingRefreshLogic ) ;
	return true;
}

bool CWaitingRefreshLogic::UnRegFunc()
{
	return true;
}

void CWaitingRefreshLogic::RegMsg()
{
	REG_MSG_HANDLER( UI_CNC_BEGINWAITING_REFRESH, CWaitingRefreshLogic::OnBeginWaitingRefresh, m_pLogic, CWaitingRefreshLogic );
	REG_MSG_HANDLER( UI_CNC_ENDWAITING_REFRESH, CWaitingRefreshLogic::OnEndWaitingRefresh, m_pLogic, CWaitingRefreshLogic );
	REG_MSG_HANDLER( UI_CNC_LOADADDRNUM_NTY, CWaitingRefreshLogic::OnLoadAddrNumNty, m_pLogic, CWaitingRefreshLogic );
}


CWaitingRefreshLogic* CWaitingRefreshLogic::GetLogicPtr()
{
	if ( m_pLogic == NULL )
	{  
		m_pLogic = new CWaitingRefreshLogic();  
	}
	
	return m_pLogic;
}


bool CWaitingRefreshLogic::InitWnd( const IArgs & args )
{
	CWndLogicBase::InitWnd( args );
	
	return true;
}

void CWaitingRefreshLogic::Clear()
{
    if ( g_nTmHandleWaiting != 0 )
    {
        KillTimer( NULL, g_nTmHandleWaiting );
        g_nTmHandleWaiting = 0;
	    UIFACTORYMGR_PTR->Endmodal( IDCANCEL,g_strWaitingRefreshDlg );
    }
	UIManagePtr->ShowWindow( g_strWaitingRefreshDlg, false );
}


void CWaitingRefreshLogic::UpdateWaitingImg()
{
	switch ( m_emImgSchm )
    {
    case emImgSchm1:
        m_emImgSchm = emImgSchm2;
        UIManagePtr->LoadScheme( m_shmImg2, m_pWndTree, m_stcUpdateImg );
        break;
    case emImgSchm2:
        m_emImgSchm = emImgSchm3;
        UIManagePtr->LoadScheme( m_shmImg3, m_pWndTree, m_stcUpdateImg );
        break;
    case emImgSchm3:
        m_emImgSchm = emImgSchm4;
        UIManagePtr->LoadScheme( m_shmImg4, m_pWndTree, m_stcUpdateImg );
        break;  
	case emImgSchm4:
        m_emImgSchm = emImgSchm1;
        UIManagePtr->LoadScheme( m_shmImg1, m_pWndTree, m_stcUpdateImg );
        break;  
    default:
        m_emImgSchm = emImgSchm1;
        UIManagePtr->LoadScheme( m_shmImg1, m_pWndTree, m_stcUpdateImg );
		break;    
    } 

	m_nUpdateTime++;
	int nUpdateTime = 20; //60  注册信息超时时间10s
	if ( m_emWaitType == emWaitConfInfo )
	{
		nUpdateTime = 4;
	}

	if ( m_nUpdateTime > nUpdateTime )
	{
		//超时
		OnEndWaitingRefresh( 0, 0 );
		if ( m_emWaitType == emWaitRegInfo )
		{
			//清空列表
			//	ComInterface->ClearSipRegInfo( m_emGetType );
			CMsgDispatch::SendMessage( UI_CNC_WAITINGREFRESH_OVERTIME, m_emGetType, 0 );
		}
	
	}
}


LRESULT CWaitingRefreshLogic::OnBeginWaitingRefresh(WPARAM wParam, LPARAM lParam)
{
	Value_WindowOwer owerVal;
	owerVal.pWnd = (Window*)wParam;
	UIManagePtr->SetPropertyValue( owerVal, g_strWaitingRefreshDlg );

	//2013.1.16 yjj 
	m_emWaitType = (EmWaitType)lParam;
 
    switch( m_emWaitType )
	{
	case emWaitConfInfo: //等待会议信息
        UIFACTORYMGR_PTR->LoadScheme( "SchmWaitConfInfo", m_pWndTree);
        break;
	case emWaitLoadAddr: //等待导入地址簿
		UIFACTORYMGR_PTR->LoadScheme( "SchmWaitLoadAddr", m_pWndTree);
		UIFACTORYMGR_PTR->SetCaption( "StcMsg", "正在导入...", m_pWndTree );
		UIFACTORYMGR_PTR->SetCaption( "StcPt", "", m_pWndTree );
        break;
	default://emWaitRegInfo: 等待注册信息
        UIFACTORYMGR_PTR->LoadScheme( "", m_pWndTree);
        break;
    }

    //pc版本位置重设 dyy 2013.8.12
//    if ( UIDATAMGR->IsPcVersion() )
    {
        POINT pt;
        Value_WindowSize val;
        UIManagePtr->GetPropertyValue( val, g_strWaitingRefreshDlg );
        
        Value_WindowSize valParent;
        UIManagePtr->GetPropertyValue( valParent, g_stcStrMainFrameDlg );
        
        pt.x = ( valParent.nWidth - val.nWidth ) / 2;
        pt.y = 335; 
        UIFACTORYMGR_PTR->SetWndPos( pt, g_strWaitingRefreshDlg, NULL, g_stcStrMainFrameDlg );
    }
 
//	m_emGetType = (EmGetRegInfoType)lParam;

	m_nUpdateTime = 0;
	g_nTmHandleWaiting = SetTimer( NULL, 0, 500, CWaitingTimerFun );
//UIManagePtr->ShowWindow( g_strWaitingRefreshDlg, true );  //2013.1.30 yjj
	UIFACTORYMGR_PTR->Domodal(g_strWaitingRefreshDlg);
	
	return NO_ERROR;
}


LRESULT CWaitingRefreshLogic::OnEndWaitingRefresh(WPARAM wParam, LPARAM lParam)
{
    if ( g_nTmHandleWaiting == 0 )
    {
        return NO_ERROR;
    }

	KillTimer( NULL, g_nTmHandleWaiting ); 
    g_nTmHandleWaiting = 0;
    
	UIFACTORYMGR_PTR->Endmodal(IDCANCEL,g_strWaitingRefreshDlg);

	//焦点还给Owner窗口
	CWnd* pWnd = UIManagePtr->GetWindowPtr( g_strWaitingRefreshDlg );
	if ( pWnd != NULL && pWnd->m_hWndOwner != NULL )
	{
		HWND hOwner = pWnd->m_hWndOwner;
        
		::PostMessage( hOwner, WM_SETFOCUS, 0, 0 );
	}
	return NO_ERROR;
}


LRESULT CWaitingRefreshLogic::OnLoadAddrNumNty(WPARAM wParam, LPARAM lParam)
{
	u32 dwLoadAddrNum = (u32)lParam;
	CString strNum;
	strNum.Format( "%d", dwLoadAddrNum );
	CString strTip = "正在导入...\n剩余：";
	strTip += strNum;
	strTip += "条";
	
	UIFACTORYMGR_PTR->SetCaption( "StcMsg", (LPCSTR)strTip, m_pWndTree );
	return NO_ERROR;
}