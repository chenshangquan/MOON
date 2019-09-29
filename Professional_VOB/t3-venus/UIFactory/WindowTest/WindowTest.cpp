// WindowTest.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "WindowTest.h"
#include "WindowTestDlg.h"
#include "LogicTest.h"
#include "WndFactory.h"
#include "TestLog.h"
#include "WndTreeHelp.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWindowTestApp

BEGIN_MESSAGE_MAP(CWindowTestApp, CWinApp)
	//{{AFX_MSG_MAP(CWindowTestApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWindowTestApp construction

CWindowTestApp::CWindowTestApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CWindowTestApp object

CWindowTestApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CWindowTestApp initialization

BOOL CWindowTestApp::InitInstance()
{
	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

// 	GdiplusStartupInput gdiplusStartupInput;
//     ULONG_PTR           gdiplusToken;
//     GdiplusStartup( &gdiplusToken, &gdiplusStartupInput, NULL );

	SetCurrentDirectory( "layout" );
	new CSystem( "System.xml" );
	IPropertySet* pSet = CPropertyAssist::GetSingletonPtr()->GetPropertySet( "CTouchList" );
	
  	LogicTest* pTest = new LogicTest();
  	REG_GOBAL_MEMBER_FUNC( "Login::Click", LogicTest::Test, pTest, LogicTest );
  	IWndTree* pTree2 = const_cast<IWndTree*>(CWindowManage::GetSingletonPtr()->GetWindowTree( "TPDlg" ));
   	if ( pTree2 == 0 )
  	{
  		return FALSE;
  	}
  	WndInfo* pInfo = pTree2->GetItemData();
	pInfo->pWnd->ShowWindow( SW_SHOW );
  	m_pMainWnd = pInfo->pWnd;

	pTree2 = const_cast<IWndTree*>(CWndTreeHelp::GetWindow( "TPDlg1", pTree2 ));
	pInfo = pTree2->GetItemData();
	CTouchList* pList = dynamic_cast<CTouchList*>(pInfo->pWnd) ;
	pList->AddItem( CItemFactory::GetSingletonPtr()->CreateItem( "ImageItem") );
	pList->AddItem( CItemFactory::GetSingletonPtr()->CreateItem( "TextItem") );
	pList->AddItem( CItemFactory::GetSingletonPtr()->CreateItem( "ImageItem") );
	
 	return TRUE;

// 	CBmpWnd* pWnd = new CBmpWnd( 0, "Name", CRect(0,0,100,100), NULL, 0 , "1.bmp" , GETUNIQID );
//   	pWnd->ShowWindow( SW_SHOW );
//  	m_pMainWnd = pWnd;
//  	return TRUE;

  	CWindowTestDlg dlg;// = new CWindowTestDlg(NULL);
 //	dlg->Create( CWindowTestDlg::IDD, NULL );
  	m_pMainWnd = &dlg;
 //	dlg->ShowWindow( SW_SHOW );
//  	return TRUE;
 	int nResponse = dlg.DoModal();
 	if (nResponse == IDOK)
 	{
 		// TODO: Place code here to handle when the dialog is
 		//  dismissed with OK
 	}
 	else if (nResponse == IDCANCEL)
 	{
 		// TODO: Place code here to handle when the dialog is
 		//  dismissed with Cancel
 	}


	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}

BOOL CWindowTestApp::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	if ( pMsg->message == WM_LBUTTONUP )
	{
		if ( CWndMsgEventManage::GetSingletonPtr() != 0 )
		{
			CWndMsgEventManage::GetSingletonPtr()->TransMsg( pMsg );
		}		
	}
	return CWinApp::PreTranslateMessage(pMsg);
}
