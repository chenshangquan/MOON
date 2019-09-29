// cfgFrameLogic.cpp: implementation of the CCfgFrameLogic class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "cnsToolDll.h"
#include "cfgFrameLogic.h"
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCfgFrameLogic::CCfgFrameLogic()
{
	m_strLstFunMenu = "CfgMenuDlg/LstCfgFuncMenu";
}

CCfgFrameLogic::~CCfgFrameLogic()
{

}


void CCfgFrameLogic::RegCBFun()
{
	CCfgFrameLogic *pThis =  GetSingletonPtr();
	
    REG_GOBAL_MEMBER_FUNC( "CCfgFrameLogic::InitWnd", CCfgFrameLogic::InitWnd, pThis, CCfgFrameLogic ) ;
	//ÁÐ±í°´Å¥µã»÷ÊÂ¼þ
	REG_LIST_CALLFUNC( "CCfgFrameLogic::OnClickCnsCfg", CCfgFrameLogic::OnClickCnsCfg, pThis, CCfgFrameLogic ) ;
	REG_LIST_CALLFUNC( "CCfgFrameLogic::OnClickAudioPortCfg", CCfgFrameLogic::OnClickAudioPortCfg, pThis, CCfgFrameLogic ) ;
	REG_LIST_CALLFUNC( "CCfgFrameLogic::OnClickNetMgrCfg", CCfgFrameLogic::OnClickNetMgrCfg, pThis, CCfgFrameLogic ) ;
	REG_LIST_CALLFUNC( "CCfgFrameLogic::OnClickMixCfg", CCfgFrameLogic::OnClickMixCfg, pThis, CCfgFrameLogic ) ;
	REG_LIST_CALLFUNC( "CCfgFrameLogic::OnClickEqCfg", CCfgFrameLogic::OnClickEqCfg, pThis, CCfgFrameLogic ) ;
	REG_LIST_CALLFUNC( "CCfgFrameLogic::OnClickServerCfg", CCfgFrameLogic::OnClickServerCfg, pThis, CCfgFrameLogic ) ;
	REG_LIST_CALLFUNC( "CCfgFrameLogic::OnClickCallSerCfg", CCfgFrameLogic::OnClickCallSerCfg, pThis, CCfgFrameLogic ) ;
}

void CCfgFrameLogic::UnRegFunc()
{
	UN_REG_GOBAL_FUNC( "CCfgFrameLogic::InitWnd" );
}

bool CCfgFrameLogic::InitWnd( const IArgs & arg )
{    
	CLogicBase::InitWnd( arg );
	InitCfgFuncMenu();
	UIFACTORYMGR_PTR->ShowWindow(g_strCfgCnsDlg);
	UIFACTORYMGR_PTR->ShowWindow( g_strCfgAudioPort, false );
	UIFACTORYMGR_PTR->ShowWindow( g_stcStrCfgNetMngDlg, false );
	UIFACTORYMGR_PTR->ShowWindow( g_stcStrNetMngOptDlg, false );
	UIFACTORYMGR_PTR->ShowWindow( g_strCfgMixDlg, false );
	UIFACTORYMGR_PTR->ShowWindow( g_strCfgEqDlg, false );
	UIFACTORYMGR_PTR->ShowWindow( g_strCfgServerDlg, false );
	UIFACTORYMGR_PTR->ShowWindow( g_strCfgCallSer, false );
	m_strCurWnd = g_strCfgCnsDlg;
	m_strCfgCurWnd = g_strCfgCnsDlg;
	return true;
}

void CCfgFrameLogic::Clear()
{
	m_strCfgCurWnd = g_strCfgCnsDlg;
	if ( m_pWndTree != NULL )
	{		
		UIFACTORYMGR_PTR->LoadScheme( "SchmConfMenuListDefault", m_pWndTree );   //µÇÂ½ºó³õÊ¼»¯Ä¬ÈÏÒ³Ãæ
	}
}

void CCfgFrameLogic::RegMsg()
{
	CCfgFrameLogic *pThis =  GetSingletonPtr(); 
	//REG_MSG_HANDLER( UI_CNS_DISCONNECTED, CCfgFrameLogic::OnDisConnect, pThis, CCfgFrameLogic );
	
}

void CCfgFrameLogic::UnRegMsg()
{
	
}
 

bool CCfgFrameLogic::OnClickCnsCfg( const IArgs& args )
{
	SwitchCfgTabWnd(g_strCfgCnsDlg);
	return true;
}

bool CCfgFrameLogic::OnClickAudioPortCfg( const IArgs& args )
{
	SwitchCfgTabWnd(g_strCfgAudioPort);
	return true;
}

void CCfgFrameLogic::SwitchCfgTabWnd( string strWnd )
{
	if ( m_strCurWnd == g_strCfgCnsDlg && strWnd != g_strCfgCnsDlg )
	{
		bool bChange = CCfgCnsLogic::GetSingletonPtr()->IsCfgCnsChange();
		if ( false == bChange )
		{
			UIDATAMGR_PTR->SetLstSelItem( m_strLstFunMenu, m_pWndTree, 0 );
			return;
		}
	}

	if ( m_strCurWnd == g_strCfgCallSer && strWnd != g_strCfgCallSer )
	{
		bool bChange = CCfgCallSerLogic::GetSingletonPtr()->IsCfgCallChange();
		if ( false == bChange )
		{
			UIDATAMGR_PTR->SetLstSelItem( m_strLstFunMenu, m_pWndTree, 1 );
			return;
		}
	}

	if ( m_strCurWnd == g_strCfgServerDlg && strWnd != g_strCfgServerDlg )
	{
		bool bChange = CCfgServerLogic::GetSingletonPtr()->IsCfgSerChange();
		if ( false == bChange )
		{
			UIDATAMGR_PTR->SetLstSelItem( m_strLstFunMenu, m_pWndTree, 2 );
			return;
		}
	}
	
	if ( m_strCurWnd == g_strCfgAudioPort && strWnd != g_strCfgAudioPort )
	{
		bool bChange = CCfgAudioPortLogic::GetSingletonPtr()->IsCfgAudioChange();
		if ( false == bChange )
		{
			UIDATAMGR_PTR->SetLstSelItem( m_strLstFunMenu, m_pWndTree, 3 );
			return;
		}
	}
	
	if ( m_strCurWnd == g_strCfgMixDlg && strWnd != g_strCfgMixDlg )
	{
		bool bChange = CCfgMixLogic::GetSingletonPtr()->IsCfgMixChange();
		if ( false == bChange )
		{
			UIDATAMGR_PTR->SetLstSelItem( m_strLstFunMenu, m_pWndTree, 4 );
			return;
		}
	}
	
	if ( m_strCurWnd == g_strCfgEqDlg && strWnd != g_strCfgEqDlg )
	{
		bool bChange = CCfgEqLogic::GetSingletonPtr()->IsCfgEqChange();
		if ( false == bChange )
		{
			UIDATAMGR_PTR->SetLstSelItem( m_strLstFunMenu, m_pWndTree, 5 );
			return;
		}	
	}
	HideAllWnd();
	UIFACTORYMGR_PTR->ShowWindow(strWnd);
	m_strCurWnd = strWnd;
	m_strCfgCurWnd = strWnd;
}

bool CCfgFrameLogic::OnClickNetMgrCfg( const IArgs& args )
{
	SwitchCfgTabWnd(g_stcStrCfgNetMngDlg);
	return true;
}

void CCfgFrameLogic::InitCfgFuncMenu()
{
	ARRAY<TMenuItem> aryItem;
	TMenuItem item; 
	
	item.SetItemName("CNSÅäÖÃ" );  
	item.SetItemType("ImageItemMenuCfgCns");
	aryItem.push_back(item);
	
	item.SetItemName("ºô½ÐÅäÖÃ" );  
	item.SetItemType("ImageItemMenuCfgCall");
	aryItem.push_back(item);
		
	item.SetItemName("·þÎñÆ÷ÅäÖÃ" );  
	item.SetItemType("ImageItemMenuServerCfg");
	aryItem.push_back(item);
			
	item.SetItemName("ÒôÆµ½Ó¿ÚÅäÖÃ" ); 
	item.SetItemType("ImageItemMenuAudioPortCfg");
	aryItem.push_back(item);
	
	item.SetItemName("»ìÒôÅäÖÃ" ); 
	item.SetItemType("ImageItemMenuMixCfg");
	aryItem.push_back(item);
	
	item.SetItemName("¾ùºâÆ÷ÅäÖÃ" );  
	item.SetItemType("ImageItemMenuEqCfg");
	aryItem.push_back(item);
				
	item.SetItemName("Íø¹ÜÅäÖÃ" );  
	item.SetItemType("ImageItemMenuNetMgrCfg");
	aryItem.push_back(item);
	
	Value_ItemMenu valueMenu( &aryItem ); 
	valueMenu.m_strAlgroithm = IAlgorithm::strVert;
	UIFACTORYMGR_PTR->SetPropertyValue( valueMenu, m_strLstFunMenu, m_pWndTree ); 
}

bool CCfgFrameLogic::OnClickMixCfg( const IArgs& args )
{
	SwitchCfgTabWnd(g_strCfgMixDlg);
	return true;
}

bool CCfgFrameLogic::OnClickEqCfg( const IArgs& args )
{
	SwitchCfgTabWnd(g_strCfgEqDlg);
	return true;
}

bool CCfgFrameLogic::OnClickServerCfg( const IArgs& args )
{
	SwitchCfgTabWnd(g_strCfgServerDlg);
	return true;
}

bool CCfgFrameLogic::OnClickCallSerCfg( const IArgs& args )
{
	SwitchCfgTabWnd(g_strCfgCallSer);
	return true;
}

void CCfgFrameLogic::HideAllWnd()
{
	UIFACTORYMGR_PTR->ShowWindow(g_strCfgCnsDlg, false);
	UIFACTORYMGR_PTR->ShowWindow(g_strCfgAudioPort, false);
	UIFACTORYMGR_PTR->ShowWindow(g_stcStrCfgNetMngDlg, false);
	UIFACTORYMGR_PTR->ShowWindow(g_strCfgMixDlg, false);
	UIFACTORYMGR_PTR->ShowWindow(g_strCfgEqDlg, false);
	UIFACTORYMGR_PTR->ShowWindow(g_strCfgServerDlg, false);
	UIFACTORYMGR_PTR->ShowWindow( g_strCfgCallSer, false );
}

