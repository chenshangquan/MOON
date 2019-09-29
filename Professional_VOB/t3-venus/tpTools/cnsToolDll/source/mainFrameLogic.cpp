// mainFrameLogic.cpp: implementation of the CMainFrameLogic class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "cnsToolDll.h"
#include "MainFrameLogic.h" 
#include "uidatamgr.h"
#include "CfgCnsLogic.h"
#include "cfgAudioPortLogic.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
//template<> CMainFrameLogic* ISingleTon<CMainFrameLogic>::ms_pSingleton = NULL;

CMainFrameLogic::CMainFrameLogic()
:m_stcStrCnsIp( "StcSvrIP")
{
	m_strLstFunMenu = "LstFuncMenu";
}

CMainFrameLogic::~CMainFrameLogic()
{
 
}

void CMainFrameLogic::RegCBFun()
{
	CMainFrameLogic *pThis =  GetSingletonPtr();

    REG_GOBAL_MEMBER_FUNC( "CMainFrameLogic::InitWnd", CMainFrameLogic::InitWnd, pThis, CMainFrameLogic ) ;
	REG_GOBAL_MEMBER_FUNC( "CMainFrameLogic::OnBtnLogoff", CMainFrameLogic::OnBtnLogoff, pThis, CMainFrameLogic ) ;
	REG_GOBAL_MEMBER_FUNC( "CMainFrameLogic::OnBtnMinmize", CMainFrameLogic::OnBtnMinmize, pThis, CMainFrameLogic ) ;
	REG_GOBAL_MEMBER_FUNC( "CMainFrameLogic::OnBtnTerminalCnstool", CMainFrameLogic::OnBtnTerminalCnstool, pThis, CMainFrameLogic ) ;
	REG_GOBAL_MEMBER_FUNC( "CMainFrameLogic::OnBtnDowloadLog", CMainFrameLogic::OnBtnDowloadLog, pThis, CMainFrameLogic ) ;
	REG_GOBAL_MEMBER_FUNC( "CMainFrameLogic::OnBtnResetSrv", CMainFrameLogic::OnBtnResetSrv, pThis, CMainFrameLogic ) ;
	 
	//���˵���ť�¼�g_strDiagInfoDlg
	REG_LIST_CALLFUNC( "CMainFrameLogic::OnClickCfg", CMainFrameLogic::OnClickCfg, pThis, CMainFrameLogic ) ;
	REG_LIST_CALLFUNC( "CMainFrameLogic::OnClickBaSic", CMainFrameLogic::OnClickBaSic, pThis, CMainFrameLogic ) ;
	REG_LIST_CALLFUNC( "CMainFrameLogic::OnClickDiag", CMainFrameLogic::OnClickDiag, pThis, CMainFrameLogic ) ;	 
	REG_LIST_CALLFUNC( "CMainFrameLogic::OnClickCentCtrl", CMainFrameLogic::OnClickCentCtrl, pThis, CMainFrameLogic ) ;	 
	REG_LIST_CALLFUNC( "CMainFrameLogic::OnClickCamera", CMainFrameLogic::OnClickCamera, pThis, CMainFrameLogic ) ;
	REG_LIST_CALLFUNC( "CMainFrameLogic::OnClickAddrBook", CMainFrameLogic::OnClickAddrBook, pThis, CMainFrameLogic ) ;

}

void CMainFrameLogic::UnRegFunc()
{
	UN_REG_GOBAL_FUNC( "CMainFrameLogic::InitWnd" );
}

bool CMainFrameLogic::InitWnd( const IArgs & arg )
{    
	CLogicBase::InitWnd( arg );
	InitFunMenu();
	UIFACTORYMGR_PTR->ShowWindow( g_strBasicInfoDlg );
	UIFACTORYMGR_PTR->ShowWindow( g_strAddrbookExpDlg, false );	
	UIFACTORYMGR_PTR->ShowWindow( g_strDiagInfoDlg, false );	
	UIFACTORYMGR_PTR->ShowWindow( g_strDiagTestFrame, false );	
	UIFACTORYMGR_PTR->ShowWindow( g_StrCameraDlg, false );		
	UIFACTORYMGR_PTR->ShowWindow( g_stcStrImpCommonDlg, false );	
	UIFACTORYMGR_PTR->ShowWindow( g_strCfgFrame, false );		
	UIFACTORYMGR_PTR->ShowWindow( g_stcStrExpCommonDlg, false );	
	UIFACTORYMGR_PTR->ShowWindow( g_strCentCfgFrame, false );
	UIFACTORYMGR_PTR->ShowWindow( g_stcMsgboxDlg, false );		
	UIFACTORYMGR_PTR->ShowWindow( g_strWarningDlg );		
	m_strCurWnd = g_strBasicInfoDlg;
	return true;
}

void CMainFrameLogic::Clear()
{
	UIDATAMGR_PTR->NotifyOuterWnd( WM_TPTOOL_LOGINRESULT, em_LOGIN_LOGOFF, 0 );
	UIFACTORYMGR_PTR->ShowWindow( g_strMainFrame, false );
	
	if ( m_pWndTree != NULL )
	{		
		UIFACTORYMGR_PTR->LoadScheme( "SchmNormal", m_pWndTree );
		UIFACTORYMGR_PTR->LoadScheme( "SchmMenuListDefault", m_pWndTree );   //��½���ʼ��������Ϣҳ��
	}
}

void CMainFrameLogic::RegMsg()
{
	CMainFrameLogic *m_pThis =  GetSingletonPtr();
	REG_MSG_HANDLER( UI_CNS_CONNECTED, CMainFrameLogic::OnConnectRsp, m_pThis, CMainFrameLogic );
	REG_MSG_HANDLER( UI_CNS_DISCONNECTED, CMainFrameLogic::OnDisConnect, m_pThis, CMainFrameLogic );
	REG_MSG_HANDLER( UI_UMS_GRAB_LOGIN_NOTIFY, CMainFrameLogic::OnGrabLoginNty, m_pThis, CMainFrameLogic );
	REG_MSG_HANDLER( UI_CNS_LOGIN_TIMEOUT, CMainFrameLogic::OnLoginTimeOut, m_pThis, CMainFrameLogic );
}

void CMainFrameLogic::UnRegMsg()
{
	
}
 

bool CMainFrameLogic::OnBtnLogoff( const IArgs& args )
{ 
	s32 nRe = IsCfgChange();	
	if ( nRe == 0 )
 	{
		MSGBOX_RET nMsgBoxRet = MSGBOX_CANCEL;
		MSG_BOX( nMsgBoxRet, "�Ƿ�ע����ǰϵͳ��" );
		if ( MSGBOX_OK == nMsgBoxRet )
		{
			//�Ͽ�cns
			COMIFMGRPTR->DisConnect();
			UIFACTORYMGR_PTR->HideAllWindow();
			LOGICMGR_PTR->DestroyLogic();
			//����cnstool����ʾ��¼���� 		
			UIDATAMGR_PTR->NotifyOuterWnd( WM_TPTOOL_LOGINRESULT, em_LOGIN_LOGOFF, 0 );		
		}
	}
	else
	{
		MSG_BOX_OK( "���������޸ģ����ȱ����޸ĺ���ע����" );
	}
	return true;
}

bool CMainFrameLogic::OnBtnMinmize( const IArgs& args )
{   
	UIFACTORYMGR_PTR->MinmizeWnd(); 
	return true;
}


bool CMainFrameLogic::OnBtnTerminalCnstool( const IArgs& args )
{   
	//2013.10.30  jyy �رճ������������޸�,���ȡ���˳�����,������治�����������˳�����(̨�������Լ��ϴ���Ҫʱ��)
 	s32 nRe = IsCfgChange();	
 	if ( nRe == 0 )
 	{
		MSGBOX_RET nMsgBoxRet = MSGBOX_CANCEL;
		MSG_BOX( nMsgBoxRet, "�Ƿ��˳���ǰϵͳ��" );
		if ( MSGBOX_OK == nMsgBoxRet )
		{
			if ( !UIDATAMGR_PTR->NotifyOuterWnd(WM_CLOSE, 0, 0) )
			{
				UINT uExitCode = 0; 
				ExitProcess( uExitCode );
			}
		}
 	}
	else
	{
// 		MSGBOX_RET nMsgBoxRet = MSGBOX_CANCEL;
// 		MSG_BOX( nMsgBoxRet, "���������޸ģ����ȱ����޸ĺ����˳���" );
// 		if ( MSGBOX_OK != nMsgBoxRet )
// 		{
// 			if ( !UIDATAMGR_PTR->NotifyOuterWnd(WM_CLOSE, 0, 0) )
// 			{
// 				UINT uExitCode = 0; 
// 				ExitProcess( uExitCode );
// 			}
// 		}
		MSG_BOX_OK( "���������޸ģ����ȱ����޸ĺ����˳���" );
	}
// 	else if ( nRe == 1 )
// 	{
// 		if ( !UIDATAMGR_PTR->NotifyOuterWnd(WM_CLOSE, 0, 0) )
// 		{
// 			UINT uExitCode = 0; 
// 			ExitProcess( uExitCode );
// 		}
// 	}
	return true;
} 

bool CMainFrameLogic::OnBtnDowloadLog( const IArgs& args )
{
	UIFACTORYMGR_PTR->LoadScheme( "SchmExpCommonClean", NULL, g_stcStrExpCommonDlg );
	UIFACTORYMGR_PTR->LoadScheme( "SchLogDownload", NULL, g_stcStrExpCommonDlg );
	s32 nDodalResult = UIFACTORYMGR_PTR->Domodal( g_stcStrExpCommonDlg );	
	
	return true;
}

bool CMainFrameLogic::OnBtnResetSrv( const IArgs& args )
{
 	s32 nRe = IsCfgChange();		//2013.10.23  jyy��������ڼ���������޸�,����᳡�����漰̨�������Լ��ϴ�,���ֵ����ⲻ�ý��
 	if ( nRe == 0 )
 	{
		MSGBOX_RET nMsgBoxRet = MSGBOX_CANCEL;
		MSG_BOX( nMsgBoxRet, "�Ƿ�������" );
		if ( MSGBOX_OK == nMsgBoxRet )
		{
			u16 wRet = COMIFMGRPTR->RebootCns();
			if ( wRet != NO_ERROR )
			{
				WARNMESSAGE( "����cns������ʧ��" );
			}
		}
 	} 
	else
	{
// 		MSGBOX_RET nMsgBoxRet = MSGBOX_CANCEL;
// 		MSG_BOX( nMsgBoxRet, "���������޸ģ����ȱ����޸ĺ���������" );
// 		if ( MSGBOX_OK != nMsgBoxRet )
// 		{
// 			u16 wRet = COMIFMGRPTR->RebootCns();
// 			if ( wRet != NO_ERROR )
// 			{
// 				WARNMESSAGE( "����cns������ʧ��" );
// 			}
// 		}
		MSG_BOX_OK( "���������޸ģ����ȱ����޸ĺ���������" );
	}
// 	else if ( nRe == 1 )
// 	{
// 		u16 wRet = COMIFMGRPTR->RebootCns();
// 		if ( wRet != NO_ERROR )
// 		{
// 			WARNMESSAGE( "����cns������ʧ��" );
// 		}
// 	}

	return true;
}

HRESULT CMainFrameLogic::OnConnectRsp( WPARAM wparam, LPARAM lparam )
{
	if (TRUE == wparam)
	{
		u32 dwIp;
		LIBDATAMGRPTR->GetLoginIp(dwIp);
		String strIp = TransformIp(dwIp); 
		UIFACTORYMGR_PTR->ShowWindow( g_strMainFrame, true );
		//�����½��ʼ������Զ��ʾ�ڻ�����Ϣ����   2013.4.3 --JYY
		SwitchCfgTabWnd(g_strBasicInfoDlg);
		UIDATAMGR_PTR->SetLstSelItem( m_strLstFunMenu, m_pWndTree, 0 );
		
		UIFACTORYMGR_PTR->SetCaption( m_stcStrCnsIp, strIp, m_pWndTree, TRUE );

		UIDATAMGR_PTR->NotifyOuterWnd( WM_TPTOOL_LOGINRESULT, em_LOGIN_SUCCESS, 0 );		
		Window* pWndMain = UIFACTORYMGR_PTR->GetWindowPtr( g_strMainFrame );
		if ( NULL != pWndMain )
		{
			pWndMain->CenterWindow();
		}
	}
	else
	{
		LPCTSTR strErr;

		switch( lparam )
		{
		case ERR_UMC_LOGIN_UMS_USER_ERR:
			strErr = "�û�������";
			break;
		case ERR_UMC_LOGIN_UMS_PSWD_ERR:
			strErr = "�������";
			break;
		case ERR_UMC_LOGIN_UMS_MAX_LOGIN:
			strErr = "�Ѵ��¼�û������";
			break;
		case ERR_UMC_LOGIN_UMS_LOGED:
			strErr = "��ǰ�û��ѵ�¼";
			break;
		case ERR_UMC_LOGIN_UMS_SYSINITING:
			strErr = "��ǰϵͳ���ڳ�ʼ�������Ժ�";
			break;
		case ERR_CNC_TCPCONNECT:
			strErr = "��������ʧ��";
			break;
		case ERR_UMC_LOGIN_FAIL:
			strErr = "��½ʧ��";
			break;
		}
		UIDATAMGR_PTR->NotifyOuterWnd( WM_TPTOOL_LOGINRESULT, em_LOGIN_ERROR_RSQ, LPARAM(strErr));
	}	
	return S_OK;
}

HRESULT CMainFrameLogic::OnDisConnect( WPARAM wparam, LPARAM lparam )
{  
	LOGICMGR_PTR->DestroyLogic();
	//if ( UIFACTORYMGR_PTR->IsVisible( g_strMainFrame ) )
	UIFACTORYMGR_PTR->HideAllWindow();
	//LPCTSTR strErr = "";  
	UIDATAMGR_PTR->NotifyOuterWnd( WM_TPTOOL_LOGINRESULT, em_LOGIN_BREAK, NULL/*LPARAM(strErr)*/);
		
	//UIDATAMGR_PTR->NotifyOuterWnd( WM_TPTOOL_LOGOFF, 1, 0 );

	return S_OK;
}

String CMainFrameLogic::TransformIp(u32 dwIp)
{
	struct in_addr addr1;
	addr1.s_addr =  ntohl(dwIp);
	String strIP = inet_ntoa(addr1);
	return strIP;
}

void CMainFrameLogic::InitFunMenu()
{
	ARRAY<TMenuItem> aryItem;
	TMenuItem item; 

	item.SetItemName("������Ϣ" );  
	item.SetItemType("ImageItemMenuGenerInfo");
	aryItem.push_back(item);
	

	item.SetItemName("�������" ); 
	item.SetItemType("ImageItemMenuCfg");
	aryItem.push_back(item);


	item.SetItemName("��ϲ���" );  
	item.SetItemType("ImageItemMenuDiag");
	aryItem.push_back(item);

	item.SetItemName("��ַ��" );  
	item.SetItemType("ImageItemMenuAddr");
	aryItem.push_back(item);

	item.SetItemName("���������" ); 
	item.SetItemType("ImageItemMenuCam");
	aryItem.push_back(item);

	item.SetItemName("�п�" );  
	item.SetItemType("ImageItemMenuCentCtrl"); 
	aryItem.push_back(item);


	Value_ItemMenu valueMenu( &aryItem ); 
	UIFACTORYMGR_PTR->SetPropertyValue( valueMenu, m_strLstFunMenu, m_pWndTree ); 

}

bool CMainFrameLogic::OnClickBaSic( const IArgs& args )
{
	SwitchCfgTabWnd(g_strBasicInfoDlg);
	return true;
}

bool CMainFrameLogic::OnClickCfg( const IArgs& args )
{   
	SwitchCfgTabWnd(g_strCfgFrame);
	return true;
}

bool CMainFrameLogic::OnClickDiag( const IArgs& args )
{	
	SwitchCfgTabWnd(g_strDiagInfoDlg);
	return true;
}

bool CMainFrameLogic::OnClickCentCtrl( const IArgs& args )
{
	SwitchCfgTabWnd(g_strCentCfgFrame);
	return true;
}

bool CMainFrameLogic::OnClickCamera( const IArgs& args )
{
	SwitchCfgTabWnd(g_StrCameraDlg);	
	return true;
}

bool CMainFrameLogic::OnClickAddrBook( const IArgs& args )
{
	SwitchCfgTabWnd(g_strAddrbookExpDlg);
	return true;
}

HRESULT CMainFrameLogic::OnGrabLoginNty( WPARAM wparam, LPARAM lparam )
{
// 	u32 dwIP = (u32)wparam;
//     in_addr tAddr;
//     tAddr.S_un.S_addr =  dwIP ; 
//     CString CMsg;
//     CMsg.Format("���Ѿ���ǿ�����ߣ����˻�%s������һ���ط���¼", inet_ntoa(tAddr));
// 	String msg = LPCSTR(CMsg);
// 	MSG_BOX_OK( msg );
	COMIFMGRPTR->DisConnect();
	UIFACTORYMGR_PTR->HideAllWindow();
	LOGICMGR_PTR->DestroyLogic();
	UIDATAMGR_PTR->NotifyOuterWnd( WM_TPTOOL_LOGINRESULT , em_LOGIN_GRAP, (LPARAM)wparam );
//	UIDATAMGR_PTR->NotifyOuterWnd( WM_TPTOOL_LOGOFF, 1, 0 );	
	return S_OK;
}

void CMainFrameLogic::SwitchCfgTabWnd( string strWnd )
{
	if ( m_strCurWnd == g_strCfgCnsDlg && strWnd != g_strCfgCnsDlg )
	{
		bool bChange = CCfgCnsLogic::GetSingletonPtr()->IsCfgCnsChange();
		if ( false == bChange )
		{
			UIDATAMGR_PTR->SetLstSelItem( m_strLstFunMenu, m_pWndTree, 1 );
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
			UIDATAMGR_PTR->SetLstSelItem( m_strLstFunMenu, m_pWndTree, 1 );
			return;
		}
	}
	
	if ( m_strCurWnd == g_strCfgAudioPort && strWnd != g_strCfgAudioPort )
	{
		bool bChange = CCfgAudioPortLogic::GetSingletonPtr()->IsCfgAudioChange();
		if ( false == bChange )
		{
			UIDATAMGR_PTR->SetLstSelItem( m_strLstFunMenu, m_pWndTree, 1 );
			return;
		}
	}
	
	if ( m_strCurWnd == g_strCfgMixDlg && strWnd != g_strCfgMixDlg )
	{
		bool bChange = CCfgMixLogic::GetSingletonPtr()->IsCfgMixChange();
		if ( false == bChange )
		{
			UIDATAMGR_PTR->SetLstSelItem( m_strLstFunMenu, m_pWndTree, 1 );
			return;
		}
	}
	
	if ( m_strCurWnd == g_strCfgEqDlg && strWnd != g_strCfgEqDlg )
	{
		bool bChange = CCfgEqLogic::GetSingletonPtr()->IsCfgEqChange();
		if ( false == bChange )
		{
			UIDATAMGR_PTR->SetLstSelItem( m_strLstFunMenu, m_pWndTree, 1 );
			return;
		}	
	}
	
	if ( m_strCurWnd == g_strCentDisplayDlg && strWnd != g_strCentDisplayDlg )
	{
		bool bChange = CCentCfgDisplayDlg::GetSingletonPtr()->IsCentCfgDisplayChange();
		if ( false == bChange )
		{
			UIDATAMGR_PTR->SetLstSelItem( m_strLstFunMenu, m_pWndTree, 5 );
			return;
		}	
	}
	
	if ( m_strCurWnd != g_strCfgFrame && strWnd == g_strCfgFrame )
	{
		m_strCurWnd = CCfgFrameLogic::GetSingletonPtr()->m_strCfgCurWnd;
		HideAllWnd();
		UIFACTORYMGR_PTR->ShowWindow(strWnd);
		CCfgFrameLogic::GetSingletonPtr()->HideAllWnd();
		UIFACTORYMGR_PTR->ShowWindow(m_strCurWnd);
		return;
	}

	if ( m_strCurWnd != g_strCentCfgFrame && strWnd == g_strCentCfgFrame )
	{
		m_strCurWnd = CCentCfgFrameLogic::GetSingletonPtr()->m_strCfgCurWnd;
		HideAllWnd();
		UIFACTORYMGR_PTR->ShowWindow(strWnd);
		CCentCfgFrameLogic::GetSingletonPtr()->HideAllWnd();
		UIFACTORYMGR_PTR->ShowWindow(m_strCurWnd);
		return;
	}

	HideAllWnd();
	UIFACTORYMGR_PTR->ShowWindow(strWnd);
	m_strCurWnd = strWnd;
}

void CMainFrameLogic::HideAllWnd()
{
	UIFACTORYMGR_PTR->ShowWindow( g_strCfgFrame, false );
	UIFACTORYMGR_PTR->ShowWindow( g_strBasicInfoDlg, false );
	UIFACTORYMGR_PTR->ShowWindow( g_strDiagInfoDlg, false );
	UIFACTORYMGR_PTR->ShowWindow( g_strCentCfgFrame, false );
	UIFACTORYMGR_PTR->ShowWindow( g_StrCameraDlg, false );
	UIFACTORYMGR_PTR->ShowWindow( g_strAddrbookExpDlg, false );
}

HRESULT CMainFrameLogic::OnLoginTimeOut( WPARAM wparam, LPARAM lparam )
{
//	UIFACTORYMGR_PTR->HideAllWindow();
//	LPCTSTR strErr = "���ӷ�������ʱ";  
	UIDATAMGR_PTR->NotifyOuterWnd( WM_TPTOOL_LOGINRESULT, em_LOGIN_TIMEOUT, NULL/*LPARAM(strErr)*/ );
	
//	UIDATAMGR_PTR->NotifyOuterWnd( WM_TPTOOL_LOGOFF, 1, 0 );
	
	return S_OK;
}

s32 CMainFrameLogic::IsCfgChange()
{
	bool bChange = false;
	s32 bFlag = 0;
	s32 n = 0;
	if ( m_strCurWnd == g_strCfgCnsDlg )
	{
		/*s32*/ n = CCfgCnsLogic::GetSingletonPtr()->GetCtrlChangeNum();
		if ( n > 0 )
		{
			//bChange = CCfgCnsLogic::GetSingletonPtr()->IsCfgCnsChange();
			if ( bChange )
			{
				bFlag = 1;
			} 
			else
			{
				bFlag = 2;
			}
		} 
	}
	else if ( m_strCurWnd == g_strCfgServerDlg )
	{
		/*s32*/ n = CCfgServerLogic::GetSingletonPtr()->GetCtrlChangeNum();
		if ( n > 0 )
		{
			//bChange = CCfgServerLogic::GetSingletonPtr()->IsCfgSerChange();
			if ( bChange )
			{
				bFlag = 1;
			} 
			else
			{
				bFlag = 2;
			}
		} 
	}
	else if ( m_strCurWnd == g_strCfgAudioPort )
	{
		/*s32*/ n = CCfgAudioPortLogic::GetSingletonPtr()->GetCtrlChangeNum();
		if ( n > 0 )
		{
			//bChange = CCfgAudioPortLogic::GetSingletonPtr()->IsCfgAudioChange();
			if ( bChange )
			{
				bFlag = 1;
			} 
			else
			{
				bFlag = 2;
			}
		} 
	}
	else if ( m_strCurWnd == g_strCfgMixDlg )
	{
		/*s32*/ n = CCfgMixLogic::GetSingletonPtr()->GetCtrlChangeNum();
		if ( n > 0 )
		{
			//bChange = CCfgMixLogic::GetSingletonPtr()->IsCfgMixChange();
			if ( bChange )
			{
				bFlag = 1;
			} 
			else
			{
				bFlag = 2;
			}
		} 
	}
	else if ( m_strCurWnd == g_strCfgEqDlg )
	{
		/*s32*/ n = CCfgEqLogic::GetSingletonPtr()->GetCtrlChangeNum();
		if ( n > 0 )
		{
			//bChange = CCfgEqLogic::GetSingletonPtr()->IsCfgEqChange();
			if ( bChange )
			{
				bFlag = 1;
			} 
			else
			{
				bFlag = 2;
			}
		} 
	}
	else if ( m_strCurWnd == g_strCentDisplayDlg )
	{
		/*s32*/ n = CCentCfgDisplayDlg::GetSingletonPtr()->GetCtrlChangeNum();
		if ( n > 0 )
		{
			//bChange = CCfgEqLogic::GetSingletonPtr()->IsCfgEqChange();
			if ( bChange )
			{
				bFlag = 1;
			} 
			else
			{
				bFlag = 2;
			}
		} 
	}

	return /*bFlag*/n;
}
