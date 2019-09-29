// CurtainCfgLogic.cpp: implementation of the CCurtainCfgLogic class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CurtainCfgLogic.h"

CCurtainCfgLogic *CCurtainCfgLogic::m_pLogic = NULL;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
const String CCurtainCfgLogic::m_strSwitchBtn = "MultiCurtainBkgDlg/SwitchBtn";
const String CCurtainCfgLogic::m_strSwitchBtn1 = "SingelCurtainBkgDlg1/SwitchBtn1";
const String CCurtainCfgLogic::m_strSwitchBtn2 = "SingelCurtainBkgDlg2/SwitchBtn2";
const String CCurtainCfgLogic::m_strSwitchBtn3 = "SingelCurtainBkgDlg3/SwitchBtn3";
const String CCurtainCfgLogic::m_strSwitchBtn4 = "SingelCurtainBkgDlg4/SwitchBtn4";
const String CCurtainCfgLogic::m_strSwitchBtn5 = "SingelCurtainBkgDlg5/SwitchBtn5";
const String CCurtainCfgLogic::m_strSwitchBtn6 = "SingelCurtainBkgDlg6/SwitchBtn6";

CCurtainCfgLogic::CCurtainCfgLogic()
{
	DataClear();
	m_nCurNum = 0;
	UIFACTORYMGR_PTR->LoadScheme( "SchmNoCheck", m_pWndTree );
}

CCurtainCfgLogic::~CCurtainCfgLogic()
{

}

CCurtainCfgLogic* CCurtainCfgLogic::GetLogicPtr()
{
    if ( m_pLogic == NULL )
    {
        m_pLogic = new CCurtainCfgLogic(); 
    } 
    return m_pLogic;
}

void CCurtainCfgLogic::RegMsg()
{
	REG_MSG_HANDLER( UI_TPAD_CURTAINSTATE_NTY, CCurtainCfgLogic::OnCurtainStateNty, m_pLogic, CCurtainCfgLogic );
}

void CCurtainCfgLogic::UnRegMsg()
{
    
}

bool CCurtainCfgLogic::RegCBFun()
{   
    REG_GOBAL_MEMBER_FUNC( "CCurtainCfgLogic::InitWnd", CCurtainCfgLogic::InitWnd, m_pLogic, CCurtainCfgLogic );
	REG_GOBAL_MEMBER_FUNC( "CCurtainCfgLogic::OnClickSwitchBtn1", CCurtainCfgLogic::OnClickSwitchBtn1, m_pLogic, CCurtainCfgLogic );
	REG_GOBAL_MEMBER_FUNC( "CCurtainCfgLogic::OnClickBtnStop1", CCurtainCfgLogic::OnClickBtnStop1, m_pLogic, CCurtainCfgLogic );
	REG_GOBAL_MEMBER_FUNC( "CCurtainCfgLogic::OnClickBtnUp1", CCurtainCfgLogic::OnClickBtnUp1, m_pLogic, CCurtainCfgLogic );
	REG_GOBAL_MEMBER_FUNC( "CCurtainCfgLogic::OnClickBtnDown1", CCurtainCfgLogic::OnClickBtnDown1, m_pLogic, CCurtainCfgLogic );
	REG_GOBAL_MEMBER_FUNC( "CCurtainCfgLogic::OnClickSwitchBtn2", CCurtainCfgLogic::OnClickSwitchBtn2, m_pLogic, CCurtainCfgLogic );
	REG_GOBAL_MEMBER_FUNC( "CCurtainCfgLogic::OnClickBtnStop2", CCurtainCfgLogic::OnClickBtnStop2, m_pLogic, CCurtainCfgLogic );
	REG_GOBAL_MEMBER_FUNC( "CCurtainCfgLogic::OnClickBtnUp2", CCurtainCfgLogic::OnClickBtnUp2, m_pLogic, CCurtainCfgLogic );
	REG_GOBAL_MEMBER_FUNC( "CCurtainCfgLogic::OnClickBtnDown2", CCurtainCfgLogic::OnClickBtnDown2, m_pLogic, CCurtainCfgLogic );
	REG_GOBAL_MEMBER_FUNC( "CCurtainCfgLogic::OnClickSwitchBtn3", CCurtainCfgLogic::OnClickSwitchBtn3, m_pLogic, CCurtainCfgLogic );
	REG_GOBAL_MEMBER_FUNC( "CCurtainCfgLogic::OnClickBtnStop3", CCurtainCfgLogic::OnClickBtnStop3, m_pLogic, CCurtainCfgLogic );
	REG_GOBAL_MEMBER_FUNC( "CCurtainCfgLogic::OnClickBtnUp3", CCurtainCfgLogic::OnClickBtnUp3, m_pLogic, CCurtainCfgLogic );
	REG_GOBAL_MEMBER_FUNC( "CCurtainCfgLogic::OnClickBtnDown3", CCurtainCfgLogic::OnClickBtnDown3, m_pLogic, CCurtainCfgLogic );
	REG_GOBAL_MEMBER_FUNC( "CCurtainCfgLogic::OnClickSwitchBtn4", CCurtainCfgLogic::OnClickSwitchBtn4, m_pLogic, CCurtainCfgLogic );
	REG_GOBAL_MEMBER_FUNC( "CCurtainCfgLogic::OnClickBtnStop4", CCurtainCfgLogic::OnClickBtnStop4, m_pLogic, CCurtainCfgLogic );
	REG_GOBAL_MEMBER_FUNC( "CCurtainCfgLogic::OnClickBtnUp4", CCurtainCfgLogic::OnClickBtnUp4, m_pLogic, CCurtainCfgLogic );
	REG_GOBAL_MEMBER_FUNC( "CCurtainCfgLogic::OnClickBtnDown4", CCurtainCfgLogic::OnClickBtnDown4, m_pLogic, CCurtainCfgLogic );
	REG_GOBAL_MEMBER_FUNC( "CCurtainCfgLogic::OnClickSwitchBtn5", CCurtainCfgLogic::OnClickSwitchBtn5, m_pLogic, CCurtainCfgLogic );
	REG_GOBAL_MEMBER_FUNC( "CCurtainCfgLogic::OnClickBtnStop5", CCurtainCfgLogic::OnClickBtnStop5, m_pLogic, CCurtainCfgLogic );
	REG_GOBAL_MEMBER_FUNC( "CCurtainCfgLogic::OnClickBtnUp5", CCurtainCfgLogic::OnClickBtnUp5, m_pLogic, CCurtainCfgLogic );
	REG_GOBAL_MEMBER_FUNC( "CCurtainCfgLogic::OnClickBtnDown5", CCurtainCfgLogic::OnClickBtnDown5, m_pLogic, CCurtainCfgLogic );
	REG_GOBAL_MEMBER_FUNC( "CCurtainCfgLogic::OnClickSwitchBtn6", CCurtainCfgLogic::OnClickSwitchBtn6, m_pLogic, CCurtainCfgLogic );
	REG_GOBAL_MEMBER_FUNC( "CCurtainCfgLogic::OnClickBtnStop6", CCurtainCfgLogic::OnClickBtnStop6, m_pLogic, CCurtainCfgLogic );
	REG_GOBAL_MEMBER_FUNC( "CCurtainCfgLogic::OnClickBtnUp6", CCurtainCfgLogic::OnClickBtnUp6, m_pLogic, CCurtainCfgLogic );
	REG_GOBAL_MEMBER_FUNC( "CCurtainCfgLogic::OnClickBtnDown6", CCurtainCfgLogic::OnClickBtnDown6, m_pLogic, CCurtainCfgLogic );
	REG_GOBAL_MEMBER_FUNC( "CCurtainCfgLogic::OnClickSwitchBtn", CCurtainCfgLogic::OnClickSwitchBtn, m_pLogic, CCurtainCfgLogic );
	REG_GOBAL_MEMBER_FUNC( "CCurtainCfgLogic::OnClickBtnStop", CCurtainCfgLogic::OnClickBtnStop, m_pLogic, CCurtainCfgLogic );
	REG_GOBAL_MEMBER_FUNC( "CCurtainCfgLogic::OnClickBtnUp", CCurtainCfgLogic::OnClickBtnUp, m_pLogic, CCurtainCfgLogic );
	REG_GOBAL_MEMBER_FUNC( "CCurtainCfgLogic::OnClickBtnDown", CCurtainCfgLogic::OnClickBtnDown, m_pLogic, CCurtainCfgLogic );

    return true;
}

bool CCurtainCfgLogic::UnRegFunc()
{
    return true;
}

bool CCurtainCfgLogic::InitWnd( const IArgs & args )
{   
    CWndLogicBase::InitWnd( args );

    return true;
}

void CCurtainCfgLogic::Clear()
{
	DataClear();
	UIFACTORYMGR_PTR->LoadScheme( "SchmNoCheck", m_pWndTree );
}

bool CCurtainCfgLogic::OnClickSwitchBtn1( const IArgs& args )
{
	if ( !m_bCheck )
	{
		DataClear();
	}

	bool bOn = false;
    UIFACTORYMGR_PTR->GetSwitchState( m_strSwitchBtn1, bOn, m_pWndTree );

	if ( bOn )
	{
//		UIFACTORYMGR_PTR->SetSwitchState( m_strSwitchBtn1, true, m_pWndTree );
		m_bIsCheck[0] = TRUE;
	}
	else
	{
//		UIFACTORYMGR_PTR->SetSwitchState( m_strSwitchBtn1, false, m_pWndTree );
	    m_bIsCheck[0] = FALSE;
	}

	BtnStateCtrl();

	for( u8 Index = 0; Index < m_nCurNum; Index++ )
	{
		if ( !m_bIsCheck[Index] )
		{
			UIFACTORYMGR_PTR->SetSwitchState( m_strSwitchBtn, false, m_pWndTree );
			return false;
		}
	}

	UIFACTORYMGR_PTR->SetSwitchState( m_strSwitchBtn, true, m_pWndTree );

	return true;
}

bool CCurtainCfgLogic::OnClickBtnStop1( const IArgs& args )
{
	DataClear();

	m_bIsCheck[0] = TRUE;

 	ComInterface->SetCurtainState( m_bIsCheck, emCurStop );		

	return true;	
}

bool CCurtainCfgLogic::OnClickBtnUp1( const IArgs& args )
{
	DataClear();

	m_bIsCheck[0] = TRUE;

 	ComInterface->SetCurtainState( m_bIsCheck, emCurUp );

	return true;
}

bool CCurtainCfgLogic::OnClickBtnDown1( const IArgs& args )
{
	DataClear();

	m_bIsCheck[0] = TRUE;
	
 	ComInterface->SetCurtainState( m_bIsCheck, emCurDown );

	return true;
}

bool CCurtainCfgLogic::OnClickSwitchBtn2( const IArgs& args )
{
	if ( !m_bCheck )
	{
		DataClear();
	}

	bool bOn = false;

    UIFACTORYMGR_PTR->GetSwitchState( m_strSwitchBtn2, bOn, m_pWndTree );

	if ( bOn )
	{
//		UIFACTORYMGR_PTR->SetSwitchState( m_strSwitchBtn2, true, m_pWndTree );
		m_bIsCheck[1] = TRUE;
	}
	else
	{
//		UIFACTORYMGR_PTR->SetSwitchState( m_strSwitchBtn2, false, m_pWndTree );
		m_bIsCheck[1] = FALSE;
	}

	BtnStateCtrl();

	for( u8 Index = 0; Index < m_nCurNum; Index++ )
	{
		if ( !m_bIsCheck[Index] )
		{
			UIFACTORYMGR_PTR->SetSwitchState( m_strSwitchBtn, false, m_pWndTree );
			return false;
		}		
	}

	UIFACTORYMGR_PTR->SetSwitchState( m_strSwitchBtn, true, m_pWndTree );

	return true;
}

bool CCurtainCfgLogic::OnClickBtnStop2( const IArgs& args )
{
	DataClear();

	m_bIsCheck[1] = TRUE;
	
	ComInterface->SetCurtainState( m_bIsCheck, emCurStop );	

	return true;
}

bool CCurtainCfgLogic::OnClickBtnUp2( const IArgs& args )
{
	DataClear();

	m_bIsCheck[1] = TRUE;
	
	ComInterface->SetCurtainState( m_bIsCheck, emCurUp );	

	return true;
}

bool CCurtainCfgLogic::OnClickBtnDown2( const IArgs& args )
{
	DataClear();

	m_bIsCheck[1] = TRUE;
	
	ComInterface->SetCurtainState( m_bIsCheck, emCurDown );

	return true;
}

bool CCurtainCfgLogic::OnClickSwitchBtn3( const IArgs& args )
{
	if ( !m_bCheck )
	{
		DataClear();
	}

	bool bOn = false;

    UIFACTORYMGR_PTR->GetSwitchState( m_strSwitchBtn3, bOn, m_pWndTree );

	if ( bOn )
	{
		UIFACTORYMGR_PTR->SetSwitchState( m_strSwitchBtn3, true, m_pWndTree );
		m_bIsCheck[2] = TRUE;
	}
	else
	{
		UIFACTORYMGR_PTR->SetSwitchState( m_strSwitchBtn3, false, m_pWndTree );
		m_bIsCheck[2] = FALSE;
	}

	BtnStateCtrl();
	
	for( u8 Index = 0; Index < m_nCurNum; Index++ )
	{
		if ( !m_bIsCheck[Index] )
		{
			UIFACTORYMGR_PTR->SetSwitchState( m_strSwitchBtn, false, m_pWndTree );
			return false;
		}		
	}

	UIFACTORYMGR_PTR->SetSwitchState( m_strSwitchBtn, true, m_pWndTree );

	return true;
}

bool CCurtainCfgLogic::OnClickBtnStop3( const IArgs& args )
{
	DataClear();

	m_bIsCheck[2] = TRUE;
	
	ComInterface->SetCurtainState( m_bIsCheck, emCurStop );	

	return true;
}

bool CCurtainCfgLogic::OnClickBtnUp3( const IArgs& args )
{
	DataClear();

	m_bIsCheck[2] = TRUE;
	
	ComInterface->SetCurtainState( m_bIsCheck, emCurUp );	

	return true;
}

bool CCurtainCfgLogic::OnClickBtnDown3( const IArgs& args )
{
	DataClear();

	m_bIsCheck[2] = TRUE;
	
	ComInterface->SetCurtainState( m_bIsCheck, emCurDown );

	return true;
}

bool CCurtainCfgLogic::OnClickSwitchBtn4( const IArgs& args )
{
	if ( !m_bCheck )
	{
		DataClear();
	}
	
	bool bOn = false;
	
    UIFACTORYMGR_PTR->GetSwitchState( m_strSwitchBtn4, bOn, m_pWndTree );
	
	if ( bOn )
	{
		UIFACTORYMGR_PTR->SetSwitchState( m_strSwitchBtn4, true, m_pWndTree );
		m_bIsCheck[3] = TRUE;
	}
	else
	{
		UIFACTORYMGR_PTR->SetSwitchState( m_strSwitchBtn4, false, m_pWndTree );
		m_bIsCheck[3] = FALSE;
	}
	
	BtnStateCtrl();

	for( u8 Index = 0; Index < m_nCurNum; Index++ )
	{
		if ( !m_bIsCheck[Index] )
		{
			UIFACTORYMGR_PTR->SetSwitchState( m_strSwitchBtn, false, m_pWndTree );
			return false;
		}		
	}

	UIFACTORYMGR_PTR->SetSwitchState( m_strSwitchBtn, true, m_pWndTree );
	
	return true;
}

bool CCurtainCfgLogic::OnClickBtnStop4( const IArgs& args )
{
	DataClear();
	
	m_bIsCheck[3] = TRUE;
	
	ComInterface->SetCurtainState( m_bIsCheck, emCurStop );	
	
	return true;
}

bool CCurtainCfgLogic::OnClickBtnUp4( const IArgs& args )
{
	DataClear();
	
	m_bIsCheck[3] = TRUE;
	
 	ComInterface->SetCurtainState( m_bIsCheck, emCurUp );

	return true;
}

bool CCurtainCfgLogic::OnClickBtnDown4( const IArgs& args )
{
	DataClear();
	
	m_bIsCheck[3] = TRUE;
	
	ComInterface->SetCurtainState( m_bIsCheck, emCurDown );

	return true;
}

bool CCurtainCfgLogic::OnClickSwitchBtn5( const IArgs& args )
{
	if ( !m_bCheck )
	{
		DataClear();
	}
	
	bool bOn = false;
	
    UIFACTORYMGR_PTR->GetSwitchState( m_strSwitchBtn5, bOn, m_pWndTree );
	
	if ( bOn )
	{
		UIFACTORYMGR_PTR->SetSwitchState( m_strSwitchBtn5, true, m_pWndTree );
		m_bIsCheck[4] = TRUE;
	}
	else
	{
		UIFACTORYMGR_PTR->SetSwitchState( m_strSwitchBtn5, false, m_pWndTree );
		m_bIsCheck[4] = FALSE;
	}
	
	BtnStateCtrl();

	for( u8 Index = 0; Index < m_nCurNum; Index++ )
	{
		if ( !m_bIsCheck[Index] )
		{
			UIFACTORYMGR_PTR->SetSwitchState( m_strSwitchBtn, false, m_pWndTree );
			return false;
		}		
	}

	UIFACTORYMGR_PTR->SetSwitchState( m_strSwitchBtn, true, m_pWndTree );
	
	return true;
}

bool CCurtainCfgLogic::OnClickBtnStop5( const IArgs& args )
{
	DataClear();
	
	m_bIsCheck[4] = TRUE;
	
	ComInterface->SetCurtainState( m_bIsCheck, emCurStop );	
	
	return true;
}

bool CCurtainCfgLogic::OnClickBtnUp5( const IArgs& args )
{
	DataClear();
	
	m_bIsCheck[4] = TRUE;
	
	ComInterface->SetCurtainState( m_bIsCheck, emCurUp );
	
	return true;
}

bool CCurtainCfgLogic::OnClickBtnDown5( const IArgs& args )
{
	DataClear();
	
	m_bIsCheck[4] = TRUE;
	
	ComInterface->SetCurtainState( m_bIsCheck, emCurDown );

	return true;
}

bool CCurtainCfgLogic::OnClickSwitchBtn6( const IArgs& args )
{
	if ( !m_bCheck )
	{
		DataClear();
	}
	
	bool bOn = false;
	
    UIFACTORYMGR_PTR->GetSwitchState( m_strSwitchBtn6, bOn, m_pWndTree );
	
	if ( bOn )
	{
		UIFACTORYMGR_PTR->SetSwitchState( m_strSwitchBtn6, true, m_pWndTree );
		m_bIsCheck[5] = TRUE;
	}
	else
	{
		UIFACTORYMGR_PTR->SetSwitchState( m_strSwitchBtn6, false, m_pWndTree );
		m_bIsCheck[5] = FALSE;
	}
	
	BtnStateCtrl();

	for( u8 Index = 0; Index < m_nCurNum; Index++ )
	{
		if ( !m_bIsCheck[Index] )
		{
			UIFACTORYMGR_PTR->SetSwitchState( m_strSwitchBtn, false, m_pWndTree );
			return false;
		}				
	}

	UIFACTORYMGR_PTR->SetSwitchState( m_strSwitchBtn, true, m_pWndTree );
	
	return true;
}

bool CCurtainCfgLogic::OnClickBtnStop6( const IArgs& args )
{
	DataClear();
	
	m_bIsCheck[5] = TRUE;
	
	ComInterface->SetCurtainState( m_bIsCheck, emCurStop );	
	
	return true;
}

bool CCurtainCfgLogic::OnClickBtnUp6( const IArgs& args )
{
	DataClear();
	
	m_bIsCheck[5] = TRUE;
	
	ComInterface->SetCurtainState( m_bIsCheck, emCurUp );
	
	return true;
}

bool CCurtainCfgLogic::OnClickBtnDown6( const IArgs& args )
{
	DataClear();
	
	m_bIsCheck[5] = TRUE;
	
	ComInterface->SetCurtainState( m_bIsCheck, emCurDown );

	return true;
}

bool CCurtainCfgLogic::OnClickSwitchBtn( const IArgs& args )
{	
	bool bOn = false;
    UIFACTORYMGR_PTR->GetSwitchState( m_strSwitchBtn, bOn, m_pWndTree );

	if ( bOn )
	{
		for ( int i = 0; i< m_nCurNum; i++ )
		{
			CString strDlgName;
			strDlgName.Format( "SingelCurtainBkgDlg%d", i+1 );
			CString strBtnName;
			strBtnName.Format( "SwitchBtn%d", i+1 );
			CString strPath;
	        strPath = strDlgName +"/"+ strBtnName;
			UIFACTORYMGR_PTR->SetSwitchState( (LPCTSTR)strPath, true, m_pWndTree );
			m_bIsCheck[i] = TRUE;
		}
		m_bCheck = TRUE;
		UIFACTORYMGR_PTR->LoadScheme( "SchmAllCheck", m_pWndTree );
	}
	else
	{
		for ( int i = 0; i< m_nCurNum; i++ )
		{
			CString strDlgName;
			strDlgName.Format( "SingelCurtainBkgDlg%d", i+1 );
			CString strBtnName;
			strBtnName.Format( "SwitchBtn%d", i+1 );
			CString strPath;
			strPath = strDlgName +"/"+ strBtnName;
			UIFACTORYMGR_PTR->SetSwitchState( (LPCTSTR)strPath, false, m_pWndTree );
			m_bIsCheck[i] = FALSE;
		}
		m_bCheck = FALSE;
		UIFACTORYMGR_PTR->LoadScheme( "SchmNoCheck", m_pWndTree );
	}

	return true;
}

bool CCurtainCfgLogic::OnClickBtnStop( const IArgs& args )
{
	ComInterface->SetCurtainState( m_bIsCheck, emCurStop );
	return true;
}

bool CCurtainCfgLogic::OnClickBtnUp( const IArgs& args )
{
	ComInterface->SetCurtainState( m_bIsCheck, emCurUp );
	return true;
}

bool CCurtainCfgLogic::OnClickBtnDown( const IArgs& args )
{
	ComInterface->SetCurtainState( m_bIsCheck, emCurDown );
	return true;
}

HRESULT CCurtainCfgLogic::OnCurtainStateNty( WPARAM wparam, LPARAM lparam )
{
	if ( m_pWndTree == NULL )
    {
        return NO_ERROR;
    }
	
	m_nCurNum = (u8)wparam;
	if ( m_nCurNum > 0 )
	{
		UIFACTORYMGR_PTR->LoadScheme( "SchmCurExist", m_pWndTree );
	}
	vector<TCentreCurName> vecTCentreCurName;
	ComInterface->GetCentreCurName( vecTCentreCurName );
	
    CString strCurNum;	
	strCurNum.Format( "SchmCurtainCfg%d", m_nCurNum );	
	UIFACTORYMGR_PTR->LoadScheme( (LPCTSTR)strCurNum, m_pWndTree );

	for( u8 Index = 0; Index < m_nCurNum; Index++ )
	{
		CString strDlgName;
		strDlgName.Format( "SingelCurtainBkgDlg%d", Index+1 );
		CString strCurName;
		strCurName.Format( "StcCurtainName%d", Index+1 );
		CString strPath;
		strPath = strDlgName +"/"+ strCurName;
		UIFACTORYMGR_PTR->SetCaption( (LPCTSTR)strPath, (LPCSTR)vecTCentreCurName[Index].achCurName, m_pWndTree );
	}
	
	return true;	
}

void CCurtainCfgLogic::BtnStateCtrl()
{
	for ( int i = 0; i< m_nCurNum; i++ )
	{
		if( m_bIsCheck[i] )
		{
			UIFACTORYMGR_PTR->LoadScheme( "SchmAllCheck", m_pWndTree );
			m_bCheck = TRUE;
			return;
		}
	}

	UIFACTORYMGR_PTR->LoadScheme( "SchmNoCheck", m_pWndTree );
	m_bCheck = FALSE;
}

void CCurtainCfgLogic::DataClear()
{
	memset( m_bIsCheck, 0, sizeof(m_bIsCheck) );
	m_bCheck = FALSE;
}
