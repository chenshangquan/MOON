// centCfgDisplayDlg.cpp: implementation of the CCentCfgDisplayDlg class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "centCfgDisplayDlg.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCentCfgDisplayDlg::CCentCfgDisplayDlg()
:m_strTerminalOut1("ComboboxTerminalOut1")
,m_strTVWALLOut1("ComboboxTVWALLOut1")
,m_strTerminalOut3("ComboboxTerminalOut3")
,m_strTVWALLOut3("ComboboxTVWALLOut3")
{

}

CCentCfgDisplayDlg::~CCentCfgDisplayDlg()
{

}

void CCentCfgDisplayDlg::RegCBFun()
{
	CCentCfgDisplayDlg *pThis = GetSingletonPtr();
    REG_GOBAL_MEMBER_FUNC( "CCentCfgDisplayDlg::InitWnd", CCentCfgDisplayDlg::InitWnd, pThis, CCentCfgDisplayDlg );
	REG_GOBAL_MEMBER_FUNC( "CCentCfgDisplayDlg::OnBtnSwitchTVWALL", CCentCfgDisplayDlg::OnBtnSwitchTVWALL, pThis, CCentCfgDisplayDlg );
	REG_GOBAL_MEMBER_FUNC( "CCentCfgDisplayDlg::OnBtnSave", CCentCfgDisplayDlg::OnBtnSave, pThis, CCentCfgDisplayDlg );
	REG_GOBAL_MEMBER_FUNC( "CCentCfgDisplayDlg::OnBtnCancel", CCentCfgDisplayDlg::OnBtnCancel, pThis, CCentCfgDisplayDlg );
	REG_GOBAL_MEMBER_FUNC( "CCentCfgDisplayDlg::OnTerminalOut1Change", CCentCfgDisplayDlg::OnTerminalOut1Change, pThis, CCentCfgDisplayDlg );
	REG_GOBAL_MEMBER_FUNC( "CCentCfgDisplayDlg::OnTVWALLOut1Change", CCentCfgDisplayDlg::OnTVWALLOut1Change, pThis, CCentCfgDisplayDlg );
	REG_GOBAL_MEMBER_FUNC( "CCentCfgDisplayDlg::OnTerminalOut3Change", CCentCfgDisplayDlg::OnTerminalOut3Change, pThis, CCentCfgDisplayDlg );
	REG_GOBAL_MEMBER_FUNC( "CCentCfgDisplayDlg::OnTVWALLOut3Change", CCentCfgDisplayDlg::OnTVWALLOut3Change, pThis, CCentCfgDisplayDlg );

}

void CCentCfgDisplayDlg::UnRegFunc()
{
	
}

bool CCentCfgDisplayDlg::InitWnd( const IArgs & arg )
{
	CLogicBase::InitWnd( arg );	
	m_vecOut.push_back("HDMI 1");
	m_vecOut.push_back("HDMI 2");
	m_vecOut.push_back("HDMI 3");
	m_vecOut.push_back("HDMI 4");
// 	m_vecOut.push_back("YPbPr");
// 	m_vecOut.push_back("CVBS1");
// 	m_vecOut.push_back("CVBS2");
// 	m_vecOut.push_back("电脑");
	UIFACTORYMGR_PTR->SetComboListData( m_strTerminalOut1, m_vecOut, m_pWndTree ); 
	UIFACTORYMGR_PTR->SetComboListData( m_strTVWALLOut1, m_vecOut, m_pWndTree ); 
	UIFACTORYMGR_PTR->SetComboListData( m_strTerminalOut3, m_vecOut, m_pWndTree ); 
	UIFACTORYMGR_PTR->SetComboListData( m_strTVWALLOut3, m_vecOut, m_pWndTree ); 
	m_vctWndName.clear();
	UpBtnState();
	return true;
}

void CCentCfgDisplayDlg::Clear()
{
	m_vctWndName.clear();
	UpBtnState();
}

void CCentCfgDisplayDlg::RegMsg()
{
	CCentCfgDisplayDlg *pThis =  GetSingletonPtr();
	REG_MSG_HANDLER( UI_CNSTOOL_MSG_DISPLAY_IND, CCentCfgDisplayDlg::OnUpdateDisplayInfo, pThis, CCentCfgDisplayDlg );
	REG_MSG_HANDLER( UI_CNSTOOL_MSG_CONF_NTY, CCentCfgDisplayDlg::OnConfStateNty, pThis, CCentCfgDisplayDlg );
	
}

void CCentCfgDisplayDlg::UnRegMsg()
{
	
}

bool CCentCfgDisplayDlg::OnBtnSave( const IArgs& args )
{
	BOOL bInConf = LIBDATAMGRPTR->IsInConf();
	if ( bInConf )
	{		
		MSG_BOX_OK( _T("有会议进行中，不能配置") );
		OnBtnCancel(args);
		m_vctWndName.clear();
		UpBtnState();
		return false;	
	}

	TTPDisplayType tDisplayType1, tDisplayType3;
	tDisplayType1.emTPT300Type = GetDisplayType(m_strTerminalOut1);
	tDisplayType1.emTPHduType = GetDisplayType(m_strTVWALLOut1);
	if ( tDisplayType1.emTPT300Type == tDisplayType1.emTPHduType )
	{
		MSG_BOX_OK("显示器1终端输出信号源、电视墙输出信号源必须不一致");
		return false;
	}

	tDisplayType3.emTPT300Type = GetDisplayType(m_strTerminalOut3);
	tDisplayType3.emTPHduType = GetDisplayType(m_strTVWALLOut3);
	if ( tDisplayType3.emTPT300Type == tDisplayType3.emTPHduType )
	{
		MSG_BOX_OK("显示器3终端输出信号源、电视墙输出信号源必须不一致");
		return false;
	}

	bool bDisplay = false;
	UIFACTORYMGR_PTR->GetSwitchState( "BtnTVWALLSwitch", bDisplay, m_pWndTree );

	u16 wRet = COMIFMGRPTR->SetDisplayCmd( bDisplay, tDisplayType1, tDisplayType3 );
	if (wRet != NO_ERROR)
	{
		WARNMESSAGE( "保存中控电视墙配置请求发送失败" );
		return false;
	}

	m_vctWndName.clear();
	UpBtnState();
	return true;
}

bool CCentCfgDisplayDlg::OnBtnCancel( const IArgs& args )
{
	SetDisplayInfo();
	m_vctWndName.clear();
	UpBtnState();
	
	BOOL bInConf = LIBDATAMGRPTR->IsInConf();
	if ( bInConf )
	{		
		OnConfStateNty(0,0);
		return false;	
	}
	return true;
}

bool CCentCfgDisplayDlg::IsCentCfgDisplayChange()
{
	s32 n = m_vctWndName.size();
	if ( n > 0 )
	{
		return SaveMsgBox();
	}
	return true;
}

bool CCentCfgDisplayDlg::SaveMsgBox()
{
	IArgs args("");
	MSGBOX_RET nMsgBoxRet = MSGBOX_CANCEL;
	MSG_BOX( nMsgBoxRet, "配置项已修改，是否保存配置？" );	
	if ( MSGBOX_OK == nMsgBoxRet )
	{
		return OnBtnSave(args);		 
	}
	else
	{
		OnBtnCancel(args);
	}
	return true;
}

bool CCentCfgDisplayDlg::OnBtnSwitchTVWALL( const IArgs& args )
{
	BOOL bDisplay = LIBDATAMGRPTR->GetDisplayState();
	
	bool bOldDisplay = false;
	UIFACTORYMGR_PTR->GetSwitchState( "BtnTVWALLSwitch", bOldDisplay, m_pWndTree );

	bool bChange = false;
	if ( bDisplay != (BOOL)bOldDisplay )
	{
		bChange = true;
	}

	CheckData( "BtnTVWALLSwitch", bChange );

 	if ( bOldDisplay )
 	{
 		UIFACTORYMGR_PTR->LoadScheme( "SchmSwitchOn", m_pWndTree );
 	}
 	else
 	{
// 		TTPDisplayType tDisplayType1, tDisplayType3;
// 		tDisplayType1.emTPT300Type = emTVHDMI1;
// 		tDisplayType1.emTPHduType = emTVHDMI2;
// 		tDisplayType3.emTPT300Type = emTVHDMI1;
// 		tDisplayType3.emTPHduType = emTVHDMI2;
// 		u16 wRet = COMIFMGRPTR->SetDisplayCmd( false, tDisplayType1, tDisplayType3 );
// 		if (wRet != NO_ERROR)
// 		{
// 			WARNMESSAGE( "保存中控电视墙配置请求发送失败" );
// 			return false;
// 		}
// 		m_vctWndName.clear();
// 		UpBtnState();
 		UIFACTORYMGR_PTR->LoadScheme( "SchmSwitchOff", m_pWndTree );
 	}

	return true;
}

LRESULT CCentCfgDisplayDlg::OnConfStateNty( WPARAM wparam, LPARAM lparam )
{
	if ( m_vctWndName.size() > 0 && m_pWndTree != NULL )
	{
		return S_FALSE;
	}
	BOOL bInConf = LIBDATAMGRPTR->IsInConf();
	if ( bInConf )
	{
		UIFACTORYMGR_PTR->LoadScheme( "SchmConf", m_pWndTree );
	} 
	else
	{
		UIFACTORYMGR_PTR->LoadScheme( "SchmNoConf", m_pWndTree );
	}
	return S_FALSE;
}

LRESULT CCentCfgDisplayDlg::OnUpdateDisplayInfo( WPARAM wParam, LPARAM lParam )
{
	if ( m_vctWndName.size() > 0 )
	{
		return S_FALSE;
	}
	BOOL bSuccess = (BOOL)wParam;
	if ( !bSuccess )
	{
		WARNMESSAGE( "中控电视墙配置失败" );
	}
	SetDisplayInfo();

	return S_FALSE;
}

bool CCentCfgDisplayDlg::OnTerminalOut1Change( const IArgs& args )
{
	if ( m_pWndTree == NULL )
	{
		return false;
	}
	bool bChange = false;
	TTPDisplayType tDisplayType;
	tDisplayType.emTPT300Type = GetDisplayType(m_strTerminalOut1);
	TTPDisplayType tOldDisplayType = LIBDATAMGRPTR->GetDisplayType1();
	
	if ( tOldDisplayType.emTPT300Type != tDisplayType.emTPT300Type )
	{
		bChange = true;	
	}
	
	CheckData( m_strTerminalOut1,bChange );
	return true;	
}

bool CCentCfgDisplayDlg::OnTVWALLOut1Change( const IArgs& args )
{
	if ( m_pWndTree == NULL )
	{
		return false;
	}
	bool bChange = false;
	TTPDisplayType tDisplayType;
	tDisplayType.emTPHduType = GetDisplayType(m_strTVWALLOut1);
	TTPDisplayType tOldDisplayType = LIBDATAMGRPTR->GetDisplayType1();
	
	if ( tOldDisplayType.emTPHduType != tDisplayType.emTPHduType )
	{
		bChange = true;	
	}
	
	CheckData( m_strTVWALLOut1,bChange );
	return true;	
}

bool CCentCfgDisplayDlg::OnTerminalOut3Change( const IArgs& args )
{
	if ( m_pWndTree == NULL )
	{
		return false;
	}
	bool bChange = false;
	TTPDisplayType tDisplayType;
	tDisplayType.emTPT300Type = GetDisplayType(m_strTerminalOut3);
	TTPDisplayType tOldDisplayType = LIBDATAMGRPTR->GetDisplayType3();
	
	if ( tOldDisplayType.emTPT300Type != tDisplayType.emTPT300Type )
	{
		bChange = true;	
	}
	
	CheckData( m_strTerminalOut3, bChange );
	return true;	
}

bool CCentCfgDisplayDlg::OnTVWALLOut3Change( const IArgs& args )
{
	if ( m_pWndTree == NULL )
	{
		return false;
	}
	bool bChange = false;
	TTPDisplayType tDisplayType;
	tDisplayType.emTPHduType = GetDisplayType(m_strTVWALLOut3);
	TTPDisplayType tOldDisplayType = LIBDATAMGRPTR->GetDisplayType3();
	
	if ( tOldDisplayType.emTPHduType != tDisplayType.emTPHduType )
	{
		bChange = true;	
	}
	
	CheckData( m_strTVWALLOut3,bChange );
	return true;	
}

EmTVInputSelect CCentCfgDisplayDlg::GetDisplayType( String strCtrl )
{
	String strDisplayType;
	UIFACTORYMGR_PTR->GetComboText( strCtrl, strDisplayType, m_pWndTree );

	if ( strDisplayType.find( "HDMI 1", 0 ) != string::npos )
	{
		return emTVHDMI1;
	}
	else if ( strDisplayType.find( "HDMI 2", 0 ) != string::npos )
	{
		return emTVHDMI2;
	}
	else if ( strDisplayType.find( "HDMI 3", 0 ) != string::npos )
	{
		return emTVHDMI3;
	}
	else if ( strDisplayType.find( "HDMI 4", 0 ) != string::npos )
	{
		return emTVHDMI4;
	}
	else if ( strDisplayType.find( "YPbPr", 0 ) != string::npos )
	{
		return emTVYpbPr;
	}
	else if ( strDisplayType.find( "CVBS1", 0 ) != string::npos )
	{
		return emTVCVBS1;
	}
	else if ( strDisplayType.find( "CVBS2", 0 ) != string::npos )
	{
		return emTVCVBS2;
	}
	else if ( strDisplayType.find( "电脑", 0 ) != string::npos )
	{
		return emTVComputer;
	}
}

string CCentCfgDisplayDlg::TransDisplayType( EmTVInputSelect emType )
{
	string strType;
	switch ( emType )
	{
	case emTVHDMI1:
		strType = "HDMI 1";
		break;
	case emTVHDMI2:
		strType = "HDMI 2";
		break;
	case emTVHDMI3:
		strType = "HDMI 3";
		break;
	case emTVHDMI4:
		strType = "HDMI 4";
		break;
	case emTVYpbPr:
		strType = "YPbPr";
		break;
	case emTVCVBS1:
		strType = "CVBS1";
		break;
	case emTVCVBS2:
		strType = "CVBS2";
		break;
	case emTVComputer:
		strType = "电脑";
		break;
	default:
		strType = "";
		break;
	}

	return strType;
}

void CCentCfgDisplayDlg::SetDisplayInfo()
{
	BOOL bDisplay = LIBDATAMGRPTR->GetDisplayState();
	UIFACTORYMGR_PTR->SetSwitchState( "BtnTVWALLSwitch", bDisplay, m_pWndTree );
	
	TTPDisplayType tDisplayType = LIBDATAMGRPTR->GetDisplayType1();
	String strType = TransDisplayType( tDisplayType.emTPT300Type );
	UIFACTORYMGR_PTR->SetComboText( m_strTerminalOut1, strType, m_pWndTree );
	
	strType = TransDisplayType( tDisplayType.emTPHduType );
	UIFACTORYMGR_PTR->SetComboText( m_strTVWALLOut1, strType, m_pWndTree );
	
	tDisplayType = LIBDATAMGRPTR->GetDisplayType3();
	strType = TransDisplayType( tDisplayType.emTPT300Type );
	UIFACTORYMGR_PTR->SetComboText( m_strTerminalOut3, strType, m_pWndTree );
	
	strType = TransDisplayType( tDisplayType.emTPHduType );
	UIFACTORYMGR_PTR->SetComboText( m_strTVWALLOut3, strType, m_pWndTree );
	
	if ( bDisplay )
	{
		UIFACTORYMGR_PTR->LoadScheme( "SchmSwitchOn", m_pWndTree );
	}
	else
	{
		UIFACTORYMGR_PTR->LoadScheme( "SchmSwitchOff", m_pWndTree );
	}
}
