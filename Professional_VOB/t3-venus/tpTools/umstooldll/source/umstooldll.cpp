// umstooldll.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "umstooldll.h"

#define _NMS_COMMON_CPP_
#include "common.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//
//	Note!
//
//		If this DLL is dynamically linked against the MFC
//		DLLs, any functions exported from this DLL which
//		call into MFC must have the AFX_MANAGE_STATE macro
//		added at the very beginning of the function.
//
//		For example:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// normal function body here
//		}
//
//		It is very important that this macro appear in each
//		function, prior to any calls into MFC.  This means that
//		it must appear as the first statement within the 
//		function, even before any object variable declarations
//		as their constructors may generate calls into the MFC
//		DLL.
//
//		Please see MFC Technical Notes 33 and 58 for additional
//		details.
//

/////////////////////////////////////////////////////////////////////////////
// CUmstooldllApp

BEGIN_MESSAGE_MAP(CUmstooldllApp, CWinApp)
	//{{AFX_MSG_MAP(CUmstooldllApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUmstooldllApp construction

CUmstooldllApp::CUmstooldllApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

BOOL CUmstooldllApp::PreTranslateMessage(MSG* pMsg) 
{
    UIFACTORYMGR_PTR->HandleMsg( pMsg );
    
    return CWinApp::PreTranslateMessage(pMsg);
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CUmstooldllApp object

CUmstooldllApp theApp;
HWND g_hNotifyWnd = NULL;
static BOOL g_bInit = FALSE;

TOOLDLL_API void DestoryUmsToolUI()
{ 
	g_bInit = FALSE;
};

TOOLDLL_API BOOL IsInitUmsTool()
{   
	return g_bInit;
}

TOOLDLL_API void InitUmsTool( HWND hNotifyWnd )
{ 
	AFX_MANAGE_STATE( AfxGetStaticModuleState());
	g_hNotifyWnd = hNotifyWnd;
	if( !g_bInit )
	{
		g_bInit = TRUE;

		//�쳣����
		CString strFullPath = GetModuleFullPath();
		strFullPath += UMSTOOLEXCEPTION_FILE;
		CExceptionCatch::LogToFile( (LPSTR)(LPCSTR)strFullPath );
		CExceptionCatch::Start();  

		//��ʼ��������Ϣ
		UIFACTORYMGR_PTR->InitUIFactory(SYSTEM_UMSTOOL_XML);
		
		SESSIONPTR->CreateSession(AID_UMSTOOL2UMS_APP);//��ʼ������Session
		DATAMGRPTR->CreateDataMgr();

		//��OSPע�᱾ģ��
		ModuleRegToOsp();
		
		DWORD dwProcessId = GetCurrentProcessId();
		TCHAR aszPrompt[32] = "";
		
		sprintf( aszPrompt, "tptool(%d):", dwProcessId );
		OspSetPrompt( aszPrompt );
		
		//��ʼ�����ڹ����߼���Ϣ
		CLogicManage::GetLogicManagePtr()->CreateLogic();
		
		IWndTree* pTree = const_cast<IWndTree*>( UIFACTORYMGR_PTR->GetWindow( g_stcStrMainFrmDlg )); 
		UIFACTORYMGR_PTR->ShowWindow( g_stcStrSysinfoDlg  );
		
		if ( pTree == 0 )
		{
			return;
		}
		
		WndInfo* pInfo = pTree->GetItemData();
		
		CWnd* pMainWnd = AfxGetMainWnd()/*theApp.GetMainWnd()*/;
		
		pMainWnd = pInfo->pWnd ;  
		pMainWnd->SendMessage( WM_REDRAW_UI ,0 ,0 ); 
	}
}

TOOLDLL_API BOOL ConnectToUms(  LPCTSTR strIpAddr, u16 nPort, LPCTSTR pStrUserName, LPCTSTR pStrPswd )
{ 
 	AFX_MANAGE_STATE( AfxGetStaticModuleState());

	//���ӵ�ums������
	u16 nRet = COMMONMGRIFPTR->Connect( htonl(inet_addr(strIpAddr)), nPort, pStrUserName, pStrPswd );
	if ( nRet != NO_ERROR )
	{
		LPCTSTR strErr = "��������ʧ��";
		CUmstoolCommon::NotifyOuterWnd( WM_TPTOOL_LOGINRESULT, em_LOGIN_ERROR_RSQ, LPARAM(strErr));

		return FALSE;
	}

	return TRUE;
};

TOOLDLL_API BOOL /*PASCAL*/ DllPreTranslateMessage(MSG *pMsg)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return theApp.PreTranslateMessage(pMsg);
}

//////////////////////////////////OSP��ӡ����/////////////////////////////////////////////
API void help()
{
    PrtMsg( "\n    showver:                    ��ʾ�汾�ͱ���ʱ��");
	PrtMsg( "\n    prt:                        ��ӡ���м���Ϊ3���ϵ���Ϣ");
	PrtMsg( "\n    prtlevel nLevel:            ��ӡ����ΪnLevel����Ϣ����Ϣ���� 1-3��\n \
                                               1Ϊ������ߵ���Ϣ���ü������Ϣ��ϵͳ���ܲ�������Ӱ��\n \
                                               2Ϊһ�㼶�����Ϣ\n \
                                               3Ϊ��ͼ�����Ϣ " );
	PrtMsg( "\n    stopprt:                    ֹͣ��ӡ");
	PrtMsg( "\n    prtid msgID:                ��ӡ��Ϣ����msgID����Ϣ");
    PrtMsg( "\n    prtrange beginID endID:     ��ӡ��Ϣ�ŷ�Χ�� beginID �� endID ֮�����Ϣ");
    PrtMsg( "\n    prtrecive 0 / 1:            ��ӡ���н��ܵ�����Ϣ, 0:����ӡ��1:��ӡ");
    PrtMsg( "\n    prtsend 0 / 1:              ��ӡ���з��ͳ�ȥ����Ϣ, 0:����ӡ��1:��ӡ");
}

API void showver()
{   
    PrtMsg( "umstool version: %s ", GetUmsToolBuildVersion() ); 
    PrtMsg( "compile time:%s %s", __DATE__, __TIME__ );
}

API void prt()
{
    CPrintCtrl::GetPrintCtrl()->PrintAllMsg();
}


API void prtlevel( u8 byLevel )
{
    CPrintCtrl::GetPrintCtrl()->PrintMsgLevel( byLevel );
}

API void stopprt()
{
	CPrintCtrl::GetPrintCtrl()->StopPrint();
}

API void prtid( u32 msgID )
{
	CPrintCtrl::GetPrintCtrl()->SetPrintMsgID( msgID );
}

API void prtrange( u32 beginID, u32 endID )
{ 
    CPrintCtrl::GetPrintCtrl()->SetPrintMsgRange( beginID, endID ); 
}

API void prtrecive( BOOL bPrint /*= TRUE */ )
{
    CPrintCtrl::GetPrintCtrl()->PrintEnterMsg( bPrint ); 
}

API void prtsend( BOOL bPrint/* = TRUE */)
{
	CPrintCtrl::GetPrintCtrl()->PrintOutMsg( bPrint );
}