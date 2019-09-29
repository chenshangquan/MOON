// WindowTestDlg.h : header file
//

#if !defined(AFX_WINDOWTESTDLG_H__FFF50179_D3DE_4173_A4E0_140EC79D84E7__INCLUDED_)
#define AFX_WINDOWTESTDLG_H__FFF50179_D3DE_4173_A4E0_140EC79D84E7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CWindowTestDlg dialog
class CWindowTestDlg : public CDialog
{
// Construction
public:
	CWindowTestDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CWindowTestDlg)
	enum { IDD = IDD_WINDOWTEST_DIALOG };
	CEdit	m_editsave;
	CListBox	m_list;
	CEdit	m_edit;
	CEdit	m_edit2;
	CEdit	m_edit3;
	CString	m_strFile;
	CString	m_strFile1;
	CString	m_strFile2;
	CString	m_strSave;
	CFlatButton m_btn;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWindowTestDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
	void Print( IWndTree* pTree );
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CWindowTestDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButton1();
	afx_msg void OnButton2();
	afx_msg void OnButton3();
	afx_msg void OnButton4();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WINDOWTESTDLG_H__FFF50179_D3DE_4173_A4E0_140EC79D84E7__INCLUDED_)
