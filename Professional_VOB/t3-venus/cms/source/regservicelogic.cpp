// regservicelogic.cpp: implementation of the CRegServiceLogic class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "regservicelogic.h"
#include "msgBoxLogic.h"

String CRegServiceLogic::m_stBtnGkSwitch = "RegServiceDlg/BtnGkSwitch";
String CRegServiceLogic::m_strGkIP = "RegServiceDlg/IPCtrlGkIp";
CRegServiceLogic * CRegServiceLogic::m_pRegLogic = NULL;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CRegServiceLogic::CRegServiceLogic()
{

}

CRegServiceLogic::~CRegServiceLogic()
{
	if ( m_pRegLogic != NULL )
	{   
		UnRegMsg();
		UnRegFunc();
		delete m_pRegLogic;
		m_pRegLogic = NULL;
	}
}


bool CRegServiceLogic::RegCBFun()
{
	REG_GOBAL_MEMBER_FUNC( "CRegServiceLogic::InitWnd", CRegServiceLogic::InitWnd, m_pRegLogic, CRegServiceLogic );
	REG_GOBAL_MEMBER_FUNC( "CRegServiceLogic::OnSave", CRegServiceLogic::OnSave, m_pRegLogic, CRegServiceLogic );
	REG_GOBAL_MEMBER_FUNC( "CRegServiceLogic::OnCancel", CRegServiceLogic::OnCancel, m_pRegLogic, CRegServiceLogic );
	REG_GOBAL_MEMBER_FUNC( "CRegServiceLogic::OnEdit", CRegServiceLogic::OnEdit, m_pRegLogic, CRegServiceLogic );
	REG_GOBAL_MEMBER_FUNC( "CRegServiceLogic::OnSysCfg", CRegServiceLogic::OnSysCfg, m_pRegLogic, CRegServiceLogic );
	REG_GOBAL_MEMBER_FUNC( "CRegServiceLogic::OnCloseDlg", CRegServiceLogic::OnCloseDlg, m_pRegLogic, CRegServiceLogic );
	REG_GOBAL_MEMBER_FUNC( "CRegServiceLogic::BtnSwitchGkClick", CRegServiceLogic::BtnSwitchGkClick, m_pRegLogic, CRegServiceLogic );
	return true;
}

bool CRegServiceLogic::UnRegFunc()
{
	
	return true;
}

void CRegServiceLogic::RegMsg()
{
	REG_MSG_HANDLER( UI_CNS_REGSIP_NOTIFY, CRegServiceLogic::UpdateSipCfg, m_pRegLogic, CRegServiceLogic );
	REG_MSG_HANDLER( UI_CNS_REGRESULT_NOTIFY, CRegServiceLogic::OnRegResultNty, m_pRegLogic, CRegServiceLogic );
	REG_MSG_HANDLER( UI_CNS_SIPREG_ALIASREPEAT_NOTIFY, CRegServiceLogic::OnRegAliasRepeatNty, m_pRegLogic, CRegServiceLogic );
	REG_MSG_HANDLER( UI_CNS_REG_GK_NTY, CRegServiceLogic::UpdateGkCfg, m_pRegLogic, CRegServiceLogic );	
	REG_MSG_HANDLER( UI_CNS_REG_GK_RSP, CRegServiceLogic::OnRegRsp, m_pRegLogic, CRegServiceLogic );
	REG_MSG_HANDLER( UI_CNSTOOL_MSG_CallSer_NTY, CRegServiceLogic::OnCallServiceInfoNty, m_pRegLogic, CRegServiceLogic );
 	REG_MSG_HANDLER( UI_CNSTOOL_MSG_CallSer_IND, CRegServiceLogic::OnCallServerInfoInd, m_pRegLogic, CRegServiceLogic );
	REG_MSG_HANDLER( UI_CNSTOOL_MSG_UpgradeSer_NTY, CRegServiceLogic::OnUpdServiceIPNty, m_pRegLogic, CRegServiceLogic );
	REG_MSG_HANDLER( UI_CNSTOOL_MSG_UpgradeSer_IND, CRegServiceLogic::OnUpdServiceIPInd, m_pRegLogic, CRegServiceLogic );
}


CRegServiceLogic* CRegServiceLogic::GetLogicPtr()
{
	if ( m_pRegLogic == NULL )
	{  
		m_pRegLogic = new CRegServiceLogic();  
	}
	
	return m_pRegLogic;
}

void CRegServiceLogic::Clear()
{
	if ( m_pWndTree != NULL )
	{
		UpdateSipCfg( 0, 0 );
		UpdateGkCfg( 0, 0 );
		TTPCallSerInfo tTPCallSerInfo;
		SetCallServerInfo( tTPCallSerInfo );
        UIManagePtr->SetCaption( _T("IPCtrlServiceIp"), _T(""), m_pWndTree );

		UIManagePtr->LoadScheme( "SchmNormal", m_pWndTree);
	}
}


bool CRegServiceLogic::InitWnd( const IArgs & args )
{
	CWndLogicBase::InitWnd( args );
	
	TTPSipRegistrarCfg tSipCfg;
	ComInterface->GetSipCfg( tSipCfg );
	
	Value_IpEditData valIp;
	valIp.dwIP = ntohl(tSipCfg.dwRegIP);
    UIManagePtr->SetPropertyValue(valIp, "IPCtrlUpdServiceIp", m_pWndTree); 

	UpdateGkCfg( 0 , 0 );
	
	return true;
}

bool CRegServiceLogic::OnSave( const IArgs& args )
{
	Value_IpEditData valServiceIp;
    UIManagePtr->GetPropertyValue(valServiceIp, "IPCtrlServiceIp", m_pWndTree); 

    //У��ע�������IP
    Args_MsgBox msgArg; 
	String strServiceIp;
	UIManagePtr->GetCaption( "IPCtrlServiceIp" , strServiceIp , m_pWndTree );

	if ( !strServiceIp.empty() && !CCallAddr::IsValidIpV4(valServiceIp.dwIP) )//����ip��ַΪ�� ��Ϊ������֤ dyy 2013.7.9
	{   
		msgArg.pOwnerWnd = UIManagePtr->GetWindowPtr( "IPCtrlServiceIp", m_pWndTree );
		MSG_BOX( "����ע���������ַ�Ƿ�", FALSE, &msgArg );
		msgArg.pOwnerWnd->SetFocus();
		return false;
	}
	
	TTPSipRegistrarCfg tSipcfg;
	tSipcfg.bUsed = TRUE;
	tSipcfg.dwRegIP = htonl(valServiceIp.dwIP);
	tSipcfg.wRegPort = 5060;
	tSipcfg.wExpire = 40;
	
	TTPSipRegistrarCfg tOldSipCfg;
	ComInterface->GetSipCfg( tOldSipCfg );
	
	if ( tSipcfg.dwRegIP != tOldSipCfg.dwRegIP )
	{
        BOOL bInConf = BusinessManagePtr->IsInConf();
        if ( bInConf )
        {		
            MSG_BOX( "�����У������޸ķ���������", FALSE, &msgArg );
            return false;
	    }

		u16 wRet = NO_ERROR;		 
		wRet = ComInterface->CnsRegSipService( tSipcfg );
	}

	TTPGKCfg tOldGkCfg;
    ComInterface->GetGkCfg( tOldGkCfg );
	
    bool bUseGk = false;
    UIManagePtr->GetSwitchState( m_stBtnGkSwitch, bUseGk, m_pWndTree );
	
    Value_IpEditData valGkIp;
	UIManagePtr->GetPropertyValue(valGkIp, m_strGkIP, m_pWndTree); 
	
	//У��GK��������ַ
	String strGkIp;
    UIManagePtr->GetCaption( m_strGkIP, strGkIp, m_pWndTree );  
	
	if ( !CCallAddr::IsValidIpV4(valGkIp.dwIP) && !strGkIp.empty() )
	{
		Args_MsgBox msgArg;
		msgArg.pOwnerWnd = UIManagePtr->GetWindowPtr( m_strGkIP, m_pWndTree );
		MSG_BOX( "GK��������ַ�Ƿ�", FALSE, &msgArg );
		msgArg.pOwnerWnd->SetFocus();
		return false;
	} 
	
    if ( ( bUseGk != (bool)tOldGkCfg.bUsed ) || htonl( valGkIp.dwIP ) != tOldGkCfg.dwGKIP )
	{    
        Args_MsgBox msgArg;    
        BOOL bInConf = BusinessManagePtr->IsInConf();
        if ( bInConf )
        {		
            msgArg.pOwnerWnd = m_pWndTree->GetItemData()->pWnd;
            MSG_BOX( "�����У������޸ķ���������", FALSE, &msgArg );
			msgArg.pOwnerWnd->SetFocus();
            return false;
		}
		
		TTPGKCfg tSipcfg; 
		tSipcfg.wExpire = 40; 
		tSipcfg.bUsed = bUseGk;
		tSipcfg.dwGKIP = htonl(valGkIp.dwIP);  
		
        u16 wRet  = ComInterface->CnsRegGkService( tSipcfg );
        if ( wRet != NO_ERROR )
        {
            HANDLE_ERROR(wRet);
        }		 
	}

    //У����з�������ַ
	TTPCallSerInfo tCallSerInfo;
	
    String strCallServiceIP;
    UIManagePtr->GetCaption( _T("IPCtrlCallServiceIp"), strCallServiceIP, m_pWndTree );
    
    u32_ip dwCallServiceIP = inet_addr(strCallServiceIP.c_str());
    
    TTPCallSerInfo tCnsCallSerInfo;
    BusinessManagePtr->GetCallServerInfo( tCnsCallSerInfo );
	
    if ( tCnsCallSerInfo.dwCallServiceIP != dwCallServiceIP )
    {
        bool bGet = GetCallServerInfo( tCallSerInfo );
        if ( bGet == false )
        {
            return false;
        }
        
        BOOL bInConf = BusinessManagePtr->IsInConf();
        if ( bInConf )
        {
            Args_MsgBox msgArg;
            msgArg.pOwnerWnd = UIManagePtr->GetWindowPtr( _T(""), m_pWndTree );
            MSG_BOX( "�����У������޸ķ���������", FALSE, &msgArg );
            return false;
        }
        
        u16 wRet = NO_ERROR;		 
		wRet = ComInterface->CallServerCmd( tCallSerInfo );		
    }

	//У��������������ַ
	TTPUpgradeSer tCnsUpgSerInfo;
	BusinessManagePtr->GetUpgradeSerInfo( tCnsUpgSerInfo );
	
    String strUpdServiceIp = GetServiceIP();
    u32_ip dwUpgServiceIP = inet_addr(strUpdServiceIp.c_str());
	
    Value_IpEditData valUpdIp;
    UIManagePtr->GetPropertyValue(valUpdIp, "IPCtrlUpdServiceIp", m_pWndTree); 
	TTPUpgradeSer tUpgradeSer;
	tUpgradeSer.dwSerIP = htonl( valUpdIp.dwIP );
	
	if ( !strUpdServiceIp.empty() && !CCallAddr::IsValidIpV4(valUpdIp.dwIP) )//��������������Ϊ�� dyy 2013��8��27��
    {   
		Args_MsgBox msgArg; 
        msgArg.pOwnerWnd = UIManagePtr->GetWindowPtr( "IPCtrlUpdServiceIp", m_pWndTree );
        MSG_BOX( "������������ַ�Ƿ�", FALSE, &msgArg );
        msgArg.pOwnerWnd->SetFocus();
        return false;
	}  
	
	if ( tUpgradeSer.dwSerIP != tCnsUpgSerInfo.dwSerIP)
    {	    
		u16 wRet = NO_ERROR;		 
	    wRet = ComInterface->UpgradeSerCmd( tUpgradeSer );
	}

	UIManagePtr->LoadScheme( "SchmNormal", m_pWndTree);
	return true;
}

bool CRegServiceLogic::OnCancel( const IArgs& args )
{
	UpdateSipCfg( 0, 0 );
	UpdateGkCfg( 0, 0 );
	SetServiceIP();
	TTPCallSerInfo tCallSerInfo;
	ComInterface->GetCallServerInfo( tCallSerInfo );
	
	SetCallServerInfo( tCallSerInfo );	
	UIManagePtr->LoadScheme( "SchmNormal", m_pWndTree);
	return true;
}


bool CRegServiceLogic::OnEdit( const IArgs& args )
{	
	Args_MsgBox msgArg;
	msgArg.pOwnerWnd = m_pWndTree->GetItemData()->pWnd;

	TTPCnsConfStatus tConfStatus = BusinessManagePtr->GetLocalCnsConfState();
	if ( tConfStatus.emState == em_CALL_CONNECTED )
	{
		MSG_BOX( "�����У������޸ķ���������", FALSE, &msgArg );
		return false;
	}

	BOOL bInConf = BusinessManagePtr->IsInConf();
	if ( bInConf )
	{		
		MSG_BOX( "�����У������޸ķ���������", FALSE, &msgArg );
		return false;
	}

	UIManagePtr->LoadScheme( "SchmEdit", m_pWndTree);

	IArgs Args("");
    BtnSwitchGkClick( Args );
    UpdateGkCfg( 0 , 0 );

	UIManagePtr->SetFocus( "IPCtrlServiceIp", m_pWndTree );

	return true;
}

LRESULT CRegServiceLogic::UpdateSipCfg( WPARAM wParam, LPARAM lParam )
{
	if ( m_pWndTree == NULL )
	{
		return NO_ERROR;
	}

	TTPSipRegistrarCfg tSipCfg;
	ComInterface->GetSipCfg( tSipCfg );
	
	Value_IpEditData valIp;
	valIp.dwIP = ntohl(tSipCfg.dwRegIP);
    UIManagePtr->SetPropertyValue(valIp, "IPCtrlServiceIp", m_pWndTree); 

	return NO_ERROR;
}
 

LRESULT CRegServiceLogic::OnRegResultNty( WPARAM wParam, LPARAM lParam )
{
	if ( m_pWndTree == NULL )
	{
		return NO_ERROR;
	}

	EmTpCnsRegUms emReg = (EmTpCnsRegUms)wParam;

	BOOL bOk = FALSE;
	CString strTemp = "";
    switch( emReg )
    {		
    case tp_CnsRegRet_Success:		//�ɹ�
        bOk  = TRUE;
        break;
    case tp_CnsRegRet_MaxRegNum:		//ע����
        strTemp = "ע������Ѵﵽ���ֵ";
        break;
    case tp_CnsRegRet_MaxAliasNum:	//ע����
        strTemp = "ע������ĸ����Ѵﵽ���ֵ";
        break;
    case tp_CnsRegRet_MsgError:		//ע����Ϣ����
        strTemp = "ע����Ϣ����";
        break;
    case tp_CnsRegRet_AliasRepeat:	//�����ظ�
        strTemp = "ע������ظ�";
        break;
    case tp_CnsRegRet_UnReg:		//ɾ��ʱ��δ�ҵ�ɾ����¼
        strTemp = "δ�ҵ�ɾ����¼";
        break;
    case tp_CnsRegRet_SysError:		//APP����
        strTemp = "APP����";
        break;
    case tp_CnsRegRet_NotFind:		//����ʧ��
        strTemp = "����ʧ��";
        break;   
    case tp_CnsRegRet_Unreachable:   //���������ɴ�
        strTemp = "���������ɴ�";
        break;
    default:
		strTemp = ""; //"δ֪����";  //2012-8-7 SEʯ�ľ�ȷ��δ֪��������ʾ by yjj
    }

	
    CString strName;
	//strName.Format( "�᳡ %s ", (s8*)lParam );
	
	if ( bOk )
	{
		ShowPopMsg( "ע�����ʷ������ɹ�" );
	}
	else
	{   
		strName = "ע�����ʷ�����ʧ��";
		if ( !strTemp.IsEmpty() )
		{
			strName = strName + ": " + strTemp;
		}
		ShowPopMsg( strName );
	}
	return NO_ERROR;
}

LRESULT CRegServiceLogic::OnRegAliasRepeatNty( WPARAM wParam, LPARAM lParam )
{
	if ( m_pWndTree == NULL )
	{
		return NO_ERROR;
	}

	TTPRegNameRepeatInfo tRepeatInfo = *(TTPRegNameRepeatInfo*)wParam;

	CString strName;
	strName.Format( "ע�����ʷ�����ʧ��: ", (s8*)lParam );

	CString strTemp = "ע������ظ�";

	u32 dwSize = tRepeatInfo.dwsize;
	if ( 1 == dwSize )
	{
		TTPRegName tRegName = tRepeatInfo.atTPRegName[0];
		if ( tRegName.emPAAddrType == emTpAlias )
		{
			strTemp = "�᳡�����ظ�";
		}
		else if ( tRegName.emPAAddrType == emTpE164Num )
		{
			strTemp = "�᳡�����ظ�";
		}
	}
	else if ( 2 == dwSize )
	{
		strTemp = "�᳡���ƺͻ᳡���붼�ظ�";
	}

	ShowPopMsg( strName + strTemp );

	return NO_ERROR;
}


bool CRegServiceLogic::OnSysCfg( const IArgs& args )
{
    if ( ! UIManagePtr->IsVisible( "RegServiceDlg/BtnEdit" ) )
    {
		//SIP
		String strCaption;
		UIFACTORYMGR_PTR->GetCaption( "IPCtrlServiceIp", strCaption, m_pWndTree);
		DWORD dwIP = inet_addr(strCaption.c_str());
		if ( "" == strCaption )
		{
			dwIP = 0;
		}

        Value_IpEditData valIp;
        UIManagePtr->GetPropertyValue(valIp, "IPCtrlServiceIp", m_pWndTree); 
        TTPSipRegistrarCfg tSipcfg;
        tSipcfg.bUsed = TRUE;
        tSipcfg.dwRegIP = htonl(valIp.dwIP);
        tSipcfg.wRegPort = 5060;
        tSipcfg.wExpire = 40;
        
        TTPSipRegistrarCfg tOldSipCfg;
        ComInterface->GetSipCfg( tOldSipCfg );
		in_addr tAddr;
		tAddr.S_un.S_addr = tOldSipCfg.dwRegIP;
		String strOldInfo = inet_ntoa(tAddr);
		if ( "0.0.0.0" == strOldInfo )
		{
			strOldInfo = "";
		}

		//GK
		TTPGKCfg tOldGkCfg;
        ComInterface->GetGkCfg( tOldGkCfg );
		in_addr tGkAddr;
		tGkAddr.S_un.S_addr = tOldGkCfg.dwGKIP;
		String strOldGkInfo = inet_ntoa(tGkAddr);
		if ( "0.0.0.0" == strOldGkInfo )
		{
			strOldGkInfo = "";
		}
		
		String strGkCaption;
		UIFACTORYMGR_PTR->GetCaption( m_strGkIP, strGkCaption, m_pWndTree);
		DWORD dwGkIP = inet_addr(strGkCaption.c_str());
		if ( "" == strGkCaption )
		{
			dwGkIP = 0;
		}
		
        bool bUseGk = false;
        UIManagePtr->GetSwitchState( m_stBtnGkSwitch, bUseGk, m_pWndTree );
        
        Value_IpEditData valGkIp;
        UIManagePtr->GetPropertyValue(valGkIp, m_strGkIP, m_pWndTree); 
        
        TTPGKCfg tGkcfg; 
        tGkcfg.wExpire = 40; 
        tGkcfg.bUsed = bUseGk;
        tGkcfg.dwGKIP = htonl(valGkIp.dwIP);  

		//CallServerIP
		String strCallServiceIP;
        UIManagePtr->GetCaption( _T("IPCtrlCallServiceIp"), strCallServiceIP, m_pWndTree );
		
        u32_ip dwCallServiceIP = inet_addr(strCallServiceIP.c_str());
		if ( "" == strCallServiceIP )
		{
			dwCallServiceIP = 0;
		}
        
        TTPCallSerInfo tCnsCallSerInfo;
        BusinessManagePtr->GetCallServerInfo( tCnsCallSerInfo );
		in_addr tCallSerAddr;
		tCallSerAddr.S_un.S_addr = tCnsCallSerInfo.dwCallServiceIP;
		String strOldCallSerInfo = inet_ntoa(tCallSerAddr);
		if ( "0.0.0.0" == strOldCallSerInfo )
		{
			strOldCallSerInfo = "";
		}

		//UpdSerIP
		TTPUpgradeSer tCnsUpgSerInfo;
        BusinessManagePtr->GetUpgradeSerInfo( tCnsUpgSerInfo );
		in_addr tUpdAddr;
		tUpdAddr.S_un.S_addr = tCnsUpgSerInfo.dwSerIP;
		String strOldUpdInfo = inet_ntoa(tUpdAddr);
		if ( "0.0.0.0" == strOldUpdInfo )
		{
			strOldUpdInfo = "";
		}
        
        String strUpdServiceIp = GetServiceIP();
        u32_ip dwUpdServiceIP = inet_addr(strUpdServiceIp.c_str());
		if ( "" == strUpdServiceIp )
		{
			dwUpdServiceIP = 0;
		}
	
	if ( tSipcfg.dwRegIP != tOldSipCfg.dwRegIP || strCaption != strOldInfo || 
		( bUseGk != (bool)tOldGkCfg.bUsed ) || ( tGkcfg.dwGKIP != tOldGkCfg.dwGKIP ) || strGkCaption != strOldGkInfo ||
		tCnsCallSerInfo.dwCallServiceIP != dwCallServiceIP || strCallServiceIP != strOldCallSerInfo ||
		dwUpdServiceIP != tCnsUpgSerInfo.dwSerIP || strUpdServiceIp != strOldUpdInfo )
	{
		CString strMsg = "�Ƿ�Ա༭���б���?";
            Args_MsgBox argMsg;
            argMsg.pOwnerWnd = UIManagePtr->GetWindowPtr( "RegServiceDlg" );
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
// 	UIManagePtr->ShowWindow( "RegServiceDlg", false );
// 	UIManagePtr->ShowWindow( "SysCfgDlg", true );
	UIManagePtr->LoadScheme( "SchmSysCfg", NULL, "SysCfgDlg" );
	return true;
}

bool CRegServiceLogic::OnCloseDlg( const IArgs& args )
{
	return UIManagePtr->ShowWindow( "RegServiceDlg", false );
}

LRESULT CRegServiceLogic::UpdateGkCfg( WPARAM wParam, LPARAM lParam )
{
	if ( m_pWndTree == NULL )
	{
		return NO_ERROR;
	}
	
	TTPGKCfg tCfg;
	ComInterface->GetGkCfg( tCfg );
	
	Value_IpEditData valIp;
	valIp.dwIP = ntohl(tCfg.dwGKIP);
	UIManagePtr->SetPropertyValue(valIp, m_strGkIP, m_pWndTree); 
	
    UIManagePtr->SetSwitchState( m_stBtnGkSwitch, tCfg.bUsed, m_pWndTree );
    
	return NO_ERROR;
}

LRESULT CRegServiceLogic::OnRegRsp( WPARAM wParam, LPARAM lParam )
{
	if ( m_pWndTree == NULL )
	{
		return NO_ERROR;
	}

    bool bOk = false;
    TUCSipRegResult tRegResult = *(TUCSipRegResult*)wParam;

    CString strTemp = "";
    switch( tRegResult.m_emTpCnsRegUms )
    {  
    case tp_CnsRegRet_Success:		//�ɹ�
        bOk  = true;
        break;
    case tp_CnsRegRet_MaxRegNum:    //ע����
        strTemp = "ע������Ѵﵽ���ֵ";
        break;
    case tp_CnsRegRet_MaxAliasNum:	//ע����
        strTemp = "ע������ĸ����Ѵﵽ���ֵ";
        break;
    case tp_CnsRegRet_MsgError:		//ע����Ϣ����
        strTemp = "ע����Ϣ����";
        break;
    case tp_CnsRegRet_AliasRepeat:	//�����ظ�
        strTemp = "ע������ظ�";
        break;
    case tp_CnsRegRet_UnReg:	    //ɾ��ʱ��δ�ҵ�ɾ����¼
        strTemp = "δ�ҵ��ü�¼";
        break;
    case tp_CnsRegRet_SysError:		//APP����
        strTemp = "APP����";
        break;
    case tp_CnsRegRet_NotFind:		//����ʧ��
        strTemp = "����ʧ��";
        break;   
    case tp_CnsRegRet_Unreachable:  //���������ɴ�
        strTemp = "���������ɴ�";
        break;
    case tp_CnsRegRet_E164Repeat:   //E164���ظ�
        strTemp = "E164���ظ�";
        break;
	case tp_CnsRegRet_NameDup:
		strTemp = "������E164�����ظ�";
		break;
    default:
		strTemp = "";//2012-8-7 SEʯ�ľ�ȷ��δ֪��������ʾ by yjj
		break;
    }
	
	CString strName = "ע��GKʧ��";
 	 
	if ( bOk )
	{
		ShowPopMsg( "ע��GK�ɹ�" );
	}
	else
	{
        //�����ظ�ʱ��Ҫ��ϸ��ʾ
        /*
        if ( tRegResult.m_emTpCnsRegUms == tp_CnsRegRet_AliasRepeat )
        {           
            u32 dwSize = tRegResult.m_nAliasNum;
            if ( 1 == dwSize )
            {
                TTPAlias tRegAlias = tRegResult.m_atTPAlias[0];
                if ( tRegAlias.m_byType == tp_Alias_h323  )
                {
                    strTemp = "�᳡�����ظ�";
                }
                else if ( tRegAlias.m_byType == tp_Alias_e164 )
                {
                    strTemp = "�᳡�����ظ�";
                }
            }
            else if ( 2 == dwSize )
            {
                strTemp = "�᳡���ƺͻ᳡���붼�ظ�";
	        }
        }
        */
		if ( !strTemp.IsEmpty() )
		{
			strName = strName + ": " + strTemp;
		}

		ShowPopMsg( strName  );
	}
	return NO_ERROR;
}

LRESULT CRegServiceLogic::OnCallServiceInfoNty( WPARAM wParam, LPARAM lParam )
{
	if ( m_pWndTree == NULL )
	{
		return NO_ERROR;
	}
	
	TTPCallSerInfo tCallSerInfo;
	ComInterface->GetCallServerInfo( tCallSerInfo );
	
	SetCallServerInfo( tCallSerInfo );
	
	return NO_ERROR;
}

LRESULT CRegServiceLogic::OnCallServerInfoInd( WPARAM wParam, LPARAM lParam )
{
	if ( m_pWndTree == NULL )
	{
		return NO_ERROR;
	}
	
	BOOL bSuccess = *(BOOL*)(lParam);
	if ( TRUE != bSuccess )
	{
// 		Args_MsgBox msgArg;
// 		MSG_BOX( _T("���ú��з�������ַʧ��"), FALSE, &msgArg );
// 		UIManagePtr->SetFocus( _T("IPCtrlCallServiceIp"), m_pWndTree );
		ShowPopMsg( "���ú��з�������ַʧ��" );
	} 
	return S_OK;	
}

void CRegServiceLogic::SetCallServerInfo( TTPCallSerInfo tCallSerInfo )
{
	if ( m_pWndTree == NULL )
	{
		return;
	}
	
	in_addr tAddr;
	tAddr.S_un.S_addr = tCallSerInfo.dwCallServiceIP;
	String strServiceIP = inet_ntoa(tAddr);
	if ( strServiceIP == _T("0.0.0.0") )
	{
		strServiceIP = _T("");
	}
	UIManagePtr->SetCaption( _T("IPCtrlCallServiceIp") , strServiceIP , m_pWndTree );	
}

LRESULT CRegServiceLogic::OnUpdServiceIPNty( WPARAM wParam, LPARAM lParam )
{
	if ( m_pWndTree == NULL )
	{
		return NO_ERROR;
	}
	
	SetServiceIP();
    
	return NO_ERROR;
}

LRESULT CRegServiceLogic::OnUpdServiceIPInd( WPARAM wParam, LPARAM lParam )
{
	if ( m_pWndTree == NULL )
	{
		return NO_ERROR;
	}
	
	BOOL bRes = static_cast<BOOL>(lParam);
	if ( FALSE == bRes )
	{
// 		Args_MsgBox msgArg;
// 		msgArg.pOwnerWnd = UIManagePtr->GetWindowPtr( _T(""), m_pWndTree );
// 		MSG_BOX( _T("��������������ʧ��"), FALSE, &msgArg );
// 		UIManagePtr->SetFocus( _T("IPCtrlUpdServiceIp"), m_pWndTree );
		ShowPopMsg("��������������ʧ��");
	}

    //������������ֵ�������õ����ڼ���	
//	SetServiceIP();
    
	return NO_ERROR;
}

void CRegServiceLogic::SetServiceIP()
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
	UIManagePtr->SetCaption( _T("IPCtrlUpdServiceIp") , strServiceIP , m_pWndTree );
}

bool CRegServiceLogic::GetCallServerInfo( TTPCallSerInfo& tCallSerInfo )
{
	if ( m_pWndTree == NULL )
	{
		return false;
	}  
	
	Args_MsgBox msgArg;
	String strServiceIP;
	UIManagePtr->GetCaption( _T("IPCtrlCallServiceIp"), strServiceIP, m_pWndTree );
	
    Value_IpEditData valIp;
    UIManagePtr->GetPropertyValue(valIp, _T("IPCtrlCallServiceIp"), m_pWndTree ); 
	
	if ( !CCallAddr::IsValidIpV4( valIp.dwIP ) && !strServiceIP.empty() ) //��Ϊ�ս����ж� dyy
	{
		msgArg.pOwnerWnd = UIManagePtr->GetWindowPtr( _T("IPCtrlCallServiceIp"), m_pWndTree );
		MSG_BOX( _T("���з�������ַ��Ч"), FALSE, &msgArg );
		UIManagePtr->SetFocus( _T("IPCtrlCallServiceIp"), m_pWndTree );
		return false;
    }
	
    tCallSerInfo.dwCallServiceIP = htonl( valIp.dwIP );
	
	return true;
}

String CRegServiceLogic::GetServiceIP()
{
	String strServiceIP;
	UIManagePtr->GetCaption( _T("IPCtrlUpdServiceIp") , strServiceIP , m_pWndTree );
	return strServiceIP;
}

bool CRegServiceLogic::BtnSwitchGkClick( const IArgs& args )
{
    bool bUseGk = false;
    UIManagePtr->GetSwitchState( m_stBtnGkSwitch, bUseGk, m_pWndTree );
    if ( bUseGk )
    {
        UIManagePtr->EnableWindow( m_strGkIP, true, m_pWndTree );
    }
    else
    {   
        UIManagePtr->EnableWindow( m_strGkIP, false, m_pWndTree );
    }
    return true;
}

