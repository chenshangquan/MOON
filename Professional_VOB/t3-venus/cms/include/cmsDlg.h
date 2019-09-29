// cmsDlg.h : header file
//

#if !defined(AFX_CMSDLG_H__51AC4774_D04E_4582_94BC_4E4B2E70E42B__INCLUDED_)
#define AFX_CMSDLG_H__51AC4774_D04E_4582_94BC_4E4B2E70E42B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CCmsDlg dialog

class CCmsDlg : public CDialog
{
// Construction
public:
	CCmsDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CCmsDlg)
	enum { IDD = IDD_CMS_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCmsDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CCmsDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBtnTestCns(); 
	afx_msg void OnBtnTestUms();
	afx_msg void OnBtnTestUifactory();
	virtual void OnOK();

    afx_msg void OnWindowPosChanging(WINDOWPOS FAR* lpwndpos);

	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CMSDLG_H__51AC4774_D04E_4582_94BC_4E4B2E70E42B__INCLUDED_)
