// updservicelogic.cpp: implementation of the CUpdServiceLogic class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "updservicelogic.h"
#include "msgBoxLogic.h"

CUpdServiceLogic * CUpdServiceLogic::m_pLogic = NULL;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CUpdServiceLogic::CUpdServiceLogic()
{

}

CUpdServiceLogic::~CUpdServiceLogic()
{
	if ( m_pLogic != NULL )
	{   
		UnRegMsg();
		UnRegFunc();
		delete m_pLogic;
		m_pLogic = NULL;
	}
}


bool CUpdServiceLogic::RegCBFun()
{
	REG_GOBAL_MEMBER_FUNC( "CUpdServiceLogic::InitWnd", CUpdServiceLogic::InitWnd, m_pLogic, CUpdServiceLogic );
	REG_GOBAL_MEMBER_FUNC( "CUpdServiceLogic::OnSysCfg", CUpdServiceLogic::OnSysCfg, m_pLogic, CUpdServiceLogic );
	REG_GOBAL_MEMBER_FUNC( "CUpdServiceLogic::OnEdit", CUpdServiceLogic::OnEdit, m_pLogic, CUpdServiceLogic );
	REG_GOBAL_MEMBER_FUNC( "CUpdServiceLogic::OnCancel", CUpdServiceLogic::OnCancel, m_pLogic, CUpdServiceLogic );
	REG_GOBAL_MEMBER_FUNC( "CUpdServiceLogic::OnSave", CUpdServiceLogic::OnSave, m_pLogic, CUpdServiceLogic );
	REG_GOBAL_MEMBER_FUNC( "CUpdServiceLogic::OnCloseDlg", CUpdServiceLogic::OnCloseDlg, m_pLogic, CUpdServiceLogic );

	return true;
}

bool CUpdServiceLogic::UnRegFunc()
{
	
	return true;
}

void CUpdServiceLogic::RegMsg()
{
 	REG_MSG_HANDLER( UI_CNSTOOL_MSG_UpgradeSer_NTY, CUpdServiceLogic::OnUpdServiceIPNty, m_pLogic, CUpdServiceLogic );
	REG_MSG_HANDLER( UI_CNSTOOL_MSG_UpgradeSer_IND, CUpdServiceLogic::OnUpdServiceIPInd, m_pLogic, CUpdServiceLogic );
}


CUpdServiceLogic* CUpdServiceLogic::GetLogicPtr()
{
	if ( m_pLogic == NULL )
	{  
		m_pLogic = new CUpdServiceLogic();  
	}
	
	return m_pLogic;
}

void CUpdServiceLogic::Clear()
{
	if ( m_pWndTree != NULL )
	{
		UIManagePtr->SetCaption( _T("IPCtrlServiceIp"), _T(""), m_pWndTree );
		UIManagePtr->LoadScheme( "SchmNormal", m_pWndTree);
	}
}


bool CUpdServiceLogic::InitWnd( const IArgs & args )
{
	CWndLogicBase::InitWnd( args );
	return true;
}

bool CUpdServiceLogic::OnSysCfg( const IArgs& args )
{  
    if ( !UIManagePtr->IsVisible( "UpdServiceDlg/BtnEdit" ) )
    {
        TTPUpgradeSer tCnsUpgSerInfo;
        BusinessManagePtr->GetUpgradeSerInfo( tCnsUpgSerInfo );
		in_addr tAddr;
		tAddr.S_un.S_addr = tCnsUpgSerInfo.dwSerIP;
		String strOldInfo = inet_ntoa(tAddr);
		if ( "0.0.0.0" == strOldInfo )
		{
			strOldInfo = "";
		}
        
        String strServiceIp = GetServiceIP();
        u32_ip dwServiceIP = inet_addr(strServiceIp.c_str());
		if ( "" == strServiceIp )
		{
			dwServiceIP = 0;
		}
        
        if ( dwServiceIP != tCnsUpgSerInfo.dwSerIP || strServiceIp != strOldInfo )
        {
            CString strMsg = "是否对编辑进行保存?";
            Args_MsgBox argMsg;
            argMsg.pOwnerWnd = UIManagePtr->GetWindowPtr( "UpdServiceDlg" );
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
            UIManagePtr->LoadScheme( "SchmNormal", m_pWndTree);
        }
    }
   
	UIManagePtr->LoadScheme( _T("SchmSysCfg"), NULL, _T("SysCfgDlg") );
	return true;
}

bool CUpdServiceLogic::OnEdit( const IArgs& args )
{	
	UIManagePtr->LoadScheme( "SchmEdit", m_pWndTree);
	UIManagePtr->SetFocus( "IPCtrlServiceIp", m_pWndTree );

	return true;
}

bool CUpdServiceLogic::OnCancel( const IArgs& args )
{	
	SetServiceIP();
	
	UIManagePtr->LoadScheme( "SchmNormal", m_pWndTree);
	return true;
}

bool CUpdServiceLogic::OnSave( const IArgs& args )
{
    TTPUpgradeSer tCnsUpgSerInfo;
	BusinessManagePtr->GetUpgradeSerInfo( tCnsUpgSerInfo );

    String strServiceIp = GetServiceIP();
    u32_ip dwServiceIP = inet_addr(strServiceIp.c_str());

    Value_IpEditData valIp;
    UIManagePtr->GetPropertyValue(valIp, "IPCtrlServiceIp", m_pWndTree); 
	TTPUpgradeSer tUpgradeSer;
	tUpgradeSer.dwSerIP = htonl( valIp.dwIP );
	
	if ( !strServiceIp.empty() && !CCallAddr::IsValidIpV4(valIp.dwIP) )//升级服务器可以为空 dyy 2013年8月27日
    {   
		Args_MsgBox msgArg; 
        msgArg.pOwnerWnd = UIManagePtr->GetWindowPtr( "IPCtrlServiceIp", m_pWndTree );
        MSG_BOX( "升级服务器地址非法", FALSE, &msgArg );
        msgArg.pOwnerWnd->SetFocus();
        return false;
	}  
  
	if ( tUpgradeSer.dwSerIP != tCnsUpgSerInfo.dwSerIP)
    {	    
	    u16 wRet = NO_ERROR;		 
	    wRet = ComInterface->UpgradeSerCmd( tUpgradeSer );
    }
// 	if ( dwServiceIP == 0 )			//输入0或00或000提示ip地址非法 ps:当ip地址为空时,dwServiceIP不为0
// 	{
// 		Args_MsgBox msgArg; 
// 		msgArg.pOwnerWnd = UIManagePtr->GetWindowPtr( "IPCtrlServiceIp", m_pWndTree );
// 		MSG_BOX( "IP 地址非法", FALSE, &msgArg );
// 		msgArg.pOwnerWnd->SetFocus();
//         return false;
// 	}
	UIManagePtr->LoadScheme( "SchmNormal", m_pWndTree);
	return true;
}

bool CUpdServiceLogic::OnCloseDlg( const IArgs& args )
{
	return UIManagePtr->ShowWindow( "UpdServiceDlg", false );
}

LRESULT CUpdServiceLogic::OnUpdServiceIPNty( WPARAM wParam, LPARAM lParam )
{
	if ( m_pWndTree == NULL )
	{
		return NO_ERROR;
	}

	SetServiceIP();
    
	return NO_ERROR;
}

LRESULT CUpdServiceLogic::OnUpdServiceIPInd( WPARAM wParam, LPARAM lParam )
{
	if ( m_pWndTree == NULL )
	{
		return NO_ERROR;
	}

	BOOL bRes = static_cast<BOOL>(lParam);
	if ( FALSE == bRes )
	{
		//Args_MsgBox msgArg;
		//msgArg.pOwnerWnd = UIManagePtr->GetWindowPtr( _T(""), m_pWndTree );
		//MSG_BOX( _T("设置升级服务器失败"), FALSE, &msgArg );
        ShowPopMsg( _T("设置升级服务器失败") );
	}

	SetServiceIP();
    
	return NO_ERROR;
}

String CUpdServiceLogic::GetServiceIP()
{
	String strServiceIP;
	UIManagePtr->GetCaption( _T("IPCtrlServiceIp") , strServiceIP , m_pWndTree );
	return strServiceIP;
}

void CUpdServiceLogic::SetServiceIP()
{	
	TTPUpgradeSer tUpgradeSer;
	ComInterface->GetUpgradeSerInfo( tUpgradeSer );
	
	in_addr tAddr;
	tAddr.S_un.S_addr = tUpgradeSer.dwSerIP;
	String strServiceIP = inet_ntoa(tAddr);
	if ( strServiceIP == _T("0.0.0.0") )
	{
		strServiceIP = _T("");
	}
	UIManagePtr->SetCaption( _T("IPCtrlServiceIp") , strServiceIP , m_pWndTree );
}

bool CUpdServiceLogic::CheckServiceIP( String strServiceIP )
{
	u32_ip dwServiceIP = inet_addr(strServiceIP.c_str());

    CString cstrErrStr;
	if ( !CCallAddr::IsValidCallIP( dwServiceIP, cstrErrStr, 0 ) )  
	{
		Args_MsgBox msgArg;
		msgArg.pOwnerWnd = UIManagePtr->GetWindowPtr( _T("IPCtrlServiceIp"), m_pWndTree );
		MSG_BOX( _T("服务器地址无效"), FALSE, &msgArg );
		UIManagePtr->SetFocus( _T("IPCtrlServiceIp"), m_pWndTree );
		return false;
    }
	return true;
}