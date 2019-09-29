// fileManager.cpp : Defines the entry point for the application.
//

#include "stdafx.h" 
//#include "DUIDialog.h"  
#include "mainframelogic.h" 
int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	//  ×¢²áLogic 
	CMainFrameLogic* p = CMainFrameLogic::GetSingletonPtr();
	REG_LOGIC( p, p->GetClassName()  ); 


	CPaintManagerUI::SetInstance( hInstance );

	TCHAR chPath[MAX_PATH] = {0};
	wcscat( chPath, CPaintManagerUI::GetInstancePath() );
	wcscat( chPath, _T("skin\\filemanager\\") );
	CPaintManagerUI::SetResourcePath( chPath );
	//CPaintManagerUI::SetResourceZip( _T("skin.zip") );
	
	CDlgManager::GetSingletonPtr()->InitDlgMap(_T("dlgmap.xml"));
	CDUIDialog *pDlg = CDlgManager::GetSingletonPtr()->FindDlgByName(_T("mainframe") ) ;
	::ShowWindow( pDlg->GetHWND(),SW_SHOW );



// 	CDUIDialog *pDlg = new CDUIDialog(_T("main_frame.xml"));
// 	 
// 	ASSERT( NULL != pDlg );
// 	pDlg->Create( NULL,_T("UIDEMO"),  WS_POPUPWINDOW | WS_CAPTION , WS_EX_WINDOWEDGE);
// 	
// 	::ShowWindow( pDlg->GetHWND(),SW_SHOW );

	CPaintManagerUI::MessageLoop();

	return 0;
}

 