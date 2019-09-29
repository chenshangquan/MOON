#if !defined(AFX_POPUPDLG_H__4BC92C5B_B09B_4F0F_8B6A_6CBC7CCA49BF__INCLUDED_)
#define AFX_POPUPDLG_H__4BC92C5B_B09B_4F0F_8B6A_6CBC7CCA49BF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// popupdlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPopupDlg dialog

class CPopupDlg : public CDialog
{
// Construction
public:
	CPopupDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPopupDlg)
	enum { IDD = IDD_POPUP_DLG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPopupDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPopupDlg)
		// NOTE: the ClassWizard will add member functions here
	HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
    void OnShowWindow(BOOL bShow, UINT nStatus);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_POPUPDLG_H__4BC92C5B_B09B_4F0F_8B6A_6CBC7CCA49BF__INCLUDED_)
