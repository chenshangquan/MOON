// connectcnslogic.cpp: implementation of the CConnectCnsLogic class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "connectcnslogic.h"
#include "logicManage.h"

CConnectCnsLogic * CConnectCnsLogic::m_pLogic = NULL;
const String CConnectCnsLogic::m_strListCns = "CnsList"; 
const String CConnectCnsLogic::m_strStcLastCns = "StcLastCns"; 
String CConnectCnsLogic::m_strRadioBtn[MAX_PAGE];
String CConnectCnsLogic::m_strScheme[MAX_PAGE];
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CConnectCnsLogic::CConnectCnsLogic()
{
	CString strStr;
	for ( int i = 0; i < MAX_PAGE; i++ )
	{
		strStr.Format( "RadioPage%d", i+1 );
		m_strRadioBtn[i] = (LPCTSTR)strStr;

		strStr.Format( "SchmPage%d", i+1 );
		m_strScheme[i] = (LPCTSTR)strStr;		
	}
	m_nPage = 0;
}

CConnectCnsLogic::~CConnectCnsLogic()
{
	if ( m_pLogic != NULL )
	{   
		UnRegMsg();
		UnRegFunc();
		delete m_pLogic;
		m_pLogic = NULL; 
	}
}

CConnectCnsLogic* CConnectCnsLogic::GetLogicPtr()
{
	if ( m_pLogic == NULL )
	{  
		m_pLogic = new CConnectCnsLogic();   
	}
	
	return m_pLogic;
}

void CConnectCnsLogic::RegMsg()
{
    REG_MSG_HANDLER( UI_CNS_CNLIST_NOTIFY, CConnectCnsLogic::OnCnListNotify, m_pLogic, CConnectCnsLogic ); 	
	REG_MSG_HANDLER( UI_CNSINS_CONNECTED, CConnectCnsLogic::OnConnectCnsInsRsp, m_pLogic, CConnectCnsLogic ); 	
	REG_MSG_HANDLER( UI_CMS_AUTOLOG_CNSINS, CConnectCnsLogic::OnAutoLogCnsIns, m_pLogic, CConnectCnsLogic );
	
}

void CConnectCnsLogic::UnRegMsg()
{
}

bool CConnectCnsLogic::RegCBFun()
{  
	REG_GOBAL_MEMBER_FUNC( "CConnectCnsLogic::InitWnd", CConnectCnsLogic::InitWnd, m_pLogic, CConnectCnsLogic);
 	REG_GOBAL_MEMBER_FUNC( "CConnectCnsLogic::OnClickCnItem", CConnectCnsLogic::OnClickCnItem, m_pLogic, CConnectCnsLogic );
	REG_GOBAL_MEMBER_FUNC( "CConnectCnsLogic::OnListOffsetNotify", CConnectCnsLogic::OnListOffsetNotify, m_pLogic, CConnectCnsLogic );
	
	return true;
}

bool CConnectCnsLogic::UnRegFunc()
{	
	return true;
}

bool CConnectCnsLogic::InitWnd( const IArgs & args )
{
	CWndLogicBase::InitWnd( args );
	
	return true;
}


void CConnectCnsLogic::Clear()
{
	memset( &m_tCnList, 0, sizeof(m_tCnList) );
	m_nPage = 0;
	UIManagePtr->ShowWindow( g_stcStrConnectCnsDlg, false );
	if ( m_pWndTree != NULL )
	{
		Value_HoriListOffset val;
		val.nOffset = 0;
		UIManagePtr->SetPropertyValue( val, m_strListCns, m_pWndTree );
		
		Value_ListConnectCns listCns( &m_tCnList, "CConnectCnsLogic::OnClickCnItem" );
		UIManagePtr->SetPropertyValue( listCns, m_strListCns, m_pWndTree );

		UIManagePtr->LoadScheme( m_strScheme[0], m_pWndTree );
	}
}


bool CConnectCnsLogic::OnClickCnItem( const IArgs & args )
{
	if ( const Args_ClickItemInfo *pClickInfo = dynamic_cast<const Args_ClickItemInfo*>(&args) )
    {
		IBaseItem* pBaseItem = pClickInfo->m_pClickList->GetItemData();
		if ( const Data_TPCnInfo *pCnInfo = dynamic_cast<const Data_TPCnInfo*>( pBaseItem->GetUserData() ) )
		{
			TTPCn tCnInfo = pCnInfo->m_tCnInfo;

			BusinessManagePtr->LoginCnsIns( tCnInfo.byInsId );

			//保存至文件
			UIManagePtr->SetCaption( m_strStcLastCns, tCnInfo.achName, m_pWndTree );
			UIManagePtr->SaveToFile( g_stcStrConnectCnsDlg, m_strStcLastCns, "WindowCaption", TRUE ); 
		}
	}
	return true;
}


bool CConnectCnsLogic::OnListOffsetNotify( const IArgs & args )
{
	if ( const Args_WindowMsg* pWinMsg = dynamic_cast<const Args_WindowMsg*>(&args) )
	{
		WindowMsg msg = pWinMsg->m_Msg;

		int nIndex = msg.wParam;

		UpdateRadioButton();
	}
	
	return true;
}

HRESULT CConnectCnsLogic::OnAutoLogCnsIns( WPARAM wparam, LPARAM lparam )
{
	if ( m_pWndTree == NULL )
	{
		return NO_ERROR;
	}

	String strName;
	UIManagePtr->GetCaption( m_strStcLastCns, strName, m_pWndTree );

	BOOL bFind = FALSE;
	if ( strName != "" )
	{
		for ( int i = 0; i < m_tCnList.wNum; i++ )
		{
			TTPCn tCn = m_tCnList.tCn[i];
			if ( strcmp( strName.c_str(), tCn.achName ) == 0 )
			{
				bFind = TRUE;
				BusinessManagePtr->LoginCnsIns( tCn.byInsId );
				break;
			}
		}
	}

	if ( !bFind )
	{
		UIManagePtr->ShowWindow( "LoginDlg/DlgLoginFrame", false );
		UIManagePtr->ShowWindow( g_stcStrConnectCnsDlg, true );
		UIManagePtr->LoadScheme( "SchmBackLogin", NULL, "LoginDlg/BtnPowerOff" );			
	}

	return NO_ERROR;
}


HRESULT CConnectCnsLogic::OnConnectCnsInsRsp( WPARAM wparam, LPARAM lparam )
{

	if ( wparam == TRUE )
    {  
		UIManagePtr->ShowWindow( g_stcStrLoginDlg, FALSE ); 

		UIManagePtr->SetTransparentDlgImage( g_stcStrMainFrameDlg, g_strMainFrameSimulateBkg );	

		UIManagePtr->LoadScheme( g_schmMainFrameCnsBkg, NULL, UIDATAMGR->GetCurSimulateDlgName() ); 

		UIManagePtr->ShowWindow( g_stcStrMainMenuDlg ); 
        
        CTitleBarLogic::GetLogicPtr()->ShowWindow( TRUE );       
	    //UIManagePtr->ShowWindow( g_stcStrTitleBarDlg );

		CMsgDispatch::SendMessage( WM_CMS_UI_LOGIN_OK , 0, 0 );	
	}

	return NO_ERROR;
}


HRESULT CConnectCnsLogic::OnCnListNotify( WPARAM wparam, LPARAM lparam )
{
	if ( m_pWndTree == NULL )
	{
		return NO_ERROR;
	}
	
	memset( &m_tCnList, 0, sizeof(m_tCnList) );
	BusinessManagePtr->GetConnectCnsList( m_tCnList );
	
	Value_ListConnectCns listCns( &m_tCnList, "CConnectCnsLogic::OnClickCnItem" );
	UIManagePtr->SetPropertyValue( listCns, m_strListCns, m_pWndTree );

	m_nPage = 0;
	if ( m_tCnList.wNum > 0 )
	{
		m_nPage = ( m_tCnList.wNum - 1 ) / MAX_PAGE_COUNT + 1;
	}
	if ( m_nPage > 0 && m_nPage < MAX_PAGE + 1 )
	{
		UIManagePtr->LoadScheme( m_strScheme[m_nPage-1], m_pWndTree );

		UpdateRadioButton();
	}	
	else
	{
		UIManagePtr->LoadScheme( m_strScheme[0], m_pWndTree );
	}

	return NO_ERROR;
}


void CConnectCnsLogic::UpdateRadioButton()
{
	if ( m_pWndTree == NULL )
	{
		return;
	}

	Value_HoriListOffsetIndex valIndex;
	UIManagePtr->GetPropertyValue( valIndex, m_strListCns, m_pWndTree );

	int nIndex = valIndex.nIndex;
	if ( nIndex < m_nPage )
	{
		for ( int i = 0; i < m_nPage; i++ )
		{
			UIManagePtr->SetCheckState( m_strRadioBtn[i], i == nIndex, m_pWndTree );
		}
	}

}