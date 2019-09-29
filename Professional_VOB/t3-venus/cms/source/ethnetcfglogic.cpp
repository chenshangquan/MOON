// ethnetcfglogic.cpp: implementation of the CEthnetCfgLogic class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ethnetcfglogic.h"
#include "msgBoxLogic.h"

CEthnetCfgLogic * CEthnetCfgLogic::m_pCfgLogic = NULL;

const String CEthnetCfgLogic::m_strEdtIp = "IPCtrlAddress" ;
const String CEthnetCfgLogic::m_strEdtSubMask = "IPCtrlSubMask";
const String CEthnetCfgLogic::m_strEdtGateWay = "IPCtrlGateway";
const String CEthnetCfgLogic::m_strBtnNATSwitch = "BtnNATSwitch";
const String CEthnetCfgLogic::m_strEdtNatIP = "IPCtrlNATIp";

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CEthnetCfgLogic::CEthnetCfgLogic()
{

}

CEthnetCfgLogic::~CEthnetCfgLogic()
{
	if ( m_pCfgLogic != NULL )
	{   
		UnRegMsg();
		UnRegFunc();
		delete m_pCfgLogic;
		m_pCfgLogic = NULL;
	}
}

CEthnetCfgLogic* CEthnetCfgLogic::GetLogicPtr()
{
	if ( m_pCfgLogic == NULL )
	{  
		m_pCfgLogic = new CEthnetCfgLogic();  
	}
	
	return m_pCfgLogic;
}

bool CEthnetCfgLogic::RegCBFun()
{
	REG_GOBAL_MEMBER_FUNC( "CEthnetCfgLogic::InitWnd", CEthnetCfgLogic::InitWnd, m_pCfgLogic, CEthnetCfgLogic );
	REG_GOBAL_MEMBER_FUNC( "CEthnetCfgLogic::OnSave", CEthnetCfgLogic::OnSave, m_pCfgLogic, CEthnetCfgLogic );
	REG_GOBAL_MEMBER_FUNC( "CEthnetCfgLogic::OnCancel", CEthnetCfgLogic::OnCancel, m_pCfgLogic, CEthnetCfgLogic );
	REG_GOBAL_MEMBER_FUNC( "CEthnetCfgLogic::OnEdit", CEthnetCfgLogic::OnEdit, m_pCfgLogic, CEthnetCfgLogic );
	REG_GOBAL_MEMBER_FUNC( "CEthnetCfgLogic::OnSysCfg", CEthnetCfgLogic::OnSysCfg, m_pCfgLogic, CEthnetCfgLogic );
	REG_GOBAL_MEMBER_FUNC( "CEthnetCfgLogic::OnCloseDlg", CEthnetCfgLogic::OnCloseDlg, m_pCfgLogic, CEthnetCfgLogic );
	REG_GOBAL_MEMBER_FUNC( "CEthnetCfgLogic::BtnSwitchNATClick", CEthnetCfgLogic::BtnSwitchNATClick, m_pCfgLogic, CEthnetCfgLogic );
	return true;
}

bool CEthnetCfgLogic::UnRegFunc()
{
	
	return true;
}

void CEthnetCfgLogic::RegMsg()
{
	REG_MSG_HANDLER( UI_CNS_ETHNETINFO_NOTIFY, CEthnetCfgLogic::UpdateEthnetInfo, m_pCfgLogic, CEthnetCfgLogic );
    REG_MSG_HANDLER( UI_UMS_ETHNETINFO_NOTIFY, CEthnetCfgLogic::UpdateEthnetInfo, m_pCfgLogic, CEthnetCfgLogic );
	REG_MSG_HANDLER( UI_CNS_REG_NAT_NTY, CEthnetCfgLogic::UpdateNatInfo, m_pCfgLogic, CEthnetCfgLogic ); 

}

void CEthnetCfgLogic::Clear()
{
	if ( m_pWndTree != NULL )
	{
		UpdateEthnetInfo( 0 ,0 );		
		UIManagePtr->LoadScheme( "SchmNormal", m_pWndTree );
	}
}


bool CEthnetCfgLogic::InitWnd( const IArgs & args )
{
	CWndLogicBase::InitWnd( args );
	
	UpdateEthnetInfo( 0 ,0 );
	UpdateNatInfo( 0 , 0 );	
	return true;
}

bool CEthnetCfgLogic::OnSave( const IArgs& args )
{
	Value_IpEditData valIp;
    UIManagePtr->GetPropertyValue(valIp, m_strEdtIp, m_pWndTree); 
	
	Value_IpEditData valSubMask;
    UIManagePtr->GetPropertyValue(valSubMask, m_strEdtSubMask, m_pWndTree); 

	Value_IpEditData valGateway;
    UIManagePtr->GetPropertyValue(valGateway, m_strEdtGateWay, m_pWndTree); 

	TTPEthnetInfo tOldEthnetInfo;
	ComInterface->GetEthnetCfg( tOldEthnetInfo );	

	//添加关于NAT的设置
	bool bUseNAT = false;
    UIManagePtr->GetSwitchState( m_strBtnNATSwitch, bUseNAT, m_pWndTree );

	Value_IpEditData valNatIp;
	UIManagePtr->GetPropertyValue(valNatIp, m_strEdtNatIP, m_pWndTree); 
	
	TTPNatCfg tOldNatInfo;
	ComInterface->GetNATCfg(tOldNatInfo);
	
	//校验NATIP
	String strNatIp;
	UIFACTORYMGR_PTR->GetCaption( m_strEdtNatIP, strNatIp, m_pWndTree );

	String strOldNatIp;
	in_addr tAddr;
	tAddr.S_un.S_addr = tOldNatInfo.dwNatIP;	
	if ( 0 != tOldNatInfo.dwNatIP )
	{
		strOldNatIp = inet_ntoa(tAddr);
	}
	else
	{
		strOldNatIp = "";
	}

// 	if ( htonl( valIp.dwIP ) != tOldEthnetInfo.dwIP || htonl( valSubMask.dwIP ) != tOldEthnetInfo.dwMask
// 		|| htonl( valGateway.dwIP ) != tOldEthnetInfo.dwGateWay || strNatIp != strOldNatIp || (BOOL)bUseNAT != tOldNatInfo.bUsed )
// 	{	
	if ( CheckAllIp() )
	{
		Args_MsgBox msgArg;
		BOOL bInConf = BusinessManagePtr->IsInConf();
        if ( bInConf )
        {	
			msgArg.pOwnerWnd = m_pWndTree->GetItemData()->pWnd;
            MSG_BOX( "会议中，不能修改服务器设置", FALSE , &msgArg );
            return false;
		}
        
		//效验IP
		String strCaption;
		UIManagePtr->GetCaption( m_strEdtIp, strCaption, m_pWndTree );
		if ( strCaption.empty() )
		{  
			msgArg.pOwnerWnd = UIManagePtr->GetWindowPtr( m_strEdtIp, m_pWndTree );
			MSG_BOX( "CNS IP地址不能为空", FALSE, &msgArg );
			msgArg.pOwnerWnd->SetFocus();
			return false;
		}
		if ( !CCallAddr::IsValidIpV4( valIp.dwIP ) )
        {		
            msgArg.pOwnerWnd = UIManagePtr->GetWindowPtr( m_strEdtIp, m_pWndTree );
            MSG_BOX( "CNS IP地址非法", FALSE, &msgArg );
            msgArg.pOwnerWnd->SetFocus();
			return false;
		}
		CString cstrErrStr;
		if ( !CCallAddr::IsValidCallIP( valIp.dwIP, cstrErrStr, 0 ) ) 
		{
			msgArg.pOwnerWnd = UIManagePtr->GetWindowPtr( m_strEdtIp, m_pWndTree );
			MSG_BOX( cstrErrStr, FALSE, &msgArg );
			msgArg.pOwnerWnd->SetFocus();
			return false;
		}

		//效验子网掩码
		UIManagePtr->GetCaption( m_strEdtSubMask, strCaption, m_pWndTree );
		if ( strCaption.empty() )
		{  
			msgArg.pOwnerWnd = UIManagePtr->GetWindowPtr( m_strEdtSubMask, m_pWndTree );
			MSG_BOX( "子网掩码不能为空", FALSE, &msgArg );
			msgArg.pOwnerWnd->SetFocus();
			return false;
		}

		if ( !CCallAddr::IsValidIpMask(valSubMask.dwIP) )
		{
			msgArg.pOwnerWnd = UIManagePtr->GetWindowPtr( m_strEdtSubMask, m_pWndTree );
			MSG_BOX( "子网掩码无效。子网掩码必须是相邻的，请输入有效的掩码", FALSE, &msgArg );
			msgArg.pOwnerWnd->SetFocus();
			return false;
		}

		if ( !CCallAddr::IsValidDevIP( valIp.dwIP, valSubMask.dwIP, cstrErrStr, 0 ) )
		{
			msgArg.pOwnerWnd = UIManagePtr->GetWindowPtr( m_strEdtIp, m_pWndTree );
			MSG_BOX( cstrErrStr, FALSE, &msgArg );
			msgArg.pOwnerWnd->SetFocus();
			return false;
		}
		
		//效验网关
		UIManagePtr->GetCaption( m_strEdtGateWay, strCaption, m_pWndTree );
		if ( !strCaption.empty() && !CCallAddr::IsValidIpV4( valGateway.dwIP ) )
		{
			msgArg.pOwnerWnd = UIManagePtr->GetWindowPtr( m_strEdtGateWay, m_pWndTree );
			MSG_BOX( "网关IP地址非法", FALSE, &msgArg );
			msgArg.pOwnerWnd->SetFocus();
			return false;
		}

		if ( !strCaption.empty() )
		{
			DWORD dwNetID = valIp.dwIP & valSubMask.dwIP;
			DWORD dwNetGate = valGateway.dwIP & valSubMask.dwIP;
			if ( dwNetGate != dwNetID )
			{
				msgArg.pOwnerWnd = UIManagePtr->GetWindowPtr( m_strEdtGateWay, m_pWndTree );
				MSG_BOX( "网关不在由IP地址和子网掩码定义的同一网络段上", FALSE, &msgArg );
				msgArg.pOwnerWnd->SetFocus();
				return false; 
			}
		}

 		if ( strNatIp != strOldNatIp || bUseNAT != (bool)tOldNatInfo.bUsed )
 		{	
			if ( !CCallAddr::IsValidCallIP( valNatIp.dwIP ) && !strNatIp.empty() ) 
			{
				msgArg.pOwnerWnd = UIManagePtr->GetWindowPtr( m_strEdtNatIP, m_pWndTree );
				MSG_BOX( "NAT地址非法", FALSE, &msgArg );
				msgArg.pOwnerWnd->SetFocus();
				return false;
			}

 			TTPNatCfg tNatInfo;
			tNatInfo.bUsed = bUseNAT;
			tNatInfo.dwNatIP = htonl(valNatIp.dwIP);
				
			u16 wRet = ComInterface->UpdateNATCfg(tNatInfo);
		}

		if ( htonl( valIp.dwIP ) != tOldEthnetInfo.dwIP || htonl( valSubMask.dwIP ) != tOldEthnetInfo.dwMask
			|| htonl( valGateway.dwIP ) != tOldEthnetInfo.dwGateWay )
		{
			Args_MsgBox msgarg;
			msgarg.pOwnerWnd = m_pWndTree->GetItemData()->pWnd;
			int nReslut = MSG_BOX( "修改IP地址将断开连接，请确认是否修改", TRUE, &msgarg ); //dyy 2013年9月2日 Bug00154718
            if ( IDOK == nReslut )
			{
				IArgs arg("");
				SaveEthnetCfg( arg );
                UIManagePtr->LoadScheme( "SchmNormal", m_pWndTree );
			}  
            else
            {
                UpdateEthnetInfo( 0, 0 );
                UpdateNatInfo( 0, 0 );
                UIManagePtr->LoadScheme( "SchmNormal", m_pWndTree );
            }
		}
        else
        {
            UIManagePtr->LoadScheme( "SchmNormal", m_pWndTree );
        }
	}
    else
    {
		UpdateEthnetInfo( 0, 0 );
		UpdateNatInfo( 0, 0 );
        UIManagePtr->LoadScheme( "SchmNormal", m_pWndTree );
    } 
	
	return true;
}

bool CEthnetCfgLogic::SaveEthnetCfg( const IArgs& args )
{
	Value_IpEditData valIp;
    UIManagePtr->GetPropertyValue(valIp, m_strEdtIp, m_pWndTree); 
	
	Value_IpEditData valSubMask;
    UIManagePtr->GetPropertyValue(valSubMask, m_strEdtSubMask, m_pWndTree); 

	Value_IpEditData valGateway;
    UIManagePtr->GetPropertyValue(valGateway, m_strEdtGateWay, m_pWndTree); 


	TTPEthnetInfo tEthnetInfo;
	tEthnetInfo.bEnable = TRUE;
	tEthnetInfo.dwIP = htonl( valIp.dwIP );
	tEthnetInfo.dwMask = htonl( valSubMask.dwIP );
	tEthnetInfo.dwGateWay = htonl( valGateway.dwIP );
	  
	u16 wRet = ComInterface->UpdateEthnetCfg( tEthnetInfo );
	
	return true;
}


bool CEthnetCfgLogic::OnCancel( const IArgs& args )
{
	UpdateEthnetInfo( 0 ,0 );
	UpdateNatInfo( 0 , 0 );
	UIManagePtr->LoadScheme( "SchmNormal", m_pWndTree );
	return true;
}


bool CEthnetCfgLogic::OnEdit( const IArgs& args )
{	
	BOOL bInConf = BusinessManagePtr->IsInConf();
	if ( bInConf )
	{	
		Args_MsgBox msgArg;
		msgArg.pOwnerWnd = m_pWndTree->GetItemData()->pWnd;
		MSG_BOX( "会议中，不能修改服务器设置", FALSE, &msgArg );
		return false;
	}
        

	UIManagePtr->LoadScheme( "SchmEdit", m_pWndTree );
	IArgs* pArg = NULL;
    BtnSwitchNATClick( *pArg );
	return true;
}

bool CEthnetCfgLogic::OnSysCfg( const IArgs& args )
{
    if ( ! UIManagePtr->IsVisible( "EthnetCfgDlg/BtnEdit" ) )
    {
// 	    Value_IpEditData valIp;
//         UIManagePtr->GetPropertyValue(valIp, m_strEdtIp, m_pWndTree); 
// 	    
// 	    Value_IpEditData valSubMask;
//         UIManagePtr->GetPropertyValue(valSubMask, m_strEdtSubMask, m_pWndTree); 
//     
//         Value_IpEditData valGateway;
//         UIManagePtr->GetPropertyValue(valGateway, m_strEdtGateWay, m_pWndTree); 
//     
//         TTPEthnetInfo tOldEthnetInfo;
//         ComInterface->GetEthnetCfg( tOldEthnetInfo );	
//     
//         bool bUseNAT = false;
//         UIManagePtr->GetSwitchState( m_strBtnNATSwitch, bUseNAT, m_pWndTree );
//     
//         Value_IpEditData valNatIp;
//         UIManagePtr->GetPropertyValue(valNatIp, m_strEdtNatIP, m_pWndTree); 
//     
//         TTPNatCfg tOldNatInfo;
//         ComInterface->GetNATCfg(tOldNatInfo);
    
//         if ( htonl( valIp.dwIP ) != tOldEthnetInfo.dwIP || htonl( valSubMask.dwIP ) != tOldEthnetInfo.dwMask
//             || htonl( valGateway.dwIP ) != tOldEthnetInfo.dwGateWay || htonl(valNatIp.dwIP) != tOldNatInfo.dwNatIP 
//             || (BOOL)bUseNAT != tOldNatInfo.bUsed)
		if ( CheckAllIp() )
        {
            CString strMsg = "是否对编辑进行保存?";
            Args_MsgBox argMsg;
            argMsg.pOwnerWnd = UIManagePtr->GetWindowPtr( "EthnetCfgDlg" );
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

bool CEthnetCfgLogic::OnCloseDlg( const IArgs& args )
{
	return UIManagePtr->ShowWindow( "EthnetCfgDlg", false );
}

LRESULT CEthnetCfgLogic::UpdateEthnetInfo( WPARAM wParam, LPARAM lParam )
{
	if ( m_pWndTree == NULL )
	{
		return NO_ERROR;
	}
	
	TTPEthnetInfo tEthnetInfo;
	ComInterface->GetEthnetCfg( tEthnetInfo );

	Value_IpEditData valIp;
	valIp.dwIP = ntohl(tEthnetInfo.dwIP);
    UIManagePtr->SetPropertyValue( valIp, m_strEdtIp, m_pWndTree ); 
	
	valIp.dwIP = ntohl(tEthnetInfo.dwMask);
    UIManagePtr->SetPropertyValue( valIp, m_strEdtSubMask, m_pWndTree ); 
	
	valIp.dwIP = ntohl(tEthnetInfo.dwGateWay);
    UIManagePtr->SetPropertyValue( valIp, m_strEdtGateWay, m_pWndTree ); 

    //UIManagePtr->UpdateUI( "", m_pWndTree );
	
	return NO_ERROR;
}

bool CEthnetCfgLogic::BtnSwitchNATClick( const IArgs& args )
{
    bool bUseNAT = false;
    UIManagePtr->GetSwitchState( m_strBtnNATSwitch, bUseNAT, m_pWndTree );
    if ( bUseNAT )
    {
        UIManagePtr->EnableWindow( m_strEdtNatIP, true, m_pWndTree );
    }
    else
    {   
        UIManagePtr->EnableWindow( m_strEdtNatIP, false, m_pWndTree );
    }
    return true;
}

LRESULT CEthnetCfgLogic::UpdateNatInfo( WPARAM wParam, LPARAM lParam )
{
	if ( m_pWndTree == NULL )
	{
		return NO_ERROR;
	}
	
	TTPNatCfg tNatInfo;
	ComInterface->GetNATCfg( tNatInfo );

	Value_IpEditData valIp;
	valIp.dwIP = ntohl(tNatInfo.dwNatIP);
	UIManagePtr->SetPropertyValue( valIp, m_strEdtNatIP, m_pWndTree ); 

	UIManagePtr->SetSwitchState( m_strBtnNATSwitch, tNatInfo.bUsed, m_pWndTree );
	
	return NO_ERROR;
}

BOOL CEthnetCfgLogic::CheckAllIp()
{
	BOOL bChange = FALSE;

	TTPEthnetInfo tOldEthnetInfo;
	ComInterface->GetEthnetCfg( tOldEthnetInfo );	

	String strCnsIp;
	UIFACTORYMGR_PTR->GetCaption( m_strEdtIp, strCnsIp, m_pWndTree );
	
	String strOldCnsIp;
	in_addr tAddr1;
	tAddr1.S_un.S_addr = tOldEthnetInfo.dwIP;	
	if ( 0 != tOldEthnetInfo.dwIP )
	{
		strOldCnsIp = inet_ntoa(tAddr1);
	}
	else
	{
		strOldCnsIp = "";
	}
	
	String strSubMask;
	UIFACTORYMGR_PTR->GetCaption( m_strEdtSubMask, strSubMask, m_pWndTree );
	
	String strOldSubMask;
	in_addr tAddr2;
	tAddr2.S_un.S_addr = tOldEthnetInfo.dwMask;	
	if ( 0 != tOldEthnetInfo.dwMask )
	{
		strOldSubMask = inet_ntoa(tAddr2);
	}
	else
	{
		strOldSubMask = "";
	}
	
	String strGateway;
	UIFACTORYMGR_PTR->GetCaption( m_strEdtGateWay, strGateway, m_pWndTree );
	
	String strOldGateway;
	in_addr tAddr3;
	tAddr3.S_un.S_addr = tOldEthnetInfo.dwGateWay;	
	if ( 0 != tOldEthnetInfo.dwGateWay )
	{
		strOldGateway = inet_ntoa(tAddr3);
	}
	else
	{
		strOldGateway = "";
	}

	TTPNatCfg tOldNatInfo;
	ComInterface->GetNATCfg(tOldNatInfo);

	bool bUseNAT = false;
    UIManagePtr->GetSwitchState( m_strBtnNATSwitch, bUseNAT, m_pWndTree );
	
	//校验NATIP
	String strNatIp;
	UIFACTORYMGR_PTR->GetCaption( m_strEdtNatIP, strNatIp, m_pWndTree );
	
	String strOldNatIp;
	in_addr tAddr;
	tAddr.S_un.S_addr = tOldNatInfo.dwNatIP;	
	if ( 0 != tOldNatInfo.dwNatIP )
	{
		strOldNatIp = inet_ntoa(tAddr);
	}
	else
	{
		strOldNatIp = "";
	}

	if ( strCnsIp != strOldCnsIp || strSubMask != strOldSubMask || strGateway != strOldGateway || strNatIp != strOldNatIp || (BOOL)bUseNAT != tOldNatInfo.bUsed )
	{
		bChange = TRUE;
	}

	return bChange;
}
