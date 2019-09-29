#if !defined(AFX_TESTWND_H__FA7E91E6_2298_4277_AB74_9B51C905AF26__INCLUDED_)
#define AFX_TESTWND_H__FA7E91E6_2298_4277_AB74_9B51C905AF26__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TestWnd.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTestWnd dialog

class CTestWnd : public CDialog
{
// Construction
public:
	CTestWnd(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CTestWnd)
	enum { IDD = IDD_DIALOG1 };
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestWnd)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTestWnd)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTWND_H__FA7E91E6_2298_4277_AB74_9B51C905AF26__INCLUDED_)
