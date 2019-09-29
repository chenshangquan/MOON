// popupdlg.cpp : implementation file
//

#include "stdafx.h"
#include "cms.h"
#include "popupdlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPopupDlg dialog


CPopupDlg::CPopupDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPopupDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPopupDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CPopupDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPopupDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPopupDlg, CDialog)
	//{{AFX_MSG_MAP(CPopupDlg)
	//ON_WM_CTLCOLOR()
		// NOTE: the ClassWizard will add message map macros here
    ON_WM_SHOWWINDOW()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPopupDlg message handlers

HBRUSH CPopupDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
 
/*	switch (nCtlColor)
	{
	case CTLCOLOR_DLG:
		HBRUSH aBrush;
		aBrush = CreateSolidBrush(RGB(0, 0, 0));
		hbr = aBrush;
		DeleteObject(aBrush);			//É¾³ý»­Ë¢,·ÀÖ¹gdi¶ÔÏóÐ¹Â¶
		break;
	}
 */
	return hbr;
}

//Bug00169236 2014Äê1ÔÂ16ÈÕ
void CPopupDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
    if ( nStatus == SW_PARENTCLOSING && bShow == FALSE )
    {
        //Òþ²ØË«Á÷´°¿Ú
		CMsgDispatch::SendMessage( WM_CMS_HIDE_VEDIO ,0 , 0 );
    }
}
