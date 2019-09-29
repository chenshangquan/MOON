// cnscfglogic.cpp: implementation of the CCnsCfgLogic class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "cnscfglogic.h"
#include "msgBoxLogic.h"

CCnsCfgLogic* CCnsCfgLogic::m_pLogic = NULL;

const String CCnsCfgLogic::m_strCnsLst = "CnsList";              //cns 列表
const String CCnsCfgLogic::m_strDlgCnsConfig = "DlgCnsConfig";   //会场设置界面
const String CCnsCfgLogic::m_strBtnMainCns = "DlgCnsConfig/BtnSetMainCns";
const String CCnsCfgLogic::m_strEdtCnsName = "DlgCnsConfig/EdtCnsName";
const String CCnsCfgLogic::m_strEdtCnsNumber = "DlgCnsConfig/EdtCnsNumber";
const String CCnsCfgLogic::m_strBtnCnsCfgSwitch = "DlgCnsConfig/BtnCnsCfgSwitch";
const String CCnsCfgLogic::m_strRadioProvince = "DlgCnsConfig/RadioCnsLevel1";
const String CCnsCfgLogic::m_strRadioCity = "DlgCnsConfig/RadioCnsLevel2";
const String CCnsCfgLogic::m_strRadioCounty = "DlgCnsConfig/RadioCnsLevel3";
const String CCnsCfgLogic::m_strStDualIp = "DlgCnsConfig/StDualIP";
const String CCnsCfgLogic::m_strBtnNATSwitch = "DlgCnsConfig/BtnNATSwitch";
const String CCnsCfgLogic::m_strEdtNatIP = "DlgCnsConfig/IPCtrlNATIp";
const String CCnsCfgLogic::m_strEdtIp = "DlgCnsConfig/IPCtrlAddress" ;
const String CCnsCfgLogic::m_strEdtSubMask = "DlgCnsConfig/IPCtrlSubMask";
const String CCnsCfgLogic::m_strEdtGateWay = "DlgCnsConfig/IPCtrlGateway";
TCnsScreenIp CCnsCfgLogic::m_tCtrlScreenIp[MAX_CNS_SCREEN]; 

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CCnsCfgLogic::CCnsCfgLogic()
{
	CString strEdit;
	for ( int i = 0; i < MAX_CNS_SCREEN; i++ )
	{	
		strEdit.Format( "StCnsScreen%d", i+1 );
		m_tCtrlScreenIp[i].strCnsScreen = m_strDlgCnsConfig + "/" + (LPCTSTR)strEdit;

		strEdit.Format( "StScreenIP%d", i+1 );
		m_tCtrlScreenIp[i].strScreenIP = m_strDlgCnsConfig + "/" + (LPCTSTR)strEdit;

		strEdit.Format( "StScreen%d", i+1 );
		m_tCtrlScreenIp[i].strScreenPic = m_strDlgCnsConfig + "/" + (LPCTSTR)strEdit;
	}
	memset( m_achMainCns, 0, sizeof(m_achMainCns) );

}

CCnsCfgLogic::~CCnsCfgLogic()
{
	if ( m_pLogic != NULL )
	{   
		UnRegMsg();
		UnRegFunc();
		delete m_pLogic;
		m_pLogic = NULL;
	}
}

bool CCnsCfgLogic::RegCBFun()
{
	REG_DEFAULT_WINDOW_MSG( WM_CNC_FTPCONFSIGNPROGRESS );
	REG_GOBAL_MEMBER_FUNC( "CCnsCfgLogic::OnUploadProgress", CCnsCfgLogic::OnUploadProgress, m_pLogic, CCnsCfgLogic );
	REG_GOBAL_MEMBER_FUNC( "CCnsCfgLogic::InitWnd", CCnsCfgLogic::InitWnd, m_pLogic, CCnsCfgLogic );
	REG_GOBAL_MEMBER_FUNC( "CCnsCfgLogic::OnSave", CCnsCfgLogic::OnSave, m_pLogic, CCnsCfgLogic );
	REG_GOBAL_MEMBER_FUNC( "CCnsCfgLogic::OnCancel", CCnsCfgLogic::OnCancel, m_pLogic, CCnsCfgLogic );
	REG_GOBAL_MEMBER_FUNC( "CCnsCfgLogic::OnEdit", CCnsCfgLogic::OnEdit, m_pLogic, CCnsCfgLogic );
	REG_GOBAL_MEMBER_FUNC( "CCnsCfgLogic::OnSysCfg", CCnsCfgLogic::OnSysCfg, m_pLogic, CCnsCfgLogic );
	REG_GOBAL_MEMBER_FUNC( "CCnsCfgLogic::OnCfgCnsList", CCnsCfgLogic::OnCfgCnsList, m_pLogic, CCnsCfgLogic );

	REG_GOBAL_MEMBER_FUNC( "CCnsCfgLogic::OnSetMainCns", CCnsCfgLogic::OnSetMainCns, m_pLogic, CCnsCfgLogic );
	REG_GOBAL_MEMBER_FUNC( "CCnsCfgLogic::BtnSwitchCnsCfgClick",CCnsCfgLogic::BtnSwitchCnsCfgClick,m_pLogic,CCnsCfgLogic );
	
	REG_GOBAL_MEMBER_FUNC( "CCnsCfgLogic::OnBtnCnsLevel1", CCnsCfgLogic::OnBtnCnsLevel1, m_pLogic, CCnsCfgLogic );
	REG_GOBAL_MEMBER_FUNC( "CCnsCfgLogic::OnBtnCnsLevel2", CCnsCfgLogic::OnBtnCnsLevel2, m_pLogic, CCnsCfgLogic );
	REG_GOBAL_MEMBER_FUNC( "CCnsCfgLogic::OnBtnCnsLevel3", CCnsCfgLogic::OnBtnCnsLevel3, m_pLogic, CCnsCfgLogic );
	
	REG_GOBAL_MEMBER_FUNC( "CCnsCfgLogic::OnOpenCnsInfo", CCnsCfgLogic::OnOpenCnsInfo, m_pLogic, CCnsCfgLogic );
    REG_GOBAL_MEMBER_FUNC( "CCnsCfgLogic::OnCnsLstItem", CCnsCfgLogic::OnCnsLstItem, m_pLogic, CCnsCfgLogic );
	REG_GOBAL_MEMBER_FUNC( "CCnsCfgLogic::BtnSwitchNATClick", CCnsCfgLogic::BtnSwitchNATClick, m_pLogic, CCnsCfgLogic );

	REG_GOBAL_MEMBER_FUNC( "CCnsCfgLogic::OnCloseDlg", CCnsCfgLogic::OnCloseDlg, m_pLogic, CCnsCfgLogic );	
	return true;
}

bool CCnsCfgLogic::UnRegFunc()
{
	
	return true;
}

void CCnsCfgLogic::RegMsg()
{
	REG_MSG_HANDLER( UI_CNS_MAINROOM_NOTIFY, CCnsCfgLogic::OnMainRoomNotify, m_pLogic, CCnsCfgLogic );
	REG_MSG_HANDLER( UI_CNS_CNSINFO_NOTIFY, CCnsCfgLogic::OnCnsInfoNotify, m_pLogic, CCnsCfgLogic );
	REG_MSG_HANDLER( UI_CNS_ETHNETINFO_NOTIFY, CCnsCfgLogic::UpdateEthnetInfo, m_pLogic, CCnsCfgLogic );
    REG_MSG_HANDLER( UI_UMS_ETHNETINFO_NOTIFY, CCnsCfgLogic::UpdateEthnetInfo, m_pLogic, CCnsCfgLogic );
	REG_MSG_HANDLER( UI_CNS_REG_NAT_NTY, CCnsCfgLogic::UpdateNatInfo, m_pLogic, CCnsCfgLogic ); 
}

CCnsCfgLogic* CCnsCfgLogic::GetLogicPtr()
{
	if ( m_pLogic == NULL )
	{  
		m_pLogic = new CCnsCfgLogic();  
	}
	
	return m_pLogic;
}


bool CCnsCfgLogic::InitWnd( const IArgs & args )
{
	CWndLogicBase::InitWnd( args );
	
	ComInterface->GetLocalCnsInfo( m_SelCnsInfo );
	ShowCnsInfo();
	UpdateEthnetInfo( 0 ,0 );
	UpdateNatInfo( 0 , 0 );
	/*
	ComInterface->GetLocalCnsList( m_vctCnsList );

	ARRAY<String> vctItem;
	vctItem.push_back( "ImageItemOpenCns" );
	Value_TouchListCnsList touchListCns( &m_vctCnsList, "CCnsCfgLogic::OnCnsLstItem", &vctItem );
	UIManagePtr->SetPropertyValue( touchListCns , "CnsList", m_pWndTree );
	*/
	
	m_pWnd = UIFACTORYMGR_PTR->GetWindowPtr( "SysCfgDlg" );
	
	if ( NULL != m_pWnd )
	{
		return false;
	}
	
	return true;
}


bool CCnsCfgLogic::OnOpenCnsInfo( const IArgs & args )
{
	if ( const Args_ClickItemInfo* pClickInfo = dynamic_cast<const Args_ClickItemInfo*>(&args) )
	{
		IBaseItem* pBaseItem = pClickInfo->m_pClickList->GetParentItem()->GetItemData();
		if ( pBaseItem != NULL )
		{
			Data_TPCnsInfo CnsInfo = *dynamic_cast<const Data_TPCnsInfo*>( pBaseItem->GetUserData() );
			m_SelCnsInfo = *(CnsInfo.m_pCnsInfo);
			
			ShowCnsInfo();
			UIManagePtr->LoadScheme( "SchmNormal", m_pWndTree, "", false );
			UIManagePtr->LoadScheme( "SchmConfig", m_pWndTree );			
		}
	}
	return true;
}


bool CCnsCfgLogic::OnCnsLstItem( const IArgs & args )
{
    if ( const Args_ClickItemInfo* pClickInfo = dynamic_cast<const Args_ClickItemInfo*>(&args) )
    {
        IBaseItem* pBaseItem = pClickInfo->m_pClickList->GetItemData();
        if ( pBaseItem != NULL )
        {
            Data_TPCnsInfo CnsInfo = *dynamic_cast<const Data_TPCnsInfo*>( pBaseItem->GetUserData() );
            m_SelCnsInfo = *(CnsInfo.m_pCnsInfo);
            
            ShowCnsInfo();
            UIManagePtr->LoadScheme( "SchmNormal", m_pWndTree, "", false );
            UIManagePtr->LoadScheme( "SchmConfig", m_pWndTree );			
        }
    }
    return true;
}

void CCnsCfgLogic::ShowCnsInfo()
{
	/*
	strcpy( m_achMainCns, ComInterface->GetMainCnsName() );
	if ( strcmp( m_achMainCns, m_SelCnsInfo.m_achRoomName ) == 0 )
	{
		UIManagePtr->SetSwitchState( m_strBtnMainCns, true, m_pWndTree );
	}
	else
	{
		UIManagePtr->SetSwitchState( m_strBtnMainCns, false, m_pWndTree );
	}
	
	UIManagePtr->SetCaption( "StTitle", m_SelCnsInfo.m_achRoomName, m_pWndTree );
	*/
	UIManagePtr->SetSwitchState( m_strBtnCnsCfgSwitch, m_SelCnsInfo.m_bIsShowRoomName, m_pWndTree );
	UIManagePtr->SetCaption( m_strEdtCnsName, m_SelCnsInfo.m_achRoomName, m_pWndTree );
	UIManagePtr->SetCaption( m_strEdtCnsNumber, m_SelCnsInfo.m_achE164, m_pWndTree );

	m_emLevel = m_SelCnsInfo.m_emLevel;
 	UIManagePtr->SetCheckState( m_strRadioProvince, m_emLevel == emTPSipProvince, m_pWndTree );
 	UIManagePtr->SetCheckState( m_strRadioCity, m_emLevel == emTPSipCity, m_pWndTree );
 	UIManagePtr->SetCheckState( m_strRadioCounty, m_emLevel == emTPSipCounty, m_pWndTree );

	UpdateCnsLevel( m_emLevel );

	u8 byDualPos = m_SelCnsInfo.m_byDualPos;
	if ( byDualPos != 0xff && byDualPos < MAX_CNS_SCREEN )
	{
		in_addr tAddr;
		tAddr.S_un.S_addr = m_SelCnsInfo.m_adwIP[byDualPos];
		String strDualIp;
		strDualIp = inet_ntoa(tAddr);
		UIManagePtr->SetCaption( m_strStDualIp, strDualIp, m_pWndTree, FALSE );
	}	
	else
	{
		UIManagePtr->SetCaption( m_strStDualIp, "", m_pWndTree, FALSE );
	}
}

void CCnsCfgLogic::UpdateCnsLevel( EmTPSipLevel emLevel )
{
	String astrScreenIp[MAX_CNS_SCREEN];
	for ( int nIndex = 0; nIndex < m_SelCnsInfo.m_wScreenNum; nIndex++ )
	{
		in_addr tAddr;
		tAddr.S_un.S_addr = m_SelCnsInfo.m_adwIP[nIndex];
		if ( emLevel == emTPSipProvince )
		{
			astrScreenIp[nIndex+1] = inet_ntoa(tAddr);
		}
		else
		{
			astrScreenIp[nIndex] = inet_ntoa(tAddr);
		}		
	}
	
	int nScreenCount = 0;
	//三级会场也可以三屏，不再用会场等级决定屏数
	if ( m_SelCnsInfo.m_wScreenNum > 1 )
	{
		if ( emLevel == emTPSipProvince )
		{
			nScreenCount = 5;
		}
		else
		{
			nScreenCount = 3;
		}
	}
	else
	{
		nScreenCount = m_SelCnsInfo.m_wScreenNum;
	}
	
	for ( int i = 0; i < MAX_CNS_SCREEN; i++ )
	{
		if ( i < nScreenCount )
		{
			UIManagePtr->ShowWindow( m_tCtrlScreenIp[i].strScreenPic, true, m_pWndTree, FALSE );
			UIManagePtr->ShowWindow( m_tCtrlScreenIp[i].strCnsScreen, true, m_pWndTree, FALSE );
			UIManagePtr->SetCaption( m_tCtrlScreenIp[i].strScreenIP, astrScreenIp[i], m_pWndTree, FALSE );
			UIManagePtr->ShowWindow( m_tCtrlScreenIp[i].strScreenIP, true, m_pWndTree, FALSE );
		}
		else
		{
			UIManagePtr->ShowWindow( m_tCtrlScreenIp[i].strScreenPic, false, m_pWndTree, FALSE );
			UIManagePtr->ShowWindow( m_tCtrlScreenIp[i].strCnsScreen, false, m_pWndTree, FALSE );
			UIManagePtr->ShowWindow( m_tCtrlScreenIp[i].strScreenIP, false, m_pWndTree, FALSE );
		}		
	}
}


bool CCnsCfgLogic::OnSetMainCns( const IArgs& args )
{
	bool bState;
	UIManagePtr->GetSwitchState( m_strBtnMainCns, bState, m_pWndTree );
	
	if ( bState )
	{
		memset( m_achMainCns, 0, sizeof(m_achMainCns) );
	}
	else
	{
		memcpy( m_achMainCns, m_SelCnsInfo.m_achRoomName, sizeof(m_achMainCns) );		
	}

	return true;
}

bool CCnsCfgLogic::OnSave( const IArgs& args )
{
	s8 achRoomName[TP_MAX_ALIAS_LEN+1] = {0};
	strcpy( achRoomName, ComInterface->GetMainCnsName() );

	if ( strcmp( achRoomName, m_achMainCns ) != 0 )
	{
		ComInterface->SetMainCns( m_achMainCns );
	}

	bool bDisPlay;
	String strCnsName;
	String strCnsNumber;

	Args_MsgBox msgArg;
	Window* pNameWnd = UIManagePtr->GetWindowPtr( _T(""), m_pWndTree );//UIManagePtr->GetWindowPtr( m_strEdtCnsName, m_pWndTree );
	msgArg.pOwnerWnd = pNameWnd;
	bool bChange = false;

	UIManagePtr->GetSwitchState( m_strBtnCnsCfgSwitch, bDisPlay, m_pWndTree);
	if ( m_SelCnsInfo.m_bIsShowRoomName != (BOOL)bDisPlay )
	{
		bChange = true;
	}

	UIManagePtr->GetCaption( m_strEdtCnsName, strCnsName, m_pWndTree );
	if ( strcmp( m_SelCnsInfo.m_achRoomName, strCnsName.c_str() ) != 0 )
	{	
		if ( strCnsName.length() <= 0 )
		{
			MSG_BOX( "会场名称不能为空", FALSE  , &msgArg );
			UIManagePtr->SetFocus( m_strEdtCnsName, m_pWndTree );//pNameWnd->SetFocus();

			return false;
		}
		if ( IsAllE164Number( strCnsName ) )
		{
			MSG_BOX( "会场名称不能全为数字及*#,号", FALSE  , &msgArg );
			UIManagePtr->SetFocus( m_strEdtCnsName, m_pWndTree );//pNameWnd->SetFocus();
			return false;
		}
		if ( !IsValidTPStr( strCnsName ) )
		{ 
			CString str; 
			str.Format( "会场名称不可以包含空格及括号中的任意字符 [ %s ]", INVALID_ALIAS_FOR_SHOW );
	    	MSG_BOX( str , FALSE  ,&msgArg ); 
			UIManagePtr->SetFocus( m_strEdtCnsName, m_pWndTree );//pNameWnd->SetFocus();
		 
			return false;
		}
		bChange = true;
	}
	
	UIManagePtr->GetCaption( m_strEdtCnsNumber, strCnsNumber, m_pWndTree );
	
	if ( strcmp( m_SelCnsInfo.m_achE164, strCnsNumber.c_str() ) != 0 )
	{
		CString cstrE164 = "";
		cstrE164.Format( "%s", strCnsNumber.c_str() );
		if ( !cstrE164.IsEmpty() && !CCallAddr::IsValidE164(cstrE164) )
		{
			//Window* pWnd = UIManagePtr->GetWindowPtr( m_strEdtCnsNumber, m_pWndTree );
			//msgArg.pOwnerWnd = pWnd;
			msgArg.pOwnerWnd = m_pWndTree->GetItemData()->pWnd;
			MSG_BOX( "会场号码不合法，E164号只能包含数字及*#,号", FALSE  , &msgArg );
			UIManagePtr->SetFocus( m_strEdtCnsNumber, m_pWndTree );//pWnd->SetFocus();
			return false;
		}
		bChange = true;
	}
	
	if ( m_emLevel != m_SelCnsInfo.m_emLevel )
	{
		bChange = true;
	}

	if ( bChange )
	{
        BOOL bInConf = BusinessManagePtr->IsInConf();
        if ( bInConf )
        {		
            MSG_BOX( "会议中，不能修改会场设置", FALSE  , &msgArg );
            return false;
	    }
		
		TTPCnsInfo tCnsInfo = m_SelCnsInfo;
		tCnsInfo.m_bIsShowRoomName = bDisPlay;
		strncpy( tCnsInfo.m_achRoomName, strCnsName.c_str(), sizeof( tCnsInfo.m_achRoomName ) );
		strncpy( tCnsInfo.m_achE164, strCnsNumber.c_str(), sizeof( tCnsInfo.m_achE164 ) );
		tCnsInfo.m_emLevel = m_emLevel;

		//绘制台标图片并上传
		if ( strcmp( m_SelCnsInfo.m_achRoomName, strCnsName.c_str() ) != 0 )
		{
			CString strFullPath = GetModuleFullPath();

			CString str1080Path = strFullPath + "confname1080.bmp";
			BOOL bSuccess1 = ConfSign->MakeImgByChar( strCnsName.c_str(), "宋体", FontStyleBold, Color(255,235,0), Color(0,0,0), 
				Color(255,255,255), 48, 2, (LPCSTR)str1080Path );

			CString str720Path = strFullPath + "confname720.bmp";
			BOOL bSuccess2 = ConfSign->MakeImgByChar( strCnsName.c_str(), "宋体", FontStyleBold, Color(255,235,0), Color(0,0,0), 
				Color(255,255,255), 32, 2, (LPCSTR)str720Path );

			if ( bSuccess1 && bSuccess2 )
			{
				m_vecConfFile.clear();
				m_vecConfFile.push_back("confname1080.bmp");
				m_vecConfFile.push_back("confname720.bmp");
				if( !UploadCore( CNSCONF_FILE_PATH, (String)GetModuleFullPath()+m_vecConfFile.at(0), m_vecConfFile.at(0), FALSE) )
				{
					ComInterface->ConfSignCmd( FALSE, 0 );
					PrtMsg( 0, emEventTypeCmsWindow, "%s还没开始进行ftp传输便失败！", m_vecConfFile.at(0).c_str() );
				}
			} 
			else if ( !bSuccess1 && bSuccess2 )
			{
				MSG_BOX( "1080P台标图片生成失败", FALSE, &msgArg );
			}
			else if ( bSuccess1 && !bSuccess2 )
			{
				MSG_BOX( "720P台标图片生成失败", FALSE, &msgArg );
			}
		}
		else
		{
			if ( bDisPlay )
			{
				ComInterface->ConfSignCmd( TRUE, 0 );
			}
		}

		u16 wRet = ComInterface->UpdateCnsInfo( tCnsInfo, 0 );
		if (wRet != NO_ERROR)
		{
			MSG_BOX( "保存会场配置请求发送失败", FALSE, &msgArg );
			return false;
		}	
	}
	
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
	
	if ( CheckAllIp() )
	{
		Args_MsgBox msgArg;
// 		BOOL bInConf = BusinessManagePtr->IsInConf();
//         if ( bInConf )
//         {	
// 			msgArg.pOwnerWnd = m_pWndTree->GetItemData()->pWnd;
//             MSG_BOX( "会议中，不能修改服务器设置", FALSE , &msgArg );
//             return false;
// 		   }
        
		//效验IP
		String strCaption;
		UIManagePtr->GetCaption( m_strEdtIp, strCaption, m_pWndTree );
		if ( strCaption.empty() )
		{  
			msgArg.pOwnerWnd = m_pWndTree->GetItemData()->pWnd;
			MSG_BOX( "CNS IP地址不能为空", FALSE, &msgArg );
			UIManagePtr->SetFocus( m_strEdtIp, m_pWndTree );
			return false;
		}
		if ( !CCallAddr::IsValidIpV4( valIp.dwIP ) )
        {		
            msgArg.pOwnerWnd = m_pWndTree->GetItemData()->pWnd;
            MSG_BOX( "CNS IP地址非法", FALSE, &msgArg );
            UIManagePtr->SetFocus( m_strEdtIp, m_pWndTree );
			return false;
		}
		CString cstrErrStr;
		if ( !CCallAddr::IsValidCallIP( valIp.dwIP, cstrErrStr, 0 ) ) 
		{
			msgArg.pOwnerWnd = m_pWndTree->GetItemData()->pWnd;
			MSG_BOX( cstrErrStr, FALSE, &msgArg );
			UIManagePtr->SetFocus( m_strEdtIp, m_pWndTree );
			return false;
		}

		//效验子网掩码
		UIManagePtr->GetCaption( m_strEdtSubMask, strCaption, m_pWndTree );
		if ( strCaption.empty() )
		{  
			msgArg.pOwnerWnd = m_pWndTree->GetItemData()->pWnd;
			MSG_BOX( "子网掩码不能为空", FALSE, &msgArg );
			UIManagePtr->SetFocus( m_strEdtSubMask, m_pWndTree );
			return false;
		}

		if ( !CCallAddr::IsValidIpMask(valSubMask.dwIP) )
		{
			msgArg.pOwnerWnd = m_pWndTree->GetItemData()->pWnd;
			MSG_BOX( "子网掩码无效。子网掩码必须是相邻的，请输入有效的掩码", FALSE, &msgArg );
			UIManagePtr->SetFocus( m_strEdtSubMask, m_pWndTree );
			return false;
		}

		if ( !CCallAddr::IsValidDevIP( valIp.dwIP, valSubMask.dwIP, cstrErrStr, 0 ) )
		{
			msgArg.pOwnerWnd = m_pWndTree->GetItemData()->pWnd;
			MSG_BOX( cstrErrStr, FALSE, &msgArg );
			UIManagePtr->SetFocus( m_strEdtSubMask, m_pWndTree );
			return false;
		}
		
		//效验网关
		UIManagePtr->GetCaption( m_strEdtGateWay, strCaption, m_pWndTree );
		if ( !strCaption.empty() && !CCallAddr::IsValidIpV4( valGateway.dwIP ) )
		{
			msgArg.pOwnerWnd = m_pWndTree->GetItemData()->pWnd;
			MSG_BOX( "网关IP地址非法", FALSE, &msgArg );
			UIManagePtr->SetFocus( m_strEdtGateWay, m_pWndTree );
			return false;
		}

		if ( !strCaption.empty() )
		{
			DWORD dwNetID = valIp.dwIP & valSubMask.dwIP;
			DWORD dwNetGate = valGateway.dwIP & valSubMask.dwIP;
			if ( dwNetGate != dwNetID )
			{
				msgArg.pOwnerWnd = m_pWndTree->GetItemData()->pWnd;
				int nReslut = MSG_BOX( "默认网关不在由IP地址和子网掩码定义的同一网络段(子网)上,是否保存此配置？", TRUE, &msgArg );
				if ( IDOK != nReslut )
				{
					UIManagePtr->SetFocus( m_strEdtGateWay, m_pWndTree );//msgArg.pOwnerWnd->SetFocus();
					return false; 
				}  
			}
		}

 		if ( strNatIp != strOldNatIp || bUseNAT != (bool)tOldNatInfo.bUsed )
 		{	
			if ( strNatIp.empty() && true == bUseNAT )
			{
				msgArg.pOwnerWnd = m_pWndTree->GetItemData()->pWnd;
				MSG_BOX( "NAT地址不能为空", FALSE, &msgArg );
				UIManagePtr->SetFocus( m_strEdtNatIP, m_pWndTree );
				return false;
			}

			if ( !CCallAddr::IsValidCallIP( valNatIp.dwIP ) && !strNatIp.empty() ) 
			{
				msgArg.pOwnerWnd = m_pWndTree->GetItemData()->pWnd;
				MSG_BOX( "NAT地址非法", FALSE, &msgArg );
				UIManagePtr->SetFocus( m_strEdtNatIP, m_pWndTree );
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
// 			Args_MsgBox msgarg;
// 			msgarg.pOwnerWnd = m_pWndTree->GetItemData()->pWnd;
// 			int nReslut = MSG_BOX( "修改IP地址将断开连接，请确认是否修改", TRUE, &msgarg ); //dyy 2013年9月2日 Bug00154718
//             if ( IDOK == nReslut )
// 			{
				IArgs arg("");
				SaveEthnetCfg( arg );
                UIManagePtr->LoadScheme( "SchmNormal", m_pWndTree );
// 			}  
//             else
//             {
//                 UpdateEthnetInfo( 0, 0 );
//                 UpdateNatInfo( 0, 0 );
//                 UIManagePtr->LoadScheme( "SchmNormal", m_pWndTree );
//             }
		}
        else
        {
            UpdateEthnetInfo( 0, 0 );
            UIManagePtr->LoadScheme( "SchmNormal", m_pWndTree );
        }
	}
    else
    {
		UpdateEthnetInfo( 0, 0 );
		UpdateNatInfo( 0, 0 );
        UIManagePtr->LoadScheme( "SchmNormal", m_pWndTree );
    }
//	UIManagePtr->LoadScheme( "SchmNormal", m_pWndTree );

	return true;
}

bool CCnsCfgLogic::OnCancel( const IArgs& args )
{
	ShowCnsInfo();
	UpdateEthnetInfo( 0 ,0 );
	UpdateNatInfo( 0 , 0 );
	UIManagePtr->LoadScheme( "SchmNormal", m_pWndTree );
	return true;
}

bool CCnsCfgLogic::OnEdit( const IArgs& args )
{
	Args_MsgBox msgArg;
	msgArg.pOwnerWnd = m_pWndTree->GetItemData()->pWnd;

	TTPCnsConfStatus tConfStatus = BusinessManagePtr->GetLocalCnsConfState();
	if ( tConfStatus.emState == em_CALL_CONNECTED )
	{
		MSG_BOX( "会议中，不能修改会场设置", FALSE  , &msgArg );
		return false;
	}

	BOOL bInConf = BusinessManagePtr->IsInConf();
	if ( bInConf )
	{		
		MSG_BOX( "会议中，不能修改会场设置", FALSE  , &msgArg );
		return false;
	}

	bInConf = BusinessManagePtr->IsCnsInConf( m_SelCnsInfo.m_achRoomName );
	if ( bInConf )
	{
		CString strError;
		strError.Format( "会场：%s在会议中，不能修改会场设置", m_SelCnsInfo.m_achRoomName );
		MSG_BOX( strError, FALSE  , &msgArg );
		return false;
	}
	
	UIManagePtr->LoadScheme( "SchmEdit", m_pWndTree );

	IArgs* pArg = NULL;
    BtnSwitchNATClick( *pArg );

	//如果是1屏会场，不能设置为主会场
	if ( m_SelCnsInfo.m_wScreenNum < 3 )
	{
		UIManagePtr->EnableWindow( m_strRadioProvince, false, m_pWndTree );
		UIManagePtr->SetCheckState( m_strRadioProvince, false, m_pWndTree );
		UIManagePtr->EnableWindow( m_strRadioCity, false, m_pWndTree );
		UIManagePtr->SetCheckState( m_strRadioCity, false, m_pWndTree );
	}
	
	return true;
}

bool CCnsCfgLogic::BtnSwitchCnsCfgClick( const IArgs& args )
{	
	bool bIsShowRoomName = false;
	UIManagePtr->GetSwitchState( m_strBtnCnsCfgSwitch, bIsShowRoomName, m_pWndTree );
	return true;
}

bool CCnsCfgLogic::OnBtnCnsLevel1( const IArgs& args )
{
	m_emLevel = emTPSipProvince;
	UpdateCnsLevel( m_emLevel );
	return true;
}

bool CCnsCfgLogic::OnBtnCnsLevel2( const IArgs& args )
{
	m_emLevel = emTPSipCity;
	UpdateCnsLevel( m_emLevel );
	return true;
}

bool CCnsCfgLogic::OnBtnCnsLevel3( const IArgs& args )
{
	m_emLevel = emTPSipCounty;
	UpdateCnsLevel( m_emLevel );
	return true;
}

bool CCnsCfgLogic::OnCfgCnsList( const IArgs& args )
{
	ZeroMemory( &m_SelCnsInfo, sizeof(TTPCnsInfo) );
	UIManagePtr->LoadScheme( "SchmList", m_pWndTree );
	return true;
}

bool CCnsCfgLogic::OnSysCfg( const IArgs& args )
{
    if ( ! UIManagePtr->IsVisible( "CnsCfgDlg/BtnEdit" ) )
    {        
        s8 achRoomName[TP_MAX_ALIAS_LEN+1] = {0};
        strcpy( achRoomName, ComInterface->GetMainCnsName() );
        bool bDisPlay;
        String strCnsName;
        String strCnsNumber;
        UIManagePtr->GetSwitchState( m_strBtnCnsCfgSwitch, bDisPlay, m_pWndTree);
        UIManagePtr->GetCaption( m_strEdtCnsName, strCnsName, m_pWndTree );       
        UIManagePtr->GetCaption( m_strEdtCnsNumber, strCnsNumber, m_pWndTree );
        
        if ( strcmp( achRoomName, m_achMainCns ) != 0 || strcmp( m_SelCnsInfo.m_achRoomName, strCnsName.c_str() ) != 0
            || strcmp( m_SelCnsInfo.m_achE164, strCnsNumber.c_str() ) != 0 || m_SelCnsInfo.m_bIsShowRoomName != (BOOL)bDisPlay || CheckAllIp() )
        {
            CString strMsg = "是否对编辑进行保存?";
            Args_MsgBox argMsg;
            argMsg.pOwnerWnd = UIManagePtr->GetWindowPtr( "CnsCfgDlg" );
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

bool CCnsCfgLogic::OnCloseDlg( const IArgs& args )
{
	UIManagePtr->ShowWindow( "CnsCfgDlg", false );
	return true;
}


LRESULT CCnsCfgLogic::OnMainRoomNotify( WPARAM wParam, LPARAM lParam )
{
	if ( m_pWndTree == NULL )
	{
		return NO_ERROR;
	}

	memcpy( m_achMainCns, ComInterface->GetMainCnsName(), sizeof(m_achMainCns) );

	if ( strcmp( m_achMainCns, m_SelCnsInfo.m_achRoomName ) == 0 )
	{
		UIManagePtr->SetSwitchState( m_strBtnMainCns, true, m_pWndTree );
	}
	else
	{
		UIManagePtr->SetSwitchState( m_strBtnMainCns, false, m_pWndTree );
	}

	return NO_ERROR;
}

LRESULT CCnsCfgLogic::OnCnsInfoNotify( WPARAM wparam, LPARAM lparam )
{
	if ( m_pWndTree == NULL )
	{
		return NO_ERROR;
	}

	TTPCnsInfo tCnsInfo = *(TTPCnsInfo*)wparam;
	EmTPCNSInfoRst emRst = (EmTPCNSInfoRst)lparam;

	if ( emRst != emTPCNSInfoSuccess )
	{
		CString strName;
		strName.Format( "会场 %s 注册服务器失败: ", m_SelCnsInfo.m_achRoomName );
		
		CString strTemp = "注册别名重复";

		if ( emRst == emTPCNSRepeatAliasName )
		{
			strTemp = "会场名称重复";
		}
		else if ( emRst == emTPCNSRepeatE164 )
		{
			strTemp = "会场号码重复";
		}

		ShowPopMsg( strName + strTemp );
	}

	ComInterface->GetLocalCnsInfo( m_SelCnsInfo );
		
	ShowCnsInfo();
		
	return NO_ERROR;
}


void CCnsCfgLogic::Clear()
{
    m_vctCnsList.clear() ;
    ZeroMemory( &m_SelCnsInfo, sizeof(TTPCnsInfo) );
    ZeroMemory( m_achMainCns, sizeof(m_achMainCns) );  

	if ( m_pWndTree != NULL )
	{	
		UpdateEthnetInfo( 0 ,0 );
		UIManagePtr->LoadScheme( "SchmNormal", m_pWndTree );
	}
}

bool CCnsCfgLogic::OnUploadProgress( const IArgs & arg )
{
	Args_WindowMsg WinMsg = *dynamic_cast<const Args_WindowMsg*>(&arg);
	WindowMsg msg = WinMsg.m_Msg;
	
	m_emFileFtpStatus = static_cast<EmFtpStatus>(msg.wParam);
	
	switch( m_emFileFtpStatus )
	{
	case emFtpBegin:
		{
			PrtMsg( 0, emEventTypeCmsWindow, "%s已经进入传输状态！", m_vecConfFile.at(0).c_str() );
		}
		break;
	case emFtpTransfer:
		{
		}
		break;
	case emFtpEnd:
		{
			DWORD dwSuccess = static_cast<DWORD>(msg.lParam);     //FTP接口0为成功  默认失败
			m_cFtp.EndFtpFile();	
			if ( 0 == dwSuccess )
			{
				PrtMsg( 0, emEventTypeCmsWindow, "此时待传输文件个数：%d", m_vecConfFile.size()-1 );
				if ( m_vecConfFile.size() >0 )
				{	
					vector<String>::iterator itr = m_vecConfFile.begin();
					m_vecConfFile.erase(itr);
					if ( m_vecConfFile.size() > 0 )
					{
						if ( !UploadCore( CNSCONF_FILE_PATH, (String)GetModuleFullPath()+m_vecConfFile.at(0), m_vecConfFile.at(0), FALSE) )
						{			
							ComInterface->ConfSignCmd( FALSE, 0 );
							PrtMsg( 0, emEventTypeCmsWindow, "%s还没开始进行ftp传输便失败！", m_vecConfFile.at(0).c_str() );
						}		
					}
					else
					{
						bool bDisPlay = false;						
						UIManagePtr->GetSwitchState( m_strBtnCnsCfgSwitch, bDisPlay, m_pWndTree);
						if ( bDisPlay )
						{
							ComInterface->ConfSignCmd( TRUE, 0 );
						}		
						PrtMsg( 0, emEventTypeCmsWindow, "图片上传完毕，界面显示台标开关：%d", bDisPlay );
					}

				}
			}
			else
			{
				ComInterface->ConfSignCmd( FALSE, 0 );
				PrtMsg( 0, emEventTypeCmsWindow, "进行ftp后%s传输失败！", m_vecConfFile.at(0).c_str() );
				LPTSTR pszMsg = NULL;
				m_cFtp.FormatFtpError( dwSuccess, &pszMsg );
				OspPrintf( TRUE, FALSE, "导入文件出错，错误原因：%s！", pszMsg );
				//IArgs iargs("");
				//MSG_BOX( pszMsg,FALSE,&iargs );
				LocalFree( pszMsg );
			}		
		}
		break;
	default:
		{
		}
		break;
	}	
	return true;
}

BOOL CCnsCfgLogic::UploadCore( const String& strRemotePath, const String& strLocalFile, const String& strCheckFileName, BOOL bAutoEnd /*= TRUE */ )
{
	CString strIpAddr;
	
	m_cFtp.RegisterMsgHandle( WM_CNC_FTPCONFSIGNPROGRESS );

	u32 dwIp;
	BusinessManagePtr->GetLoginIp(dwIp);		
	struct in_addr addrIPAddr;
	addrIPAddr.S_un.S_addr = htonl(dwIp);
	strIpAddr = inet_ntoa(addrIPAddr);
	
	BOOL32 bRet = m_cFtp.SetServerParam( strIpAddr, "admin", "admin" );
	if ( !bRet )
	{
		IArgs iargs("");
		MSG_BOX("设置FTP上传服务器失败!",FALSE,&iargs);		
		return FALSE;
	}
	
	String strRemoteFilePath = strRemotePath;
	strRemoteFilePath += strCheckFileName;
	m_cFtp.SetAutoEndFtpFile(bAutoEnd/*FALSE*/);
	
	if ( !m_cFtp.BeginUpload( m_pWnd->GetSafeHwnd(), strRemoteFilePath.c_str(), strLocalFile.c_str(),
		FTP_TRANSFER_TYPE_BINARY, FTP_AGENT ) )
	{
		// IArgs iargs("");
		// MSG_BOX("上传文件失败，参数错误!",FALSE,&iargs);	
		m_cFtp.SetAutoEndFtpFile(TRUE);
		return FALSE;
	}
	return TRUE;
}

bool CCnsCfgLogic::BtnSwitchNATClick( const IArgs& args )
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

LRESULT CCnsCfgLogic::UpdateEthnetInfo( WPARAM wParam, LPARAM lParam )
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

LRESULT CCnsCfgLogic::UpdateNatInfo( WPARAM wParam, LPARAM lParam )
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

bool CCnsCfgLogic::SaveEthnetCfg( const IArgs& args )
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

BOOL CCnsCfgLogic::CheckAllIp()
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