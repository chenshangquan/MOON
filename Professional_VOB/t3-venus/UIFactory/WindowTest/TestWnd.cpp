// TestWnd.cpp : implementation file
//

#include "stdafx.h"
#include "WindowTest.h"
#include "TestWnd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTestWnd dialog


CTestWnd::CTestWnd(CWnd* pParent /*=NULL*/)
	: CDialog(CTestWnd::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTestWnd)
	//}}AFX_DATA_INIT
}


void CTestWnd::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTestWnd)
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTestWnd, CDialog)
	//{{AFX_MSG_MAP(CTestWnd)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestWnd message handlers

void CTestWnd::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here	
	CUILayoutHelp::LayoutUI( "TPDlg");
}