// mainFrameLogic.cpp: implementation of the CMainFrameLogic class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "moonToolDll.h"
#include "MainFrameLogic.h" 
#include "SysCfgDlgLogic.h"
#include "uidatamgr.h"
#include "common.h"

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
:m_stcStrMoonIp( "StcSvrIP")
,m_stcStcCprt( "StcCprt" )
,m_stcTitle("StcTitle")
{
	m_strLstFunMenu = "LstFuncMenu";
	m_byIndex = 0;
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
	REG_GOBAL_MEMBER_FUNC( "CMainFrameLogic::OnBtnRestore", CMainFrameLogic::OnBtnRestore, pThis, CMainFrameLogic ) ;
	REG_GOBAL_MEMBER_FUNC( "CMainFrameLogic::OnBtnUpdate", CMainFrameLogic::OnBtnUpdate, pThis, CMainFrameLogic ) ;
	REG_GOBAL_MEMBER_FUNC( "CMainFrameLogic::OnBtnReboot", CMainFrameLogic::OnBtnReboot, pThis, CMainFrameLogic ) ;
		 
	//���˵���ť�¼�g_strDiagInfoDlg
	REG_LIST_CALLFUNC( "CMainFrameLogic::OnClickMonAdjust", CMainFrameLogic::OnClickMonAdjust, pThis, CMainFrameLogic ) ;
	REG_LIST_CALLFUNC( "CMainFrameLogic::OnClickCamCtrl", CMainFrameLogic::OnClickCamCtrl, pThis, CMainFrameLogic ) ;
	REG_LIST_CALLFUNC( "CMainFrameLogic::OnClickSysCfg", CMainFrameLogic::OnClickSysCfg, pThis, CMainFrameLogic ) ;	 
}

void CMainFrameLogic::UnRegFunc()
{
	UN_REG_GOBAL_FUNC( "CMainFrameLogic::InitWnd" );
}

bool CMainFrameLogic::InitWnd( const IArgs & arg )
{    
	CLogicBase::InitWnd( arg );
	InitFunMenu();
	UIFACTORYMGR_PTR->ShowWindow( g_strCamCtrlDlg );
	UIFACTORYMGR_PTR->ShowWindow( g_strMoonAdjustDlg, false );
	UIFACTORYMGR_PTR->ShowWindow( g_strSysCfgDlg, false );	
	UIFACTORYMGR_PTR->ShowWindow( g_stcMsgboxDlg, false );
	UIFACTORYMGR_PTR->ShowWindow( g_strOrderListDlg, false );
	UIFACTORYMGR_PTR->ShowWindow( g_stcStrImpCommonDlg, false );
	UIFACTORYMGR_PTR->ShowWindow( g_stcStrExpCommonDlg, false );
	UIFACTORYMGR_PTR->ShowWindow( g_stcStrOrderPosInfoDlg, false );
	UIFACTORYMGR_PTR->ShowWindow( g_stcStrCorrectParamDlg, false );
	UIFACTORYMGR_PTR->ShowWindow( g_stcStrSetContrastAreaDlg, false );
	UIFACTORYMGR_PTR->ShowWindow( g_strWarningDlg );		
	m_strCurWnd = g_strCamCtrlDlg;
	m_byIndex = 0;
	UIFACTORYMGR_PTR->SetCaption( m_stcStcCprt, GetMoonToolBuildVersion(), m_pWndTree );
	return true;
}

void CMainFrameLogic::Clear()
{
	UIDATAMGR_PTR->NotifyOuterWnd( WM_TPTOOL_LOGINRESULT, em_LOGIN_LOGOFF, 0 );
	UIFACTORYMGR_PTR->ShowWindow( g_strMoonMainFrame, false );
//	m_VecCurMenuItem = m_VecOldMenuItem;
	if ( m_pWndTree != NULL )
	{		
		UIFACTORYMGR_PTR->LoadScheme( "SchmNormal", m_pWndTree );
		UIFACTORYMGR_PTR->LoadScheme( "SchmMenuListDefault", m_pWndTree );   //��½���ʼ��������Ϣҳ��
	}
}

void CMainFrameLogic::RegMsg()
{
	CMainFrameLogic *m_pThis =  GetSingletonPtr();
	REG_MSG_HANDLER( UI_MOONTOOL_CONNECTED, CMainFrameLogic::OnConnectRsp, m_pThis, CMainFrameLogic );
	REG_MSG_HANDLER( UI_CNS_DISCONNECTED, CMainFrameLogic::OnDisConnect, m_pThis, CMainFrameLogic );
	REG_MSG_HANDLER( UI_UMS_GRAB_LOGIN_NOTIFY, CMainFrameLogic::OnGrabLoginNty, m_pThis, CMainFrameLogic );
	REG_MSG_HANDLER( UI_CNS_LOGIN_TIMEOUT, CMainFrameLogic::OnLoginTimeOut, m_pThis, CMainFrameLogic );
	REG_MSG_HANDLER( UI_MOONTOOL_VERINFO_NTY, CMainFrameLogic::OnProductModelNty, m_pThis, CMainFrameLogic );

	//����Ԥ��λ�б�ҳ�棬֪ͨ���������������˵���
	REG_MSG_HANDLER( UI_MOONTOOL_LISTMENU_OPTION, CMainFrameLogic::OnListMenuShow, m_pThis, CMainFrameLogic );
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
		MSG_BOX_OK( "���������޸ģ����ȱ����޸ĺ����˳���" );
	}
// 	else
// 	{
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
// 		MSG_BOX_OK( "���������޸ģ����ȱ����޸ĺ����˳���" );
// 	}
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

HRESULT CMainFrameLogic::OnConnectRsp( WPARAM wparam, LPARAM lparam )
{
	if (TRUE == wparam)
	{
		u32 dwIp;
		MOONLIBDATAMGRPTR->GetLoginIp(dwIp);
		String strIp = TransformIp(dwIp); 
		UIFACTORYMGR_PTR->ShowWindow( g_strMoonMainFrame, true );
		//�����½��ʼ������Զ��ʾ�ڻ�����Ϣ����   2013.4.3 --JYY
		SwitchCfgTabWnd(g_strCamCtrlDlg);
		UIDATAMGR_PTR->SetLstSelItem( m_strLstFunMenu, m_pWndTree, 0 );
		
		UIFACTORYMGR_PTR->SetCaption( m_stcStrMoonIp, strIp, m_pWndTree, TRUE );

		UIDATAMGR_PTR->NotifyOuterWnd( WM_TPTOOL_LOGINRESULT, em_LOGIN_SUCCESS, 0 );		
		Window* pWndMain = UIFACTORYMGR_PTR->GetWindowPtr( g_strMoonMainFrame );
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
	TMenuItem item; 
	
	item.SetItemName("�������" );  
	item.SetItemType("ImageItemCamCtrl");
	m_VecOldMenuItem.push_back(item);
	
 	/*item.SetItemName("ƴ�ӵ���" ); 
 	item.SetItemType("ImageItemMonAdjust");
 	m_VecOldMenuItem.push_back(item);*/

	item.SetItemName("ϵͳ����" );  
	item.SetItemType("ImageItemSysCfg");
	m_VecOldMenuItem.push_back(item);

//	m_VecCurMenuItem = m_VecOldMenuItem;
	Value_ItemMenu valueMenu( &m_VecOldMenuItem ); 
	UIFACTORYMGR_PTR->SetPropertyValue( valueMenu, m_strLstFunMenu, m_pWndTree ); 

}

bool CMainFrameLogic::OnClickCamCtrl( const IArgs& args )
{
	SwitchCfgTabWnd(g_strCamCtrlDlg);
	m_byIndex = 0;
//	UIFACTORYMGR_PTR->ShowWindow( g_strCamCtrlDlg, true );
	return true;
}

bool CMainFrameLogic::OnClickMonAdjust( const IArgs& args )
{   
	SwitchCfgTabWnd(g_strMoonAdjustDlg);
	m_byIndex = 1;
	return true;
}

bool CMainFrameLogic::OnClickSysCfg( const IArgs& args )
{	
	SwitchCfgTabWnd(g_strSysCfgDlg);
	m_byIndex = 2;
	UIFACTORYMGR_PTR->ShowWindow( g_strSysCfgDlg, true );
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
//	LOGICMGR_PTR->DestroyLogic();
	UIDATAMGR_PTR->NotifyOuterWnd( WM_TPTOOL_LOGINRESULT , em_LOGIN_GRAP, (LPARAM)wparam );
//	UIDATAMGR_PTR->NotifyOuterWnd( WM_TPTOOL_LOGOFF, 1, 0 );	
	return S_OK;
}

void CMainFrameLogic::HideAllWnd()
{
	UIFACTORYMGR_PTR->ShowWindow( g_strCamCtrlDlg, false );
	UIFACTORYMGR_PTR->ShowWindow( g_strMoonAdjustDlg, false );
	UIFACTORYMGR_PTR->ShowWindow( g_strSysCfgDlg, false );
	UIFACTORYMGR_PTR->ShowWindow( g_strOrderListDlg, false );
}

HRESULT CMainFrameLogic::OnLoginTimeOut( WPARAM wparam, LPARAM lparam )
{
//	UIFACTORYMGR_PTR->HideAllWindow();
//	LPCTSTR strErr = "���ӷ�������ʱ";  
	UIDATAMGR_PTR->NotifyOuterWnd( WM_TPTOOL_LOGINRESULT, em_LOGIN_TIMEOUT, NULL/*LPARAM(strErr)*/ );
	
//	UIDATAMGR_PTR->NotifyOuterWnd( WM_TPTOOL_LOGOFF, 1, 0 );
	
	return S_OK;
}

bool CMainFrameLogic::OnBtnRestore( const IArgs& args )
{
	if ( m_pWndTree == NULL )
	{
		return false;
	}

	if( m_byIndex == 2 )
	{
		return false;
	}

	u16 nRet = COMIFMGRPTR->MoonCamResetCmd( m_byIndex );
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "�ָ�Ĭ��������ʧ��" );
		return true;
	}
	
//	MSG_BOX_ONLY_READ( _T("���ڻָ�Ĭ��ֵ�����Եȣ������������ʱ�޷�����") );

	return true;	
}

bool CMainFrameLogic::OnBtnUpdate( const IArgs& args )
{
	s32 nRe = IsCfgChange();		
	if ( nRe == 0 )
 	{
		UIFACTORYMGR_PTR->LoadScheme( "SchmImpCommonClean", NULL, g_stcStrImpCommonDlg );
		UIFACTORYMGR_PTR->LoadScheme( "SchUpgradeMoon", NULL, g_stcStrImpCommonDlg );
		s32 nDodalResult = UIFACTORYMGR_PTR->Domodal( g_stcStrImpCommonDlg );
	}
	else
	{
		MSG_BOX_OK( "���������޸ģ����ȱ����޸ĺ���������" );
	}
	return true;	
}

bool CMainFrameLogic::OnBtnReboot( const IArgs& args )
{
	s32 nRe = IsCfgChange();		//2013.10.23  jyy��������ڼ���������޸�,����᳡�����漰̨�������Լ��ϴ�,���ֵ����ⲻ�ý��
	if ( nRe == 0 )
 	{
		MSGBOX_RET nMsgBoxRet = MSGBOX_CANCEL;
		MSG_BOX( nMsgBoxRet, "�Ƿ�������������" );
		if ( MSGBOX_OK == nMsgBoxRet )
		{
			u16 wRet = COMIFMGRPTR->RebootMoon();
			if ( wRet != NO_ERROR )
			{
				WARNMESSAGE( "����moon90������ʧ��" );
			}
		}
	}
	else
	{
		MSG_BOX_OK( "���������޸ģ����ȱ����޸ĺ���������" );
	}

	return true;	
}

HRESULT CMainFrameLogic::OnListMenuShow( WPARAM wparam, LPARAM lparam )
{
	EM_MENULISTOPT_TYPE emMenuListOptType = static_cast<EM_MENULISTOPT_TYPE>(lparam);

	if ( emMenuListOptType == em_MENULIST_HIDE )
	{
		UIFACTORYMGR_PTR->LoadScheme( "SchmMenuListHide", m_pWndTree );
	}
	if ( emMenuListOptType == em_MENULIST_SHOW )
	{
		UIFACTORYMGR_PTR->LoadScheme( "SchmMenuListShow", m_pWndTree );
	}

	return S_OK;	
}

void CMainFrameLogic::SwitchCfgTabWnd( string strWnd )
{
	if ( m_strCurWnd == g_strSysCfgDlg && strWnd != g_strSysCfgDlg )
	{
		bool bChange = CSysCfgDlgLogic::GetSingletonPtr()->IsCfgCnsChange();
		if ( false == bChange )
		{
			UIDATAMGR_PTR->SetLstSelItem( m_strLstFunMenu, m_pWndTree, 1 );
			return;
		}
	}
	HideAllWnd();
	UIFACTORYMGR_PTR->ShowWindow(strWnd);
	m_strCurWnd = strWnd;	
}

s32 CMainFrameLogic::IsCfgChange()
{
	bool bChange = false;
	s32 bFlag = 0;
	s32 n = 0;
	if ( m_strCurWnd == g_strSysCfgDlg )
	{
		/*s32*/ n = CSysCfgDlgLogic::GetSingletonPtr()->GetCtrlChangeNum();
		if ( n > 0 )
		{
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

HRESULT CMainFrameLogic::OnProductModelNty( WPARAM wparam, LPARAM lparam )
{
	EmTpVer emMoonVer = *(EmTpVer*)lparam;
	if ( emMoonVer == tp_Ver_MOON90 )
	{
		UIFACTORYMGR_PTR->SetCaption(m_stcTitle,"Moon 90",m_pWndTree);
	}
	else if( emMoonVer == tp_Ver_MOON90H )
	{
		UIFACTORYMGR_PTR->SetCaption(m_stcTitle,"Moon 90H",m_pWndTree);
	}
/*	TMenuItem item; 
	
	item.SetItemName("ƴ�ӵ���" ); 
	item.SetItemType("ImageItemMonAdjust");

	UpdateTabList(item,FALSE);
	Value_ItemMenu valueMenu( &m_VecCurMenuItem ); 
	valueMenu.m_strAlgroithm = IAlgorithm::strHori;

	Value_WindowSize TabListWndSize;
	TabListWndSize.
	UIFACTORYMGR_PTR->SetPropertyValue( TabListWndSize, m_strLstFunMenu, m_pWndTree );
	UIFACTORYMGR_PTR->SetPropertyValue( valueMenu, m_strLstFunMenu, m_pWndTree );*/

	return S_OK;
}

void CMainFrameLogic::UpdateTabList( TMenuItem item ,BOOL bAdd )
{
	ARRAY<TMenuItem> vecItem;
	
	if ( bAdd == FALSE )				//ɾ���б���
	{
		for ( vector<TMenuItem>::iterator iterCur =m_VecCurMenuItem.begin(); iterCur != m_VecCurMenuItem.end(); iterCur++ )
		{
			if ( strcmp(item.szName,iterCur->szName) == 0 )	
			{
				m_VecCurMenuItem.erase(iterCur);
				break;
			}
		}
	}
	else
	{
		for ( vector<TMenuItem>::iterator iter = m_VecCurMenuItem.begin() ; iter !=m_VecCurMenuItem.end(); iter++ )	//	�ж��Ƿ����
		{
			if ( strcmp(item.szName,iter->szName) == 0 )
			{
				return;
			}
		}
		vector<TMenuItem>::iterator iterTemp = m_VecCurMenuItem.begin();
		vector<TMenuItem>::iterator iterCur = m_VecCurMenuItem.begin() ;
		
		for ( vector<TMenuItem>::iterator iterOld =m_VecOldMenuItem.begin(); iterOld != m_VecOldMenuItem.end(); iterOld++ )
		{
			if ( strcmp(item.szName,iterOld->szName) == 0 )				//��������ӵ���͵�ǰ��������ƥ�䣬���ӵ���ʱ������
			{
				m_VecCurMenuItem.insert(iterTemp,*iterOld);				//���뵽ƥ�����һ�������λ����
				break;
			}
			else																//������Ҫ���ӵ��б���
			{
				for ( ; iterCur !=m_VecCurMenuItem.end(); iterCur++ )			//��⵱ǰ�б���Ƿ������ITEM
				{
					if ( strcmp( iterCur->szName,iterOld->szName ) == 0)
					{
						iterCur++;
						iterTemp = iterCur;									//�ҵ��ˣ��´α�������һ����ʼ
						break;
					}
				}
				
				if ( iterCur == m_VecCurMenuItem.end() )					//��ǰӦ�õ��б���û�и��� ���ϴ�ƥ��ĺ�һ�ʼ
				{
					iterCur = iterTemp;
				}
			}
		}
	}
}