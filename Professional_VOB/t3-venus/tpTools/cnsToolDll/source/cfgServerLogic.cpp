// cfgServerLogic.cpp: implementation of the CCfgServerLogic class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "cfgServerLogic.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCfgServerLogic::CCfgServerLogic()
: m_strEdtSIp("CfgServerDlg/SIPCtrlAddress")
, m_strBtnGKSwitch("CfgServerDlg/BtnGKSwitch")
, m_strEdtGKIP("CfgServerDlg/IPCtrlGKIp")
, m_strEdtCSIP("CfgServerDlg/IPCtrlCallServer")
, m_strEdtUGIP("CfgServerDlg/IPCtrlUpAddress")		 
{
	m_vctWndName.clear();
}

CCfgServerLogic::~CCfgServerLogic()
{

}

bool CCfgServerLogic::InitWnd( const IArgs & arg )
{
	CLogicBase::InitWnd( arg );	
	m_vctWndName.clear();
	UpBtnState();
	return true;
}

void CCfgServerLogic::RegMsg()
{
	CCfgServerLogic *pThis = GetSingletonPtr();
	REG_MSG_HANDLER( UI_CNS_REG_GK_NTY, CCfgServerLogic::OnUpdateGkNty, pThis, CCfgServerLogic );
	REG_MSG_HANDLER( UI_CNS_REGSIP_NOTIFY, CCfgServerLogic::OnUpdateSipNty, pThis, CCfgServerLogic );
	REG_MSG_HANDLER( UI_CNSTOOL_MSG_CallSer_NTY, CCfgServerLogic::OnCallSerNty, pThis, CCfgServerLogic );
	REG_MSG_HANDLER( UI_CNSTOOL_MSG_UpgradeSer_NTY, CCfgServerLogic::OnUpgradeSerNty, pThis, CCfgServerLogic );
	//ע�����ʷ�������Ϣ����
	REG_MSG_HANDLER( UI_CNS_SIPREG_ALIASREPEAT_NOTIFY, CCfgServerLogic::OnRegSIPAliasRepeatNty, pThis, CCfgServerLogic );
	REG_MSG_HANDLER( UI_CNS_REGRESULT_NOTIFY, CCfgServerLogic::OnRegSIPResultNty, pThis, CCfgServerLogic );
	//ע��GK��Ϣ����
	REG_MSG_HANDLER( UI_CNS_REG_GK_RSP, CCfgServerLogic::OnRegGKRsp, pThis, CCfgServerLogic );
	//ע����з�������Ϣ����
	REG_MSG_HANDLER( UI_CNSTOOL_MSG_CallSer_IND, CCfgServerLogic::OnCallSerInd, pThis, CCfgServerLogic );
	//ע��������������Ϣ����
	REG_MSG_HANDLER( UI_CNSTOOL_MSG_UpgradeSer_IND, CCfgServerLogic::OnUpgradeSerInd, pThis, CCfgServerLogic );
	//���ջ���״̬��Ϣ
	REG_MSG_HANDLER( UI_CNSTOOL_MSG_CONF_NTY, CCfgServerLogic::OnConfStateNty, pThis, CCfgServerLogic );
}

void CCfgServerLogic::UnRegMsg()
{
	
}

void CCfgServerLogic::RegCBFun()
{
	CCfgServerLogic *pThis = GetSingletonPtr();
	REG_GOBAL_MEMBER_FUNC( "CCfgServerLogic::InitWnd", CCfgServerLogic::InitWnd, pThis, CCfgServerLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgServerLogic::OnBtnSave", CCfgServerLogic::OnBtnSave, pThis, CCfgServerLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgServerLogic::OnBtnCancel", CCfgServerLogic::OnBtnCancel, pThis, CCfgServerLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgServerLogic::OnBtnSwitchGK", CCfgServerLogic::OnBtnSwitchGK, pThis, CCfgServerLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgServerLogic::OnChangedSIp", CCfgServerLogic::OnChangedSIp, pThis, CCfgServerLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgServerLogic::OnChangedGKIp", CCfgServerLogic::OnChangedGKIp, pThis, CCfgServerLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgServerLogic::OnChangedCallSerIp", CCfgServerLogic::OnChangedCallSerIp, pThis, CCfgServerLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgServerLogic::OnChangedUpSerIp", CCfgServerLogic::OnChangedUpSerIp, pThis, CCfgServerLogic );

}

void CCfgServerLogic::UnRegFunc()
{
	UN_REG_GOBAL_FUNC( "CCfgServerLogic::InitWnd" );	
}

void CCfgServerLogic::Clear()
{
	m_vctWndName.clear();
	UpBtnState();

}

bool CCfgServerLogic::OnBtnSave( const IArgs& args )
{
	BOOL bInConf = LIBDATAMGRPTR->IsInConf();
	if ( bInConf )
	{		
		MSG_BOX_OK( _T("�л�������У���������") );
		SetCallSerData();
		SetGKData();
		SetSipData();
		SetUpgradeSerData();
		m_vctWndName.clear();
		UpBtnState();
		OnConfStateNty(0,0);
		return false;	
	}

	bool bSucceed = true;
	bSucceed = SaveSip();
	if (false == bSucceed)
	{
		return false;
	}
	bSucceed = SaveGk();
	if (false == bSucceed)
	{
		return false;
	}
	bSucceed = SaveCallSer();
	if (false == bSucceed)
	{
		return false;
	}
	bSucceed = SaveUpgradeSer();
	if (false == bSucceed)
	{
		return false;
	}
	m_vctWndName.clear();
	UpBtnState();
	return true;
}

bool CCfgServerLogic::OnBtnCancel( const IArgs& args )
{
	SetCallSerData();
	SetGKData();
	SetSipData();
	SetUpgradeSerData();
	m_vctWndName.clear();
	UpBtnState();
	//�����鿪����,���ý���ȡ�������ȫ�������û�
	BOOL bInConf = LIBDATAMGRPTR->IsInConf();
	if ( bInConf )
	{		
		OnConfStateNty(0,0);
		return false;	
	}
	return true;
}

/*---------------------------------------------------------------------
* �������ƣ�FocusWindow
* ��    �ܣ�������ʾ���λ�����崰��λ��
* ����˵����
* �޸ļ�¼��
* ����			�汾		�޸���		�޸ļ�¼
* 2012/12/29	v1.0		������		����
----------------------------------------------------------------------*/
void CCfgServerLogic::FocusWindow(String strWindow)
{
	UIFACTORYMGR_PTR->SetFocus( strWindow, m_pWndTree );
}

/*---------------------------------------------------------------------
* �������ƣ�SaveSip
* ��    �ܣ�����ע�����ʷ���������	
* ����˵����
* �޸ļ�¼��
* ����			�汾		�޸���		�޸ļ�¼
* 2012/12/29	v1.0		������		����
----------------------------------------------------------------------*/
bool CCfgServerLogic::SaveSip( /*const IArgs& args*/ )
{		
	if ( m_pWndTree == NULL)
	{
		return S_FALSE;
	}
	String strServiceIp;
	Value_IpEditData valIp;
    UIFACTORYMGR_PTR->GetPropertyValue( valIp, m_strEdtSIp, m_pWndTree ); 
	
	//Ч��IP
	String strCaption;
	UIFACTORYMGR_PTR->GetCaption( m_strEdtSIp, strCaption, m_pWndTree );
	if ( !CCallAddr::IsValidIpV4(valIp.dwIP) && !strCaption.empty() )
	{   
		MSG_BOX_OK( "���ʷ�������ַ�Ƿ�" );
		FocusWindow(m_strEdtSIp);
		return false;
	}

	TTPSipRegistrarCfg tSipcfg;
	if ( strCaption.empty() )
	{  
		tSipcfg.bUsed = FALSE;
		tSipcfg.dwRegIP = 0;
		tSipcfg.wRegPort = 5060;
		tSipcfg.wExpire = 40;
	}
	else
	{	
		tSipcfg.bUsed = TRUE;
		tSipcfg.dwRegIP = htonl(valIp.dwIP);
		tSipcfg.wRegPort = 5060;
		tSipcfg.wExpire = 40;
	}		
	
	TTPSipRegistrarCfg tOldSipCfg;
	LIBDATAMGRPTR->GetSipCfg( tOldSipCfg );
	
	if ( tSipcfg.dwRegIP != tOldSipCfg.dwRegIP )
	{		 
		u16 wRet = COMIFMGRPTR->CnsRegSipService( tSipcfg );
		if (wRet != NO_ERROR)
		{
			WARNMESSAGE( "�������ʷ���������������ʧ��" );
			return false;
		}
	}
	return true;
}

/*---------------------------------------------------------------------
* �������ƣ�SaveGk
* ��    �ܣ�����GK����
* ����˵����
* �޸ļ�¼��
* ����			�汾		�޸���		�޸ļ�¼
* 2012/12/29	v1.0		������		����
----------------------------------------------------------------------*/
bool CCfgServerLogic::SaveGk()
{	
	//GK����
    TTPGKCfg tOldGkCfg;
    LIBDATAMGRPTR->GetGkCfg( tOldGkCfg );
	
    bool bUseGk = false;
    UIFACTORYMGR_PTR->GetSwitchState( m_strBtnGKSwitch, bUseGk, m_pWndTree );
	
    Value_IpEditData valGkIp;
	UIFACTORYMGR_PTR->GetPropertyValue(valGkIp, m_strEdtGKIP, m_pWndTree); 
	
	//Ч��IP
	String strCaption;
	UIFACTORYMGR_PTR->GetCaption( m_strEdtGKIP , strCaption , m_pWndTree ); 

	if ( !CCallAddr::IsValidIpV4(valGkIp.dwIP) && !strCaption.empty() )
	{
		MSG_BOX_OK( "GK��������ַ�Ƿ�" );
		FocusWindow(m_strEdtGKIP);
		return false;
	} 

    if ( ( bUseGk != (bool)tOldGkCfg.bUsed ) || htonl( valGkIp.dwIP ) != tOldGkCfg.dwGKIP )
	{        		
		TTPGKCfg tGkcfg; 
		tGkcfg.wExpire = 40; 
		tGkcfg.bUsed = bUseGk;
		tGkcfg.dwGKIP = htonl(valGkIp.dwIP);  
	
        u16 wRet  = COMIFMGRPTR->CnsRegGkService( tGkcfg );
		if (wRet != NO_ERROR)
		{
			//MSG_BOX_OK( "����GK����������ʧ��" );
			WARNMESSAGE( "����GK����������������ʧ��" );
			return false;
		}		 
	}
	return true;
}


LRESULT CCfgServerLogic::OnUpdateGkNty( WPARAM wParam, LPARAM lParam )
{
	if ( m_vctWndName.size() > 0 )
	{
		return S_FALSE;
	}
	SetGKData();
	return S_OK;
}

LRESULT CCfgServerLogic::OnUpdateSipNty( WPARAM wParam, LPARAM lParam )
{
	if ( m_vctWndName.size() > 0 )
	{
		return S_FALSE;
	}
	SetSipData();
	return S_OK;
}

LRESULT CCfgServerLogic::OnRegSIPAliasRepeatNty( WPARAM wParam, LPARAM lParam )
{
	if ( m_pWndTree == NULL )
	{
		return S_FALSE;
	}
	
	TTPRegNameRepeatInfo tRepeatInfo = *(TTPRegNameRepeatInfo*)wParam;
	
	CString strName;
	strName.Format( "%sע�����ʷ�����ʧ�ܣ�", (s8*)lParam );
	
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
	strName = strName + strTemp;
	//MSG_BOX_OK((String)strName);
	WARNMESSAGE(strName);
	FocusWindow(m_strEdtSIp);
	CMsgDispatch::SendMessage( UI_CNSTOOL_MSG_SIPRsp_NTY, 0, 0 );
	return S_OK;
}

LRESULT CCfgServerLogic::OnRegSIPResultNty( WPARAM wParam, LPARAM lParam )
{
	if ( m_pWndTree == NULL )
	{
		return S_FALSE;
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
		strTemp = ""; //"δ֪����";  
    }
	
	
    CString strName;
	
	if ( bOk )
	{
		//MSG_BOX_OK( "ע��SIP�������ɹ�" );
		WARNMESSAGE( "ע�����ʷ������ɹ�" );
	}
	else
	{   
		strName = "ע�����ʷ�����ʧ��";
		if ( !strTemp.IsEmpty() )
		{
			strName = strName + "��" + strTemp;
		}
		//String str(strName);
		//MSG_BOX_OK(str);
		WARNMESSAGE(strName);
		FocusWindow(m_strEdtSIp);
	}
	CMsgDispatch::SendMessage( UI_CNSTOOL_MSG_SIPRsp_NTY, (WPARAM)bOk, 0 );
	return S_OK;
}

LRESULT CCfgServerLogic::OnRegGKRsp( WPARAM wParam, LPARAM lParam )
{
	if ( m_pWndTree == NULL )
	{
		return S_FALSE;
	}
	
    bool bOk = false;
    TUCSipRegResult tRegResult = *(TUCSipRegResult*)wParam;
	
    CString strTemp = "";
    switch( tRegResult.m_emTpCnsRegUms )
    {  
    case tp_CnsRegRet_Success:		//�ɹ�
        bOk  = true;
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
    case tp_CnsRegRet_UnReg:	    //ɾ��ʱ��δ�ҵ�ɾ����¼
        strTemp = "δ�ҵ��ü�¼";
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
		strTemp = "";
		break;
    }
	
	CString strName = "ע��GK������ʧ��";
	
	if ( bOk )
	{
		//MSG_BOX_OK( "ע��GK�ɹ�" );
		WARNMESSAGE( "ע��GK�������ɹ�" );
	}
	else
	{
		if ( !strTemp.IsEmpty() )
		{
			strName = strName + "��" + strTemp;
		}
		
		//MSG_BOX_OK((String)strName);
		WARNMESSAGE(strName);
		FocusWindow(m_strEdtGKIP);
	}
	CMsgDispatch::SendMessage( UI_CNSTOOL_MSG_GKRsp_NTY, (WPARAM)bOk, 0 );
	return S_OK;
}

bool CCfgServerLogic::OnBtnSwitchGK( const IArgs& args )
{
	TTPGKCfg tGkCfg;
	LIBDATAMGRPTR->GetGkCfg( tGkCfg );

	bool bUseGK = false;
    UIFACTORYMGR_PTR->GetSwitchState( m_strBtnGKSwitch, bUseGK, m_pWndTree );
    if ( bUseGK )
    {
        UIFACTORYMGR_PTR->LoadScheme( "SchmEdit", m_pWndTree, m_strEdtGKIP); 
    }
    else
    {   
        UIFACTORYMGR_PTR->LoadScheme( "SchmNormal", m_pWndTree,m_strEdtGKIP);
    }

	bool bChange = false;
	if ( (BOOL)bUseGK != tGkCfg.bUsed )
	{
		bChange = true;
	}	
	CheckData(m_strBtnGKSwitch,bChange);
	return true;	
}

LRESULT CCfgServerLogic::OnCallSerNty( WPARAM wParam, LPARAM lParam )
{
	if ( m_vctWndName.size() > 0 )
	{
		return S_FALSE;
	}
	SetCallSerData();
	return S_OK;
}

LRESULT CCfgServerLogic::OnCallSerInd( WPARAM wParam, LPARAM lParam )
{	
	BOOL bSuccess = *(BOOL*)(lParam);
	if ( TRUE != bSuccess )
	{
		//MSG_BOX_OK("���ú��з�������ַʧ��");
		WARNMESSAGE("���ú��з�������ַʧ��");
		FocusWindow(m_strEdtCSIP);
	} 
	return S_OK;	
}

bool CCfgServerLogic::SaveCallSer()
{
	Value_IpEditData valIp;
    UIFACTORYMGR_PTR->GetPropertyValue( valIp, m_strEdtCSIP, m_pWndTree ); 
	
	TTPCallSerInfo tCallSerInfo;
	tCallSerInfo.dwCallServiceIP = htonl(valIp.dwIP);
	
	TTPCallSerInfo tOldCallSerInfo;
	LIBDATAMGRPTR->GetCallServerInfo(tOldCallSerInfo);

	//Ч��IP
	String strCaption;
	UIFACTORYMGR_PTR->GetCaption( m_strEdtCSIP, strCaption, m_pWndTree );
	
	if ( !CCallAddr::IsValidIpV4(valIp.dwIP) && !strCaption.empty() )
	{   
		MSG_BOX_OK( "���з�������ַ�Ƿ�" );
		FocusWindow(m_strEdtCSIP);
		return false;
	}

	if ( tOldCallSerInfo.dwCallServiceIP != tCallSerInfo.dwCallServiceIP )
	{
		u16 wRet = COMIFMGRPTR->CallServerCmd( tCallSerInfo );
		if (wRet != NO_ERROR)
		{
			WARNMESSAGE( "������з���������������ʧ��" );
			return false;
		}
	}
	return true;
}

bool CCfgServerLogic::IsCfgSerChange()
{
	s32 n = m_vctWndName.size();
	if ( n > 0 )
	{
		return SaveMsgBox();
	}
	return true;
}

bool CCfgServerLogic::SaveMsgBox()
{
	IArgs args("");
	MSGBOX_RET nMsgBoxRet = MSGBOX_CANCEL;
	MSG_BOX( nMsgBoxRet, "���������޸ģ��Ƿ񱣴����ã�" );	
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

bool CCfgServerLogic::OnChangedSIp( const IArgs& args )
{
	if (m_pWndTree == NULL)
	{
		return false;
	}	
	TTPSipRegistrarCfg tOldSipCfg;
	LIBDATAMGRPTR->GetSipCfg( tOldSipCfg );
	in_addr tAddr;
	tAddr.S_un.S_addr = tOldSipCfg.dwRegIP;
	String strOldInfo = inet_ntoa(tAddr);
	if ( "0.0.0.0" == strOldInfo )
	{
		strOldInfo = "";
	}
	
	bool bChange = false;
	//DWORD dwIP = StrToDWIp( m_strEdtSIp );
	String strCaption;
	UIFACTORYMGR_PTR->GetCaption( m_strEdtSIp, strCaption, m_pWndTree);
// 	DWORD dwIP = inet_addr(strCaption.c_str());
// 	if ( "" == strCaption )
// 	{
// 		dwIP = 0;
// 	}

	if ( /*dwIP != tOldSipCfg.dwRegIP || */strCaption != strOldInfo )
	{
	 	bChange = true;		
	}

	CheckData(m_strEdtSIp,bChange);
	return true;
}

bool CCfgServerLogic::OnChangedGKIp( const IArgs& args )
{
	if (m_pWndTree == NULL)
	{
		return false;
	}
	TTPGKCfg tOldGkCfg;
    LIBDATAMGRPTR->GetGkCfg( tOldGkCfg );
	in_addr tAddr;
	tAddr.S_un.S_addr = tOldGkCfg.dwGKIP;
	String strOldInfo = inet_ntoa(tAddr);
	if ( "0.0.0.0" == strOldInfo )
	{
		strOldInfo = "";
	}

	bool bChange = false;
	//DWORD dwIP = StrToDWIp( m_strEdtGKIP );
	
	String strCaption;
	UIFACTORYMGR_PTR->GetCaption( m_strEdtGKIP, strCaption, m_pWndTree);
// 	DWORD dwIP = inet_addr(strCaption.c_str());
// 	if ( "" == strCaption )
// 	{
// 		dwIP = 0;
// 	}

    if ( /*dwIP != tOldGkCfg.dwGKIP || */strCaption != strOldInfo )
	{ 
		bChange = true;	
	}

	CheckData(m_strEdtGKIP,bChange);
	return true;	
}

bool CCfgServerLogic::OnChangedCallSerIp( const IArgs& args )
{
	if ( m_pWndTree == NULL )
	{
		return false;
	}
	bool bChange = false;
	//DWORD dwIP = StrToDWIp( m_strEdtCSIP );

	TTPCallSerInfo tCallSerInfo;
	LIBDATAMGRPTR->GetCallServerInfo(tCallSerInfo);
	in_addr tAddr;
	tAddr.S_un.S_addr = tCallSerInfo.dwCallServiceIP;
	String strOldInfo = inet_ntoa(tAddr);
	if ( "0.0.0.0" == strOldInfo )
	{
		strOldInfo = "";
	}

	String strCaption;
	UIFACTORYMGR_PTR->GetCaption( m_strEdtCSIP, strCaption, m_pWndTree);
// 	DWORD dwIP = inet_addr(strCaption.c_str());
// 	if ( "" == strCaption )
// 	{
// 		dwIP = 0;
// 	}

	if ( /*dwIP != tCallSerInfo.dwCallServiceIP || */strCaption != strOldInfo )
	{ 
		bChange = true;	
	}
	
	CheckData(m_strEdtCSIP,bChange);
	return true;	
}

bool CCfgServerLogic::OnChangedUpSerIp( const IArgs& args )
{
	if ( m_pWndTree == NULL )
	{
		return false;
	}
	bool bChange = false;
	//DWORD dwIP = StrToDWIp( m_strEdtUGIP );

	TTPUpgradeSer tUpgradeSer;
	LIBDATAMGRPTR->GetUpgradeSerInfo( tUpgradeSer );
	in_addr tAddr;
	tAddr.S_un.S_addr = tUpgradeSer.dwSerIP;
	String strOldInfo = inet_ntoa(tAddr);
	if ( "0.0.0.0" == strOldInfo )
	{
		strOldInfo = "";
	}
	
	String strCaption;
	UIFACTORYMGR_PTR->GetCaption( m_strEdtUGIP, strCaption, m_pWndTree);
// 	DWORD dwIP = inet_addr(strCaption.c_str());
// 	if ( "" == strCaption )
// 	{
// 		dwIP = 0;
// 	}

	if ( /*dwIP != tUpgradeSer.dwSerIP || */strCaption != strOldInfo )
	{ 
		bChange = true;	
	}

	CheckData(m_strEdtUGIP,bChange);
	return true;		
}

void CCfgServerLogic::SetGKData()
{
	if ( m_pWndTree == NULL )
	{
		return;
	}	
	TTPGKCfg tGkCfg;
	LIBDATAMGRPTR->GetGkCfg( tGkCfg );
	
	Value_IpEditData valIp;
	valIp.dwIP = ntohl(tGkCfg.dwGKIP);
	UIFACTORYMGR_PTR->SetPropertyValue( valIp, m_strEdtGKIP, m_pWndTree ); 

	UIFACTORYMGR_PTR->SetSwitchState( m_strBtnGKSwitch, tGkCfg.bUsed, m_pWndTree );
    if ( tGkCfg.bUsed )
    {
		BOOL bInConf = LIBDATAMGRPTR->IsInConf();
		if ( !bInConf )
		{
			UIFACTORYMGR_PTR->LoadScheme( "SchmEdit", m_pWndTree, m_strEdtGKIP); 
		}
    }
    else
    {   
        UIFACTORYMGR_PTR->LoadScheme( "SchmNormal", m_pWndTree,m_strEdtGKIP);
    }
}

void CCfgServerLogic::SetSipData()
{
	if ( m_pWndTree == NULL )
	{
		return;
	}
	TTPSipRegistrarCfg tSipCfg;
	LIBDATAMGRPTR->GetSipCfg( tSipCfg );
	
	Value_IpEditData valIp;
	valIp.dwIP = ntohl(tSipCfg.dwRegIP);
    UIFACTORYMGR_PTR->SetPropertyValue( valIp, m_strEdtSIp, m_pWndTree ); 
}

void CCfgServerLogic::SetCallSerData()
{
	if ( m_pWndTree == NULL )
	{
		return;
	}	
	TTPCallSerInfo tCallSerInfo;
	LIBDATAMGRPTR->GetCallServerInfo(tCallSerInfo);

	Value_IpEditData valIp;
	valIp.dwIP = ntohl(tCallSerInfo.dwCallServiceIP);
	UIFACTORYMGR_PTR->SetPropertyValue( valIp, m_strEdtCSIP, m_pWndTree ); 
}

LRESULT CCfgServerLogic::OnUpgradeSerNty( WPARAM wParam, LPARAM lParam )
{
	if ( m_vctWndName.size() > 0 )
	{
		return S_FALSE;
	}
	SetUpgradeSerData();
	return S_OK;
}

LRESULT CCfgServerLogic::OnUpgradeSerInd( WPARAM wParam, LPARAM lParam )
{
	BOOL bSuccess = (BOOL)(lParam);
	if ( TRUE != bSuccess )
	{
		//MSG_BOX_OK("����������������ַʧ��");
		WARNMESSAGE("����������������ַʧ��");
		FocusWindow(m_strEdtUGIP);
	} 
	return S_OK;
}

void CCfgServerLogic::SetUpgradeSerData()
{
	if ( m_pWndTree == NULL )
	{
		return;
	}	
	TTPUpgradeSer tUpgradeSer;
	LIBDATAMGRPTR->GetUpgradeSerInfo( tUpgradeSer );
	
	Value_IpEditData valIp;
	valIp.dwIP = ntohl(tUpgradeSer.dwSerIP);
	UIFACTORYMGR_PTR->SetPropertyValue( valIp, m_strEdtUGIP, m_pWndTree ); 
}

bool CCfgServerLogic::SaveUpgradeSer()
{
	Value_IpEditData valIp;
    UIFACTORYMGR_PTR->GetPropertyValue( valIp, m_strEdtUGIP, m_pWndTree ); 

	TTPUpgradeSer tOldUpgradeSer;
	LIBDATAMGRPTR->GetUpgradeSerInfo( tOldUpgradeSer );

	//Ч��IP
	String strCaption;
	UIFACTORYMGR_PTR->GetCaption( m_strEdtUGIP, strCaption, m_pWndTree );

	if ( !CCallAddr::IsValidIpV4(valIp.dwIP) && !strCaption.empty() )
	{   
		MSG_BOX_OK( "������������ַ�Ƿ�" );
		FocusWindow(m_strEdtUGIP);
		return false;
	}

	if ( htonl(valIp.dwIP) != tOldUpgradeSer.dwSerIP )
	{
		TTPUpgradeSer tUpgradeSer;
		tUpgradeSer.dwSerIP = htonl(valIp.dwIP);
		u16 wRet = COMIFMGRPTR->UpgradeSerCmd( tUpgradeSer );
		if (wRet != NO_ERROR)
		{
			//MSG_BOX_OK( "������������������������ʧ��" );
			WARNMESSAGE( "������������������������ʧ��" );
			return false;
		}
	}
	return true;
}

LRESULT CCfgServerLogic::OnConfStateNty( WPARAM wparam, LPARAM lparam )
{
	if ( m_vctWndName.size() > 0  && m_pWndTree != NULL )
	{
		return S_FALSE;
	}
	bool bUseGk = false;
    UIFACTORYMGR_PTR->GetSwitchState( m_strBtnGKSwitch, bUseGk, m_pWndTree );

	BOOL bInConf = LIBDATAMGRPTR->IsInConf();
	if ( bInConf )
	{
		UIFACTORYMGR_PTR->LoadScheme( "SchmConf", m_pWndTree );
		if ( bUseGk )		//���������еĴ�����Ϊdisable״̬
		{
			UIFACTORYMGR_PTR->EnableWindow( m_strEdtGKIP, false, m_pWndTree );
		}
	} 
	else
	{
		UIFACTORYMGR_PTR->LoadScheme( "SchmNoConf", m_pWndTree );
		if ( bUseGk )
		{
			UIFACTORYMGR_PTR->EnableWindow( m_strEdtGKIP, true, m_pWndTree );
		} 
		else
		{
			UIFACTORYMGR_PTR->EnableWindow( m_strEdtGKIP, false, m_pWndTree );
		}
	}
	return S_OK;
}

DWORD CCfgServerLogic::StrToDWIp( String strName )
{
	String strCaption;
	UIFACTORYMGR_PTR->GetCaption( strName, strCaption, m_pWndTree);
	if ( strCaption == "0." || strCaption == "00." || strCaption == "000." )
	{
		MSG_BOX_OK( "0������Ч��.��ָ��һ������1��223���ֵ." );
		UIFACTORYMGR_PTR->SetCaption( strName, "1.", m_pWndTree);
		Window* pWnd = UIFACTORYMGR_PTR->GetWindowPtr( strName, m_pWndTree );
		if ( pWnd )
		{
			(( CEdit *) pWnd)->SetSel( -1 );
		}
	}
	DWORD dwIP = inet_addr(strCaption.c_str());
	if ( strCaption.empty() )
	{
		dwIP = 0;
	}
	return dwIP;
}
