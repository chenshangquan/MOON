// regservicelogic.cpp: implementation of the CRegServiceLogic class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "regGklogic.h"
#include "msgBoxLogic.h"

String CRegGkLogic::m_stBtnGkSwitch = "BtnGkSwitch";
String CRegGkLogic::m_strGkIP = "IPCtrlGkIp";
CRegGkLogic * CRegGkLogic::m_pRegLogic = NULL;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CRegGkLogic::CRegGkLogic()
{

}

CRegGkLogic::~CRegGkLogic()
{
	if ( m_pRegLogic != NULL )
	{   
		UnRegMsg();
		UnRegFunc();
		delete m_pRegLogic;
		m_pRegLogic = NULL;
	}
}

bool CRegGkLogic::RegCBFun()
{
	REG_GOBAL_MEMBER_FUNC( "CRegGkLogic::InitWnd", CRegGkLogic::InitWnd, m_pRegLogic, CRegGkLogic );
	REG_GOBAL_MEMBER_FUNC( "CRegGkLogic::OnSave", CRegGkLogic::OnSave, m_pRegLogic, CRegGkLogic );
	REG_GOBAL_MEMBER_FUNC( "CRegGkLogic::OnCancel", CRegGkLogic::OnCancel, m_pRegLogic, CRegGkLogic );
	REG_GOBAL_MEMBER_FUNC( "CRegGkLogic::OnEdit", CRegGkLogic::OnEdit, m_pRegLogic, CRegGkLogic );
	REG_GOBAL_MEMBER_FUNC( "CRegGkLogic::OnSysCfg", CRegGkLogic::OnSysCfg, m_pRegLogic, CRegGkLogic );
	REG_GOBAL_MEMBER_FUNC( "CRegGkLogic::OnCloseDlg", CRegGkLogic::OnCloseDlg, m_pRegLogic, CRegGkLogic );
    REG_GOBAL_MEMBER_FUNC( "CRegGkLogic::BtnSwitchGkClick", CRegGkLogic::BtnSwitchGkClick, m_pRegLogic, CRegGkLogic );
    
	return true;
}

bool CRegGkLogic::UnRegFunc()
{
	
	return true;
}

void CRegGkLogic::RegMsg()
{
	REG_MSG_HANDLER( UI_CNS_REG_GK_NTY, CRegGkLogic::UpdateGkCfg, m_pRegLogic, CRegGkLogic );
  
	REG_MSG_HANDLER( UI_CNS_REG_GK_RSP, CRegGkLogic::OnRegRsp, m_pRegLogic, CRegGkLogic );	  
}


CRegGkLogic* CRegGkLogic::GetLogicPtr()
{
	if ( m_pRegLogic == NULL )
	{  
		m_pRegLogic = new CRegGkLogic();  
	}
	
	return m_pRegLogic;
}

void CRegGkLogic::Clear()
{
	if ( m_pWndTree != NULL )
	{
		UpdateGkCfg( 0, 0 );		
		UIManagePtr->LoadScheme( "SchmNormal", m_pWndTree);
	}
}


bool CRegGkLogic::InitWnd( const IArgs & args )
{
	CWndLogicBase::InitWnd( args );
	
	UpdateGkCfg( 0 , 0 );
	return true;
}

bool CRegGkLogic::OnSave( const IArgs& args )
{
    TTPGKCfg tOldGkCfg;
    ComInterface->GetGkCfg( tOldGkCfg );

    bool bUseGk = false;
    UIManagePtr->GetSwitchState( m_stBtnGkSwitch, bUseGk, m_pWndTree );

    Value_IpEditData valIp;
	UIManagePtr->GetPropertyValue(valIp, m_strGkIP, m_pWndTree); 

	//效验IP
	String strCaption;
    UIManagePtr->GetCaption( m_strGkIP, strCaption, m_pWndTree );  
	
	if ( !CCallAddr::IsValidIpV4(valIp.dwIP) && !strCaption.empty() )
	{
		Args_MsgBox msgArg;
		msgArg.pOwnerWnd = UIManagePtr->GetWindowPtr( m_strGkIP, m_pWndTree );
		MSG_BOX( "GK服务器地址非法", FALSE, &msgArg );
		msgArg.pOwnerWnd->SetFocus();
		return false;
	} 

    if ( ( bUseGk != (bool)tOldGkCfg.bUsed ) || htonl( valIp.dwIP ) != tOldGkCfg.dwGKIP )
	{    
        Args_MsgBox msgArg;    
        BOOL bInConf = BusinessManagePtr->IsInConf();
        if ( bInConf )
        {		
            msgArg.pOwnerWnd = m_pWndTree->GetItemData()->pWnd;
            MSG_BOX( "会议中，不能修改GK服务器地址", FALSE, &msgArg );
			msgArg.pOwnerWnd->SetFocus();
            return false;
	    }

		TTPGKCfg tSipcfg; 
		tSipcfg.wExpire = 40; 
		tSipcfg.bUsed = bUseGk;
		tSipcfg.dwGKIP = htonl(valIp.dwIP);  

        u16 wRet  = ComInterface->CnsRegGkService( tSipcfg );
        if ( wRet != NO_ERROR )
        {
            HANDLE_ERROR(wRet);
        }		 
	}

	UIManagePtr->LoadScheme( "SchmNormal", m_pWndTree);
	return true;
}

bool CRegGkLogic::OnCancel( const IArgs& args )
{
	UpdateGkCfg( 0, 0 );
		
	UIManagePtr->LoadScheme( "SchmNormal", m_pWndTree);
	return true;
}


bool CRegGkLogic::OnEdit( const IArgs& args )
{	
	Args_MsgBox msgArg;
	msgArg.pOwnerWnd = m_pWndTree->GetItemData()->pWnd;

	TTPCnsConfStatus tConfStatus = BusinessManagePtr->GetLocalCnsConfState();
	if ( tConfStatus.emState == em_CALL_CONNECTED )
	{
		MSG_BOX( "会议中，不能修改GK地址", FALSE, &msgArg );
		return false;
	}

	BOOL bInConf = BusinessManagePtr->IsInConf();
	if ( bInConf )
	{		
		MSG_BOX( "会议中，不能修改GK地址", FALSE, &msgArg );
		return false;
	}

	UIManagePtr->LoadScheme( "SchmEdit", m_pWndTree);

	IArgs Args("");
    BtnSwitchGkClick( Args );
    UpdateGkCfg( 0 , 0 );

	return true;
}


bool CRegGkLogic::BtnSwitchGkClick( const IArgs& args )
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

LRESULT CRegGkLogic::UpdateGkCfg( WPARAM wParam, LPARAM lParam )
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
 
/*
//CNS注册UMS失败类型
enum EmTpCnsRegUms
{
    tp_CnsRegRet_Unknow,
        tp_CnsRegRet_Success,		//成功
        tp_CnsRegRet_MaxRegNum,		//注册满
        tp_CnsRegRet_MaxAliasNum,	//注册满
        tp_CnsRegRet_MsgError,		//注册消息错误
        tp_CnsRegRet_AliasRepeat,	//别名重复
        tp_CnsRegRet_UnReg,			//删除时，未找到删除记录
        tp_CnsRegRet_SysError,		//APP错误
        tp_CnsRegRet_NotFind,		//查找失败
        tp_CnsRegRet_Fail,          //其他失败
        tp_CnsRegRet_Unreachable,   //服务器不可达
};*/
LRESULT CRegGkLogic::OnRegRsp( WPARAM wParam, LPARAM lParam )
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
    case tp_CnsRegRet_Success:		//成功
        bOk  = true;
        break;
    case tp_CnsRegRet_MaxRegNum:    //注册满
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
    case tp_CnsRegRet_Unreachable:  //服务器不可达
        strTemp = "服务器不可达";
        break;
    case tp_CnsRegRet_E164Repeat:   //E164号重复
        strTemp = "E164号重复";
        break;
	case tp_CnsRegRet_NameDup:
	    strTemp = "别名或E164号码重复";
		break;
    default:
		strTemp = "";//2012-8-7 SE石文娟确认未知错误不做提示 by yjj
		break;
    }
	
	CString strName = "注册GK失败";
 	 
	if ( bOk )
	{
		ShowPopMsg( "注册GK成功" );
	}
	else
	{
        //别名重复时需要详细提示
        /*
        if ( tRegResult.m_emTpCnsRegUms == tp_CnsRegRet_AliasRepeat )
        {           
            u32 dwSize = tRegResult.m_nAliasNum;
            if ( 1 == dwSize )
            {
                TTPAlias tRegAlias = tRegResult.m_atTPAlias[0];
                if ( tRegAlias.m_byType == tp_Alias_h323  )
                {
                    strTemp = "会场名称重复";
                }
                else if ( tRegAlias.m_byType == tp_Alias_e164 )
                {
                    strTemp = "会场号码重复";
                }
            }
            else if ( 2 == dwSize )
            {
                strTemp = "会场名称和会场号码都重复";
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


bool CRegGkLogic::OnSysCfg( const IArgs& args )
{
    if ( ! UIManagePtr->IsVisible( "RegGkDlg/BtnEdit" ) )
    {
        TTPGKCfg tOldGkCfg;
        ComInterface->GetGkCfg( tOldGkCfg );
		in_addr tAddr;
		tAddr.S_un.S_addr = tOldGkCfg.dwGKIP;
		String strOldInfo = inet_ntoa(tAddr);
		if ( "0.0.0.0" == strOldInfo )
		{
			strOldInfo = "";
		}
 		
		String strCaption;
		UIFACTORYMGR_PTR->GetCaption( m_strGkIP, strCaption, m_pWndTree);
		DWORD dwIP = inet_addr(strCaption.c_str());
		if ( "" == strCaption )
		{
			dwIP = 0;
		}

        bool bUseGk = false;
        UIManagePtr->GetSwitchState( m_stBtnGkSwitch, bUseGk, m_pWndTree );
        
        Value_IpEditData valIp;
        UIManagePtr->GetPropertyValue(valIp, m_strGkIP, m_pWndTree); 
        
        TTPGKCfg tSipcfg; 
        tSipcfg.wExpire = 40; 
        tSipcfg.bUsed = bUseGk;
        tSipcfg.dwGKIP = htonl(valIp.dwIP);  
        
        if ( ( bUseGk != (bool)tOldGkCfg.bUsed ) || ( tSipcfg.dwGKIP != tOldGkCfg.dwGKIP ) || strCaption != strOldInfo )
        {
            CString strMsg = "是否对编辑进行保存?";
            Args_MsgBox argMsg;
            argMsg.pOwnerWnd = UIManagePtr->GetWindowPtr( "RegGkDlg" );
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

bool CRegGkLogic::OnCloseDlg( const IArgs& args )
{
	return UIManagePtr->ShowWindow( "RegServiceDlg", false );
}