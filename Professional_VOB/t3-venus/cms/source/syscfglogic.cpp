// syscfglogic.cpp: implementation of the CSysCfgLogic class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "syscfglogic.h"
#include "SaveLogLogic.h"
CSysCfgLogic* CSysCfgLogic::m_pCfgLogic = NULL;

//const String CSysCfgLogic::m_strEthnetCfg = "服务器设置"; 
const String CSysCfgLogic::m_strCnsCfg = "会场设置";
const String CSysCfgLogic::m_strRegService = "服务器配置";
//const String CSysCfgLogic::m_strRegGK = "GK设置";
const String CSysCfgLogic::m_strSysTem = "系统时间设置";
const String CSysCfgLogic::m_strSaveLog = "系统日志";
const String CSysCfgLogic::m_strDualSrcCfg = "演示源设置";
const String CSysCfgLogic::m_strSysStandBy = "系统待机配置";
const String CSysCfgLogic::m_strNetManageCfg = "网管配置";
//const String CSysCfgLogic::m_strUpdService = _T("升级服务器地址");
const String CSysCfgLogic::m_strCallServerCfg = _T("呼叫配置");
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CSysCfgLogic::CSysCfgLogic()
{

}

CSysCfgLogic::~CSysCfgLogic()
{
	if ( m_pCfgLogic != NULL )
	{   
		UnRegMsg();
		UnRegFunc();
		delete m_pCfgLogic;
		m_pCfgLogic = NULL;
	}
}


bool CSysCfgLogic::RegCBFun()
{
	REG_GOBAL_MEMBER_FUNC( "CSysCfgLogic::InitWnd", CSysCfgLogic::InitWnd, m_pCfgLogic, CSysCfgLogic );
//	REG_GOBAL_MEMBER_FUNC( "CSysCfgLogic::OnEthnetSet", CSysCfgLogic::OnEthnetSet, m_pCfgLogic, CSysCfgLogic );
	REG_GOBAL_MEMBER_FUNC( "CSysCfgLogic::OnCnsCfg", CSysCfgLogic::OnCnsCfg, m_pCfgLogic, CSysCfgLogic );	
	REG_GOBAL_MEMBER_FUNC( "CSysCfgLogic::OnRegService", CSysCfgLogic::OnRegService, m_pCfgLogic, CSysCfgLogic );
    REG_GOBAL_MEMBER_FUNC( "CSysCfgLogic::OnRegGK", CSysCfgLogic::OnRegGK, m_pCfgLogic, CSysCfgLogic );
    REG_GOBAL_MEMBER_FUNC( "CSysCfgLogic::OnSetTime", CSysCfgLogic::OnSetTime, m_pCfgLogic, CSysCfgLogic );
	REG_GOBAL_MEMBER_FUNC( "CSysCfgLogic::OnDualSrcCfg", CSysCfgLogic::OnDualSrcCfg, m_pCfgLogic, CSysCfgLogic );
	REG_GOBAL_MEMBER_FUNC( "CSysCfgLogic::OnSysStandBy", CSysCfgLogic::OnSysStandBy, m_pCfgLogic, CSysCfgLogic );
	REG_GOBAL_MEMBER_FUNC( "CSysCfgLogic::OnNetManageCfg", CSysCfgLogic::OnNetManageCfg, m_pCfgLogic, CSysCfgLogic );
	REG_GOBAL_MEMBER_FUNC( "CSysCfgLogic::OnOpenSysList", CSysCfgLogic::OnOpenSysList, m_pCfgLogic, CSysCfgLogic );
	REG_GOBAL_MEMBER_FUNC( "CSysCfgLogic::OnCloseDlg", CSysCfgLogic::OnCloseDlg, m_pCfgLogic, CSysCfgLogic );
    REG_GOBAL_MEMBER_FUNC( "CSysCfgLogic::OnSaveLog", CSysCfgLogic::OnSaveLog, m_pCfgLogic, CSysCfgLogic );
	REG_GOBAL_MEMBER_FUNC( "CSysCfgLogic::OnUpdService", CSysCfgLogic::OnUpdService, m_pCfgLogic, CSysCfgLogic );	
	REG_GOBAL_MEMBER_FUNC( "CSysCfgLogic::OnCallServerCfg", CSysCfgLogic::OnCallServerCfg, m_pCfgLogic, CSysCfgLogic );	

	return true;
}

bool CSysCfgLogic::UnRegFunc()
{
	
	return true;
}

void CSysCfgLogic::RegMsg()
{
	
}


CSysCfgLogic* CSysCfgLogic::GetLogicPtr()
{
	if ( m_pCfgLogic == NULL )
	{  
		m_pCfgLogic = new CSysCfgLogic();  
	}
	
	return m_pCfgLogic;
}


bool CSysCfgLogic::InitWnd( const IArgs & args )
{
	CWndLogicBase::InitWnd( args );
	
	InitCfgList();

//	UIManagePtr->ShowWindow( "EthnetCfgDlg", false );
	UIManagePtr->ShowWindow( "CnsCfgDlg", false );
	UIManagePtr->ShowWindow( "RegServiceDlg", false );
//	UIManagePtr->ShowWindow( "RegGkDlg", false ); 
    UIManagePtr->ShowWindow( "DlgSysTime", false ); 
	UIManagePtr->ShowWindow( "DualSrcManageDlg", false );
	UIManagePtr->ShowWindow( "SysStandByDlg", false );
	UIManagePtr->ShowWindow( "NetManageCfgDlg", false );
    UIManagePtr->ShowWindow( g_strSaveLogDlg, false );
//	UIManagePtr->ShowWindow( _T("UpdServiceDlg"), false );
	UIManagePtr->ShowWindow( _T("CallServerCfgDlg"), false );

	return true;
}

void CSysCfgLogic::InitCfgList()
{   
    TMenuItemInfo tMenu;
    ARRAY<String> vcItem;
   
    vcItem.push_back( "ImageItemSysCfg" );
    tMenu.m_pVctSubItem = &vcItem;
    
        
    ARRAY<TMenuItemInfo> menuList; 
    
//     tMenu.strTxt = m_strEthnetCfg;
//     tMenu.strItemFunc = "CSysCfgLogic::OnEthnetSet";
//     menuList.push_back( tMenu );
      
    tMenu.strTxt = m_strCnsCfg;
    tMenu.strItemFunc = "CSysCfgLogic::OnCnsCfg";
    menuList.push_back( tMenu );

	tMenu.strTxt = m_strCallServerCfg;
    tMenu.strItemFunc = "CSysCfgLogic::OnCallServerCfg";
    menuList.push_back( tMenu );
    
	tMenu.strTxt = m_strRegService;
    tMenu.strItemFunc = "CSysCfgLogic::OnRegService";
    menuList.push_back( tMenu );

//     tMenu.strTxt = m_strRegGK;
//     tMenu.strItemFunc = "CSysCfgLogic::OnRegGK";
//     menuList.push_back( tMenu );
   
    tMenu.strTxt = m_strSysTem;
    tMenu.strItemFunc = "CSysCfgLogic::OnSetTime";
    menuList.push_back( tMenu );

	tMenu.strTxt = m_strDualSrcCfg;
    tMenu.strItemFunc = "CSysCfgLogic::OnDualSrcCfg";
    menuList.push_back( tMenu );

// 	tMenu.strTxt = m_strUpdService;
//     tMenu.strItemFunc = "CSysCfgLogic::OnUpdService";
//     menuList.push_back( tMenu );

 	tMenu.strTxt = m_strSysStandBy;
    tMenu.strItemFunc = "CSysCfgLogic::OnSysStandBy";
    menuList.push_back( tMenu );

	tMenu.strTxt = m_strNetManageCfg;
    tMenu.strItemFunc = "CSysCfgLogic::OnNetManageCfg";
    menuList.push_back( tMenu );
    
    ARRAY<String> vcItem2;   
    vcItem2.push_back( "ImgItemDownloadLog" );
    tMenu.m_pVctSubItem = &vcItem2;
    tMenu.strTxt = m_strSaveLog;
    tMenu.strItemFunc = "CSysCfgLogic::OnSaveLog";
    menuList.push_back( tMenu );

    Value_TouchListMenu val( &menuList );
    UIManagePtr->SetPropertyValue( val, "CfgList", m_pWndTree );
}

bool CSysCfgLogic::OnOpenSysList( const IArgs& args )
{
	if ( const Args_ClickItemInfo *pClickInfo =  dynamic_cast< const Args_ClickItemInfo*>(&args) )
    {
        IBaseItem* pBaseItem = pClickInfo->m_pClickList->GetParentItem()->GetItemData();        
        if ( const Data_Menu *pItemInfo = dynamic_cast<const Data_Menu*>( pBaseItem->GetUserData() )) 
        {   
//          if ( pItemInfo->m_tMenuInfo.strTxt == m_strEthnetCfg )
//          {  
// 				OnEthnetSet(args);
// 			}
			if ( pItemInfo->m_tMenuInfo.strTxt == m_strCnsCfg )
			{
				OnCnsCfg(args);
			}
            else if ( pItemInfo->m_tMenuInfo.strTxt == m_strSaveLog )
            {
                OnSaveLog(args);
            }
			else
			{
				OnRegService(args);
			}
		}
	}
	return true;
}

bool CSysCfgLogic::OnEthnetSet( const IArgs& args )
{
    UIManagePtr->LoadScheme( "SchmEthnetCfg", m_pWndTree );
	return true;
}

bool CSysCfgLogic::OnCnsCfg( const IArgs& args )
{
	UIManagePtr->LoadScheme( "SchmCnsCfg", m_pWndTree );
	return true;
}

bool CSysCfgLogic::OnRegService( const IArgs& args )
{
	UIManagePtr->LoadScheme( "SchmRegService", m_pWndTree );
	return true;
}

bool CSysCfgLogic::OnRegGK( const IArgs& args )
{
    UIManagePtr->LoadScheme( "SchmRegGk", m_pWndTree );
	return true;
}

bool CSysCfgLogic::OnSetTime( const IArgs& args )
{
    UIManagePtr->LoadScheme( "SchmSetTime", m_pWndTree );
	return true;
}

bool CSysCfgLogic::OnDualSrcCfg( const IArgs& args )
{
    UIManagePtr->LoadScheme( "SchmShowDualLst", NULL, "DualSrcManageDlg" );
	UIManagePtr->LoadScheme( "SchmDualSrc", m_pWndTree );
	return true;
}

bool CSysCfgLogic::OnSysStandBy( const IArgs& args )
{
    UIManagePtr->LoadScheme( "SchmSysStandBy", m_pWndTree );
	return true;
}

bool CSysCfgLogic::OnNetManageCfg( const IArgs& args )
{
    UIManagePtr->LoadScheme( "SchmShowNetManageLst", NULL, "NetManageCfgDlg" );
	UIManagePtr->LoadScheme( "SchmNetManage", m_pWndTree );
	return true;
}

bool CSysCfgLogic::OnUpdService( const IArgs& args )
{
	UIManagePtr->LoadScheme( _T("SchmUpdService"), m_pWndTree );
	return true;
}

bool CSysCfgLogic::OnCallServerCfg( const IArgs& args )
{
	UIManagePtr->LoadScheme( _T("SchmCallServerCfg"), m_pWndTree );
	return true;
}

void CSysCfgLogic::Clear()
{
	if ( m_pWndTree != NULL )
	{
		UIManagePtr->LoadScheme( "SchmSysCfg", m_pWndTree );
        UIManagePtr->ShowWindow( "SysCfgDlg", false );
	}
}


bool CSysCfgLogic::OnCloseDlg( const IArgs& args )
{
	return UIManagePtr->ShowWindow( "SysCfgDlg", false );
}

bool CSysCfgLogic::OnSaveLog( const IArgs& args )
{     
    //for set g_strSaveLogDlg's owner WND
    Value_WindowOwer valOwner;
    valOwner.pWnd = m_pWndTree->m_ptItemData->pWnd;
    UIManagePtr->SetPropertyValue( valOwner, g_strSaveLogDlg );

    UIManagePtr->LoadScheme( "", NULL, g_strSaveLogDlg );
    UIManagePtr->ShowWindow( g_strSaveLogDlg, true );

    //pc版 显示保存日志时位置进行调整 dyy
//    if ( UIDATAMGR->IsPcVersion() )
    {
        POINT pt;
        Value_WindowSize val;
        UIManagePtr->GetPropertyValue( val, g_strSaveLogDlg );
        
        Value_WindowSize valParent;
        UIManagePtr->GetPropertyValue( valParent, g_stcStrMainFrameDlg );
        
        pt.x = ( valParent.nWidth - val.nWidth ) / 2;
        pt.y = 189; 
        UIFACTORYMGR_PTR->SetWndPos( pt, g_strSaveLogDlg, NULL, g_stcStrMainFrameDlg );
    }
    
    return true;
}