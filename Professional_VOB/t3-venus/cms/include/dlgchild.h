#if !defined(AFX_DLGCHILD_H__CFA810F1_303B_4A0A_BBF7_465259725327__INCLUDED_)
#define AFX_DLGCHILD_H__CFA810F1_303B_4A0A_BBF7_465259725327__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// dlgchild.h : header file
//
 
#include "cms.h"
#include "transparentbasedlg.h"
 
 
/////////////////////////////////////////////////////////////////////////////
// CDlgChild dialog

class CDlgChild : public CTransparentBaseDlg
{
// Construction
public:
	CDlgChild(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgChild)
	enum { IDD = IDD_DLG_CHILD };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgChild)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgChild)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG

    afx_msg LRESULT OnRedrawUI( WPARAM wParam, LPARAM lParam );

	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGCHILD_H__CFA810F1_303B_4A0A_BBF7_465259725327__INCLUDED_)
