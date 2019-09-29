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
	//注册网呈服务器消息反馈
	REG_MSG_HANDLER( UI_CNS_SIPREG_ALIASREPEAT_NOTIFY, CCfgServerLogic::OnRegSIPAliasRepeatNty, pThis, CCfgServerLogic );
	REG_MSG_HANDLER( UI_CNS_REGRESULT_NOTIFY, CCfgServerLogic::OnRegSIPResultNty, pThis, CCfgServerLogic );
	//注册GK消息反馈
	REG_MSG_HANDLER( UI_CNS_REG_GK_RSP, CCfgServerLogic::OnRegGKRsp, pThis, CCfgServerLogic );
	//注册呼叫服务器消息反馈
	REG_MSG_HANDLER( UI_CNSTOOL_MSG_CallSer_IND, CCfgServerLogic::OnCallSerInd, pThis, CCfgServerLogic );
	//注册升级服务器消息反馈
	REG_MSG_HANDLER( UI_CNSTOOL_MSG_UpgradeSer_IND, CCfgServerLogic::OnUpgradeSerInd, pThis, CCfgServerLogic );
	//接收会议状态消息
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
		MSG_BOX_OK( _T("有会议进行中，不能配置") );
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
	//当会议开启后,配置界面取消保存后将全部界面置灰
	BOOL bInConf = LIBDATAMGRPTR->IsInConf();
	if ( bInConf )
	{		
		OnConfStateNty(0,0);
		return false;	
	}
	return true;
}

/*---------------------------------------------------------------------
* 函数名称：FocusWindow
* 功    能：弹出提示框后定位到具体窗口位置
* 特殊说明：
* 修改记录：
* 日期			版本		修改人		修改记录
* 2012/12/29	v1.0		景洋洋		创建
----------------------------------------------------------------------*/
void CCfgServerLogic::FocusWindow(String strWindow)
{
	UIFACTORYMGR_PTR->SetFocus( strWindow, m_pWndTree );
}

/*---------------------------------------------------------------------
* 函数名称：SaveSip
* 功    能：保存注册网呈服务器部分	
* 特殊说明：
* 修改记录：
* 日期			版本		修改人		修改记录
* 2012/12/29	v1.0		景洋洋		创建
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
	
	//效验IP
	String strCaption;
	UIFACTORYMGR_PTR->GetCaption( m_strEdtSIp, strCaption, m_pWndTree );
	if ( !CCallAddr::IsValidIpV4(valIp.dwIP) && !strCaption.empty() )
	{   
		MSG_BOX_OK( "网呈服务器地址非法" );
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
			WARNMESSAGE( "保存网呈服务器配置请求发送失败" );
			return false;
		}
	}
	return true;
}

/*---------------------------------------------------------------------
* 函数名称：SaveGk
* 功    能：保存GK设置
* 特殊说明：
* 修改记录：
* 日期			版本		修改人		修改记录
* 2012/12/29	v1.0		景洋洋		创建
----------------------------------------------------------------------*/
bool CCfgServerLogic::SaveGk()
{	
	//GK设置
    TTPGKCfg tOldGkCfg;
    LIBDATAMGRPTR->GetGkCfg( tOldGkCfg );
	
    bool bUseGk = false;
    UIFACTORYMGR_PTR->GetSwitchState( m_strBtnGKSwitch, bUseGk, m_pWndTree );
	
    Value_IpEditData valGkIp;
	UIFACTORYMGR_PTR->GetPropertyValue(valGkIp, m_strEdtGKIP, m_pWndTree); 
	
	//效验IP
	String strCaption;
	UIFACTORYMGR_PTR->GetCaption( m_strEdtGKIP , strCaption , m_pWndTree ); 

	if ( !CCallAddr::IsValidIpV4(valGkIp.dwIP) && !strCaption.empty() )
	{
		MSG_BOX_OK( "GK服务器地址非法" );
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
			//MSG_BOX_OK( "保存GK配置请求发送失败" );
			WARNMESSAGE( "保存GK服务器配置请求发送失败" );
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
	strName.Format( "%s注册网呈服务器失败：", (s8*)lParam );
	
	CString strTemp = "注册别名重复";
	
	u32 dwSize = tRepeatInfo.dwsize;
	if ( 1 == dwSize )
	{
		TTPRegName tRegName = tRepeatInfo.atTPRegName[0];
		if ( tRegName.emPAAddrType == emTpAlias )
		{
			strTemp = "会场名称重复";
		}
		else if ( tRegName.emPAAddrType == emTpE164Num )
		{
			strTemp = "会场号码重复";
		}
	}
	else if ( 2 == dwSize )
	{
		strTemp = "会场名称和会场号码都重复";
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
    case tp_CnsRegRet_Success:		//成功
        bOk  = TRUE;
        break;
    case tp_CnsRegRet_MaxRegNum:		//注册满
        strTemp = "注册个数已达到最大值";
        break;
    case tp_CnsRegRet_MaxAliasNum:	//注册满
        strTemp = "注册别名的个数已达到最大值";
        break;
    case tp_CnsRegRet_MsgError:		//注册消息错误
        strTemp = "注册消息错误";
        break;
    case tp_CnsRegRet_AliasRepeat:	//别名重复
        strTemp = "注册别名重复";
        break;
    case tp_CnsRegRet_UnReg:		//删除时，未找到删除记录
        strTemp = "未找到删除记录";
        break;
    case tp_CnsRegRet_SysError:		//APP错误
        strTemp = "APP错误";
        break;
    case tp_CnsRegRet_NotFind:		//查找失败
        strTemp = "查找失败";
        break;   
    case tp_CnsRegRet_Unreachable:   //服务器不可达
        strTemp = "服务器不可达";
        break;
    default:
		strTemp = ""; //"未知错误";  
    }
	
	
    CString strName;
	
	if ( bOk )
	{
		//MSG_BOX_OK( "注册SIP服务器成功" );
		WARNMESSAGE( "注册网呈服务器成功" );
	}
	else
	{   
		strName = "注册网呈服务器失败";
		if ( !strTemp.IsEmpty() )
		{
			strName = strName + "：" + strTemp;
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
    case tp_CnsRegRet_Success:		//成功
        bOk  = true;
        break;
    case tp_CnsRegRet_MaxRegNum:		//注册满
        strTemp = "注册个数已达到最大值";
        break;
    case tp_CnsRegRet_MaxAliasNum:	//注册满
        strTemp = "注册别名的个数已达到最大值";
        break;
    case tp_CnsRegRet_MsgError:		//注册消息错误
        strTemp = "注册消息错误";
        break;
    case tp_CnsRegRet_AliasRepeat:	//别名重复
        strTemp = "注册别名重复";
        break;
    case tp_CnsRegRet_UnReg:	    //删除时，未找到删除记录
        strTemp = "未找到该记录";
        break;
    case tp_CnsRegRet_SysError:		//APP错误
        strTemp = "APP错误";
        break;
    case tp_CnsRegRet_NotFind:		//查找失败
        strTemp = "查找失败";
        break;   
    case tp_CnsRegRet_Unreachable:   //服务器不可达
        strTemp = "服务器不可达";
        break;
    default:
		strTemp = "";
		break;
    }
	
	CString strName = "注册GK服务器失败";
	
	if ( bOk )
	{
		//MSG_BOX_OK( "注册GK成功" );
		WARNMESSAGE( "注册GK服务器成功" );
	}
	else
	{
		if ( !strTemp.IsEmpty() )
		{
			strName = strName + "：" + strTemp;
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
		//MSG_BOX_OK("设置呼叫服务器地址失败");
		WARNMESSAGE("设置呼叫服务器地址失败");
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

	//效验IP
	String strCaption;
	UIFACTORYMGR_PTR->GetCaption( m_strEdtCSIP, strCaption, m_pWndTree );
	
	if ( !CCallAddr::IsValidIpV4(valIp.dwIP) && !strCaption.empty() )
	{   
		MSG_BOX_OK( "呼叫服务器地址非法" );
		FocusWindow(m_strEdtCSIP);
		return false;
	}

	if ( tOldCallSerInfo.dwCallServiceIP != tCallSerInfo.dwCallServiceIP )
	{
		u16 wRet = COMIFMGRPTR->CallServerCmd( tCallSerInfo );
		if (wRet != NO_ERROR)
		{
			WARNMESSAGE( "保存呼叫服务器配置请求发送失败" );
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
		//MSG_BOX_OK("设置升级服务器地址失败");
		WARNMESSAGE("设置升级服务器地址失败");
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

	//效验IP
	String strCaption;
	UIFACTORYMGR_PTR->GetCaption( m_strEdtUGIP, strCaption, m_pWndTree );

	if ( !CCallAddr::IsValidIpV4(valIp.dwIP) && !strCaption.empty() )
	{   
		MSG_BOX_OK( "升级服务器地址非法" );
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
			//MSG_BOX_OK( "保存升级服务器配置请求发送失败" );
			WARNMESSAGE( "保存升级服务器配置请求发送失败" );
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
		if ( bUseGk )		//会议中所有的窗口置为disable状态
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
		MSG_BOX_OK( "0不是有效项.请指定一个介于1和223间的值." );
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
