// WndFactory.cpp: implementation of the CWndFactory class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "WindowTest.h"
#include "TestWnd.h"
#include "WndFactory.h"
#include "MfcDefaultArgs.h"

// #ifdef _DEBUG
// #undef THIS_FILE
// static char THIS_FILE[]=__FILE__;
// #define new DEBUG_NEW
// #endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Window* CWindowFactory::Create( IArgs& iArgs )
{
	try
	{
		Args_WindowCreate& args = dynamic_cast<Args_WindowCreate&>(iArgs);
		DWORD dwStyle = 0;
		CWindowDefaultStyleMap::StringToStyle( args.m_strStyle, dwStyle );

		CBmpWnd* pWnd = new CBmpWnd();
// 		CTestWnd* pTestWnd = new CTestWnd( args.m_pParent );
// 		pTestWnd->Create( CTestWnd::IDD, args.m_pParent );
// 		pTestWnd->SetWindowText( args.m_strName.c_str() );
// 		pTestWnd->ModifyStyle( 0, IWindowFactory::m_dwDefaultStyle );	
		return pWnd;
	}
	catch( bad_cast )
	{
		return 0;
	}
	
}
