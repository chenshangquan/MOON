// dlgoverlapped.cpp : implementation file
//

#include "stdafx.h"
#include "cms.h"
#include "dlgoverlapped.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgOverLapped dialog


CDlgOverLapped::CDlgOverLapped(CWnd* pParent /*=NULL*/)
: CTransparentBaseDlg(CDlgOverLapped::IDD,pParent)
{
	//{{AFX_DATA_INIT(CDlgOverLapped)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgOverLapped::DoDataExchange(CDataExchange* pDX)
{
	CTransparentBaseDlg::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgOverLapped)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgOverLapped, CTransparentBaseDlg)
	//{{AFX_MSG_MAP(CDlgOverLapped)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgOverLapped message handlers
