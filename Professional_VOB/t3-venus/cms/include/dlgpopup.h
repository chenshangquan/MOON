#if !defined(AFX_DLGPOPUP_H__E817CDD3_967E_4AAD_947D_587D28AA54DB__INCLUDED_)
#define AFX_DLGPOPUP_H__E817CDD3_967E_4AAD_947D_587D28AA54DB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// dlgpopup.h : header file
#include "transparentbasedlg.h"
 
/////////////////////////////////////////////////////////////////////////////
// CDlgPopup dialog

class CDlgPopup : public CTransparentBaseDlg
{
// Construction
public:
	CDlgPopup(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgPopup)
	enum { IDD = IDD_DLG_POPUP };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgPopup)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	afx_msg void OnMove( int x, int y );
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgPopup)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPOPUP_H__E817CDD3_967E_4AAD_947D_587D28AA54DB__INCLUDED_)
