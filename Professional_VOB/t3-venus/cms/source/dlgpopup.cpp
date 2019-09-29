// dlgpopup.cpp : implementation file
//

#include "stdafx.h"
#include "cms.h"
#include "dlgpopup.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgPopup dialog


CDlgPopup::CDlgPopup(CWnd* pParent /*=NULL*/)
	: CTransparentBaseDlg(CDlgPopup::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgPopup)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgPopup::DoDataExchange(CDataExchange* pDX)
{
	CTransparentBaseDlg::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgPopup)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgPopup, CTransparentBaseDlg)
	//{{AFX_MSG_MAP(CDlgPopup)
		// NOTE: the ClassWizard will add message map macros here
		ON_WM_MOVE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgPopup message handlers

void CDlgPopup::OnMove( int x, int y )
{
	//Òþ²ØË«Á÷´°¿Ú 2013.2.1 yjj
    if ( IsWindowVisible() )
    {
	    CMsgDispatch::SendMessage( WM_CMS_HIDE_VEDIO ,0 , 0 );
    }
}
